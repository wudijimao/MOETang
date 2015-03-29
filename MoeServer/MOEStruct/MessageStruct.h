#ifndef MESSAGE_STRUCT_H
#define MESSAGE_STRUCT_H
#include <string>
using namespace std;


#define login_PORT 4000
#define login_IP "192.168.1.111"
#define hallSelect_PORT 4001
#define hallSelect_IP "192.168.1.111"

#define hall_PORT1 4002
#define hall_IP1 "192.168.1.111"


#define ServerID "99999$^%%$"
#define ServerSession 98735425
#define ServerPassWord "545123$%^"

#define MaxHouseNum 128


struct Message
{
public:
	virtual int getSize()
	{
		return sizeof(Message);
	}
};
struct NumberSend: Message
{
	int num;
	int getSize()
	{
		return sizeof(NumberSend);
	}
};
struct StringSend: Message
{
	char Str[128];
	void setStr(const char *id)
	{
		int i;
		for (i=0;*id!='\0';++i,++id)
		{
			Str[i] = *id;
		}
		Str[i] = *id;
	}
	int getSize()
	{
		return sizeof(StringSend);
	}
};
//��½�û���������Ϣ
struct LoginMessage:Message
{
	char ID[16];
	char PassWord[16];
	void setID(const char *id)
	{
		int i;
		for (i=0;*id!='\0';++i,++id)
		{
			ID[i] = *id;
		}
		ID[i] = *id;
	}
	void setPassword(const char *Password)
	{
		int i;
		for (i=0;*Password!='\0';++i,++Password)
		{
			PassWord[i] = *Password;
		}
		PassWord[i] = *Password;
	}
	int getSize()
	{
		return sizeof(LoginMessage);
	}
};
//��¼��֤���ݵĽṹ
struct SessionMessage:Message
{
	char ID[16];
	int session;
	void setID(const char *id)
	{
		int i;
		for (i=0;*id!='\0';++i,++id)
		{
			ID[i] = *id;
		}
		ID[i] = *id;
	}
	int getSize()
	{
		return sizeof(SessionMessage);
	}
};
//���ڷ��ͷ�����IP�Ͷ˿���Ϣ
struct ServerMessage:Message
{
	int port;
	char IP[16];
	void setIP(const char *ip)
	{
		int i;
		for (i=0;*ip!='\0';++i,++ip)
		{
			IP[i] = *ip;
		}
		IP[i] = *ip;
	}
	int getSize()
	{
		return sizeof(ServerMessage);
	}
};
//���ڷ�����������֤��ȷ������֤��Ϣ��
struct CheckMessage:Message
{
	bool IsOk;
	CheckMessage()
	{
		IsOk = false;
	}
	int getSize()
	{
		return sizeof(CheckMessage);
	}
};
//��������������Ϣ
struct oneHallServerWorkload:Message
{
	ServerMessage server;
	int workload;
	int getSize()
	{
		return sizeof(oneHallServerWorkload);
	}
};
//���ڷ������д�����������æ��Ϣ
struct HallServerWorkload:Message
{
	int serverNum;
	int workload[16];//��������:0-100;-1������ֹ����
	ServerMessage server[16];
	int getSize()
	{
		return sizeof(HallServerWorkload);
	}
};

//�����������Ϣ
struct HouseSimple
{
	ServerMessage houseServer;
	int HouseNo;
	char HouseName[64];
	int MaxPlayer;
	int Player;
	int MapNo;
	int MapType;
	void setName(char *name)
	{
		int i;
		for (i=0;*name!='\0';++i,++name)
		{
			HouseName[i] = *name;
		}
		HouseName[i] = *name;
	}
};
//���ڷ������з�����Ϣ
struct HouseSimpleMessage:Message
{
	int HouseNum;
	HouseSimple house[128];
	int getSize()
	{
		return sizeof(HouseSimpleMessage);
	}
};
//�����û���Ϣ���������ϣ�
struct UserMessage:Message
{
	//�û�����
	int userBody;
	int userHead;
	int userBomb;//�׵���ʽ
	int brith_year;
	int brith_month;
	int brith_day;
	int sex;//�У�Ů��δ֪
	int getSize()
	{
		return sizeof(UserMessage);
	}
};
//������Ϸ����Ϣ
struct PlayerMessage:Message
{
	char ID[16];
	void setID(const char *id)
	{
		int i;
		for (i=0;*id!='\0';++i,++id)
		{
			ID[i] = *id;
		}
		ID[i] = *id;
	}
	//�û�����
	int userBody;
	int userHead;
	int userBomb;//�׵���ʽ
	int getSize()
	{
		return sizeof(PlayerMessage);
	}
};
struct oneHouseMessage:Message
{
	int HouseNo;
	char HouseName[64];
	int MaxPlayer;
	int PlayerNum;
	int position[8];//�򿪣�����,�ر�
	PlayerMessage playerMessage[8];
	int MapNo;//-1  �����ͼ
	int MapType;// 1 ����
	void setName(char *name)
	{
		int i;
		for (i=0;*name!='\0';++i,++name)
		{
			HouseName[i] = *name;
		}
		HouseName[i] = *name;
	}
	int getSize()
	{
		return sizeof(oneHouseMessage);
	}
};
struct PlayerPosition
{
	int X;
    int Y;
};
struct ClientMapMessage:Message//�����������ͻ��˵ĵ�ͼ��Ϣ
{
	int Map[15][15];
	PlayerPosition Pos[8];
	int getSize()
	{
		return sizeof(ClientMapMessage);
	}
};
struct ClientKeysMessage:Message//�ͻ��˴����������İ�����Ϣ
{
	int Dir;// ��ʾ��ǰ���ﰴ�������������ĸ�������0=δ����1=�����£�2=�����£�3=�����£�4=�����¡�
	int Space;// ��ʾ�����Ƿ����˿ո��,0=δ��,1=����
	int getSize()
	{
		return sizeof(ClientKeysMessage);
	}
};
#endif