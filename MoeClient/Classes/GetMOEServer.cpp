#include "getMOEServer.h"
using namespace std;
ServerMessage GetMOEServer123(int Num)
{
	fstream f;
	char ch[240];
	f.open("server.ini");
	string temp1,temp2;
	if(f){
		int i;
		//for (i=0;!f.eof();i++)
		//{
		//	ch[i] = getch();
		//}
		//ch[i-1] = '\0';
		f.getline(ch,240);
		string temp = string(ch);
		temp1 = temp.substr(temp.find_first_of(" ")+1);
		f.getline(ch,240);
		temp = string(ch);
		temp2 = temp.substr(temp.find_first_of(" ")+1);
	}
	f.close();
	ServerMessage server;
	if (Num == 1)
	{
		server.setIP(temp1.substr(0,temp1.find_first_of(":")).c_str());
		string t = temp1.substr(temp1.find_first_of(":")+1);
		server.port = atoi(t.c_str());
	}
	else
	{
		server.setIP(temp2.substr(0,temp2.find_first_of(":")).c_str());
		string t = temp2.substr(temp2.find_first_of(":")+1);
		server.port = atoi(t.c_str());
	}
	return server;
}