#include "MOEMessageServer.h"
HallServerCollection hallCollection;
ServerMessage LoginServer;
void main()
{
	LoginServer = GetMOEServer(1);
	ServerMessage MessageServer = GetMOEServer(2);
	MOEServer server = MOEServer(MessageServer.port,MessageServer.IP);
	server.SetThread(MessageClientThread);
	cout<<"MessageServer now running,Welcom!!!"<<endl;
	server.run();
}

//消息收发子线程 包括大厅服务器信息的分发和更新维护，负责用户信息的查询和维护
DWORD WINAPI MessageClientThread(LPVOID lpParameter)
{
	threadBegin();
	CLientThread newThread = CLientThread((SOCKET)lpParameter);
	SessionMessage seMes;
	newThread.Recv(seMes);//接受客户端发来的验证信息

	if(string(seMes.ID)==ServerID&&seMes.session==ServerSession)
	{
		//用来大厅服务器提交繁忙记录
		oneHallServerWorkload workload;
		newThread.Recv(workload);
		if(hallCollection.AddServer(workload.workload,workload.server))
		{
			cout<<"HallServer Registe Complete!::"<<workload.server.IP<<":"<<workload.server.port<<"   Workload:"<<workload.workload<<"%"<<endl;
		}
		else
		{
			cout<<"HallServer Refreshe Complete!::"<<workload.server.IP<<":"<<workload.server.port<<"   Workload:"<<workload.workload<<"%"<<endl;
		}

	}
	else
	{
		CheckMessage cMes = CheckLogin(seMes,LoginServer);
		newThread.Send(cMes);//向客户端返回登录验证是否成功
		if (cMes.IsOk)
		{
			cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"Login Check......OK,Sending Hall Server's Messages...."<<endl;
			HallServerWorkload hMes;
			hMes = hallCollection.workload;
			newThread.Send(hMes);
			cout<<"Send All Right Completed!!!"<<endl;
		}
		else
		{
			cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"Login Check......Faild,Need reLogin!!";
		}
	}
	//system("pause");
	threadEnd();
	return 0;
}


HallServerCollection::HallServerCollection()
{
	workload.serverNum=0;
}
bool HallServerCollection::AddServer(int Workload,ServerMessage Server)//true 成功添加,false 更新操作
{
	//循环检查是否已经注册过
	for (int i=0;i<workload.serverNum;++i)
	{
		if (string(workload.server[i].IP)==string(Server.IP)&&workload.server[i].port==Server.port)
		{
			//注册过，更新负载信息
			workload.workload[i]=Workload;
			return false;
		}
	}
	//未注册过 注册
	workload.workload[workload.serverNum]=Workload;
	workload.server[workload.serverNum]=Server;
	++workload.serverNum;
	return true;
}