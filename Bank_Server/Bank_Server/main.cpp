#include "Customer.h"
#include "Server.h"
#include <iostream>
#include <mutex>
#include "state.h"

#define N 4 //��̨��
#define T 1000 //ʱ������


int now;


void Clock() {
	while (true) {
		Sleep(1000);
		Time++;
	}
}

void start()
{
	//�˿͵��߳�����
	HANDLE *custom_thread = new HANDLE[NUM_CUSTOM];
	DWORD *custom_threadID = new DWORD[NUM_CUSTOM];
	//NUM_DONE   ����ɷ���Ĺ˿���
	//NUM_CUSTOM �ܹ˿���
	while (now_clone)
	{
		int i;
		for (i = 0; i < now; i++)
		{
				//got_num��ʾ�˿��Ƿ�鵽��
				if (!(*(customers + i))->got_num)//��ʱ�䵽�Ҹù˿�δȡ�������ȡ���߳�
				{
					//�˿��߳�ִ��Get_num����	
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
	//clock_thread��ʱ���߳�
	clock_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Clock, NULL, 0, &clock_threadID);//��ʼʱ�Ӻ���



	HANDLE Come_thread;
	DWORD Come_threadID;
	Come_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CustomerComing, NULL, 0, &Come_threadID);//��ʼʱ�Ӻ���
																								  //��̨�߳�����
	HANDLE server_thread[N];
	DWORD server_threadID[N];
	//servers�Ƕ�������
	Server **servers;
	servers = new Server*[N];
	for (int i = 0; i < N; i++)//�����й�̨��ʼ����
	{
		*(servers + i) = new Server(i+1);//��ʼ����̨
		Server* thisserver = *(servers + i);
		//һ����̨�̶߳�Ӧһ����̨����
		//��̨�߳�ִ��Call_num����, ���кź���
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
			//customersÿһ����ַ����еĵ�ַһһ��Ӧ
			*(customers + i) = &customers_queue.front();
			customers_queue.pop();
		}
		//ReleaseMutex(hMutex);
		start();//��ʼ����˿�
	}
	system("pause");
	return 0;
}