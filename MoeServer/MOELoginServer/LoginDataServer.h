#ifndef LOGIN_DATA_SERVER_H
#define LOGIN_DATA_SERVER_H
#include "../MOEDataServer/MOEDataServer.h"
#include <sstream>
class LoginDataServer
{
	MOEDataServer server;
public:
	string getPassword(string username)
	{
		server.myselect("login","username='"+username+"'");
		if (server.isEnd())//未查询到信息
		{
			return "";
		}
		string a = server.getLineString("password");
		return server.getLineString("password");
	}
	int getSessionID(string username)
	{
		server.myselect("login","username='"+username+"'");
		return server.getLineInt("sessionID");
	}
	bool setSessionID(string username,int SessionID)
	{
		stringstream str;
		str<<"sessionID="<<SessionID;
		return server.myupdate("login","username='"+username+"'",str.str());
	}
	bool signup(string username,string password)
	{
		return server.myinsert("login","username,password","'"+username+"','"+password+"'");
	}
	bool unsign(string username)
	{
		return server.mydelete("login","username='"+username+"'");
	}
};
#endif