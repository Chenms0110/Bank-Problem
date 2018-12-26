#pragma once
#include <Windows.h>
#include <queue>

class Customer
{
private:
	HANDLE M_CUSTOM = CreateSemaphore(NULL, 1, 1, NULL);//�˿��ź���
	int customer_num;   //�˿ͺ�
	int enter_time;     //�˿ͽ������е�ʱ�䣨ע�⣺���ǽ��ܷ����ʱ�䣩
	int duration_time;  //��Ҫ�ķ���ʱ�䡣
	int num;            //�˿�ȡ���ĺ��루ע�⣺��˿ͺŲ���һ���£�
	int start_time;     //��ʼ�����ʱ��
	int server_num;     //���ܷ���Ĺ�̨��
	int end_time;       //���������ʱ�䣨���뿪ʱ�䣩
public:
	bool got_num;       //�Ƿ�ȡ�˺�
	Customer(int customer_num, int enter_time, int duration_time);  //��ʼ���˿ͱ�Ҫ��Ϣ
	friend void Get_num(Customer *this_customer);  //ȡ�ź���
	int Get_serve(int server_num, int start_num);  //���ܷ�����
	bool Entered();    //ȷ���Ƿ񵽽���ʱ�䣬�����Ǽ�ʱ����
	void End_serve();          //����������ز�������,�����ֱ��Ǽ�ʱ���͡��Ѿ���ɷ���Ĺ˿����������ã�����������
};
