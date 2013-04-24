#include "stdafx.h"
#include "Data.h"

#include <math.h>


static Data *g_data=NULL;

Data* Data::shareData(LPCTSTR m_file_name)
{
	if(g_data==NULL)
	{
		if(m_file_name==NULL)
			return NULL;
		g_data=new Data(m_file_name);
	}
	return g_data;
}



Data::Data(LPCTSTR m_file_name)
{
	file_name=m_file_name;
	data_num=0;
	scaling_x=1;
	scaling_y=1;
	scaling_old_x=1;
	scaling_old_y=1;
	display_x=false;
	display_y=false;
	file_offset=0;
	pos_x_offset=0;
	count=0;
}




Data::Data(void)
{
}


Data::~Data(void)
{
}



//配置数据格式
bool Data::configureData(int m_data_num)
{
	data_num=m_data_num;
	pData=(NODE *)malloc(sizeof(NODE)*data_num*MAX_DATA_NUM);
	memset(pData,0,sizeof(NODE)*data_num*MAX_DATA_NUM);

	
	pWriteData=(NODE *)malloc(sizeof(NODE)*data_num*MAX_DATA_NUM);
	memset(pWriteData,0,sizeof(NODE)*data_num*MAX_DATA_NUM);

	
	pTmpData=(NODE *)malloc(sizeof(NODE)*data_num);
	memset(pWriteData,0,sizeof(NODE)*data_num);

	pData_info=(NODE_INFO *)malloc(sizeof(NODE_INFO)*data_num);
	memset(pData_info,0,sizeof(NODE_INFO)*data_num);


	for(int i=0;i<data_num;i++)
	{
		pTmpData[i].data_y=0;
		pTmpData[i].data_x=0;
	}

	return true;
}


//添加数据
bool Data::addData(int index,int data)
{
	pTmpData[index].data_y=data;
	pTmpData[index].data_x=0;
	return true;
}

	//移动到下一周期
bool Data::moveNext()
{
	for(int i=0;i<data_num;i++)
	{
		
		(*(pWriteData+i*MAX_DATA_NUM+count)).data_y=(*(pTmpData+i)).data_y;
	}
	count++;
	if(count==MAX_DATA_NUM)
	{
		//满MAX_NUM_DATA个写入文件
		WriteFile();
		count=0;
		return false;
	}

	return true;
}




//写入文件
bool Data::WriteFile()
{
	CFile file;
	CFileFind finder;

	if(finder.FindFile(file_name))
	{
		file.Open(file_name,CFile::modeWrite|CFile::typeBinary|CFile::shareDenyNone);
	}else
	{
		file.Open(file_name,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary|CFile::shareDenyNone);
	}
	file.SeekToEnd();
	for(int i=0;i<MAX_DATA_NUM;i++)
		for(int j=0;j<data_num;j++)
		{
			file.Write(&((pWriteData+j*MAX_DATA_NUM+i)->data_y), sizeof(int)); 
			
		}

	file.Close();

	return true;
}



//读取文件
bool Data::ReadFile()
{
	CFile file;
	CFileFind finder;

	if(finder.FindFile(file_name))
		{
			file.Open(file_name,CFile::modeRead|CFile::typeBinary|CFile::shareDenyNone);
		}else
		{
			file.Open(file_name,CFile::modeCreate|CFile::modeRead|CFile::typeBinary|CFile::shareDenyNone);
		}

		for(int i=0;i<MAX_DATA_NUM;i++)
			for(int j=0;j<data_num;j++)
			{
				pData[j*MAX_DATA_NUM+i].data_x=i;
				file.Read(&(pData[j*MAX_DATA_NUM+i].data_y), sizeof(int)); 
				file_offset+=4;
			}

	file.Close();



	return true;
}



bool Data::ReadNextFile(FileReadStatus type)
{

	CFile file;
	CFileFind finder;

	if(type==kNext)
		pos_x_offset++;
	int read_end=0;
	if(finder.FindFile(file_name))
		{
			file.Open(file_name,CFile::modeRead|CFile::typeBinary|CFile::shareDenyNone);
		}else
		{
			file.Open(file_name,CFile::modeCreate|CFile::modeRead|CFile::typeBinary|CFile::shareDenyNone);
		}

		if(type==kNext)
			file.Seek(file_offset,CFile::begin);

		for(int i=0;i<MAX_DATA_NUM;i++)
			for(int j=0;j<data_num;j++)
			{
				pData[j*MAX_DATA_NUM+i].data_x=i;
				read_end=file.Read(&(pData[j*MAX_DATA_NUM+i].data_y), sizeof(int));
				if(read_end==0 && j==data_num-1)
				{
					file.Close();
					return true;
				}else if(read_end<4)
				{
					file.Close();
					AfxMessageBox(_T("文件未完结，可能造成数据错误"));
					return false;
				}
				file_offset+=4;
			}

	file.Close();


	return true;
}



