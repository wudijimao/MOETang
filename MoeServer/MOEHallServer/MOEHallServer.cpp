#include "../MOEServer/MOEServer.h"
#include "../MOEClient/MOEClient.h"
#include "Game.h"
#include <time.h>
oneHallServerWorkload workload;
ServerMessage LoginServer;
void UploadWorkload()
{
	//发送负载信息
	ServerMessage MessageServer = GetMOEServer(2);
	MOEClient WorkLoadSender = MOEClient(MessageServer.port,MessageServer.IP);
	SessionMessage seMes;
	seMes.setID(ServerID);
	seMes.session = ServerSession;
	WorkLoadSender.Send(seMes);
	workload.workload = (ConnectionNum*100)/1000;
	WorkLoadSender.Send(workload);
}

DWORD WINAPI ClientThread(LPVOID lpParameter)//例子,实际使用需要自己写这个函数的逻辑 并调用setTread 传入这个类
{
	CLientThread newThread = CLientThread((SOCKET)lpParameter);
	SessionMessage seMes;
	if (!newThread.Recv(seMes))//接受客户端发来的验证信息
	{
		cout<<"客户端从大厅服务器异常断开"<<endl;
		return -1;
	}
	

	if(string(seMes.ID)==ServerID&&seMes.session==ServerSession)
	{
		//用来大厅管理服务器来查询繁忙记录

	}
	else
	{
		CheckMessage cMes = CheckLogin(seMes,LoginServer);
		newThread.Send(cMes);//向客户端返回登录验证是否成功
		if (cMes.IsOk)
		{
			cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"Login Check......OK,Waiting For Request...."<<endl;
			NumberSend reqire;//获取客户请求
			newThread.Recv(reqire);
			CheckMessage cCreatMes;//c1 c3
			NumberSend HNum;//c1存房间号
			HouseSimpleMessage hMes;//c0
			ServerMessage GameServer;
			//ServerMessage GameServer;
			int Num;
			switch(reqire.num)
			{
			case 0://获取大厅中房间信息
				cout<<"Sending Houses' Messages ..."<<endl;
				collection.getSimpleMessage(hMes);
				newThread.Send(hMes);
				cout<<"Send All Right Completed!!!"<<endl;
				break;
			case 1://创建游戏
				cout<<"ID:"<<seMes.ID<<"Creat Game!"<<endl;
				if (collection.getGameNum()<MaxHouseNum)
				{
					cCreatMes.IsOk = true;
					Num = collection.getFreeRoom();
					HNum.num = Num;
					HANDLE hThread = NULL;
					hThread = CreateThread(NULL, 0, GameThread, (LPVOID)&Num, 0, NULL);//创建房间服务线程
					CloseHandle(hThread);
					newThread.Send(cCreatMes);//成功信息
					newThread.Send(HNum);//房间号
				}
				else
				{
					newThread.Send(cCreatMes);//失败
				}
				break;
			case 2://加入游戏
				cout<<"ID:"<<seMes.ID<<"Join Game!"<<endl;
				break;
			case 3://获取特定游戏服务器是
				newThread.Recv(HNum);
				if (collection.getGameServer(HNum.num,GameServer))
				{
					cCreatMes.IsOk = true;
					newThread.Send(cCreatMes);
					newThread.Send(GameServer);
				}
				else
				{
					newThread.Send(cCreatMes);
				}
				break;
			}
			UploadWorkload();
		}
		else
		{
			cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"Login Check......Faild,Need reLogin!!";
		}
	}
	//system("pause");
	return 0;
}
void main()
{
	LoginServer = GetMOEServer(1);
	ServerMessage hserver;
	MOEServer server = MOEServer();
	server.SetThread(ClientThread);
	workload.server.setIP(server.getIP().c_str());
	workload.server.port = server.getPort();
	UploadWorkload();
	cout<<"HallServer now running,Welcome!!!"<<endl;
	server.run();
}