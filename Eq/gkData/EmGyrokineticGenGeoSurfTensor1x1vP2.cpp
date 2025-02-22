#include <GyrokineticModDecl.h>
double EmGyrokineticGenGeoSurf1x1vTensor_xL_P2_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagL[0] = 0.7071067811865475*jacobTotInv[0]*(1.732050807568877*b_y[0]*Apar[1]*rdx2L+1.414213562373095*cmag[0]); 
  BstarZdBmagL[1] = 2.738612787525831*b_y[0]*jacobTotInv[0]*Apar[2]*rdx2L; 

  double alphaL[3]; 
  alphaL[0] = (0.1767766952966368*(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2]*rdvpar2L)/m_; 
  alphaL[1] = (0.1767766952966368*(6.708203932499369*BstarZdBmagL[1]+3.872983346207417*BstarZdBmagL[0])*hamilL[5]*rdvpar2L)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgL = (0.0625*(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2]*rdvpar2L)/m_; 

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
double EmGyrokineticGenGeoSurf1x1vTensor_xR_P2_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagR[0] = 0.7071067811865475*jacobTotInv[0]*(1.732050807568877*b_y[0]*Apar[1]*rdx2R+1.414213562373095*cmag[0]); 
  BstarZdBmagR[1] = 2.738612787525831*b_y[0]*jacobTotInv[0]*Apar[2]*rdx2R; 

  double BstarZdBmagL[9]; 
  BstarZdBmagL[0] = -0.7071067811865475*jacobTotInv[0]*(1.732050807568877*b_y[0]*AparL[1]*rdx2R-1.414213562373095*cmag[0]); 
  BstarZdBmagL[1] = 2.738612787525831*b_y[0]*jacobTotInv[0]*AparL[2]*rdx2R; 

  double alphaR[3]; 
  alphaR[0] = -(0.1767766952966368*(3.0*(BstarZdBmagR[1]+BstarZdBmagL[1])-1.732050807568877*(BstarZdBmagR[0]+BstarZdBmagL[0]))*hamilR[2]*rdvpar2R)/m_; 
  alphaR[1] = -(0.1767766952966368*(6.708203932499369*(BstarZdBmagR[1]+BstarZdBmagL[1])-3.872983346207417*(BstarZdBmagR[0]+BstarZdBmagL[0]))*hamilR[5]*rdvpar2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.0625*(3.0*BstarZdBmagR[1]+3.0*BstarZdBmagL[1]-1.732050807568877*BstarZdBmagR[0]-1.732050807568877*BstarZdBmagL[0])*hamilR[2]*rdvpar2R)/m_; 

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
double EmGyrokineticGenGeoSurf1x1vTensor_vpar_P2_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagR[0] = 0.7071067811865475*jacobTotInv[0]*(1.732050807568877*b_y[0]*Apar[1]*rdx2R+1.414213562373095*cmag[0]); 
  BstarZdBmagR[1] = 2.738612787525831*b_y[0]*jacobTotInv[0]*Apar[2]*rdx2R; 

  double alphaR[3]; 
  alphaR[0] = -(0.3535533905932737*((3.872983346207417*BstarZdBmagR[1]*hamilR[4]+1.732050807568877*BstarZdBmagR[0]*hamilR[1])*rdx2R+2.828427124746191*dApardt[0]*q_))/m_; 
  alphaR[1] = -(0.3535533905932737*((3.872983346207417*BstarZdBmagR[0]*hamilR[4]+1.732050807568877*BstarZdBmagR[1]*hamilR[1])*rdx2R+2.828427124746191*dApardt[1]*q_))/m_; 
  alphaR[2] = -(0.7071067811865475*(1.732050807568877*BstarZdBmagR[1]*hamilR[4]*rdx2R+1.414213562373095*dApardt[2]*q_))/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.125*((3.872983346207417*BstarZdBmagR[1]*hamilR[4]+1.732050807568877*BstarZdBmagR[0]*hamilR[1])*rdx2R+2.828427124746191*dApardt[0]*q_))/m_; 

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
double EmGyrokineticGenGeoSurf1x1vTensor_xL_P2_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagL[0] = (0.5*(3.464101615137754*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2L*wvparL+q_*(2.449489742783178*(3.0*(Apar[1]*b_y[2]+b_y[1]*Apar[2])*jacobTotInv[2]+(4.0*jacobTotInv[1]*Apar[2]+2.23606797749979*(Apar[0]*jacobTotInv[1]+jacobTotInv[0]*Apar[1]))*b_y[2]+2.23606797749979*(b_y[0]*jacobTotInv[1]+jacobTotInv[0]*b_y[1])*Apar[2]+2.0*Apar[1]*b_y[1]*jacobTotInv[1]+jacobTotInv[0]*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*rdx2L+2.0*(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0]))))/q_; 
  BstarZdBmagL[1] = (0.01428571428571429*(24.24871130596428*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2L*wvparL+q_*(2.449489742783178*(2.0*((122.9837387624885*Apar[2]+35.0*Apar[0])*b_y[2]+7.0*(5.0*b_y[0]*Apar[2]+4.47213595499958*Apar[1]*b_y[1]))*jacobTotInv[2]+7.0*((20.0*jacobTotInv[0]*Apar[2]+2.23606797749979*(11.0*Apar[1]*jacobTotInv[1]+5.0*Apar[0]*jacobTotInv[0]))*b_y[2]+2.23606797749979*(11.0*b_y[1]*jacobTotInv[1]+5.0*b_y[0]*jacobTotInv[0])*Apar[2]+5.0*((Apar[0]*b_y[1]+b_y[0]*Apar[1])*jacobTotInv[1]+2.0*jacobTotInv[0]*Apar[1]*b_y[1])))*rdx2L+14.0*(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1])))))/q_; 
  BstarZdBmagL[2] = ((2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2L)/(q_*rdvpar2L); 
  BstarZdBmagL[3] = ((b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2L)/(q_*rdvpar2L); 
  BstarZdBmagL[4] = (0.01428571428571429*(121.2435565298214*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2L*wvparL+q_*(2.449489742783178*((145.3444185374863*(Apar[1]*b_y[2]+b_y[1]*Apar[2])+35.0*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*jacobTotInv[2]+(245.9674775249769*jacobTotInv[1]*Apar[2]+35.0*(2.0*Apar[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*Apar[1]))*b_y[2]+7.0*(5.0*(2.0*b_y[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*b_y[1])*Apar[2]+8.94427190999916*Apar[1]*b_y[1]*jacobTotInv[1]))*rdx2L+2.0*((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1])))))/q_; 
  BstarZdBmagL[6] = (1.0*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2L)/(q_*rdvpar2L); 

  double alphaL[3]; 
  alphaL[0] = (0.1767766952966368*(hamilL[5]*(8.660254037844387*BstarZdBmagL[6]+6.708203932499369*BstarZdBmagL[3]+3.872983346207417*BstarZdBmagL[2])+hamilL[2]*(3.872983346207417*BstarZdBmagL[4]+3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0]))*rdvpar2L)/m_; 
  alphaL[1] = (0.1767766952966368*(3.872983346207417*hamilL[2]*BstarZdBmagL[6]+(8.660254037844386*BstarZdBmagL[4]+6.708203932499369*BstarZdBmagL[1]+3.872983346207417*BstarZdBmagL[0])*hamilL[5]+hamilL[2]*(3.0*BstarZdBmagL[3]+1.732050807568877*BstarZdBmagL[2]))*rdvpar2L)/m_; 
  alphaL[2] = (0.3535533905932737*hamilL[5]*(3.872983346207417*BstarZdBmagL[6]+3.0*BstarZdBmagL[3]+1.732050807568877*BstarZdBmagL[2])*rdvpar2L)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgL = (0.0625*(8.660254037844387*hamilL[5]*BstarZdBmagL[6]+(6.708203932499369*BstarZdBmagL[3]+3.872983346207417*BstarZdBmagL[2])*hamilL[5]+3.872983346207417*hamilL[2]*BstarZdBmagL[4]+(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2])*rdvpar2L)/m_; 

  double incr[9]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgL>0) { 
  incr[0] = 0.01666666666666667*(alphaL[2]*(47.43416490252571*fL[8]+36.74234614174768*fL[7])+47.43416490252569*alphaL[1]*fL[6]+21.21320343559643*alphaL[2]*fL[5]+47.43416490252571*alphaL[0]*fL[4]+alphaL[1]*(36.74234614174767*fL[3]+21.21320343559643*fL[2])+alphaL[0]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[1] = -0.05*(alphaL[2]*(27.38612787525831*fL[8]+21.21320343559643*fL[7])+27.38612787525831*alphaL[1]*fL[6]+12.24744871391589*alphaL[2]*fL[5]+27.38612787525831*alphaL[0]*fL[4]+alphaL[1]*(21.21320343559643*fL[3]+12.24744871391589*fL[2])+alphaL[0]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[2] = 0.01666666666666667*(alphaL[1]*(42.42640687119286*fL[8]+32.86335345030997*fL[7])+(42.42640687119286*alphaL[2]+47.43416490252569*alphaL[0])*fL[6]+alphaL[1]*(18.97366596101028*fL[5]+47.43416490252571*fL[4])+(32.86335345030997*alphaL[2]+36.74234614174767*alphaL[0])*fL[3]+(18.97366596101028*alphaL[2]+21.21320343559643*alphaL[0])*fL[2]+alphaL[1]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[3] = -0.05*(alphaL[1]*(24.49489742783179*fL[8]+18.97366596101028*fL[7])+(24.49489742783179*alphaL[2]+27.38612787525831*alphaL[0])*fL[6]+alphaL[1]*(10.95445115010332*fL[5]+27.38612787525831*fL[4])+(18.97366596101028*alphaL[2]+21.21320343559643*alphaL[0])*fL[3]+(10.95445115010332*alphaL[2]+12.24744871391589*alphaL[0])*fL[2]+alphaL[1]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[4] = 0.08333333333333333*(alphaL[2]*(21.21320343559643*fL[8]+16.43167672515499*fL[7])+21.21320343559643*alphaL[1]*fL[6]+9.48683298050514*alphaL[2]*fL[5]+21.21320343559643*alphaL[0]*fL[4]+alphaL[1]*(16.43167672515498*fL[3]+9.48683298050514*fL[2])+alphaL[0]*(16.43167672515498*fL[1]+9.48683298050514*fL[0])); 
  incr[5] = 0.002380952380952381*((212.1320343559643*alphaL[2]+332.0391543176799*alphaL[0])*fL[8]+(164.3167672515499*alphaL[2]+257.1964229922337*alphaL[0])*fL[7]+296.98484809835*alphaL[1]*fL[6]+(94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fL[5]+332.0391543176799*alphaL[2]*fL[4]+alphaL[1]*(230.0434741521698*fL[3]+132.815661727072*fL[2])+(257.1964229922337*fL[1]+148.492424049175*fL[0])*alphaL[2]); 
  incr[6] = 0.01666666666666667*(alphaL[1]*(94.8683298050514*fL[8]+73.48469228349535*fL[7])+(94.86832980505142*alphaL[2]+106.0660171779821*alphaL[0])*fL[6]+alphaL[1]*(42.42640687119286*fL[5]+106.0660171779822*fL[4])+(73.48469228349536*alphaL[2]+82.15838362577493*alphaL[0])*fL[3]+(42.42640687119286*alphaL[2]+47.43416490252569*alphaL[0])*fL[2]+alphaL[1]*(82.15838362577493*fL[1]+47.43416490252569*fL[0])); 
  incr[7] = -0.007142857142857143*((122.474487139159*alphaL[2]+191.7028951268082*alphaL[0])*fL[8]+(94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fL[7]+171.4642819948225*alphaL[1]*fL[6]+(54.77225575051663*alphaL[2]+85.73214099741125*alphaL[0])*fL[5]+191.7028951268082*alphaL[2]*fL[4]+alphaL[1]*(132.815661727072*fL[3]+76.68115805072327*fL[2])+(148.492424049175*fL[1]+85.73214099741125*fL[0])*alphaL[2]); 
  incr[8] = 0.0119047619047619*((94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fL[8]+(73.48469228349536*alphaL[2]+115.0217370760849*alphaL[0])*fL[7]+132.815661727072*alphaL[1]*fL[6]+(42.42640687119286*alphaL[2]+66.40783086353598*alphaL[0])*fL[5]+148.492424049175*alphaL[2]*fL[4]+alphaL[1]*(102.8785691968935*fL[3]+59.39696961967*fL[2])+(115.0217370760849*fL[1]+66.40783086353598*fL[0])*alphaL[2]); 
  } else { 
  incr[0] = 0.01666666666666667*(alphaL[2]*(47.43416490252571*fR[8]-36.74234614174768*fR[7])+47.43416490252569*alphaL[1]*fR[6]+21.21320343559643*alphaL[2]*fR[5]+47.43416490252571*alphaL[0]*fR[4]+alphaL[1]*(21.21320343559643*fR[2]-36.74234614174767*fR[3])+alphaL[0]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[1] = -0.05*(alphaL[2]*(27.38612787525831*fR[8]-21.21320343559643*fR[7])+27.38612787525831*alphaL[1]*fR[6]+12.24744871391589*alphaL[2]*fR[5]+27.38612787525831*alphaL[0]*fR[4]+alphaL[1]*(12.24744871391589*fR[2]-21.21320343559643*fR[3])+alphaL[0]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[2] = 0.01666666666666667*(alphaL[1]*(42.42640687119286*fR[8]-32.86335345030997*fR[7])+(42.42640687119286*alphaL[2]+47.43416490252569*alphaL[0])*fR[6]+alphaL[1]*(18.97366596101028*fR[5]+47.43416490252571*fR[4])+((-32.86335345030997*alphaL[2])-36.74234614174767*alphaL[0])*fR[3]+(18.97366596101028*alphaL[2]+21.21320343559643*alphaL[0])*fR[2]+alphaL[1]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[3] = -0.05*(alphaL[1]*(24.49489742783179*fR[8]-18.97366596101028*fR[7])+(24.49489742783179*alphaL[2]+27.38612787525831*alphaL[0])*fR[6]+alphaL[1]*(10.95445115010332*fR[5]+27.38612787525831*fR[4])+((-18.97366596101028*alphaL[2])-21.21320343559643*alphaL[0])*fR[3]+(10.95445115010332*alphaL[2]+12.24744871391589*alphaL[0])*fR[2]+alphaL[1]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[4] = 0.08333333333333333*(alphaL[2]*(21.21320343559643*fR[8]-16.43167672515499*fR[7])+21.21320343559643*alphaL[1]*fR[6]+9.48683298050514*alphaL[2]*fR[5]+21.21320343559643*alphaL[0]*fR[4]+alphaL[1]*(9.48683298050514*fR[2]-16.43167672515498*fR[3])+alphaL[0]*(9.48683298050514*fR[0]-16.43167672515498*fR[1])); 
  incr[5] = 0.002380952380952381*((212.1320343559643*alphaL[2]+332.0391543176799*alphaL[0])*fR[8]+((-164.3167672515499*alphaL[2])-257.1964229922337*alphaL[0])*fR[7]+296.98484809835*alphaL[1]*fR[6]+(94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fR[5]+332.0391543176799*alphaL[2]*fR[4]+alphaL[1]*(132.815661727072*fR[2]-230.0434741521698*fR[3])+(148.492424049175*fR[0]-257.1964229922337*fR[1])*alphaL[2]); 
  incr[6] = 0.01666666666666667*(alphaL[1]*(94.8683298050514*fR[8]-73.48469228349535*fR[7])+(94.86832980505142*alphaL[2]+106.0660171779821*alphaL[0])*fR[6]+alphaL[1]*(42.42640687119286*fR[5]+106.0660171779822*fR[4])+((-73.48469228349536*alphaL[2])-82.15838362577493*alphaL[0])*fR[3]+(42.42640687119286*alphaL[2]+47.43416490252569*alphaL[0])*fR[2]+alphaL[1]*(47.43416490252569*fR[0]-82.15838362577493*fR[1])); 
  incr[7] = -0.007142857142857143*((122.474487139159*alphaL[2]+191.7028951268082*alphaL[0])*fR[8]+((-94.86832980505142*alphaL[2])-148.492424049175*alphaL[0])*fR[7]+171.4642819948225*alphaL[1]*fR[6]+(54.77225575051663*alphaL[2]+85.73214099741125*alphaL[0])*fR[5]+191.7028951268082*alphaL[2]*fR[4]+alphaL[1]*(76.68115805072327*fR[2]-132.815661727072*fR[3])+(85.73214099741125*fR[0]-148.492424049175*fR[1])*alphaL[2]); 
  incr[8] = 0.0119047619047619*((94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fR[8]+((-73.48469228349536*alphaL[2])-115.0217370760849*alphaL[0])*fR[7]+132.815661727072*alphaL[1]*fR[6]+(42.42640687119286*alphaL[2]+66.40783086353598*alphaL[0])*fR[5]+148.492424049175*alphaL[2]*fR[4]+alphaL[1]*(59.39696961967*fR[2]-102.8785691968935*fR[3])+(66.40783086353598*fR[0]-115.0217370760849*fR[1])*alphaL[2]); 
  }
#elif upwindType == QUAD 
  double alphaOrdL;
  double fUpOrd[3];
  alphaOrdL = 0.6324555320336759*alphaL[2]-0.9486832980505137*alphaL[1]+0.7071067811865475*alphaL[0]; 
  fUpOrd[0] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]-1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])+1.161895003862225*fR[3]-1.161895003862225*fL[3]-0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])+1.5*fR[6]-(1.5*fL[6]+0.4472135954999579*(fR[5]-fL[5]))+1.118033988749895*(fL[4]-fR[4])-1.161895003862225*(fR[3]+fL[3])-(0.6708203932499369*(fL[2]-fR[2])-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdL); 
  alphaOrdL = 0.7071067811865475*alphaL[0]-0.7905694150420947*alphaL[2]; 
  fUpOrd[1] = 0.5*((1.25*fR[8]-1.25*fL[8]-0.9682458365518543*(fR[7]+fL[7])+0.5590169943749475*fR[5]-0.5590169943749475*fL[5]-1.118033988749895*fR[4]+1.118033988749895*fL[4]+0.8660254037844386*(fR[1]+fL[1])-0.5*fR[0]+0.5*fL[0])*sgn(alphaOrdL)-1.25*(fR[8]+fL[8])+0.9682458365518543*fR[7]-0.9682458365518543*fL[7]-0.5590169943749475*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0])); 
  alphaOrdL = 0.6324555320336759*alphaL[2]+0.9486832980505137*alphaL[1]+0.7071067811865475*alphaL[0]; 
  fUpOrd[2] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]+1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-1.161895003862225*fR[3]+1.161895003862225*fL[3]+0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])-1.5*fR[6]-(0.4472135954999579*(fR[5]-fL[5])-1.5*fL[6])+1.118033988749895*(fL[4]-fR[4])+1.161895003862225*(fR[3]+fL[3])-((-0.6708203932499369*(fL[2]-fR[2]))-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdL); 

  double fUp[3];
  fUp[0] = 0.07856742013183861*(5.0*fUpOrd[2]+8.0*fUpOrd[1]+5.0*fUpOrd[0]); 
  fUp[1] = 0.5270462766947298*(fUpOrd[2]-1.0*fUpOrd[0]); 
  fUp[2] = 0.3513641844631533*(fUpOrd[2]-2.0*fUpOrd[1]+fUpOrd[0]); 

  incr[0] = 0.5*(alphaL[2]*fUp[2]+alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[1] = -0.8660254037844386*(alphaL[2]*fUp[2]+alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[2] = 0.1*(4.47213595499958*(alphaL[1]*fUp[2]+fUp[1]*alphaL[2])+5.0*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[3] = -0.1*(7.745966692414834*(alphaL[1]*fUp[2]+fUp[1]*alphaL[2])+8.660254037844386*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[4] = 1.118033988749895*(alphaL[2]*fUp[2]+alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[5] = 0.01428571428571429*((22.3606797749979*alphaL[2]+35.0*alphaL[0])*fUp[2]+35.0*fUp[0]*alphaL[2]+31.30495168499706*alphaL[1]*fUp[1]); 
  incr[6] = 0.03333333333333333*(30.0*(alphaL[1]*fUp[2]+fUp[1]*alphaL[2])+33.54101966249684*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[7] = -0.01428571428571429*((38.72983346207417*alphaL[2]+60.62177826491071*alphaL[0])*fUp[2]+60.62177826491071*fUp[0]*alphaL[2]+54.22176684690384*alphaL[1]*fUp[1]); 
  incr[8] = 0.07142857142857142*((10.0*alphaL[2]+15.65247584249853*alphaL[0])*fUp[2]+15.65247584249853*fUp[0]*alphaL[2]+14.0*alphaL[1]*fUp[1]); 

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
double EmGyrokineticGenGeoSurf1x1vTensor_xR_P2_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagR[0] = (0.5*(3.464101615137754*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(3.0*(Apar[1]*b_y[2]+b_y[1]*Apar[2])*jacobTotInv[2]+(4.0*jacobTotInv[1]*Apar[2]+2.23606797749979*(Apar[0]*jacobTotInv[1]+jacobTotInv[0]*Apar[1]))*b_y[2]+2.23606797749979*(b_y[0]*jacobTotInv[1]+jacobTotInv[0]*b_y[1])*Apar[2]+2.0*Apar[1]*b_y[1]*jacobTotInv[1]+jacobTotInv[0]*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*rdx2R+2.0*(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0]))))/q_; 
  BstarZdBmagR[1] = (0.01428571428571429*(24.24871130596428*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(2.0*((122.9837387624885*Apar[2]+35.0*Apar[0])*b_y[2]+7.0*(5.0*b_y[0]*Apar[2]+4.47213595499958*Apar[1]*b_y[1]))*jacobTotInv[2]+7.0*((20.0*jacobTotInv[0]*Apar[2]+2.23606797749979*(11.0*Apar[1]*jacobTotInv[1]+5.0*Apar[0]*jacobTotInv[0]))*b_y[2]+2.23606797749979*(11.0*b_y[1]*jacobTotInv[1]+5.0*b_y[0]*jacobTotInv[0])*Apar[2]+5.0*((Apar[0]*b_y[1]+b_y[0]*Apar[1])*jacobTotInv[1]+2.0*jacobTotInv[0]*Apar[1]*b_y[1])))*rdx2R+14.0*(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1])))))/q_; 
  BstarZdBmagR[2] = ((2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagR[3] = ((b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagR[4] = (0.01428571428571429*(121.2435565298214*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R*wvparR+q_*(2.449489742783178*((145.3444185374863*(Apar[1]*b_y[2]+b_y[1]*Apar[2])+35.0*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*jacobTotInv[2]+(245.9674775249769*jacobTotInv[1]*Apar[2]+35.0*(2.0*Apar[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*Apar[1]))*b_y[2]+7.0*(5.0*(2.0*b_y[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*b_y[1])*Apar[2]+8.94427190999916*Apar[1]*b_y[1]*jacobTotInv[1]))*rdx2R+2.0*((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1])))))/q_; 
  BstarZdBmagR[6] = (1.0*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R)/(q_*rdvpar2R); 

  double BstarZdBmagL[9]; 
  BstarZdBmagL[0] = (0.5*(3.464101615137754*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(3.0*(b_y[1]*AparL[2]-1.0*AparL[1]*b_y[2])*jacobTotInv[2]+(4.0*jacobTotInv[1]*AparL[2]+2.23606797749979*(AparL[0]*jacobTotInv[1]-1.0*jacobTotInv[0]*AparL[1]))*b_y[2]+2.23606797749979*(b_y[0]*jacobTotInv[1]+jacobTotInv[0]*b_y[1])*AparL[2]-2.0*AparL[1]*b_y[1]*jacobTotInv[1]+jacobTotInv[0]*(AparL[0]*b_y[1]-1.0*b_y[0]*AparL[1]))*rdx2R+2.0*(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0]))))/q_; 
  BstarZdBmagL[1] = (0.01428571428571429*(24.24871130596428*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(2.0*((122.9837387624885*AparL[2]+35.0*AparL[0])*b_y[2]+7.0*(5.0*b_y[0]*AparL[2]-4.47213595499958*AparL[1]*b_y[1]))*jacobTotInv[2]+7.0*((20.0*jacobTotInv[0]*AparL[2]+2.23606797749979*(5.0*AparL[0]*jacobTotInv[0]-11.0*AparL[1]*jacobTotInv[1]))*b_y[2]+2.23606797749979*(11.0*b_y[1]*jacobTotInv[1]+5.0*b_y[0]*jacobTotInv[0])*AparL[2]+5.0*((AparL[0]*b_y[1]-1.0*b_y[0]*AparL[1])*jacobTotInv[1]-2.0*jacobTotInv[0]*AparL[1]*b_y[1])))*rdx2R+14.0*(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1])))))/q_; 
  BstarZdBmagL[2] = ((2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagL[3] = ((b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagL[4] = (0.01428571428571429*(121.2435565298214*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R*wvparR+q_*(2.0*((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1]))-2.449489742783178*((145.3444185374863*(AparL[1]*b_y[2]-1.0*b_y[1]*AparL[2])+35.0*(b_y[0]*AparL[1]-1.0*AparL[0]*b_y[1]))*jacobTotInv[2]-1.0*(245.9674775249769*jacobTotInv[1]*AparL[2]+35.0*(2.0*AparL[0]*jacobTotInv[1]-3.0*jacobTotInv[0]*AparL[1]))*b_y[2]+7.0*(8.94427190999916*AparL[1]*b_y[1]*jacobTotInv[1]-5.0*(2.0*b_y[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*b_y[1])*AparL[2]))*rdx2R)))/q_; 
  BstarZdBmagL[6] = (1.0*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R)/(q_*rdvpar2R); 

  double alphaR[3]; 
  alphaR[0] = (0.1767766952966368*(hamilR[5]*(8.660254037844387*(BstarZdBmagR[6]+BstarZdBmagL[6])-6.708203932499369*(BstarZdBmagR[3]+BstarZdBmagL[3])+3.872983346207417*(BstarZdBmagR[2]+BstarZdBmagL[2]))+hamilR[2]*(3.872983346207417*(BstarZdBmagR[4]+BstarZdBmagL[4])-3.0*(BstarZdBmagR[1]+BstarZdBmagL[1])+1.732050807568877*(BstarZdBmagR[0]+BstarZdBmagL[0])))*rdvpar2R)/m_; 
  alphaR[1] = (0.1767766952966368*(3.872983346207417*hamilR[2]*(BstarZdBmagR[6]+BstarZdBmagL[6])+(8.660254037844386*(BstarZdBmagR[4]+BstarZdBmagL[4])-6.708203932499369*(BstarZdBmagR[1]+BstarZdBmagL[1])+3.872983346207417*(BstarZdBmagR[0]+BstarZdBmagL[0]))*hamilR[5]+hamilR[2]*(1.732050807568877*(BstarZdBmagR[2]+BstarZdBmagL[2])-3.0*(BstarZdBmagR[3]+BstarZdBmagL[3])))*rdvpar2R)/m_; 
  alphaR[2] = (0.3535533905932737*hamilR[5]*(3.872983346207417*(BstarZdBmagR[6]+BstarZdBmagL[6])-3.0*(BstarZdBmagR[3]+BstarZdBmagL[3])+1.732050807568877*(BstarZdBmagR[2]+BstarZdBmagL[2]))*rdvpar2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = (0.0625*(8.660254037844387*hamilR[5]*BstarZdBmagR[6]+8.660254037844387*hamilR[5]*BstarZdBmagL[6]+((-6.708203932499369*BstarZdBmagR[3])-6.708203932499369*BstarZdBmagL[3]+3.872983346207417*BstarZdBmagR[2]+3.872983346207417*BstarZdBmagL[2])*hamilR[5]+3.872983346207417*hamilR[2]*BstarZdBmagR[4]+3.872983346207417*hamilR[2]*BstarZdBmagL[4]+((-3.0*BstarZdBmagR[1])-3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagR[0]+1.732050807568877*BstarZdBmagL[0])*hamilR[2])*rdvpar2R)/m_; 

  double incr[9]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgR>0) { 
  incr[0] = 0.01666666666666667*(alphaR[2]*(47.43416490252571*fL[8]+36.74234614174768*fL[7])+47.43416490252569*alphaR[1]*fL[6]+21.21320343559643*alphaR[2]*fL[5]+47.43416490252571*alphaR[0]*fL[4]+alphaR[1]*(36.74234614174767*fL[3]+21.21320343559643*fL[2])+alphaR[0]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[1] = -0.05*(alphaR[2]*(27.38612787525831*fL[8]+21.21320343559643*fL[7])+27.38612787525831*alphaR[1]*fL[6]+12.24744871391589*alphaR[2]*fL[5]+27.38612787525831*alphaR[0]*fL[4]+alphaR[1]*(21.21320343559643*fL[3]+12.24744871391589*fL[2])+alphaR[0]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[2] = 0.01666666666666667*(alphaR[1]*(42.42640687119286*fL[8]+32.86335345030997*fL[7])+(42.42640687119286*alphaR[2]+47.43416490252569*alphaR[0])*fL[6]+alphaR[1]*(18.97366596101028*fL[5]+47.43416490252571*fL[4])+(32.86335345030997*alphaR[2]+36.74234614174767*alphaR[0])*fL[3]+(18.97366596101028*alphaR[2]+21.21320343559643*alphaR[0])*fL[2]+alphaR[1]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[3] = -0.05*(alphaR[1]*(24.49489742783179*fL[8]+18.97366596101028*fL[7])+(24.49489742783179*alphaR[2]+27.38612787525831*alphaR[0])*fL[6]+alphaR[1]*(10.95445115010332*fL[5]+27.38612787525831*fL[4])+(18.97366596101028*alphaR[2]+21.21320343559643*alphaR[0])*fL[3]+(10.95445115010332*alphaR[2]+12.24744871391589*alphaR[0])*fL[2]+alphaR[1]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[4] = 0.08333333333333333*(alphaR[2]*(21.21320343559643*fL[8]+16.43167672515499*fL[7])+21.21320343559643*alphaR[1]*fL[6]+9.48683298050514*alphaR[2]*fL[5]+21.21320343559643*alphaR[0]*fL[4]+alphaR[1]*(16.43167672515498*fL[3]+9.48683298050514*fL[2])+alphaR[0]*(16.43167672515498*fL[1]+9.48683298050514*fL[0])); 
  incr[5] = 0.002380952380952381*((212.1320343559643*alphaR[2]+332.0391543176799*alphaR[0])*fL[8]+(164.3167672515499*alphaR[2]+257.1964229922337*alphaR[0])*fL[7]+296.98484809835*alphaR[1]*fL[6]+(94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fL[5]+332.0391543176799*alphaR[2]*fL[4]+alphaR[1]*(230.0434741521698*fL[3]+132.815661727072*fL[2])+(257.1964229922337*fL[1]+148.492424049175*fL[0])*alphaR[2]); 
  incr[6] = 0.01666666666666667*(alphaR[1]*(94.8683298050514*fL[8]+73.48469228349535*fL[7])+(94.86832980505142*alphaR[2]+106.0660171779821*alphaR[0])*fL[6]+alphaR[1]*(42.42640687119286*fL[5]+106.0660171779822*fL[4])+(73.48469228349536*alphaR[2]+82.15838362577493*alphaR[0])*fL[3]+(42.42640687119286*alphaR[2]+47.43416490252569*alphaR[0])*fL[2]+alphaR[1]*(82.15838362577493*fL[1]+47.43416490252569*fL[0])); 
  incr[7] = -0.007142857142857143*((122.474487139159*alphaR[2]+191.7028951268082*alphaR[0])*fL[8]+(94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fL[7]+171.4642819948225*alphaR[1]*fL[6]+(54.77225575051663*alphaR[2]+85.73214099741125*alphaR[0])*fL[5]+191.7028951268082*alphaR[2]*fL[4]+alphaR[1]*(132.815661727072*fL[3]+76.68115805072327*fL[2])+(148.492424049175*fL[1]+85.73214099741125*fL[0])*alphaR[2]); 
  incr[8] = 0.0119047619047619*((94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fL[8]+(73.48469228349536*alphaR[2]+115.0217370760849*alphaR[0])*fL[7]+132.815661727072*alphaR[1]*fL[6]+(42.42640687119286*alphaR[2]+66.40783086353598*alphaR[0])*fL[5]+148.492424049175*alphaR[2]*fL[4]+alphaR[1]*(102.8785691968935*fL[3]+59.39696961967*fL[2])+(115.0217370760849*fL[1]+66.40783086353598*fL[0])*alphaR[2]); 
  } else { 
  incr[0] = 0.01666666666666667*(alphaR[2]*(47.43416490252571*fR[8]-36.74234614174768*fR[7])+47.43416490252569*alphaR[1]*fR[6]+21.21320343559643*alphaR[2]*fR[5]+47.43416490252571*alphaR[0]*fR[4]+alphaR[1]*(21.21320343559643*fR[2]-36.74234614174767*fR[3])+alphaR[0]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[1] = -0.05*(alphaR[2]*(27.38612787525831*fR[8]-21.21320343559643*fR[7])+27.38612787525831*alphaR[1]*fR[6]+12.24744871391589*alphaR[2]*fR[5]+27.38612787525831*alphaR[0]*fR[4]+alphaR[1]*(12.24744871391589*fR[2]-21.21320343559643*fR[3])+alphaR[0]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[2] = 0.01666666666666667*(alphaR[1]*(42.42640687119286*fR[8]-32.86335345030997*fR[7])+(42.42640687119286*alphaR[2]+47.43416490252569*alphaR[0])*fR[6]+alphaR[1]*(18.97366596101028*fR[5]+47.43416490252571*fR[4])+((-32.86335345030997*alphaR[2])-36.74234614174767*alphaR[0])*fR[3]+(18.97366596101028*alphaR[2]+21.21320343559643*alphaR[0])*fR[2]+alphaR[1]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[3] = -0.05*(alphaR[1]*(24.49489742783179*fR[8]-18.97366596101028*fR[7])+(24.49489742783179*alphaR[2]+27.38612787525831*alphaR[0])*fR[6]+alphaR[1]*(10.95445115010332*fR[5]+27.38612787525831*fR[4])+((-18.97366596101028*alphaR[2])-21.21320343559643*alphaR[0])*fR[3]+(10.95445115010332*alphaR[2]+12.24744871391589*alphaR[0])*fR[2]+alphaR[1]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[4] = 0.08333333333333333*(alphaR[2]*(21.21320343559643*fR[8]-16.43167672515499*fR[7])+21.21320343559643*alphaR[1]*fR[6]+9.48683298050514*alphaR[2]*fR[5]+21.21320343559643*alphaR[0]*fR[4]+alphaR[1]*(9.48683298050514*fR[2]-16.43167672515498*fR[3])+alphaR[0]*(9.48683298050514*fR[0]-16.43167672515498*fR[1])); 
  incr[5] = 0.002380952380952381*((212.1320343559643*alphaR[2]+332.0391543176799*alphaR[0])*fR[8]+((-164.3167672515499*alphaR[2])-257.1964229922337*alphaR[0])*fR[7]+296.98484809835*alphaR[1]*fR[6]+(94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fR[5]+332.0391543176799*alphaR[2]*fR[4]+alphaR[1]*(132.815661727072*fR[2]-230.0434741521698*fR[3])+(148.492424049175*fR[0]-257.1964229922337*fR[1])*alphaR[2]); 
  incr[6] = 0.01666666666666667*(alphaR[1]*(94.8683298050514*fR[8]-73.48469228349535*fR[7])+(94.86832980505142*alphaR[2]+106.0660171779821*alphaR[0])*fR[6]+alphaR[1]*(42.42640687119286*fR[5]+106.0660171779822*fR[4])+((-73.48469228349536*alphaR[2])-82.15838362577493*alphaR[0])*fR[3]+(42.42640687119286*alphaR[2]+47.43416490252569*alphaR[0])*fR[2]+alphaR[1]*(47.43416490252569*fR[0]-82.15838362577493*fR[1])); 
  incr[7] = -0.007142857142857143*((122.474487139159*alphaR[2]+191.7028951268082*alphaR[0])*fR[8]+((-94.86832980505142*alphaR[2])-148.492424049175*alphaR[0])*fR[7]+171.4642819948225*alphaR[1]*fR[6]+(54.77225575051663*alphaR[2]+85.73214099741125*alphaR[0])*fR[5]+191.7028951268082*alphaR[2]*fR[4]+alphaR[1]*(76.68115805072327*fR[2]-132.815661727072*fR[3])+(85.73214099741125*fR[0]-148.492424049175*fR[1])*alphaR[2]); 
  incr[8] = 0.0119047619047619*((94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fR[8]+((-73.48469228349536*alphaR[2])-115.0217370760849*alphaR[0])*fR[7]+132.815661727072*alphaR[1]*fR[6]+(42.42640687119286*alphaR[2]+66.40783086353598*alphaR[0])*fR[5]+148.492424049175*alphaR[2]*fR[4]+alphaR[1]*(59.39696961967*fR[2]-102.8785691968935*fR[3])+(66.40783086353598*fR[0]-115.0217370760849*fR[1])*alphaR[2]); 
  }
#elif upwindType == QUAD 
  double alphaOrdR;
  double fUpOrd[3];
  alphaOrdR = 0.6324555320336759*alphaR[2]-0.9486832980505137*alphaR[1]+0.7071067811865475*alphaR[0]; 
  fUpOrd[0] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]-1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])+1.161895003862225*fR[3]-1.161895003862225*fL[3]-0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])+1.5*fR[6]-(1.5*fL[6]+0.4472135954999579*(fR[5]-fL[5]))+1.118033988749895*(fL[4]-fR[4])-1.161895003862225*(fR[3]+fL[3])-(0.6708203932499369*(fL[2]-fR[2])-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdR); 
  alphaOrdR = 0.7071067811865475*alphaR[0]-0.7905694150420947*alphaR[2]; 
  fUpOrd[1] = 0.5*((1.25*fR[8]-1.25*fL[8]-0.9682458365518543*(fR[7]+fL[7])+0.5590169943749475*fR[5]-0.5590169943749475*fL[5]-1.118033988749895*fR[4]+1.118033988749895*fL[4]+0.8660254037844386*(fR[1]+fL[1])-0.5*fR[0]+0.5*fL[0])*sgn(alphaOrdR)-1.25*(fR[8]+fL[8])+0.9682458365518543*fR[7]-0.9682458365518543*fL[7]-0.5590169943749475*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0])); 
  alphaOrdR = 0.6324555320336759*alphaR[2]+0.9486832980505137*alphaR[1]+0.7071067811865475*alphaR[0]; 
  fUpOrd[2] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]+1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-1.161895003862225*fR[3]+1.161895003862225*fL[3]+0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])-1.5*fR[6]-(0.4472135954999579*(fR[5]-fL[5])-1.5*fL[6])+1.118033988749895*(fL[4]-fR[4])+1.161895003862225*(fR[3]+fL[3])-((-0.6708203932499369*(fL[2]-fR[2]))-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdR); 

  double fUp[3];
  fUp[0] = 0.07856742013183861*(5.0*fUpOrd[2]+8.0*fUpOrd[1]+5.0*fUpOrd[0]); 
  fUp[1] = 0.5270462766947298*(fUpOrd[2]-1.0*fUpOrd[0]); 
  fUp[2] = 0.3513641844631533*(fUpOrd[2]-2.0*fUpOrd[1]+fUpOrd[0]); 

  incr[0] = 0.5*(alphaR[2]*fUp[2]+alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[1] = -0.8660254037844386*(alphaR[2]*fUp[2]+alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[2] = 0.1*(4.47213595499958*(alphaR[1]*fUp[2]+fUp[1]*alphaR[2])+5.0*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[3] = -0.1*(7.745966692414834*(alphaR[1]*fUp[2]+fUp[1]*alphaR[2])+8.660254037844386*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[4] = 1.118033988749895*(alphaR[2]*fUp[2]+alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[5] = 0.01428571428571429*((22.3606797749979*alphaR[2]+35.0*alphaR[0])*fUp[2]+35.0*fUp[0]*alphaR[2]+31.30495168499706*alphaR[1]*fUp[1]); 
  incr[6] = 0.03333333333333333*(30.0*(alphaR[1]*fUp[2]+fUp[1]*alphaR[2])+33.54101966249684*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[7] = -0.01428571428571429*((38.72983346207417*alphaR[2]+60.62177826491071*alphaR[0])*fUp[2]+60.62177826491071*fUp[0]*alphaR[2]+54.22176684690384*alphaR[1]*fUp[1]); 
  incr[8] = 0.07142857142857142*((10.0*alphaR[2]+15.65247584249853*alphaR[0])*fUp[2]+15.65247584249853*fUp[0]*alphaR[2]+14.0*alphaR[1]*fUp[1]); 

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
double EmGyrokineticGenGeoSurf1x1vTensor_vpar_P2_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagR[0] = (0.5*(3.464101615137754*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(3.0*(Apar[1]*b_y[2]+b_y[1]*Apar[2])*jacobTotInv[2]+(4.0*jacobTotInv[1]*Apar[2]+2.23606797749979*(Apar[0]*jacobTotInv[1]+jacobTotInv[0]*Apar[1]))*b_y[2]+2.23606797749979*(b_y[0]*jacobTotInv[1]+jacobTotInv[0]*b_y[1])*Apar[2]+2.0*Apar[1]*b_y[1]*jacobTotInv[1]+jacobTotInv[0]*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*rdx2R+2.0*(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0]))))/q_; 
  BstarZdBmagR[1] = (0.01428571428571429*(24.24871130596428*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(2.0*((122.9837387624885*Apar[2]+35.0*Apar[0])*b_y[2]+7.0*(5.0*b_y[0]*Apar[2]+4.47213595499958*Apar[1]*b_y[1]))*jacobTotInv[2]+7.0*((20.0*jacobTotInv[0]*Apar[2]+2.23606797749979*(11.0*Apar[1]*jacobTotInv[1]+5.0*Apar[0]*jacobTotInv[0]))*b_y[2]+2.23606797749979*(11.0*b_y[1]*jacobTotInv[1]+5.0*b_y[0]*jacobTotInv[0])*Apar[2]+5.0*((Apar[0]*b_y[1]+b_y[0]*Apar[1])*jacobTotInv[1]+2.0*jacobTotInv[0]*Apar[1]*b_y[1])))*rdx2R+14.0*(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1])))))/q_; 
  BstarZdBmagR[2] = ((2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagR[3] = ((b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagR[4] = (0.01428571428571429*(121.2435565298214*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R*wvparR+q_*(2.449489742783178*((145.3444185374863*(Apar[1]*b_y[2]+b_y[1]*Apar[2])+35.0*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*jacobTotInv[2]+(245.9674775249769*jacobTotInv[1]*Apar[2]+35.0*(2.0*Apar[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*Apar[1]))*b_y[2]+7.0*(5.0*(2.0*b_y[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*b_y[1])*Apar[2]+8.94427190999916*Apar[1]*b_y[1]*jacobTotInv[1]))*rdx2R+2.0*((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1])))))/q_; 
  BstarZdBmagR[6] = (1.0*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R)/(q_*rdvpar2R); 

  double alphaR[3]; 
  alphaR[0] = (0.3535533905932737*(((6.708203932499369*BstarZdBmagR[3]-3.872983346207417*BstarZdBmagR[1])*hamilR[4]+hamilR[1]*(3.0*BstarZdBmagR[2]-1.732050807568877*BstarZdBmagR[0]))*rdx2R-2.828427124746191*dApardt[0]*q_))/m_; 
  alphaR[1] = (0.07071067811865474*((hamilR[4]*(30.0*BstarZdBmagR[6]-17.32050807568877*BstarZdBmagR[4]+33.54101966249685*BstarZdBmagR[2]-19.36491673103709*BstarZdBmagR[0])+hamilR[1]*(15.0*BstarZdBmagR[3]-8.660254037844386*BstarZdBmagR[1]))*rdx2R-14.14213562373095*dApardt[1]*q_))/m_; 
  alphaR[2] = (0.07071067811865474*((15.0*hamilR[1]*BstarZdBmagR[6]+(30.0*BstarZdBmagR[3]-17.32050807568877*BstarZdBmagR[1])*hamilR[4]-8.660254037844386*hamilR[1]*BstarZdBmagR[4])*rdx2R-14.14213562373095*dApardt[2]*q_))/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = (0.125*(((6.708203932499369*BstarZdBmagR[3]-3.872983346207417*BstarZdBmagR[1])*hamilR[4]+3.0*hamilR[1]*BstarZdBmagR[2]-1.732050807568877*BstarZdBmagR[0]*hamilR[1])*rdx2R-2.828427124746191*dApardt[0]*q_))/m_; 

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
double EmGyrokineticGenGeoSurf1x1vTensor_xL_P2_Bvarsz(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagL[0] = 0.7071067811865475*jacobTotInv[0]*(1.732050807568877*b_y[0]*Apar[1]*rdx2L+1.414213562373095*cmag[0]); 
  BstarZdBmagL[1] = 2.738612787525831*b_y[0]*jacobTotInv[0]*Apar[2]*rdx2L; 

  double alphaL[3]; 
  alphaL[0] = (0.1767766952966368*(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2]*rdvpar2L)/m_; 
  alphaL[1] = (0.1767766952966368*(6.708203932499369*BstarZdBmagL[1]+3.872983346207417*BstarZdBmagL[0])*hamilL[5]*rdvpar2L)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgL = (0.0625*(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2]*rdvpar2L)/m_; 

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
double EmGyrokineticGenGeoSurf1x1vTensor_xR_P2_Bvarsz(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagR[0] = 0.7071067811865475*jacobTotInv[0]*(1.732050807568877*b_y[0]*Apar[1]*rdx2R+1.414213562373095*cmag[0]); 
  BstarZdBmagR[1] = 2.738612787525831*b_y[0]*jacobTotInv[0]*Apar[2]*rdx2R; 

  double BstarZdBmagL[9]; 
  BstarZdBmagL[0] = -0.7071067811865475*jacobTotInv[0]*(1.732050807568877*b_y[0]*AparL[1]*rdx2R-1.414213562373095*cmag[0]); 
  BstarZdBmagL[1] = 2.738612787525831*b_y[0]*jacobTotInv[0]*AparL[2]*rdx2R; 

  double alphaR[3]; 
  alphaR[0] = -(0.1767766952966368*(3.0*(BstarZdBmagR[1]+BstarZdBmagL[1])-1.732050807568877*(BstarZdBmagR[0]+BstarZdBmagL[0]))*hamilR[2]*rdvpar2R)/m_; 
  alphaR[1] = -(0.1767766952966368*(6.708203932499369*(BstarZdBmagR[1]+BstarZdBmagL[1])-3.872983346207417*(BstarZdBmagR[0]+BstarZdBmagL[0]))*hamilR[5]*rdvpar2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.0625*(3.0*BstarZdBmagR[1]+3.0*BstarZdBmagL[1]-1.732050807568877*BstarZdBmagR[0]-1.732050807568877*BstarZdBmagL[0])*hamilR[2]*rdvpar2R)/m_; 

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
double EmGyrokineticGenGeoSurf1x1vTensor_vpar_P2_Bvarsz(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagR[0] = 0.7071067811865475*jacobTotInv[0]*(1.732050807568877*b_y[0]*Apar[1]*rdx2R+1.414213562373095*cmag[0]); 
  BstarZdBmagR[1] = 2.738612787525831*b_y[0]*jacobTotInv[0]*Apar[2]*rdx2R; 

  double alphaR[3]; 
  alphaR[0] = -(0.3535533905932737*((3.872983346207417*BstarZdBmagR[1]*hamilR[4]+1.732050807568877*BstarZdBmagR[0]*hamilR[1])*rdx2R+2.828427124746191*dApardt[0]*q_))/m_; 
  alphaR[1] = -(0.3535533905932737*((3.872983346207417*BstarZdBmagR[0]*hamilR[4]+1.732050807568877*BstarZdBmagR[1]*hamilR[1])*rdx2R+2.828427124746191*dApardt[1]*q_))/m_; 
  alphaR[2] = -(0.7071067811865475*(1.732050807568877*BstarZdBmagR[1]*hamilR[4]*rdx2R+1.414213562373095*dApardt[2]*q_))/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = -(0.125*((3.872983346207417*BstarZdBmagR[1]*hamilR[4]+1.732050807568877*BstarZdBmagR[0]*hamilR[1])*rdx2R+2.828427124746191*dApardt[0]*q_))/m_; 

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
double EmGyrokineticGenGeoSurf1x1vTensor_xL_P2_Bvarsxz(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagL[0] = (0.5*(3.464101615137754*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2L*wvparL+q_*(2.449489742783178*(3.0*(Apar[1]*b_y[2]+b_y[1]*Apar[2])*jacobTotInv[2]+(4.0*jacobTotInv[1]*Apar[2]+2.23606797749979*(Apar[0]*jacobTotInv[1]+jacobTotInv[0]*Apar[1]))*b_y[2]+2.23606797749979*(b_y[0]*jacobTotInv[1]+jacobTotInv[0]*b_y[1])*Apar[2]+2.0*Apar[1]*b_y[1]*jacobTotInv[1]+jacobTotInv[0]*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*rdx2L+2.0*(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0]))))/q_; 
  BstarZdBmagL[1] = (0.01428571428571429*(24.24871130596428*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2L*wvparL+q_*(2.449489742783178*(2.0*((122.9837387624885*Apar[2]+35.0*Apar[0])*b_y[2]+7.0*(5.0*b_y[0]*Apar[2]+4.47213595499958*Apar[1]*b_y[1]))*jacobTotInv[2]+7.0*((20.0*jacobTotInv[0]*Apar[2]+2.23606797749979*(11.0*Apar[1]*jacobTotInv[1]+5.0*Apar[0]*jacobTotInv[0]))*b_y[2]+2.23606797749979*(11.0*b_y[1]*jacobTotInv[1]+5.0*b_y[0]*jacobTotInv[0])*Apar[2]+5.0*((Apar[0]*b_y[1]+b_y[0]*Apar[1])*jacobTotInv[1]+2.0*jacobTotInv[0]*Apar[1]*b_y[1])))*rdx2L+14.0*(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1])))))/q_; 
  BstarZdBmagL[2] = ((2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2L)/(q_*rdvpar2L); 
  BstarZdBmagL[3] = ((b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2L)/(q_*rdvpar2L); 
  BstarZdBmagL[4] = (0.01428571428571429*(121.2435565298214*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2L*wvparL+q_*(2.449489742783178*((145.3444185374863*(Apar[1]*b_y[2]+b_y[1]*Apar[2])+35.0*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*jacobTotInv[2]+(245.9674775249769*jacobTotInv[1]*Apar[2]+35.0*(2.0*Apar[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*Apar[1]))*b_y[2]+7.0*(5.0*(2.0*b_y[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*b_y[1])*Apar[2]+8.94427190999916*Apar[1]*b_y[1]*jacobTotInv[1]))*rdx2L+2.0*((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1])))))/q_; 
  BstarZdBmagL[6] = (1.0*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2L)/(q_*rdvpar2L); 

  double alphaL[3]; 
  alphaL[0] = (0.1767766952966368*(hamilL[5]*(8.660254037844387*BstarZdBmagL[6]+6.708203932499369*BstarZdBmagL[3]+3.872983346207417*BstarZdBmagL[2])+hamilL[2]*(3.872983346207417*BstarZdBmagL[4]+3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0]))*rdvpar2L)/m_; 
  alphaL[1] = (0.1767766952966368*(3.872983346207417*hamilL[2]*BstarZdBmagL[6]+(8.660254037844386*BstarZdBmagL[4]+6.708203932499369*BstarZdBmagL[1]+3.872983346207417*BstarZdBmagL[0])*hamilL[5]+hamilL[2]*(3.0*BstarZdBmagL[3]+1.732050807568877*BstarZdBmagL[2]))*rdvpar2L)/m_; 
  alphaL[2] = (0.3535533905932737*hamilL[5]*(3.872983346207417*BstarZdBmagL[6]+3.0*BstarZdBmagL[3]+1.732050807568877*BstarZdBmagL[2])*rdvpar2L)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgL = (0.0625*(8.660254037844387*hamilL[5]*BstarZdBmagL[6]+(6.708203932499369*BstarZdBmagL[3]+3.872983346207417*BstarZdBmagL[2])*hamilL[5]+3.872983346207417*hamilL[2]*BstarZdBmagL[4]+(3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagL[0])*hamilL[2])*rdvpar2L)/m_; 

  double incr[9]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgL>0) { 
  incr[0] = 0.01666666666666667*(alphaL[2]*(47.43416490252571*fL[8]+36.74234614174768*fL[7])+47.43416490252569*alphaL[1]*fL[6]+21.21320343559643*alphaL[2]*fL[5]+47.43416490252571*alphaL[0]*fL[4]+alphaL[1]*(36.74234614174767*fL[3]+21.21320343559643*fL[2])+alphaL[0]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[1] = -0.05*(alphaL[2]*(27.38612787525831*fL[8]+21.21320343559643*fL[7])+27.38612787525831*alphaL[1]*fL[6]+12.24744871391589*alphaL[2]*fL[5]+27.38612787525831*alphaL[0]*fL[4]+alphaL[1]*(21.21320343559643*fL[3]+12.24744871391589*fL[2])+alphaL[0]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[2] = 0.01666666666666667*(alphaL[1]*(42.42640687119286*fL[8]+32.86335345030997*fL[7])+(42.42640687119286*alphaL[2]+47.43416490252569*alphaL[0])*fL[6]+alphaL[1]*(18.97366596101028*fL[5]+47.43416490252571*fL[4])+(32.86335345030997*alphaL[2]+36.74234614174767*alphaL[0])*fL[3]+(18.97366596101028*alphaL[2]+21.21320343559643*alphaL[0])*fL[2]+alphaL[1]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[3] = -0.05*(alphaL[1]*(24.49489742783179*fL[8]+18.97366596101028*fL[7])+(24.49489742783179*alphaL[2]+27.38612787525831*alphaL[0])*fL[6]+alphaL[1]*(10.95445115010332*fL[5]+27.38612787525831*fL[4])+(18.97366596101028*alphaL[2]+21.21320343559643*alphaL[0])*fL[3]+(10.95445115010332*alphaL[2]+12.24744871391589*alphaL[0])*fL[2]+alphaL[1]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[4] = 0.08333333333333333*(alphaL[2]*(21.21320343559643*fL[8]+16.43167672515499*fL[7])+21.21320343559643*alphaL[1]*fL[6]+9.48683298050514*alphaL[2]*fL[5]+21.21320343559643*alphaL[0]*fL[4]+alphaL[1]*(16.43167672515498*fL[3]+9.48683298050514*fL[2])+alphaL[0]*(16.43167672515498*fL[1]+9.48683298050514*fL[0])); 
  incr[5] = 0.002380952380952381*((212.1320343559643*alphaL[2]+332.0391543176799*alphaL[0])*fL[8]+(164.3167672515499*alphaL[2]+257.1964229922337*alphaL[0])*fL[7]+296.98484809835*alphaL[1]*fL[6]+(94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fL[5]+332.0391543176799*alphaL[2]*fL[4]+alphaL[1]*(230.0434741521698*fL[3]+132.815661727072*fL[2])+(257.1964229922337*fL[1]+148.492424049175*fL[0])*alphaL[2]); 
  incr[6] = 0.01666666666666667*(alphaL[1]*(94.8683298050514*fL[8]+73.48469228349535*fL[7])+(94.86832980505142*alphaL[2]+106.0660171779821*alphaL[0])*fL[6]+alphaL[1]*(42.42640687119286*fL[5]+106.0660171779822*fL[4])+(73.48469228349536*alphaL[2]+82.15838362577493*alphaL[0])*fL[3]+(42.42640687119286*alphaL[2]+47.43416490252569*alphaL[0])*fL[2]+alphaL[1]*(82.15838362577493*fL[1]+47.43416490252569*fL[0])); 
  incr[7] = -0.007142857142857143*((122.474487139159*alphaL[2]+191.7028951268082*alphaL[0])*fL[8]+(94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fL[7]+171.4642819948225*alphaL[1]*fL[6]+(54.77225575051663*alphaL[2]+85.73214099741125*alphaL[0])*fL[5]+191.7028951268082*alphaL[2]*fL[4]+alphaL[1]*(132.815661727072*fL[3]+76.68115805072327*fL[2])+(148.492424049175*fL[1]+85.73214099741125*fL[0])*alphaL[2]); 
  incr[8] = 0.0119047619047619*((94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fL[8]+(73.48469228349536*alphaL[2]+115.0217370760849*alphaL[0])*fL[7]+132.815661727072*alphaL[1]*fL[6]+(42.42640687119286*alphaL[2]+66.40783086353598*alphaL[0])*fL[5]+148.492424049175*alphaL[2]*fL[4]+alphaL[1]*(102.8785691968935*fL[3]+59.39696961967*fL[2])+(115.0217370760849*fL[1]+66.40783086353598*fL[0])*alphaL[2]); 
  } else { 
  incr[0] = 0.01666666666666667*(alphaL[2]*(47.43416490252571*fR[8]-36.74234614174768*fR[7])+47.43416490252569*alphaL[1]*fR[6]+21.21320343559643*alphaL[2]*fR[5]+47.43416490252571*alphaL[0]*fR[4]+alphaL[1]*(21.21320343559643*fR[2]-36.74234614174767*fR[3])+alphaL[0]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[1] = -0.05*(alphaL[2]*(27.38612787525831*fR[8]-21.21320343559643*fR[7])+27.38612787525831*alphaL[1]*fR[6]+12.24744871391589*alphaL[2]*fR[5]+27.38612787525831*alphaL[0]*fR[4]+alphaL[1]*(12.24744871391589*fR[2]-21.21320343559643*fR[3])+alphaL[0]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[2] = 0.01666666666666667*(alphaL[1]*(42.42640687119286*fR[8]-32.86335345030997*fR[7])+(42.42640687119286*alphaL[2]+47.43416490252569*alphaL[0])*fR[6]+alphaL[1]*(18.97366596101028*fR[5]+47.43416490252571*fR[4])+((-32.86335345030997*alphaL[2])-36.74234614174767*alphaL[0])*fR[3]+(18.97366596101028*alphaL[2]+21.21320343559643*alphaL[0])*fR[2]+alphaL[1]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[3] = -0.05*(alphaL[1]*(24.49489742783179*fR[8]-18.97366596101028*fR[7])+(24.49489742783179*alphaL[2]+27.38612787525831*alphaL[0])*fR[6]+alphaL[1]*(10.95445115010332*fR[5]+27.38612787525831*fR[4])+((-18.97366596101028*alphaL[2])-21.21320343559643*alphaL[0])*fR[3]+(10.95445115010332*alphaL[2]+12.24744871391589*alphaL[0])*fR[2]+alphaL[1]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[4] = 0.08333333333333333*(alphaL[2]*(21.21320343559643*fR[8]-16.43167672515499*fR[7])+21.21320343559643*alphaL[1]*fR[6]+9.48683298050514*alphaL[2]*fR[5]+21.21320343559643*alphaL[0]*fR[4]+alphaL[1]*(9.48683298050514*fR[2]-16.43167672515498*fR[3])+alphaL[0]*(9.48683298050514*fR[0]-16.43167672515498*fR[1])); 
  incr[5] = 0.002380952380952381*((212.1320343559643*alphaL[2]+332.0391543176799*alphaL[0])*fR[8]+((-164.3167672515499*alphaL[2])-257.1964229922337*alphaL[0])*fR[7]+296.98484809835*alphaL[1]*fR[6]+(94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fR[5]+332.0391543176799*alphaL[2]*fR[4]+alphaL[1]*(132.815661727072*fR[2]-230.0434741521698*fR[3])+(148.492424049175*fR[0]-257.1964229922337*fR[1])*alphaL[2]); 
  incr[6] = 0.01666666666666667*(alphaL[1]*(94.8683298050514*fR[8]-73.48469228349535*fR[7])+(94.86832980505142*alphaL[2]+106.0660171779821*alphaL[0])*fR[6]+alphaL[1]*(42.42640687119286*fR[5]+106.0660171779822*fR[4])+((-73.48469228349536*alphaL[2])-82.15838362577493*alphaL[0])*fR[3]+(42.42640687119286*alphaL[2]+47.43416490252569*alphaL[0])*fR[2]+alphaL[1]*(47.43416490252569*fR[0]-82.15838362577493*fR[1])); 
  incr[7] = -0.007142857142857143*((122.474487139159*alphaL[2]+191.7028951268082*alphaL[0])*fR[8]+((-94.86832980505142*alphaL[2])-148.492424049175*alphaL[0])*fR[7]+171.4642819948225*alphaL[1]*fR[6]+(54.77225575051663*alphaL[2]+85.73214099741125*alphaL[0])*fR[5]+191.7028951268082*alphaL[2]*fR[4]+alphaL[1]*(76.68115805072327*fR[2]-132.815661727072*fR[3])+(85.73214099741125*fR[0]-148.492424049175*fR[1])*alphaL[2]); 
  incr[8] = 0.0119047619047619*((94.86832980505142*alphaL[2]+148.492424049175*alphaL[0])*fR[8]+((-73.48469228349536*alphaL[2])-115.0217370760849*alphaL[0])*fR[7]+132.815661727072*alphaL[1]*fR[6]+(42.42640687119286*alphaL[2]+66.40783086353598*alphaL[0])*fR[5]+148.492424049175*alphaL[2]*fR[4]+alphaL[1]*(59.39696961967*fR[2]-102.8785691968935*fR[3])+(66.40783086353598*fR[0]-115.0217370760849*fR[1])*alphaL[2]); 
  }
#elif upwindType == QUAD 
  double alphaOrdL;
  double fUpOrd[3];
  alphaOrdL = 0.6324555320336759*alphaL[2]-0.9486832980505137*alphaL[1]+0.7071067811865475*alphaL[0]; 
  fUpOrd[0] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]-1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])+1.161895003862225*fR[3]-1.161895003862225*fL[3]-0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])+1.5*fR[6]-(1.5*fL[6]+0.4472135954999579*(fR[5]-fL[5]))+1.118033988749895*(fL[4]-fR[4])-1.161895003862225*(fR[3]+fL[3])-(0.6708203932499369*(fL[2]-fR[2])-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdL); 
  alphaOrdL = 0.7071067811865475*alphaL[0]-0.7905694150420947*alphaL[2]; 
  fUpOrd[1] = 0.5*((1.25*fR[8]-1.25*fL[8]-0.9682458365518543*(fR[7]+fL[7])+0.5590169943749475*fR[5]-0.5590169943749475*fL[5]-1.118033988749895*fR[4]+1.118033988749895*fL[4]+0.8660254037844386*(fR[1]+fL[1])-0.5*fR[0]+0.5*fL[0])*sgn(alphaOrdL)-1.25*(fR[8]+fL[8])+0.9682458365518543*fR[7]-0.9682458365518543*fL[7]-0.5590169943749475*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0])); 
  alphaOrdL = 0.6324555320336759*alphaL[2]+0.9486832980505137*alphaL[1]+0.7071067811865475*alphaL[0]; 
  fUpOrd[2] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]+1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-1.161895003862225*fR[3]+1.161895003862225*fL[3]+0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])-1.5*fR[6]-(0.4472135954999579*(fR[5]-fL[5])-1.5*fL[6])+1.118033988749895*(fL[4]-fR[4])+1.161895003862225*(fR[3]+fL[3])-((-0.6708203932499369*(fL[2]-fR[2]))-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdL); 

  double fUp[3];
  fUp[0] = 0.07856742013183861*(5.0*fUpOrd[2]+8.0*fUpOrd[1]+5.0*fUpOrd[0]); 
  fUp[1] = 0.5270462766947298*(fUpOrd[2]-1.0*fUpOrd[0]); 
  fUp[2] = 0.3513641844631533*(fUpOrd[2]-2.0*fUpOrd[1]+fUpOrd[0]); 

  incr[0] = 0.5*(alphaL[2]*fUp[2]+alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[1] = -0.8660254037844386*(alphaL[2]*fUp[2]+alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[2] = 0.1*(4.47213595499958*(alphaL[1]*fUp[2]+fUp[1]*alphaL[2])+5.0*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[3] = -0.1*(7.745966692414834*(alphaL[1]*fUp[2]+fUp[1]*alphaL[2])+8.660254037844386*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[4] = 1.118033988749895*(alphaL[2]*fUp[2]+alphaL[1]*fUp[1]+alphaL[0]*fUp[0]); 
  incr[5] = 0.01428571428571429*((22.3606797749979*alphaL[2]+35.0*alphaL[0])*fUp[2]+35.0*fUp[0]*alphaL[2]+31.30495168499706*alphaL[1]*fUp[1]); 
  incr[6] = 0.03333333333333333*(30.0*(alphaL[1]*fUp[2]+fUp[1]*alphaL[2])+33.54101966249684*(alphaL[0]*fUp[1]+fUp[0]*alphaL[1])); 
  incr[7] = -0.01428571428571429*((38.72983346207417*alphaL[2]+60.62177826491071*alphaL[0])*fUp[2]+60.62177826491071*fUp[0]*alphaL[2]+54.22176684690384*alphaL[1]*fUp[1]); 
  incr[8] = 0.07142857142857142*((10.0*alphaL[2]+15.65247584249853*alphaL[0])*fUp[2]+15.65247584249853*fUp[0]*alphaL[2]+14.0*alphaL[1]*fUp[1]); 

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
double EmGyrokineticGenGeoSurf1x1vTensor_xR_P2_Bvarsxz(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagR[0] = (0.5*(3.464101615137754*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(3.0*(Apar[1]*b_y[2]+b_y[1]*Apar[2])*jacobTotInv[2]+(4.0*jacobTotInv[1]*Apar[2]+2.23606797749979*(Apar[0]*jacobTotInv[1]+jacobTotInv[0]*Apar[1]))*b_y[2]+2.23606797749979*(b_y[0]*jacobTotInv[1]+jacobTotInv[0]*b_y[1])*Apar[2]+2.0*Apar[1]*b_y[1]*jacobTotInv[1]+jacobTotInv[0]*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*rdx2R+2.0*(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0]))))/q_; 
  BstarZdBmagR[1] = (0.01428571428571429*(24.24871130596428*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(2.0*((122.9837387624885*Apar[2]+35.0*Apar[0])*b_y[2]+7.0*(5.0*b_y[0]*Apar[2]+4.47213595499958*Apar[1]*b_y[1]))*jacobTotInv[2]+7.0*((20.0*jacobTotInv[0]*Apar[2]+2.23606797749979*(11.0*Apar[1]*jacobTotInv[1]+5.0*Apar[0]*jacobTotInv[0]))*b_y[2]+2.23606797749979*(11.0*b_y[1]*jacobTotInv[1]+5.0*b_y[0]*jacobTotInv[0])*Apar[2]+5.0*((Apar[0]*b_y[1]+b_y[0]*Apar[1])*jacobTotInv[1]+2.0*jacobTotInv[0]*Apar[1]*b_y[1])))*rdx2R+14.0*(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1])))))/q_; 
  BstarZdBmagR[2] = ((2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagR[3] = ((b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagR[4] = (0.01428571428571429*(121.2435565298214*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R*wvparR+q_*(2.449489742783178*((145.3444185374863*(Apar[1]*b_y[2]+b_y[1]*Apar[2])+35.0*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*jacobTotInv[2]+(245.9674775249769*jacobTotInv[1]*Apar[2]+35.0*(2.0*Apar[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*Apar[1]))*b_y[2]+7.0*(5.0*(2.0*b_y[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*b_y[1])*Apar[2]+8.94427190999916*Apar[1]*b_y[1]*jacobTotInv[1]))*rdx2R+2.0*((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1])))))/q_; 
  BstarZdBmagR[6] = (1.0*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R)/(q_*rdvpar2R); 

  double BstarZdBmagL[9]; 
  BstarZdBmagL[0] = (0.5*(3.464101615137754*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(3.0*(b_y[1]*AparL[2]-1.0*AparL[1]*b_y[2])*jacobTotInv[2]+(4.0*jacobTotInv[1]*AparL[2]+2.23606797749979*(AparL[0]*jacobTotInv[1]-1.0*jacobTotInv[0]*AparL[1]))*b_y[2]+2.23606797749979*(b_y[0]*jacobTotInv[1]+jacobTotInv[0]*b_y[1])*AparL[2]-2.0*AparL[1]*b_y[1]*jacobTotInv[1]+jacobTotInv[0]*(AparL[0]*b_y[1]-1.0*b_y[0]*AparL[1]))*rdx2R+2.0*(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0]))))/q_; 
  BstarZdBmagL[1] = (0.01428571428571429*(24.24871130596428*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(2.0*((122.9837387624885*AparL[2]+35.0*AparL[0])*b_y[2]+7.0*(5.0*b_y[0]*AparL[2]-4.47213595499958*AparL[1]*b_y[1]))*jacobTotInv[2]+7.0*((20.0*jacobTotInv[0]*AparL[2]+2.23606797749979*(5.0*AparL[0]*jacobTotInv[0]-11.0*AparL[1]*jacobTotInv[1]))*b_y[2]+2.23606797749979*(11.0*b_y[1]*jacobTotInv[1]+5.0*b_y[0]*jacobTotInv[0])*AparL[2]+5.0*((AparL[0]*b_y[1]-1.0*b_y[0]*AparL[1])*jacobTotInv[1]-2.0*jacobTotInv[0]*AparL[1]*b_y[1])))*rdx2R+14.0*(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1])))))/q_; 
  BstarZdBmagL[2] = ((2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagL[3] = ((b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagL[4] = (0.01428571428571429*(121.2435565298214*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R*wvparR+q_*(2.0*((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1]))-2.449489742783178*((145.3444185374863*(AparL[1]*b_y[2]-1.0*b_y[1]*AparL[2])+35.0*(b_y[0]*AparL[1]-1.0*AparL[0]*b_y[1]))*jacobTotInv[2]-1.0*(245.9674775249769*jacobTotInv[1]*AparL[2]+35.0*(2.0*AparL[0]*jacobTotInv[1]-3.0*jacobTotInv[0]*AparL[1]))*b_y[2]+7.0*(8.94427190999916*AparL[1]*b_y[1]*jacobTotInv[1]-5.0*(2.0*b_y[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*b_y[1])*AparL[2]))*rdx2R)))/q_; 
  BstarZdBmagL[6] = (1.0*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R)/(q_*rdvpar2R); 

  double alphaR[3]; 
  alphaR[0] = (0.1767766952966368*(hamilR[5]*(8.660254037844387*(BstarZdBmagR[6]+BstarZdBmagL[6])-6.708203932499369*(BstarZdBmagR[3]+BstarZdBmagL[3])+3.872983346207417*(BstarZdBmagR[2]+BstarZdBmagL[2]))+hamilR[2]*(3.872983346207417*(BstarZdBmagR[4]+BstarZdBmagL[4])-3.0*(BstarZdBmagR[1]+BstarZdBmagL[1])+1.732050807568877*(BstarZdBmagR[0]+BstarZdBmagL[0])))*rdvpar2R)/m_; 
  alphaR[1] = (0.1767766952966368*(3.872983346207417*hamilR[2]*(BstarZdBmagR[6]+BstarZdBmagL[6])+(8.660254037844386*(BstarZdBmagR[4]+BstarZdBmagL[4])-6.708203932499369*(BstarZdBmagR[1]+BstarZdBmagL[1])+3.872983346207417*(BstarZdBmagR[0]+BstarZdBmagL[0]))*hamilR[5]+hamilR[2]*(1.732050807568877*(BstarZdBmagR[2]+BstarZdBmagL[2])-3.0*(BstarZdBmagR[3]+BstarZdBmagL[3])))*rdvpar2R)/m_; 
  alphaR[2] = (0.3535533905932737*hamilR[5]*(3.872983346207417*(BstarZdBmagR[6]+BstarZdBmagL[6])-3.0*(BstarZdBmagR[3]+BstarZdBmagL[3])+1.732050807568877*(BstarZdBmagR[2]+BstarZdBmagL[2]))*rdvpar2R)/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = (0.0625*(8.660254037844387*hamilR[5]*BstarZdBmagR[6]+8.660254037844387*hamilR[5]*BstarZdBmagL[6]+((-6.708203932499369*BstarZdBmagR[3])-6.708203932499369*BstarZdBmagL[3]+3.872983346207417*BstarZdBmagR[2]+3.872983346207417*BstarZdBmagL[2])*hamilR[5]+3.872983346207417*hamilR[2]*BstarZdBmagR[4]+3.872983346207417*hamilR[2]*BstarZdBmagL[4]+((-3.0*BstarZdBmagR[1])-3.0*BstarZdBmagL[1]+1.732050807568877*BstarZdBmagR[0]+1.732050807568877*BstarZdBmagL[0])*hamilR[2])*rdvpar2R)/m_; 

  double incr[9]; 
#if upwindType == SURFAVG 
  if (alphaSurfAvgR>0) { 
  incr[0] = 0.01666666666666667*(alphaR[2]*(47.43416490252571*fL[8]+36.74234614174768*fL[7])+47.43416490252569*alphaR[1]*fL[6]+21.21320343559643*alphaR[2]*fL[5]+47.43416490252571*alphaR[0]*fL[4]+alphaR[1]*(36.74234614174767*fL[3]+21.21320343559643*fL[2])+alphaR[0]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[1] = -0.05*(alphaR[2]*(27.38612787525831*fL[8]+21.21320343559643*fL[7])+27.38612787525831*alphaR[1]*fL[6]+12.24744871391589*alphaR[2]*fL[5]+27.38612787525831*alphaR[0]*fL[4]+alphaR[1]*(21.21320343559643*fL[3]+12.24744871391589*fL[2])+alphaR[0]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[2] = 0.01666666666666667*(alphaR[1]*(42.42640687119286*fL[8]+32.86335345030997*fL[7])+(42.42640687119286*alphaR[2]+47.43416490252569*alphaR[0])*fL[6]+alphaR[1]*(18.97366596101028*fL[5]+47.43416490252571*fL[4])+(32.86335345030997*alphaR[2]+36.74234614174767*alphaR[0])*fL[3]+(18.97366596101028*alphaR[2]+21.21320343559643*alphaR[0])*fL[2]+alphaR[1]*(36.74234614174767*fL[1]+21.21320343559643*fL[0])); 
  incr[3] = -0.05*(alphaR[1]*(24.49489742783179*fL[8]+18.97366596101028*fL[7])+(24.49489742783179*alphaR[2]+27.38612787525831*alphaR[0])*fL[6]+alphaR[1]*(10.95445115010332*fL[5]+27.38612787525831*fL[4])+(18.97366596101028*alphaR[2]+21.21320343559643*alphaR[0])*fL[3]+(10.95445115010332*alphaR[2]+12.24744871391589*alphaR[0])*fL[2]+alphaR[1]*(21.21320343559643*fL[1]+12.24744871391589*fL[0])); 
  incr[4] = 0.08333333333333333*(alphaR[2]*(21.21320343559643*fL[8]+16.43167672515499*fL[7])+21.21320343559643*alphaR[1]*fL[6]+9.48683298050514*alphaR[2]*fL[5]+21.21320343559643*alphaR[0]*fL[4]+alphaR[1]*(16.43167672515498*fL[3]+9.48683298050514*fL[2])+alphaR[0]*(16.43167672515498*fL[1]+9.48683298050514*fL[0])); 
  incr[5] = 0.002380952380952381*((212.1320343559643*alphaR[2]+332.0391543176799*alphaR[0])*fL[8]+(164.3167672515499*alphaR[2]+257.1964229922337*alphaR[0])*fL[7]+296.98484809835*alphaR[1]*fL[6]+(94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fL[5]+332.0391543176799*alphaR[2]*fL[4]+alphaR[1]*(230.0434741521698*fL[3]+132.815661727072*fL[2])+(257.1964229922337*fL[1]+148.492424049175*fL[0])*alphaR[2]); 
  incr[6] = 0.01666666666666667*(alphaR[1]*(94.8683298050514*fL[8]+73.48469228349535*fL[7])+(94.86832980505142*alphaR[2]+106.0660171779821*alphaR[0])*fL[6]+alphaR[1]*(42.42640687119286*fL[5]+106.0660171779822*fL[4])+(73.48469228349536*alphaR[2]+82.15838362577493*alphaR[0])*fL[3]+(42.42640687119286*alphaR[2]+47.43416490252569*alphaR[0])*fL[2]+alphaR[1]*(82.15838362577493*fL[1]+47.43416490252569*fL[0])); 
  incr[7] = -0.007142857142857143*((122.474487139159*alphaR[2]+191.7028951268082*alphaR[0])*fL[8]+(94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fL[7]+171.4642819948225*alphaR[1]*fL[6]+(54.77225575051663*alphaR[2]+85.73214099741125*alphaR[0])*fL[5]+191.7028951268082*alphaR[2]*fL[4]+alphaR[1]*(132.815661727072*fL[3]+76.68115805072327*fL[2])+(148.492424049175*fL[1]+85.73214099741125*fL[0])*alphaR[2]); 
  incr[8] = 0.0119047619047619*((94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fL[8]+(73.48469228349536*alphaR[2]+115.0217370760849*alphaR[0])*fL[7]+132.815661727072*alphaR[1]*fL[6]+(42.42640687119286*alphaR[2]+66.40783086353598*alphaR[0])*fL[5]+148.492424049175*alphaR[2]*fL[4]+alphaR[1]*(102.8785691968935*fL[3]+59.39696961967*fL[2])+(115.0217370760849*fL[1]+66.40783086353598*fL[0])*alphaR[2]); 
  } else { 
  incr[0] = 0.01666666666666667*(alphaR[2]*(47.43416490252571*fR[8]-36.74234614174768*fR[7])+47.43416490252569*alphaR[1]*fR[6]+21.21320343559643*alphaR[2]*fR[5]+47.43416490252571*alphaR[0]*fR[4]+alphaR[1]*(21.21320343559643*fR[2]-36.74234614174767*fR[3])+alphaR[0]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[1] = -0.05*(alphaR[2]*(27.38612787525831*fR[8]-21.21320343559643*fR[7])+27.38612787525831*alphaR[1]*fR[6]+12.24744871391589*alphaR[2]*fR[5]+27.38612787525831*alphaR[0]*fR[4]+alphaR[1]*(12.24744871391589*fR[2]-21.21320343559643*fR[3])+alphaR[0]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[2] = 0.01666666666666667*(alphaR[1]*(42.42640687119286*fR[8]-32.86335345030997*fR[7])+(42.42640687119286*alphaR[2]+47.43416490252569*alphaR[0])*fR[6]+alphaR[1]*(18.97366596101028*fR[5]+47.43416490252571*fR[4])+((-32.86335345030997*alphaR[2])-36.74234614174767*alphaR[0])*fR[3]+(18.97366596101028*alphaR[2]+21.21320343559643*alphaR[0])*fR[2]+alphaR[1]*(21.21320343559643*fR[0]-36.74234614174767*fR[1])); 
  incr[3] = -0.05*(alphaR[1]*(24.49489742783179*fR[8]-18.97366596101028*fR[7])+(24.49489742783179*alphaR[2]+27.38612787525831*alphaR[0])*fR[6]+alphaR[1]*(10.95445115010332*fR[5]+27.38612787525831*fR[4])+((-18.97366596101028*alphaR[2])-21.21320343559643*alphaR[0])*fR[3]+(10.95445115010332*alphaR[2]+12.24744871391589*alphaR[0])*fR[2]+alphaR[1]*(12.24744871391589*fR[0]-21.21320343559643*fR[1])); 
  incr[4] = 0.08333333333333333*(alphaR[2]*(21.21320343559643*fR[8]-16.43167672515499*fR[7])+21.21320343559643*alphaR[1]*fR[6]+9.48683298050514*alphaR[2]*fR[5]+21.21320343559643*alphaR[0]*fR[4]+alphaR[1]*(9.48683298050514*fR[2]-16.43167672515498*fR[3])+alphaR[0]*(9.48683298050514*fR[0]-16.43167672515498*fR[1])); 
  incr[5] = 0.002380952380952381*((212.1320343559643*alphaR[2]+332.0391543176799*alphaR[0])*fR[8]+((-164.3167672515499*alphaR[2])-257.1964229922337*alphaR[0])*fR[7]+296.98484809835*alphaR[1]*fR[6]+(94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fR[5]+332.0391543176799*alphaR[2]*fR[4]+alphaR[1]*(132.815661727072*fR[2]-230.0434741521698*fR[3])+(148.492424049175*fR[0]-257.1964229922337*fR[1])*alphaR[2]); 
  incr[6] = 0.01666666666666667*(alphaR[1]*(94.8683298050514*fR[8]-73.48469228349535*fR[7])+(94.86832980505142*alphaR[2]+106.0660171779821*alphaR[0])*fR[6]+alphaR[1]*(42.42640687119286*fR[5]+106.0660171779822*fR[4])+((-73.48469228349536*alphaR[2])-82.15838362577493*alphaR[0])*fR[3]+(42.42640687119286*alphaR[2]+47.43416490252569*alphaR[0])*fR[2]+alphaR[1]*(47.43416490252569*fR[0]-82.15838362577493*fR[1])); 
  incr[7] = -0.007142857142857143*((122.474487139159*alphaR[2]+191.7028951268082*alphaR[0])*fR[8]+((-94.86832980505142*alphaR[2])-148.492424049175*alphaR[0])*fR[7]+171.4642819948225*alphaR[1]*fR[6]+(54.77225575051663*alphaR[2]+85.73214099741125*alphaR[0])*fR[5]+191.7028951268082*alphaR[2]*fR[4]+alphaR[1]*(76.68115805072327*fR[2]-132.815661727072*fR[3])+(85.73214099741125*fR[0]-148.492424049175*fR[1])*alphaR[2]); 
  incr[8] = 0.0119047619047619*((94.86832980505142*alphaR[2]+148.492424049175*alphaR[0])*fR[8]+((-73.48469228349536*alphaR[2])-115.0217370760849*alphaR[0])*fR[7]+132.815661727072*alphaR[1]*fR[6]+(42.42640687119286*alphaR[2]+66.40783086353598*alphaR[0])*fR[5]+148.492424049175*alphaR[2]*fR[4]+alphaR[1]*(59.39696961967*fR[2]-102.8785691968935*fR[3])+(66.40783086353598*fR[0]-115.0217370760849*fR[1])*alphaR[2]); 
  }
#elif upwindType == QUAD 
  double alphaOrdR;
  double fUpOrd[3];
  alphaOrdR = 0.6324555320336759*alphaR[2]-0.9486832980505137*alphaR[1]+0.7071067811865475*alphaR[0]; 
  fUpOrd[0] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]-1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])+1.161895003862225*fR[3]-1.161895003862225*fL[3]-0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])+1.5*fR[6]-(1.5*fL[6]+0.4472135954999579*(fR[5]-fL[5]))+1.118033988749895*(fL[4]-fR[4])-1.161895003862225*(fR[3]+fL[3])-(0.6708203932499369*(fL[2]-fR[2])-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdR); 
  alphaOrdR = 0.7071067811865475*alphaR[0]-0.7905694150420947*alphaR[2]; 
  fUpOrd[1] = 0.5*((1.25*fR[8]-1.25*fL[8]-0.9682458365518543*(fR[7]+fL[7])+0.5590169943749475*fR[5]-0.5590169943749475*fL[5]-1.118033988749895*fR[4]+1.118033988749895*fL[4]+0.8660254037844386*(fR[1]+fL[1])-0.5*fR[0]+0.5*fL[0])*sgn(alphaOrdR)-1.25*(fR[8]+fL[8])+0.9682458365518543*fR[7]-0.9682458365518543*fL[7]-0.5590169943749475*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0])); 
  alphaOrdR = 0.6324555320336759*alphaR[2]+0.9486832980505137*alphaR[1]+0.7071067811865475*alphaR[0]; 
  fUpOrd[2] = 0.5*(fR[8]+fL[8]-0.7745966692414833*fR[7]+0.7745966692414833*fL[7]+1.5*(fR[6]+fL[6])+0.4472135954999579*(fR[5]+fL[5])+1.118033988749895*(fR[4]+fL[4])-1.161895003862225*fR[3]+1.161895003862225*fL[3]+0.6708203932499369*(fR[2]+fL[2])-0.8660254037844386*fR[1]+0.8660254037844386*fL[1]+0.5*(fR[0]+fL[0]))-0.5*(fR[8]-(fL[8]+0.7745966692414833*(fR[7]+fL[7])-1.5*fR[6]-(0.4472135954999579*(fR[5]-fL[5])-1.5*fL[6])+1.118033988749895*(fL[4]-fR[4])+1.161895003862225*(fR[3]+fL[3])-((-0.6708203932499369*(fL[2]-fR[2]))-0.8660254037844386*(fR[1]+fL[1]))-0.5*fR[0]+0.5*fL[0]))*sgn(alphaOrdR); 

  double fUp[3];
  fUp[0] = 0.07856742013183861*(5.0*fUpOrd[2]+8.0*fUpOrd[1]+5.0*fUpOrd[0]); 
  fUp[1] = 0.5270462766947298*(fUpOrd[2]-1.0*fUpOrd[0]); 
  fUp[2] = 0.3513641844631533*(fUpOrd[2]-2.0*fUpOrd[1]+fUpOrd[0]); 

  incr[0] = 0.5*(alphaR[2]*fUp[2]+alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[1] = -0.8660254037844386*(alphaR[2]*fUp[2]+alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[2] = 0.1*(4.47213595499958*(alphaR[1]*fUp[2]+fUp[1]*alphaR[2])+5.0*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[3] = -0.1*(7.745966692414834*(alphaR[1]*fUp[2]+fUp[1]*alphaR[2])+8.660254037844386*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[4] = 1.118033988749895*(alphaR[2]*fUp[2]+alphaR[1]*fUp[1]+alphaR[0]*fUp[0]); 
  incr[5] = 0.01428571428571429*((22.3606797749979*alphaR[2]+35.0*alphaR[0])*fUp[2]+35.0*fUp[0]*alphaR[2]+31.30495168499706*alphaR[1]*fUp[1]); 
  incr[6] = 0.03333333333333333*(30.0*(alphaR[1]*fUp[2]+fUp[1]*alphaR[2])+33.54101966249684*(alphaR[0]*fUp[1]+fUp[0]*alphaR[1])); 
  incr[7] = -0.01428571428571429*((38.72983346207417*alphaR[2]+60.62177826491071*alphaR[0])*fUp[2]+60.62177826491071*fUp[0]*alphaR[2]+54.22176684690384*alphaR[1]*fUp[1]); 
  incr[8] = 0.07142857142857142*((10.0*alphaR[2]+15.65247584249853*alphaR[0])*fUp[2]+15.65247584249853*fUp[0]*alphaR[2]+14.0*alphaR[1]*fUp[1]); 

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
double EmGyrokineticGenGeoSurf1x1vTensor_vpar_P2_Bvarsxz(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *wR, const double *dxvR, const double amax_in, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *Apar, const double *AparL, const double *dApardt, const double *dApardtPrev, const double *fL, const double *fR, double *outL, double *outR, double *emModL, double *emModR) 
{ 
  // Apar: parallel component of magnetic vector potential.
  // AparL: Apar in the left cell.
  // dApardt: time derivative of Apar.
  // dApardtPrev: previous dApardt.
  // emModL,emModR: .
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
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
  BstarZdBmagR[0] = (0.5*(3.464101615137754*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(3.0*(Apar[1]*b_y[2]+b_y[1]*Apar[2])*jacobTotInv[2]+(4.0*jacobTotInv[1]*Apar[2]+2.23606797749979*(Apar[0]*jacobTotInv[1]+jacobTotInv[0]*Apar[1]))*b_y[2]+2.23606797749979*(b_y[0]*jacobTotInv[1]+jacobTotInv[0]*b_y[1])*Apar[2]+2.0*Apar[1]*b_y[1]*jacobTotInv[1]+jacobTotInv[0]*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*rdx2R+2.0*(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0]))))/q_; 
  BstarZdBmagR[1] = (0.01428571428571429*(24.24871130596428*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2R*wvparR+q_*(2.449489742783178*(2.0*((122.9837387624885*Apar[2]+35.0*Apar[0])*b_y[2]+7.0*(5.0*b_y[0]*Apar[2]+4.47213595499958*Apar[1]*b_y[1]))*jacobTotInv[2]+7.0*((20.0*jacobTotInv[0]*Apar[2]+2.23606797749979*(11.0*Apar[1]*jacobTotInv[1]+5.0*Apar[0]*jacobTotInv[0]))*b_y[2]+2.23606797749979*(11.0*b_y[1]*jacobTotInv[1]+5.0*b_y[0]*jacobTotInv[0])*Apar[2]+5.0*((Apar[0]*b_y[1]+b_y[0]*Apar[1])*jacobTotInv[1]+2.0*jacobTotInv[0]*Apar[1]*b_y[1])))*rdx2R+14.0*(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1])))))/q_; 
  BstarZdBmagR[2] = ((2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagR[3] = ((b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2R)/(q_*rdvpar2R); 
  BstarZdBmagR[4] = (0.01428571428571429*(121.2435565298214*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R*wvparR+q_*(2.449489742783178*((145.3444185374863*(Apar[1]*b_y[2]+b_y[1]*Apar[2])+35.0*(Apar[0]*b_y[1]+b_y[0]*Apar[1]))*jacobTotInv[2]+(245.9674775249769*jacobTotInv[1]*Apar[2]+35.0*(2.0*Apar[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*Apar[1]))*b_y[2]+7.0*(5.0*(2.0*b_y[0]*jacobTotInv[1]+3.0*jacobTotInv[0]*b_y[1])*Apar[2]+8.94427190999916*Apar[1]*b_y[1]*jacobTotInv[1]))*rdx2R+2.0*((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1])))))/q_; 
  BstarZdBmagR[6] = (1.0*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2R)/(q_*rdvpar2R); 

  double alphaR[3]; 
  alphaR[0] = (0.3535533905932737*(((6.708203932499369*BstarZdBmagR[3]-3.872983346207417*BstarZdBmagR[1])*hamilR[4]+hamilR[1]*(3.0*BstarZdBmagR[2]-1.732050807568877*BstarZdBmagR[0]))*rdx2R-2.828427124746191*dApardt[0]*q_))/m_; 
  alphaR[1] = (0.07071067811865474*((hamilR[4]*(30.0*BstarZdBmagR[6]-17.32050807568877*BstarZdBmagR[4]+33.54101966249685*BstarZdBmagR[2]-19.36491673103709*BstarZdBmagR[0])+hamilR[1]*(15.0*BstarZdBmagR[3]-8.660254037844386*BstarZdBmagR[1]))*rdx2R-14.14213562373095*dApardt[1]*q_))/m_; 
  alphaR[2] = (0.07071067811865474*((15.0*hamilR[1]*BstarZdBmagR[6]+(30.0*BstarZdBmagR[3]-17.32050807568877*BstarZdBmagR[1])*hamilR[4]-8.660254037844386*hamilR[1]*BstarZdBmagR[4])*rdx2R-14.14213562373095*dApardt[2]*q_))/m_; 

  // Surface-averaged phase velocity in this direction.
  double alphaSurfAvgR = (0.125*(((6.708203932499369*BstarZdBmagR[3]-3.872983346207417*BstarZdBmagR[1])*hamilR[4]+3.0*hamilR[1]*BstarZdBmagR[2]-1.732050807568877*BstarZdBmagR[0]*hamilR[1])*rdx2R-2.828427124746191*dApardt[0]*q_))/m_; 

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
