#ifndef DTMB_TOP_H
#define DTMB_TOP_H

#include <stdio.h>

#ifndef _WIN32
	typedef long long Int64;
	typedef short Int16;
	typedef char Int8;

	typedef unsigned long long Uint64;
	typedef unsigned short Uint16;
	typedef unsigned char Uint8;

#else
	typedef __int64 Int64;
	typedef __int16 Int16;
	typedef char Int8;

	typedef unsigned __int64 Uint64;
	typedef unsigned __int16 Uint16;
	typedef unsigned char Uint8;

	#if _MSC_VER > 1000
		#pragma once
		#pragma warning (disable: 4996)
	#endif // _MSC_VER > 1000

#endif

#define MAX_FILE_NAME_LEN           256

#define CHECKPRECISION_SIGNED(Y,N) (Y = (((Y)&((Int64)1<<(N-1)))?((Y)&(((Int64)1<<N)-1))+(-(Int64)1<<N):((Y)&(((Int64)1<<N)-1))))
#define CHECKPRECISION_UNSIGNED(Y,N) (Y = (Y)&(((Int64)1<<(N)) - 1))     
#define CRITICAL_CHECKPRECISION_SIGNED(Y,N)  {if( (Y < (((Int64)1<<(N-1)))) && ( Y>= (-(Int64)1<<(N-1)))) {} else printf("\nWarning : data overflowed %d, at file %s, line %d", Y, __FILE__, __LINE__); CHECKPRECISION_SIGNED(Y,N);}                        
#define CRITICAL_CHECKPRECISION_UNSIGNED(Y,N) {if (Y &(-(Int64)1<<N)) printf("\nWarning : data overflowed %d, at file %s, line %d", Y, __FILE__, __LINE__); CHECKPRECISION_UNSIGNED(Y,N); }               

#define SATURATE_SIGNED(Y,N)  (Y = ((Y) > (((Int64)1<<((N)-1))-1)) ? (((Int64)1<<((N)-1))-1) : (((Y) < (-(Int64)1<<((N)-1))) ? (-(Int64)1<<((N)-1)) : (Y)))
#define SATURATE_SIGNED1(Y,N) (Y = ((Y) > (((Int64)1<<((N)-1))-1)) ? (((Int64)1<<((N)-1))-1) : (((Y) < ((-(Int64)1<<((N)-1))+1)) ? (-(Int64)1<<((N)-1))+1 : (Y)))
#define SATURATE_UNSIGNED(Y,N) (Y = ((Y) > (((Int64)1<<(N))-1)) ? (((Int64)1<<(N))-1) : ((Y)<0)?0:(Y))
#define CRITICAL_SATURATE_SIGNED(Y,N)  {if((Y) > (((Int64)1<<((N)-1))-1) || (Y) < (-(Int64)1<<((N)-1))) printf("\nWarning : data saturated %d, file %s, line %d", Y, __FILE__, __LINE__); SATURATE_SIGNED(Y,N); }
#define CRITICAL_SATURATE_UNSIGNED(Y,N) {if((Y) > (((Int64)1<<(N))-1)||(Y)<0) printf("\nWarning : data saturated %d, file %s, line %d", Y, __FILE__, __LINE__); SATURATE_UNSIGNED(Y,N); }

/*
#define CHECKPRECISION_SIGNED(Y,N) (Y = (((Y)&(1<<(N-1)))?((Y)&((1<<N)-1))+(-1<<N):((Y)&((1<<N)-1))))
#define CHECKPRECISION_UNSIGNED(Y,N) (Y = (Y)&((1<<(N)) - 1))     
#define CRITICAL_CHECKPRECISION_SIGNED(Y,N)  {if( (Y < ((1<<(N-1)))) && ( Y>= (-1<<(N-1)))) {} else printf("\nWarning : data overflowed %d, at file %s, line %d", Y, __FILE__, __LINE__); CHECKPRECISION_SIGNED(Y,N);}                        
#define CRITICAL_CHECKPRECISION_UNSIGNED(Y,N) {if (Y &(-1<<N)) printf("\nWarning : data overflowed %d, at file %s, line %d", Y, __FILE__, __LINE__); CHECKPRECISION_UNSIGNED(Y,N); }               
#define SATURATE_SIGNED(Y,N) (Y = ((Y) > ((1<<((N)-1))-1)) ? ((1<<((N)-1))-1) : (((Y) < (-1<<((N)-1))) ? (-1<<((N)-1)) : (Y)))
#define SATURATE_SIGNED1(Y,N) (Y = ((Y) > ((1<<((N)-1))-1)) ? ((1<<((N)-1))-1) : (((Y) < ((-1<<((N)-1))+1)) ? (-1<<((N)-1))+1 : (Y)))
#define SATURATE_UNSIGNED(Y,N) (Y = ((Y) > ((1<<(N))-1)) ? ((1<<(N))-1) : ((Y)<0)?0:(Y))
#define CRITICAL_SATURATE_SIGNED(Y,N)  {if((Y) > ((1<<((N)-1))-1) || (Y) < (-1<<((N)-1))) printf("\nWarning : data saturated %d, file %s, line %d", Y, __FILE__, __LINE__); SATURATE_SIGNED(Y,N); }
#define CRITICAL_SATURATE_UNSIGNED(Y,N) {if((Y) > ((1<<(N))-1)||(Y)<0) printf("\nWarning : data saturated %d, file %s, line %d", Y, __FILE__, __LINE__); SATURATE_UNSIGNED(Y,N); }
#define SIGN_EXT(Y,N) (Y = ((Y)&(1<<(N-1)))?(Y)|(-1<<N):(Y))
*/

#endif



