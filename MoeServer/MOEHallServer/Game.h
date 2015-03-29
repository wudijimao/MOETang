#ifndef GAME_H
#define GAME_H
#include <vector>
#include <windows.h>
#include <time.h>
#include "../MOEServer/MOEServer.h"
#include "../MOEClient/MOEClient.h"
#include "game/Server.h"


#define login_PORT 4000
#define login_IP "192.168.1.111"
#define hallSelect_PORT 4001
#define hallSelect_IP "192.168.1.111"



#define ServerID "99999$^%%$"
#define ServerSession 98735425
#define ServerPassWord "545123$%^"
#define MaxHouseNum 128

extern ServerMessage LoginServer;
class GamesMessage
{
private:
	ServerMessage server[MaxHouseNum];
	bool writeLock[MaxHouseNum];//写入锁
	bool refreshed[MaxHouseNum];//标记房间信息是否刷新过
	bool used[MaxHouseNum];//房间是否被使用
	
	bool ReadingLock;//全局锁
	int gameNum;//游戏数量
public:
	oneHouseMessage houses[MaxHouseNum];
	GameServer gameServer[MaxHouseNum];
	void getMapMessage(int Num,ClientMapMessage &Mes)
	{
		for (int i=0;i<15;++i)
		{
			for (int j=0;j<15;++j)
			{
				Mes.Map[i][j] = gameServer[Num].ground->GroundFloor[i][j].type;
			}
		}
		for (int i = 0; i<gameServer[Num].playerNum;++i)
		{
			Mes.Pos[i].X = gameServer[Num].player[i].posX;
			Mes.Pos[i].Y = gameServer[Num].player[i].posY;
		}
	}
	void setGame(int Num,char *GameName,int MaxPlayer,int MapNo,int Maptype)
	{
		houses[Num].HouseNo = Num;
		houses[Num].setName(GameName);
		houses[Num].MaxPlayer = MaxPlayer;
		houses[Num].PlayerNum = 0;
		houses[Num].MapNo = MapNo;
		houses[Num].MapType = Maptype;
		for(int i=0;i<MaxPlayer;++i)
		{
			houses[Num].position[i]= 0;
		}
	}
	void PlayerEntry(int Num,SessionMessage user)
	{
		for(int i=0;i<houses[Num].MaxPlayer;++i)
		{
			if (houses[Num].position[i] == 0)
			{
				houses[Num].playerMessage[i].setID(user.ID);
				houses[Num].position[i] = 1;
				houses[Num].PlayerNum++;
				break;
			}
		}
	}
	void PlayerExit(int Num,SessionMessage user)
	{
		string name1,name2;
		name1 = user.ID;
		for(int i=0;i<houses[Num].MaxPlayer;++i)
		{
			name2 = houses[Num].playerMessage[i].ID;
			if (name1 == name2)
			{
				houses[Num].position[i] = 1;
				houses[Num].PlayerNum++;
				break;
			}
		}
		if (gameServer[Num].isStarted())
		{
			gameServer[Num].Exit(user.ID);//从游戏中退出
		}
	}
	void registeGame(int Num,int Port,const char *Address)//创建一个游戏
	{
		if (ReadingLock)
		{
			srand(time(0));
			do 
			{
				Sleep(rand()%100);
			} while (ReadingLock);
		}
		if (writeLock[Num])
		{
			srand(time(0));
			do 
			{
				Sleep(rand()%100);
			} while (writeLock[Num]);
		}
		writeLock[Num]=true;
		ReadingLock = true;
		gameNum++;
		used[Num] = true;
		refreshed[Num] = true;
		//server[Num] = ServerMessage();
		server[Num].port = Port;
		server[Num].setIP(Address);
		writeLock[Num]=false;
		ReadingLock = false;
	}
	int getGameNum()
	{
		return gameNum;
	}
	GamesMessage():ReadingLock(false)
	{
		memset(used,false,sizeof(bool)*MaxHouseNum);
		memset(refreshed,false,sizeof(bool)*MaxHouseNum);
		memset(writeLock,false,sizeof(bool)*MaxHouseNum);
	}
	//返回所有游戏信息,用于传送给所有大厅的用户
	void getSimpleMessage(HouseSimpleMessage &SimpleMessage)
	{
		if (ReadingLock)
		{
			srand(time(0));
			do 
			{
				Sleep(rand()%100);
			} while (ReadingLock);
		}
		ReadingLock = true;
		SimpleMessage.HouseNum=gameNum;
		for (int i=0,j=0;i<SimpleMessage.HouseNum;++i)
		{
			while(true)
			{
				if (used[j]=true)
				{
					SimpleMessage.house[i].setName(houses[j].HouseName);
					SimpleMessage.house[i].HouseNo = j;
					SimpleMessage.house[i].houseServer.setIP(server[j].IP);
					SimpleMessage.house[i].houseServer.port = server[j].port;
					SimpleMessage.house[i].MaxPlayer = 8;
					SimpleMessage.house[i].Player = 1;
					SimpleMessage.house[0].MapNo=1;
					SimpleMessage.house[0].MapType=1;
					break;
				}
				++j;
			}	
		}
		ReadingLock = false;
	}
	int getFreeRoom()
	{
		for (int i=0;i<MaxHouseNum;++i )
		{
			if (!used[i])//房间号未被使用
			{
				return i;
			}
		}
		return -1;
	}
	bool getGameServer(const int Num,ServerMessage &GameServer)
	{
		if (used[Num]==false)
		{
			return false;
		}
		GameServer.port = server[Num].port;
		GameServer.setIP(server[Num].IP);
		return true;
	}
	bool getOneHouseMessage(const int Num,oneHouseMessage &Mes)
	{
		if (used[Num]==false)
		{
			return false;
		}
		Mes = houses[Num];
		return true;
	}
};




