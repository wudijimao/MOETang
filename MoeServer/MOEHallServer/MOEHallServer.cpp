#include "../MOEServer/MOEServer.h"
#include "../MOEClient/MOEClient.h"
#include "Game.h"
#include <time.h>
oneHallServerWorkload workload;
ServerMessage LoginServer;
void UploadWorkload()
{
	//���͸�����Ϣ
	ServerMessage MessageServer = GetMOEServer(2);
	MOEClient WorkLoadSender = MOEClient(MessageServer.port,MessageServer.IP);
	SessionMessage seMes;
	seMes.setID(ServerID);
	seMes.session = ServerSession;
	WorkLoadSender.Send(seMes);
	workload.workload = (ConnectionNum*100)/1000;
	WorkLoadSender.Send(workload);
}

DWORD WINAPI ClientThread(LPVOID lpParameter)//����,ʵ��ʹ����Ҫ�Լ�д����������߼� ������setTread ���������
{
	CLientThread newThread = CLientThread((SOCKET)lpParameter);
	SessionMessage seMes;
	if (!newThread.Recv(seMes))//���ܿͻ��˷�������֤��Ϣ
	{
		cout<<"�ͻ��˴Ӵ����������쳣�Ͽ�"<<endl;
		return -1;
	}
	

	if(string(seMes.ID)==ServerID&&seMes.session==ServerSession)
	{
		//���������������������ѯ��æ��¼

	}
	else
	{
		CheckMessage cMes = CheckLogin(seMes,LoginServer);
		newThread.Send(cMes);//��ͻ��˷��ص�¼��֤�Ƿ�ɹ�
		if (cMes.IsOk)
		{
			cout<<"ID:"<<seMes.ID<<"  Session:"<<seMes.session<<"Login Check......OK,Waiting For Request...."<<endl;
			NumberSend reqire;//��ȡ�ͻ�����
			newThread.Recv(reqire);
			CheckMessage cCreatMes;//c1 c3
			NumberSend HNum;//c1�淿���
			HouseSimpleMessage hMes;//c0
			ServerMessage GameServer;
			//ServerMessage GameServer;
			int Num;
			switch(reqire.num)
			{
			case 0://��ȡ�����з�����Ϣ
				cout<<"Sending Houses' Messages ..."<<endl;
				collection.getSimpleMessage(hMes);
				newThread.Send(hMes);
				cout<<"Send All Right Completed!!!"<<endl;
				break;
			case 1://������Ϸ
				cout<<"ID:"<<seMes.ID<<"Creat Game!"<<endl;
				if (collection.getGameNum()<MaxHouseNum)
				{
					cCreatMes.IsOk = true;
					Num = collection.getFreeRoom();
					HNum.num = Num;
					HANDLE hThread = NULL;
					hThread = CreateThread(NULL, 0, GameThread, (LPVOID)&Num, 0, NULL);//������������߳�
					CloseHandle(hThread);
					newThread.Send(cCreatMes);//�ɹ���Ϣ
					newThread.Send(HNum);//�����
				}
				else
				{
					newThread.Send(cCreatMes);//ʧ��
				}
				break;
			case 2://������Ϸ
				cout<<"ID:"<<seMes.ID<<"Join Game!"<<endl;
				break;
			case 3://��ȡ�ض���Ϸ��������
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