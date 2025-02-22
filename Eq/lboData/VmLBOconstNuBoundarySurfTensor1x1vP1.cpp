#include <VmLBOModDecl.h> 
double VmLBOconstNuBoundarySurf1x1vTensor_VX_P1(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const int *idxl, const int *idxr, const double nuSum, const double vMuMidMax, const double *nuUSum, const double *nuVtSqSum, const double *fl, const double *fr, double *outl, double *outr) 
{ 
  // w[2]:       Cell-center coordinates.
  // dxv[2]:     Cell spacing.
  // idx[2]:     current grid index.
  // nuSum:         collisionalities added (self and cross species collisionalities). 
  // vMuMidMax:     maximum midpoint value of v-u. 
  // nuUSum[2]:     sum of bulk velocities times their respective collisionalities. 
  // nuVtSqSum[2]:  sum of thermal speeds squared time their respective collisionalities. 
  // fl/fr:      Distribution function in left/right cells 
  // outl/outr:  Incremented distribution function in left/right cells 
  double rdvSq4L = 4.0/(dxvl[1]*dxvl[1]); 
  double rdvSq4R = 4.0/(dxvr[1]*dxvr[1]); 

  if (idxr[1] == 1) {

    outr[2] += (-1.060660171779821*nuVtSqSum[1]*fr[3]*rdvSq4R)-1.060660171779821*nuVtSqSum[0]*fr[2]*rdvSq4R+0.6123724356957944*fr[1]*nuVtSqSum[1]*rdvSq4R+0.6123724356957944*fr[0]*nuVtSqSum[0]*rdvSq4R; 
    outr[3] += (-1.060660171779821*nuVtSqSum[0]*fr[3]*rdvSq4R)-1.060660171779821*nuVtSqSum[1]*fr[2]*rdvSq4R+0.6123724356957944*fr[0]*nuVtSqSum[1]*rdvSq4R+0.6123724356957944*nuVtSqSum[0]*fr[1]*rdvSq4R; 

  } else {

    outl[2] += (-1.060660171779821*nuVtSqSum[1]*fl[3]*rdvSq4L)-1.060660171779821*nuVtSqSum[0]*fl[2]*rdvSq4L-0.6123724356957944*fl[1]*nuVtSqSum[1]*rdvSq4L-0.6123724356957944*fl[0]*nuVtSqSum[0]*rdvSq4L; 
    outl[3] += (-1.060660171779821*nuVtSqSum[0]*fl[3]*rdvSq4L)-1.060660171779821*nuVtSqSum[1]*fl[2]*rdvSq4L-0.6123724356957944*fl[0]*nuVtSqSum[1]*rdvSq4L-0.6123724356957944*nuVtSqSum[0]*fl[1]*rdvSq4L; 

  }
  return 0.0; 
} 
