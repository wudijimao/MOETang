#ifndef MESSAGE_H
#define MESSAGE_H
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "login.h"
#include "SimpleAudioEngine.h"
class message: public cocos2d::CCLayer
{
public:
	message();
	message(string inmsg);
	message(string inmsg,int inx,int iny);
	void showmessage();
	virtual void menuCloseCallback(cocos2d::CCObject* pSender);
private:
	string msg;//��ʾ��Ϣ��������ʾһ�У�
	int X;//������
	int Y;//������
};
#endif