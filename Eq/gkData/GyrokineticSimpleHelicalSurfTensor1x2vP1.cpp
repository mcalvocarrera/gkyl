#include <GyrokineticModDecl.h>
double GyrokineticSimpleHelicalSurf1x2vTensor_xL_P1_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
{ 
  // bmagInv: 1/bmag.
  // BdriftX,BdriftY: x,y components of gradB/curvature drift.
  // q_,m_: species charge and mass.
  // cflL,cflR: CFL rate in left and right cells.
  // wL[NDIM],wR[NDIM]: cell-center in left and right cells.
  // dxvL[NDIM],dxvR[NDIM]: Cell length in left and right cells.
  // amax_in: maximum phase-space speed.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // fL,fR: Distribution function in left and right cells.
  // outL/outR: Output increment in left and right cells.

  double wxL = wL[0];
  double wxR = wR[0];
  double rdx2L = 2.0/dxvL[0];
  double rdx2R = 2.0/dxvR[0];
  double wvparL = wL[1];
  double wvparR = wR[1];
  double rdvpar2L = 2.0/dxvL[1];
  double rdvpar2R = 2.0/dxvR[1];
  double wmuL = wL[2];
  double wmuR = wR[2];
  double rdmu2L = 2.0/dxvL[2];
  double rdmu2R = 2.0/dxvR[2];

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;
  double wmuSqL = wL[2]*wL[2];
  double wmuSqR = wR[2]*wR[2];
  double rdmu2SqL = rdmu2L*rdmu2L;
  double rdmu2SqR = rdmu2R*rdmu2R;

  double hamilL[8]; 
  hamilL[0] = (0.2357022603955158*(3.0*rdvpar2SqL*(2.0*m_*wvparSqL+2.828427124746191*(bmag[0]*wmuL+phi[0]*q_))+2.0*m_))/rdvpar2SqL; 
  hamilL[1] = 2.0*phi[1]*q_; 
  hamilL[2] = (1.632993161855453*m_*wvparL)/rdvpar2L; 
  hamilL[3] = (1.154700538379252*bmag[0])/rdmu2L; 

  double BstarZdBmagL[8]; 
  BstarZdBmagL[0] = 2.0*cmag[0]; 

  double alphaL[4]; 
  alphaL[0] = (0.4330127018922193*BstarZdBmagL[0]*hamilL[2]*rdvpar2L)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgL = (0.1082531754730548*BstarZdBmagL[0]*hamilL[2]*rdvpar2L)/m_; 

  double incr[8]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgL>0) { 
  incr[0] = 0.25*alphaL[0]*(1.732050807568877*fL[1]+fL[0]); 
  incr[1] = -0.25*alphaL[0]*(3.0*fL[1]+1.732050807568877*fL[0]); 
  incr[2] = 0.25*alphaL[0]*(1.732050807568877*fL[4]+fL[2]); 
  incr[3] = 0.25*alphaL[0]*(1.732050807568877*fL[5]+fL[3]); 
  incr[4] = -0.25*alphaL[0]*(3.0*fL[4]+1.732050807568877*fL[2]); 
  incr[5] = -0.25*alphaL[0]*(3.0*fL[5]+1.732050807568877*fL[3]); 
  incr[6] = 0.25*alphaL[0]*(1.732050807568877*fL[7]+fL[6]); 
  incr[7] = -0.25*alphaL[0]*(3.0*fL[7]+1.732050807568877*fL[6]); 
  } else { 
  incr[0] = -0.25*alphaL[0]*(1.732050807568877*fR[1]-1.0*fR[0]); 
  incr[1] = 0.25*alphaL[0]*(3.0*fR[1]-1.732050807568877*fR[0]); 
  incr[2] = -0.25*alphaL[0]*(1.732050807568877*fR[4]-1.0*fR[2]); 
  incr[3] = -0.25*alphaL[0]*(1.732050807568877*fR[5]-1.0*fR[3]); 
  incr[4] = 0.25*alphaL[0]*(3.0*fR[4]-1.732050807568877*fR[2]); 
  incr[5] = 0.25*alphaL[0]*(3.0*fR[5]-1.732050807568877*fR[3]); 
  incr[6] = -0.25*alphaL[0]*(1.732050807568877*fR[7]-1.0*fR[6]); 
  incr[7] = 0.25*alphaL[0]*(3.0*fR[7]-1.732050807568877*fR[6]); 
  }
