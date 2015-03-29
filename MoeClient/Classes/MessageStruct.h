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
//登陆用户名密码信息
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
//登录验证数据的结构
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
//用于发送服务器IP和端口信息
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
//用于服务器返回验证正确与否的验证信息块
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
//单个大厅负载信息
struct oneHallServerWorkload:Message
{
	ServerMessage server;
	int workload;
	int getSize()
	{
		return sizeof(oneHallServerWorkload);
	}
};
//用于返回所有大厅服务器繁忙信息
struct HallServerWorkload:Message
{
	int serverNum;
	int workload[16];//工作负荷:0-100;-1代表终止工作
	ServerMessage server[16];
	int getSize()
	{
		return sizeof(HallServerWorkload);
	}
};

//单个房间简单信息
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
//用于返回所有房间信息
struct HouseSimpleMessage:Message
{
	int HouseNum;
	HouseSimple house[128];
	int getSize()
	{
		return sizeof(HouseSimpleMessage);
	}
};
//单个用户信息（个人资料）
struct UserMessage:Message
{
	//用户形象
	int userBody;
	int userHead;
	int userBomb;//雷的样式
	int brith_year;
	int brith_month;
	int brith_day;
	int sex;//男，女，未知
	int getSize()
	{
		return sizeof(UserMessage);
	}
};
//单个游戏者信息
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
	//用户形象
	int userBody;
	int userHead;
	int userBomb;//雷的样式
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
	int position[8];//打开，有人,关闭
	PlayerMessage playerMessage[8];
	int MapNo;//-1  随机地图
	int MapType;// 1 比武
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
struct ClientMapMessage:Message//服务器传给客户端的地图信息
{
	int Map[15][15];
	PlayerPosition Pos[8];
	int getSize()
	{
		return sizeof(ClientMapMessage);
	}
};
struct ClientKeysMessage:Message//客户端传给服务器的按键信息
{
	int Dir;// 表示当前人物按下了上下左右哪个按键，0=未按，1=↑按下，2=↓按下，3=←按下，4=→按下。
	int Space;// 表示人物是否按下了空格键,0=未按,1=按下
	int getSize()
	{
		return sizeof(ClientKeysMessage);
	}
};
#endif