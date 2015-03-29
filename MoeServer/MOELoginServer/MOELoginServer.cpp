#include "../MOEServer/MOEServer.h"
#include "LoginDataServer.h"
#include <time.h>
#include <Windows.h>

class CheckLogin
{
	bool WriteLock;
	LoginDataServer server;
public:
	bool updateSession(string ID,int Session)
	{
		if (WriteLock)
		{
			srand(time(0));
			do 
			{
				Sleep(rand()%100);
			} while (WriteLock);
		}
		WriteLock = true;
		server.setSessionID(ID,Session);
		WriteLock = false;
		return true;
	}
	bool isPassWordCurrect(string ID,string PassWord)
	{
		if(PassWord == server.getPassword(ID)&&PassWord!="")
		{
			return true;
		}
		return false;
	}
	bool isSessionCurrect(string ID,int Sessioon)
	{
		if(Sessioon == server.getSessionID(ID))
		{
			return true;
		}
		return false;
	}
	bool signUp(string username,string password)
	{
		if(server.getPassword(username)=="")
		{
			server.signup(username,password);
			return true;
		}
		return false;
	}
	bool unSign(string username,string password)
	{
		if (WriteLock)
		{
			srand(time(0));
			do 
			{
				Sleep(rand()%100);
			} while (WriteLock);
		}
		WriteLock = true;
		if(password == server.getPassword(username)&&password!="")
		{
			WriteLock = false;
			return server.unsign(username);
		}
		WriteLock = false;
		return false;
	}
};
CheckLogin login;
DWORD WINAPI ClientThread(LPVOID lpParameter)//例子,实际使用需要自己写这个函数的逻辑 并调用setTread 传入这个类
{
	clock_t myclock = clock();
	threadBegin();
	CLientThread newThread = CLientThread((SOCKET)lpParameter);
	LoginMessage Mes = LoginMessage();

	if(!newThread.Recv(Mes))
	{
		cout<<"客户端异常断开"<<endl;
		return -1;
	}
	
	if (string(Mes.ID)==ServerID&&string(Mes.PassWord)==ServerPassWord)
	{
		//服务器来验证用户是否登录
		cout<<"服务器登录验证"<<endl;
		SessionMessage seMes;
		newThread.Recv(seMes);
		CheckMessage cMes;
		cMes.IsOk = login.isSessionCurrect(seMes.ID,seMes.session);
		newThread.Send(cMes);
	}
	else if (login.isPassWordCurrect(Mes.ID,Mes.PassWord))
	{
		cout<<"ID:"<<Mes.ID<<"  PassWord:"<<Mes.PassWord<<"用户名密码验证成功，正常登陆"<<endl;
		//用户登录
		SessionMessage seMes;
		seMes.setID(Mes.ID);
		srand(time(0));
		seMes.session = rand();
		login.updateSession(seMes.ID,seMes.session);//加入用户已登录信息
		newThread.Send(seMes);//回送验证信息
		//下边放发送大厅管理服务器地址
		ServerMessage sMes = GetMOEServer(2);
		newThread.Send(sMes);//服务器信息
		//system("pause");
	}
	else
	{
		cout<<"ID:"<<Mes.ID<<endl<<"PassWord:"<<Mes.PassWord<<"用户登录失败，用户名密码不正确"<<endl;
	}
	int a = clock()-myclock;
	cout<<"time:"<<float(a)/1000.0;
	threadEnd();
	return 0;
}
void main()
{

	CheckLogin login = CheckLogin();
	ServerMessage LoginServer = GetMOEServer(1);
	MOEServer server=MOEServer(LoginServer.port,LoginServer.IP);
	server.SetThread(ClientThread);
	cout<<"LoginServer now running,Welcom!!!"<<endl;
	server.run();
}