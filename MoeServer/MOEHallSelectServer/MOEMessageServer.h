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
	bool AddServer(int Workload,ServerMessage Server);//true �ɹ����,false ���²���
};
//��Ϣ�շ����߳�
DWORD WINAPI MessageClientThread(LPVOID lpParameter);
#endif