#elif upwindType == QUAD 
  double alphaOrdL;
  double fUpOrd[4];
  alphaOrdL = 0.5*alphaL[0]; 
  fUpOrd[0] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.3535533905932737*fR[6]+0.3535533905932737*fL[6]-0.6123724356957944*(fR[5]+fL[5]+fR[4]+fL[4])+0.3535533905932737*(fR[3]+fR[2])-0.3535533905932737*(fL[3]+fL[2])+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdL)-0.6123724356957944*fR[7]+0.6123724356957944*fL[7]+0.3535533905932737*(fR[6]+fL[6])+0.6123724356957944*(fR[5]+fR[4])-0.6123724356957944*(fL[5]+fL[4])-0.3535533905932737*(fR[3]+fL[3]+fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdL = 0.5*alphaL[0]; 
  fUpOrd[1] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.3535533905932737*fR[6]-0.3535533905932737*fL[6]-0.6123724356957944*(fR[5]+fL[5])+0.6123724356957944*(fR[4]+fL[4])+0.3535533905932737*fR[3]-0.3535533905932737*(fL[3]+fR[2])+0.3535533905932737*fL[2]+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdL)+0.6123724356957944*fR[7]-0.6123724356957944*fL[7]-0.3535533905932737*(fR[6]+fL[6])+0.6123724356957944*fR[5]-0.6123724356957944*(fL[5]+fR[4])+0.6123724356957944*fL[4]-0.3535533905932737*(fR[3]+fL[3])+0.3535533905932737*(fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdL = 0.5*alphaL[0]; 
  fUpOrd[2] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.3535533905932737*fR[6]-0.3535533905932737*fL[6]+0.6123724356957944*(fR[5]+fL[5])-0.6123724356957944*(fR[4]+fL[4])-0.3535533905932737*fR[3]+0.3535533905932737*(fL[3]+fR[2])-0.3535533905932737*fL[2]+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdL)+0.6123724356957944*fR[7]-0.6123724356957944*fL[7]-0.3535533905932737*(fR[6]+fL[6])-0.6123724356957944*fR[5]+0.6123724356957944*(fL[5]+fR[4])-0.6123724356957944*fL[4]+0.3535533905932737*(fR[3]+fL[3])-0.3535533905932737*(fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdL = 0.5*alphaL[0]; 
  fUpOrd[3] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.3535533905932737*fR[6]+0.3535533905932737*fL[6]+0.6123724356957944*(fR[5]+fL[5]+fR[4]+fL[4])-0.3535533905932737*(fR[3]+fR[2])+0.3535533905932737*(fL[3]+fL[2])+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdL)-0.6123724356957944*fR[7]+0.6123724356957944*fL[7]+0.3535533905932737*(fR[6]+fL[6])-0.6123724356957944*(fR[5]+fR[4])+0.6123724356957944*(fL[5]+fL[4])+0.3535533905932737*(fR[3]+fL[3]+fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 

  double fUp[4];
  fUp[0] = 0.5*(fUpOrd[3]+fUpOrd[2]+fUpOrd[1]+fUpOrd[0]); 
  fUp[1] = 0.5*(fUpOrd[3]-1.0*fUpOrd[2]+fUpOrd[1]-1.0*fUpOrd[0]); 
  fUp[2] = 0.5*(fUpOrd[3]+fUpOrd[2]-1.0*(fUpOrd[1]+fUpOrd[0])); 
  fUp[3] = 0.5*(fUpOrd[3]-1.0*(fUpOrd[2]+fUpOrd[1])+fUpOrd[0]); 

  incr[0] = 0.3535533905932737*alphaL[0]*fUp[0]; 
  incr[1] = -0.6123724356957944*alphaL[0]*fUp[0]; 
  incr[2] = 0.3535533905932737*alphaL[0]*fUp[1]; 
  incr[3] = 0.3535533905932737*alphaL[0]*fUp[2]; 
  incr[4] = -0.6123724356957944*alphaL[0]*fUp[1]; 
  incr[5] = -0.6123724356957944*alphaL[0]*fUp[2]; 
  incr[6] = 0.3535533905932737*alphaL[0]*fUp[3]; 
  incr[7] = -0.6123724356957944*alphaL[0]*fUp[3]; 

#endif 
  outR[0] += incr[0]*rdx2R; 
  outR[1] += incr[1]*rdx2R; 
  outR[2] += incr[2]*rdx2R; 
  outR[3] += incr[3]*rdx2R; 
  outR[4] += incr[4]*rdx2R; 
  outR[5] += incr[5]*rdx2R; 
  outR[6] += incr[6]*rdx2R; 
  outR[7] += incr[7]*rdx2R; 

  outL[0] += -1.0*incr[0]*rdx2L; 
  outL[1] += incr[1]*rdx2L; 
  outL[2] += -1.0*incr[2]*rdx2L; 
  outL[3] += -1.0*incr[3]*rdx2L; 
  outL[4] += incr[4]*rdx2L; 
  outL[5] += incr[5]*rdx2L; 
  outL[6] += -1.0*incr[6]*rdx2L; 
  outL[7] += incr[7]*rdx2L; 

  return std::abs(alphaSurfAvgL); 
} 
double GyrokineticSimpleHelicalSurf1x2vTensor_xR_P1_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
{ 
  // bmagInv: 1/bmag.
  // BdriftX,BdriftY: x,y components of gradB/curvature drift.
  // q_,m_: species charge and mass.
  // cflL,cflR: CFL rate in left and right cells.
  // wL[NDIM],wR[NDIM]: cell-center in left and right cells.
  // dxvL[NDIM],dxvR[NDIM]: Cell length in left and right cells.
  // amax_in: maximum phase-space speed.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // fL,fR: Distribution function in left and right cells.
  // outL/outR: Output increment in left and right cells.

  double wxL = wL[0];
  double wxR = wR[0];
  double rdx2L = 2.0/dxvL[0];
  double rdx2R = 2.0/dxvR[0];
  double wvparL = wL[1];
  double wvparR = wR[1];
  double rdvpar2L = 2.0/dxvL[1];
  double rdvpar2R = 2.0/dxvR[1];
  double wmuL = wL[2];
  double wmuR = wR[2];
  double rdmu2L = 2.0/dxvL[2];
  double rdmu2R = 2.0/dxvR[2];

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;
  double wmuSqL = wL[2]*wL[2];
  double wmuSqR = wR[2]*wR[2];
  double rdmu2SqL = rdmu2L*rdmu2L;
  double rdmu2SqR = rdmu2R*rdmu2R;

  double hamilR[8]; 
  hamilR[0] = (0.2357022603955158*(3.0*rdvpar2SqR*(2.0*m_*wvparSqR+2.828427124746191*(bmag[0]*wmuR+phi[0]*q_))+2.0*m_))/rdvpar2SqR; 
  hamilR[1] = 2.0*phi[1]*q_; 
  hamilR[2] = (1.632993161855453*m_*wvparR)/rdvpar2R; 
  hamilR[3] = (1.154700538379252*bmag[0])/rdmu2R; 

  double BstarZdBmagR[8]; 
  BstarZdBmagR[0] = 2.0*cmag[0]; 

  double alphaR[4]; 
  alphaR[0] = (0.4330127018922193*BstarZdBmagR[0]*hamilR[2]*rdvpar2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = (0.1082531754730548*BstarZdBmagR[0]*hamilR[2]*rdvpar2R)/m_; 

  double incr[8]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgR>0) { 
  incr[0] = 0.25*alphaR[0]*(1.732050807568877*fL[1]+fL[0]); 
  incr[1] = -0.25*alphaR[0]*(3.0*fL[1]+1.732050807568877*fL[0]); 
  incr[2] = 0.25*alphaR[0]*(1.732050807568877*fL[4]+fL[2]); 
  incr[3] = 0.25*alphaR[0]*(1.732050807568877*fL[5]+fL[3]); 
  incr[4] = -0.25*alphaR[0]*(3.0*fL[4]+1.732050807568877*fL[2]); 
  incr[5] = -0.25*alphaR[0]*(3.0*fL[5]+1.732050807568877*fL[3]); 
  incr[6] = 0.25*alphaR[0]*(1.732050807568877*fL[7]+fL[6]); 
  incr[7] = -0.25*alphaR[0]*(3.0*fL[7]+1.732050807568877*fL[6]); 
  } else { 
  incr[0] = -0.25*alphaR[0]*(1.732050807568877*fR[1]-1.0*fR[0]); 
  incr[1] = 0.25*alphaR[0]*(3.0*fR[1]-1.732050807568877*fR[0]); 
  incr[2] = -0.25*alphaR[0]*(1.732050807568877*fR[4]-1.0*fR[2]); 
  incr[3] = -0.25*alphaR[0]*(1.732050807568877*fR[5]-1.0*fR[3]); 
  incr[4] = 0.25*alphaR[0]*(3.0*fR[4]-1.732050807568877*fR[2]); 
  incr[5] = 0.25*alphaR[0]*(3.0*fR[5]-1.732050807568877*fR[3]); 
  incr[6] = -0.25*alphaR[0]*(1.732050807568877*fR[7]-1.0*fR[6]); 
  incr[7] = 0.25*alphaR[0]*(3.0*fR[7]-1.732050807568877*fR[6]); 
  }
#elif upwindType == QUAD 
  double alphaOrdR;
  double fUpOrd[4];
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[0] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.3535533905932737*fR[6]+0.3535533905932737*fL[6]-0.6123724356957944*(fR[5]+fL[5]+fR[4]+fL[4])+0.3535533905932737*(fR[3]+fR[2])-0.3535533905932737*(fL[3]+fL[2])+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdR)-0.6123724356957944*fR[7]+0.6123724356957944*fL[7]+0.3535533905932737*(fR[6]+fL[6])+0.6123724356957944*(fR[5]+fR[4])-0.6123724356957944*(fL[5]+fL[4])-0.3535533905932737*(fR[3]+fL[3]+fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[1] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.3535533905932737*fR[6]-0.3535533905932737*fL[6]-0.6123724356957944*(fR[5]+fL[5])+0.6123724356957944*(fR[4]+fL[4])+0.3535533905932737*fR[3]-0.3535533905932737*(fL[3]+fR[2])+0.3535533905932737*fL[2]+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdR)+0.6123724356957944*fR[7]-0.6123724356957944*fL[7]-0.3535533905932737*(fR[6]+fL[6])+0.6123724356957944*fR[5]-0.6123724356957944*(fL[5]+fR[4])+0.6123724356957944*fL[4]-0.3535533905932737*(fR[3]+fL[3])+0.3535533905932737*(fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[2] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.3535533905932737*fR[6]-0.3535533905932737*fL[6]+0.6123724356957944*(fR[5]+fL[5])-0.6123724356957944*(fR[4]+fL[4])-0.3535533905932737*fR[3]+0.3535533905932737*(fL[3]+fR[2])-0.3535533905932737*fL[2]+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdR)+0.6123724356957944*fR[7]-0.6123724356957944*fL[7]-0.3535533905932737*(fR[6]+fL[6])-0.6123724356957944*fR[5]+0.6123724356957944*(fL[5]+fR[4])-0.6123724356957944*fL[4]+0.3535533905932737*(fR[3]+fL[3])-0.3535533905932737*(fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[3] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.3535533905932737*fR[6]+0.3535533905932737*fL[6]+0.6123724356957944*(fR[5]+fL[5]+fR[4]+fL[4])-0.3535533905932737*(fR[3]+fR[2])+0.3535533905932737*(fL[3]+fL[2])+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdR)-0.6123724356957944*fR[7]+0.6123724356957944*fL[7]+0.3535533905932737*(fR[6]+fL[6])-0.6123724356957944*(fR[5]+fR[4])+0.6123724356957944*(fL[5]+fL[4])+0.3535533905932737*(fR[3]+fL[3]+fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 

  double fUp[4];
  fUp[0] = 0.5*(fUpOrd[3]+fUpOrd[2]+fUpOrd[1]+fUpOrd[0]); 
  fUp[1] = 0.5*(fUpOrd[3]-1.0*fUpOrd[2]+fUpOrd[1]-1.0*fUpOrd[0]); 
  fUp[2] = 0.5*(fUpOrd[3]+fUpOrd[2]-1.0*(fUpOrd[1]+fUpOrd[0])); 
  fUp[3] = 0.5*(fUpOrd[3]-1.0*(fUpOrd[2]+fUpOrd[1])+fUpOrd[0]); 

  incr[0] = 0.3535533905932737*alphaR[0]*fUp[0]; 
  incr[1] = -0.6123724356957944*alphaR[0]*fUp[0]; 
  incr[2] = 0.3535533905932737*alphaR[0]*fUp[1]; 
  incr[3] = 0.3535533905932737*alphaR[0]*fUp[2]; 
  incr[4] = -0.6123724356957944*alphaR[0]*fUp[1]; 
  incr[5] = -0.6123724356957944*alphaR[0]*fUp[2]; 
  incr[6] = 0.3535533905932737*alphaR[0]*fUp[3]; 
  incr[7] = -0.6123724356957944*alphaR[0]*fUp[3]; 

#endif 
  outR[0] += incr[0]*rdx2R; 
  outR[1] += incr[1]*rdx2R; 
  outR[2] += incr[2]*rdx2R; 
  outR[3] += incr[3]*rdx2R; 
  outR[4] += incr[4]*rdx2R; 
  outR[5] += incr[5]*rdx2R; 
  outR[6] += incr[6]*rdx2R; 
  outR[7] += incr[7]*rdx2R; 

  outL[0] += -1.0*incr[0]*rdx2L; 
  outL[1] += incr[1]*rdx2L; 
  outL[2] += -1.0*incr[2]*rdx2L; 
  outL[3] += -1.0*incr[3]*rdx2L; 
  outL[4] += incr[4]*rdx2L; 
  outL[5] += incr[5]*rdx2L; 
  outL[6] += -1.0*incr[6]*rdx2L; 
  outL[7] += incr[7]*rdx2L; 

  return std::abs(alphaSurfAvgR); 
} 
double GyrokineticSimpleHelicalSurf1x2vTensor_vpar_P1_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
{ 
  // bmagInv: 1/bmag.
  // BdriftX,BdriftY: x,y components of gradB/curvature drift.
  // q_,m_: species charge and mass.
  // cflL,cflR: CFL rate in left and right cells.
  // wL[NDIM],wR[NDIM]: cell-center in left and right cells.
  // dxvL[NDIM],dxvR[NDIM]: Cell length in left and right cells.
  // amax_in: maximum phase-space speed.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // fL,fR: Distribution function in left and right cells.
  // outL/outR: Output increment in left and right cells.

  double wxL = wL[0];
  double wxR = wR[0];
  double rdx2L = 2.0/dxvL[0];
  double rdx2R = 2.0/dxvR[0];
  double wvparL = wL[1];
  double wvparR = wR[1];
  double rdvpar2L = 2.0/dxvL[1];
  double rdvpar2R = 2.0/dxvR[1];
  double wmuL = wL[2];
  double wmuR = wR[2];
  double rdmu2L = 2.0/dxvL[2];
  double rdmu2R = 2.0/dxvR[2];

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;
  double wmuSqL = wL[2]*wL[2];
  double wmuSqR = wR[2]*wR[2];
  double rdmu2SqL = rdmu2L*rdmu2L;
  double rdmu2SqR = rdmu2R*rdmu2R;

  double hamilR[8]; 
  hamilR[0] = (0.2357022603955158*(3.0*rdvpar2SqR*(2.0*m_*wvparSqR+2.828427124746191*(bmag[0]*wmuR+phi[0]*q_))+2.0*m_))/rdvpar2SqR; 
  hamilR[1] = 2.0*phi[1]*q_; 
  hamilR[2] = (1.632993161855453*m_*wvparR)/rdvpar2R; 
  hamilR[3] = (1.154700538379252*bmag[0])/rdmu2R; 

  double BstarZdBmagR[8]; 
  BstarZdBmagR[0] = 2.0*cmag[0]; 

  double alphaR[4]; 
  alphaR[0] = -(0.4330127018922193*BstarZdBmagR[0]*hamilR[1]*rdx2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.1082531754730548*BstarZdBmagR[0]*hamilR[1]*rdx2R)/m_; 

  double incr[8]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgR>0) { 
  incr[0] = 0.25*alphaR[0]*(1.732050807568877*fL[2]+fL[0]); 
  incr[1] = 0.25*alphaR[0]*(1.732050807568877*fL[4]+fL[1]); 
  incr[2] = -0.25*alphaR[0]*(3.0*fL[2]+1.732050807568877*fL[0]); 
  incr[3] = 0.25*alphaR[0]*(1.732050807568877*fL[6]+fL[3]); 
  incr[4] = -0.25*alphaR[0]*(3.0*fL[4]+1.732050807568877*fL[1]); 
  incr[5] = 0.25*alphaR[0]*(1.732050807568877*fL[7]+fL[5]); 
  incr[6] = -0.25*alphaR[0]*(3.0*fL[6]+1.732050807568877*fL[3]); 
  incr[7] = -0.25*alphaR[0]*(3.0*fL[7]+1.732050807568877*fL[5]); 
  } else { 
  incr[0] = -0.25*alphaR[0]*(1.732050807568877*fR[2]-1.0*fR[0]); 
  incr[1] = -0.25*alphaR[0]*(1.732050807568877*fR[4]-1.0*fR[1]); 
  incr[2] = 0.25*alphaR[0]*(3.0*fR[2]-1.732050807568877*fR[0]); 
  incr[3] = -0.25*alphaR[0]*(1.732050807568877*fR[6]-1.0*fR[3]); 
  incr[4] = 0.25*alphaR[0]*(3.0*fR[4]-1.732050807568877*fR[1]); 
  incr[5] = -0.25*alphaR[0]*(1.732050807568877*fR[7]-1.0*fR[5]); 
  incr[6] = 0.25*alphaR[0]*(3.0*fR[6]-1.732050807568877*fR[3]); 
  incr[7] = 0.25*alphaR[0]*(3.0*fR[7]-1.732050807568877*fR[5]); 
  }
