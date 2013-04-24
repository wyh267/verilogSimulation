#ifndef MY_GLOBAL_H_
#define MY_GLOBAL_H_


#define EC_SEG_LEN 5
#define EC_SEG_NUM 190 //378
#define EC_LENGTH (EC_SEG_LEN*EC_SEG_NUM) 
#define EC_FFT_SHIFT 8 //12
#define EC_FRAC 8
#define EC_INT 8
#define EC_MAG (1<<(EC_FRAC+EC_INT))
#define EC_2MAG (1<<(EC_FRAC+EC_INT+1))

//sub-carrier mode
#define CM_C1       0    
#define CM_C3780    1
#define CM_AUTO    -1

//frame header mode
#define HDR_NC   0       //unknown frame header mode
#define HDR_420  1
#define HDR_595  2
#define HDR_945  3 

 #define GetTime()  -1.0

#define MT_NC      7     //unknown modulation type 
#define MT_4QAM    0
#define MT_16QAM   1
#define MT_32QAM   2
#define MT_64QAM   3
#define MT_4QAMNR  4
#define MT_128QAM  5 
#define MT_256QAM  6

void data_comp_mod(int * * vect,char * str,int num,int ind,int ind_j,...);
void data_comp_mod_lcc(int * * vect,char * str,int en,int num,int ind,int ind_j,...);

#endif //MY_GLOBAL_H_