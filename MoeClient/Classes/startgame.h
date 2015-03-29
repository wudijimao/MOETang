#ifndef STARTGAME_H
#define STARTGAME_H
#include "my_Input.h"
#include "cocos2d.h"
#include "Global variables.h"
#include "player.h"
#include "mymap.h"
#include "MessageStruct.h"
#include "MOEClient.h"
#include "cr.h"
class userlabel:public cocos2d::CCLayer
{
public:
	userlabel();
	userlabel(string pn,int pm,int num);
	void showlabel();
	void showhead();
private:
	string playername;
	int playermod;
	int shownum;
};
class startgame:public cocos2d::CCLayer
{
public:
	startgame();
	startgame(ServerMessage sm,ClientMapMessage incmm,oneHouseMessage inohm);
	void showmain();
	void update(cocos2d::ccTime dt);
	void showtime();
	void showpower();
	void showmyself();
	void showplayer();
	void showmap();
	virtual void exitgame(cocos2d::CCObject* pSender);
private:
	my_Keyboard mykeyboard1;
	oneHouseMessage ohm;
	ServerMessage gameserver;
	ClientMapMessage cmm;
	int time;
	string roomname;
	player players[8];
	mymap* thismap;
	int myself;
	int key;
	bool isspace;
	userlabel* playerlabel[8];
};


#endif