#elif upwindType == QUAD 
  double alphaOrdR;
  double fUpOrd[4];
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[0] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.6123724356957944*(fR[6]+fL[6])-0.3535533905932737*fR[5]+0.3535533905932737*fL[5]-0.6123724356957944*(fR[4]+fL[4])+0.3535533905932737*fR[3]-0.3535533905932737*fL[3]+0.6123724356957944*(fR[2]+fL[2])+0.3535533905932737*fR[1]-0.3535533905932737*(fL[1]+fR[0])+0.3535533905932737*fL[0])*sgn(alphaOrdR)-0.6123724356957944*fR[7]+0.6123724356957944*(fL[7]+fR[6])-0.6123724356957944*fL[6]+0.3535533905932737*(fR[5]+fL[5])+0.6123724356957944*fR[4]-0.6123724356957944*fL[4]-0.3535533905932737*(fR[3]+fL[3])-0.6123724356957944*fR[2]+0.6123724356957944*fL[2]-0.3535533905932737*(fR[1]+fL[1])+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[1] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]+fR[6]+fL[6]))+0.3535533905932737*fR[5]-0.3535533905932737*fL[5]+0.6123724356957944*(fR[4]+fL[4])+0.3535533905932737*fR[3]-0.3535533905932737*fL[3]+0.6123724356957944*(fR[2]+fL[2])-0.3535533905932737*(fR[1]+fR[0])+0.3535533905932737*(fL[1]+fL[0]))*sgn(alphaOrdR)+0.6123724356957944*(fR[7]+fR[6])-0.6123724356957944*(fL[7]+fL[6])-0.3535533905932737*(fR[5]+fL[5])-0.6123724356957944*fR[4]+0.6123724356957944*fL[4]-0.3535533905932737*(fR[3]+fL[3])-0.6123724356957944*fR[2]+0.6123724356957944*fL[2]+0.3535533905932737*(fR[1]+fL[1]+fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[2] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.6123724356957944*(fR[6]+fL[6])+0.3535533905932737*fR[5]-0.3535533905932737*fL[5]-0.6123724356957944*(fR[4]+fL[4])-0.3535533905932737*fR[3]+0.3535533905932737*fL[3]+0.6123724356957944*(fR[2]+fL[2])+0.3535533905932737*fR[1]-0.3535533905932737*(fL[1]+fR[0])+0.3535533905932737*fL[0])*sgn(alphaOrdR)+0.6123724356957944*fR[7]-0.6123724356957944*(fL[7]+fR[6])+0.6123724356957944*fL[6]-0.3535533905932737*(fR[5]+fL[5])+0.6123724356957944*fR[4]-0.6123724356957944*fL[4]+0.3535533905932737*(fR[3]+fL[3])-0.6123724356957944*fR[2]+0.6123724356957944*fL[2]-0.3535533905932737*(fR[1]+fL[1])+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[3] = 0.5*((0.6123724356957944*(fR[7]+fL[7]+fR[6]+fL[6])-0.3535533905932737*fR[5]+0.3535533905932737*fL[5]+0.6123724356957944*(fR[4]+fL[4])-0.3535533905932737*fR[3]+0.3535533905932737*fL[3]+0.6123724356957944*(fR[2]+fL[2])-0.3535533905932737*(fR[1]+fR[0])+0.3535533905932737*(fL[1]+fL[0]))*sgn(alphaOrdR)-0.6123724356957944*(fR[7]+fR[6])+0.6123724356957944*(fL[7]+fL[6])+0.3535533905932737*(fR[5]+fL[5])-0.6123724356957944*fR[4]+0.6123724356957944*fL[4]+0.3535533905932737*(fR[3]+fL[3])-0.6123724356957944*fR[2]+0.6123724356957944*fL[2]+0.3535533905932737*(fR[1]+fL[1]+fR[0]+fL[0])); 

  double fUp[4];
  fUp[0] = 0.5*(fUpOrd[3]+fUpOrd[2]+fUpOrd[1]+fUpOrd[0]); 
  fUp[1] = 0.5*(fUpOrd[3]-1.0*fUpOrd[2]+fUpOrd[1]-1.0*fUpOrd[0]); 
  fUp[2] = 0.5*(fUpOrd[3]+fUpOrd[2]-1.0*(fUpOrd[1]+fUpOrd[0])); 
  fUp[3] = 0.5*(fUpOrd[3]-1.0*(fUpOrd[2]+fUpOrd[1])+fUpOrd[0]); 

  incr[0] = 0.3535533905932737*alphaR[0]*fUp[0]; 
  incr[1] = 0.3535533905932737*alphaR[0]*fUp[1]; 
  incr[2] = -0.6123724356957944*alphaR[0]*fUp[0]; 
  incr[3] = 0.3535533905932737*alphaR[0]*fUp[2]; 
  incr[4] = -0.6123724356957944*alphaR[0]*fUp[1]; 
  incr[5] = 0.3535533905932737*alphaR[0]*fUp[3]; 
  incr[6] = -0.6123724356957944*alphaR[0]*fUp[2]; 
  incr[7] = -0.6123724356957944*alphaR[0]*fUp[3]; 

