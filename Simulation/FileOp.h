#ifndef FILE_OP_H_
#define FILE_OP_H_

#include "DTMBFILEOP.h"

class CFileOp
{
public:
		CFileOp(void);
		~CFileOp(void);
		int InitClassMember(char * base_name);
		Uint64 Transfer_to_OtherType(char type,unsigned int convlen);
		Uint64 Transfer_to_OtherType(char type);
		Uint64 ReadData();

		int      m_vec_len;
		void * * m_vec_buf;

private:
	DTMBFILEOP * m_dtmbfileop;
	char file_base_name[MAX_FILE_NAME_LEN];
	char file_type;
	Data_Align_Type data_align;

	int  vec_num;
	int  * intbit_table;
	int  * bit_table;
	Data_is_Sign * vec_sign_tab;
	bool   vect_align;

	Data_Type data_type;

	char * buf;
	int    buf_size;

	void init_vec_buf(void * * * vec_buf,Data_Type data_type,int vec_num,int vec_len);
	void allocate_vec_buf(void * * * vec_buf,Data_Type data_type,int vec_num,int vec_len);
};

#endif //FILE_OP_H_
