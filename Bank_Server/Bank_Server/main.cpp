#include "Customer.h"
#include "Server.h"
#include <iostream>
#include <mutex>
#include "state.h"

#define N 4 //柜台数
#define T 1000 //时钟周期


int now;


void Clock() {
	while (true) {
		Sleep(1000);
		Time++;
	}
}

void start()
{
	//顾客的线程数组
	HANDLE *custom_thread = new HANDLE[NUM_CUSTOM];
	DWORD *custom_threadID = new DWORD[NUM_CUSTOM];
	//NUM_DONE   已完成服务的顾客数
	//NUM_CUSTOM 总顾客数
	while (now_clone)
	{
		int i;
		for (i = 0; i < now; i++)
		{
				//got_num表示顾客是否抽到号
				if (!(*(customers + i))->got_num)//若时间到且该顾客未取号则加入取号线程
				{
					//顾客线程执行Get_num函数	
					*(custom_thread + i) = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Get_num, *(customers + i), 0, custom_threadID + i);
					(*(customers + i))->got_num = true;
				}
		}
	}
}

HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

void CustomerComing() {
	int i = 0;
	int n = 0;
	while (NUM_CUSTOM - NUM_DONE < 30) {
		//WaitForSingleObject(hMutex, INFINITE);
		customers_queue.push(Customer(i++, Time+(n++), 3));
		NUM_CUSTOM++;
		//ReleaseMutex(hMutex);
	}
}



int main() {
	HANDLE clock_thread;
	DWORD clock_threadID;
	//clock_thread是时钟线程
	clock_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Clock, NULL, 0, &clock_threadID);//开始时钟函数



	HANDLE Come_thread;
	DWORD Come_threadID;
	Come_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CustomerComing, NULL, 0, &Come_threadID);//开始时钟函数
																								  //柜台线程数组
	HANDLE server_thread[N];
	DWORD server_threadID[N];
	//servers是对象数组
	Server **servers;
	servers = new Server*[N];
	for (int i = 0; i < N; i++)//令所有柜台开始服务
	{
		*(servers + i) = new Server(i+1);//初始化柜台
		Server* thisserver = *(servers + i);
		//一个柜台线程对应一个柜台对象
		//柜台线程执行Call_num函数, 即叫号函数
		server_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Call_num, *(servers + i), 0, &server_threadID[i]);
	}

	while (1) {
		while (NUM_CUSTOM - NUM_DONE == 0);
		now = NUM_CUSTOM - NUM_DONE;
		now_clone = now;
		customers = new Customer*[now];
		//WaitForSingleObject(hMutex, INFINITE);
		for (int i = 0; i < now; i++)
		{
			//customers每一个地址与队列的地址一一对应
			*(customers + i) = &customers_queue.front();
			customers_queue.pop();
		}
		//ReleaseMutex(hMutex);
		start();//开始进入顾客
	}
	system("pause");
	return 0;
}