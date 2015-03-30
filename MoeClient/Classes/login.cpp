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
		//�����뿪��ťͼƬ
		CCMenuItemImage *pLoginExitItem=CCMenuItemImage::create(
			"image\\button\\login_exit.png","image\\button\\login_exit_selected.png",this,menu_selector(login::menuCloseCallback));
		CC_BREAK_IF(! pLoginExitItem);
		//�����뿪��ťλ��
		pLoginExitItem->setPosition(ccp(731,212));
		//��Ӳ˵���������
		CCMenu* pLoginExitMenu = CCMenu::create(pLoginExitItem, NULL);
        pLoginExitMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pLoginExitMenu);
        this->addChild(pLoginExitMenu, 1);
		//������¼��ťͼƬ
		CCMenuItemImage *pLoginLoginItem = CCMenuItemImage::create(
			"image\\button\\login_login.png","image\\button\\login_login_selected.png",this,menu_selector(login::menulogin));
		CC_BREAK_IF(! pLoginLoginItem);
		//���õ�¼��ťλ��
		pLoginLoginItem->setPosition(ccp(665,212));
		//��Ӳ˵���������
		CCMenu* pLoginLoginMenu = CCMenu::create(pLoginLoginItem, NULL);
        pLoginLoginMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pLoginLoginMenu);
        this->addChild(pLoginLoginMenu, 2);
		//�趨������С
		CCSize Inputsize=CCSize(115,25);
		//�趨�����������ɫ
		ccColor3B mycolor=ccc3(255,255,255);
		//�趨�������������
		char font_family[]="Thonburi";
		//�趨��������ִ�С
		float font_size=25;
		//��ʼ��QQ�������
		pLoginQQInput = CCTextFieldTTF::textFieldWithPlaceHolder("", Inputsize, TextHAlignment::LEFT, font_family, font_size);
		pLoginQQInput->setColor(mycolor);
		CCMenuItemImage *pLoginQQItem = CCMenuItemImage::create(
			"image\\others\\Input.png","image\\others\\Input.png",this,menu_selector(login::chooseQQ));
		pLoginQQItem->setPosition(ccp(640,370));
		CCMenu* pQQItemMenu = CCMenu::create(pLoginQQItem, NULL);
        pQQItemMenu->setPosition(CCPointZero);
        this->addChild(pQQItemMenu);
		//�趨QQ�������λ�ã���ȡ���㲢���������
		pLoginQQInput->setPosition(ccp(640,370));
		pLoginQQInput->attachWithIME();
		this->addChild(pLoginQQInput,3);
		//��ʼ�����������
		pLoginPWInput = CCTextFieldTTF::textFieldWithPlaceHolder("", Inputsize, TextHAlignment::LEFT, font_family, font_size);
		pLoginPWInput->setColor(mycolor);
		//�趨���������λ�ã����������
		CCMenuItemImage *pLoginPWItem = CCMenuItemImage::create(
			"image\\others\\Input.png","image\\others\\Input.png",this,menu_selector(login::choosePW));
		CCMenu* pPWItemMenu = CCMenu::create(pLoginPWItem, NULL);
        pPWItemMenu->setPosition(CCPointZero);
        this->addChild(pPWItemMenu);
		pLoginPWItem->setPosition(ccp(640,325));
		pLoginPWInput->setPosition(ccp(640,325));
		this->addChild(pLoginPWInput,4);
		//����������
		CCSprite* pLoginMain = CCSprite::create("image\\form\\login_main.png");
        CC_BREAK_IF(! pLoginMain);
		//����������λ��
        pLoginMain->setPosition(ccp(400,300));
		//����������Ϊ�ӽ�����ӽ�FORM��
		this->addChild(pLoginMain,0);
		//���ű�������
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music\\M09.mp3", true);
        bRet = true;
    } while (0);

    return bRet;
}
//����ύ��ťʱ����
void login::menulogin(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	string ID=pLoginQQInput->getString();//���������ID
	string PW=pLoginPWInput->getString();//�������������
	ID=ID.substr(0,15);//��ȡ�̶�����
	PW=PW.substr(0,15);
	userID=ID;
	//�޷�����ʱ������
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


	//�������������Ϣ
	////////////////////////////////////////////////////////////
	isconsuccess=0;//׼����ʼ����
	sendmsg(ID,PW);
	//showconview();
	while(suc==0)
	{
		Sleep(100);//���շ��ز���
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
//ѡ����������ʱ���ã�ȡ��ID����򽹵㣬����������ȡ����
void login::choosePW(CCObject* pSender)
{
	pLoginQQInput->detachWithIME();
	pLoginPWInput->attachWithIME();
}
//ѡ������IDʱ���ã�ȡ����������򽹵㣬ID������ȡ����
void login::chooseQQ(CCObject* pSender)
{
	pLoginPWInput->detachWithIME();
	pLoginQQInput->attachWithIME();
}
//����رհ�ťʱ����
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
	///�д���δ���
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	pConView = CCSprite::create("image\\form\\login_con.png");
    pConView->setPosition(ccp(400,300));
	this->addChild(pConView);
	CCMenuItemImage *pLoginConItem = CCMenuItemImage::create(
		"image\\button\\login_con_close.png","image\\button\\login_con_close_selected.png",this,menu_selector(login::closeconview));
	//���ùرհ�ťλ��
	pLoginConItem->setPosition(ccp(400,273));
	//��Ӳ˵���������
	pLoginConClose = CCMenu::create(pLoginConItem, NULL);
    pLoginConClose->setPosition(CCPointZero);
    this->addChild(pLoginConClose);
}