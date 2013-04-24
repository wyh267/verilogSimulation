

#ifndef _AISC_SIM_SDK_
#define _AISC_SIM_SDK_



#define DISPLAY_VAULE	0x9001




//颜色定义
#define COLOR_RED	RGB(255,0,0)
#define COLOR_BLUE	RGB(0,0,255)
#define COLOR_GREEN RGB(0,255,0)
#define COLOR_BLACK	RGB(0,0,0)
#define COLOR_PALEV RGB(219,112,147) //palevioletred（脸红的淡紫红）  
#define COLOR_PINK  RGB(255,105,180) //pink（热情的粉红）   




//初始化仿真器
bool createSimulation(LPCTSTR name,  //需要保存的文件名
					  int data_num   //数据个数
					  );



//配置仿真器
bool configureSimulation(bool enabled=true,               //是否启动仿真器
						 bool write_to_file=true,		  //是否保存向量信息到文件
						 bool real_time_simulation=true   //是否允许进行实时仿真
						);




//配置变量信息
bool configureValue(LPCTSTR value_name, //变量名称
					int ID,				//变量ID，ID0为时钟信号
					int weight,			//位宽
					bool sigh,			//是否有符号
					COLORREF color=RGB(255,0,0)	//颜色
					);



//发送变量
bool sendMessageToSimulation(int index,  //变量ID
							 int data    //变量内容
							 );






//设置变量的最大最小值，已经作废
bool setValueMaxAndMin(LPCTSTR value_name, //变量名称
					   int ID,				//变量ID，ID0为时钟信号
					   int max,
					   int min,
					   COLORREF color=RGB(255,0,0));




#endif