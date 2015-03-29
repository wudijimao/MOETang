
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
	CCSprite* pmsgMain=CCSprite::spriteWithFile("image\\form\\message.png");
	//设定主界面显示位置并添加入layer中
    pmsgMain->setPosition(ccp(X,Y));
	this->addChild(pmsgMain);
	//创建关闭按钮图片
	CCMenuItemImage *pmsgCloseItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\message_close.png","image\\button\\message_close_selected.png",this,menu_selector(message::menuCloseCallback));
	//设置关闭按钮位置
	pmsgCloseItem->setPosition(ccp(X-4,Y-133));
	//添加菜单至界面中
	CCMenu* pmsgCloseMenu = CCMenu::menuWithItems(pmsgCloseItem, NULL);
    pmsgCloseMenu->setPosition(CCPointZero);
    this->addChild(pmsgCloseMenu);
	//设置提示信息框大小
	CCSize mysize=CCSize(300,200);
	//初始化提示信息框
	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(msg.c_str(),mysize,CCTextAlignmentLeft,"Thonburi",14);
	//设置提示信息框位置
	pLabel->setPosition(ccp(X,Y+80));
	this->addChild(pLabel);
}
//点击关闭按钮时调用
void message::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	this->getParent()->removeChild(this,true);
}