#endif 
  outR[0] += incr[0]*rdvpar2R; 
  outR[1] += incr[1]*rdvpar2R; 
  outR[2] += incr[2]*rdvpar2R; 
  outR[3] += incr[3]*rdvpar2R; 
  outR[4] += incr[4]*rdvpar2R; 
  outR[5] += incr[5]*rdvpar2R; 
  outR[6] += incr[6]*rdvpar2R; 
  outR[7] += incr[7]*rdvpar2R; 

  outL[0] += -1.0*incr[0]*rdvpar2L; 
  outL[1] += -1.0*incr[1]*rdvpar2L; 
  outL[2] += incr[2]*rdvpar2L; 
  outL[3] += -1.0*incr[3]*rdvpar2L; 
  outL[4] += incr[4]*rdvpar2L; 
  outL[5] += -1.0*incr[5]*rdvpar2L; 
  outL[6] += incr[6]*rdvpar2L; 
  outL[7] += incr[7]*rdvpar2L; 

  return std::abs(alphaSurfAvgR); 
} 
double GyrokineticSimpleHelicalSurf1x2vTensor_xL_P1_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
{ 
  // bmagInv: 1/bmag.
  // BdriftX,BdriftY: x,y components of gradB/curvature drift.
  // q_,m_: species charge and mass.
  // cflL,cflR: CFL rate in left and right cells.
  // wL[NDIM],wR[NDIM]: cell-center in left and right cells.
  // dxvL[NDIM],dxvR[NDIM]: Cell length in left and right cells.
  // amax_in: maximum phase-space speed.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // fL,fR: Distribution function in left and right cells.
  // outL/outR: Output increment in left and right cells.

  double wxL = wL[0];
  double wxR = wR[0];
  double rdx2L = 2.0/dxvL[0];
  double rdx2R = 2.0/dxvR[0];
  double wvparL = wL[1];
  double wvparR = wR[1];
  double rdvpar2L = 2.0/dxvL[1];
  double rdvpar2R = 2.0/dxvR[1];
  double wmuL = wL[2];
  double wmuR = wR[2];
  double rdmu2L = 2.0/dxvL[2];
  double rdmu2R = 2.0/dxvR[2];

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;
  double wmuSqL = wL[2]*wL[2];
  double wmuSqR = wR[2]*wR[2];
  double rdmu2SqL = rdmu2L*rdmu2L;
  double rdmu2SqR = rdmu2R*rdmu2R;

  double hamilL[8]; 
  hamilL[0] = (0.2357022603955158*(3.0*rdvpar2SqL*(2.0*m_*wvparSqL+2.828427124746191*(bmag[0]*wmuL+phi[0]*q_))+2.0*m_))/rdvpar2SqL; 
  hamilL[1] = 2.0*(bmag[1]*wmuL+phi[1]*q_); 
  hamilL[2] = (1.632993161855453*m_*wvparL)/rdvpar2L; 
  hamilL[3] = (1.154700538379252*bmag[0])/rdmu2L; 
  hamilL[5] = (1.154700538379252*bmag[1])/rdmu2L; 

  double BstarZdBmagL[8]; 
  BstarZdBmagL[0] = 2.0*cmag[0]; 
  BstarZdBmagL[1] = 2.0*cmag[1]; 

  double alphaL[4]; 
  alphaL[0] = (0.25*(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2]*rdvpar2L)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgL = (0.0625*(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2]*rdvpar2L)/m_; 

  double incr[8]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgL>0) { 
  incr[0] = 0.25*alphaL[0]*(1.732050807568877*fL[1]+fL[0]); 
  incr[1] = -0.25*alphaL[0]*(3.0*fL[1]+1.732050807568877*fL[0]); 
  incr[2] = 0.25*alphaL[0]*(1.732050807568877*fL[4]+fL[2]); 
  incr[3] = 0.25*alphaL[0]*(1.732050807568877*fL[5]+fL[3]); 
  incr[4] = -0.25*alphaL[0]*(3.0*fL[4]+1.732050807568877*fL[2]); 
  incr[5] = -0.25*alphaL[0]*(3.0*fL[5]+1.732050807568877*fL[3]); 
  incr[6] = 0.25*alphaL[0]*(1.732050807568877*fL[7]+fL[6]); 
  incr[7] = -0.25*alphaL[0]*(3.0*fL[7]+1.732050807568877*fL[6]); 
  } else { 
  incr[0] = -0.25*alphaL[0]*(1.732050807568877*fR[1]-1.0*fR[0]); 
  incr[1] = 0.25*alphaL[0]*(3.0*fR[1]-1.732050807568877*fR[0]); 
  incr[2] = -0.25*alphaL[0]*(1.732050807568877*fR[4]-1.0*fR[2]); 
  incr[3] = -0.25*alphaL[0]*(1.732050807568877*fR[5]-1.0*fR[3]); 
  incr[4] = 0.25*alphaL[0]*(3.0*fR[4]-1.732050807568877*fR[2]); 
  incr[5] = 0.25*alphaL[0]*(3.0*fR[5]-1.732050807568877*fR[3]); 
  incr[6] = -0.25*alphaL[0]*(1.732050807568877*fR[7]-1.0*fR[6]); 
  incr[7] = 0.25*alphaL[0]*(3.0*fR[7]-1.732050807568877*fR[6]); 
  }
