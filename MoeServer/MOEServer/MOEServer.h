#ifndef MOE_SERVER_H
#define MOE_SERVER_H
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <Windows.h>
#include <string>
#include "../MOEStruct/MessageStruct.h"
#include <time.h>
#include "getMOEServer.h"
using namespace std;


struct myObject//用于传递参数给子进程
{
	SOCKET ClientSocket;
};
struct SendNumObject:myObject
{
	int Num;
};
class CLientThread
{
	SOCKET ClientSocket;
public:
	CLientThread(SOCKET lpParameter)
	{
		ClientSocket = lpParameter;
	}
	~CLientThread()
	{
		closesocket(ClientSocket);
	}
	bool Recv(Message &mes)
	{
		char * buf = (char *)malloc(mes.getSize());
		int Ret = recv(ClientSocket, buf, mes.getSize(), 0);
		if ( Ret == 0 || Ret == SOCKET_ERROR ) 
		{
			cout<<"接收失败!   ERRORCODE:"<<Ret<<endl;
			return false;
		}
		memcpy(&mes,buf,mes.getSize());
		//cout<<"接收到客户信息为:"<<RecvBuffer<<endl;
		return true;
	}
	bool Recv(Message &mes,int size)
	{
		char * buf = (char *)malloc(size);
		int Ret = recv(ClientSocket, buf, size, 0);
		if ( Ret == 0 || Ret == SOCKET_ERROR ) 
		{
			cout<<"接收失败!   ERRORCODE:"<<Ret<<endl;
			return false;
		}
		memcpy(&mes,buf,size);
		//cout<<"接收到客户信息为:"<<RecvBuffer<<endl;
		return true;
	}
	bool Send(Message &mes)
	{
		int Ret = send(ClientSocket, (char*)&mes, mes.getSize(), 0);
		if ( Ret == SOCKET_ERROR )
		{
			cout<<"Send Info Error::"<<GetLastError()<<endl;
			return false;
		}
		return true;
	}
};

int ConnectionNum=0;
void threadBegin()
{
	++ConnectionNum;
}
void threadEnd()
{
	--ConnectionNum;
}

class MOEServer
{
	int PORT;//端口
	string IP_ADDRESS;//地址
	SOCKET ServerSocket,CientSocket;
	LPTHREAD_START_ROUTINE Thread;
	int MaxConnectionNum;
	string getlocalIP()
	{
		WSADATA wsaData;
		WORD sockVersion = MAKEWORD(2, 2);
		::WSAStartup(sockVersion, &wsaData);
		char lv_name[50];
		gethostname(lv_name, 50);
		hostent * lv_pHostent;
		//lv_pHostent = (hostent *)malloc(sizeof(hostent));
		//*lv_pHostent = *gethostbyname(lv_name);
		if( NULL == (lv_pHostent=gethostbyname(lv_name)))
		{
			printf("get Hosrname Fail \n");
			return 0;
		}
		SOCKADDR_IN lv_sa;
		lv_sa.sin_family = AF_INET;
		lv_sa.sin_port = htons(6000);
		memcpy(&lv_sa.sin_addr.S_un.S_addr, lv_pHostent->h_addr_list[0], lv_pHostent->h_length);
		string IP = inet_ntoa(lv_sa.sin_addr);
		//free(lv_pHostent);
		return IP;
	}
public:
	int getPort()
	{
		return PORT;
	}
	string getIP()
	{
		return IP_ADDRESS;
	}
	MOEServer(int myport,char* IP,int connectMaxNum=10)
	{
		PORT=myport;
		IP_ADDRESS =IP;
		//ConnectionNum = 0;
		MaxConnectionNum = connectMaxNum;
		Init();
	}
	MOEServer(char *IP,int connectMaxNum=10)
	{
		IP_ADDRESS = IP;
		PORT=0;
		//ConnectionNum = 0;
		MaxConnectionNum = connectMaxNum;
		Init();
	}
	MOEServer(int connectMaxNum=10)
	{
		PORT=0;
		IP_ADDRESS =getlocalIP();
		//ConnectionNum = 0;
		MaxConnectionNum = connectMaxNum;
		Init();
	}
	static DWORD WINAPI ClientThread(LPVOID lpParameter)//例子,实际使用需要自己写这个函数的逻辑 并调用setTread 传入这个类
	{
		threadBegin();
		CLientThread newThread = CLientThread((SOCKET)lpParameter);
		int i=0; 
		while(true)
		{
			clock_t myclock = clock(); 
			NumberSend sendmsg1;
			NumberSend sendmsg2;
			newThread.Recv(sendmsg1);
			newThread.Recv(sendmsg2);
			//ClientMapMessage abc;
			//newThread.Send(abc);
			int a = clock()-myclock;
			cout<<i<<":"<<a<<endl;
			i++;
		}
		system("pause");
		threadEnd();
		return 0;
	}
	int getWorkload()
	{
		return (ConnectionNum*100)/MaxConnectionNum;
	}
	bool Init()
	{
		WSADATA  Ws;
		struct sockaddr_in LocalAddr;
		int Ret = 0;

		//Init Windows Socket
		if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
		{
			cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
			system("pause");
			return false;
		}

		//Create Socket
		ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if ( ServerSocket == INVALID_SOCKET )
		{
			cout<<"Create Socket Failed::"<<GetLastError()<<endl;
			system("pause");
			return false;
		}

		LocalAddr.sin_family = AF_INET;
		LocalAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS.c_str());
		LocalAddr.sin_port = htons(PORT);
		memset(LocalAddr.sin_zero, 0x00, 8);

