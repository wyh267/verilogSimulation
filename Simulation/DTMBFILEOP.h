// DTMBFILEOP.h: interface for the DTMBFILEOP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DTMBFILEOP_H__7BC9F9F7_62C8_4A6D_9C08_E0EFBA41DBFE__INCLUDED_)
#define AFX_DTMBFILEOP_H__7BC9F9F7_62C8_4A6D_9C08_E0EFBA41DBFE__INCLUDED_



#include "DTMBTop.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>


#define DATABUFF_MAX_RESERVE_SIZE   512
#define Data_num_Display            100000
#define MAX_SAVEFILE_SIZE           1024*1024*1024 //1024*1024*1024
#define MAX_SAVEFILE_NUM            10

typedef enum {Data_Sign=0,Data_Unsigned=1}   Data_is_Sign;
typedef enum {MSB_Align=0,LSB_Align=1}		 Data_Align_Type;
typedef enum {	Bool_Type=0,
				Int8_Type=1,
				Int16_Type=2,
				Int_Type=3,
				Int64_Type=4,
				Double_Type=5} Data_Type;
typedef enum {GetSign = 1, GetInteger =2, GetDot=3 ,GetDecimal=4,GetValidHex=5} get_decimal_state;


#define Verbose 0





class DTMBFILEOP  
{
	typedef struct
	{
		unsigned char * m_buf;
		unsigned int    m_buf_size;
		unsigned int    m_buf_point;
		unsigned int    m_buf_readvalid_point;
	}filebuf_info;
	typedef struct
	{
			int				 vec_num;
			int			 *	 vec_bits;
			int			 *   vec_int_bits;
			Data_is_Sign *	 vec_sign;
			unsigned int	 vec_len;
			void         **  vec_buf;
			Data_Type        buf_data_type;
			bool             m_vect_align;
			unsigned int     m_data_point;
	}vect_info;

	typedef struct
	{
			char			 file_name[MAX_FILE_NAME_LEN];
			char			 file_continue_name[MAX_FILE_NAME_LEN];
			char	**		 file_transfer_name;
			char	**		 file_transfer_continue_name;
			char			 file_type;
			char			 transferfile_type;
			Int64			 m_file_offset;
			unsigned int	 m_data_offset;
			Data_Align_Type  align;
			FILE *			 m_main_file;
			FILE **			 m_transfer_file;
			Int64  *	 m_transfer_file_offset;
			int              m_file_continue_no;
			int  *           m_transferfile_continue_no;
	}file_info;





public:
	DTMBFILEOP();
	DTMBFILEOP(char*file_name,char file_type,int vec_num,int * vec_bits,int*vec_int_bits,Data_is_Sign*vec_sign,unsigned char * f_buf,int f_buf_size);
	DTMBFILEOP(char*file_name,char file_type,int vec_bits,int vec_int_bits,Data_is_Sign vec_sign,unsigned char * f_buf,int f_buf_size);
	virtual ~DTMBFILEOP();

	unsigned int GetFileOffset();
	void SetFileOffset(unsigned int	 file_offset);
	void SetDataBufType(Data_Type		buf_data_type);
	void SetVectAlign(bool				vect_align);
	void SetDataAlign(Data_Align_Type	data_align);
	void SetTransferDataAlign(Data_Align_Type	data_align);

	void InitClassMember();
	void InitFileInfo(char * file_name,char file_type,Data_Align_Type data_align);
	void InitVectInfo(int vec_num,int*vec_bits,int*vec_int_bits,Data_is_Sign*vec_sign);
	void InitFileBufInfo(unsigned char * f_buf,int f_buf_size);


	Uint64 WriteData(void ** vect,unsigned int vec_len,unsigned int data_offset);
	Uint64 WriteData(void ** vect,unsigned int vec_len);
	Uint64 WriteData(void * vect,unsigned int vec_len,unsigned int data_offset);
	Uint64 WriteData(void * vect,unsigned int vec_len);


	Uint64 ReadData(void ** vect,unsigned int vec_len,unsigned int data_offset);
	Uint64 ReadData(void ** vect,unsigned int vec_len);
	Uint64 ReadData(void * vect,unsigned int vec_len,unsigned int data_offset);
	Uint64 ReadData(void * vect,unsigned int vec_len);

	Uint64 GetDataNum();

