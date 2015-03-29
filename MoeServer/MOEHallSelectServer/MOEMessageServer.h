#ifndef MOE_HALL_SELECT_SERVER_H
#define MOE_HALL_SELECT_SERVER_H

#include "../MOEServer/MOEServer.h"
#include "../MOEClient/MOEClient.h"
#include <time.h>
class HallServerCollection
{
public:
	HallServerCollection();
	HallServerWorkload workload;
	bool AddServer(int Workload,ServerMessage Server);//true 成功添加,false 更新操作
};
//消息收发子线程
DWORD WINAPI MessageClientThread(LPVOID lpParameter);
#endif