		//Bind Socket
		Ret = bind(ServerSocket, (struct sockaddr*)&LocalAddr, sizeof(LocalAddr));
		if ( Ret != 0 )
		{
			cout<<"Bind Socket Failed::"<<GetLastError()<<endl;
			system("pause");
			return false;
		}
		Ret = listen(ServerSocket, MaxConnectionNum);
		if ( Ret != 0 )
		{
			cout<<"listen Socket Failed::"<<GetLastError()<<endl;
			system("pause");
			return false;
		}
		sockaddr_in *add = new sockaddr_in();
		int length = 200;
		Ret =  getsockname(ServerSocket,(sockaddr*)add,&length);
		if ( Ret != 0 )
		{
			cout<<"listen Socket Failed::"<<GetLastError()<<endl;
			system("pause");
			return false;
		}
		else
		{
			PORT = ntohs(add->sin_port);
		}
		cout<<"Server started::"<<inet_ntoa(add->sin_addr)<<":"<<ntohs(add->sin_port)<<endl;
		return true;
	}
	void SetThread(LPTHREAD_START_ROUTINE myThread)
	{
		Thread =myThread;
	}
	void run()
	{
		int AddrLen = 0;
		struct sockaddr_in ClientAddr;
		HANDLE hThread = NULL;
		while ( true )
		{
			AddrLen = sizeof(ClientAddr);
			CientSocket = accept(ServerSocket, (struct sockaddr*)&ClientAddr, &AddrLen);
			if ( CientSocket == INVALID_SOCKET )
			{
				cout<<"Accept Failed::"<<GetLastError()<<endl;
				system("pause");
				break;
			}
			cout<<"Client connecting::"<<inet_ntoa(ClientAddr.sin_addr)<<":"<<ntohs(ClientAddr.sin_port)<<endl;
			//cout<<++ConnectionNum;
			hThread = CreateThread(NULL, 0, Thread, (LPVOID)CientSocket, 0, NULL);
			if ( hThread == NULL )
			{
				cout<<"Create Thread Failed!"<<endl;
				break;
			}
			cout<<"Server workload:"<<getWorkload()<<"%"<<endl;
			CloseHandle(hThread);
		}
	}
	SendNumObject myobj;
	void run(SendNumObject obj)
	{
		myobj = obj;
		int AddrLen = 0;
		struct sockaddr_in ClientAddr;
		HANDLE hThread = NULL;
		while ( true )
		{
			AddrLen = sizeof(ClientAddr);
			CientSocket = accept(ServerSocket, (struct sockaddr*)&ClientAddr, &AddrLen);
			if ( CientSocket == INVALID_SOCKET )
			{
				cout<<"Accept Failed::"<<GetLastError()<<endl;
				system("pause");
				break;
			}
			cout<<"Client connecting::"<<inet_ntoa(ClientAddr.sin_addr)<<":"<<ClientAddr.sin_port<<endl;
			myobj.ClientSocket = CientSocket;
			hThread = CreateThread(NULL, 0, Thread, (LPVOID)&myobj, 0, NULL);
			if ( hThread == NULL )
			{
				cout<<"Create Thread Failed!"<<endl;
				break;
			}
			cout<<"Server workload:"<<getWorkload()<<"%"<<endl;
			CloseHandle(hThread);
		}
	}
	void close()
	{
		closesocket(ServerSocket);
		closesocket(CientSocket);
		WSACleanup();
	}
	~MOEServer()
	{
		close();
	}
};

#endif