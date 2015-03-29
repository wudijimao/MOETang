#ifndef ENTERROOM_H
#define ENTERROOM_H
#include "cocos2d.h"
#include "MOEClient.h"
#include "MessageStruct.h"
#include "Global variables.h"
#include "startgame.h"
#include "message.h"
class enterroom: public cocos2d::CCLayer
{
public:
	enterroom();
	enterroom(bool host,oneHouseMessage inohm,ServerMessage insm);
	void showroom();
	void showplayers();
	void showplayername();
	void showbutton();
	void update(cocos2d::ccTime dt);
	virtual void start(cocos2d::CCObject* pSender);
	virtual void exitgame(cocos2d::CCObject* pSender);
	virtual void changeroomname(cocos2d::CCObject* pSender);
private:
	int time;
	ServerMessage roomserver;//房间服务器
	oneHouseMessage ohm;//房间信息
	bool ishost;//是否是房主
	string roomname;//房间名称
	int roomnum;//房间号
	int roomid;//地图编号
	int roomtype;//地图种类
	int maxplayer;//最大玩家数量
	int numplayer;//当前玩家数量
	string playernamestr[8];//玩家名字
	int playerbody[8];//玩家使用人物
	int playerhead[8];//玩家人物头部
	int playerbomb[8];//玩家使用糖泡样式
	cocos2d::CCLabelTTF* playername[8];
	cocos2d::CCSprite* player[8];
	cocos2d::CCTextFieldTTF* roomnameinput;

};


#endif