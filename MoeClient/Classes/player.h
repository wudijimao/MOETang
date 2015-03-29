#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include "cocos2d.h"
using namespace std;
class player
{
public:
	player();
	player(string uname,string mod,int px,int py,cocos2d::CCLayer* p);
	void showplayer();
	void move(int nx,int ny,bool die);
	void change();
	void showname();
	void checkface();
private:
	cocos2d::CCLayer* parent;//父容器
	string username;//用户名称
	string playermod;//人物造型
	int positionX;//横坐标
	int positionY;//纵坐标
	int faceto;//朝向
	int newX;//新横坐标
	int newY;//新纵坐标
	bool isdie;//是否死亡
	cocos2d::CCRepeatForever* moveleft;
	cocos2d::CCRepeatForever* moveright;
	cocos2d::CCRepeatForever* moveup;
	cocos2d::CCRepeatForever* movedown;
	cocos2d::CCSprite* player0;
	cocos2d::CCSprite* player1;
	cocos2d::CCSprite* player2;
	cocos2d::CCSprite* player3;
	cocos2d::CCSprite* player4;
};
#endif