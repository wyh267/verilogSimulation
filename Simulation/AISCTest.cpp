#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "resource.h"
#include "AISCTest.h"
#include "AISCsimulationSDK.h"

  
DWORD dwThreadID;
HANDLE hThread;

void TestMain(void);


///////////////////////////////////////////////
//
//
//          主函数入口
//
//
///////////////////////////////////////////////
void func()
{
	printf("开始运行程序...\n");
	TestMain();
	printf("程序运行完成...\n");
}



void AISCTest()
{

	printf("配置仿真器开始...\n");

	/////////////////////////////////////////////////////////////////////////////////
	//
	//
	//配置仿真器【保存的文件名】【需要监控的变量数量】
	//
	//
	/////////////////////////////////////////////////////////////////////////////////
	createSimulation(_T("D:\\MyTest_out_3.dat"),4);



	/////////////////////////////////////////////////////////////////////////////////
	//
	//
	//配置变量【变量名】【变量ID】【最大值】【最小值】【颜色(该参数可选，默认为红色)】
	//注意：变量ID为0 必须配置，且必须是时钟周期变量
	//正式版使用位宽和是否有符号来代替最大值最小值
	//
	//
	/////////////////////////////////////////////////////////////////////////////////
	/************************************配置变量开始************************************/
	configureValue(_T("fir_xi"),0,13,true,COLOR_RED);
	configureValue(_T("fir_xr"),1,13,false,COLOR_BLUE);
	configureValue(_T("agc2_xi_d"),2,13,true,COLOR_GREEN);
	configureValue(_T("agc2_xr_d"),3,13,true,COLOR_PINK);
	/************************************配置变量结束************************************/

	
	/////////////////////////////////////////////////////////////////////////////////
	//
	//
	//配置仿真器【是否开启仿真器】【是否存文件】【是否实时监控】
	//
	//
	/////////////////////////////////////////////////////////////////////////////////
	//configureSimulation(true,true,true);
	Sleep(1000);
	


	printf("配置仿真器结束..启动程序....\n");
	//启动应用【不用修改】
	hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)func,NULL,0,&dwThreadID);

	
}



void AISCTestStop()
{
	printf("\r\n停止程序...\n");
	TerminateThread(hThread,2);
}