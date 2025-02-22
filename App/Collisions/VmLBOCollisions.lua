-- Gkyl ------------------------------------------------------------------------
--
-- PlasmaOnCartGrid support code: Vlasov LB Collision operator
--
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

local CollisionsBase = require "App.Collisions.CollisionsBase"
local Constants      = require "Lib.Constants"
local DataStruct     = require "DataStruct"
local Proto          = require "Lib.Proto"
local Time           = require "Lib.Time"
local Updater        = require "Updater"
local VmLBOconstNuEq = require "Eq.VmLBO"
local xsys           = require "xsys"
local Lin            = require "Lib.Linalg"
local Mpi            = require "Comm.Mpi"
local lume           = require "Lib.lume"
local DiagsApp       = require "App.Diagnostics.SpeciesDiagnostics"
local DiagsImplBase  = require "App.Diagnostics.DiagnosticsImplBase"

-- ............... IMPLEMENTATION OF DIAGNOSTICS ................. --
-- Diagnostics could be placed in a separate file if they balloon in
-- number. But if we only have one or two we can just place it here.

-- ~~~~ Source integrated over the domain ~~~~~~~~~~~~~~~~~~~~~~
local VmLBODiagsImpl = function()
   -- IMPORTANT: this diagnostic is only here for testing!!! do not use (MF).
   local _collOut = Proto(DiagsImplBase)
   function _collOut:fullInit(diagApp, mySpecies, fieldIn, owner)
      self.field = mySpecies:allocDistf()
      self.owner = owner 
      self.done  = false
   end
   function _collOut:getType() return "grid" end
   function _collOut:advance(tm, inFlds, outFlds)
      local specIn = inFlds[1]
      self.field:copy(self.owner.collOut)
   end

   return {collOut = _collOut}
end

-- .................... END OF DIAGNOSTICS ...................... --

-- VmLBOCollisions ---------------------------------------------------------------
--
-- Lenard-Bernstein Collision operator.
-- Actually dates back to Lord Rayleigh, Philos. Mag. 32, 424 (1891).
-- Really LBO=the Dougherty operator.
--------------------------------------------------------------------------------

local VmLBOCollisions = Proto(CollisionsBase)

-- This ctor simply stores what is passed to it and defers actual
-- construction to the fullInit() method below.
function VmLBOCollisions:init(tbl)
   self.tbl = tbl
end

-- Function to find the index of an element in table.
local function findInd(tblIn, el)
   for i, v in ipairs(tblIn) do
      if v == el then
         return i
      end
   end
   return #tblIn+1    -- If not found return a number larger than the length of the table.
end