#elif upwindType == QUAD 
  double alphaOrdL;
  double fUpOrd[4];
  alphaOrdL = 0.5*alphaL[0]; 
  fUpOrd[0] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.3535533905932737*fR[6]+0.3535533905932737*fL[6]-0.6123724356957944*(fR[5]+fL[5]+fR[4]+fL[4])+0.3535533905932737*(fR[3]+fR[2])-0.3535533905932737*(fL[3]+fL[2])+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdL)-0.6123724356957944*fR[7]+0.6123724356957944*fL[7]+0.3535533905932737*(fR[6]+fL[6])+0.6123724356957944*(fR[5]+fR[4])-0.6123724356957944*(fL[5]+fL[4])-0.3535533905932737*(fR[3]+fL[3]+fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdL = 0.5*alphaL[0]; 
  fUpOrd[1] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.3535533905932737*fR[6]-0.3535533905932737*fL[6]-0.6123724356957944*(fR[5]+fL[5])+0.6123724356957944*(fR[4]+fL[4])+0.3535533905932737*fR[3]-0.3535533905932737*(fL[3]+fR[2])+0.3535533905932737*fL[2]+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdL)+0.6123724356957944*fR[7]-0.6123724356957944*fL[7]-0.3535533905932737*(fR[6]+fL[6])+0.6123724356957944*fR[5]-0.6123724356957944*(fL[5]+fR[4])+0.6123724356957944*fL[4]-0.3535533905932737*(fR[3]+fL[3])+0.3535533905932737*(fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdL = 0.5*alphaL[0]; 
  fUpOrd[2] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.3535533905932737*fR[6]-0.3535533905932737*fL[6]+0.6123724356957944*(fR[5]+fL[5])-0.6123724356957944*(fR[4]+fL[4])-0.3535533905932737*fR[3]+0.3535533905932737*(fL[3]+fR[2])-0.3535533905932737*fL[2]+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdL)+0.6123724356957944*fR[7]-0.6123724356957944*fL[7]-0.3535533905932737*(fR[6]+fL[6])-0.6123724356957944*fR[5]+0.6123724356957944*(fL[5]+fR[4])-0.6123724356957944*fL[4]+0.3535533905932737*(fR[3]+fL[3])-0.3535533905932737*(fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdL = 0.5*alphaL[0]; 
  fUpOrd[3] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.3535533905932737*fR[6]+0.3535533905932737*fL[6]+0.6123724356957944*(fR[5]+fL[5]+fR[4]+fL[4])-0.3535533905932737*(fR[3]+fR[2])+0.3535533905932737*(fL[3]+fL[2])+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdL)-0.6123724356957944*fR[7]+0.6123724356957944*fL[7]+0.3535533905932737*(fR[6]+fL[6])-0.6123724356957944*(fR[5]+fR[4])+0.6123724356957944*(fL[5]+fL[4])+0.3535533905932737*(fR[3]+fL[3]+fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 

  double fUp[4];
  fUp[0] = 0.5*(fUpOrd[3]+fUpOrd[2]+fUpOrd[1]+fUpOrd[0]); 
  fUp[1] = 0.5*(fUpOrd[3]-1.0*fUpOrd[2]+fUpOrd[1]-1.0*fUpOrd[0]); 
  fUp[2] = 0.5*(fUpOrd[3]+fUpOrd[2]-1.0*(fUpOrd[1]+fUpOrd[0])); 
  fUp[3] = 0.5*(fUpOrd[3]-1.0*(fUpOrd[2]+fUpOrd[1])+fUpOrd[0]); 

  incr[0] = 0.3535533905932737*alphaL[0]*fUp[0]; 
  incr[1] = -0.6123724356957944*alphaL[0]*fUp[0]; 
  incr[2] = 0.3535533905932737*alphaL[0]*fUp[1]; 
  incr[3] = 0.3535533905932737*alphaL[0]*fUp[2]; 
  incr[4] = -0.6123724356957944*alphaL[0]*fUp[1]; 
  incr[5] = -0.6123724356957944*alphaL[0]*fUp[2]; 
  incr[6] = 0.3535533905932737*alphaL[0]*fUp[3]; 
  incr[7] = -0.6123724356957944*alphaL[0]*fUp[3]; 

#endif 
  outR[0] += incr[0]*rdx2R; 
  outR[1] += incr[1]*rdx2R; 
  outR[2] += incr[2]*rdx2R; 
  outR[3] += incr[3]*rdx2R; 
  outR[4] += incr[4]*rdx2R; 
  outR[5] += incr[5]*rdx2R; 
  outR[6] += incr[6]*rdx2R; 
  outR[7] += incr[7]*rdx2R; 

  outL[0] += -1.0*incr[0]*rdx2L; 
  outL[1] += incr[1]*rdx2L; 
  outL[2] += -1.0*incr[2]*rdx2L; 
  outL[3] += -1.0*incr[3]*rdx2L; 
  outL[4] += incr[4]*rdx2L; 
  outL[5] += incr[5]*rdx2L; 
  outL[6] += -1.0*incr[6]*rdx2L; 
  outL[7] += incr[7]*rdx2L; 

  return std::abs(alphaSurfAvgL); 
} 
double GyrokineticSimpleHelicalSurf1x2vTensor_xR_P1_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
{ 
  // bmagInv: 1/bmag.
  // BdriftX,BdriftY: x,y components of gradB/curvature drift.
  // q_,m_: species charge and mass.
  // cflL,cflR: CFL rate in left and right cells.
  // wL[NDIM],wR[NDIM]: cell-center in left and right cells.
  // dxvL[NDIM],dxvR[NDIM]: Cell length in left and right cells.
  // amax_in: maximum phase-space speed.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // fL,fR: Distribution function in left and right cells.
  // outL/outR: Output increment in left and right cells.

  double wxL = wL[0];
  double wxR = wR[0];
  double rdx2L = 2.0/dxvL[0];
  double rdx2R = 2.0/dxvR[0];
  double wvparL = wL[1];
  double wvparR = wR[1];
  double rdvpar2L = 2.0/dxvL[1];
  double rdvpar2R = 2.0/dxvR[1];
  double wmuL = wL[2];
  double wmuR = wR[2];
  double rdmu2L = 2.0/dxvL[2];
  double rdmu2R = 2.0/dxvR[2];

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;
  double wmuSqL = wL[2]*wL[2];
  double wmuSqR = wR[2]*wR[2];
  double rdmu2SqL = rdmu2L*rdmu2L;
  double rdmu2SqR = rdmu2R*rdmu2R;

  double hamilR[8]; 
  hamilR[0] = (0.2357022603955158*(3.0*rdvpar2SqR*(2.0*m_*wvparSqR+2.828427124746191*(bmag[0]*wmuR+phi[0]*q_))+2.0*m_))/rdvpar2SqR; 
  hamilR[1] = 2.0*(bmag[1]*wmuR+phi[1]*q_); 
  hamilR[2] = (1.632993161855453*m_*wvparR)/rdvpar2R; 
  hamilR[3] = (1.154700538379252*bmag[0])/rdmu2R; 
  hamilR[5] = (1.154700538379252*bmag[1])/rdmu2R; 

  double BstarZdBmagR[8]; 
  BstarZdBmagR[0] = 2.0*cmag[0]; 
  BstarZdBmagR[1] = 2.0*cmag[1]; 

  double alphaR[4]; 
  alphaR[0] = -(0.25*(3.0*BstarZdBmagR[1]-1.732050807568877*BstarZdBmagR[0])*hamilR[2]*rdvpar2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.0625*(3.0*BstarZdBmagR[1]-1.732050807568877*BstarZdBmagR[0])*hamilR[2]*rdvpar2R)/m_; 

  double incr[8]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgR>0) { 
  incr[0] = 0.25*alphaR[0]*(1.732050807568877*fL[1]+fL[0]); 
  incr[1] = -0.25*alphaR[0]*(3.0*fL[1]+1.732050807568877*fL[0]); 
  incr[2] = 0.25*alphaR[0]*(1.732050807568877*fL[4]+fL[2]); 
  incr[3] = 0.25*alphaR[0]*(1.732050807568877*fL[5]+fL[3]); 
  incr[4] = -0.25*alphaR[0]*(3.0*fL[4]+1.732050807568877*fL[2]); 
  incr[5] = -0.25*alphaR[0]*(3.0*fL[5]+1.732050807568877*fL[3]); 
  incr[6] = 0.25*alphaR[0]*(1.732050807568877*fL[7]+fL[6]); 
  incr[7] = -0.25*alphaR[0]*(3.0*fL[7]+1.732050807568877*fL[6]); 
  } else { 
  incr[0] = -0.25*alphaR[0]*(1.732050807568877*fR[1]-1.0*fR[0]); 
  incr[1] = 0.25*alphaR[0]*(3.0*fR[1]-1.732050807568877*fR[0]); 
  incr[2] = -0.25*alphaR[0]*(1.732050807568877*fR[4]-1.0*fR[2]); 
  incr[3] = -0.25*alphaR[0]*(1.732050807568877*fR[5]-1.0*fR[3]); 
  incr[4] = 0.25*alphaR[0]*(3.0*fR[4]-1.732050807568877*fR[2]); 
  incr[5] = 0.25*alphaR[0]*(3.0*fR[5]-1.732050807568877*fR[3]); 
  incr[6] = -0.25*alphaR[0]*(1.732050807568877*fR[7]-1.0*fR[6]); 
  incr[7] = 0.25*alphaR[0]*(3.0*fR[7]-1.732050807568877*fR[6]); 
  }
