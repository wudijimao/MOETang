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

//��Ϣ�շ����߳� ����������������Ϣ�ķַ��͸���ά���������û���Ϣ�Ĳ�ѯ��ά��
DWORD WINAPI MessageClientThread(LPVOID lpParameter)
{
	threadBegin();
	CLientThread newThread = CLientThread((SOCKET)lpParameter);
	SessionMessage seMes;
	newThread.Recv(seMes);//���ܿͻ��˷�������֤��Ϣ

	if(string(seMes.ID)==ServerID&&seMes.session==ServerSession)
	{
		//���������������ύ��æ��¼
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
		newThread.Send(cMes);//��ͻ��˷��ص�¼��֤�Ƿ�ɹ�
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
bool HallServerCollection::AddServer(int Workload,ServerMessage Server)//true �ɹ����,false ���²���
{
	//ѭ������Ƿ��Ѿ�ע���
	for (int i=0;i<workload.serverNum;++i)
	{
		if (string(workload.server[i].IP)==string(Server.IP)&&workload.server[i].port==Server.port)
		{
			//ע��������¸�����Ϣ
			workload.workload[i]=Workload;
			return false;
		}
	}
	//δע��� ע��
	workload.workload[workload.serverNum]=Workload;
	workload.server[workload.serverNum]=Server;
	++workload.serverNum;
	return true;
}