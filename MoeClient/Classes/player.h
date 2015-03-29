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
	cocos2d::CCLayer* parent;//������
	string username;//�û�����
	string playermod;//��������
	int positionX;//������
	int positionY;//������
	int faceto;//����
	int newX;//�º�����
	int newY;//��������
	bool isdie;//�Ƿ�����
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