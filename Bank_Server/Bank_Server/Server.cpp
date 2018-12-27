#include "Server.h"
#include "state.h"



Server::Server(int server_num){
	this->server_num = server_num;
}

void Server::serve(int duration) {
	Sleep(duration * 1000);
	custom->End_serve();
	Call_num(this);
}


void Call_num(Server* this_server) {
	while (1) {
		while (NUM_DONE < NUM_CUSTOM) {
			if (WaitForSingleObject(M_CALL_NUM, INFINITE) == WAIT_OBJECT_0) {
				if (waitlist.size() != 0) {
					this_server->custom = waitlist.front();
					waitlist.pop();
					ReleaseSemaphore(M_CALL_NUM, 1, NULL);
					int duration;
					duration = this_server->custom->Get_serve(this_server->server_num, Time);//该顾客服务柜台为当前柜台
					this_server->serve(duration);//开始服务
				}
				else {
					ReleaseSemaphore(M_CALL_NUM, 1, NULL);
				}
			}
		}
	}
}