#include <GyrokineticModDecl.h>
double GyrokineticSimpleHelicalSurf1x1vTensor_xL_P2_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
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

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;

  double hamilL[9]; 
  hamilL[0] = (0.3333333333333333*(3.0*rdvpar2SqL*(m_*wvparSqL+1.414213562373095*phi[0]*q_)+m_))/rdvpar2SqL; 
  hamilL[1] = 1.414213562373095*phi[1]*q_; 
  hamilL[2] = (1.154700538379252*m_*wvparL)/rdvpar2L; 
  hamilL[4] = 1.414213562373095*phi[2]*q_; 
  hamilL[5] = (0.2981423969999719*m_)/rdvpar2SqL; 

  double BstarZdBmagL[9]; 
  BstarZdBmagL[0] = 1.414213562373095*cmag[0]; 

  double alphaL[3]; 
  alphaL[0] = (0.6123724356957944*BstarZdBmagL[0]*hamilL[2]*rdvpar2L)/m_; 
  alphaL[1] = (1.369306393762915*BstarZdBmagL[0]*hamilL[5]*rdvpar2L)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgL = (0.2165063509461096*BstarZdBmagL[0]*hamilL[2]*rdvpar2L)/m_; 

  double incr[9]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgL>0) { 
  incr[0] = 0.08333333333333333*(9.48683298050514*(alphaL[1]*fL[6]+alphaL[0]*fL[4])+alphaL[1]*(7.348469228349534*fL[3]+4.242640687119286*fL[2])+alphaL[0]*(7.348469228349534*fL[1]+4.242640687119286*fL[0])); 
  incr[1] = -0.25*(5.477225575051662*(alphaL[1]*fL[6]+alphaL[0]*fL[4])+alphaL[1]*(4.242640687119286*fL[3]+2.449489742783178*fL[2])+alphaL[0]*(4.242640687119286*fL[1]+2.449489742783178*fL[0])); 
  incr[2] = 0.01666666666666667*(alphaL[1]*(42.42640687119286*fL[8]+32.86335345030997*fL[7])+47.43416490252569*alphaL[0]*fL[6]+alphaL[1]*(18.97366596101028*fL[5]+47.43416490252571*fL[4])+alphaL[0]*(36.74234614174767*fL[3]+21.21320343559643*fL[2])+alphaL[1]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[3] = -0.05*(alphaL[1]*(24.49489742783179*fL[8]+18.97366596101028*fL[7])+27.38612787525831*alphaL[0]*fL[6]+alphaL[1]*(10.95445115010332*fL[5]+27.38612787525831*fL[4])+alphaL[0]*(21.21320343559643*fL[3]+12.24744871391589*fL[2])+alphaL[1]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[4] = 0.08333333333333333*(21.21320343559643*alphaL[1]*fL[6]+21.21320343559643*alphaL[0]*fL[4]+alphaL[1]*(16.43167672515498*fL[3]+9.48683298050514*fL[2])+alphaL[0]*(16.43167672515498*fL[1]+9.48683298050514*fL[0])); 
  incr[5] = 0.01666666666666667*(alphaL[0]*(47.43416490252571*fL[8]+36.74234614174768*fL[7])+42.42640687119286*alphaL[1]*fL[6]+21.21320343559643*alphaL[0]*fL[5]+alphaL[1]*(32.86335345030997*fL[3]+18.97366596101028*fL[2])); 
  incr[6] = 0.01666666666666667*(alphaL[1]*(94.8683298050514*fL[8]+73.48469228349535*fL[7])+106.0660171779821*alphaL[0]*fL[6]+alphaL[1]*(42.42640687119286*fL[5]+106.0660171779822*fL[4])+alphaL[0]*(82.15838362577493*fL[3]+47.43416490252569*fL[2])+alphaL[1]*(82.15838362577493*fL[1]+47.43416490252569*fL[0])); 
  incr[7] = -0.05*(alphaL[0]*(27.38612787525831*fL[8]+21.21320343559643*fL[7])+24.49489742783179*alphaL[1]*fL[6]+12.24744871391589*alphaL[0]*fL[5]+alphaL[1]*(18.97366596101028*fL[3]+10.95445115010333*fL[2])); 
  incr[8] = 0.08333333333333333*(alphaL[0]*(21.21320343559643*fL[8]+16.43167672515499*fL[7])+18.97366596101028*alphaL[1]*fL[6]+9.48683298050514*alphaL[0]*fL[5]+alphaL[1]*(14.69693845669907*fL[3]+8.485281374238571*fL[2])); 
  } else { 
  incr[0] = 0.08333333333333333*(9.48683298050514*(alphaL[1]*fR[6]+alphaL[0]*fR[4])+alphaL[1]*(4.242640687119286*fR[2]-7.348469228349534*fR[3])+alphaL[0]*(4.242640687119286*fR[0]-7.348469228349534*fR[1])); 
  incr[1] = -0.25*(5.477225575051662*(alphaL[1]*fR[6]+alphaL[0]*fR[4])+alphaL[1]*(2.449489742783178*fR[2]-4.242640687119286*fR[3])+alphaL[0]*(2.449489742783178*fR[0]-4.242640687119286*fR[1])); 
  incr[2] = 0.01666666666666667*(alphaL[1]*(42.42640687119286*fR[8]-32.86335345030997*fR[7])+47.43416490252569*alphaL[0]*fR[6]+alphaL[1]*(18.97366596101028*fR[5]+47.43416490252571*fR[4])+alphaL[0]*(21.21320343559643*fR[2]-36.74234614174767*fR[3])+alphaL[1]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[3] = -0.05*(alphaL[1]*(24.49489742783179*fR[8]-18.97366596101028*fR[7])+27.38612787525831*alphaL[0]*fR[6]+alphaL[1]*(10.95445115010332*fR[5]+27.38612787525831*fR[4])+alphaL[0]*(12.24744871391589*fR[2]-21.21320343559643*fR[3])+alphaL[1]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[4] = 0.08333333333333333*(21.21320343559643*alphaL[1]*fR[6]+21.21320343559643*alphaL[0]*fR[4]+alphaL[1]*(9.48683298050514*fR[2]-16.43167672515498*fR[3])+alphaL[0]*(9.48683298050514*fR[0]-16.43167672515498*fR[1])); 
  incr[5] = 0.01666666666666667*(alphaL[0]*(47.43416490252571*fR[8]-36.74234614174768*fR[7])+42.42640687119286*alphaL[1]*fR[6]+21.21320343559643*alphaL[0]*fR[5]+alphaL[1]*(18.97366596101028*fR[2]-32.86335345030997*fR[3])); 
  incr[6] = 0.01666666666666667*(alphaL[1]*(94.8683298050514*fR[8]-73.48469228349535*fR[7])+106.0660171779821*alphaL[0]*fR[6]+alphaL[1]*(42.42640687119286*fR[5]+106.0660171779822*fR[4])+alphaL[0]*(47.43416490252569*fR[2]-82.15838362577493*fR[3])+alphaL[1]*(47.43416490252569*fR[0]-82.15838362577493*fR[1])); 
  incr[7] = -0.05*(alphaL[0]*(27.38612787525831*fR[8]-21.21320343559643*fR[7])+24.49489742783179*alphaL[1]*fR[6]+12.24744871391589*alphaL[0]*fR[5]+alphaL[1]*(10.95445115010333*fR[2]-18.97366596101028*fR[3])); 
  incr[8] = 0.08333333333333333*(alphaL[0]*(21.21320343559643*fR[8]-16.43167672515499*fR[7])+18.97366596101028*alphaL[1]*fR[6]+9.48683298050514*alphaL[0]*fR[5]+alphaL[1]*(8.485281374238571*fR[2]-14.69693845669907*fR[3])); 
  }
#elif upwindType == QUAD 
  double alphaOrdL;
  double fUpOrd[3];
  alphaOrdL = 0.7071067811865475*alphaL[0]-0.9486832980505137*alphaL[1]; 
  fUpOrd[0] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]-1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])+1.161895003862225*fR[3]-1.161895003862225*fL[3]-0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])+1.5*fR[6]-(1.5*fL[6]+0.4472135954999579*(fR[5]-fL[5]))+1.118033988749895*(fL[4]-fR[4])-1.161895003862225*(fR[3]+fL[3])-(0.6708203932499369*(fL[2]-fR[2])-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdL); 
  alphaOrdL = 0.7071067811865475*alphaL[0]; 
  fUpOrd[1] = 0.5*((1.25*fR[8]-1.25*fL[8]-0.9682458365518543*(fR[7]+fL[7])+0.5590169943749475*fR[5]-0.5590169943749475*fL[5]-1.118033988749895*fR[4]+1.118033988749895*fL[4]+0.8660254037844386*(fR[1]+fL[1])-0.5*fR[0]+0.5*fL[0])*sgn(alphaOrdL)-1.25*(fR[8]+fL[8])+0.9682458365518543*fR[7]-0.9682458365518543*fL[7]-0.5590169943749475*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0])); 
  alphaOrdL = 0.9486832980505137*alphaL[1]+0.7071067811865475*alphaL[0]; 
  fUpOrd[2] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]+1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-1.161895003862225*fR[3]+1.161895003862225*fL[3]+0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])-1.5*fR[6]-(0.4472135954999579*(fR[5]-fL[5])-1.5*fL[6])+1.118033988749895*(fL[4]-fR[4])+1.161895003862225*(fR[3]+fL[3])-((-0.6708203932499369*(fL[2]-fR[2]))-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdL); 

  double fUp[3];
  fUp[0] = 0.07856742013183861*(5.0*fUpOrd[2]+8.0*fUpOrd[1]+5.0*fUpOrd[0]); 
  fUp[1] = 0.5270462766947298*(fUpOrd[2]-1.0*fUpOrd[0]); 
  fUp[2] = 0.3513641844631533*(fUpOrd[2]-2.0*fUpOrd[1]+fUpOrd[0]); 

  incr[0] = 0.5*(alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[1] = -0.8660254037844386*(alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[2] = 0.1*(4.47213595499958*alphaL[1]*fUp[2]+5.0*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[3] = -0.1*(7.745966692414834*alphaL[1]*fUp[2]+8.660254037844386*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[4] = 1.118033988749895*(alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[5] = 0.1*(5.0*alphaL[0]*fUp[2]+4.47213595499958*alphaL[1]*fUp[1]); 
  incr[6] = 0.03333333333333333*(30.0*alphaL[1]*fUp[2]+33.54101966249684*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[7] = -0.1*(8.660254037844387*alphaL[0]*fUp[2]+7.745966692414834*alphaL[1]*fUp[1]); 
  incr[8] = 0.5*(2.23606797749979*alphaL[0]*fUp[2]+2.0*alphaL[1]*fUp[1]); 

#endif 
  outR[0] += incr[0]*rdx2R; 
  outR[1] += incr[1]*rdx2R; 
  outR[2] += incr[2]*rdx2R; 
  outR[3] += incr[3]*rdx2R; 
  outR[4] += incr[4]*rdx2R; 
  outR[5] += incr[5]*rdx2R; 
  outR[6] += incr[6]*rdx2R; 
  outR[7] += incr[7]*rdx2R; 
  outR[8] += incr[8]*rdx2R; 

  outL[0] += -1.0*incr[0]*rdx2L; 
  outL[1] += incr[1]*rdx2L; 
  outL[2] += -1.0*incr[2]*rdx2L; 
  outL[3] += incr[3]*rdx2L; 
  outL[4] += -1.0*incr[4]*rdx2L; 
  outL[5] += -1.0*incr[5]*rdx2L; 
  outL[6] += -1.0*incr[6]*rdx2L; 
  outL[7] += incr[7]*rdx2L; 
  outL[8] += -1.0*incr[8]*rdx2L; 

  return std::abs(alphaSurfAvgL); 
} 
double GyrokineticSimpleHelicalSurf1x1vTensor_xR_P2_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
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

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;

  double hamilR[9]; 
  hamilR[0] = (0.3333333333333333*(3.0*rdvpar2SqR*(m_*wvparSqR+1.414213562373095*phi[0]*q_)+m_))/rdvpar2SqR; 
  hamilR[1] = 1.414213562373095*phi[1]*q_; 
  hamilR[2] = (1.154700538379252*m_*wvparR)/rdvpar2R; 
  hamilR[4] = 1.414213562373095*phi[2]*q_; 
  hamilR[5] = (0.2981423969999719*m_)/rdvpar2SqR; 

  double BstarZdBmagR[9]; 
  BstarZdBmagR[0] = 1.414213562373095*cmag[0]; 

  double alphaR[3]; 
  alphaR[0] = (0.6123724356957944*BstarZdBmagR[0]*hamilR[2]*rdvpar2R)/m_; 
  alphaR[1] = (1.369306393762915*BstarZdBmagR[0]*hamilR[5]*rdvpar2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = (0.2165063509461096*BstarZdBmagR[0]*hamilR[2]*rdvpar2R)/m_; 

  double incr[9]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgR>0) { 
  incr[0] = 0.08333333333333333*(9.48683298050514*(alphaR[1]*fL[6]+alphaR[0]*fL[4])+alphaR[1]*(7.348469228349534*fL[3]+4.242640687119286*fL[2])+alphaR[0]*(7.348469228349534*fL[1]+4.242640687119286*fL[0])); 
  incr[1] = -0.25*(5.477225575051662*(alphaR[1]*fL[6]+alphaR[0]*fL[4])+alphaR[1]*(4.242640687119286*fL[3]+2.449489742783178*fL[2])+alphaR[0]*(4.242640687119286*fL[1]+2.449489742783178*fL[0])); 
  incr[2] = 0.01666666666666667*(alphaR[1]*(42.42640687119286*fL[8]+32.86335345030997*fL[7])+47.43416490252569*alphaR[0]*fL[6]+alphaR[1]*(18.97366596101028*fL[5]+47.43416490252571*fL[4])+alphaR[0]*(36.74234614174767*fL[3]+21.21320343559643*fL[2])+alphaR[1]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[3] = -0.05*(alphaR[1]*(24.49489742783179*fL[8]+18.97366596101028*fL[7])+27.38612787525831*alphaR[0]*fL[6]+alphaR[1]*(10.95445115010332*fL[5]+27.38612787525831*fL[4])+alphaR[0]*(21.21320343559643*fL[3]+12.24744871391589*fL[2])+alphaR[1]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[4] = 0.08333333333333333*(21.21320343559643*alphaR[1]*fL[6]+21.21320343559643*alphaR[0]*fL[4]+alphaR[1]*(16.43167672515498*fL[3]+9.48683298050514*fL[2])+alphaR[0]*(16.43167672515498*fL[1]+9.48683298050514*fL[0])); 
  incr[5] = 0.01666666666666667*(alphaR[0]*(47.43416490252571*fL[8]+36.74234614174768*fL[7])+42.42640687119286*alphaR[1]*fL[6]+21.21320343559643*alphaR[0]*fL[5]+alphaR[1]*(32.86335345030997*fL[3]+18.97366596101028*fL[2])); 
  incr[6] = 0.01666666666666667*(alphaR[1]*(94.8683298050514*fL[8]+73.48469228349535*fL[7])+106.0660171779821*alphaR[0]*fL[6]+alphaR[1]*(42.42640687119286*fL[5]+106.0660171779822*fL[4])+alphaR[0]*(82.15838362577493*fL[3]+47.43416490252569*fL[2])+alphaR[1]*(82.15838362577493*fL[1]+47.43416490252569*fL[0])); 
  incr[7] = -0.05*(alphaR[0]*(27.38612787525831*fL[8]+21.21320343559643*fL[7])+24.49489742783179*alphaR[1]*fL[6]+12.24744871391589*alphaR[0]*fL[5]+alphaR[1]*(18.97366596101028*fL[3]+10.95445115010333*fL[2])); 
  incr[8] = 0.08333333333333333*(alphaR[0]*(21.21320343559643*fL[8]+16.43167672515499*fL[7])+18.97366596101028*alphaR[1]*fL[6]+9.48683298050514*alphaR[0]*fL[5]+alphaR[1]*(14.69693845669907*fL[3]+8.485281374238571*fL[2])); 
  } else { 
  incr[0] = 0.08333333333333333*(9.48683298050514*(alphaR[1]*fR[6]+alphaR[0]*fR[4])+alphaR[1]*(4.242640687119286*fR[2]-7.348469228349534*fR[3])+alphaR[0]*(4.242640687119286*fR[0]-7.348469228349534*fR[1])); 
  incr[1] = -0.25*(5.477225575051662*(alphaR[1]*fR[6]+alphaR[0]*fR[4])+alphaR[1]*(2.449489742783178*fR[2]-4.242640687119286*fR[3])+alphaR[0]*(2.449489742783178*fR[0]-4.242640687119286*fR[1])); 
  incr[2] = 0.01666666666666667*(alphaR[1]*(42.42640687119286*fR[8]-32.86335345030997*fR[7])+47.43416490252569*alphaR[0]*fR[6]+alphaR[1]*(18.97366596101028*fR[5]+47.43416490252571*fR[4])+alphaR[0]*(21.21320343559643*fR[2]-36.74234614174767*fR[3])+alphaR[1]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[3] = -0.05*(alphaR[1]*(24.49489742783179*fR[8]-18.97366596101028*fR[7])+27.38612787525831*alphaR[0]*fR[6]+alphaR[1]*(10.95445115010332*fR[5]+27.38612787525831*fR[4])+alphaR[0]*(12.24744871391589*fR[2]-21.21320343559643*fR[3])+alphaR[1]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[4] = 0.08333333333333333*(21.21320343559643*alphaR[1]*fR[6]+21.21320343559643*alphaR[0]*fR[4]+alphaR[1]*(9.48683298050514*fR[2]-16.43167672515498*fR[3])+alphaR[0]*(9.48683298050514*fR[0]-16.43167672515498*fR[1])); 
  incr[5] = 0.01666666666666667*(alphaR[0]*(47.43416490252571*fR[8]-36.74234614174768*fR[7])+42.42640687119286*alphaR[1]*fR[6]+21.21320343559643*alphaR[0]*fR[5]+alphaR[1]*(18.97366596101028*fR[2]-32.86335345030997*fR[3])); 
  incr[6] = 0.01666666666666667*(alphaR[1]*(94.8683298050514*fR[8]-73.48469228349535*fR[7])+106.0660171779821*alphaR[0]*fR[6]+alphaR[1]*(42.42640687119286*fR[5]+106.0660171779822*fR[4])+alphaR[0]*(47.43416490252569*fR[2]-82.15838362577493*fR[3])+alphaR[1]*(47.43416490252569*fR[0]-82.15838362577493*fR[1])); 
  incr[7] = -0.05*(alphaR[0]*(27.38612787525831*fR[8]-21.21320343559643*fR[7])+24.49489742783179*alphaR[1]*fR[6]+12.24744871391589*alphaR[0]*fR[5]+alphaR[1]*(10.95445115010333*fR[2]-18.97366596101028*fR[3])); 
  incr[8] = 0.08333333333333333*(alphaR[0]*(21.21320343559643*fR[8]-16.43167672515499*fR[7])+18.97366596101028*alphaR[1]*fR[6]+9.48683298050514*alphaR[0]*fR[5]+alphaR[1]*(8.485281374238571*fR[2]-14.69693845669907*fR[3])); 
  }
#elif upwindType == QUAD 
  double alphaOrdR;
  double fUpOrd[3];
  alphaOrdR = 0.7071067811865475*alphaR[0]-0.9486832980505137*alphaR[1]; 
  fUpOrd[0] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]-1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])+1.161895003862225*fR[3]-1.161895003862225*fL[3]-0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])+1.5*fR[6]-(1.5*fL[6]+0.4472135954999579*(fR[5]-fL[5]))+1.118033988749895*(fL[4]-fR[4])-1.161895003862225*(fR[3]+fL[3])-(0.6708203932499369*(fL[2]-fR[2])-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdR); 
  alphaOrdR = 0.7071067811865475*alphaR[0]; 
  fUpOrd[1] = 0.5*((1.25*fR[8]-1.25*fL[8]-0.9682458365518543*(fR[7]+fL[7])+0.5590169943749475*fR[5]-0.5590169943749475*fL[5]-1.118033988749895*fR[4]+1.118033988749895*fL[4]+0.8660254037844386*(fR[1]+fL[1])-0.5*fR[0]+0.5*fL[0])*sgn(alphaOrdR)-1.25*(fR[8]+fL[8])+0.9682458365518543*fR[7]-0.9682458365518543*fL[7]-0.5590169943749475*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0])); 
  alphaOrdR = 0.9486832980505137*alphaR[1]+0.7071067811865475*alphaR[0]; 
  fUpOrd[2] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]+1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-1.161895003862225*fR[3]+1.161895003862225*fL[3]+0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])-1.5*fR[6]-(0.4472135954999579*(fR[5]-fL[5])-1.5*fL[6])+1.118033988749895*(fL[4]-fR[4])+1.161895003862225*(fR[3]+fL[3])-((-0.6708203932499369*(fL[2]-fR[2]))-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdR); 

  double fUp[3];
  fUp[0] = 0.07856742013183861*(5.0*fUpOrd[2]+8.0*fUpOrd[1]+5.0*fUpOrd[0]); 
  fUp[1] = 0.5270462766947298*(fUpOrd[2]-1.0*fUpOrd[0]); 
  fUp[2] = 0.3513641844631533*(fUpOrd[2]-2.0*fUpOrd[1]+fUpOrd[0]); 

  incr[0] = 0.5*(alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[1] = -0.8660254037844386*(alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[2] = 0.1*(4.47213595499958*alphaR[1]*fUp[2]+5.0*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[3] = -0.1*(7.745966692414834*alphaR[1]*fUp[2]+8.660254037844386*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[4] = 1.118033988749895*(alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[5] = 0.1*(5.0*alphaR[0]*fUp[2]+4.47213595499958*alphaR[1]*fUp[1]); 
  incr[6] = 0.03333333333333333*(30.0*alphaR[1]*fUp[2]+33.54101966249684*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[7] = -0.1*(8.660254037844387*alphaR[0]*fUp[2]+7.745966692414834*alphaR[1]*fUp[1]); 
  incr[8] = 0.5*(2.23606797749979*alphaR[0]*fUp[2]+2.0*alphaR[1]*fUp[1]); 

#endif 
  outR[0] += incr[0]*rdx2R; 
  outR[1] += incr[1]*rdx2R; 
  outR[2] += incr[2]*rdx2R; 
  outR[3] += incr[3]*rdx2R; 
  outR[4] += incr[4]*rdx2R; 
  outR[5] += incr[5]*rdx2R; 
  outR[6] += incr[6]*rdx2R; 
  outR[7] += incr[7]*rdx2R; 
  outR[8] += incr[8]*rdx2R; 

  outL[0] += -1.0*incr[0]*rdx2L; 
  outL[1] += incr[1]*rdx2L; 
  outL[2] += -1.0*incr[2]*rdx2L; 
  outL[3] += incr[3]*rdx2L; 
  outL[4] += -1.0*incr[4]*rdx2L; 
  outL[5] += -1.0*incr[5]*rdx2L; 
  outL[6] += -1.0*incr[6]*rdx2L; 
  outL[7] += incr[7]*rdx2L; 
  outL[8] += -1.0*incr[8]*rdx2L; 

  return std::abs(alphaSurfAvgR); 
} 
double GyrokineticSimpleHelicalSurf1x1vTensor_vpar_P2_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
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

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;

  double hamilR[9]; 
  hamilR[0] = (0.3333333333333333*(3.0*rdvpar2SqR*(m_*wvparSqR+1.414213562373095*phi[0]*q_)+m_))/rdvpar2SqR; 
  hamilR[1] = 1.414213562373095*phi[1]*q_; 
  hamilR[2] = (1.154700538379252*m_*wvparR)/rdvpar2R; 
  hamilR[4] = 1.414213562373095*phi[2]*q_; 
  hamilR[5] = (0.2981423969999719*m_)/rdvpar2SqR; 

  double BstarZdBmagR[9]; 
  BstarZdBmagR[0] = 1.414213562373095*cmag[0]; 

  double alphaR[3]; 
  alphaR[0] = -(0.6123724356957944*BstarZdBmagR[0]*hamilR[1]*rdx2R)/m_; 
  alphaR[1] = -(1.369306393762915*BstarZdBmagR[0]*hamilR[4]*rdx2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.2165063509461096*BstarZdBmagR[0]*hamilR[1]*rdx2R)/m_; 

  double incr[9]; 
  double amax = amax_in; 

  double fAvg[3]; 
  fAvg[0] = 0.7071067811865475*(2.23606797749979*(fR[5]+fL[5])+1.732050807568877*(fL[2]-1.0*fR[2])+fR[0]+fL[0]); 
  fAvg[1] = 0.2357022603955158*(1.732050807568877*(3.872983346207417*(fR[7]+fL[7])+3.0*(fL[3]-1.0*fR[3]))+3.0*(fR[1]+fL[1])); 
  fAvg[2] = 0.1414213562373095*(2.23606797749979*(5.0*(fR[8]+fL[8])+3.872983346207417*(fL[6]-1.0*fR[6]))+5.0*(fR[4]+fL[4])); 

  double Ghat[3]; 
  Ghat[0] = -0.25*((3.16227766016838*fR[5]-3.16227766016838*fL[5]-2.449489742783178*(fR[2]+fL[2])+1.414213562373095*fR[0]-1.414213562373095*fL[0])*amax-1.414213562373095*(alphaR[1]*fAvg[1]+alphaR[0]*fAvg[0])); 
  Ghat[1] = -0.01666666666666667*((47.43416490252569*fR[7]-47.43416490252569*fL[7]-36.74234614174767*(fR[3]+fL[3])+21.21320343559643*fR[1]-21.21320343559643*fL[1])*amax-18.97366596101028*alphaR[1]*fAvg[2]-21.21320343559643*(alphaR[0]*fAvg[1]+fAvg[0]*alphaR[1])); 
  Ghat[2] = -0.05*((15.8113883008419*fR[8]-15.8113883008419*fL[8]-12.24744871391589*(fR[6]+fL[6])+7.071067811865476*fR[4]-7.071067811865476*fL[4])*amax-7.071067811865476*alphaR[0]*fAvg[2]-6.324555320336761*alphaR[1]*fAvg[1]); 

  incr[0] = 0.7071067811865475*Ghat[0]; 
  incr[1] = 0.7071067811865475*Ghat[1]; 
  incr[2] = -1.224744871391589*Ghat[0]; 
  incr[3] = -1.224744871391589*Ghat[1]; 
  incr[4] = 0.7071067811865475*Ghat[2]; 
  incr[5] = 1.58113883008419*Ghat[0]; 
  incr[6] = -1.224744871391589*Ghat[2]; 
  incr[7] = 1.58113883008419*Ghat[1]; 
  incr[8] = 1.58113883008419*Ghat[2]; 

  outR[0] += incr[0]*rdvpar2R; 
  outR[1] += incr[1]*rdvpar2R; 
  outR[2] += incr[2]*rdvpar2R; 
  outR[3] += incr[3]*rdvpar2R; 
  outR[4] += incr[4]*rdvpar2R; 
  outR[5] += incr[5]*rdvpar2R; 
  outR[6] += incr[6]*rdvpar2R; 
  outR[7] += incr[7]*rdvpar2R; 
  outR[8] += incr[8]*rdvpar2R; 

  outL[0] += -1.0*incr[0]*rdvpar2L; 
  outL[1] += -1.0*incr[1]*rdvpar2L; 
  outL[2] += incr[2]*rdvpar2L; 
  outL[3] += incr[3]*rdvpar2L; 
  outL[4] += -1.0*incr[4]*rdvpar2L; 
  outL[5] += -1.0*incr[5]*rdvpar2L; 
  outL[6] += incr[6]*rdvpar2L; 
  outL[7] += -1.0*incr[7]*rdvpar2L; 
  outL[8] += -1.0*incr[8]*rdvpar2L; 
return std::abs(alphaSurfAvgR); 
} 
double GyrokineticSimpleHelicalSurf1x1vTensor_xL_P2_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
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

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;

  double hamilL[9]; 
  hamilL[0] = (0.3333333333333333*(3.0*rdvpar2SqL*(m_*wvparSqL+1.414213562373095*phi[0]*q_)+m_))/rdvpar2SqL; 
  hamilL[1] = 1.414213562373095*phi[1]*q_; 
  hamilL[2] = (1.154700538379252*m_*wvparL)/rdvpar2L; 
  hamilL[4] = 1.414213562373095*phi[2]*q_; 
  hamilL[5] = (0.2981423969999719*m_)/rdvpar2SqL; 

  double BstarZdBmagL[9]; 
  BstarZdBmagL[0] = 1.414213562373095*cmag[0]; 
  BstarZdBmagL[1] = 1.414213562373095*cmag[1]; 
  BstarZdBmagL[4] = 1.414213562373095*cmag[2]; 

  double alphaL[3]; 
  alphaL[0] = (0.3535533905932737*hamilL[2]*(3.872983346207417*BstarZdBmagL[4]+3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*rdvpar2L)/m_; 
  alphaL[1] = (0.3535533905932737*(8.660254037844386*BstarZdBmagL[4]+6.708203932499369*BstarZdBmagL[1]+3.872983346207417*BstarZdBmagL[0])*hamilL[5]*rdvpar2L)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgL = (0.125*(3.872983346207417*hamilL[2]*BstarZdBmagL[4]+(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2])*rdvpar2L)/m_; 

  double incr[9]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgL>0) { 
  incr[0] = 0.08333333333333333*(9.48683298050514*(alphaL[1]*fL[6]+alphaL[0]*fL[4])+alphaL[1]*(7.348469228349534*fL[3]+4.242640687119286*fL[2])+alphaL[0]*(7.348469228349534*fL[1]+4.242640687119286*fL[0])); 
  incr[1] = -0.25*(5.477225575051662*(alphaL[1]*fL[6]+alphaL[0]*fL[4])+alphaL[1]*(4.242640687119286*fL[3]+2.449489742783178*fL[2])+alphaL[0]*(4.242640687119286*fL[1]+2.449489742783178*fL[0])); 
  incr[2] = 0.01666666666666667*(alphaL[1]*(42.42640687119286*fL[8]+32.86335345030997*fL[7])+47.43416490252569*alphaL[0]*fL[6]+alphaL[1]*(18.97366596101028*fL[5]+47.43416490252571*fL[4])+alphaL[0]*(36.74234614174767*fL[3]+21.21320343559643*fL[2])+alphaL[1]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[3] = -0.05*(alphaL[1]*(24.49489742783179*fL[8]+18.97366596101028*fL[7])+27.38612787525831*alphaL[0]*fL[6]+alphaL[1]*(10.95445115010332*fL[5]+27.38612787525831*fL[4])+alphaL[0]*(21.21320343559643*fL[3]+12.24744871391589*fL[2])+alphaL[1]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[4] = 0.08333333333333333*(21.21320343559643*alphaL[1]*fL[6]+21.21320343559643*alphaL[0]*fL[4]+alphaL[1]*(16.43167672515498*fL[3]+9.48683298050514*fL[2])+alphaL[0]*(16.43167672515498*fL[1]+9.48683298050514*fL[0])); 
  incr[5] = 0.01666666666666667*(alphaL[0]*(47.43416490252571*fL[8]+36.74234614174768*fL[7])+42.42640687119286*alphaL[1]*fL[6]+21.21320343559643*alphaL[0]*fL[5]+alphaL[1]*(32.86335345030997*fL[3]+18.97366596101028*fL[2])); 
  incr[6] = 0.01666666666666667*(alphaL[1]*(94.8683298050514*fL[8]+73.48469228349535*fL[7])+106.0660171779821*alphaL[0]*fL[6]+alphaL[1]*(42.42640687119286*fL[5]+106.0660171779822*fL[4])+alphaL[0]*(82.15838362577493*fL[3]+47.43416490252569*fL[2])+alphaL[1]*(82.15838362577493*fL[1]+47.43416490252569*fL[0])); 
  incr[7] = -0.05*(alphaL[0]*(27.38612787525831*fL[8]+21.21320343559643*fL[7])+24.49489742783179*alphaL[1]*fL[6]+12.24744871391589*alphaL[0]*fL[5]+alphaL[1]*(18.97366596101028*fL[3]+10.95445115010333*fL[2])); 
  incr[8] = 0.08333333333333333*(alphaL[0]*(21.21320343559643*fL[8]+16.43167672515499*fL[7])+18.97366596101028*alphaL[1]*fL[6]+9.48683298050514*alphaL[0]*fL[5]+alphaL[1]*(14.69693845669907*fL[3]+8.485281374238571*fL[2])); 
  } else { 
  incr[0] = 0.08333333333333333*(9.48683298050514*(alphaL[1]*fR[6]+alphaL[0]*fR[4])+alphaL[1]*(4.242640687119286*fR[2]-7.348469228349534*fR[3])+alphaL[0]*(4.242640687119286*fR[0]-7.348469228349534*fR[1])); 
  incr[1] = -0.25*(5.477225575051662*(alphaL[1]*fR[6]+alphaL[0]*fR[4])+alphaL[1]*(2.449489742783178*fR[2]-4.242640687119286*fR[3])+alphaL[0]*(2.449489742783178*fR[0]-4.242640687119286*fR[1])); 
  incr[2] = 0.01666666666666667*(alphaL[1]*(42.42640687119286*fR[8]-32.86335345030997*fR[7])+47.43416490252569*alphaL[0]*fR[6]+alphaL[1]*(18.97366596101028*fR[5]+47.43416490252571*fR[4])+alphaL[0]*(21.21320343559643*fR[2]-36.74234614174767*fR[3])+alphaL[1]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[3] = -0.05*(alphaL[1]*(24.49489742783179*fR[8]-18.97366596101028*fR[7])+27.38612787525831*alphaL[0]*fR[6]+alphaL[1]*(10.95445115010332*fR[5]+27.38612787525831*fR[4])+alphaL[0]*(12.24744871391589*fR[2]-21.21320343559643*fR[3])+alphaL[1]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[4] = 0.08333333333333333*(21.21320343559643*alphaL[1]*fR[6]+21.21320343559643*alphaL[0]*fR[4]+alphaL[1]*(9.48683298050514*fR[2]-16.43167672515498*fR[3])+alphaL[0]*(9.48683298050514*fR[0]-16.43167672515498*fR[1])); 
  incr[5] = 0.01666666666666667*(alphaL[0]*(47.43416490252571*fR[8]-36.74234614174768*fR[7])+42.42640687119286*alphaL[1]*fR[6]+21.21320343559643*alphaL[0]*fR[5]+alphaL[1]*(18.97366596101028*fR[2]-32.86335345030997*fR[3])); 
  incr[6] = 0.01666666666666667*(alphaL[1]*(94.8683298050514*fR[8]-73.48469228349535*fR[7])+106.0660171779821*alphaL[0]*fR[6]+alphaL[1]*(42.42640687119286*fR[5]+106.0660171779822*fR[4])+alphaL[0]*(47.43416490252569*fR[2]-82.15838362577493*fR[3])+alphaL[1]*(47.43416490252569*fR[0]-82.15838362577493*fR[1])); 
  incr[7] = -0.05*(alphaL[0]*(27.38612787525831*fR[8]-21.21320343559643*fR[7])+24.49489742783179*alphaL[1]*fR[6]+12.24744871391589*alphaL[0]*fR[5]+alphaL[1]*(10.95445115010333*fR[2]-18.97366596101028*fR[3])); 
  incr[8] = 0.08333333333333333*(alphaL[0]*(21.21320343559643*fR[8]-16.43167672515499*fR[7])+18.97366596101028*alphaL[1]*fR[6]+9.48683298050514*alphaL[0]*fR[5]+alphaL[1]*(8.485281374238571*fR[2]-14.69693845669907*fR[3])); 
  }
#elif upwindType == QUAD 
  double alphaOrdL;
  double fUpOrd[3];
  alphaOrdL = 0.7071067811865475*alphaL[0]-0.9486832980505137*alphaL[1]; 
  fUpOrd[0] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]-1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])+1.161895003862225*fR[3]-1.161895003862225*fL[3]-0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])+1.5*fR[6]-(1.5*fL[6]+0.4472135954999579*(fR[5]-fL[5]))+1.118033988749895*(fL[4]-fR[4])-1.161895003862225*(fR[3]+fL[3])-(0.6708203932499369*(fL[2]-fR[2])-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdL); 
  alphaOrdL = 0.7071067811865475*alphaL[0]; 
  fUpOrd[1] = 0.5*((1.25*fR[8]-1.25*fL[8]-0.9682458365518543*(fR[7]+fL[7])+0.5590169943749475*fR[5]-0.5590169943749475*fL[5]-1.118033988749895*fR[4]+1.118033988749895*fL[4]+0.8660254037844386*(fR[1]+fL[1])-0.5*fR[0]+0.5*fL[0])*sgn(alphaOrdL)-1.25*(fR[8]+fL[8])+0.9682458365518543*fR[7]-0.9682458365518543*fL[7]-0.5590169943749475*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0])); 
  alphaOrdL = 0.9486832980505137*alphaL[1]+0.7071067811865475*alphaL[0]; 
  fUpOrd[2] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]+1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-1.161895003862225*fR[3]+1.161895003862225*fL[3]+0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])-1.5*fR[6]-(0.4472135954999579*(fR[5]-fL[5])-1.5*fL[6])+1.118033988749895*(fL[4]-fR[4])+1.161895003862225*(fR[3]+fL[3])-((-0.6708203932499369*(fL[2]-fR[2]))-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdL); 

  double fUp[3];
  fUp[0] = 0.07856742013183861*(5.0*fUpOrd[2]+8.0*fUpOrd[1]+5.0*fUpOrd[0]); 
  fUp[1] = 0.5270462766947298*(fUpOrd[2]-1.0*fUpOrd[0]); 
  fUp[2] = 0.3513641844631533*(fUpOrd[2]-2.0*fUpOrd[1]+fUpOrd[0]); 

  incr[0] = 0.5*(alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[1] = -0.8660254037844386*(alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[2] = 0.1*(4.47213595499958*alphaL[1]*fUp[2]+5.0*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[3] = -0.1*(7.745966692414834*alphaL[1]*fUp[2]+8.660254037844386*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[4] = 1.118033988749895*(alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[5] = 0.1*(5.0*alphaL[0]*fUp[2]+4.47213595499958*alphaL[1]*fUp[1]); 
  incr[6] = 0.03333333333333333*(30.0*alphaL[1]*fUp[2]+33.54101966249684*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[7] = -0.1*(8.660254037844387*alphaL[0]*fUp[2]+7.745966692414834*alphaL[1]*fUp[1]); 
  incr[8] = 0.5*(2.23606797749979*alphaL[0]*fUp[2]+2.0*alphaL[1]*fUp[1]); 

#endif 
  outR[0] += incr[0]*rdx2R; 
  outR[1] += incr[1]*rdx2R; 
  outR[2] += incr[2]*rdx2R; 
  outR[3] += incr[3]*rdx2R; 
  outR[4] += incr[4]*rdx2R; 
  outR[5] += incr[5]*rdx2R; 
  outR[6] += incr[6]*rdx2R; 
  outR[7] += incr[7]*rdx2R; 
  outR[8] += incr[8]*rdx2R; 

  outL[0] += -1.0*incr[0]*rdx2L; 
  outL[1] += incr[1]*rdx2L; 
  outL[2] += -1.0*incr[2]*rdx2L; 
  outL[3] += incr[3]*rdx2L; 
  outL[4] += -1.0*incr[4]*rdx2L; 
  outL[5] += -1.0*incr[5]*rdx2L; 
  outL[6] += -1.0*incr[6]*rdx2L; 
  outL[7] += incr[7]*rdx2L; 
  outL[8] += -1.0*incr[8]*rdx2L; 

  return std::abs(alphaSurfAvgL); 
} 
double GyrokineticSimpleHelicalSurf1x1vTensor_xR_P2_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
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

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;

  double hamilR[9]; 
  hamilR[0] = (0.3333333333333333*(3.0*rdvpar2SqR*(m_*wvparSqR+1.414213562373095*phi[0]*q_)+m_))/rdvpar2SqR; 
  hamilR[1] = 1.414213562373095*phi[1]*q_; 
  hamilR[2] = (1.154700538379252*m_*wvparR)/rdvpar2R; 
  hamilR[4] = 1.414213562373095*phi[2]*q_; 
  hamilR[5] = (0.2981423969999719*m_)/rdvpar2SqR; 

  double BstarZdBmagR[9]; 
  BstarZdBmagR[0] = 1.414213562373095*cmag[0]; 
  BstarZdBmagR[1] = 1.414213562373095*cmag[1]; 
  BstarZdBmagR[4] = 1.414213562373095*cmag[2]; 

  double alphaR[3]; 
  alphaR[0] = (0.3535533905932737*hamilR[2]*(3.872983346207417*BstarZdBmagR[4]-3.0*BstarZdBmagR[1]+1.732050807568877*BstarZdBmagR[0])*rdvpar2R)/m_; 
  alphaR[1] = (0.3535533905932737*(8.660254037844386*BstarZdBmagR[4]-6.708203932499369*BstarZdBmagR[1]+3.872983346207417*BstarZdBmagR[0])*hamilR[5]*rdvpar2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = (0.125*(3.872983346207417*hamilR[2]*BstarZdBmagR[4]+(1.732050807568877*BstarZdBmagR[0]-3.0*BstarZdBmagR[1])*hamilR[2])*rdvpar2R)/m_; 

  double incr[9]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgR>0) { 
  incr[0] = 0.08333333333333333*(9.48683298050514*(alphaR[1]*fL[6]+alphaR[0]*fL[4])+alphaR[1]*(7.348469228349534*fL[3]+4.242640687119286*fL[2])+alphaR[0]*(7.348469228349534*fL[1]+4.242640687119286*fL[0])); 
  incr[1] = -0.25*(5.477225575051662*(alphaR[1]*fL[6]+alphaR[0]*fL[4])+alphaR[1]*(4.242640687119286*fL[3]+2.449489742783178*fL[2])+alphaR[0]*(4.242640687119286*fL[1]+2.449489742783178*fL[0])); 
  incr[2] = 0.01666666666666667*(alphaR[1]*(42.42640687119286*fL[8]+32.86335345030997*fL[7])+47.43416490252569*alphaR[0]*fL[6]+alphaR[1]*(18.97366596101028*fL[5]+47.43416490252571*fL[4])+alphaR[0]*(36.74234614174767*fL[3]+21.21320343559643*fL[2])+alphaR[1]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[3] = -0.05*(alphaR[1]*(24.49489742783179*fL[8]+18.97366596101028*fL[7])+27.38612787525831*alphaR[0]*fL[6]+alphaR[1]*(10.95445115010332*fL[5]+27.38612787525831*fL[4])+alphaR[0]*(21.21320343559643*fL[3]+12.24744871391589*fL[2])+alphaR[1]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[4] = 0.08333333333333333*(21.21320343559643*alphaR[1]*fL[6]+21.21320343559643*alphaR[0]*fL[4]+alphaR[1]*(16.43167672515498*fL[3]+9.48683298050514*fL[2])+alphaR[0]*(16.43167672515498*fL[1]+9.48683298050514*fL[0])); 
  incr[5] = 0.01666666666666667*(alphaR[0]*(47.43416490252571*fL[8]+36.74234614174768*fL[7])+42.42640687119286*alphaR[1]*fL[6]+21.21320343559643*alphaR[0]*fL[5]+alphaR[1]*(32.86335345030997*fL[3]+18.97366596101028*fL[2])); 
  incr[6] = 0.01666666666666667*(alphaR[1]*(94.8683298050514*fL[8]+73.48469228349535*fL[7])+106.0660171779821*alphaR[0]*fL[6]+alphaR[1]*(42.42640687119286*fL[5]+106.0660171779822*fL[4])+alphaR[0]*(82.15838362577493*fL[3]+47.43416490252569*fL[2])+alphaR[1]*(82.15838362577493*fL[1]+47.43416490252569*fL[0])); 
  incr[7] = -0.05*(alphaR[0]*(27.38612787525831*fL[8]+21.21320343559643*fL[7])+24.49489742783179*alphaR[1]*fL[6]+12.24744871391589*alphaR[0]*fL[5]+alphaR[1]*(18.97366596101028*fL[3]+10.95445115010333*fL[2])); 
  incr[8] = 0.08333333333333333*(alphaR[0]*(21.21320343559643*fL[8]+16.43167672515499*fL[7])+18.97366596101028*alphaR[1]*fL[6]+9.48683298050514*alphaR[0]*fL[5]+alphaR[1]*(14.69693845669907*fL[3]+8.485281374238571*fL[2])); 
  } else { 
  incr[0] = 0.08333333333333333*(9.48683298050514*(alphaR[1]*fR[6]+alphaR[0]*fR[4])+alphaR[1]*(4.242640687119286*fR[2]-7.348469228349534*fR[3])+alphaR[0]*(4.242640687119286*fR[0]-7.348469228349534*fR[1])); 
  incr[1] = -0.25*(5.477225575051662*(alphaR[1]*fR[6]+alphaR[0]*fR[4])+alphaR[1]*(2.449489742783178*fR[2]-4.242640687119286*fR[3])+alphaR[0]*(2.449489742783178*fR[0]-4.242640687119286*fR[1])); 
  incr[2] = 0.01666666666666667*(alphaR[1]*(42.42640687119286*fR[8]-32.86335345030997*fR[7])+47.43416490252569*alphaR[0]*fR[6]+alphaR[1]*(18.97366596101028*fR[5]+47.43416490252571*fR[4])+alphaR[0]*(21.21320343559643*fR[2]-36.74234614174767*fR[3])+alphaR[1]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[3] = -0.05*(alphaR[1]*(24.49489742783179*fR[8]-18.97366596101028*fR[7])+27.38612787525831*alphaR[0]*fR[6]+alphaR[1]*(10.95445115010332*fR[5]+27.38612787525831*fR[4])+alphaR[0]*(12.24744871391589*fR[2]-21.21320343559643*fR[3])+alphaR[1]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[4] = 0.08333333333333333*(21.21320343559643*alphaR[1]*fR[6]+21.21320343559643*alphaR[0]*fR[4]+alphaR[1]*(9.48683298050514*fR[2]-16.43167672515498*fR[3])+alphaR[0]*(9.48683298050514*fR[0]-16.43167672515498*fR[1])); 
  incr[5] = 0.01666666666666667*(alphaR[0]*(47.43416490252571*fR[8]-36.74234614174768*fR[7])+42.42640687119286*alphaR[1]*fR[6]+21.21320343559643*alphaR[0]*fR[5]+alphaR[1]*(18.97366596101028*fR[2]-32.86335345030997*fR[3])); 
  incr[6] = 0.01666666666666667*(alphaR[1]*(94.8683298050514*fR[8]-73.48469228349535*fR[7])+106.0660171779821*alphaR[0]*fR[6]+alphaR[1]*(42.42640687119286*fR[5]+106.0660171779822*fR[4])+alphaR[0]*(47.43416490252569*fR[2]-82.15838362577493*fR[3])+alphaR[1]*(47.43416490252569*fR[0]-82.15838362577493*fR[1])); 
  incr[7] = -0.05*(alphaR[0]*(27.38612787525831*fR[8]-21.21320343559643*fR[7])+24.49489742783179*alphaR[1]*fR[6]+12.24744871391589*alphaR[0]*fR[5]+alphaR[1]*(10.95445115010333*fR[2]-18.97366596101028*fR[3])); 
  incr[8] = 0.08333333333333333*(alphaR[0]*(21.21320343559643*fR[8]-16.43167672515499*fR[7])+18.97366596101028*alphaR[1]*fR[6]+9.48683298050514*alphaR[0]*fR[5]+alphaR[1]*(8.485281374238571*fR[2]-14.69693845669907*fR[3])); 
  }
#elif upwindType == QUAD 
  double alphaOrdR;
  double fUpOrd[3];
  alphaOrdR = 0.7071067811865475*alphaR[0]-0.9486832980505137*alphaR[1]; 
  fUpOrd[0] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]-1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])+1.161895003862225*fR[3]-1.161895003862225*fL[3]-0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])+1.5*fR[6]-(1.5*fL[6]+0.4472135954999579*(fR[5]-fL[5]))+1.118033988749895*(fL[4]-fR[4])-1.161895003862225*(fR[3]+fL[3])-(0.6708203932499369*(fL[2]-fR[2])-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdR); 
  alphaOrdR = 0.7071067811865475*alphaR[0]; 
  fUpOrd[1] = 0.5*((1.25*fR[8]-1.25*fL[8]-0.9682458365518543*(fR[7]+fL[7])+0.5590169943749475*fR[5]-0.5590169943749475*fL[5]-1.118033988749895*fR[4]+1.118033988749895*fL[4]+0.8660254037844386*(fR[1]+fL[1])-0.5*fR[0]+0.5*fL[0])*sgn(alphaOrdR)-1.25*(fR[8]+fL[8])+0.9682458365518543*fR[7]-0.9682458365518543*fL[7]-0.5590169943749475*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0])); 
  alphaOrdR = 0.9486832980505137*alphaR[1]+0.7071067811865475*alphaR[0]; 
  fUpOrd[2] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]+1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-1.161895003862225*fR[3]+1.161895003862225*fL[3]+0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])-1.5*fR[6]-(0.4472135954999579*(fR[5]-fL[5])-1.5*fL[6])+1.118033988749895*(fL[4]-fR[4])+1.161895003862225*(fR[3]+fL[3])-((-0.6708203932499369*(fL[2]-fR[2]))-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdR); 

  double fUp[3];
  fUp[0] = 0.07856742013183861*(5.0*fUpOrd[2]+8.0*fUpOrd[1]+5.0*fUpOrd[0]); 
  fUp[1] = 0.5270462766947298*(fUpOrd[2]-1.0*fUpOrd[0]); 
  fUp[2] = 0.3513641844631533*(fUpOrd[2]-2.0*fUpOrd[1]+fUpOrd[0]); 

  incr[0] = 0.5*(alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[1] = -0.8660254037844386*(alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[2] = 0.1*(4.47213595499958*alphaR[1]*fUp[2]+5.0*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[3] = -0.1*(7.745966692414834*alphaR[1]*fUp[2]+8.660254037844386*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[4] = 1.118033988749895*(alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[5] = 0.1*(5.0*alphaR[0]*fUp[2]+4.47213595499958*alphaR[1]*fUp[1]); 
  incr[6] = 0.03333333333333333*(30.0*alphaR[1]*fUp[2]+33.54101966249684*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[7] = -0.1*(8.660254037844387*alphaR[0]*fUp[2]+7.745966692414834*alphaR[1]*fUp[1]); 
  incr[8] = 0.5*(2.23606797749979*alphaR[0]*fUp[2]+2.0*alphaR[1]*fUp[1]); 

#endif 
  outR[0] += incr[0]*rdx2R; 
  outR[1] += incr[1]*rdx2R; 
  outR[2] += incr[2]*rdx2R; 
  outR[3] += incr[3]*rdx2R; 
  outR[4] += incr[4]*rdx2R; 
  outR[5] += incr[5]*rdx2R; 
  outR[6] += incr[6]*rdx2R; 
  outR[7] += incr[7]*rdx2R; 
  outR[8] += incr[8]*rdx2R; 

  outL[0] += -1.0*incr[0]*rdx2L; 
  outL[1] += incr[1]*rdx2L; 
  outL[2] += -1.0*incr[2]*rdx2L; 
  outL[3] += incr[3]*rdx2L; 
  outL[4] += -1.0*incr[4]*rdx2L; 
  outL[5] += -1.0*incr[5]*rdx2L; 
  outL[6] += -1.0*incr[6]*rdx2L; 
  outL[7] += incr[7]*rdx2L; 
  outL[8] += -1.0*incr[8]*rdx2L; 

  return std::abs(alphaSurfAvgR); 
} 
double GyrokineticSimpleHelicalSurf1x1vTensor_vpar_P2_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *bmagInv, const double *cmag, const double *BdriftX, const double *BdriftY, const double *phi, const double *fL, const double *fR, double *outL, double *outR) 
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

  double wxSqL = wL[0]*wL[0];
  double wxSqR = wR[0]*wR[0];
  double rdx2SqL = rdx2L*rdx2L;
  double rdx2SqR = rdx2R*rdx2R;
  double wvparSqL = wL[1]*wL[1];
  double wvparSqR = wR[1]*wR[1];
  double rdvpar2SqL = rdvpar2L*rdvpar2L;
  double rdvpar2SqR = rdvpar2R*rdvpar2R;

  double hamilR[9]; 
  hamilR[0] = (0.3333333333333333*(3.0*rdvpar2SqR*(m_*wvparSqR+1.414213562373095*phi[0]*q_)+m_))/rdvpar2SqR; 
  hamilR[1] = 1.414213562373095*phi[1]*q_; 
  hamilR[2] = (1.154700538379252*m_*wvparR)/rdvpar2R; 
  hamilR[4] = 1.414213562373095*phi[2]*q_; 
  hamilR[5] = (0.2981423969999719*m_)/rdvpar2SqR; 

  double BstarZdBmagR[9]; 
  BstarZdBmagR[0] = 1.414213562373095*cmag[0]; 
  BstarZdBmagR[1] = 1.414213562373095*cmag[1]; 
  BstarZdBmagR[4] = 1.414213562373095*cmag[2]; 

  double alphaR[3]; 
  alphaR[0] = -(0.3535533905932737*(3.872983346207417*BstarZdBmagR[1]*hamilR[4]+1.732050807568877*BstarZdBmagR[0]*hamilR[1])*rdx2R)/m_; 
  alphaR[1] = -(0.3535533905932737*((3.464101615137754*BstarZdBmagR[4]+3.872983346207417*BstarZdBmagR[0])*hamilR[4]+1.732050807568877*BstarZdBmagR[1]*hamilR[1])*rdx2R)/m_; 
  alphaR[2] = -(0.3535533905932737*(3.464101615137754*BstarZdBmagR[1]*hamilR[4]+1.732050807568877*hamilR[1]*BstarZdBmagR[4])*rdx2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.125*(3.872983346207417*BstarZdBmagR[1]*hamilR[4]+1.732050807568877*BstarZdBmagR[0]*hamilR[1])*rdx2R)/m_; 

  double incr[9]; 
  double amax = amax_in; 

  double fAvg[3]; 
  fAvg[0] = 0.7071067811865475*(2.23606797749979*(fR[5]+fL[5])+1.732050807568877*(fL[2]-1.0*fR[2])+fR[0]+fL[0]); 
  fAvg[1] = 0.2357022603955158*(1.732050807568877*(3.872983346207417*(fR[7]+fL[7])+3.0*(fL[3]-1.0*fR[3]))+3.0*(fR[1]+fL[1])); 
  fAvg[2] = 0.1414213562373095*(2.23606797749979*(5.0*(fR[8]+fL[8])+3.872983346207417*(fL[6]-1.0*fR[6]))+5.0*(fR[4]+fL[4])); 

  double Ghat[3]; 
  Ghat[0] = -0.25*((3.16227766016838*fR[5]-3.16227766016838*fL[5]-2.449489742783178*(fR[2]+fL[2])+1.414213562373095*fR[0]-1.414213562373095*fL[0])*amax-1.414213562373095*(alphaR[2]*fAvg[2]+alphaR[1]*fAvg[1]+alphaR[0]*fAvg[0])); 
  Ghat[1] = -0.01666666666666667*((47.43416490252569*fR[7]-47.43416490252569*fL[7]-36.74234614174767*(fR[3]+fL[3])+21.21320343559643*fR[1]-21.21320343559643*fL[1])*amax-18.97366596101028*(alphaR[1]*fAvg[2]+fAvg[1]*alphaR[2])-21.21320343559643*(alphaR[0]*fAvg[1]+fAvg[0]*alphaR[1])); 
  Ghat[2] = -0.007142857142857143*((110.6797181058933*fR[8]-110.6797181058933*fL[8]-85.73214099741125*(fR[6]+fL[6])+49.49747468305833*fR[4]-49.49747468305833*fL[4])*amax+((-31.62277660168381*alphaR[2])-49.49747468305833*alphaR[0])*fAvg[2]-49.49747468305833*fAvg[0]*alphaR[2]-44.27188724235732*alphaR[1]*fAvg[1]); 

  incr[0] = 0.7071067811865475*Ghat[0]; 
  incr[1] = 0.7071067811865475*Ghat[1]; 
  incr[2] = -1.224744871391589*Ghat[0]; 
  incr[3] = -1.224744871391589*Ghat[1]; 
  incr[4] = 0.7071067811865475*Ghat[2]; 
  incr[5] = 1.58113883008419*Ghat[0]; 
  incr[6] = -1.224744871391589*Ghat[2]; 
  incr[7] = 1.58113883008419*Ghat[1]; 
  incr[8] = 1.58113883008419*Ghat[2]; 

  outR[0] += incr[0]*rdvpar2R; 
  outR[1] += incr[1]*rdvpar2R; 
  outR[2] += incr[2]*rdvpar2R; 
  outR[3] += incr[3]*rdvpar2R; 
  outR[4] += incr[4]*rdvpar2R; 
  outR[5] += incr[5]*rdvpar2R; 
  outR[6] += incr[6]*rdvpar2R; 
  outR[7] += incr[7]*rdvpar2R; 
  outR[8] += incr[8]*rdvpar2R; 

  outL[0] += -1.0*incr[0]*rdvpar2L; 
  outL[1] += -1.0*incr[1]*rdvpar2L; 
  outL[2] += incr[2]*rdvpar2L; 
  outL[3] += incr[3]*rdvpar2L; 
  outL[4] += -1.0*incr[4]*rdvpar2L; 
  outL[5] += -1.0*incr[5]*rdvpar2L; 
  outL[6] += incr[6]*rdvpar2L; 
  outL[7] += -1.0*incr[7]*rdvpar2L; 
  outL[8] += -1.0*incr[8]*rdvpar2L; 
return std::abs(alphaSurfAvgR); 
} 