#elif upwindType == QUAD 
  double alphaOrdR;
  double fUpOrd[4];
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[0] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.3535533905932737*fR[6]+0.3535533905932737*fL[6]-0.6123724356957944*(fR[5]+fL[5]+fR[4]+fL[4])+0.3535533905932737*(fR[3]+fR[2])-0.3535533905932737*(fL[3]+fL[2])+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdR)-0.6123724356957944*fR[7]+0.6123724356957944*fL[7]+0.3535533905932737*(fR[6]+fL[6])+0.6123724356957944*(fR[5]+fR[4])-0.6123724356957944*(fL[5]+fL[4])-0.3535533905932737*(fR[3]+fL[3]+fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[1] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.3535533905932737*fR[6]-0.3535533905932737*fL[6]-0.6123724356957944*(fR[5]+fL[5])+0.6123724356957944*(fR[4]+fL[4])+0.3535533905932737*fR[3]-0.3535533905932737*(fL[3]+fR[2])+0.3535533905932737*fL[2]+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdR)+0.6123724356957944*fR[7]-0.6123724356957944*fL[7]-0.3535533905932737*(fR[6]+fL[6])+0.6123724356957944*fR[5]-0.6123724356957944*(fL[5]+fR[4])+0.6123724356957944*fL[4]-0.3535533905932737*(fR[3]+fL[3])+0.3535533905932737*(fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[2] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.3535533905932737*fR[6]-0.3535533905932737*fL[6]+0.6123724356957944*(fR[5]+fL[5])-0.6123724356957944*(fR[4]+fL[4])-0.3535533905932737*fR[3]+0.3535533905932737*(fL[3]+fR[2])-0.3535533905932737*fL[2]+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdR)+0.6123724356957944*fR[7]-0.6123724356957944*fL[7]-0.3535533905932737*(fR[6]+fL[6])-0.6123724356957944*fR[5]+0.6123724356957944*(fL[5]+fR[4])-0.6123724356957944*fL[4]+0.3535533905932737*(fR[3]+fL[3])-0.3535533905932737*(fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*alphaR[0]; 
  fUpOrd[3] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.3535533905932737*fR[6]+0.3535533905932737*fL[6]+0.6123724356957944*(fR[5]+fL[5]+fR[4]+fL[4])-0.3535533905932737*(fR[3]+fR[2])+0.3535533905932737*(fL[3]+fL[2])+0.6123724356957944*(fR[1]+fL[1])-0.3535533905932737*fR[0]+0.3535533905932737*fL[0])*sgn(alphaOrdR)-0.6123724356957944*fR[7]+0.6123724356957944*fL[7]+0.3535533905932737*(fR[6]+fL[6])-0.6123724356957944*(fR[5]+fR[4])+0.6123724356957944*(fL[5]+fL[4])+0.3535533905932737*(fR[3]+fL[3]+fR[2]+fL[2])-0.6123724356957944*fR[1]+0.6123724356957944*fL[1]+0.3535533905932737*(fR[0]+fL[0])); 

  double fUp[4];
  fUp[0] = 0.5*(fUpOrd[3]+fUpOrd[2]+fUpOrd[1]+fUpOrd[0]); 
  fUp[1] = 0.5*(fUpOrd[3]-1.0*fUpOrd[2]+fUpOrd[1]-1.0*fUpOrd[0]); 
  fUp[2] = 0.5*(fUpOrd[3]+fUpOrd[2]-1.0*(fUpOrd[1]+fUpOrd[0])); 
  fUp[3] = 0.5*(fUpOrd[3]-1.0*(fUpOrd[2]+fUpOrd[1])+fUpOrd[0]); 

  incr[0] = 0.3535533905932737*alphaR[0]*fUp[0]; 
  incr[1] = -0.6123724356957944*alphaR[0]*fUp[0]; 
  incr[2] = 0.3535533905932737*alphaR[0]*fUp[1]; 
  incr[3] = 0.3535533905932737*alphaR[0]*fUp[2]; 
  incr[4] = -0.6123724356957944*alphaR[0]*fUp[1]; 
  incr[5] = -0.6123724356957944*alphaR[0]*fUp[2]; 
  incr[6] = 0.3535533905932737*alphaR[0]*fUp[3]; 
  incr[7] = -0.6123724356957944*alphaR[0]*fUp[3]; 

