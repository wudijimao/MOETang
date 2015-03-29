#ifndef MOE_CLIENT_H
#define MOE_CLIENT_H
#pragma comment(lib, "ws2_32.lib")
//Client.cpp
#include <iostream>
#include <Windows.h>
#include "../MOEStruct/MessageStruct.h"
using namespace std;
class MOEClient
{
	int PORT;//端口
	string IP_ADDRESS;//地址	
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
			return false;
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
			cout<<"Connecting Server.........OK!!"<<endl;
			return true;
		}
		return false;
	}
	bool Send(Message &mes)
	{
		Ret = send(ClientSocket, (char*)&mes, mes.getSize(), 0);
		if ( Ret == SOCKET_ERROR )
		{
			cout<<"ERROR, Send Error Info::"<<GetLastError()<<endl;
			return false;
		}
		return true;
	}
	bool Recv(Message &mes)
	{
		int Ret = recv(ClientSocket, (char *)&mes, mes.getSize(), 0);
		if ( Ret == 0 || Ret == SOCKET_ERROR ) 
		{
			cout<<"ERROR, RECEIVE FAILD!!"<<endl;
			return false;
		}
		//cout<<"接收到客户信息为:"<<RecvBuffer<<endl;
		return true;
	}
	void close()
	{
		closesocket(ClientSocket);
		WSACleanup();
	}
	~MOEClient()
	{
		close();
	}
};
CheckMessage CheckLogin(SessionMessage &seMes,ServerMessage &LoginServer)
{
	//下边向登录服务器验证用户是否登录
	MOEClient check = MOEClient(login_PORT,login_IP);
	LoginMessage lMes;
	lMes.setID(ServerID);
	lMes.setPassword(ServerPassWord);
	check.Send(lMes);
	SessionMessage seMes1 = seMes;
	check.Send(seMes1);
	CheckMessage cMes;
	check.Recv(cMes);
	return cMes;
}
#endif