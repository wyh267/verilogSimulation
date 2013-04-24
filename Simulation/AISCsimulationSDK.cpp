#include "stdafx.h"
//
#include "resource.h"
#include "AISCsimulationSDK.h"
//#include "SimulationView.h"
#include "Data.h"
#include <math.h>

#include "MainFrm.h"

//#define BM_DATA_RECIVE (WM_USER + 100)



//初始化仿真器
bool createSimulation(LPCTSTR name,  //需要保存的文件名
					  int data_num   //数据个数
					  )
{
	Data* my_data=Data::shareData(name);
	my_data->configureData(data_num);
	return true;

}



//配置仿真器
bool configureSimulation(bool enabled,               //是否启动仿真器
						 bool write_to_file,		  //是否保存向量信息到文件
						 bool real_time_simulation   //是否允许进行实时仿真
						)
{
	sendMessageToSimulation(0x9001,0);
	return true;
}



//配置变量信息
bool configureValue(LPCTSTR value_name, //变量名称
					int ID,				//变量ID，ID0为时钟信号
					int weight,			//位宽
					bool sigh,			//是否有符号
					COLORREF color
					)
{
	Data *pData=Data::shareData();

	int max,min;

	max=pow(2.0,weight-1);
	min=0-max;

	pData->configureValueInfo(value_name,ID,max,min,color);

	return true;
}








//发送变量
bool sendMessageToSimulation(int index,  //变量ID
							 int data    //变量内容
							 )
{
	Data* pData=Data::shareData();
	int new_data=0;
	if(pData->pData_info[index].node_sigh==true)
	{
		new_data=data;
	}else
	{
		new_data=data-(int)pow(2.0,pData->pData_info[index].node_len);
	}


	pData->addData((int)index,(int)data);

	

	if(index==0)
	{
		pData->moveNext();
	}



	/*CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	::SendMessage(pFrame->GetSafeHwnd(),BM_DATA_RECIVE,index,new_data);*/
	return true;

}















//该函数作废
bool setValueMaxAndMin(LPCTSTR value_name, //变量名称
					   int ID,				//变量ID，ID0为时钟信号
					   int max,
					   int min,
					   COLORREF color)
{
	Data *pData=Data::shareData();
	pData->configureValueInfo(value_name,ID,max,min,color);
	return true;

}