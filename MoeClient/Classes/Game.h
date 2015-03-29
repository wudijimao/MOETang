#ifndef GAME_H
#define GAME_H
#include <vector>
#include <windows.h>
#include <time.h>
#include "MOEServer.h"
#include "MOEClient.h"
#include "game/Server.h"


#define login_PORT 4000
#define login_IP "192.168.1.111"
#define hallSelect_PORT 4001
#define hallSelect_IP "192.168.1.111"



#define ServerID "99999$^%%$"
#define ServerSession 98735425
#define ServerPassWord "545123$%^"
#define MaxHouseNum 128


class GamesMessage
{
private:
	oneHouseMessage houses[MaxHouseNum];
	ServerMessage server[MaxHouseNum];
	bool writeLock[MaxHouseNum];//д����
	bool refreshed[MaxHouseNum];//��Ƿ�����Ϣ�Ƿ�ˢ�¹�
	bool used[MaxHouseNum];//�����Ƿ�ʹ��
	
	bool ReadingLock;//ȫ����
	int gameNum;//��Ϸ����
public:
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
			gameServer[Num].Exit(user.ID);//����Ϸ���˳�
		}
	}
	void registeGame(int Num,int Port,const char *Address)//����һ����Ϸ
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
	//����������Ϸ��Ϣ,���ڴ��͸����д������û�
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
			if (!used[i])//�����δ��ʹ��
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


DWORD WINAPI GameClientThread(LPVOID obj)//�˺��������û��뵱ǰ��Ϸ�������������ݵ��߼�,������Ϸ��Ϣbuhu
{
	SendNumObject *myobj = (SendNumObject *)obj;
	CLientThread newThread = CLientThread(myobj->ClientSocket);
	SessionMessage seMes;
	newThread.Recv(seMes);//���ܿͻ��˷�������֤��Ϣ

	//�±����¼��������֤�û��Ƿ��¼
	CheckMessage cMes = CheckLogin(seMes);
	newThread.Send(cMes);//��ͻ��˷��ص�¼��֤�Ƿ�ɹ�
	if (cMes.IsOk)
	{
		cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"��½��֤�ɹ�,�ȴ��û���������...."<<endl;
		NumberSend reqire;//��ȡ�ͻ�����
		while(true)
		{
			newThread.Recv(reqire);
			CheckMessage cCreatMes;//c1
			oneHouseMessage hMes;//c0
			ClientKeysMessage kMes;//c4
			ClientMapMessage mMes;//c4
			switch(reqire.num)
			{
			case 0://������Ϣ
				cout<<"Player:"<<seMes.ID<<" ������Ϸ....."<<"��ʼ���"<<myobj->Num<<"������Ϣ..."<<endl;
				collection.PlayerEntry(myobj->Num,seMes);
				collection.getOneHouseMessage(myobj->Num,hMes);
				newThread.Send(hMes);
				cout<<"���������Ϣ���~"<<endl;
				break;
			case 1:
				cout<<"ID:"<<seMes.ID<<"��ʼ��Ϸ"<<endl;
				collection.gameServer[myobj->Num].StartGame();//Ӧ���ж��Ƿ��Ƿ���
				break;
			case 2:
				cout<<"ID:"<<seMes.ID<<"�뿪��Ϸ"<<endl;
				collection.PlayerExit(myobj->Num,seMes);
				goto GAME_EXIT;
				break;
			case 3:
				cout<<"ID:"<<seMes.ID<<"������Ϸ��Ϣ"<<endl;
				collection.getOneHouseMessage(myobj->Num,hMes);
				newThread.Send(hMes);
				cout<<"���������Ϣ���~"<<endl;
				break;
			case 4:
				cout<<"ID:"<<seMes.ID<<"�ϴ���Ϸ��Ϣ...."<<endl;
				newThread.Recv(kMes);
				collection.gameServer[myobj->Num].uploadKeys(seMes.ID, kMes.Dir,kMes.Space);
				collection.getMapMessage(myobj->Num,mMes);
				newThread.Send(mMes);
				break;
			case 5:
				cout<<"��ѯ��Ϸ�Ƿ�ʼ";
				cCreatMes.IsOk = collection.gameServer[myobj->Num].isStarted();
				newThread.Send(cCreatMes);
				if (cCreatMes.IsOk)
				{
					collection.getMapMessage(myobj->Num,mMes);
					newThread.Send(mMes);
				}
				break;
			}
		}
	}
	else
	{
		cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"��½��֤�ɹ�,�ͻ�����Ҫ���³�������";
	}
	//system("pause");
GAME_EXIT:
	return 0;
}
DWORD WINAPI GameMessageServerThread(LPVOID num)//ר�Ž��ܿͻ�������
{
	SendNumObject *obj;
	obj = (SendNumObject *)num;
	MOEServer server = MOEServer();
	collection.registeGame((*obj).Num,server.getPort(),server.getIP().c_str());//ע����Ϸ��Ϣ�����߳�
	server.SetThread(GameClientThread);
	server.run(*obj);
	return 0;
}
SendNumObject obj;
DWORD WINAPI GameThread(LPVOID num)//һ����Ϸ��������
{
	int Num=*((int *)num);//��ӦoneGameMessage[Num] ��ȡ��Ϸ��Ϣ
	collection.setGame(Num,"New Game",8,-1,1);
	obj.Num = Num;
	HANDLE hThread = NULL;
	hThread = CreateThread(NULL, 0, GameMessageServerThread, (LPVOID)&obj, 0, NULL);//������Ϸ�Ŀͻ������ӽ����߳�
	CloseHandle(hThread);
	//�±�Ϊ��Ϸ�߼���ÿ֡�ж�ը�ݵ�
	while(true)
	{
		if (!collection.gameServer[Num].pass())
		{
			break;
		}
		Sleep(300);
	}
	return 0;
}


#endif