	Uint64 Transfer_to_OtherType(char file_type,void ** vect,unsigned int vec_len,unsigned int transfer_len,unsigned int data_offset);
	Uint64 Transfer_to_OtherType(char file_type,void ** vect,unsigned int vec_len,unsigned int transfer_len);
	Uint64 Transfer_to_OtherType(char file_type,void *  vect,unsigned int vec_len,unsigned int transfer_len,unsigned int data_offset);
	Uint64 Transfer_to_OtherType(char file_type,void *  vect,unsigned int vec_len,unsigned int transfer_len);

	void RecordSignal(bool  * data,  int vec_bits);
	void RecordSignal(Int8  * data,   int vec_bits);
	void RecordSignal(Int16 * data,   int vec_bits);
	void RecordSignal(int  * data,   int vec_bits);
	void RecordSignal(double  * data,int vec_bits);

	void BeginRecordSignal(char * file_name,unsigned char * f_buf,int f_buf_size);
	void RecordSignal(Uint64  * data,int vec_bits);
	int RecordNextSignal();
	void EndRecordSignal();

	int  GetSignal(bool* data, int bits);
	int  GetSignal(Int16* data, int bits);
	int  GetSignal(Int8* data, int bits);
	int  GetSignal(int* data, int bits);
	int  GetSignal(double* data, int bits);

	int  GetSignSignal(Int16* data, int bits);
	int  GetSignSignal(Int8* data, int bits);
	int  GetSignSignal(int* data, int bits);


	void BeginGetSignal(char * file_name,unsigned char * f_buf,int f_buf_size);
	int  GetSignal(Uint64* data, int bits);
	void GetNextSignal();
	void EndGetSignal();

	void test();
private:

	file_info		m_file_info;
	vect_info		m_vect_info;
	filebuf_info    m_filebuf_info;

	int					m_remain_bits;
	Uint64    m_remain_data;
	bool				m_vect_mem_allocate;
	Uint64	all_data_operate;
	unsigned   int      m_transfer_len;
	Data_Align_Type     m_data_align;
	Data_Align_Type     m_transfer_data_align;


	int  *				m_deci_wid;
	Uint64 *  m_max_int;
	Uint64 *  m_deci_data;
	int *				m_single_data_chars;
	int				 *  m_base_radix;
	Uint64 *  m_max_radix;

	int  *				m_transfer_deci_wid;
	Uint64 *  m_transfer_max_int;
	Uint64 *  m_transfer_deci_data;
	int *				m_transfer_single_data_chars;
	int				 *  m_transfer_base_radix;
	Uint64 *  m_transfer_max_radix;


	Uint64 DTMBFILEOP::GetDataFromVect(Uint64 i,int j,Uint64 * data_out);
	void write_data_to_buf(int j,Uint64  * data);
	void write_remaindata_to_buf();
	int WriteBuf_to_File();
	Uint64 WriteData();

	Uint64 ReadData();
	int Read_File_to_Buf();
	int Read_Data_From_Buf(double * data,int j);
	int Read_Double_Data(double * data);
	int Read_Binary_Data(double * data,int j);
	int Read_Text_Data(double * data,int j);
	int Read_Valid_Decimal(double * data);
	void Complement_to_Double(double * data_float,Uint64 *data_int,int j );
	void SaveData_to_OutBuf(double data_float,Uint64 i,int j);

	Uint64 Transfer_to_OtherType();
	void Initial_TransferFile();
	void Close_TransferFile();
	Uint64 WriteTransferData(int vect_no,Uint64 data_num);
	int WriteBuf_to_TransferFile(int vect_no);
	void write_tramsferdata_to_buf(int j,Uint64  * data);

	void InitVectInfo();
	void InitFileInfo();
	void InitFileBufInfo();
	void ResetClassInfo();
	void gen_txtdata_formtion();
	void gen_transfertxtdata_formtion();
	void free_vecttmp_buf(void * buf);
	void free_vect_buf();


/*
	InitFileInfo(char*filename,char file_type,int Vector_num,int * vec_bits_tab,unsigned int vec_len,
				 int * int_bits_tab,Data_is_Sign * vec_sign_tab,Data_Align_Type	align,Data_Type data_type);
	InitFileInfo(char*filename,char file_type,int Vector_num,int * vec_bits_tab,unsigned int vec_len);
*/
};

#endif // !defined(AFX_DTMBFILEOP_H__7BC9F9F7_62C8_4A6D_9C08_E0EFBA41DBFE__INCLUDED_)


