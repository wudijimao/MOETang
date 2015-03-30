#include "login.h"
using namespace std;
using namespace cocos2d;
bool turnonmusic1;
bool turnonsound1;
string userID;
SessionMessage recmsg1;
bool isnoservertest=false;
int suc=0;
HallServerWorkload hsw;
CCScene* login::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        login *layer = login::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

void login::sendmsg(string inid,string inpw)
{
	LoginMessage sendmsg1;
	sendmsg1.setID(inid.c_str());
	sendmsg1.setPassword(inpw.c_str());
	ServerMessage sssss=GetMOEServer123(1);
	MOEClient myclient=MOEClient(sssss.port,sssss.IP);
	myclient.Send(sendmsg1);
	myclient.Recv(recmsg1);
	ServerMessage sermsg1;
	myclient.Recv(sermsg1);
	myclient.~MOEClient();
	MOEClient myclient1=MOEClient(sermsg1.port,sermsg1.IP);
	SessionMessage recmsg=recmsg1;
	myclient1.Send(recmsg);
	CheckMessage chkmsg1;
	myclient1.Recv(chkmsg1);
	if(chkmsg1.IsOk){
		myclient1.Recv(hsw);
		suc=1;
	}
	else 
		suc=2;
}
bool login::init()
{	
	turnonmusic1=true;
	turnonsound1=true;
	userID="";
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        CC_BREAK_IF(! CCLayer::init());
        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
		//创建离开按钮图片
		CCMenuItemImage *pLoginExitItem=CCMenuItemImage::create(
			"image\\button\\login_exit.png","image\\button\\login_exit_selected.png",this,menu_selector(login::menuCloseCallback));
		CC_BREAK_IF(! pLoginExitItem);
		//设置离开按钮位置
		pLoginExitItem->setPosition(ccp(731,212));
		//添加菜单至界面中
		CCMenu* pLoginExitMenu = CCMenu::create(pLoginExitItem, NULL);
        pLoginExitMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pLoginExitMenu);
        this->addChild(pLoginExitMenu, 1);
		//创建登录按钮图片
		CCMenuItemImage *pLoginLoginItem = CCMenuItemImage::create(
			"image\\button\\login_login.png","image\\button\\login_login_selected.png",this,menu_selector(login::menulogin));
		CC_BREAK_IF(! pLoginLoginItem);
		//设置登录按钮位置
		pLoginLoginItem->setPosition(ccp(665,212));
		//添加菜单至界面中
		CCMenu* pLoginLoginMenu = CCMenu::create(pLoginLoginItem, NULL);
        pLoginLoginMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pLoginLoginMenu);
        this->addChild(pLoginLoginMenu, 2);
		//设定输入框大小
		CCSize Inputsize=CCSize(115,25);
		//设定输入框文字颜色
		ccColor3B mycolor=ccc3(255,255,255);
		//设定输入框文字字体
		char font_family[]="Thonburi";
		//设定输入框文字大小
		float font_size=25;
		//初始化QQ号输入框
		pLoginQQInput = CCTextFieldTTF::textFieldWithPlaceHolder("", Inputsize, TextHAlignment::LEFT, font_family, font_size);
		pLoginQQInput->setColor(mycolor);
		CCMenuItemImage *pLoginQQItem = CCMenuItemImage::create(
			"image\\others\\Input.png","image\\others\\Input.png",this,menu_selector(login::chooseQQ));
		pLoginQQItem->setPosition(ccp(640,370));
		CCMenu* pQQItemMenu = CCMenu::create(pLoginQQItem, NULL);
        pQQItemMenu->setPosition(CCPointZero);
        this->addChild(pQQItemMenu);
		//设定QQ号输入框位置，获取焦点并添入界面中
		pLoginQQInput->setPosition(ccp(640,370));
		pLoginQQInput->attachWithIME();
		this->addChild(pLoginQQInput,3);
		//初始化密码输入框
		pLoginPWInput = CCTextFieldTTF::textFieldWithPlaceHolder("", Inputsize, TextHAlignment::LEFT, font_family, font_size);
		pLoginPWInput->setColor(mycolor);
		//设定密码输入框位置，添入界面中
		CCMenuItemImage *pLoginPWItem = CCMenuItemImage::create(
			"image\\others\\Input.png","image\\others\\Input.png",this,menu_selector(login::choosePW));
		CCMenu* pPWItemMenu = CCMenu::create(pLoginPWItem, NULL);
        pPWItemMenu->setPosition(CCPointZero);
        this->addChild(pPWItemMenu);
		pLoginPWItem->setPosition(ccp(640,325));
		pLoginPWInput->setPosition(ccp(640,325));
		this->addChild(pLoginPWInput,4);
		//创建主界面
		CCSprite* pLoginMain = CCSprite::create("image\\form\\login_main.png");
        CC_BREAK_IF(! pLoginMain);
		//设置主界面位置
        pLoginMain->setPosition(ccp(400,300));
		//将主界面作为子界面添加进FORM中
		this->addChild(pLoginMain,0);
		//播放背景音乐
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music\\M09.mp3", true);
        bRet = true;
    } while (0);

    return bRet;
}
//点击提交按钮时调用
void login::menulogin(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	string ID=pLoginQQInput->getString();//保存输入的ID
	string PW=pLoginPWInput->getString();//保存输入的密码
	ID=ID.substr(0,15);//截取固定长度
	PW=PW.substr(0,15);
	userID=ID;
	//无服务器时测试用
	if(isnoservertest==true){
		hsw.serverNum=15;
		for(int i=0;i<15;i++)
			hsw.workload[i]=99;
		hsw.workload[1]=100;
		this->removeAllChildrenWithCleanup(true);
		ca* ca1=new ca(true,true,hsw);
		this->addChild(ca1);
		return;
	}


	//与服务器交互信息
	////////////////////////////////////////////////////////////
	isconsuccess=0;//准备开始连接
	sendmsg(ID,PW);
	//showconview();
	while(suc==0)
	{
		Sleep(100);//接收返回参数
	}
	if(suc==1)
	{
		this->removeAllChildrenWithCleanup(true);
		ca* ca1=new ca(true,true,hsw);
		this->addChild(ca1);
	}
	else if(suc==2)
	{
		message* mymsg1=new message("Unable to connect to server");
		this->addChild(mymsg1);
	}
}
//选择输入密码时调用，取消ID输入框焦点，密码输入框获取焦点
void login::choosePW(CCObject* pSender)
{
	pLoginQQInput->detachWithIME();
	pLoginPWInput->attachWithIME();
}
//选择输入ID时调用，取消密码输入框焦点，ID输入框获取焦点
void login::chooseQQ(CCObject* pSender)
{
	pLoginPWInput->detachWithIME();
	pLoginQQInput->attachWithIME();
}
//点击关闭按钮时调用
void login::menuCloseCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
    CCDirector::sharedDirector()->end();
}
void login::closeconview(CCObject* pSender)
{
	this->removeChild(pConView,true);
	this->removeChild(pLoginConClose,true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
}
void login::showconview()
{
	///有错误，未解决
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	pConView = CCSprite::create("image\\form\\login_con.png");
    pConView->setPosition(ccp(400,300));
	this->addChild(pConView);
	CCMenuItemImage *pLoginConItem = CCMenuItemImage::create(
		"image\\button\\login_con_close.png","image\\button\\login_con_close_selected.png",this,menu_selector(login::closeconview));
	//设置关闭按钮位置
	pLoginConItem->setPosition(ccp(400,273));
	//添加菜单至界面中
	pLoginConClose = CCMenu::create(pLoginConItem, NULL);
    pLoginConClose->setPosition(CCPointZero);
    this->addChild(pLoginConClose);
}