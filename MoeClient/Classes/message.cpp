
#include "message.h"
using namespace cocos2d;

message::message()
{
	msg="";
	X=400;
	Y=300;
	showmessage();
}
message::message(string inmsg)
{
	msg=inmsg;
	X=400;
	Y=300;
	showmessage();
}
message::message(string inmsg,int inX,int inY)
{
	msg=inmsg;
	X=inX;
	Y=inY;
	showmessage();
}
void message::showmessage()
{
	CCSprite* pmsgMain=CCSprite::create("image\\form\\message.png");
	//�趨��������ʾλ�ò������layer��
    pmsgMain->setPosition(ccp(X,Y));
	this->addChild(pmsgMain);
	//�����رհ�ťͼƬ
	CCMenuItemImage *pmsgCloseItem=CCMenuItemImage::create(
		"image\\button\\message_close.png","image\\button\\message_close_selected.png",this,menu_selector(message::menuCloseCallback));
	//���ùرհ�ťλ��
	pmsgCloseItem->setPosition(ccp(X-4,Y-133));
	//��Ӳ˵���������
	CCMenu* pmsgCloseMenu = CCMenu::create(pmsgCloseItem, NULL);
    pmsgCloseMenu->setPosition(Point::ZERO);
    this->addChild(pmsgCloseMenu);
	//������ʾ��Ϣ���С
	CCSize mysize=CCSize(300,200);
	//��ʼ����ʾ��Ϣ��
	CCLabelTTF* pLabel = CCLabelTTF::create(msg.c_str(), "Thonburi", 14, mysize, TextHAlignment::LEFT);
	//������ʾ��Ϣ��λ��
	pLabel->setPosition(ccp(X,Y+80));
	this->addChild(pLabel);
}
//����رհ�ťʱ����
void message::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	this->getParent()->removeChild(this,true);
}