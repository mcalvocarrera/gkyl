#include <VlasovModDecl.h> 
__host__ __device__ void VlasovSurfStream1x3vSer_X_P3(const double *wl, const double *wr, const double *dxvl, const double *dxvr, const double *fl, const double *fr, double *outl, double *outr) 
{ 
  // w[NDIM]:   Cell-center coordinates.
  // dxv[NDIM]: Cell spacing.
  // fl/fr:     Distribution function in left/right cells.
  // outl/outr: Incremented distribution function in left/right cells.
  double rdxl2 = 2.0/dxvl[0]; 
  double rdxr2 = 2.0/dxvr[0]; 

  double incr[80]; 

  if (wr[1]>0) { 
  incr[0] = dxvl[1]*(0.3818813079129866*fl[48]+0.3227486121839514*fl[19]+0.25*fl[5]+0.1443375672974065*fl[2])+wl[1]*(1.322875655532295*fl[31]+1.118033988749895*fl[11]+0.8660254037844386*fl[1]+0.5*fl[0]); 
  incr[1] = dxvl[1]*((-0.6614378277661477*fl[48])-0.5590169943749476*fl[19]-0.4330127018922193*fl[5]-0.25*fl[2])+wl[1]*((-2.29128784747792*fl[31])-1.936491673103709*fl[11]-1.5*fl[1]-0.8660254037844386*fl[0]); 
  incr[2] = wl[1]*(1.322875655532295*fl[48]+1.118033988749895*fl[19]+0.8660254037844386*fl[5]+0.5*fl[2])+dxvl[1]*(0.3818813079129867*fl[31]+0.223606797749979*fl[20]+0.1290994448735806*fl[12]+0.3227486121839515*fl[11]+0.25*fl[1]+0.1443375672974065*fl[0]); 
  incr[3] = dxvl[1]*(0.3818813079129867*fl[64]+0.3227486121839515*fl[36]+0.25*fl[15]+0.1443375672974065*fl[7])+wl[1]*(1.322875655532295*fl[50]+1.118033988749895*fl[21]+0.8660254037844386*fl[6]+0.5*fl[3]); 
  incr[4] = dxvl[1]*(0.3818813079129867*fl[67]+0.3227486121839515*fl[39]+0.25*fl[16]+0.1443375672974065*fl[9])+wl[1]*(1.322875655532295*fl[54]+1.118033988749895*fl[25]+0.8660254037844386*fl[8]+0.5*fl[4]); 
  incr[5] = wl[1]*((-2.29128784747792*fl[48])-1.936491673103709*fl[19]-1.5*fl[5]-0.8660254037844386*fl[2])+dxvl[1]*((-0.6614378277661477*fl[31])-0.3872983346207417*fl[20]-0.223606797749979*fl[12]-0.5590169943749475*fl[11]-0.4330127018922193*fl[1]-0.25*fl[0]); 
  incr[6] = dxvl[1]*((-0.6614378277661477*fl[64])-0.5590169943749475*fl[36]-0.4330127018922193*fl[15]-0.25*fl[7])+wl[1]*((-2.29128784747792*fl[50])-1.936491673103709*fl[21]-1.5*fl[6]-0.8660254037844386*fl[3]); 
  incr[7] = wl[1]*(1.322875655532295*fl[64]+1.118033988749895*fl[36]+0.8660254037844386*fl[15]+0.5*fl[7])+dxvl[1]*(0.3818813079129866*fl[50]+0.223606797749979*fl[37]+0.1290994448735805*fl[22]+0.3227486121839514*fl[21]+0.25*fl[6]+0.1443375672974065*fl[3]); 
  incr[8] = dxvl[1]*((-0.6614378277661477*fl[67])-0.5590169943749475*fl[39]-0.4330127018922193*fl[16]-0.25*fl[9])+wl[1]*((-2.29128784747792*fl[54])-1.936491673103709*fl[25]-1.5*fl[8]-0.8660254037844386*fl[4]); 
  incr[9] = wl[1]*(1.322875655532295*fl[67]+1.118033988749895*fl[39]+0.8660254037844386*fl[16]+0.5*fl[9])+dxvl[1]*(0.3818813079129866*fl[54]+0.223606797749979*fl[40]+0.1290994448735805*fl[26]+0.3227486121839514*fl[25]+0.25*fl[8]+0.1443375672974065*fl[4]); 
  incr[10] = dxvl[1]*(0.3818813079129866*fl[76]+0.3227486121839514*fl[60]+0.25*fl[35]+0.1443375672974065*fl[18])+wl[1]*(1.322875655532295*fl[69]+1.118033988749895*fl[41]+0.8660254037844386*fl[17]+0.5*fl[10]); 
  incr[11] = dxvl[1]*(0.8539125638299665*fl[48]+0.7216878364870323*fl[19]+0.5590169943749475*fl[5]+0.3227486121839515*fl[2])+wl[1]*(2.958039891549809*fl[31]+2.5*fl[11]+1.936491673103709*fl[1]+1.118033988749895*fl[0]); 
  incr[12] = dxvl[1]*(0.2195775164134199*fl[49]+0.3415650255319865*fl[48]+0.1267731382092775*fl[32]+0.2886751345948129*fl[19]+0.223606797749979*fl[5]+0.1290994448735806*fl[2])+wl[1]*(0.8660254037844387*fl[20]+0.5*fl[12]); 
  incr[13] = dxvl[1]*(0.25*fl[38]+0.1443375672974064*fl[24])+wl[1]*(0.8660254037844387*fl[23]+0.5*fl[13]); 
  incr[14] = dxvl[1]*(0.25*fl[45]+0.1443375672974064*fl[29])+wl[1]*(0.8660254037844387*fl[28]+0.5*fl[14]); 
  incr[15] = wl[1]*((-2.29128784747792*fl[64])-1.936491673103709*fl[36]-1.5*fl[15]-0.8660254037844386*fl[7])+dxvl[1]*((-0.6614378277661477*fl[50])-0.3872983346207416*fl[37]-0.223606797749979*fl[22]-0.5590169943749476*fl[21]-0.4330127018922193*fl[6]-0.25*fl[3]); 
  incr[16] = wl[1]*((-2.29128784747792*fl[67])-1.936491673103709*fl[39]-1.5*fl[16]-0.8660254037844386*fl[9])+dxvl[1]*((-0.6614378277661477*fl[54])-0.3872983346207416*fl[40]-0.223606797749979*fl[26]-0.5590169943749476*fl[25]-0.4330127018922193*fl[8]-0.25*fl[4]); 
  incr[17] = dxvl[1]*((-0.6614378277661477*fl[76])-0.5590169943749476*fl[60]-0.4330127018922193*fl[35]-0.25*fl[18])+wl[1]*((-2.29128784747792*fl[69])-1.936491673103709*fl[41]-1.5*fl[17]-0.8660254037844386*fl[10]); 
  incr[18] = wl[1]*(1.322875655532295*fl[76]+1.118033988749895*fl[60]+0.8660254037844386*fl[35]+0.5*fl[18])+dxvl[1]*(0.3818813079129867*fl[69]+0.223606797749979*fl[61]+0.1290994448735806*fl[42]+0.3227486121839515*fl[41]+0.25*fl[17]+0.1443375672974065*fl[10]); 
  incr[19] = wl[1]*(2.958039891549808*fl[48]+2.5*fl[19]+1.936491673103709*fl[5]+1.118033988749895*fl[2])+dxvl[1]*(0.8539125638299666*fl[31]+0.5*fl[20]+0.2886751345948129*fl[12]+0.7216878364870323*fl[11]+0.5590169943749476*fl[1]+0.3227486121839514*fl[0]); 
  incr[20] = dxvl[1]*((-0.3803194146278325*fl[49])-0.5916079783099615*fl[48]-0.2195775164134199*fl[32]-0.5*fl[19]-0.3872983346207417*fl[5]-0.223606797749979*fl[2])+wl[1]*((-1.5*fl[20])-0.8660254037844387*fl[12]); 
  incr[21] = dxvl[1]*(0.8539125638299666*fl[64]+0.7216878364870323*fl[36]+0.5590169943749476*fl[15]+0.3227486121839514*fl[7])+wl[1]*(2.958039891549808*fl[50]+2.5*fl[21]+1.936491673103709*fl[6]+1.118033988749895*fl[3]); 
  incr[22] = dxvl[1]*(0.2195775164134199*fl[65]+0.3415650255319866*fl[64]+0.1267731382092775*fl[51]+0.2886751345948129*fl[36]+0.223606797749979*fl[15]+0.1290994448735805*fl[7])+wl[1]*(0.8660254037844387*fl[37]+0.5*fl[22]); 
  incr[23] = dxvl[1]*((-0.4330127018922194*fl[38])-0.25*fl[24])+wl[1]*((-1.5*fl[23])-0.8660254037844387*fl[13]); 
  incr[24] = wl[1]*(0.8660254037844387*fl[38]+0.5*fl[24])+dxvl[1]*(0.25*fl[23]+0.1443375672974064*fl[13]); 
  incr[25] = dxvl[1]*(0.8539125638299666*fl[67]+0.7216878364870323*fl[39]+0.5590169943749476*fl[16]+0.3227486121839514*fl[9])+wl[1]*(2.958039891549808*fl[54]+2.5*fl[25]+1.936491673103709*fl[8]+1.118033988749895*fl[4]); 
  incr[26] = dxvl[1]*(0.2195775164134199*fl[68]+0.3415650255319866*fl[67]+0.1267731382092775*fl[55]+0.2886751345948129*fl[39]+0.223606797749979*fl[16]+0.1290994448735805*fl[9])+wl[1]*(0.8660254037844387*fl[40]+0.5*fl[26]); 
  incr[27] = dxvl[1]*(0.25*fl[62]+0.1443375672974064*fl[44])+wl[1]*(0.8660254037844387*fl[43]+0.5*fl[27]); 
  incr[28] = dxvl[1]*((-0.4330127018922194*fl[45])-0.25*fl[29])+wl[1]*((-1.5*fl[28])-0.8660254037844387*fl[14]); 
  incr[29] = wl[1]*(0.8660254037844387*fl[45]+0.5*fl[29])+dxvl[1]*(0.25*fl[28]+0.1443375672974064*fl[14]); 
  incr[30] = dxvl[1]*(0.25*fl[63]+0.1443375672974064*fl[47])+wl[1]*(0.8660254037844387*fl[46]+0.5*fl[30]); 
  incr[31] = dxvl[1]*((-1.010362971081845*fl[48])-0.8539125638299666*fl[19]-0.6614378277661477*fl[5]-0.3818813079129867*fl[2])+wl[1]*((-3.5*fl[31])-2.958039891549809*fl[11]-2.29128784747792*fl[1]-1.322875655532295*fl[0]); 
  incr[32] = wl[1]*(0.8660254037844386*fl[49]+0.5*fl[32])+dxvl[1]*(0.2195775164134199*fl[20]+0.1267731382092775*fl[12]); 
  incr[33] = dxvl[1]*(0.25*fl[66]+0.1443375672974064*fl[53])+wl[1]*(0.8660254037844386*fl[52]+0.5*fl[33]); 
  incr[34] = dxvl[1]*(0.25*fl[73]+0.1443375672974064*fl[58])+wl[1]*(0.8660254037844386*fl[57]+0.5*fl[34]); 
  incr[35] = wl[1]*((-2.29128784747792*fl[76])-1.936491673103709*fl[60]-1.5*fl[35]-0.8660254037844386*fl[18])+dxvl[1]*((-0.6614378277661477*fl[69])-0.3872983346207417*fl[61]-0.223606797749979*fl[42]-0.5590169943749475*fl[41]-0.4330127018922193*fl[17]-0.25*fl[10]); 
  incr[36] = wl[1]*(2.958039891549809*fl[64]+2.5*fl[36]+1.936491673103709*fl[15]+1.118033988749895*fl[7])+dxvl[1]*(0.8539125638299665*fl[50]+0.5*fl[37]+0.2886751345948129*fl[22]+0.7216878364870323*fl[21]+0.5590169943749475*fl[6]+0.3227486121839515*fl[3]); 
  incr[37] = dxvl[1]*((-0.3803194146278324*fl[65])-0.5916079783099616*fl[64]-0.2195775164134199*fl[51]-0.5*fl[36]-0.3872983346207416*fl[15]-0.223606797749979*fl[7])+wl[1]*((-1.5*fl[37])-0.8660254037844387*fl[22]); 
  incr[38] = wl[1]*((-1.5*fl[38])-0.8660254037844387*fl[24])+dxvl[1]*((-0.4330127018922194*fl[23])-0.25*fl[13]); 
  incr[39] = wl[1]*(2.958039891549809*fl[67]+2.5*fl[39]+1.936491673103709*fl[16]+1.118033988749895*fl[9])+dxvl[1]*(0.8539125638299665*fl[54]+0.5*fl[40]+0.2886751345948129*fl[26]+0.7216878364870323*fl[25]+0.5590169943749475*fl[8]+0.3227486121839515*fl[4]); 
  incr[40] = dxvl[1]*((-0.3803194146278324*fl[68])-0.5916079783099616*fl[67]-0.2195775164134199*fl[55]-0.5*fl[39]-0.3872983346207416*fl[16]-0.223606797749979*fl[9])+wl[1]*((-1.5*fl[40])-0.8660254037844387*fl[26]); 
  incr[41] = dxvl[1]*(0.8539125638299665*fl[76]+0.7216878364870323*fl[60]+0.5590169943749475*fl[35]+0.3227486121839515*fl[18])+wl[1]*(2.958039891549809*fl[69]+2.5*fl[41]+1.936491673103709*fl[17]+1.118033988749895*fl[10]); 
  incr[42] = dxvl[1]*(0.2195775164134199*fl[77]+0.3415650255319865*fl[76]+0.1267731382092775*fl[70]+0.2886751345948129*fl[60]+0.223606797749979*fl[35]+0.1290994448735806*fl[18])+wl[1]*(0.8660254037844387*fl[61]+0.5*fl[42]); 
  incr[43] = dxvl[1]*((-0.4330127018922194*fl[62])-0.25*fl[44])+wl[1]*((-1.5*fl[43])-0.8660254037844387*fl[27]); 
  incr[44] = wl[1]*(0.8660254037844387*fl[62]+0.5*fl[44])+dxvl[1]*(0.25*fl[43]+0.1443375672974064*fl[27]); 
  incr[45] = wl[1]*((-1.5*fl[45])-0.8660254037844387*fl[29])+dxvl[1]*((-0.4330127018922194*fl[28])-0.25*fl[14]); 
  incr[46] = dxvl[1]*((-0.4330127018922194*fl[63])-0.25*fl[47])+wl[1]*((-1.5*fl[46])-0.8660254037844387*fl[30]); 
  incr[47] = wl[1]*(0.8660254037844387*fl[63]+0.5*fl[47])+dxvl[1]*(0.25*fl[46]+0.1443375672974064*fl[30]); 
  incr[48] = wl[1]*((-3.5*fl[48])-2.958039891549808*fl[19]-2.29128784747792*fl[5]-1.322875655532295*fl[2])+dxvl[1]*((-1.010362971081845*fl[31])-0.5916079783099615*fl[20]-0.3415650255319865*fl[12]-0.8539125638299665*fl[11]-0.6614378277661477*fl[1]-0.3818813079129866*fl[0]); 
  incr[49] = wl[1]*((-1.5*fl[49])-0.8660254037844386*fl[32])+dxvl[1]*((-0.3803194146278325*fl[20])-0.2195775164134199*fl[12]); 
  incr[50] = dxvl[1]*((-1.010362971081845*fl[64])-0.8539125638299665*fl[36]-0.6614378277661477*fl[15]-0.3818813079129866*fl[7])+wl[1]*((-3.5*fl[50])-2.958039891549808*fl[21]-2.29128784747792*fl[6]-1.322875655532295*fl[3]); 
  incr[51] = wl[1]*(0.8660254037844386*fl[65]+0.5*fl[51])+dxvl[1]*(0.2195775164134199*fl[37]+0.1267731382092775*fl[22]); 
  incr[52] = dxvl[1]*((-0.4330127018922193*fl[66])-0.25*fl[53])+wl[1]*((-1.5*fl[52])-0.8660254037844386*fl[33]); 
  incr[53] = wl[1]*(0.8660254037844386*fl[66]+0.5*fl[53])+dxvl[1]*(0.25*fl[52]+0.1443375672974064*fl[33]); 
  incr[54] = dxvl[1]*((-1.010362971081845*fl[67])-0.8539125638299665*fl[39]-0.6614378277661477*fl[16]-0.3818813079129866*fl[9])+wl[1]*((-3.5*fl[54])-2.958039891549808*fl[25]-2.29128784747792*fl[8]-1.322875655532295*fl[4]); 
  incr[55] = wl[1]*(0.8660254037844386*fl[68]+0.5*fl[55])+dxvl[1]*(0.2195775164134199*fl[40]+0.1267731382092775*fl[26]); 
  incr[56] = dxvl[1]*(0.25*fl[78]+0.1443375672974064*fl[72])+wl[1]*(0.8660254037844386*fl[71]+0.5*fl[56]); 
  incr[57] = dxvl[1]*((-0.4330127018922193*fl[73])-0.25*fl[58])+wl[1]*((-1.5*fl[57])-0.8660254037844386*fl[34]); 
  incr[58] = wl[1]*(0.8660254037844386*fl[73]+0.5*fl[58])+dxvl[1]*(0.25*fl[57]+0.1443375672974064*fl[34]); 
  incr[59] = dxvl[1]*(0.25*fl[79]+0.1443375672974064*fl[75])+wl[1]*(0.8660254037844386*fl[74]+0.5*fl[59]); 
  incr[60] = wl[1]*(2.958039891549808*fl[76]+2.5*fl[60]+1.936491673103709*fl[35]+1.118033988749895*fl[18])+dxvl[1]*(0.8539125638299666*fl[69]+0.5*fl[61]+0.2886751345948129*fl[42]+0.7216878364870323*fl[41]+0.5590169943749476*fl[17]+0.3227486121839514*fl[10]); 
  incr[61] = dxvl[1]*((-0.3803194146278325*fl[77])-0.5916079783099615*fl[76]-0.2195775164134199*fl[70]-0.5*fl[60]-0.3872983346207417*fl[35]-0.223606797749979*fl[18])+wl[1]*((-1.5*fl[61])-0.8660254037844387*fl[42]); 
  incr[62] = wl[1]*((-1.5*fl[62])-0.8660254037844387*fl[44])+dxvl[1]*((-0.4330127018922194*fl[43])-0.25*fl[27]); 
  incr[63] = wl[1]*((-1.5*fl[63])-0.8660254037844387*fl[47])+dxvl[1]*((-0.4330127018922194*fl[46])-0.25*fl[30]); 
  incr[64] = wl[1]*((-3.5*fl[64])-2.958039891549809*fl[36]-2.29128784747792*fl[15]-1.322875655532295*fl[7])+dxvl[1]*((-1.010362971081845*fl[50])-0.5916079783099616*fl[37]-0.3415650255319866*fl[22]-0.8539125638299666*fl[21]-0.6614378277661477*fl[6]-0.3818813079129867*fl[3]); 
  incr[65] = wl[1]*((-1.5*fl[65])-0.8660254037844386*fl[51])+dxvl[1]*((-0.3803194146278324*fl[37])-0.2195775164134199*fl[22]); 
  incr[66] = wl[1]*((-1.5*fl[66])-0.8660254037844386*fl[53])+dxvl[1]*((-0.4330127018922193*fl[52])-0.25*fl[33]); 
  incr[67] = wl[1]*((-3.5*fl[67])-2.958039891549809*fl[39]-2.29128784747792*fl[16]-1.322875655532295*fl[9])+dxvl[1]*((-1.010362971081845*fl[54])-0.5916079783099616*fl[40]-0.3415650255319866*fl[26]-0.8539125638299666*fl[25]-0.6614378277661477*fl[8]-0.3818813079129867*fl[4]); 
  incr[68] = wl[1]*((-1.5*fl[68])-0.8660254037844386*fl[55])+dxvl[1]*((-0.3803194146278324*fl[40])-0.2195775164134199*fl[26]); 
  incr[69] = dxvl[1]*((-1.010362971081845*fl[76])-0.8539125638299666*fl[60]-0.6614378277661477*fl[35]-0.3818813079129867*fl[18])+wl[1]*((-3.5*fl[69])-2.958039891549809*fl[41]-2.29128784747792*fl[17]-1.322875655532295*fl[10]); 
  incr[70] = wl[1]*(0.8660254037844386*fl[77]+0.5*fl[70])+dxvl[1]*(0.2195775164134199*fl[61]+0.1267731382092775*fl[42]); 
  incr[71] = dxvl[1]*((-0.4330127018922193*fl[78])-0.25*fl[72])+wl[1]*((-1.5*fl[71])-0.8660254037844386*fl[56]); 
  incr[72] = wl[1]*(0.8660254037844386*fl[78]+0.5*fl[72])+dxvl[1]*(0.25*fl[71]+0.1443375672974064*fl[56]); 
  incr[73] = wl[1]*((-1.5*fl[73])-0.8660254037844386*fl[58])+dxvl[1]*((-0.4330127018922193*fl[57])-0.25*fl[34]); 
  incr[74] = dxvl[1]*((-0.4330127018922193*fl[79])-0.25*fl[75])+wl[1]*((-1.5*fl[74])-0.8660254037844386*fl[59]); 
  incr[75] = wl[1]*(0.8660254037844386*fl[79]+0.5*fl[75])+dxvl[1]*(0.25*fl[74]+0.1443375672974064*fl[59]); 
  incr[76] = wl[1]*((-3.5*fl[76])-2.958039891549808*fl[60]-2.29128784747792*fl[35]-1.322875655532295*fl[18])+dxvl[1]*((-1.010362971081845*fl[69])-0.5916079783099615*fl[61]-0.3415650255319865*fl[42]-0.8539125638299665*fl[41]-0.6614378277661477*fl[17]-0.3818813079129866*fl[10]); 
  incr[77] = wl[1]*((-1.5*fl[77])-0.8660254037844386*fl[70])+dxvl[1]*((-0.3803194146278325*fl[61])-0.2195775164134199*fl[42]); 
  incr[78] = wl[1]*((-1.5*fl[78])-0.8660254037844386*fl[72])+dxvl[1]*((-0.4330127018922193*fl[71])-0.25*fl[56]); 
  incr[79] = wl[1]*((-1.5*fl[79])-0.8660254037844386*fl[75])+dxvl[1]*((-0.4330127018922193*fl[74])-0.25*fl[59]); 

  outr[0] += incr[0]*rdxr2; 
  outr[1] += incr[1]*rdxr2; 
  outr[2] += incr[2]*rdxr2; 
  outr[3] += incr[3]*rdxr2; 
  outr[4] += incr[4]*rdxr2; 
  outr[5] += incr[5]*rdxr2; 
  outr[6] += incr[6]*rdxr2; 
  outr[7] += incr[7]*rdxr2; 
  outr[8] += incr[8]*rdxr2; 
  outr[9] += incr[9]*rdxr2; 
  outr[10] += incr[10]*rdxr2; 
  outr[11] += incr[11]*rdxr2; 
  outr[12] += incr[12]*rdxr2; 
  outr[13] += incr[13]*rdxr2; 
  outr[14] += incr[14]*rdxr2; 
  outr[15] += incr[15]*rdxr2; 
  outr[16] += incr[16]*rdxr2; 
  outr[17] += incr[17]*rdxr2; 
  outr[18] += incr[18]*rdxr2; 
  outr[19] += incr[19]*rdxr2; 
  outr[20] += incr[20]*rdxr2; 
  outr[21] += incr[21]*rdxr2; 
  outr[22] += incr[22]*rdxr2; 
  outr[23] += incr[23]*rdxr2; 
  outr[24] += incr[24]*rdxr2; 
  outr[25] += incr[25]*rdxr2; 
  outr[26] += incr[26]*rdxr2; 
  outr[27] += incr[27]*rdxr2; 
  outr[28] += incr[28]*rdxr2; 
  outr[29] += incr[29]*rdxr2; 
  outr[30] += incr[30]*rdxr2; 
  outr[31] += incr[31]*rdxr2; 
  outr[32] += incr[32]*rdxr2; 
  outr[33] += incr[33]*rdxr2; 
  outr[34] += incr[34]*rdxr2; 
  outr[35] += incr[35]*rdxr2; 
  outr[36] += incr[36]*rdxr2; 
  outr[37] += incr[37]*rdxr2; 
  outr[38] += incr[38]*rdxr2; 
  outr[39] += incr[39]*rdxr2; 
  outr[40] += incr[40]*rdxr2; 
  outr[41] += incr[41]*rdxr2; 
  outr[42] += incr[42]*rdxr2; 
  outr[43] += incr[43]*rdxr2; 
  outr[44] += incr[44]*rdxr2; 
  outr[45] += incr[45]*rdxr2; 
  outr[46] += incr[46]*rdxr2; 
  outr[47] += incr[47]*rdxr2; 
  outr[48] += incr[48]*rdxr2; 
  outr[49] += incr[49]*rdxr2; 
  outr[50] += incr[50]*rdxr2; 
  outr[51] += incr[51]*rdxr2; 
  outr[52] += incr[52]*rdxr2; 
  outr[53] += incr[53]*rdxr2; 
  outr[54] += incr[54]*rdxr2; 
  outr[55] += incr[55]*rdxr2; 
  outr[56] += incr[56]*rdxr2; 
  outr[57] += incr[57]*rdxr2; 
  outr[58] += incr[58]*rdxr2; 
  outr[59] += incr[59]*rdxr2; 
  outr[60] += incr[60]*rdxr2; 
  outr[61] += incr[61]*rdxr2; 
  outr[62] += incr[62]*rdxr2; 
  outr[63] += incr[63]*rdxr2; 
  outr[64] += incr[64]*rdxr2; 
  outr[65] += incr[65]*rdxr2; 
  outr[66] += incr[66]*rdxr2; 
  outr[67] += incr[67]*rdxr2; 
  outr[68] += incr[68]*rdxr2; 
  outr[69] += incr[69]*rdxr2; 
  outr[70] += incr[70]*rdxr2; 
  outr[71] += incr[71]*rdxr2; 
  outr[72] += incr[72]*rdxr2; 
  outr[73] += incr[73]*rdxr2; 
  outr[74] += incr[74]*rdxr2; 
  outr[75] += incr[75]*rdxr2; 
  outr[76] += incr[76]*rdxr2; 
  outr[77] += incr[77]*rdxr2; 
  outr[78] += incr[78]*rdxr2; 
  outr[79] += incr[79]*rdxr2; 

  outl[0] += -1.0*incr[0]*rdxl2; 
  outl[1] += incr[1]*rdxl2; 
  outl[2] += -1.0*incr[2]*rdxl2; 
  outl[3] += -1.0*incr[3]*rdxl2; 
  outl[4] += -1.0*incr[4]*rdxl2; 
  outl[5] += incr[5]*rdxl2; 
  outl[6] += incr[6]*rdxl2; 
  outl[7] += -1.0*incr[7]*rdxl2; 
  outl[8] += incr[8]*rdxl2; 
  outl[9] += -1.0*incr[9]*rdxl2; 
  outl[10] += -1.0*incr[10]*rdxl2; 
  outl[11] += -1.0*incr[11]*rdxl2; 
  outl[12] += -1.0*incr[12]*rdxl2; 
  outl[13] += -1.0*incr[13]*rdxl2; 
  outl[14] += -1.0*incr[14]*rdxl2; 
  outl[15] += incr[15]*rdxl2; 
  outl[16] += incr[16]*rdxl2; 
  outl[17] += incr[17]*rdxl2; 
  outl[18] += -1.0*incr[18]*rdxl2; 
  outl[19] += -1.0*incr[19]*rdxl2; 
  outl[20] += incr[20]*rdxl2; 
  outl[21] += -1.0*incr[21]*rdxl2; 
  outl[22] += -1.0*incr[22]*rdxl2; 
  outl[23] += incr[23]*rdxl2; 
  outl[24] += -1.0*incr[24]*rdxl2; 
  outl[25] += -1.0*incr[25]*rdxl2; 
  outl[26] += -1.0*incr[26]*rdxl2; 
  outl[27] += -1.0*incr[27]*rdxl2; 
  outl[28] += incr[28]*rdxl2; 
  outl[29] += -1.0*incr[29]*rdxl2; 
  outl[30] += -1.0*incr[30]*rdxl2; 
  outl[31] += incr[31]*rdxl2; 
  outl[32] += -1.0*incr[32]*rdxl2; 
  outl[33] += -1.0*incr[33]*rdxl2; 
  outl[34] += -1.0*incr[34]*rdxl2; 
  outl[35] += incr[35]*rdxl2; 
  outl[36] += -1.0*incr[36]*rdxl2; 
  outl[37] += incr[37]*rdxl2; 
  outl[38] += incr[38]*rdxl2; 
  outl[39] += -1.0*incr[39]*rdxl2; 
  outl[40] += incr[40]*rdxl2; 
  outl[41] += -1.0*incr[41]*rdxl2; 
  outl[42] += -1.0*incr[42]*rdxl2; 
  outl[43] += incr[43]*rdxl2; 
  outl[44] += -1.0*incr[44]*rdxl2; 
  outl[45] += incr[45]*rdxl2; 
  outl[46] += incr[46]*rdxl2; 
  outl[47] += -1.0*incr[47]*rdxl2; 
  outl[48] += incr[48]*rdxl2; 
  outl[49] += incr[49]*rdxl2; 
  outl[50] += incr[50]*rdxl2; 
  outl[51] += -1.0*incr[51]*rdxl2; 
  outl[52] += incr[52]*rdxl2; 
  outl[53] += -1.0*incr[53]*rdxl2; 
  outl[54] += incr[54]*rdxl2; 
  outl[55] += -1.0*incr[55]*rdxl2; 
  outl[56] += -1.0*incr[56]*rdxl2; 
  outl[57] += incr[57]*rdxl2; 
  outl[58] += -1.0*incr[58]*rdxl2; 
  outl[59] += -1.0*incr[59]*rdxl2; 
  outl[60] += -1.0*incr[60]*rdxl2; 
  outl[61] += incr[61]*rdxl2; 
  outl[62] += incr[62]*rdxl2; 
  outl[63] += incr[63]*rdxl2; 
  outl[64] += incr[64]*rdxl2; 
  outl[65] += incr[65]*rdxl2; 
  outl[66] += incr[66]*rdxl2; 
  outl[67] += incr[67]*rdxl2; 
  outl[68] += incr[68]*rdxl2; 
  outl[69] += incr[69]*rdxl2; 
  outl[70] += -1.0*incr[70]*rdxl2; 
  outl[71] += incr[71]*rdxl2; 
  outl[72] += -1.0*incr[72]*rdxl2; 
  outl[73] += incr[73]*rdxl2; 
  outl[74] += incr[74]*rdxl2; 
  outl[75] += -1.0*incr[75]*rdxl2; 
  outl[76] += incr[76]*rdxl2; 
  outl[77] += incr[77]*rdxl2; 
  outl[78] += incr[78]*rdxl2; 
  outl[79] += incr[79]*rdxl2; 
  } else { 
  incr[0] = dxvr[1]*((-0.3818813079129866*fr[48])+0.3227486121839514*fr[19]-0.25*fr[5]+0.1443375672974065*fr[2])+wr[1]*((-1.322875655532295*fr[31])+1.118033988749895*fr[11]-0.8660254037844386*fr[1]+0.5*fr[0]); 
  incr[1] = dxvr[1]*(0.6614378277661477*fr[48]-0.5590169943749476*fr[19]+0.4330127018922193*fr[5]-0.25*fr[2])+wr[1]*(2.29128784747792*fr[31]-1.936491673103709*fr[11]+1.5*fr[1]-0.8660254037844386*fr[0]); 
  incr[2] = wr[1]*((-1.322875655532295*fr[48])+1.118033988749895*fr[19]-0.8660254037844386*fr[5]+0.5*fr[2])+dxvr[1]*((-0.3818813079129867*fr[31])-0.223606797749979*fr[20]+0.1290994448735806*fr[12]+0.3227486121839515*fr[11]-0.25*fr[1]+0.1443375672974065*fr[0]); 
  incr[3] = dxvr[1]*((-0.3818813079129867*fr[64])+0.3227486121839515*fr[36]-0.25*fr[15]+0.1443375672974065*fr[7])+wr[1]*((-1.322875655532295*fr[50])+1.118033988749895*fr[21]-0.8660254037844386*fr[6]+0.5*fr[3]); 
  incr[4] = dxvr[1]*((-0.3818813079129867*fr[67])+0.3227486121839515*fr[39]-0.25*fr[16]+0.1443375672974065*fr[9])+wr[1]*((-1.322875655532295*fr[54])+1.118033988749895*fr[25]-0.8660254037844386*fr[8]+0.5*fr[4]); 
  incr[5] = wr[1]*(2.29128784747792*fr[48]-1.936491673103709*fr[19]+1.5*fr[5]-0.8660254037844386*fr[2])+dxvr[1]*(0.6614378277661477*fr[31]+0.3872983346207417*fr[20]-0.223606797749979*fr[12]-0.5590169943749475*fr[11]+0.4330127018922193*fr[1]-0.25*fr[0]); 
  incr[6] = dxvr[1]*(0.6614378277661477*fr[64]-0.5590169943749475*fr[36]+0.4330127018922193*fr[15]-0.25*fr[7])+wr[1]*(2.29128784747792*fr[50]-1.936491673103709*fr[21]+1.5*fr[6]-0.8660254037844386*fr[3]); 
  incr[7] = wr[1]*((-1.322875655532295*fr[64])+1.118033988749895*fr[36]-0.8660254037844386*fr[15]+0.5*fr[7])+dxvr[1]*((-0.3818813079129866*fr[50])-0.223606797749979*fr[37]+0.1290994448735805*fr[22]+0.3227486121839514*fr[21]-0.25*fr[6]+0.1443375672974065*fr[3]); 
  incr[8] = dxvr[1]*(0.6614378277661477*fr[67]-0.5590169943749475*fr[39]+0.4330127018922193*fr[16]-0.25*fr[9])+wr[1]*(2.29128784747792*fr[54]-1.936491673103709*fr[25]+1.5*fr[8]-0.8660254037844386*fr[4]); 
  incr[9] = wr[1]*((-1.322875655532295*fr[67])+1.118033988749895*fr[39]-0.8660254037844386*fr[16]+0.5*fr[9])+dxvr[1]*((-0.3818813079129866*fr[54])-0.223606797749979*fr[40]+0.1290994448735805*fr[26]+0.3227486121839514*fr[25]-0.25*fr[8]+0.1443375672974065*fr[4]); 
  incr[10] = dxvr[1]*((-0.3818813079129866*fr[76])+0.3227486121839514*fr[60]-0.25*fr[35]+0.1443375672974065*fr[18])+wr[1]*((-1.322875655532295*fr[69])+1.118033988749895*fr[41]-0.8660254037844386*fr[17]+0.5*fr[10]); 
  incr[11] = dxvr[1]*((-0.8539125638299665*fr[48])+0.7216878364870323*fr[19]-0.5590169943749475*fr[5]+0.3227486121839515*fr[2])+wr[1]*((-2.958039891549809*fr[31])+2.5*fr[11]-1.936491673103709*fr[1]+1.118033988749895*fr[0]); 
  incr[12] = dxvr[1]*((-0.2195775164134199*fr[49])-0.3415650255319865*fr[48]+0.1267731382092775*fr[32]+0.2886751345948129*fr[19]-0.223606797749979*fr[5]+0.1290994448735806*fr[2])+wr[1]*(0.5*fr[12]-0.8660254037844387*fr[20]); 
  incr[13] = dxvr[1]*(0.1443375672974064*fr[24]-0.25*fr[38])+wr[1]*(0.5*fr[13]-0.8660254037844387*fr[23]); 
  incr[14] = dxvr[1]*(0.1443375672974064*fr[29]-0.25*fr[45])+wr[1]*(0.5*fr[14]-0.8660254037844387*fr[28]); 
  incr[15] = wr[1]*(2.29128784747792*fr[64]-1.936491673103709*fr[36]+1.5*fr[15]-0.8660254037844386*fr[7])+dxvr[1]*(0.6614378277661477*fr[50]+0.3872983346207416*fr[37]-0.223606797749979*fr[22]-0.5590169943749476*fr[21]+0.4330127018922193*fr[6]-0.25*fr[3]); 
  incr[16] = wr[1]*(2.29128784747792*fr[67]-1.936491673103709*fr[39]+1.5*fr[16]-0.8660254037844386*fr[9])+dxvr[1]*(0.6614378277661477*fr[54]+0.3872983346207416*fr[40]-0.223606797749979*fr[26]-0.5590169943749476*fr[25]+0.4330127018922193*fr[8]-0.25*fr[4]); 
  incr[17] = dxvr[1]*(0.6614378277661477*fr[76]-0.5590169943749476*fr[60]+0.4330127018922193*fr[35]-0.25*fr[18])+wr[1]*(2.29128784747792*fr[69]-1.936491673103709*fr[41]+1.5*fr[17]-0.8660254037844386*fr[10]); 
  incr[18] = wr[1]*((-1.322875655532295*fr[76])+1.118033988749895*fr[60]-0.8660254037844386*fr[35]+0.5*fr[18])+dxvr[1]*((-0.3818813079129867*fr[69])-0.223606797749979*fr[61]+0.1290994448735806*fr[42]+0.3227486121839515*fr[41]-0.25*fr[17]+0.1443375672974065*fr[10]); 
  incr[19] = wr[1]*((-2.958039891549808*fr[48])+2.5*fr[19]-1.936491673103709*fr[5]+1.118033988749895*fr[2])+dxvr[1]*((-0.8539125638299666*fr[31])-0.5*fr[20]+0.2886751345948129*fr[12]+0.7216878364870323*fr[11]-0.5590169943749476*fr[1]+0.3227486121839514*fr[0]); 
  incr[20] = dxvr[1]*(0.3803194146278325*fr[49]+0.5916079783099615*fr[48]-0.2195775164134199*fr[32]-0.5*fr[19]+0.3872983346207417*fr[5]-0.223606797749979*fr[2])+wr[1]*(1.5*fr[20]-0.8660254037844387*fr[12]); 
  incr[21] = dxvr[1]*((-0.8539125638299666*fr[64])+0.7216878364870323*fr[36]-0.5590169943749476*fr[15]+0.3227486121839514*fr[7])+wr[1]*((-2.958039891549808*fr[50])+2.5*fr[21]-1.936491673103709*fr[6]+1.118033988749895*fr[3]); 
  incr[22] = dxvr[1]*((-0.2195775164134199*fr[65])-0.3415650255319866*fr[64]+0.1267731382092775*fr[51]+0.2886751345948129*fr[36]-0.223606797749979*fr[15]+0.1290994448735805*fr[7])+wr[1]*(0.5*fr[22]-0.8660254037844387*fr[37]); 
  incr[23] = dxvr[1]*(0.4330127018922194*fr[38]-0.25*fr[24])+wr[1]*(1.5*fr[23]-0.8660254037844387*fr[13]); 
  incr[24] = wr[1]*(0.5*fr[24]-0.8660254037844387*fr[38])+dxvr[1]*(0.1443375672974064*fr[13]-0.25*fr[23]); 
  incr[25] = dxvr[1]*((-0.8539125638299666*fr[67])+0.7216878364870323*fr[39]-0.5590169943749476*fr[16]+0.3227486121839514*fr[9])+wr[1]*((-2.958039891549808*fr[54])+2.5*fr[25]-1.936491673103709*fr[8]+1.118033988749895*fr[4]); 
  incr[26] = dxvr[1]*((-0.2195775164134199*fr[68])-0.3415650255319866*fr[67]+0.1267731382092775*fr[55]+0.2886751345948129*fr[39]-0.223606797749979*fr[16]+0.1290994448735805*fr[9])+wr[1]*(0.5*fr[26]-0.8660254037844387*fr[40]); 
  incr[27] = dxvr[1]*(0.1443375672974064*fr[44]-0.25*fr[62])+wr[1]*(0.5*fr[27]-0.8660254037844387*fr[43]); 
  incr[28] = dxvr[1]*(0.4330127018922194*fr[45]-0.25*fr[29])+wr[1]*(1.5*fr[28]-0.8660254037844387*fr[14]); 
  incr[29] = wr[1]*(0.5*fr[29]-0.8660254037844387*fr[45])+dxvr[1]*(0.1443375672974064*fr[14]-0.25*fr[28]); 
  incr[30] = dxvr[1]*(0.1443375672974064*fr[47]-0.25*fr[63])+wr[1]*(0.5*fr[30]-0.8660254037844387*fr[46]); 
  incr[31] = dxvr[1]*(1.010362971081845*fr[48]-0.8539125638299666*fr[19]+0.6614378277661477*fr[5]-0.3818813079129867*fr[2])+wr[1]*(3.5*fr[31]-2.958039891549809*fr[11]+2.29128784747792*fr[1]-1.322875655532295*fr[0]); 
  incr[32] = wr[1]*(0.5*fr[32]-0.8660254037844386*fr[49])+dxvr[1]*(0.1267731382092775*fr[12]-0.2195775164134199*fr[20]); 
  incr[33] = dxvr[1]*(0.1443375672974064*fr[53]-0.25*fr[66])+wr[1]*(0.5*fr[33]-0.8660254037844386*fr[52]); 
  incr[34] = dxvr[1]*(0.1443375672974064*fr[58]-0.25*fr[73])+wr[1]*(0.5*fr[34]-0.8660254037844386*fr[57]); 
  incr[35] = wr[1]*(2.29128784747792*fr[76]-1.936491673103709*fr[60]+1.5*fr[35]-0.8660254037844386*fr[18])+dxvr[1]*(0.6614378277661477*fr[69]+0.3872983346207417*fr[61]-0.223606797749979*fr[42]-0.5590169943749475*fr[41]+0.4330127018922193*fr[17]-0.25*fr[10]); 
  incr[36] = wr[1]*((-2.958039891549809*fr[64])+2.5*fr[36]-1.936491673103709*fr[15]+1.118033988749895*fr[7])+dxvr[1]*((-0.8539125638299665*fr[50])-0.5*fr[37]+0.2886751345948129*fr[22]+0.7216878364870323*fr[21]-0.5590169943749475*fr[6]+0.3227486121839515*fr[3]); 
  incr[37] = dxvr[1]*(0.3803194146278324*fr[65]+0.5916079783099616*fr[64]-0.2195775164134199*fr[51]-0.5*fr[36]+0.3872983346207416*fr[15]-0.223606797749979*fr[7])+wr[1]*(1.5*fr[37]-0.8660254037844387*fr[22]); 
  incr[38] = wr[1]*(1.5*fr[38]-0.8660254037844387*fr[24])+dxvr[1]*(0.4330127018922194*fr[23]-0.25*fr[13]); 
  incr[39] = wr[1]*((-2.958039891549809*fr[67])+2.5*fr[39]-1.936491673103709*fr[16]+1.118033988749895*fr[9])+dxvr[1]*((-0.8539125638299665*fr[54])-0.5*fr[40]+0.2886751345948129*fr[26]+0.7216878364870323*fr[25]-0.5590169943749475*fr[8]+0.3227486121839515*fr[4]); 
  incr[40] = dxvr[1]*(0.3803194146278324*fr[68]+0.5916079783099616*fr[67]-0.2195775164134199*fr[55]-0.5*fr[39]+0.3872983346207416*fr[16]-0.223606797749979*fr[9])+wr[1]*(1.5*fr[40]-0.8660254037844387*fr[26]); 
  incr[41] = dxvr[1]*((-0.8539125638299665*fr[76])+0.7216878364870323*fr[60]-0.5590169943749475*fr[35]+0.3227486121839515*fr[18])+wr[1]*((-2.958039891549809*fr[69])+2.5*fr[41]-1.936491673103709*fr[17]+1.118033988749895*fr[10]); 
  incr[42] = dxvr[1]*((-0.2195775164134199*fr[77])-0.3415650255319865*fr[76]+0.1267731382092775*fr[70]+0.2886751345948129*fr[60]-0.223606797749979*fr[35]+0.1290994448735806*fr[18])+wr[1]*(0.5*fr[42]-0.8660254037844387*fr[61]); 
  incr[43] = dxvr[1]*(0.4330127018922194*fr[62]-0.25*fr[44])+wr[1]*(1.5*fr[43]-0.8660254037844387*fr[27]); 
  incr[44] = wr[1]*(0.5*fr[44]-0.8660254037844387*fr[62])+dxvr[1]*(0.1443375672974064*fr[27]-0.25*fr[43]); 
  incr[45] = wr[1]*(1.5*fr[45]-0.8660254037844387*fr[29])+dxvr[1]*(0.4330127018922194*fr[28]-0.25*fr[14]); 
  incr[46] = dxvr[1]*(0.4330127018922194*fr[63]-0.25*fr[47])+wr[1]*(1.5*fr[46]-0.8660254037844387*fr[30]); 
  incr[47] = wr[1]*(0.5*fr[47]-0.8660254037844387*fr[63])+dxvr[1]*(0.1443375672974064*fr[30]-0.25*fr[46]); 
  incr[48] = wr[1]*(3.5*fr[48]-2.958039891549808*fr[19]+2.29128784747792*fr[5]-1.322875655532295*fr[2])+dxvr[1]*(1.010362971081845*fr[31]+0.5916079783099615*fr[20]-0.3415650255319865*fr[12]-0.8539125638299665*fr[11]+0.6614378277661477*fr[1]-0.3818813079129866*fr[0]); 
  incr[49] = wr[1]*(1.5*fr[49]-0.8660254037844386*fr[32])+dxvr[1]*(0.3803194146278325*fr[20]-0.2195775164134199*fr[12]); 
  incr[50] = dxvr[1]*(1.010362971081845*fr[64]-0.8539125638299665*fr[36]+0.6614378277661477*fr[15]-0.3818813079129866*fr[7])+wr[1]*(3.5*fr[50]-2.958039891549808*fr[21]+2.29128784747792*fr[6]-1.322875655532295*fr[3]); 
  incr[51] = wr[1]*(0.5*fr[51]-0.8660254037844386*fr[65])+dxvr[1]*(0.1267731382092775*fr[22]-0.2195775164134199*fr[37]); 
  incr[52] = dxvr[1]*(0.4330127018922193*fr[66]-0.25*fr[53])+wr[1]*(1.5*fr[52]-0.8660254037844386*fr[33]); 
  incr[53] = wr[1]*(0.5*fr[53]-0.8660254037844386*fr[66])+dxvr[1]*(0.1443375672974064*fr[33]-0.25*fr[52]); 
  incr[54] = dxvr[1]*(1.010362971081845*fr[67]-0.8539125638299665*fr[39]+0.6614378277661477*fr[16]-0.3818813079129866*fr[9])+wr[1]*(3.5*fr[54]-2.958039891549808*fr[25]+2.29128784747792*fr[8]-1.322875655532295*fr[4]); 
  incr[55] = wr[1]*(0.5*fr[55]-0.8660254037844386*fr[68])+dxvr[1]*(0.1267731382092775*fr[26]-0.2195775164134199*fr[40]); 
  incr[56] = dxvr[1]*(0.1443375672974064*fr[72]-0.25*fr[78])+wr[1]*(0.5*fr[56]-0.8660254037844386*fr[71]); 
  incr[57] = dxvr[1]*(0.4330127018922193*fr[73]-0.25*fr[58])+wr[1]*(1.5*fr[57]-0.8660254037844386*fr[34]); 
  incr[58] = wr[1]*(0.5*fr[58]-0.8660254037844386*fr[73])+dxvr[1]*(0.1443375672974064*fr[34]-0.25*fr[57]); 
  incr[59] = dxvr[1]*(0.1443375672974064*fr[75]-0.25*fr[79])+wr[1]*(0.5*fr[59]-0.8660254037844386*fr[74]); 
  incr[60] = wr[1]*((-2.958039891549808*fr[76])+2.5*fr[60]-1.936491673103709*fr[35]+1.118033988749895*fr[18])+dxvr[1]*((-0.8539125638299666*fr[69])-0.5*fr[61]+0.2886751345948129*fr[42]+0.7216878364870323*fr[41]-0.5590169943749476*fr[17]+0.3227486121839514*fr[10]); 
  incr[61] = dxvr[1]*(0.3803194146278325*fr[77]+0.5916079783099615*fr[76]-0.2195775164134199*fr[70]-0.5*fr[60]+0.3872983346207417*fr[35]-0.223606797749979*fr[18])+wr[1]*(1.5*fr[61]-0.8660254037844387*fr[42]); 
  incr[62] = wr[1]*(1.5*fr[62]-0.8660254037844387*fr[44])+dxvr[1]*(0.4330127018922194*fr[43]-0.25*fr[27]); 
  incr[63] = wr[1]*(1.5*fr[63]-0.8660254037844387*fr[47])+dxvr[1]*(0.4330127018922194*fr[46]-0.25*fr[30]); 
  incr[64] = wr[1]*(3.5*fr[64]-2.958039891549809*fr[36]+2.29128784747792*fr[15]-1.322875655532295*fr[7])+dxvr[1]*(1.010362971081845*fr[50]+0.5916079783099616*fr[37]-0.3415650255319866*fr[22]-0.8539125638299666*fr[21]+0.6614378277661477*fr[6]-0.3818813079129867*fr[3]); 
  incr[65] = wr[1]*(1.5*fr[65]-0.8660254037844386*fr[51])+dxvr[1]*(0.3803194146278324*fr[37]-0.2195775164134199*fr[22]); 
  incr[66] = wr[1]*(1.5*fr[66]-0.8660254037844386*fr[53])+dxvr[1]*(0.4330127018922193*fr[52]-0.25*fr[33]); 
  incr[67] = wr[1]*(3.5*fr[67]-2.958039891549809*fr[39]+2.29128784747792*fr[16]-1.322875655532295*fr[9])+dxvr[1]*(1.010362971081845*fr[54]+0.5916079783099616*fr[40]-0.3415650255319866*fr[26]-0.8539125638299666*fr[25]+0.6614378277661477*fr[8]-0.3818813079129867*fr[4]); 
  incr[68] = wr[1]*(1.5*fr[68]-0.8660254037844386*fr[55])+dxvr[1]*(0.3803194146278324*fr[40]-0.2195775164134199*fr[26]); 
  incr[69] = dxvr[1]*(1.010362971081845*fr[76]-0.8539125638299666*fr[60]+0.6614378277661477*fr[35]-0.3818813079129867*fr[18])+wr[1]*(3.5*fr[69]-2.958039891549809*fr[41]+2.29128784747792*fr[17]-1.322875655532295*fr[10]); 
  incr[70] = wr[1]*(0.5*fr[70]-0.8660254037844386*fr[77])+dxvr[1]*(0.1267731382092775*fr[42]-0.2195775164134199*fr[61]); 
  incr[71] = dxvr[1]*(0.4330127018922193*fr[78]-0.25*fr[72])+wr[1]*(1.5*fr[71]-0.8660254037844386*fr[56]); 
  incr[72] = wr[1]*(0.5*fr[72]-0.8660254037844386*fr[78])+dxvr[1]*(0.1443375672974064*fr[56]-0.25*fr[71]); 
  incr[73] = wr[1]*(1.5*fr[73]-0.8660254037844386*fr[58])+dxvr[1]*(0.4330127018922193*fr[57]-0.25*fr[34]); 
  incr[74] = dxvr[1]*(0.4330127018922193*fr[79]-0.25*fr[75])+wr[1]*(1.5*fr[74]-0.8660254037844386*fr[59]); 
  incr[75] = wr[1]*(0.5*fr[75]-0.8660254037844386*fr[79])+dxvr[1]*(0.1443375672974064*fr[59]-0.25*fr[74]); 
  incr[76] = wr[1]*(3.5*fr[76]-2.958039891549808*fr[60]+2.29128784747792*fr[35]-1.322875655532295*fr[18])+dxvr[1]*(1.010362971081845*fr[69]+0.5916079783099615*fr[61]-0.3415650255319865*fr[42]-0.8539125638299665*fr[41]+0.6614378277661477*fr[17]-0.3818813079129866*fr[10]); 
  incr[77] = wr[1]*(1.5*fr[77]-0.8660254037844386*fr[70])+dxvr[1]*(0.3803194146278325*fr[61]-0.2195775164134199*fr[42]); 
  incr[78] = wr[1]*(1.5*fr[78]-0.8660254037844386*fr[72])+dxvr[1]*(0.4330127018922193*fr[71]-0.25*fr[56]); 
  incr[79] = wr[1]*(1.5*fr[79]-0.8660254037844386*fr[75])+dxvr[1]*(0.4330127018922193*fr[74]-0.25*fr[59]); 

  outr[0] += incr[0]*rdxr2; 
  outr[1] += incr[1]*rdxr2; 
  outr[2] += incr[2]*rdxr2; 
  outr[3] += incr[3]*rdxr2; 
  outr[4] += incr[4]*rdxr2; 
  outr[5] += incr[5]*rdxr2; 
  outr[6] += incr[6]*rdxr2; 
  outr[7] += incr[7]*rdxr2; 
  outr[8] += incr[8]*rdxr2; 
  outr[9] += incr[9]*rdxr2; 
  outr[10] += incr[10]*rdxr2; 
  outr[11] += incr[11]*rdxr2; 
  outr[12] += incr[12]*rdxr2; 
  outr[13] += incr[13]*rdxr2; 
  outr[14] += incr[14]*rdxr2; 
  outr[15] += incr[15]*rdxr2; 
  outr[16] += incr[16]*rdxr2; 
  outr[17] += incr[17]*rdxr2; 
  outr[18] += incr[18]*rdxr2; 
  outr[19] += incr[19]*rdxr2; 
  outr[20] += incr[20]*rdxr2; 
  outr[21] += incr[21]*rdxr2; 
  outr[22] += incr[22]*rdxr2; 
  outr[23] += incr[23]*rdxr2; 
  outr[24] += incr[24]*rdxr2; 
  outr[25] += incr[25]*rdxr2; 
  outr[26] += incr[26]*rdxr2; 
  outr[27] += incr[27]*rdxr2; 
  outr[28] += incr[28]*rdxr2; 
  outr[29] += incr[29]*rdxr2; 
  outr[30] += incr[30]*rdxr2; 
  outr[31] += incr[31]*rdxr2; 
  outr[32] += incr[32]*rdxr2; 
  outr[33] += incr[33]*rdxr2; 
  outr[34] += incr[34]*rdxr2; 
  outr[35] += incr[35]*rdxr2; 
  outr[36] += incr[36]*rdxr2; 
  outr[37] += incr[37]*rdxr2; 
  outr[38] += incr[38]*rdxr2; 
  outr[39] += incr[39]*rdxr2; 
  outr[40] += incr[40]*rdxr2; 
  outr[41] += incr[41]*rdxr2; 
  outr[42] += incr[42]*rdxr2; 
  outr[43] += incr[43]*rdxr2; 
  outr[44] += incr[44]*rdxr2; 
  outr[45] += incr[45]*rdxr2; 
  outr[46] += incr[46]*rdxr2; 
  outr[47] += incr[47]*rdxr2; 
  outr[48] += incr[48]*rdxr2; 
  outr[49] += incr[49]*rdxr2; 
  outr[50] += incr[50]*rdxr2; 
  outr[51] += incr[51]*rdxr2; 
  outr[52] += incr[52]*rdxr2; 
  outr[53] += incr[53]*rdxr2; 
  outr[54] += incr[54]*rdxr2; 
  outr[55] += incr[55]*rdxr2; 
  outr[56] += incr[56]*rdxr2; 
  outr[57] += incr[57]*rdxr2; 
  outr[58] += incr[58]*rdxr2; 
  outr[59] += incr[59]*rdxr2; 
  outr[60] += incr[60]*rdxr2; 
  outr[61] += incr[61]*rdxr2; 
  outr[62] += incr[62]*rdxr2; 
  outr[63] += incr[63]*rdxr2; 
  outr[64] += incr[64]*rdxr2; 
  outr[65] += incr[65]*rdxr2; 
  outr[66] += incr[66]*rdxr2; 
  outr[67] += incr[67]*rdxr2; 
  outr[68] += incr[68]*rdxr2; 
  outr[69] += incr[69]*rdxr2; 
  outr[70] += incr[70]*rdxr2; 
  outr[71] += incr[71]*rdxr2; 
  outr[72] += incr[72]*rdxr2; 
  outr[73] += incr[73]*rdxr2; 
  outr[74] += incr[74]*rdxr2; 
  outr[75] += incr[75]*rdxr2; 
  outr[76] += incr[76]*rdxr2; 
  outr[77] += incr[77]*rdxr2; 
  outr[78] += incr[78]*rdxr2; 
  outr[79] += incr[79]*rdxr2; 

  outl[0] += -1.0*incr[0]*rdxl2; 
  outl[1] += incr[1]*rdxl2; 
  outl[2] += -1.0*incr[2]*rdxl2; 
  outl[3] += -1.0*incr[3]*rdxl2; 
  outl[4] += -1.0*incr[4]*rdxl2; 
  outl[5] += incr[5]*rdxl2; 
  outl[6] += incr[6]*rdxl2; 
  outl[7] += -1.0*incr[7]*rdxl2; 
  outl[8] += incr[8]*rdxl2; 
  outl[9] += -1.0*incr[9]*rdxl2; 
  outl[10] += -1.0*incr[10]*rdxl2; 
  outl[11] += -1.0*incr[11]*rdxl2; 
  outl[12] += -1.0*incr[12]*rdxl2; 
  outl[13] += -1.0*incr[13]*rdxl2; 
  outl[14] += -1.0*incr[14]*rdxl2; 
  outl[15] += incr[15]*rdxl2; 
  outl[16] += incr[16]*rdxl2; 
  outl[17] += incr[17]*rdxl2; 
  outl[18] += -1.0*incr[18]*rdxl2; 
  outl[19] += -1.0*incr[19]*rdxl2; 
  outl[20] += incr[20]*rdxl2; 
  outl[21] += -1.0*incr[21]*rdxl2; 
  outl[22] += -1.0*incr[22]*rdxl2; 
  outl[23] += incr[23]*rdxl2; 
  outl[24] += -1.0*incr[24]*rdxl2; 
  outl[25] += -1.0*incr[25]*rdxl2; 
  outl[26] += -1.0*incr[26]*rdxl2; 
  outl[27] += -1.0*incr[27]*rdxl2; 
  outl[28] += incr[28]*rdxl2; 
  outl[29] += -1.0*incr[29]*rdxl2; 
  outl[30] += -1.0*incr[30]*rdxl2; 
  outl[31] += incr[31]*rdxl2; 
  outl[32] += -1.0*incr[32]*rdxl2; 
  outl[33] += -1.0*incr[33]*rdxl2; 
  outl[34] += -1.0*incr[34]*rdxl2; 
  outl[35] += incr[35]*rdxl2; 
  outl[36] += -1.0*incr[36]*rdxl2; 
  outl[37] += incr[37]*rdxl2; 
  outl[38] += incr[38]*rdxl2; 
  outl[39] += -1.0*incr[39]*rdxl2; 
  outl[40] += incr[40]*rdxl2; 
  outl[41] += -1.0*incr[41]*rdxl2; 
  outl[42] += -1.0*incr[42]*rdxl2; 
  outl[43] += incr[43]*rdxl2; 
  outl[44] += -1.0*incr[44]*rdxl2; 
  outl[45] += incr[45]*rdxl2; 
  outl[46] += incr[46]*rdxl2; 
  outl[47] += -1.0*incr[47]*rdxl2; 
  outl[48] += incr[48]*rdxl2; 
  outl[49] += incr[49]*rdxl2; 
  outl[50] += incr[50]*rdxl2; 
  outl[51] += -1.0*incr[51]*rdxl2; 
  outl[52] += incr[52]*rdxl2; 
  outl[53] += -1.0*incr[53]*rdxl2; 
  outl[54] += incr[54]*rdxl2; 
  outl[55] += -1.0*incr[55]*rdxl2; 
  outl[56] += -1.0*incr[56]*rdxl2; 
  outl[57] += incr[57]*rdxl2; 
  outl[58] += -1.0*incr[58]*rdxl2; 
  outl[59] += -1.0*incr[59]*rdxl2; 
  outl[60] += -1.0*incr[60]*rdxl2; 
  outl[61] += incr[61]*rdxl2; 
  outl[62] += incr[62]*rdxl2; 
  outl[63] += incr[63]*rdxl2; 
  outl[64] += incr[64]*rdxl2; 
  outl[65] += incr[65]*rdxl2; 
  outl[66] += incr[66]*rdxl2; 
  outl[67] += incr[67]*rdxl2; 
  outl[68] += incr[68]*rdxl2; 
  outl[69] += incr[69]*rdxl2; 
  outl[70] += -1.0*incr[70]*rdxl2; 
  outl[71] += incr[71]*rdxl2; 
  outl[72] += -1.0*incr[72]*rdxl2; 
  outl[73] += incr[73]*rdxl2; 
  outl[74] += incr[74]*rdxl2; 
  outl[75] += -1.0*incr[75]*rdxl2; 
  outl[76] += incr[76]*rdxl2; 
  outl[77] += incr[77]*rdxl2; 
  outl[78] += incr[78]*rdxl2; 
  outl[79] += incr[79]*rdxl2; 
  } 
} 
