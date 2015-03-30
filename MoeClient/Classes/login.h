#ifndef LOGIN_H
#define LOGIN_H
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "MessageStruct.h"
#include "Global variables.h"
#include "MOEClient.h"
#include "message.h"
#include"getMOEServer.h"
#include "ca.h"
#include<iostream>
#include<windows.h>
#include <time.h>
class login: public cocos2d::Layer
{
public:
	CREATE_FUNC(login);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    void showconview();
    // a selector callback
    virtual void menuCloseCallback(cocos2d::CCObject* pSender);
	virtual void menulogin(cocos2d::CCObject* pSender);
	virtual void choosePW(cocos2d::CCObject* pSender);
	virtual void chooseQQ(cocos2d::CCObject* pSender);
	virtual void closeconview(cocos2d::CCObject* pSender);
	void sendmsg(string inid,string inpw);
    // implement the "static node()" method manually
private:
	cocos2d::CCSprite* pConView;//������ʾ��
	cocos2d::CCMenu* pLoginConClose;//�����˳���ť
	cocos2d::CCTextFieldTTF* pLoginQQInput;//�˺������
	cocos2d::CCTextFieldTTF* pLoginPWInput;//���������
	int isconsuccess;//�Ƿ����ӳɹ�(0Ϊ�ȴ����ӣ�1Ϊ���ӳɹ���2Ϊ����ʧ��)
	HouseSimpleMessage hsm;
};

#endif 