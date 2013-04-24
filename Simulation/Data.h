#pragma once


//数据格式
typedef struct _node_
{
	int data_x;
	int data_y;
	int pos_x;
	int pos_y;

}NODE,*PNODE;


//数据信息
typedef struct _node_info_
{
	LPCTSTR node_name; //名称
	int node_id;		//ID
	int node_sort;		//排序位置
	COLORREF color;		//颜色
	int node_max;		//最大值
	int node_min;		//最小值
	int node_len;		//位宽
	bool node_sigh;		//是否有符合
	bool display;		//是否显示

}NODE_INFO,*PNODE_INFO;

//最大数据读取长度
#define MAX_DATA_NUM	100000






class Data
{
public:
	Data(void);
	~Data(void);
	Data(LPCTSTR m_file_name);

	typedef enum
	{
		kStart=0,
		kNext,
		kPre
	}FileReadStatus;

	//配置数据格式
	bool configureData(int m_data_num);

	//配置变量信息
	bool configureValueInfo(LPCTSTR value_name, //变量名称
							int ID,				//变量ID，ID0为时钟信号
							int max,			//最大值
							int min,				//最小值
							COLORREF color);

	//读取文件
	bool ReadFile();

	//读取下一段文件
	bool ReadNextFile(FileReadStatus type);


	//文件偏移
	long file_offset;
	//x坐标偏移
	int  pos_x_offset;

	//写入文件
	bool WriteFile();

	//添加数据
	bool addData(int index,int data);

	//移动到下一周期
	bool moveNext();

	//绘制坐标轴，根据放大缩小率决定绘制精度
	bool drawXY(int m_index_num,CDC *pDC,CRect rect);



	//获取指定索引的屏幕坐标
	bool getPointFromIndex(int m_index_num,   //数据组索引
						   int m_index_data,  //数据索引
						   int *x1,			  //前一点x坐标
						   int *y1,			  //前一点y坐标
						   int *x,			  //x坐标
						   int *y,			  //y坐标
						   int *data          //y值
						   );			 


	static Data *shareData(LPCTSTR m_file_name=NULL);


	void scanlingYplus(){scaling_old_y=scaling_y;scaling_y=scaling_y*1.2F;};
	void scanlingYsub(){scaling_old_y=scaling_y;scaling_y=scaling_y*0.8F;};
	void scanlingXplus(){scaling_old_x=scaling_x;scaling_x=scaling_x*1.2F;};
	void scanlingXsub(){scaling_old_x=scaling_x;scaling_x=scaling_x*0.8F;};
	void scalingXY(float sx,float sy){scaling_old_y=scaling_y;scaling_old_x=scaling_x;scaling_x=scaling_x*sx;scaling_y=scaling_y*sy;}
	void scalingUndo(){scaling_x=scaling_old_x;scaling_y=scaling_old_y;};



	//设置坐标值是否显示
	void EnableX(){if(display_x==true)display_x=false;else display_x=true;};
	void EnableY(){if(display_y==true)display_y=false;else display_y=true;};

	void getScrollRange(long *height,long *weith);


public:

	

	//数据个数
	int data_num;
	//数据信息
	NODE_INFO *pData_info;


private:
	LPCTSTR file_name;


	//数据
	NODE *pData;

	//写文件数据
	NODE *pWriteData;
	//临时数据，用于缓存一个周期
	NODE *pTmpData;
	//数据计数
	int count;

	

	//放大缩小倍数
	float scaling_x;
	float scaling_y;

	float scaling_old_x;
	float scaling_old_y;



	//是否显示横坐标
	bool display_x;

	//是否显示数据值
	bool display_y;

private:
	//变换矩阵
	//平移变换矩阵
	bool translateTransformedMatrix(int m_index_num,   //数据组索引
									int m_index_data   //数据索引;
									);


	bool scalingMatrix(int m_index_num,   //数据组索引
					   int m_index_data   //数据索引;
					   );




};

