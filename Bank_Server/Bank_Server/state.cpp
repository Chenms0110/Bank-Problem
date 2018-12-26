#include <Windows.h>
#include <queue>
#include "Customer.h"


 int NUM = 1;//号码
 int NUM_CUSTOM = 0;//总顾客数
 int NUM_DONE = 0;//已完成的顾客数
 int Time = 0;//当前时刻数
 int now_clone = 0;

 HANDLE M_GET_NUM = CreateSemaphore(NULL, 1, 1, NULL);//顾客取号信号量
 HANDLE M_CALL_NUM = CreateSemaphore(NULL, 1, 1, NULL);//柜台叫号信号量

 std::queue <Customer> customers_queue;
 Customer ** customers;
 std::queue <Customer*> waitlist;