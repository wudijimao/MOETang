#ifndef MESSAGE_STRUCT_H
#define MESSAGE_STRUCT_H
#include <string>
using namespace std;

struct Message
{
public:
	virtual int getSize()
	{
		return sizeof(Message);
	}
};
struct MM: Message
{
	int a;
	int getSize()
	{
		return sizeof(MM);
	}
};
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
	//LoginMessage()
	//{
	//	ID=new char[16];
	//	PassWord = new char[16];
	//}
	int getSize()
	{
		return sizeof(LoginMessage);
	}
};
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
struct CheckMessage:Message
{
	bool IsOk;
	int getSize()
	{
		return sizeof(CheckMessage);
	}
};
#endif