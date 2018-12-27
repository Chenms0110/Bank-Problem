#include "Customer.h"
#include "Server.h"
#include <iostream>
#include <cstdlib>
#include <mutex>
#include "state.h"

#define N 4 //��̨��
#define T 1000 //ʱ������
#define random(x) (rand()%x)

int now;


void Clock() {
	while (true) {
		Sleep(1000);
		Time++;
		if (Time % 30 == 0) {
			std::cout << Time << std::endl;
		}
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
			if ((*(customers + i))->Entered()) {
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
}


void haha() {
	std::vector<HANDLE> custom_thread;
	DWORD *custom_threadID;
	Customer* a;

	while (1) {
		while (!customers_queue.empty()) {
			custom_threadID = new DWORD;
			a = &customers_queue.front();

			if (a&&a->Entered()) {
				custom_thread.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Get_num, a, 0, custom_threadID));
				a->got_num = true;
				customers_queue.pop();
			}
		}
	}
}

HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

void CustomerComing() {
	int i = 1;
	int n = 0;
	int t = Time;
	int d;
	while (1) {
		while (NUM_CUSTOM - NUM_DONE < 30) {
			//WaitForSingleObject(hMutex, INFINITE);
			srand(n++);
			t = t + random(10) + 1;
			srand(t);
			d = random(10);
			customers_queue.push(Customer(i, t, d));
			WaitForSingleObject(hMutex, INFINITE);
			a.push(&customers_queue.back());
			ReleaseMutex(hMutex);
			i++;
			NUM_CUSTOM++;
			//ReleaseMutex(hMutex);
		}
	}
}



int main() {
	HANDLE clock_thread;
	DWORD clock_threadID;
	//clock_thread��ʱ���߳�
	clock_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Clock, NULL, 0, &clock_threadID);//��ʼʱ�Ӻ���



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



	HANDLE Come_thread;
	DWORD Come_threadID;
	Come_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CustomerComing, NULL, 0, &Come_threadID);//��ʼʱ�Ӻ���


	std::vector<HANDLE> custom_thread;
	std::vector<DWORD*> custom_threadID;
	//Customer* a;
	int forID = 0;
	while (a.size() != 10);
	while (1) {
		while (!customers_queue.empty()) {
			
			WaitForSingleObject(hMutex, INFINITE);
			if (!a.empty()&&a.front()->Entered()) {
				custom_threadID.push_back(new DWORD);
				custom_thread.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Get_num, a.front(), 0, custom_threadID[forID]));
				a.front()->got_num = true;
				customers_queue.pop();
				a.pop();
				forID++;
			}
			ReleaseMutex(hMutex);
		}
	}

/*
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
	*/
	system("pause");
	return 0;
}