GamesMessage collection;


DWORD WINAPI GameClientThread(LPVOID obj)//此函数处理用户与当前游戏服务器传送数据的逻辑,更新游戏信息buhu
{
	SendNumObject *myobj = (SendNumObject *)obj;
	CLientThread newThread = CLientThread(myobj->ClientSocket);
	SessionMessage seMes;
	if(!newThread.Recv(seMes))//接受客户端发来的验证信息
	{
		cout<<"接受验证信息失败，退出"<<endl;
		return -1;
	}
	//下边向登录服务器验证用户是否登录
	CheckMessage cMes = CheckLogin(seMes,LoginServer);
	newThread.Send(cMes);//向客户端返回登录验证是否成功
	if (cMes.IsOk)
	{
		cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"登陆验证成功,等待用户发起请求...."<<endl;
		while(true)
		{
			clock_t myclock = clock();
			NumberSend reqire = NumberSend();//获取客户请求
			if(!newThread.Recv(reqire))
			{
				cout<<"客户端断开连接";
				return -1;
			}
			CheckMessage cCreatMes;//c1
			oneHouseMessage hMes;//c0
			ClientKeysMessage kMes;//c4
			ClientMapMessage mMes;//c4
			int size;
			switch(reqire.num)
			{
			case 0://房间信息
				cout<<"Player:"<<seMes.ID<<" 加入游戏....."<<"开始配给"<<myobj->Num<<"房间信息..."<<endl;
				collection.PlayerEntry(myobj->Num,seMes);
				collection.getOneHouseMessage(myobj->Num,hMes);
				newThread.Send(hMes);
				cout<<"配给房间信息完成~"<<endl;
				break;
			case 1:
				cout<<"ID:"<<seMes.ID<<"开始游戏"<<endl;
				collection.gameServer[myobj->Num].StartGame(collection.houses[myobj->Num]);//应该判断是否是房主
				break;
			case 2:
				cout<<"ID:"<<seMes.ID<<"离开游戏"<<endl;
				collection.PlayerExit(myobj->Num,seMes);
				return -1;
				break;
			case 3:
				cout<<"ID:"<<seMes.ID<<"更新游戏信息"<<endl;
				collection.getOneHouseMessage(myobj->Num,hMes);
				newThread.Send(hMes);
				cout<<"配给房间信息完成~"<<endl;
				break;
			case 4:
				cout<<"ID:"<<seMes.ID<<"进入上传游戏信息循环...."<<endl;
				size = kMes.getSize();
				do 
				{
					cout<<"ID:"<<seMes.ID<<"上传游戏信息...."<<endl;
					if (!newThread.Recv(kMes,size))
					{
						collection.PlayerExit(myobj->Num,seMes);//断开连接 退出游戏
						cout<<"用户停止上传游戏按键信息，断开连接"<<endl;
						return -1;
					}
					collection.gameServer[myobj->Num].uploadKeys(seMes.ID, kMes.Dir,kMes.Space);
				} while (kMes.Space!=-1);
				break;
			case 5:
				cout<<"查询游戏是否开始";
				cCreatMes.IsOk = collection.gameServer[myobj->Num].isStarted();
				newThread.Send(cCreatMes);
				if (cCreatMes.IsOk)
				{
					collection.getMapMessage(myobj->Num,mMes);
					newThread.Send(mMes);
				}
				break;
			case 6://退出循环
				return -1;
				break;
			case 7://给客户端返回游戏内信息
				while(true)
				{
					collection.getMapMessage(myobj->Num,mMes);
					if(!newThread.Send(mMes))
					{
						return -1;
					}
					Sleep(10);
				}
				break;
			}
			int a = clock()-myclock;
			cout<<"time:"<<float(a)/1000.0;
		}
	}
	else
	{
		cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"登陆验证成功,客户端需要重新尝试连接";
	}
	//system("pause");
	return 0;
}
DWORD WINAPI GameMessageServerThread(LPVOID num)//专门接受客户端连接
{
	SendNumObject *obj;
	obj = (SendNumObject *)num;
	MOEServer server = MOEServer();
	collection.registeGame((*obj).Num,server.getPort(),server.getIP().c_str());//注册游戏信息交互线程
	server.SetThread(GameClientThread);
	server.run(*obj);
	return 0;
}
SendNumObject obj;
DWORD WINAPI GameThread(LPVOID num)//一局游戏的主进程
{
	int Num=*((int *)num);//对应oneGameMessage[Num] 获取游戏信息
	collection.setGame(Num,"New Game",8,-1,1);
	obj.Num = Num;
	HANDLE hThread = NULL;
	hThread = CreateThread(NULL, 0, GameMessageServerThread, (LPVOID)&obj, 0, NULL);//开启游戏的客户端连接接收线程
	CloseHandle(hThread);
	//下边为游戏逻辑，每帧判断炸泡等
	while(collection.houses[Num].PlayerNum>0||!collection.gameServer[Num].isStarted())//如果在游戏中人数又不大于零则退出游戏循环
	{
		if (!collection.gameServer[Num].pass())
		{
			cout<<"游戏时间到:";
			break;
		}
		Sleep(30);
	}
	cout<<"游戏结束"<<endl;
	return 0;
}


#endif