#endif 
  outR[0] += incr[0]*rdx2R; 
  outR[1] += incr[1]*rdx2R; 
  outR[2] += incr[2]*rdx2R; 
  outR[3] += incr[3]*rdx2R; 
  outR[4] += incr[4]*rdx2R; 
  outR[5] += incr[5]*rdx2R; 
  outR[6] += incr[6]*rdx2R; 
  outR[7] += incr[7]*rdx2R; 

  outL[0] += -1.0*incr[0]*rdx2L; 
  outL[1] += incr[1]*rdx2L; 
  outL[2] += -1.0*incr[2]*rdx2L; 
  outL[3] += -1.0*incr[3]*rdx2L; 
  outL[4] += incr[4]*rdx2L; 
  outL[5] += incr[5]*rdx2L; 
  outL[6] += -1.0*incr[6]*rdx2L; 
  outL[7] += incr[7]*rdx2L; 

  return std::abs(alphaSurfAvgR); 
} 
double GyrokineticSimpleHelicalSurf1x2vTensor_vpar_P1_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
{ 
  // bmagInv: 1/bmag.
  // BdriftX,BdriftY: x,y components of gradB/curvature drift.
  // q_,m_: species charge and mass.
  // cflL,cflR: CFL rate in left and right cells.
  // wL[NDIM],wR[NDIM]: cell-center in left and right cells.
  // dxvL[NDIM],dxvR[NDIM]: Cell length in left and right cells.
  // amax_in: maximum phase-space speed.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // fL,fR: Distribution function in left and right cells.
  // outL/outR: Output increment in left and right cells.

  double wxL = wL[0];
  double wxR = wR[0];
  double rdx2L = 2.0/dxvL[0];
  double rdx2R = 2.0/dxvR[0];
  double wvparL = wL[1];
  double wvparR = wR[1];
  double rdvpar2L = 2.0/dxvL[1];
  double rdvpar2R = 2.0/dxvR[1];
  double wmuL = wL[2];
  double wmuR = wR[2];
  double rdmu2L = 2.0/dxvL[2];
  double rdmu2R = 2.0/dxvR[2];

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;
  double wmuSqL = wL[2]*wL[2];
  double wmuSqR = wR[2]*wR[2];
  double rdmu2SqL = rdmu2L*rdmu2L;
  double rdmu2SqR = rdmu2R*rdmu2R;

  double hamilR[8]; 
  hamilR[0] = (0.2357022603955158*(3.0*rdvpar2SqR*(2.0*m_*wvparSqR+2.828427124746191*(bmag[0]*wmuR+phi[0]*q_))+2.0*m_))/rdvpar2SqR; 
  hamilR[1] = 2.0*(bmag[1]*wmuR+phi[1]*q_); 
  hamilR[2] = (1.632993161855453*m_*wvparR)/rdvpar2R; 
  hamilR[3] = (1.154700538379252*bmag[0])/rdmu2R; 
  hamilR[5] = (1.154700538379252*bmag[1])/rdmu2R; 

  double BstarZdBmagR[8]; 
  BstarZdBmagR[0] = 2.0*cmag[0]; 
  BstarZdBmagR[1] = 2.0*cmag[1]; 

  double alphaR[4]; 
  alphaR[0] = -(0.4330127018922193*BstarZdBmagR[0]*hamilR[1]*rdx2R)/m_; 
  alphaR[1] = -(0.4330127018922193*BstarZdBmagR[1]*hamilR[1]*rdx2R)/m_; 
  alphaR[2] = -(0.4330127018922193*BstarZdBmagR[0]*hamilR[5]*rdx2R)/m_; 
  alphaR[3] = -(0.4330127018922193*BstarZdBmagR[1]*hamilR[5]*rdx2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.1082531754730548*BstarZdBmagR[0]*hamilR[1]*rdx2R)/m_; 

  double incr[8]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgR>0) { 
  incr[0] = 0.25*(1.732050807568877*(alphaR[3]*fL[7]+alphaR[2]*fL[6])+alphaR[3]*fL[5]+1.732050807568877*alphaR[1]*fL[4]+alphaR[2]*fL[3]+1.732050807568877*alphaR[0]*fL[2]+alphaR[1]*fL[1]+alphaR[0]*fL[0]); 
  incr[1] = 0.25*(1.732050807568877*(alphaR[2]*fL[7]+alphaR[3]*fL[6])+alphaR[2]*fL[5]+1.732050807568877*alphaR[0]*fL[4]+alphaR[3]*fL[3]+1.732050807568877*alphaR[1]*fL[2]+alphaR[0]*fL[1]+fL[0]*alphaR[1]); 
  incr[2] = -0.25*(3.0*(alphaR[3]*fL[7]+alphaR[2]*fL[6])+1.732050807568877*alphaR[3]*fL[5]+3.0*alphaR[1]*fL[4]+1.732050807568877*alphaR[2]*fL[3]+3.0*alphaR[0]*fL[2]+1.732050807568877*(alphaR[1]*fL[1]+alphaR[0]*fL[0])); 
  incr[3] = 0.25*(1.732050807568877*(alphaR[1]*fL[7]+alphaR[0]*fL[6])+alphaR[1]*fL[5]+1.732050807568877*alphaR[3]*fL[4]+alphaR[0]*fL[3]+fL[1]*alphaR[3]+alphaR[2]*(1.732050807568877*fL[2]+fL[0])); 
  incr[4] = -0.25*(3.0*(alphaR[2]*fL[7]+alphaR[3]*fL[6])+1.732050807568877*alphaR[2]*fL[5]+3.0*alphaR[0]*fL[4]+1.732050807568877*alphaR[3]*fL[3]+3.0*alphaR[1]*fL[2]+1.732050807568877*(alphaR[0]*fL[1]+fL[0]*alphaR[1])); 
  incr[5] = 0.25*(1.732050807568877*(alphaR[0]*fL[7]+alphaR[1]*fL[6])+alphaR[0]*fL[5]+1.732050807568877*alphaR[2]*fL[4]+alphaR[1]*fL[3]+(1.732050807568877*fL[2]+fL[0])*alphaR[3]+fL[1]*alphaR[2]); 
  incr[6] = -0.25*(3.0*(alphaR[1]*fL[7]+alphaR[0]*fL[6])+1.732050807568877*alphaR[1]*fL[5]+3.0*alphaR[3]*fL[4]+1.732050807568877*(alphaR[0]*fL[3]+fL[1]*alphaR[3])+alphaR[2]*(3.0*fL[2]+1.732050807568877*fL[0])); 
  incr[7] = -0.25*(3.0*(alphaR[0]*fL[7]+alphaR[1]*fL[6])+1.732050807568877*alphaR[0]*fL[5]+3.0*alphaR[2]*fL[4]+1.732050807568877*alphaR[1]*fL[3]+(3.0*fL[2]+1.732050807568877*fL[0])*alphaR[3]+1.732050807568877*fL[1]*alphaR[2]); 
  } else { 
  incr[0] = -0.25*(1.732050807568877*(alphaR[3]*fR[7]+alphaR[2]*fR[6])-1.0*alphaR[3]*fR[5]+1.732050807568877*alphaR[1]*fR[4]-1.0*alphaR[2]*fR[3]+1.732050807568877*alphaR[0]*fR[2]-1.0*(alphaR[1]*fR[1]+alphaR[0]*fR[0])); 
  incr[1] = -0.25*(1.732050807568877*(alphaR[2]*fR[7]+alphaR[3]*fR[6])-1.0*alphaR[2]*fR[5]+1.732050807568877*alphaR[0]*fR[4]-1.0*alphaR[3]*fR[3]+1.732050807568877*alphaR[1]*fR[2]-1.0*(alphaR[0]*fR[1]+fR[0]*alphaR[1])); 
  incr[2] = 0.25*(3.0*(alphaR[3]*fR[7]+alphaR[2]*fR[6])-1.732050807568877*alphaR[3]*fR[5]+3.0*alphaR[1]*fR[4]-1.732050807568877*alphaR[2]*fR[3]+3.0*alphaR[0]*fR[2]-1.732050807568877*(alphaR[1]*fR[1]+alphaR[0]*fR[0])); 
  incr[3] = -0.25*(1.732050807568877*(alphaR[1]*fR[7]+alphaR[0]*fR[6])-1.0*alphaR[1]*fR[5]+1.732050807568877*alphaR[3]*fR[4]-1.0*(alphaR[0]*fR[3]+fR[1]*alphaR[3])+alphaR[2]*(1.732050807568877*fR[2]-1.0*fR[0])); 
  incr[4] = 0.25*(3.0*(alphaR[2]*fR[7]+alphaR[3]*fR[6])-1.732050807568877*alphaR[2]*fR[5]+3.0*alphaR[0]*fR[4]-1.732050807568877*alphaR[3]*fR[3]+3.0*alphaR[1]*fR[2]-1.732050807568877*(alphaR[0]*fR[1]+fR[0]*alphaR[1])); 
  incr[5] = -0.25*(1.732050807568877*(alphaR[0]*fR[7]+alphaR[1]*fR[6])-1.0*alphaR[0]*fR[5]+1.732050807568877*alphaR[2]*fR[4]-1.0*alphaR[1]*fR[3]+(1.732050807568877*fR[2]-1.0*fR[0])*alphaR[3]-1.0*fR[1]*alphaR[2]); 
  incr[6] = 0.25*(3.0*(alphaR[1]*fR[7]+alphaR[0]*fR[6])-1.732050807568877*alphaR[1]*fR[5]+3.0*alphaR[3]*fR[4]-1.732050807568877*(alphaR[0]*fR[3]+fR[1]*alphaR[3])+alphaR[2]*(3.0*fR[2]-1.732050807568877*fR[0])); 
  incr[7] = 0.25*(3.0*(alphaR[0]*fR[7]+alphaR[1]*fR[6])-1.732050807568877*alphaR[0]*fR[5]+3.0*alphaR[2]*fR[4]-1.732050807568877*alphaR[1]*fR[3]+(3.0*fR[2]-1.732050807568877*fR[0])*alphaR[3]-1.732050807568877*fR[1]*alphaR[2]); 
  }
