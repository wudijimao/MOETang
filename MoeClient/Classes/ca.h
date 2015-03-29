#ifndef CA_H
#define CA_H
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "MessageStruct.h"
#include "Global variables.h"
#include "cocos2d.h"
#include "SimpleaudioEngine.h"
#include "message.h"
#include "cr.h"
#include "login.h"
#include "MOEClient.h"
class ca: public cocos2d::CCLayer
{
public:
	cocos2d::CCMenu* pcachooseMenu[16];
	cocos2d::CCMenuItemImage* pcachooseItem[16];
	ca(bool m,bool s,HallServerWorkload inhsw);
	cocos2d::CCSprite* delay[16][5];
	void showca();
	void showclick();
	virtual void menuCloseCallback(cocos2d::CCObject* pSender);
	virtual void ShowOptionMenu(cocos2d::CCObject* pSender);
	virtual void ShowMenu1(cocos2d::CCObject* pSender);
	virtual void ShowMenu2(cocos2d::CCObject* pSender);
	virtual void ShowMenu3(cocos2d::CCObject* pSender);
	virtual void ShowMenu4(cocos2d::CCObject* pSender);
	virtual void Showmsg(cocos2d::CCObject* pSender);
	void showbutton4();
	HallServerWorkload hsw;
private:
	string mychoose;

};
#endif