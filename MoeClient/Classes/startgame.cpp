#include "startgame.h"
using namespace cocos2d;
ServerMessage mysm;
ClientMapMessage cmm1;
int nowtime;
bool isclose;
DWORD WINAPI RecvThread(LPVOID lpParameter)
{
	if(isclose==true)
		return 0;
	MOEClient* recvclient=new MOEClient(mysm.port,mysm.IP);
	SessionMessage recmsg2=recmsg1;
	recvclient->Send(recmsg2);
	CheckMessage chkmsg1;
	recvclient->Recv(chkmsg1);
	NumberSend num7;
	num7.num=7;
	recvclient->Send(num7);
	while(true){
		ClientMapMessage cmm2;
		recvclient->Recv(cmm2);
		cmm1=cmm2;
	}
	return 0;
}
DWORD WINAPI SendThread(LPVOID lpParameter)
{
	HANDLE hThread2 = CreateThread(NULL, 0, RecvThread, NULL, 0, NULL);
	MOEClient* gameclient=new MOEClient(mysm.port,mysm.IP);
	SessionMessage recmsg=recmsg1;
	gameclient->Send(recmsg);
	CheckMessage chkmsg;
	gameclient->Recv(chkmsg);
	NumberSend num1;
	num1.num=4;
	gameclient->Send(num1);
	while(true){
		if(isclose==true){
			NumberSend nsend;
			nsend.num=2;
			gameclient->Send(nsend);
			return 0;
		}
		Sleep(50);
		ClientKeysMessage ckm;
		if(my_Keyboard::Keys[MY_KEYS_SPACE])
			ckm.Space=1;
		else ckm.Space=0;
		if(my_Keyboard::Keys[MY_KEYS_UP])
			ckm.Dir=1;
		else if(my_Keyboard::Keys[MY_KEYS_DOWN])
			ckm.Dir=2;
		else if(my_Keyboard::Keys[MY_KEYS_LEFT])
			ckm.Dir=3;
		else if(my_Keyboard::Keys[MY_KEYS_RIGHT])
			ckm.Dir=4;
		else
			ckm.Dir=0;
		gameclient->Send(ckm);
	}
	return 0;
}
startgame::startgame()
{
	roomname="test";
	showmain();
}
startgame::startgame(ServerMessage sm,ClientMapMessage incmm,oneHouseMessage inohm)
{
	time=0;
	nowtime=0;
	gameserver=sm;
	cmm=incmm;
	ohm=inohm;
	roomname=ohm.HouseName;
	isclose=false;
	showmain();
}
void startgame::showmain()
{
	mysm=gameserver;
	CCSprite* pgameMain = CCSprite::create("image\\form\\game_main.png");
    pgameMain->setPosition(ccp(400,300));
	this->addChild(pgameMain);
	for(int i=0;i<8;i++)
	{	
		if(ohm.position[i]==0)
			playerlabel[i]=new userlabel();
		else
			playerlabel[i]=new userlabel(ohm.playerMessage[i].ID,ohm.playerMessage[i].userBody,0);
		playerlabel[i]->setPosition(ccp(622,445-i*51));
		this->addChild(playerlabel[i]);
	}
	CCSize roomlabelsize=CCSize(104,20);
	CCLabelTTF*	rmlabel = CCLabelTTF::create(roomname.c_str(), "arial", 15, roomlabelsize, TextHAlignment::LEFT);
	rmlabel->setPosition(ccp(780,580));
	this->addChild(rmlabel);
	showmap();
	showplayer();
	HANDLE hThread1 = CreateThread(NULL, 0, SendThread, NULL, 0, NULL);
	this->schedule( schedule_selector(startgame::update) );

	//创建退出按钮图片
	CCMenuItemImage *pexitItem = CCMenuItemImage::create(
		"image\\button\\ca_exit.png","image\\button\\ca_exit_selected.png",this,menu_selector(startgame::exitgame));
	//设置退出按钮位置
	pexitItem->setPosition(ccp(760,22+23));
	//添加菜单至界面中
	CCMenu* pexitMenu = CCMenu::create(pexitItem, NULL);
    pexitMenu->setPosition(CCPointZero);
	this->addChild(pexitMenu);
	if(turnonmusic1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(("music\\"+inttostr(ohm.MapType)+".mp3").c_str(), true);
}
void startgame::showmap()
{
	this->removeChild(thismap,true);
	thismap=new mymap(ohm.MapType,cmm.Map);
	thismap->setPosition(9,600-525-16);
	this->addChild(thismap,0);
}
void startgame::showplayer()
{
	for(int i=0;i<8;i++)
	{
		if(ohm.position[i]==1)
		{
			players[i]=player(ohm.playerMessage[i].ID,inttostr(ohm.playerMessage[i].userBody),cmm.Pos[i].X*8+9,600-cmm.Pos[i].Y*7+6,this);
		}
	}
}
void startgame::update(float delta)
{
	cmm=cmm1;
	nowtime+=1;
	showtime();
	showmap();
	for(int i=0;i<8;i++)
	{
		if(ohm.position[i]==1)
			players[i].move(cmm.Pos[i].X*8+12,600-cmm.Pos[i].Y*7+16,false);
	}
}
void startgame::showtime()
{
	if(nowtime%30==0){
		int second=nowtime/30;
		int minute=second/60;
		string zerolabel="";
		if(second-minute*60<10)
			zerolabel="0";
		else
			zerolabel="";
		CCSize timelabelsize=CCSize(200,40);
		CCSprite* timelabel = CCSprite::create("image\\form\\time_label.png");
		timelabel->setPosition(ccp(705,530));
		this->addChild(timelabel);
		CCLabelTTF*	minute_label = CCLabelTTF::create((inttostr(minute) + ":" + zerolabel + inttostr(second - minute * 60)).c_str(), "arial", 40, timelabelsize, TextHAlignment::LEFT);
		this->removeChild(minute_label,true);
		minute_label->setPosition(ccp(745,530));
		this->addChild(minute_label);
		if(second>=240)
		{
			MOEClient myclient=MOEClient(gameserver.port,gameserver.IP);
			SessionMessage recmsg=recmsg1;
			myclient.Send(recmsg);
			CheckMessage chkmsg;
			myclient.Recv(chkmsg);
			if(chkmsg.IsOk){
				NumberSend num2; num2.num=2;
				myclient.Send(num2);
				isclose=true;
				this->unschedule(schedule_selector(startgame::update));		
				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
				this->removeAllChildrenWithCleanup(true);
				cr* mycr=new cr(mychoosehsm,mychoosehsw,mychoosearea);
				this->addChild(mycr);
			}
		}
	}
}
void startgame::showpower()
{
}
void startgame::showmyself()
{
}
void startgame::exitgame(CCObject* pSender)
{if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	MOEClient myclient=MOEClient(gameserver.port,gameserver.IP);
	SessionMessage recmsg=recmsg1;
	myclient.Send(recmsg);
	CheckMessage chkmsg;
	myclient.Recv(chkmsg);
	if(chkmsg.IsOk){
		NumberSend num2; num2.num=2;
		myclient.Send(num2);
		isclose=true;
		this->unschedule(schedule_selector(startgame::update));		
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		this->removeAllChildrenWithCleanup(true);
		cr* mycr=new cr(mychoosehsm,mychoosehsw,mychoosearea);
		this->addChild(mycr);
	}
	else
	{
		message* msg=new message("connect to server failed");
		this->addChild(msg);
	}
}

userlabel::userlabel()
{
	playername="";
	playermod=1;
	shownum=0;
	showlabel();
}
userlabel::userlabel(string pn,int pm,int num)
{
	playername=pn;
	playermod=pm;
	shownum=num;
	showlabel();
	showhead();
}
void userlabel::showlabel()
{
	//设置主界面
	CCSprite* proomMain = CCSprite::create("image\\form\\userlabel_main.png");
	//设定主界面显示位置并添加入layer中
    proomMain->setPosition(ccp(87,24));
	this->addChild(proomMain);
}
void userlabel::showhead()
{
	CCSize mysize=CCSize(104,17);
	CCLabelTTF*	namelabel = CCLabelTTF::create(playername.c_str(), "arial", 14, mysize, TextHAlignment::LEFT);
	namelabel->setPosition(ccp(140,24));
	this->addChild(namelabel);
	CCSprite* pm = CCSprite::create(("image\\player\\" + inttostr(playermod) + "\\down1.png").c_str(), CCRectMake(30, 45, 40, 40));
	pm->setPosition(ccp(60,24));
	this->addChild(pm);
}