#include "player.h"
using namespace cocos2d;
player::player()
{
}
player::player(string uname,string mod,int px,int py,CCLayer* p)
{
	username=uname;
	playermod=mod;
	positionX=px;
	positionY=py;
	faceto=0;
	newX=px;
	newY=py;
	isdie=false;
	parent=p;
	showplayer();
	showname();
}
void player::showplayer()
{
	CCAnimation* animation1 = CCAnimation::create();
	CCAnimation* animation2 = CCAnimation::create();
	CCAnimation* animation3 = CCAnimation::create();
	CCAnimation* animation4 = CCAnimation::create();
    char frameName[100] = {0};
	int k=0;
	//读取图片创建动画
    for( int i=1;i<8;i++)
    {
		k=i;
		if(i>=4)
			k=i-4;
		sprintf(frameName, ("image//player//"+playermod+"//down%d.png").c_str(), k+1);
		animation1->addSpriteFrameWithFile(frameName);
        sprintf(frameName, ("image//player//"+playermod+"//left%d.png").c_str(), k+1);
		animation2->addSpriteFrameWithFile(frameName);
        sprintf(frameName, ("image//player//"+playermod+"//right%d.png").c_str(), k+1);
		animation3->addSpriteFrameWithFile(frameName);
        sprintf(frameName, ("image//player//"+playermod+"//up%d.png").c_str(), k+1);
		animation4->addSpriteFrameWithFile(frameName);
    }
	//初始化四个方向的移动动画
    CCActionInterval*  action1 = CCAnimate::create(animation1);
	action1->setDuration(1.0f);
	CCActionInterval*  action1_back = action1->reverse();
	CCActionInterval*  action2 = CCAnimate::create(animation1);
	action2->setDuration(1.0f);
	CCActionInterval*  action2_back = action2->reverse();
	CCActionInterval*  action3 = CCAnimate::create(animation1);
	action3->setDuration(1.0f);
	CCActionInterval*  action3_back = action3->reverse();
	CCActionInterval*  action4 = CCAnimate::create(animation1);
	action4->setDuration(1.0f);
	CCActionInterval*  action4_back = action4->reverse();
	//设定四个方向的重复移动动画
	movedown=CCRepeatForever::create(action1);
	moveleft = CCRepeatForever::create(action2);
	moveright = CCRepeatForever::create(action3);
	moveup = CCRepeatForever::create(action4);
	//初始化图片
	player0 = CCSprite::create(("image//player//"+playermod+"//down1.png").c_str(),CCRectMake(0, 0, 100, 100) );
	player1 = CCSprite::create(("image//player//" + playermod + "//down1.png").c_str(), CCRectMake(0, 0, 100, 100));
	player2 = CCSprite::create(("image//player//" + playermod + "//down1.png").c_str(), CCRectMake(0, 0, 100, 100));
	player3 = CCSprite::create(("image//player//" + playermod + "//down1.png").c_str(), CCRectMake(0, 0, 100, 100));
	player4 = CCSprite::create(("image//player//" + playermod + "//down1.png").c_str(), CCRectMake(0, 0, 100, 100));
	//设定初始坐标
	player0->setPosition( ccp(positionX,positionY));
	player1->setPosition( ccp(positionX,positionY));
	player2->setPosition( ccp(positionX,positionY));
	player3->setPosition( ccp(positionX,positionY));
	player4->setPosition( ccp(positionX,positionY));
	//设定动作
    player1->runAction(movedown);
    player2->runAction(moveleft);
    player3->runAction(moveright);
    player4->runAction(moveup);
	//添加入Layer中
	parent->addChild(player0,99);
	parent->addChild(player1,99);
	parent->addChild(player2,99);
	parent->addChild(player3,99);
	parent->addChild(player4,99);
	change();
}
void player::change()
{
	player0->setVisible(false);
	player1->setVisible(false);
	player2->setVisible(false);
	player3->setVisible(false);
	player4->setVisible(false);
	switch(faceto)
	{
	case 0:
		player0->setVisible(true);
		break;
	case 1:
		player1->setVisible(true);
		break;
	case 2:
		player2->setVisible(true);
		break;
	case 3:
		player3->setVisible(true);
		break;
	case 4:
		player4->setVisible(true);
		break;
	default:
		player0->setVisible(true);
	}
}
void player::move(int nx,int ny,bool die)
{
	isdie=die;
	//获取移动信息
	if(isdie==true)
	{
		faceto=-1;
		change();
		player0->setVisible(false);
	}
	else{
		newX=nx;
		newY=ny;
		checkface();
		change();
		positionX=newX;
		positionY=newY;
		player0->setPosition(ccp(newX,newY));
		player1->setPosition(ccp(newX,newY));
		player2->setPosition(ccp(newX,newY));
		player3->setPosition(ccp(newX,newY));
		player4->setPosition(ccp(newX,newY));
	}
}
void player::checkface()
{
	if(newX==positionX)
	{
		if(newY!=positionY){
			if(newY>positionY)
				faceto=4;
			else
				faceto=1;
		}
	}
	else if(newY==positionY)
	{
		if(newX!=positionX){
			if(newX>positionX)
				faceto=3;
			else
				faceto=2;
		}
	}
	else
	{
		faceto=-1;
	}
}
void player::showname()
{
	CCSize mysize=CCSize(100,15);
	CCLabelTTF* pname = CCLabelTTF::create(username.c_str(), "Thonburi", 14, mysize, TextHAlignment::LEFT);
	pname->setPosition(ccp(positionX,positionY));
	parent->addChild(pname);
}