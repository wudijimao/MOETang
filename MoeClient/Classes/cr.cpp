
#include "cr.h"
using namespace cocos2d;
cr::cr()
{
	time1=0;
	mychoose=-1;
	page=0;
	roomnum=12;
	showcr();
	this->schedule(schedule_selector(cr::update) );
}
cr::cr(HouseSimpleMessage inhsm,HallServerWorkload inhsw,int inarea)
{
	time1=0;
	area=inarea;
	mychoose=-1;
	page=0;
	hsw=inhsw;
	hsm=inhsm;
	roomnum=inhsm.HouseNum;
	showcr();
	this->schedule(schedule_selector(cr::update) );
}
void cr::showcr()
{
	//设置主界面
	CCSprite* pcrMain = CCSprite::create("image\\form\\cr_main.png");
	//设定主界面显示位置并添加入layer中
    pcrMain->setPosition(ccp(400,300));
	this->addChild(pcrMain);
	showpage();
	addroom();
	showad();
	showbutton5();
}
//向左翻页按钮点击时触发
void cr::leftpageclick(CCObject* pSender)
{
	if(turnonsound1==true)	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	page--;
	this->removeAllChildrenWithCleanup(true);
	showcr();
}
//向右翻页按钮点击时触发
void cr::rightpageclick(CCObject* pSender)
{
	if(turnonsound1==true)	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	page++;
	this->removeAllChildrenWithCleanup(true);
	showcr();
}
//添加并显示房间
void cr::addroom()
{
	int tempnum=roomnum-page*8;
	int dir=page*8;
	//循环
	for(int i=0;i<8;i++)
	{
		//添加按钮以接收点击信息
		pcrchooseItem[i] = CCMenuItemImage::create(
		"image\\others\\chooseroom.png","image\\others\\chooseroom.png",this,menu_selector(cr::chooseroom));
		//按奇偶顺序左右添加房间
		if(i%2!=0)
		{
			pcrchooseItem[i]->setPosition(ccp(88+225,-53+494-i/2*112));
			if(i<tempnum)
				myroom[i]=new room(88+225,
					-53+494-i/2*112,
					hsm.house[dir+i].HouseNo,
					hsm.house[dir+i].MapType*100+hsm.house[dir+i].MapNo,
					hsm.house[dir+i].HouseName,
					hsm.house[dir+i].MaxPlayer,
					hsm.house[dir+i].Player);
			else myroom[i]=new room(88+225,-53+494-i/2*112,-1,0,"empty",0,0);
			this->addChild(myroom[i]);
		}
		else
		{
			pcrchooseItem[i]->setPosition(ccp(88+29,-53+494-i/2*112));
			if(i<tempnum)
				myroom[i]=new room(88+29,
					-53+494-i/2*112,
					hsm.house[dir+i].HouseNo,
					hsm.house[dir+i].MapType*100+hsm.house[dir+i].MapNo,
					hsm.house[dir+i].HouseName,
					hsm.house[dir+i].MaxPlayer,
					hsm.house[dir+i].Player);
			else myroom[i]=new room(88+29,-53+494-i/2*112,-1,0,"empty",0,0);
			this->addChild(myroom[i]);
		}
		//将按钮作为菜单添加到LAYER中
		pcrchooseMenu[i] = CCMenu::create(pcrchooseItem[i], NULL);
		(pcrchooseMenu[i])->setPosition(Point::ZERO);
		this->addChild(pcrchooseMenu[i]);
	}
}
//显示翻页按钮
void cr::showpage()
{
	//创建左翻页按钮图片
	CCMenuItemImage *pleftpageimg = CCMenuItemImage::create(
		"image\\button\\cr_leftpage.png","image\\button\\cr_leftpage_selected.png","image\\button\\cr_leftpage_disabled.png",this,menu_selector(cr::leftpageclick));
	//设置左翻页按钮位置
	pleftpageimg->setPosition(ccp(348,30));
	//添加菜单至界面中
	CCMenu* pleftpagemenu = CCMenu::create(pleftpageimg, NULL);
	pleftpagemenu->setPosition(Point::ZERO);
    this->addChild(pleftpagemenu);

	//创建右翻页按钮图片
	CCMenuItemImage *prightpageimg = CCMenuItemImage::create(
		"image\\button\\cr_rightpage.png","image\\button\\cr_rightpage_selected.png","image\\button\\cr_rightpage_disabled.png",this,menu_selector(cr::rightpageclick));
	//设置右翻页按钮位置
	prightpageimg->setPosition(ccp(383,30));
	//添加菜单至界面中
	CCMenu* prightpagemenu = CCMenu::create(prightpageimg, NULL);
	prightpagemenu->setPosition(Point::ZERO);
    this->addChild(prightpagemenu);

	if(page==0)
		pleftpageimg->setEnabled(false);
	if(roomnum-page*8<8)
		prightpageimg->setEnabled(false);
}
//显示上部横条
void cr::showad()
{
	CCSprite* pcrad = CCSprite::create("image\\form\\ad.png");
	//设定主界面显示位置并添加入layer中
    pcrad->setPosition(ccp(400,565));
	this->addChild(pcrad);

}
//显示右下方的4个按钮和退出按钮
void cr::showbutton5()
{
	//创建新手练习按钮
	CCMenuItemImage *pntItem = CCMenuItemImage::create(
		"image\\button\\cr_newgame.png","image\\button\\cr_newgame_selected.png",this,menu_selector(cr::newtestclick));
	//设置新手练习按钮位置
	pntItem->setPosition(ccp(531,33));
	//添加菜单至界面中
	CCMenu* pntMenu = CCMenu::create(pntItem, NULL);
	pntMenu->setPosition(Point::ZERO);
    this->addChild(pntMenu);
	//创建快速加入按钮
	CCMenuItemImage *pfjItem = CCMenuItemImage::create(
		"image\\button\\cr_fastjoin.png","image\\button\\cr_fastjoin_selected.png",this,menu_selector(cr::fastjoinclick));
	//设置快速加入按钮位置
	pfjItem->setPosition(ccp(586,33));
	//添加菜单至界面中
	CCMenu* pfjMenu = CCMenu::create(pfjItem, NULL);
	pfjMenu->setPosition(Point::ZERO);
    this->addChild(pfjMenu);

	//创建创建房间按钮
	CCMenuItemImage *pcrItem = CCMenuItemImage::create(
		"image\\button\\cr_createroom.png","image\\button\\cr_createroom_selected.png",this,menu_selector(cr::createroomclick));
	//设置创建房间按钮位置
	pcrItem->setPosition(ccp(641,33));
	//添加菜单至界面中
	CCMenu* pcrMenu = CCMenu::create(pcrItem, NULL);
	pcrMenu->setPosition(Point::ZERO);
    this->addChild(pcrMenu);

	//创建个人信息按钮
	CCMenuItemImage *puiItem = CCMenuItemImage::create(
		"image\\button\\cr_userinfo.png","image\\button\\cr_userinfo_selected.png",this,menu_selector(cr::userinfoclick));
	//设置个人信息按钮位置
	puiItem->setPosition(ccp(696,33));
	//添加菜单至界面中
	CCMenu* puiMenu = CCMenu::create(puiItem, NULL);
	puiMenu->setPosition(Point::ZERO);
    this->addChild(puiMenu);

	//创建退出按钮
	CCMenuItemImage *pexitItem = CCMenuItemImage::create(
		"image\\button\\ca_exit.png","image\\button\\ca_exit_selected.png",this,menu_selector(cr::menuCloseCallback));
	//设置退出按钮位置
	pexitItem->setPosition(ccp(761,33));
	//添加菜单至界面中
	CCMenu* pexitMenu = CCMenu::create(pexitItem, NULL);
	pexitMenu->setPosition(Point::ZERO);
    this->addChild(pexitMenu);

}
//点击“新手练习”按钮时触发
void cr::newtestclick(CCObject* pSender)
{
	//播放音效
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	//保存房间号
	int roomnum=0;
	//与服务器交互信息
	MOEClient myclient=MOEClient(hsw.server[area].port,hsw.server[area].IP);
	SessionMessage recmsg=recmsg1;
	myclient.Send(recmsg);
	CheckMessage chkmsg1;
	myclient.Recv(chkmsg1);
	if(chkmsg1.IsOk)
	{
		NumberSend num;
		num.num=1;
		myclient.Send(num);
		CheckMessage chkmsg2;
		myclient.Recv(chkmsg2);
		if(chkmsg2.IsOk)
		{
			myclient.Recv(num);
			roomnum=num.num;
			MOEClient myclient1=MOEClient(hsw.server[area].port,hsw.server[area].IP);
			SessionMessage recmsg2=recmsg1;
			myclient1.Send(recmsg2);
			CheckMessage chkmsg3;
			myclient1.Recv(chkmsg3);
			if(chkmsg3.IsOk)
			{
				NumberSend num1;
				num1.num=3;
				myclient1.Send(num1);
				CheckMessage chkmsg4;
				NumberSend num3;
				num3.num=roomnum;
				myclient1.Send(num3);
				myclient1.Recv(chkmsg4);
				if(chkmsg4.IsOk)
				{
					ServerMessage roomserver1;
					myclient1.Recv(roomserver1);//收到游戏服务器地址
					MOEClient roomclient1=MOEClient(roomserver1.port,roomserver1.IP);
					NumberSend num2;
					num2.num=0;
					SessionMessage recmsg3=recmsg1;
					roomclient1.Send(recmsg3);
					CheckMessage chkmsg5;
					roomclient1.Recv(chkmsg5);
					if(chkmsg5.IsOk){
						roomclient1.Send(num2);
						//获取房间信息
						oneHouseMessage ohm;
						roomclient1.Recv(ohm);
						this->removeAllChildrenWithCleanup(true);
						this->unschedule(schedule_selector(cr::update));
						NumberSend num99;
						num99.num=6;
						roomclient1.Send(num99);
						enterroom* myroom=new enterroom(true,ohm,roomserver1);
						MOEClient gameclient=MOEClient(roomserver1.port,roomserver1.IP);
						SessionMessage recmsg5=recmsg1;
						gameclient.Send(recmsg5);
						CheckMessage chkmsg6;
						gameclient.Recv(chkmsg6);
						if(chkmsg6.IsOk)
						{
							NumberSend num7;
							num7.num=1;
							CheckMessage chkmsg7;
							gameclient.Send(num7);
								NumberSend num8;
								num8.num=5;
								gameclient.Send(num8);
								gameclient.Recv(chkmsg7);
								int trytime=0;
								while(!chkmsg7.IsOk)
								{
									if(trytime==10){
										message* msg=new message("start game failed");
										break;
									}
									trytime++;
									Sleep(500);
									NumberSend num3;
									num3.num=5;
									CheckMessage chkmsgt;
									gameclient.Send(num3);
									gameclient.Recv(chkmsg1);
									chkmsg7.IsOk=chkmsgt.IsOk;
								}
								if(chkmsg7.IsOk)
								{
									ClientMapMessage cmm1;
									gameclient.Recv(cmm1);
									startgame* game=new startgame(roomserver1,cmm1,ohm);
									myroom->unschedule(schedule_selector(enterroom::update));
									this->addChild(game);
								}
								if(trytime==20){
									message* mymsg=new message("start game failed");
									this->addChild(mymsg);
								}
							}
					}
				}
				else
				{
					message* mymsg=new message("unknown error");
					this->addChild(mymsg);
				}
			}
			else
			{
				message* mymsg=new message("connect to server failed");
				this->addChild(mymsg);
			}
		}
		else 
		{
			message* mymsg=new message("create room failed");
			this->addChild(mymsg);
		}
	}
	else
	{
		message* mymsg=new message("connect to server failed");
		this->addChild(mymsg);
	}

}
//点击“快速加入”按钮时触发
void cr::fastjoinclick(CCObject* pSender)
{			
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	if(hsm.HouseNum==0){
		message* msg=new message("no room to join in"); this->addChild(msg); return;}
	srand(time(0));
	int i=(rand()%hsm.HouseNum)-page*8;
	int mychoose=hsm.house[i+page*8].HouseNo;
	MOEClient myclient=MOEClient(hsm.house[i+page*8].houseServer.port,hsm.house[i+page*8].houseServer.IP);
	SessionMessage recmsg=recmsg1;
	myclient.Send(recmsg);
	CheckMessage chkmsg;
	myclient.Recv(chkmsg);
	if(chkmsg.IsOk){
		NumberSend num; num.num=0;
		myclient.Send(num);
		oneHouseMessage ohm;
		myclient.Recv(ohm);
		enterroom* myroom=new enterroom(false,ohm,hsm.house[i+page*8].houseServer);
		this->removeAllChildrenWithCleanup(true);
		this->unschedule(schedule_selector(cr::update));
		this->addChild(myroom);
	}
	else
	{
		message* msg=new message("connect to server failed");
		this->addChild(msg);
	}
}
//点击“创建房间”按钮时触发
void cr::createroomclick(CCObject* pSender)
{
	//播放音效
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	//保存房间号
	int roomnum=0;
	//与服务器交互信息
	MOEClient myclient=MOEClient(hsw.server[area].port,hsw.server[area].IP);
	SessionMessage recmsg=recmsg1;
	myclient.Send(recmsg);
	CheckMessage chkmsg1;
	myclient.Recv(chkmsg1);
	if(chkmsg1.IsOk)
	{
		NumberSend num;
		num.num=1;
		myclient.Send(num);
		CheckMessage chkmsg2;
		myclient.Recv(chkmsg2);
		if(chkmsg2.IsOk)
		{
			myclient.Recv(num);
			roomnum=num.num;
			MOEClient myclient1=MOEClient(hsw.server[area].port,hsw.server[area].IP);
			SessionMessage recmsg2=recmsg1;
			myclient1.Send(recmsg2);
			CheckMessage chkmsg3;
			myclient1.Recv(chkmsg3);
			if(chkmsg3.IsOk)
			{
				NumberSend num1;
				num1.num=3;
				myclient1.Send(num1);
				CheckMessage chkmsg4;
				NumberSend num3;
				num3.num=roomnum;
				myclient1.Send(num3);
				myclient1.Recv(chkmsg4);
				if(chkmsg4.IsOk)
				{
					ServerMessage roomserver1;
					myclient1.Recv(roomserver1);//收到游戏服务器地址
					MOEClient roomclient1=MOEClient(roomserver1.port,roomserver1.IP);
					NumberSend num2;
					num2.num=0;
					SessionMessage recmsg3=recmsg1;
					roomclient1.Send(recmsg3);
					CheckMessage chkmsg5;
					roomclient1.Recv(chkmsg5);
					if(chkmsg5.IsOk){
						roomclient1.Send(num2);
						//获取房间信息
						oneHouseMessage ohm;
						roomclient1.Recv(ohm);
						this->removeAllChildrenWithCleanup(true);
						this->unschedule(schedule_selector(cr::update));
						NumberSend num99;
						num99.num=6;
						roomclient1.Send(num99);
						enterroom* myroom=new enterroom(true,ohm,roomserver1);
						this->addChild(myroom);
					}
				}
				else
				{
					message* mymsg=new message("unknown error");
					this->addChild(mymsg);
				}
			}
			else
			{
				message* mymsg=new message("connect to server failed");
				this->addChild(mymsg);
			}
		}
		else 
		{
			message* mymsg=new message("create room failed");
			this->addChild(mymsg);
		}
	}
	else
	{
		message* mymsg=new message("connect to server failed");
		this->addChild(mymsg);
	}
}
//点击“个人信息”按钮时触发
void cr::userinfoclick(CCObject* pSender)
{

}
//点击退出按钮时调用
void cr::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
    CCDirector::sharedDirector()->end();
}
//选择房间时调用
void cr::chooseroom(CCObject* pSender)
{
	if(turnonsound1==true)	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	for(int i=0;i<hsm.HouseNum-page*8;i++)
	{
		int x =(int)(((CCMenuItemImage *)pSender)->getPositionX());
		int y =(int)(((CCMenuItemImage *)pSender)->getPositionY());
		int x1=(int)(pcrchooseItem[i]->getPositionX());
		int y1=(int)(pcrchooseItem[i]->getPositionY());
		if(x1==x&&y1==y)//判断点中的LABEL
		{
			int mychoose=hsm.house[i+page*8].HouseNo;
			MOEClient myclient=MOEClient(hsm.house[i+page*8].houseServer.port,hsm.house[i+page*8].houseServer.IP);
			SessionMessage recmsg=recmsg1;
			myclient.Send(recmsg);
			CheckMessage chkmsg;
			myclient.Recv(chkmsg);
			if(chkmsg.IsOk){
				NumberSend num; num.num=0;
				myclient.Send(num);
				oneHouseMessage ohm;
				myclient.Recv(ohm);
				enterroom* myroom=new enterroom(false,ohm,hsm.house[i+page*8].houseServer);
				this->removeAllChildrenWithCleanup(true);
				this->unschedule(schedule_selector(cr::update));
				this->addChild(myroom);
			}
			else
			{
				message* msg=new message("connect to server failed");
				this->addChild(msg);
			}
		}
	}

}
//每帧时调用
void cr::update(float delta)
{
	time1++;
	//每3秒刷新房间列表
	if(time1==100)
	{
		MOEClient myclient=MOEClient(hsw.server[area].port,hsw.server[area].IP);
		time1=0;
		SessionMessage recmsg=recmsg1;
		myclient.Send(recmsg);
		CheckMessage chkmsg1;
		myclient.Recv(chkmsg1);
		if(chkmsg1.IsOk)
		{
			NumberSend num;
			num.num=0;
			myclient.Send(num);
			HouseSimpleMessage newhsm;
			myclient.Recv(newhsm);
			hsm=newhsm;
			for(int i=0;i<8;i++)
				this->removeChild(myroom[i],true);
			this->addroom();
		}
		else
		{
			message* mymsg=new message("connect to server failed");
			this->addChild(mymsg);
		}
	}
}
room::room(){}
room::room(int inX,int inY,int inroomID,int inroomclass,char inroomname[],int inmaxusernum,int innowusernum)
{
	X=inX;Y=inY;roomID=inroomID;roomclass=inroomclass;roomname=string(inroomname);maxusernum=inmaxusernum;nowusernum=innowusernum;
	showroom();
}
//显示房间信息
void room::showroom()
{
	if(roomID==-1){
		CCSprite* proomMain = CCSprite::create("image\\form\\room_empty.png");
		//设定主界面显示位置并添加入layer中
		proomMain->setPosition(ccp(X,Y));
		this->addChild(proomMain);
		return;
	}
	CCSprite* proomMain = CCSprite::create("image\\form\\room.png");
	//设定主界面显示位置并添加入layer中
    proomMain->setPosition(ccp(X,Y));
	this->addChild(proomMain);

	//设置房间编号LABEL大小
	CCSize roomIDsize=CCSize(40,18);
	//初始化房间编号LABEL
	CCLabelTTF* proomID = CCLabelTTF::create(inttostr(roomID).c_str(), "tahoma", 18, roomIDsize, TextHAlignment::LEFT);
	//设置房间编号LABEL位置并添入
	proomID->setPosition(ccp(X-88+25+10,Y+53-5-8));
	this->addChild(proomID);
	
	//设置房间名称LABEL大小
	CCSize roomnamesize=CCSize(40,15);
	//初始化房间名称LABEL
	CCLabelTTF* proomname = CCLabelTTF::create(roomname.c_str(), "arial", 14, roomnamesize, TextHAlignment::LEFT);
	//设置房间名称LABEL位置并添入
	proomname->setPosition(ccp(X-88+63+20,Y+53-15-7));
	this->addChild(proomname);
	//初始化房间类别LABEL
	CCLabelTTF* proomclassname = CCLabelTTF::create(roomname.c_str(), "arial", 14, roomnamesize, TextHAlignment::LEFT);
	//设置房间类别LABEL位置并添入
	proomclassname->setPosition(ccp(X-88+63+20,Y+53-40-7));
	this->addChild(proomclassname);
	//设置当前玩家数LABEL大小
	CCSize usernumsize=CCSize(20,25);
	//初始化房间编号LABEL
	CCLabelTTF* pnowusernum = CCLabelTTF::create(inttostr(nowusernum).c_str(), "tahoma", 25, usernumsize, TextHAlignment::LEFT);
	//设置当前玩家数LABEL位置并添入
	pnowusernum->setPosition(ccp(X-88+60+10,Y+53-70-7));
	this->addChild(pnowusernum);
	CCLabelTTF* ptemp = CCLabelTTF::create("/", "tahoma", 25, usernumsize, TextHAlignment::LEFT);
	ptemp->setPosition(ccp(X-88+72+10,Y+53-70-7));
	this->addChild(ptemp);
	//初始化最大玩家数LABEL
	CCLabelTTF* pmaxusernum = CCLabelTTF::create(inttostr(maxusernum).c_str(), "tahoma", 25, usernumsize, TextHAlignment::LEFT);
	//设置房间编号LABEL位置并添入
	pmaxusernum->setPosition(ccp(X-88+80+10,Y+53-70-7));
	this->addChild(pmaxusernum);
	//加载房间类别图片
	CCSprite* proomclassimg = CCSprite::create("image\\roomclass\\001.png");
	//设置图片显示位置
	proomclassimg->setPosition( ccp(X-88+5+25,Y+53-40-25) );
	this->addChild(proomclassimg);

}