-- Actual function for initialization. This indirection is needed as
-- we need the app top-level table for proper initialization.
function VmLBOCollisions:fullInit(speciesTbl)
   local tbl = self.tbl -- Previously stored table.

   self.collKind = "VmLBO"    -- Type of collisions model. Useful at the species app level.

   self.collidingSpecies = assert(tbl.collideWith, "App.VmLBOCollisions: Must specify names of species to collide with in 'collideWith'.")

   -- First determine if self-species and/or cross-species collisions take place,
   -- and (if cross-collisions=true) put the names of the other colliding species in a list.
   local selfSpecInd = findInd(self.collidingSpecies, self.speciesName)
   if selfSpecInd < (#self.collidingSpecies+1) then
      self.selfCollisions = true                 -- Apply self-species collisions.
      if #self.collidingSpecies > 1 then
         self.crossCollisions = true             -- Apply cross-species collisions.
         self.crossSpecies    = lume.clone(self.collidingSpecies)
         table.remove(self.crossSpecies, selfSpecInd)
      else
         self.crossCollisions = false            -- Don't apply cross-species collisions.
      end
   else
      self.selfCollisions  = false               -- Don't apply self-species collisions.
      self.crossCollisions = true                -- Apply cross-species collisions.
      self.crossSpecies    = lume.clone(self.collidingSpecies)    -- All species in collidingSpecies must be cross-species.
   end

   -- Now establish if user wants constant or spatially varying collisionality.
   -- For constant nu, separate self and cross collision frequencies.
   self.collFreqs          = tbl.frequencies -- List of collision frequencies, if using spatially constant nu.
   if self.collFreqs then
      -- Collisionality, provided by user, will remain constant in time.
      self.timeDepNu = false

      -- Ensure that collFreqs inputs are either all numbers, or all functions.
      local collFreqType = type(self.collFreqs[1])
      if (#self.collFreqs>1) then
         for iC = 2,#self.collFreqs do
            assert(collFreqType == type(self.collFreqs[iC]), "App.VmLBOCollisions: frequencies must either all be numbers, or all be functions")
         end
      end
      if (collFreqType == "number") then
         self.varNu         = false    -- Not spatially varying nu.
      else -- collFreqType must be a function, which we assume to be spatially dependent. 
         self.varNu         = true
      end
      -- For now only cell-wise constant nu is implemented.
      self.cellConstNu      = true     -- Cell-wise constant nu?
      if self.selfCollisions then
         self.collFreqSelf  = self.collFreqs[selfSpecInd]
      end
      if self.crossCollisions then
         self.collFreqCross = lume.clone(self.collFreqs)
         table.remove(self.collFreqCross, selfSpecInd)
      end
   else
      -- Collisionality not provided by user. It will be calculated in time.
      self.timeDepNu = true

      self.varNu        = true                 -- Spatially varying nu.
      self.mass         = speciesTbl.mass      -- Mass of this species.
      self.charge       = speciesTbl.charge    -- Charge of this species.
      -- For now only cell-wise constant nu is implemented.
      self.cellConstNu  = true     -- Cell-wise constant nu?
      -- If no time-constant collision frequencies provided ('frequencies'), user can specify
      -- 'normNu' list of collisionalities normalized by T_0^(3/2)/n_0 evaluated somewhere in the
      -- simulation (see Gkeyll website for exact normalization). Otherwise code compute Spitzer
      -- collisionality from scratch.
      self.normNuIn     = tbl.normNu
      -- normNuSelf, epsilon0 and elemCharge may not used, but are
      -- initialized to avoid if-statements in advance method.
      if self.normNuIn then
         self.userInputNormNu = true
         if self.selfCollisions then
            self.normNuSelf  = self.normNuIn[selfSpecInd]
         end
         if self.crossCollisions then
            self.normNuCross = lume.clone(self.normNuIn)
            table.remove(self.normNuCross, selfSpecInd)
         end
      else
         self.userInputNormNu = false
         if self.selfCollisions then
            self.normNuSelf  = 0.0
         end
         if self.crossCollisions then
            self.normNuCross = lume.clone(self.collidingSpecies)
            table.remove(self.normNuCross, selfSpecInd)
            for i, _ in ipairs(self.normNuCross) do self.normNuCross[i] = 0.0 end 
         end
      end
      -- Check for constants epsilon_0, elementary charge e, and Planck's constant/2pi. If not use default value.
      local epsilon0In = tbl.epsilon0
      if epsilon0In then
         self.epsilon0 = epsilon0In
      else
         self.epsilon0 = Constants.EPSILON0
      end
      local elemChargeIn = tbl.elemCharge
      if elemChargeIn then
         self.elemCharge = elemChargeIn
      else
         self.elemCharge = Constants.ELEMENTARY_CHARGE
      end
      local hBarIn = tbl.hBar
      if hBarIn then
         self.hBar = hBarIn
      else
         self.hBar = Constants.PLANCKS_CONSTANT_H/(2.0*Constants.PI)
      end
   end

   if self.crossCollisions then
      self.mass       = speciesTbl.mass      -- Mass of this species.
      self.charge     = speciesTbl.charge    -- Charge of this species.
      local betaGreeneIn = tbl.betaGreene    -- Can specify 'betaGreene' free parameter in Grene cross-species collisions.
      if betaGreeneIn then
         self.betaGreene = betaGreeneIn
      else
         self.betaGreene = 0.0   -- Default value.
      end
   end

   if tbl.nuFrac then
      self.nuFrac = tbl.nuFrac
   else
      self.nuFrac = 1.0
   end

   -- fluxType used for selecting which type of numerical flux function to use in velocity space
   -- defaults to "penalty" in Eq object, supported options: "penalty," "upwind".
   self.fluxType = speciesTbl.vFlux or "penalty"
   assert(self.fluxType=="upwind" or self.fluxType=="penalty", "App.VmLBOCollisions: 'fluxType' must be 'upwind' or 'penalty'.")

   self.cfl = 0.0    -- Will be replaced.

   self.timers = {nonSlvr = 0.}
end

function VmLBOCollisions:setName(nm) self.name = self.speciesName.."_"..nm end
function VmLBOCollisions:setSpeciesName(nm) self.speciesName = nm end
function VmLBOCollisions:setCfl(cfl) self.cfl = cfl end
function VmLBOCollisions:setConfBasis(basis) self.confBasis = basis end
function VmLBOCollisions:setConfGrid(grid) self.confGrid = grid end
function VmLBOCollisions:setPhaseBasis(basis) self.phaseBasis = basis end
function VmLBOCollisions:setPhaseGrid(grid) self.phaseGrid = grid end

function VmLBOCollisions:createSolver(mySpecies, extField)
   self.vdim      = self.phaseGrid:ndim() - self.confGrid:ndim()

   self.cNumBasis = self.confBasis:numBasis()

   -- Maximum velocity of the velocity grid (and its square).
   self.vMax   = Lin.Vec(self.vdim)
   for vd = 1,self.vdim do
      self.vMax[vd]   = self.phaseGrid:upper(self.confGrid:ndim()+vd)
   end
   self.vMaxSq = self.vMax[1] 
   for vd = 1,self.vdim do
      if (self.vMaxSq < self.vMax[vd]) then
         self.vMaxSq = self.vMax[vd]
      end
   end
   self.vMaxSq = self.vMaxSq^2

   -- Intemediate storage for output of collisions.
   self.collOut = DataStruct.Field {
      onGrid        = self.phaseGrid,
      numComponents = self.phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Sum of flow velocities in vdim directions multiplied by respective collisionalities.
   self.nuUSum = DataStruct.Field {
      onGrid        = self.confGrid,
      numComponents = self.cNumBasis*self.vdim,
      ghost         = {1, 1},
   }
   -- Sum of squared thermal speeds, vthSq=T/m, multiplied by respective collisionalities.
   self.nuVtSqSum = DataStruct.Field {
      onGrid        = self.confGrid,
      numComponents = self.cNumBasis,
      ghost         = {1, 1},
   }

   -- Zero-flux BCs in the velocity dimensions.
   local zfd = { }
   for d = 1, self.vdim do
      zfd[d] = self.confGrid:ndim() + d
   end

   if self.varNu then
      -- Self-species collisionality, which varies in space.
      self.nuVarXSelf = DataStruct.Field {
         onGrid        = self.confGrid,
         numComponents = self.cNumBasis,
         ghost         = {1, 1},
      }
      -- Collisionality, nu, summed over all species pairs.
      self.nuSum = DataStruct.Field {
         onGrid        = self.confGrid,
         numComponents = self.cNumBasis,
         ghost         = {1, 1},
      }
      if self.timeDepNu then 
         -- Updater to compute spatially varying (Spitzer) nu.
         self.spitzerNu = Updater.SpitzerCollisionality {
            onGrid           = self.confGrid,
            confBasis        = self.confBasis,
            useCellAverageNu = self.cellConstNu,
            willInputNormNu  = self.userInputNormNu,
            elemCharge       = self.elemCharge,
            epsilon0         = self.epsilon0,
            hBar             = self.hBar,
            nuFrac           = self.nuFrac,
         }
      elseif self.selfCollisions then
         local projectUserNu = Updater.ProjectOnBasis {
            onGrid   = self.confGrid,
            basis    = self.confBasis,
            evaluate = self.collFreqSelf,
            onGhosts = false
         }
         projectUserNu:advance(0.0, {}, {self.nuVarXSelf})
      end
      -- Weak multiplication to multiply nu(x) with u or vtSq.
      self.confMul = Updater.CartFieldBinOp {
         onGrid    = self.confGrid,
         weakBasis = self.confBasis,
         operation = "Multiply",
      }
   else
      self.nuSum    = 0.0    -- Assigned in advance method.
   end
   -- Lenard-Bernstein equation.
   self.equation = VmLBOconstNuEq {
      phaseBasis       = self.phaseBasis,
      confBasis        = self.confBasis,
      vUpper           = self.vMax,
      varyingNu        = self.varNu,
      useCellAverageNu = self.cellConstNu,
      gridID           = self.phaseGrid:id(),
      fluxType         = self.fluxType,
   }
   self.collisionSlvr = Updater.HyperDisCont {
      onGrid             = self.phaseGrid,
      basis              = self.phaseBasis,
      cfl                = self.cfl,
      equation           = self.equation,
      updateDirections   = zfd,    -- Only update velocity directions.
      zeroFluxDirections = zfd,
   }
   if self.crossCollisions then
      if self.varNu then
         -- Temporary collisionality fields.
         self.nuCrossSelf = DataStruct.Field {
            onGrid        = self.confGrid,
            numComponents = self.cNumBasis,
            ghost         = {1, 1},
         }
         self.nuCrossOther = DataStruct.Field {
            onGrid        = self.confGrid,
            numComponents = self.cNumBasis,
            ghost         = {1, 1},
         }
         -- Cross-collision u and vtSq multiplied by collisionality.
         self.nuUCross = DataStruct.Field {
            onGrid        = self.confGrid,
            numComponents = self.cNumBasis*self.vdim,
            ghost         = {1, 1},
         }
         self.nuVtSqCross = DataStruct.Field {
            onGrid        = self.confGrid,
            numComponents = self.confBasis:numBasis(),
            ghost         = {1, 1},
         }
      else
         self.nuCrossSelf  = 0.0
         self.nuCrossOther = 0.0
      end
      -- Updater to compute cross-species primitive moments.
      self.primMomCross = Updater.CrossPrimMoments {
         onGrid           = self.confGrid,
         phaseBasis       = self.phaseBasis,
         confBasis        = self.confBasis,
         operator         = "VmLBO",
         betaGreene       = self.betaGreene, 
         varyingNu        = self.varNu,
         useCellAverageNu = self.cellConstNu,
      }
   end

   -- Number of cells in which number density was negative (somewhere).
   self.primMomLimitCrossings = DataStruct.DynVector {
      numComponents = 1,
   }
   self.primMomCrossLimitL = Lin.Vec(1)
   self.primMomCrossLimitG = Lin.Vec(1)
   -- Factor dividing zeroth-coefficient in configuration space cell average.
   self.cellAvFac          = 1.0/math.sqrt(2.0^self.confGrid:ndim())
end

function VmLBOCollisions:createDiagnostics(mySpecies, field)
   -- Create source diagnostics.
   self.diagnostics = nil
   if self.tbl.diagnostics then
      self.diagnostics = DiagsApp{implementation = VmLBODiagsImpl()}
      self.diagnostics:fullInit(mySpecies, field, self)
   end
   return self.diagnostics
end

function VmLBOCollisions:advance(tCurr, fIn, species, fRhsOut)

   -- Fetch coupling moments and primitive moments of this species.
   local selfMom     = species[self.speciesName]:fluidMoments()
   local primMomSelf = species[self.speciesName]:selfPrimitiveMoments()

   local tmNonSlvrStart = Time.clock()
   if self.varNu then
      self.nuSum:clear(0.0)
   else
      self.nuSum = 0.0
   end
   self.nuUSum:clear(0.0)
   self.nuVtSqSum:clear(0.0)

   if self.selfCollisions then

      -- NOTE: The following code is commented out because Vm users don't seem
      -- to be as worried about limit crossings as Gk users, so counting them
      -- is disabled for now. See the 'write' method as well.
      ---- Determine whether primitive moments cross limits based on
      ---- parallel flow speed and thermal speed squared.
      --self.primMomCrossLimitL[1] = 0
      --self.primMomCrossLimitG[1] = 0
      --local confIndexer          = self.velocity:genIndexer()
      --local uItr                 = self.velocity:get(1)
      --local vthSqItr             = self.vthSq:get(1)
      --for idx in self.velocity:localRangeIter() do
      --   self.velocity:fill(confIndexer(idx), uItr)
      --   self.vthSq:fill(confIndexer(idx), vthSqItr)
      --   local primCrossingFound = false
      --   for vd = 1,self.vdim do
      --      if (math.abs(uItr[(vd-1)*self.cNumBasis+1]*self.cellAvFac)>self.vMax[vd]) then
      --         uCrossingFound = true
      --         break
      --      end
      --   end
      --   local vthSq0 = vthSqItr[1]*self.cellAvFac

      --   if (uCrossingFound or (vthSq0<0) or (vthSq0>self.vMaxSq)) then
      --      self.primMomCrossLimitL[1] = self.primMomCrossLimitL[1]+1
      --   end
      --end
      --Mpi.Allreduce(self.primMomCrossLimitL:data(), self.primMomCrossLimitG:data(), 1,
      --              Mpi.DOUBLE, Mpi.SUM, self.confGrid:commSet().comm)
      --self.primMomLimitCrossings:appendData(tCurr+dt, self.primMomCrossLimitG)

      if self.varNu then
         if self.timeDepNu then
            -- Compute the Spitzer collisionality.
            self.spitzerNu:advance(tCurr, {self.charge, self.mass, selfMom[1], primMomSelf[2],
                                           self.charge, self.mass, selfMom[1], primMomSelf[2], self.normNuSelf}, {self.nuSum})
         else
            self.nuSum:copy(self.nuVarXSelf)
         end
         self.confMul:advance(tCurr, {self.nuSum, primMomSelf[1]}, {self.nuUSum})
         self.confMul:advance(tCurr, {self.nuSum, primMomSelf[2]}, {self.nuVtSqSum})
      else
         self.nuSum = self.collFreqSelf
         self.nuUSum:combine(self.collFreqSelf, primMomSelf[1])
         self.nuVtSqSum:combine(self.collFreqSelf, primMomSelf[2])
      end
   end    -- end if self.selfCollisions.

   if self.crossCollisions then

      local bCorrectionsSelf = species[self.speciesName]:boundaryCorrections()
      local starMomSelf      = species[self.speciesName]:starMoments()

      for sInd, otherNm in ipairs(self.crossSpecies) do

         local mOther            = species[otherNm]:getMass()
         local otherMom          = species[otherNm]:fluidMoments()
         local primMomOther      = species[otherNm]:selfPrimitiveMoments()
         local bCorrectionsOther = species[otherNm]:boundaryCorrections()
         local starMomOther      = species[otherNm]:starMoments()

         if self.varNu then
            if self.timeDepNu then
               -- Compute the Spitzer collisionality if another species hasn't already done so.
               local chargeOther = species[otherNm]:getCharge()
               if (not species[self.speciesName].momentFlags[6][otherNm]) then
                  self.spitzerNu:advance(tCurr, {self.charge, self.mass, selfMom[1], primMomSelf[2],
                                                 chargeOther, mOther, otherMom[1], primMomOther[2], self.normNuCross[sInd]},
                                                {species[self.speciesName].nuVarXCross[otherNm]})
                  species[self.speciesName].momentFlags[6][otherNm] = true
               end
               if (not species[otherNm].momentFlags[6][self.speciesName]) then
                  self.spitzerNu:advance(tCurr, {chargeOther, mOther, otherMom[1], primMomOther[2],
                                                 self.charge, self.mass, selfMom[1], primMomSelf[2], species[otherNm].collPairs[otherNm][self.speciesName].normNu},
                                                {species[otherNm].nuVarXCross[self.speciesName]})
                  species[otherNm].momentFlags[6][self.speciesName] = true
               end
            end
            self.nuCrossSelf:copy(species[self.speciesName].nuVarXCross[otherNm])
            self.nuCrossOther:copy(species[otherNm].nuVarXCross[self.speciesName])
         else
            self.nuCrossSelf  = self.collFreqCross[sInd]
            self.nuCrossOther = species[otherNm].collPairs[otherNm][self.speciesName].nu
         end

         if (not (species[self.speciesName].momentFlags[5][otherNm] and
                  species[otherNm].momentFlags[5][self.speciesName])) then
            -- Cross-primitive moments for the collision of these two species has not been computed.
            self.primMomCross:advance(tCurr, {self.mass, self.nuCrossSelf, selfMom, primMomSelf,
                                              mOther, self.nuCrossOther, otherMom, primMomOther,
                                              bCorrectionsSelf, starMomSelf, bCorrectionsOther, starMomOther},
                                             {species[self.speciesName].uCross[otherNm], species[self.speciesName].vtSqCross[otherNm], 
                                              species[otherNm].uCross[self.speciesName], species[otherNm].vtSqCross[self.speciesName]})

            species[self.speciesName].momentFlags[5][otherNm] = true
            species[otherNm].momentFlags[5][self.speciesName] = true
         end

         if self.varNu then
            self.confMul:advance(tCurr, {self.nuCrossSelf, species[self.speciesName].uCross[otherNm]}, {self.nuUCross})
            self.confMul:advance(tCurr, {self.nuCrossSelf, species[self.speciesName].vtSqCross[otherNm]}, {self.nuVtSqCross})

            -- Barrier over shared communicator before accumulate
            Mpi.Barrier(self.phaseGrid:commSet().sharedComm)

            self.nuSum:accumulate(1.0, self.nuCrossSelf)
            self.nuUSum:accumulate(1.0, self.nuUCross)
            self.nuVtSqSum:accumulate(1.0, self.nuVtSqCross)
         else
            self.nuSum = self.nuSum+self.nuCrossSelf

            -- Barrier over shared communicator before accumulate
            Mpi.Barrier(self.phaseGrid:commSet().sharedComm)

            self.nuUSum:accumulate(self.nuCrossSelf, species[self.speciesName].uCross[otherNm])
            self.nuVtSqSum:accumulate(self.nuCrossSelf, species[self.speciesName].vtSqCross[otherNm])
         end

      end    -- end loop over other species that this species collides with.

   end    -- end if self.crossCollisions.
   self.timers.nonSlvr = self.timers.nonSlvr + Time.clock() - tmNonSlvrStart

   -- Compute increment from collisions and accumulate it into output.
   self.collisionSlvr:advance(
      tCurr, {fIn, self.nuUSum, self.nuVtSqSum, self.nuSum}, {self.collOut})

   local tmNonSlvrStart = Time.clock()
   -- Barrier over shared communicator before accumulate
   Mpi.Barrier(self.phaseGrid:commSet().sharedComm)

   fRhsOut:accumulate(1.0, self.collOut)
   self.timers.nonSlvr = self.timers.nonSlvr + Time.clock() - tmNonSlvrStart
end

function VmLBOCollisions:write(tm, frame)
-- Since this doesn't seem to be as big a problem in Vm as in Gk, we comment this out for now.
--   self.primMomLimitCrossings:write(string.format("%s_%s.bp", self.speciesName, "primMomLimitCrossings"), tm, frame)
end

function VmLBOCollisions:totalTime()
   return self.collisionSlvr.totalTime + self.timers.nonSlvr
end
function VmLBOCollisions:slvrTime()
   return self.collisionSlvr.totalTime
end
function VmLBOCollisions:nonSlvrTime()
   return self.timers.nonSlvr
end

return VmLBOCollisions
