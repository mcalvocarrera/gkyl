-- Plasma ------------------------------------------------------------------------
local Plasma = require ("App.PlasmaOnCartGrid").PassiveAdvection()

local ux = 1
local uy = 1

local Lx = 2
local Ly = 1

local function gaussian(t, xn)
   local r2 = (xn[1]-0.5)^2 + (xn[2]-0.5)^2
   return math.exp(-50*r2)
end
local function cylinder(t, xn)
   local r2 = (xn[1]-0.5)^2 + (xn[2]-0.5)^2
   if r2 < 0.25^2 then
      return 1.0
   end
   return 1.0e-5
end
local function step(t, xn)
   local r2 = (xn[1]-0.5)^2
   if r2 < 0.25^2 then
      return 1.0
   end
   return 1.0e-5
end
local function squareHat(t, xn)
   local rx2, ry2 = (xn[1]-Lx/2)^2, (xn[2]-Ly/2)^2
   if rx2 < (Lx/4)^2 and ry2 < (Ly/4)^2 then
      return 1.0
   end
   return 1.0e-10
end
local function expTent(t, xn)
   local r = math.sqrt((xn[1]-0.5)^2 + (xn[2]-0.5)^2)
   return math.exp(-10*r)
end

plasmaApp = Plasma.App {
   logToFile = true,

   tEnd        = 2,                -- End time.
   nFrame      = 1,                -- Number of output frames.
   lower       = {0, 0},           -- Configuration space lower left.
   upper       = {Lx, Ly},         -- Configuration space upper right.
   cells       = {16, 16},         -- Configuration space cells.
   basis       = "serendipity",    -- One of "serendipity" or "maximal-order".
   polyOrder   = 1,                -- Polynomial order.
   timeStepper = "rk3",            -- One of "rk2" or "rk3".
   --maximumDt = 0.01,
   
   -- Decomposition for configuration space.
   decompCuts = {1, 1},    -- Cuts in each configuration direction.
   useShared  = false,     -- If to use shared memory.

   -- Boundary conditions for configuration space.
   periodicDirs = {2}, -- Periodic directions

   -- Fluid species.
   fluid = Plasma.Species {
      -- Initial conditions.
      init            = function(t, xn)
        local n = squareHat(t,xn)
        local vx = ux
        local vy = uy
        return n, vx, 0
      end,
        
      evolve = true, -- Evolve species?
      diagnostics = {"intMom"},
      bcx = {Plasma.AbsorbBC{},
             Plasma.AbsorbBC{}},
   },
}
-- Run application.
plasmaApp:run()
