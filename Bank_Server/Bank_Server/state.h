#pragma once
#include <Windows.h>
#include <queue>
#include "Customer.h"


extern int NUM;//����
extern int NUM_CUSTOM;//�ܹ˿���
extern int NUM_DONE;//����ɵĹ˿���
extern int Time;//��ǰʱ����
extern int now_clone;

extern HANDLE M_GET_NUM;//�˿�ȡ���ź���
extern HANDLE M_CALL_NUM;//��̨�к��ź���

extern std::queue <Customer> customers_queue;
extern Customer ** customers;
extern std::queue <Customer*> waitlist;
extern std::queue<Customer*> a;