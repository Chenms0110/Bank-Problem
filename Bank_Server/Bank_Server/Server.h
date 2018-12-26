#pragma once
#include "Customer.h"

class Server
{
private:
	Customer * custom;
	int server_num;
public:
	Server(int server_num);
	friend void Call_num(Server* this_server);
	void serve(int duration);
};

