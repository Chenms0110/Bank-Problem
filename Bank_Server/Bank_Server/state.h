#pragma once
#include <Windows.h>
#include <queue>
#include "Customer.h"


extern int NUM;//号码
extern int NUM_CUSTOM;//总顾客数
extern int NUM_DONE;//已完成的顾客数
extern int Time;//当前时刻数
extern int now_clone;

extern HANDLE M_GET_NUM;//顾客取号信号量
extern HANDLE M_CALL_NUM;//柜台叫号信号量

extern std::queue <Customer> customers_queue;
extern Customer ** customers;
extern std::queue <Customer*> waitlist;
extern std::queue<Customer*> a;