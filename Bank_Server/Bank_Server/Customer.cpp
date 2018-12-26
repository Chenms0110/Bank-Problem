#include "Customer.h"
#include <iostream>
#include "state.h"


Customer::Customer(int customer_num, int enter_time, int duration_time){
	this->customer_num = customer_num;
	this->enter_time = enter_time;
	this->duration_time = duration_time;
	this->got_num = false;  //初始化时是未取号状态
	WaitForSingleObject(this->M_CUSTOM, INFINITE);//P操作，抬起以保护用户将要使用的数据
}

bool Customer::Entered() {
	return (enter_time == Time);
}

int Customer::Get_serve(int server_num, int start_time) {
	//在顾客开始接受服务时，记录为他服务的柜台号及开始服务的时间。
	this->server_num = server_num;
	this->start_time = start_time;
	printf("顾客%d在%d时刻被%d号柜台服务.\n", this->customer_num, this->start_time, this->server_num);

	return this->duration_time;
}

void Customer::End_serve() {
	//结束服务时，记录结束服务的时间。
	this->end_time = Time;
	printf("顾客%d在%d时刻结束了服务.\n", this->customer_num, this->end_time);

	NUM_DONE++;
	ReleaseSemaphore(this->M_CUSTOM, 1, NULL);//V操作，用户相关数据使用结束，同步结束
}


void Get_num(Customer *this_customer)//取号过程
{
	Sleep(1000 / 2);
	if (WaitForSingleObject(M_GET_NUM, INFINITE) == WAIT_OBJECT_0)//P操作
	{
		this_customer->num = NUM;//记录当前号码
		NUM++;//号码加一
		printf("顾客%d在%d时刻取到了号码.\n", this_customer->customer_num,Time, this_customer->num);
		waitlist.push(this_customer);//开始排队
		ReleaseSemaphore(M_GET_NUM, 1, NULL);//V操作
	}
}

