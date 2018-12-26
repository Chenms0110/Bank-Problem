#pragma once
#include <Windows.h>
#include <queue>

class Customer
{
private:
	HANDLE M_CUSTOM = CreateSemaphore(NULL, 1, 1, NULL);//顾客信号量
	int customer_num;   //顾客号
	int enter_time;     //顾客进入银行的时间（注意：不是接受服务的时间）
	int duration_time;  //需要的服务时间。
	int num;            //顾客取到的号码（注意：与顾客号不是一回事）
	int start_time;     //开始服务的时间
	int server_num;     //接受服务的柜台号
	int end_time;       //结束服务的时间（即离开时间）
public:
	bool got_num;       //是否取了号
	Customer(int customer_num, int enter_time, int duration_time);  //初始化顾客必要信息
	friend void Get_num(Customer *this_customer);  //取号函数
	int Get_serve(int server_num, int start_num);  //接受服务函数
	bool Entered();    //确认是否到进入时间，参数是计时器。
	void End_serve();          //结束服务相关操作函数,参数分别是计时器和“已经完成服务的顾客数”的引用（方便自增）
};
