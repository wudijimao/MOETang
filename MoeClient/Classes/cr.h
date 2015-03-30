#ifndef CR_H
#define CR_H
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "MessageStruct.h"
#include "Global variables.h"
#include "message.h"
#include "MOEClient.h"
#include "enterroom.h"
#include<time.h>
#include<Windows.h>
using namespace std;
class room: public cocos2d::CCLayer
{
public:
	room();
	room(int inX,int inY,int inroomID,int inroomclass,char inroomname[],int inmaxusernum,int innowusernum);
	void showroom();
private:
	int X;
	int Y;
	int roomID;
	int roomclass;
	string roomname;
	int maxusernum;
	int nowusernum;
};
class cr: public cocos2d::CCLayer
{
public:
	cr();
	cr(HouseSimpleMessage inhsm,HallServerWorkload hsw,int inarea);
	void showcr();
	void addroom();
	void showpage();
	void showad();
	void showbutton5();
	void update(float delta);
	virtual void leftpageclick(cocos2d::CCObject* pSender);
	virtual void rightpageclick(cocos2d::CCObject* pSender);

	virtual void newtestclick(cocos2d::CCObject* pSender);
	virtual void fastjoinclick(cocos2d::CCObject* pSender);
	virtual void createroomclick(cocos2d::CCObject* pSender);
	virtual void userinfoclick(cocos2d::CCObject* pSender);

	virtual void menuCloseCallback(cocos2d::CCObject* pSender);

	virtual void chooseroom(cocos2d::CCObject* pSender);
private:
	int time1;
	int area;
	int mychoose;//选择的房间
	int roomnum;//房间数量
	room* myroom[8];//房间数组
	int page;//当前页数
	cocos2d::CCMenuItemImage* pcrchooseItem[16];
	cocos2d::CCMenu* pcrchooseMenu[16];
	HouseSimpleMessage hsm;
	HallServerWorkload hsw;
	HouseSimpleMessage roomhsm;
};
#endif
