#include <sqrt_on_basis_mod_decl.h>

void sqrt_on_basis_gauss_4x_p1_max(const double qExp, const double *fIn, double *out) 
{ 
  // qExp: exponent in sqrt(f)^q.
  // fIn:  input field.
  // out:  output field.
double sqrtfRq[16];
  sqrtfRq[0] = pow(sqrt((-0.25*fIn[4])-0.25*fIn[3]-0.25*fIn[2]-0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[1] = pow(sqrt(0.25*fIn[4]-0.25*fIn[3]-0.25*fIn[2]-0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[2] = pow(sqrt((-0.25*fIn[4])+0.25*fIn[3]-0.25*fIn[2]-0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[3] = pow(sqrt(0.25*fIn[4]+0.25*fIn[3]-0.25*fIn[2]-0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[4] = pow(sqrt((-0.25*fIn[4])-0.25*fIn[3]+0.25*fIn[2]-0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[5] = pow(sqrt(0.25*fIn[4]-0.25*fIn[3]+0.25*fIn[2]-0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[6] = pow(sqrt((-0.25*fIn[4])+0.25*fIn[3]+0.25*fIn[2]-0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[7] = pow(sqrt(0.25*fIn[4]+0.25*fIn[3]+0.25*fIn[2]-0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[8] = pow(sqrt((-0.25*fIn[4])-0.25*fIn[3]-0.25*fIn[2]+0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[9] = pow(sqrt(0.25*fIn[4]-0.25*fIn[3]-0.25*fIn[2]+0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[10] = pow(sqrt((-0.25*fIn[4])+0.25*fIn[3]-0.25*fIn[2]+0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[11] = pow(sqrt(0.25*fIn[4]+0.25*fIn[3]-0.25*fIn[2]+0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[12] = pow(sqrt((-0.25*fIn[4])-0.25*fIn[3]+0.25*fIn[2]+0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[13] = pow(sqrt(0.25*fIn[4]-0.25*fIn[3]+0.25*fIn[2]+0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[14] = pow(sqrt((-0.25*fIn[4])+0.25*fIn[3]+0.25*fIn[2]+0.25*fIn[1]+0.25*fIn[0]),qExp); 
  sqrtfRq[15] = pow(sqrt(0.25*fIn[4]+0.25*fIn[3]+0.25*fIn[2]+0.25*fIn[1]+0.25*fIn[0]),qExp); 

  out[0] = 0.25*(sqrtfRq[15]+sqrtfRq[14]+sqrtfRq[13]+sqrtfRq[12]+sqrtfRq[11]+sqrtfRq[10]+sqrtfRq[9]+sqrtfRq[8]+sqrtfRq[7]+sqrtfRq[6]+sqrtfRq[5]+sqrtfRq[4]+sqrtfRq[3]+sqrtfRq[2]+sqrtfRq[1]+sqrtfRq[0]); 
  out[1] = 0.25*(sqrtfRq[15]+sqrtfRq[14]+sqrtfRq[13]+sqrtfRq[12]+sqrtfRq[11]+sqrtfRq[10]+sqrtfRq[9]+sqrtfRq[8])-0.25*(sqrtfRq[7]+sqrtfRq[6]+sqrtfRq[5]+sqrtfRq[4]+sqrtfRq[3]+sqrtfRq[2]+sqrtfRq[1]+sqrtfRq[0]); 
  out[2] = 0.25*(sqrtfRq[15]+sqrtfRq[14]+sqrtfRq[13]+sqrtfRq[12])-0.25*(sqrtfRq[11]+sqrtfRq[10]+sqrtfRq[9]+sqrtfRq[8])+0.25*(sqrtfRq[7]+sqrtfRq[6]+sqrtfRq[5]+sqrtfRq[4])-0.25*(sqrtfRq[3]+sqrtfRq[2]+sqrtfRq[1]+sqrtfRq[0]); 
  out[3] = 0.25*(sqrtfRq[15]+sqrtfRq[14])-0.25*(sqrtfRq[13]+sqrtfRq[12])+0.25*(sqrtfRq[11]+sqrtfRq[10])-0.25*(sqrtfRq[9]+sqrtfRq[8])+0.25*(sqrtfRq[7]+sqrtfRq[6])-0.25*(sqrtfRq[5]+sqrtfRq[4])+0.25*(sqrtfRq[3]+sqrtfRq[2])-0.25*(sqrtfRq[1]+sqrtfRq[0]); 
  out[4] = 0.25*sqrtfRq[15]-0.25*sqrtfRq[14]+0.25*sqrtfRq[13]-0.25*sqrtfRq[12]+0.25*sqrtfRq[11]-0.25*sqrtfRq[10]+0.25*sqrtfRq[9]-0.25*sqrtfRq[8]+0.25*sqrtfRq[7]-0.25*sqrtfRq[6]+0.25*sqrtfRq[5]-0.25*sqrtfRq[4]+0.25*sqrtfRq[3]-0.25*sqrtfRq[2]+0.25*sqrtfRq[1]-0.25*sqrtfRq[0]; 
}
