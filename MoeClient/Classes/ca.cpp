
#include "ca.h"
using namespace cocos2d;
HouseSimpleMessage mychoosehsm;
HallServerWorkload mychoosehsw;
int mychoosearea;
ca::ca(bool m,bool s,HallServerWorkload inhsw)
{
	hsw=inhsw;
	mychoose=-1;
	showca();
	showclick();
}
void ca::showca()
{
	//设置主界面
	CCSprite* pcaMain=CCSprite::spriteWithFile("image\\form\\ca_main.png");
	//设定主界面显示位置并添加入layer中
    pcaMain->setPosition(ccp(400,300));
	this->addChild(pcaMain);
	//播放背景音乐
	if(turnonmusic1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music\\das.mp3", true);
	//创建退出按钮图片
	CCMenuItemImage *pcaExitItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\ca_exit.png","image\\button\\ca_exit_selected.png",this,menu_selector(ca::menuCloseCallback));
	//设置退出按钮位置
	pcaExitItem->setPosition(ccp(743,56));
	//添加菜单至界面中
	CCMenu* pcaExitMenu = CCMenu::menuWithItems(pcaExitItem, NULL);
    pcaExitMenu->setPosition(CCPointZero);
    this->addChild(pcaExitMenu);
	//创建系统设置按钮图片
	CCMenuItemImage *pcaOptionItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\ca_option.png","image\\button\\ca_option_selected.png",this,menu_selector(ca::ShowOptionMenu));
	//设置系统设置按钮位置
	pcaOptionItem->setPosition(ccp(602,59));
	//添加菜单至界面中
	CCMenu* pcaOptionMenu = CCMenu::menuWithItems(pcaOptionItem, NULL);
    pcaOptionMenu->setPosition(CCPointZero);
    this->addChild(pcaOptionMenu);
	showbutton4();
}
void ca::showclick()
{
	for(int i=0;i<hsw.serverNum;++i)
	{
		//点击按钮
		pcachooseItem[i]=CCMenuItemImage::itemFromNormalImage(
		"image\\others\\choosearea.png","image\\others\\choosearea.png",this,menu_selector(ca::Showmsg));
		//设置按钮位置
		if(i%2!=0){
			//触发按钮位置
			pcachooseItem[i]->setPosition(ccp(476+198,489-(i-1)/2*29));
			if(hsw.workload[i]!=100)
				//wordload框位置
			for(int j=0;j<=hsw.workload[i]/20;j++){
				delay[i][j] =CCSprite::spriteWithFile("image\\others\\delay.png",CCRectMake((float)j*10, 0, 10, 16) );
				delay[i][j]->setPosition( ccp(476+198+10+j*13,489-(i-1)/2*29) );
				this->addChild(delay[i][j]);
			}
		}
		else{
			pcachooseItem[i]->setPosition(ccp(476,489-i/2*29));
				//wordload框位置
			if(hsw.workload[i]!=100)
			for(int j=0;j<=hsw.workload[i]/20;j++){
				delay[i][j] =CCSprite::spriteWithFile("image\\others\\delay.png",CCRectMake((float)j*10, 0, 10, 16) );
				delay[i][j]->setPosition(ccp(476+10+j*13,489-i/2*29));
				this->addChild(delay[i][j]);
			}
		}
		//添加菜单至界面中
		pcachooseMenu[i] = CCMenu::menuWithItems(pcachooseItem[i], NULL);
		(pcachooseMenu[i])->setPosition(CCPointZero);
		this->addChild(pcachooseMenu[i]);
	}
}
//点击退出按钮时调用
void ca::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
    CCDirector::sharedDirector()->end();
}
//点击系统设置按钮时调用
void ca::ShowOptionMenu(CCObject* pSender)
{
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	//点按钮打开打开网页    ShellExecute(NULL,L"open", L"http://www.baidu.com", NULL, NULL, SW_SHOWNORMAL); 

}
//选区时调用
void ca::Showmsg(CCObject* pSender)
{
	if(turnonsound1==true)	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	for(int i=0;i<hsw.serverNum;++i)
	{
		int x =(int)(((CCMenuItemImage *)pSender)->getPositionX());
		int y =(int)(((CCMenuItemImage *)pSender)->getPositionY());
		int x1=(int)(pcachooseItem[i]->getPositionX());
		int y1=(int)(pcachooseItem[i]->getPositionY());
		if(x1==x&&y1==y)//判断点中的LABEL
		{
			if(hsw.workload[i]==100){
				message* msg=new message("area"+inttostr(i+1)+" is full!");
				this->addChild(msg);
			}
			else
			{
				if(isnoservertest==true)
				{
					HouseSimpleMessage hsm;
					hsm.HouseNum=12;
					for(int j=0;j<12;i++)
					{
						char s[64]="test";
						hsm.house[j].HouseNo=i;
						strcpy_s(hsm.house[i].HouseName,s);
						//hsm.house[i].HouseName=s;
						hsm.house[j].MapNo=1;
						hsm.house[j].MapType=06;
						hsm.house[j].MaxPlayer=i/2+1;
						hsm.house[j].Player=i/2+1;
					}
					this->removeAllChildrenWithCleanup(true);
					cr* mycr=new cr(hsm,hsw,i);
					this->addChild(mycr);
				}
				else{
					mychoose=inttostr(i);
					MOEClient myclient=MOEClient(hsw.server[i].port,hsw.server[i].IP);
					SessionMessage recmsg2=recmsg1;
					myclient.Send(recmsg2);
					CheckMessage chkmsg1;
					myclient.Recv(chkmsg1);
					if(chkmsg1.IsOk){
						HouseSimpleMessage hsm;
						NumberSend num;
						num.num=0;
						myclient.Send(num);
						myclient.Recv(hsm);
						this->removeAllChildrenWithCleanup(true);
						cr* mycr=new cr(hsm,hsw,i);
						mychoosehsm=hsm;mychoosehsw=hsw;mychoosearea=i;
						this->addChild(mycr);
					}
					else
					{
						message* msg=new message("connect to server failed");
						this->addChild(msg);
					}
				}
			}
		}
	}
}
//点击打开音效时调用
void ca::ShowMenu1(CCObject* pSender)
{
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	turnonsound1=true;

}
//点击关闭音效时调用
void ca::ShowMenu2(CCObject* pSender)
{
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	turnonsound1=false;
}
//点击打开音乐时调用
void ca::ShowMenu3(CCObject* pSender)
{
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	if(turnonmusic1==false){
		turnonmusic1=true;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music\\das.mp3",true);
	}

}
//点击关闭音乐时调用
void ca::ShowMenu4(CCObject* pSender)
{
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	turnonmusic1=false;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}
void ca::showbutton4()
{
	
	//创建打开音效按钮图片
	CCMenuItemImage *pItem1=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\turnonsound.png","image\\button\\turnonsound_selected.png",this,menu_selector(ca::ShowMenu1));
	//设置按钮位置
	pItem1->setPosition(ccp(405,59));
	//添加菜单至界面中
	CCMenu* pMenu1 = CCMenu::menuWithItems(pItem1, NULL);
    pMenu1->setPosition(CCPointZero);
    this->addChild(pMenu1);

	CCMenuItemImage *pItem2=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\turnoffsound.png","image\\button\\turnoffsound_selected.png",this,menu_selector(ca::ShowMenu2));
	pItem2->setPosition(ccp(471,59));
	CCMenu* pMenu2 = CCMenu::menuWithItems(pItem2, NULL);
    pMenu2->setPosition(CCPointZero);
    this->addChild(pMenu2);

	CCMenuItemImage *pItem3=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\turnonmusic.png","image\\button\\turnonmusic_selected.png",this,menu_selector(ca::ShowMenu3));
	pItem3->setPosition(ccp(535,59));
	CCMenu* pMenu3 = CCMenu::menuWithItems(pItem3, NULL);
    pMenu3->setPosition(CCPointZero);
    this->addChild(pMenu3);

	CCMenuItemImage *pItem4=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\turnoffmusic.png","image\\button\\turnoffmusic_selected.png",this,menu_selector(ca::ShowMenu4));
	pItem4->setPosition(ccp(602,59));
	CCMenu* pMenu4 = CCMenu::menuWithItems(pItem4, NULL);
    pMenu4->setPosition(CCPointZero);
    this->addChild(pMenu4);
}
