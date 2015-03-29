#ifndef MOE_CLIENT_H
#define MOE_CLIENT_H
#pragma comment(lib, "ws2_32.lib");
//Client.cpp
#include <iostream>
#include <Windows.h>
#include "MessageStruct.h"
using namespace std;
class MOEClient
{
	int PORT;//�˿�
	string IP_ADDRESS;//��ַ	
	SOCKET ClientSocket;
	int Ret;
	struct sockaddr_in ServerAddr;
public:
	MOEClient(int port,char* IP)
	{
		PORT=port;
		IP_ADDRESS =IP;
		Ret = 0;
		Init();
	}
	MOEClient()
	{
		PORT=4000;
		IP_ADDRESS ="192.168.1.111";
		Ret = 0;
		Init();
	}
	bool Init()
	{
		WSADATA  Ws;
		//Init Windows Socket
		if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
		{
			cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
			return -1;
		}

		//Create Socket
		ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if ( ClientSocket == INVALID_SOCKET )
		{
			cout<<"Create Socket Failed::"<<GetLastError()<<endl;
			return false;
		}

		ServerAddr.sin_family = AF_INET;
		ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS.c_str());
		ServerAddr.sin_port = htons(PORT);
		memset(ServerAddr.sin_zero, 0x00, 8);

		int ERETURN = connect(ClientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
		if ( ERETURN == SOCKET_ERROR )
		{
			cout<<"Connect Error::"<<GetLastError()<<endl;
			return false;
		}
		else
		{
			cout<<"���ӳɹ�!"<<endl;
			return true;
		}
		return false;
	}
	bool Send(Message &mes)
	{
		Ret = send(ClientSocket, (char*)&mes, mes.getSize(), 0);
		if ( Ret == SOCKET_ERROR )
		{
			cout<<"Send Info Error::"<<GetLastError()<<endl;
			return false;
		}
		return true;
	}
	void Recv(Message &mes)
	{
		int Ret = recv(ClientSocket, (char *)&mes, mes.getSize(), 0);
		if ( Ret == 0 || Ret == SOCKET_ERROR ) 
		{
			cout<<"����ʧ��!"<<endl;
		}
		//cout<<"���յ��ͻ���ϢΪ:"<<RecvBuffer<<endl;
		return ;
	}
	~MOEClient()
	{
		closesocket(ClientSocket);
		WSACleanup();
	}
};
#endif