#elif upwindType == QUAD 
  double alphaOrdR;
  double fUpOrd[4];
  alphaOrdR = 0.5*alphaR[3]-0.5*(alphaR[2]+alphaR[1])+0.5*alphaR[0]; 
  fUpOrd[0] = 0.5*((0.6123724356957944*(fR[7]+fL[7])-0.6123724356957944*(fR[6]+fL[6])-0.3535533905932737*fR[5]+0.3535533905932737*fL[5]-0.6123724356957944*(fR[4]+fL[4])+0.3535533905932737*fR[3]-0.3535533905932737*fL[3]+0.6123724356957944*(fR[2]+fL[2])+0.3535533905932737*fR[1]-0.3535533905932737*(fL[1]+fR[0])+0.3535533905932737*fL[0])*sgn(alphaOrdR)-0.6123724356957944*fR[7]+0.6123724356957944*(fL[7]+fR[6])-0.6123724356957944*fL[6]+0.3535533905932737*(fR[5]+fL[5])+0.6123724356957944*fR[4]-0.6123724356957944*fL[4]-0.3535533905932737*(fR[3]+fL[3])-0.6123724356957944*fR[2]+0.6123724356957944*fL[2]-0.3535533905932737*(fR[1]+fL[1])+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*(alphaR[1]+alphaR[0])-0.5*(alphaR[3]+alphaR[2]); 
  fUpOrd[1] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]+fR[6]+fL[6]))+0.3535533905932737*fR[5]-0.3535533905932737*fL[5]+0.6123724356957944*(fR[4]+fL[4])+0.3535533905932737*fR[3]-0.3535533905932737*fL[3]+0.6123724356957944*(fR[2]+fL[2])-0.3535533905932737*(fR[1]+fR[0])+0.3535533905932737*(fL[1]+fL[0]))*sgn(alphaOrdR)+0.6123724356957944*(fR[7]+fR[6])-0.6123724356957944*(fL[7]+fL[6])-0.3535533905932737*(fR[5]+fL[5])-0.6123724356957944*fR[4]+0.6123724356957944*fL[4]-0.3535533905932737*(fR[3]+fL[3])-0.6123724356957944*fR[2]+0.6123724356957944*fL[2]+0.3535533905932737*(fR[1]+fL[1]+fR[0]+fL[0])); 
  alphaOrdR = (-0.5*alphaR[3])+0.5*alphaR[2]-0.5*alphaR[1]+0.5*alphaR[0]; 
  fUpOrd[2] = 0.5*(((-0.6123724356957944*(fR[7]+fL[7]))+0.6123724356957944*(fR[6]+fL[6])+0.3535533905932737*fR[5]-0.3535533905932737*fL[5]-0.6123724356957944*(fR[4]+fL[4])-0.3535533905932737*fR[3]+0.3535533905932737*fL[3]+0.6123724356957944*(fR[2]+fL[2])+0.3535533905932737*fR[1]-0.3535533905932737*(fL[1]+fR[0])+0.3535533905932737*fL[0])*sgn(alphaOrdR)+0.6123724356957944*fR[7]-0.6123724356957944*(fL[7]+fR[6])+0.6123724356957944*fL[6]-0.3535533905932737*(fR[5]+fL[5])+0.6123724356957944*fR[4]-0.6123724356957944*fL[4]+0.3535533905932737*(fR[3]+fL[3])-0.6123724356957944*fR[2]+0.6123724356957944*fL[2]-0.3535533905932737*(fR[1]+fL[1])+0.3535533905932737*(fR[0]+fL[0])); 
  alphaOrdR = 0.5*(alphaR[3]+alphaR[2]+alphaR[1]+alphaR[0]); 
  fUpOrd[3] = 0.5*((0.6123724356957944*(fR[7]+fL[7]+fR[6]+fL[6])-0.3535533905932737*fR[5]+0.3535533905932737*fL[5]+0.6123724356957944*(fR[4]+fL[4])-0.3535533905932737*fR[3]+0.3535533905932737*fL[3]+0.6123724356957944*(fR[2]+fL[2])-0.3535533905932737*(fR[1]+fR[0])+0.3535533905932737*(fL[1]+fL[0]))*sgn(alphaOrdR)-0.6123724356957944*(fR[7]+fR[6])+0.6123724356957944*(fL[7]+fL[6])+0.3535533905932737*(fR[5]+fL[5])-0.6123724356957944*fR[4]+0.6123724356957944*fL[4]+0.3535533905932737*(fR[3]+fL[3])-0.6123724356957944*fR[2]+0.6123724356957944*fL[2]+0.3535533905932737*(fR[1]+fL[1]+fR[0]+fL[0])); 

  double fUp[4];
  fUp[0] = 0.5*(fUpOrd[3]+fUpOrd[2]+fUpOrd[1]+fUpOrd[0]); 
  fUp[1] = 0.5*(fUpOrd[3]-1.0*fUpOrd[2]+fUpOrd[1]-1.0*fUpOrd[0]); 
  fUp[2] = 0.5*(fUpOrd[3]+fUpOrd[2]-1.0*(fUpOrd[1]+fUpOrd[0])); 
  fUp[3] = 0.5*(fUpOrd[3]-1.0*(fUpOrd[2]+fUpOrd[1])+fUpOrd[0]); 

  incr[0] = 0.3535533905932737*(alphaR[3]*fUp[3]+alphaR[2]*fUp[2]+alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[1] = 0.3535533905932737*(alphaR[2]*fUp[3]+fUp[2]*alphaR[3]+alphaR[0]*fUp[1]+fUp[0]*alphaR[1]); 
  incr[2] = -0.6123724356957944*(alphaR[3]*fUp[3]+alphaR[2]*fUp[2]+alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[3] = 0.3535533905932737*(alphaR[1]*fUp[3]+fUp[1]*alphaR[3]+alphaR[0]*fUp[2]+fUp[0]*alphaR[2]); 
  incr[4] = -0.6123724356957944*(alphaR[2]*fUp[3]+fUp[2]*alphaR[3]+alphaR[0]*fUp[1]+fUp[0]*alphaR[1]); 
  incr[5] = 0.3535533905932737*(alphaR[0]*fUp[3]+fUp[0]*alphaR[3]+alphaR[1]*fUp[2]+fUp[1]*alphaR[2]); 
  incr[6] = -0.6123724356957944*(alphaR[1]*fUp[3]+fUp[1]*alphaR[3]+alphaR[0]*fUp[2]+fUp[0]*alphaR[2]); 
  incr[7] = -0.6123724356957944*(alphaR[0]*fUp[3]+fUp[0]*alphaR[3]+alphaR[1]*fUp[2]+fUp[1]*alphaR[2]); 

#endif 
  outR[0] += incr[0]*rdvpar2R; 
  outR[1] += incr[1]*rdvpar2R; 
  outR[2] += incr[2]*rdvpar2R; 
  outR[3] += incr[3]*rdvpar2R; 
  outR[4] += incr[4]*rdvpar2R; 
  outR[5] += incr[5]*rdvpar2R; 
  outR[6] += incr[6]*rdvpar2R; 
  outR[7] += incr[7]*rdvpar2R; 

  outL[0] += -1.0*incr[0]*rdvpar2L; 
  outL[1] += -1.0*incr[1]*rdvpar2L; 
  outL[2] += incr[2]*rdvpar2L; 
  outL[3] += -1.0*incr[3]*rdvpar2L; 
  outL[4] += incr[4]*rdvpar2L; 
  outL[5] += -1.0*incr[5]*rdvpar2L; 
  outL[6] += incr[6]*rdvpar2L; 
  outL[7] += incr[7]*rdvpar2L; 

  return std::abs(alphaSurfAvgR); 
} 