//绘制坐标轴，根据放大缩小率决定绘制精度
bool Data::drawXY(int m_index_num,CDC *pDC,CRect rect)
{
	CPen* pPen ; //创建一支新的笔

	pPen=new CPen ;  
	pPen->CreatePen(PS_SOLID,1,RGB(200,200,200));
	CPen *pOldPen=pDC->SelectObject(pPen);
	
	pDC->MoveTo(10,(int)((m_index_num*500+250)*scaling_y));
	pDC->LineTo((int)(MAX_DATA_NUM*scaling_x),(int)((m_index_num*500+250)*scaling_y));
	
	
		
	//显示坐标值
	if(display_x==true)
	{
		int j=0;

			
		pDC->SetTextColor(RGB(0,0,255));
		for(float i=0;i<MAX_DATA_NUM*scaling_x;i+=scaling_x*10)
		{
			if(rect.PtInRect(CPoint((int)(10+i),(int)((m_index_num*500+250)*scaling_y))))
			{
				CString str;
				str.Format(_T("%d"),j+pos_x_offset*MAX_DATA_NUM);
				pDC->TextOutW((int)(5+i),(int)((m_index_num*500+250)*scaling_y+10),str);
				pDC->MoveTo((int)(10+i),(int)((m_index_num*500+250)*scaling_y));
				pDC->LineTo((int)(10+i),(int)((m_index_num*500+250)*scaling_y-10));
			}
			j+=10;
		}
	}


	//纵坐标显示
	pDC->MoveTo(10,(int)((m_index_num*500+250-200)*scaling_y));
	pDC->LineTo(10,(int)((m_index_num*500+250+200)*scaling_y));

	pPen->DeleteObject();
	pDC->SelectObject(pOldPen);
	return true;
}





//获取指定索引的屏幕坐标
bool Data::getPointFromIndex(int m_index_num,   //数据组索引
						int m_index_data,  //数据索引
						int *x1,			  //前一点x坐标
						int *y1,			  //前一点y坐标
						int *x,			  //x坐标
						int *y,			  //y坐标
						int *data          //y值
						)
{
	scalingMatrix(m_index_num,m_index_data);
	translateTransformedMatrix(m_index_num,m_index_data);
	if(m_index_data>0)
	{
		*x1=pData[m_index_num*MAX_DATA_NUM+m_index_data-1].pos_x;
		*y1=pData[m_index_num*MAX_DATA_NUM+m_index_data-1].pos_y;
	}else
	{
		*x1=10;
		*y1=pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_y;
	}

	*x=pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_x;
	*y=pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_y;

	if(display_y==true && ((*y)!=(*y1)))
	{
		*data=pData[m_index_num*MAX_DATA_NUM+m_index_data].data_y;
		return true;
	}
	return false;
}




bool Data::scalingMatrix(int m_index_num,   //数据组索引
					   int m_index_data   //数据索引;
					   )
{


	float mat_t[3][3]={{1,0,0},
					  {0,1,0},
					  {0,0,1}
					};
	int ver[3]={1,1,1};
	float tar[3]={0,0,0};

	//缩放变换
	mat_t[0][0]=scaling_x;
	mat_t[1][1]=400/(float)(abs(pData_info[m_index_num].node_max-pData_info[m_index_num].node_min))*(0-scaling_y);


	


	ver[0]=pData[m_index_num*MAX_DATA_NUM+m_index_data].data_x;
	ver[1]=pData[m_index_num*MAX_DATA_NUM+m_index_data].data_y;

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			tar[i]=tar[i]+ver[j]*mat_t[j][i];
		}
	}

	pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_x=(int)(tar[0]);
	pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_y=(int)(tar[1]);


	return true;
}







bool Data::translateTransformedMatrix(int m_index_num,   //数据组索引
									int m_index_data  //数据索引;
									)
{
	int mat_t[3][3]={{1,0,0},
					 {0,1,0},
					 {0,0,1}
					};
	int ver[3]={1,1,1};
	float tar[3]={0,0,0};

	//平移变换
	mat_t[2][0]=10;
	//add by wyh
	mat_t[2][1]=(int)((/*m_index_num*/pData_info[m_index_num].node_sort*500+250)*scaling_y);


	


	ver[0]=pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_x;
	ver[1]=pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_y;

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			tar[i]=tar[i]+ver[j]*mat_t[j][i];
		}
	}

	pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_x=(int)(tar[0]);
	pData[m_index_num*MAX_DATA_NUM+m_index_data].pos_y=(int)(tar[1]);
	return true;
}



void Data::getScrollRange(long *height,long *weith)
{
	*weith=(long)((500*data_num)*scaling_y);
	*height=(long)(MAX_DATA_NUM*scaling_x);

}





bool Data::configureValueInfo(LPCTSTR value_name, //变量名称
							int ID,				//变量ID，ID0为时钟信号
							int max,			//最大值
							int min,				//最小值
							COLORREF color)
{
	if(ID>=data_num)
		return false;
	
	pData_info[ID].node_name=value_name;
	pData_info[ID].node_id=ID;
	pData_info[ID].node_sort=ID;
	pData_info[ID].node_max=max;
	pData_info[ID].node_min=min;
	pData_info[ID].display=true;
	pData_info[ID].node_len=0;
	pData_info[ID].node_sigh=false;
	pData_info[ID].color=color;


	return true;
}
