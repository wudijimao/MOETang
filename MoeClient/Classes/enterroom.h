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
	ServerMessage roomserver;//���������
	oneHouseMessage ohm;//������Ϣ
	bool ishost;//�Ƿ��Ƿ���
	string roomname;//��������
	int roomnum;//�����
	int roomid;//��ͼ���
	int roomtype;//��ͼ����
	int maxplayer;//����������
	int numplayer;//��ǰ�������
	string playernamestr[8];//�������
	int playerbody[8];//���ʹ������
	int playerhead[8];//�������ͷ��
	int playerbomb[8];//���ʹ��������ʽ
	cocos2d::CCLabelTTF* playername[8];
	cocos2d::CCSprite* player[8];
	cocos2d::CCTextFieldTTF* roomnameinput;

};


#endif