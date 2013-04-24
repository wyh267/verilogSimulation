使用方法：
1.将自己的程序源代码拷贝到工程目录下（自己的cpp文件和h文件，文件操作相关的.h文件不用拷贝【DTMBFILEOP.h DTMBTop.h,FileOp.h这三个文件不用拷贝】）

2.右键点工程--->添加--->现有项,将刚刚拷贝的cpp和h文件添加到工程

3.修改main函数的名称

4.将所有cpp和h文件添加#include "stdafx.h"

5.编译运行无错误。


6.配置变量，入口文件是：AISCTest.cpp中的void AISCTest()，在此函数中配置变量和变量信息

7.配置程序入口，入口文件是：AISCTest.cpp中的void func()，在这里调用你们的main函数，请将main函数改名

8.再次编译运行，无错误。