#include "Customer.h"
#include <iostream>
#include "state.h"


Customer::Customer(int customer_num, int enter_time, int duration_time){
	this->customer_num = customer_num;
	this->enter_time = enter_time;
	this->duration_time = duration_time;
	this->got_num = false;  //��ʼ��ʱ��δȡ��״̬
	WaitForSingleObject(this->M_CUSTOM, INFINITE);//P������̧���Ա����û���Ҫʹ�õ�����
}

bool Customer::Entered() {
	return (enter_time == Time);
}

int Customer::Get_serve(int server_num, int start_time) {
	//�ڹ˿Ϳ�ʼ���ܷ���ʱ����¼Ϊ������Ĺ�̨�ż���ʼ�����ʱ�䡣
	this->server_num = server_num;
	this->start_time = start_time;
	printf("�˿�%d��%dʱ�̱�%d�Ź�̨����.\n", this->customer_num, this->start_time, this->server_num);

	return this->duration_time;
}

void Customer::End_serve() {
	//��������ʱ����¼���������ʱ�䡣
	this->end_time = Time;
	printf("�˿�%d��%dʱ�̽����˷���.\n", this->customer_num, this->end_time);

	NUM_DONE++;
	ReleaseSemaphore(this->M_CUSTOM, 1, NULL);//V�������û��������ʹ�ý�����ͬ������
}


void Get_num(Customer *this_customer)//ȡ�Ź���
{
	Sleep(1000 / 2);
	if (WaitForSingleObject(M_GET_NUM, INFINITE) == WAIT_OBJECT_0)//P����
	{
		this_customer->num = NUM;//��¼��ǰ����
		NUM++;//�����һ
		printf("�˿�%d��%dʱ��ȡ���˺���.\n", this_customer->customer_num,Time, this_customer->num);
		waitlist.push(this_customer);//��ʼ�Ŷ�
		ReleaseSemaphore(M_GET_NUM, 1, NULL);//V����
	}
}

