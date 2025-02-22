#include <gkyl_lagrangeFix_kernels.h>

void lagrangeFix_gk_1x1v_ser_p1(double *dm0, double *dm1, double *dm2, double *B, double mass, double *lo, double *L, double *Nv, double *vc, double *f) {
  double lambda0 [2];
  double lambda1 [2];
  double lambda2 [2];

  lambda0[0] = (360.0*dm0[0]*pow(Nv[0],5)*pow(lo[0],4)+(720.0*L[0]*dm0[0]-720.0*dm1[0])*pow(Nv[0],5)*pow(lo[0],3)+((504.0*dm0[0]*pow(L[0],2)+360.0*dm2[0]-1080.0*L[0]*dm1[0])*pow(Nv[0],5)-24.0*Nv[0]*dm0[0]*pow(L[0],2))*pow(lo[0],2)+lo[0]*((144.0*dm0[0]*pow(L[0],3)-504.0*dm1[0]*pow(L[0],2)+360.0*L[0]*dm2[0])*pow(Nv[0],5)+Nv[0]*(24.0*dm1[0]*pow(L[0],2)-24.0*dm0[0]*pow(L[0],3)))+(18.0*dm0[0]*pow(L[0],4)-72.0*dm1[0]*pow(L[0],3)+60.0*dm2[0]*pow(L[0],2))*pow(Nv[0],5)+Nv[0]*(12.0*dm1[0]*pow(L[0],3)-8.0*dm0[0]*pow(L[0],4)))*pow(pow(L[0],6)*pow(Nv[0],4)-1.0*pow(L[0],6),-1);

  lambda0[1] = (360.0*dm0[1]*pow(Nv[0],5)*pow(lo[0],4)+(720.0*L[0]*dm0[1]-720.0*dm1[1])*pow(Nv[0],5)*pow(lo[0],3)+((504.0*dm0[1]*pow(L[0],2)+360.0*dm2[1]-1080.0*L[0]*dm1[1])*pow(Nv[0],5)-24.0*Nv[0]*dm0[1]*pow(L[0],2))*pow(lo[0],2)+lo[0]*((144.0*dm0[1]*pow(L[0],3)-504.0*dm1[1]*pow(L[0],2)+360.0*L[0]*dm2[1])*pow(Nv[0],5)+Nv[0]*(24.0*dm1[1]*pow(L[0],2)-24.0*dm0[1]*pow(L[0],3)))+(18.0*dm0[1]*pow(L[0],4)-72.0*dm1[1]*pow(L[0],3)+60.0*dm2[1]*pow(L[0],2))*pow(Nv[0],5)+Nv[0]*(12.0*dm1[1]*pow(L[0],3)-8.0*dm0[1]*pow(L[0],4)))*pow(pow(L[0],6)*pow(Nv[0],4)-1.0*pow(L[0],6),-1);

  lambda1[0] = -1.0*(720.0*dm0[0]*pow(Nv[0],5)*pow(lo[0],3)+(1080.0*L[0]*dm0[0]-1440.0*dm1[0])*pow(Nv[0],5)*pow(lo[0],2)+lo[0]*((504.0*dm0[0]*pow(L[0],2)+720.0*dm2[0]-1440.0*L[0]*dm1[0])*pow(Nv[0],5)-24.0*Nv[0]*dm0[0]*pow(L[0],2))+(72.0*dm0[0]*pow(L[0],3)-384.0*dm1[0]*pow(L[0],2)+360.0*L[0]*dm2[0])*pow(Nv[0],5)+Nv[0]*(24.0*dm1[0]*pow(L[0],2)-12.0*dm0[0]*pow(L[0],3)))*pow(pow(L[0],6)*pow(Nv[0],4)-1.0*pow(L[0],6),-1);

  lambda1[1] = -1.0*(720.0*dm0[1]*pow(Nv[0],5)*pow(lo[0],3)+(1080.0*L[0]*dm0[1]-1440.0*dm1[1])*pow(Nv[0],5)*pow(lo[0],2)+lo[0]*((504.0*dm0[1]*pow(L[0],2)+720.0*dm2[1]-1440.0*L[0]*dm1[1])*pow(Nv[0],5)-24.0*Nv[0]*dm0[1]*pow(L[0],2))+(72.0*dm0[1]*pow(L[0],3)-384.0*dm1[1]*pow(L[0],2)+360.0*L[0]*dm2[1])*pow(Nv[0],5)+Nv[0]*(24.0*dm1[1]*pow(L[0],2)-12.0*dm0[1]*pow(L[0],3)))*pow(pow(L[0],6)*pow(Nv[0],4)-1.0*pow(L[0],6),-1);

  lambda2[0] = (360.0*dm0[0]*pow(Nv[0],5)*pow(lo[0],2)+(60.0*dm0[0]*pow(L[0],2)+360.0*dm2[0]-360.0*L[0]*dm1[0])*pow(Nv[0],5)+(360.0*L[0]*dm0[0]-720.0*dm1[0])*lo[0]*pow(Nv[0],5))*pow(pow(L[0],6)*pow(Nv[0],4)-1.0*pow(L[0],6),-1);

  lambda2[1] = (360.0*dm0[1]*pow(Nv[0],5)*pow(lo[0],2)+(60.0*dm0[1]*pow(L[0],2)+360.0*dm2[1]-360.0*L[0]*dm1[1])*pow(Nv[0],5)+lo[0]*(360.0*L[0]*dm0[1]-720.0*dm1[1])*pow(Nv[0],5))*pow(pow(L[0],6)*pow(Nv[0],4)-1.0*pow(L[0],6),-1);

  f[0] = f[0] + 0.05892556509887893*pow(Nv[0],-3)*(12.0*L[0]*lambda2[0]*pow(Nv[0],2)*pow(vc[0],2)+12.0*L[0]*lambda1[0]*vc[0]*pow(Nv[0],2)+12.0*L[0]*lambda0[0]*pow(Nv[0],2)+lambda2[0]*pow(L[0],3));
  f[1] = f[1] + 0.05892556509887893*pow(Nv[0],-3)*(12.0*L[0]*lambda2[1]*pow(Nv[0],2)*pow(vc[0],2)+12.0*L[0]*vc[0]*lambda1[1]*pow(Nv[0],2)+12.0*L[0]*lambda0[1]*pow(Nv[0],2)+lambda2[1]*pow(L[0],3));
  f[2] = f[2] + 0.08333333333333333*(4.898979485566357*lambda2[0]*vc[0]*pow(L[0],2)+2.449489742783178*lambda1[0]*pow(L[0],2))*pow(Nv[0],-2);
  f[3] = f[3] + 0.08333333333333333*(4.898979485566357*vc[0]*lambda2[1]*pow(L[0],2)+2.449489742783178*lambda1[1]*pow(L[0],2))*pow(Nv[0],-2);
}

