
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
	//����������
	CCSprite* pcrMain=CCSprite::spriteWithFile("image\\form\\cr_main.png");
	//�趨��������ʾλ�ò�������layer��
    pcrMain->setPosition(ccp(400,300));
	this->addChild(pcrMain);
	showpage();
	addroom();
	showad();
	showbutton5();
}
//����ҳ��ť���ʱ����
void cr::leftpageclick(CCObject* pSender)
{
	if(turnonsound1==true)	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	page--;
	this->removeAllChildrenWithCleanup(true);
	showcr();
}
//���ҷ�ҳ��ť���ʱ����
void cr::rightpageclick(CCObject* pSender)
{
	if(turnonsound1==true)	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	page++;
	this->removeAllChildrenWithCleanup(true);
	showcr();
}
//���Ӳ���ʾ����
void cr::addroom()
{
	int tempnum=roomnum-page*8;
	int dir=page*8;
	//ѭ��
	for(int i=0;i<8;i++)
	{
		//���Ӱ�ť�Խ��յ����Ϣ
		pcrchooseItem[i]=CCMenuItemImage::itemFromNormalImage(
		"image\\others\\chooseroom.png","image\\others\\chooseroom.png",this,menu_selector(cr::chooseroom));
		//����ż˳���������ӷ���
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
		//����ť��Ϊ�˵����ӵ�LAYER��
		pcrchooseMenu[i] = CCMenu::menuWithItems(pcrchooseItem[i], NULL);
		(pcrchooseMenu[i])->setPosition(CCPointZero);
		this->addChild(pcrchooseMenu[i]);
	}
}
//��ʾ��ҳ��ť
void cr::showpage()
{
	//������ҳ��ťͼƬ
	CCMenuItemImage *pleftpageimg=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\cr_leftpage.png","image\\button\\cr_leftpage_selected.png","image\\button\\cr_leftpage_disabled.png",this,menu_selector(cr::leftpageclick));
	//������ҳ��ťλ��
	pleftpageimg->setPosition(ccp(348,30));
	//���Ӳ˵���������
	CCMenu* pleftpagemenu = CCMenu::menuWithItems(pleftpageimg, NULL);
    pleftpagemenu->setPosition(CCPointZero);
    this->addChild(pleftpagemenu);

	//�����ҷ�ҳ��ťͼƬ
	CCMenuItemImage *prightpageimg=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\cr_rightpage.png","image\\button\\cr_rightpage_selected.png","image\\button\\cr_rightpage_disabled.png",this,menu_selector(cr::rightpageclick));
	//�����ҷ�ҳ��ťλ��
	prightpageimg->setPosition(ccp(383,30));
	//���Ӳ˵���������
	CCMenu* prightpagemenu = CCMenu::menuWithItems(prightpageimg, NULL);
    prightpagemenu->setPosition(CCPointZero);
    this->addChild(prightpagemenu);

	if(page==0)
		pleftpageimg->setIsEnabled(false);
	if(roomnum-page*8<8)
		prightpageimg->setIsEnabled(false);
}
//��ʾ�ϲ�����
void cr::showad()
{
	CCSprite* pcrad=CCSprite::spriteWithFile("image\\form\\ad.png");
	//�趨��������ʾλ�ò�������layer��
    pcrad->setPosition(ccp(400,565));
	this->addChild(pcrad);

}
//��ʾ���·���4����ť���˳���ť
void cr::showbutton5()
{
	//����������ϰ��ť
	CCMenuItemImage *pntItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\cr_newgame.png","image\\button\\cr_newgame_selected.png",this,menu_selector(cr::newtestclick));
	//����������ϰ��ťλ��
	pntItem->setPosition(ccp(531,33));
	//���Ӳ˵���������
	CCMenu* pntMenu = CCMenu::menuWithItems(pntItem, NULL);
    pntMenu->setPosition(CCPointZero);
    this->addChild(pntMenu);
	//�������ټ��밴ť
	CCMenuItemImage *pfjItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\cr_fastjoin.png","image\\button\\cr_fastjoin_selected.png",this,menu_selector(cr::fastjoinclick));
	//���ÿ��ټ��밴ťλ��
	pfjItem->setPosition(ccp(586,33));
	//���Ӳ˵���������
	CCMenu* pfjMenu = CCMenu::menuWithItems(pfjItem, NULL);
    pfjMenu->setPosition(CCPointZero);
    this->addChild(pfjMenu);

	//�����������䰴ť
	CCMenuItemImage *pcrItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\cr_createroom.png","image\\button\\cr_createroom_selected.png",this,menu_selector(cr::createroomclick));
	//���ô������䰴ťλ��
	pcrItem->setPosition(ccp(641,33));
	//���Ӳ˵���������
	CCMenu* pcrMenu = CCMenu::menuWithItems(pcrItem, NULL);
    pcrMenu->setPosition(CCPointZero);
    this->addChild(pcrMenu);

	//����������Ϣ��ť
	CCMenuItemImage *puiItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\cr_userinfo.png","image\\button\\cr_userinfo_selected.png",this,menu_selector(cr::userinfoclick));
	//���ø�����Ϣ��ťλ��
	puiItem->setPosition(ccp(696,33));
	//���Ӳ˵���������
	CCMenu* puiMenu = CCMenu::menuWithItems(puiItem, NULL);
    puiMenu->setPosition(CCPointZero);
    this->addChild(puiMenu);

	//�����˳���ť
	CCMenuItemImage *pexitItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\ca_exit.png","image\\button\\ca_exit_selected.png",this,menu_selector(cr::menuCloseCallback));
	//�����˳���ťλ��
	pexitItem->setPosition(ccp(761,33));
	//���Ӳ˵���������
	CCMenu* pexitMenu = CCMenu::menuWithItems(pexitItem, NULL);
    pexitMenu->setPosition(CCPointZero);
    this->addChild(pexitMenu);

}
//�����������ϰ����ťʱ����
void cr::newtestclick(CCObject* pSender)
{
	//������Ч
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	//���淿���
	int roomnum=0;
	//�������������Ϣ
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
					myclient1.Recv(roomserver1);//�յ���Ϸ��������ַ
					MOEClient roomclient1=MOEClient(roomserver1.port,roomserver1.IP);
					NumberSend num2;
					num2.num=0;
					SessionMessage recmsg3=recmsg1;
					roomclient1.Send(recmsg3);
					CheckMessage chkmsg5;
					roomclient1.Recv(chkmsg5);
					if(chkmsg5.IsOk){
						roomclient1.Send(num2);
						//��ȡ������Ϣ
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
//��������ټ��롱��ťʱ����
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
//������������䡱��ťʱ����
void cr::createroomclick(CCObject* pSender)
{
	//������Ч
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	//���淿���
	int roomnum=0;
	//�������������Ϣ
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
					myclient1.Recv(roomserver1);//�յ���Ϸ��������ַ
					MOEClient roomclient1=MOEClient(roomserver1.port,roomserver1.IP);
					NumberSend num2;
					num2.num=0;
					SessionMessage recmsg3=recmsg1;
					roomclient1.Send(recmsg3);
					CheckMessage chkmsg5;
					roomclient1.Recv(chkmsg5);
					if(chkmsg5.IsOk){
						roomclient1.Send(num2);
						//��ȡ������Ϣ
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
//�����������Ϣ����ťʱ����
void cr::userinfoclick(CCObject* pSender)
{

}
//����˳���ťʱ����
void cr::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
    CCDirector::sharedDirector()->end();
}
//ѡ�񷿼�ʱ����
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
		if(x1==x&&y1==y)//�жϵ��е�LABEL
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
//ÿ֡ʱ����
void cr::update(ccTime dt)
{
	time1++;
	//ÿ3��ˢ�·����б�
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
//��ʾ������Ϣ
void room::showroom()
{
	if(roomID==-1){
		CCSprite* proomMain=CCSprite::spriteWithFile("image\\form\\room_empty.png");
		//�趨��������ʾλ�ò�������layer��
		proomMain->setPosition(ccp(X,Y));
		this->addChild(proomMain);
		return;
	}
	CCSprite* proomMain=CCSprite::spriteWithFile("image\\form\\room.png");
	//�趨��������ʾλ�ò�������layer��
    proomMain->setPosition(ccp(X,Y));
	this->addChild(proomMain);

	//���÷�����LABEL��С
	CCSize roomIDsize=CCSize(40,18);
	//��ʼ��������LABEL
	CCLabelTTF* proomID = CCLabelTTF::labelWithString(inttostr(roomID).c_str(),roomIDsize,CCTextAlignmentLeft,"tahoma",18);
	//���÷�����LABELλ�ò�����
	proomID->setPosition(ccp(X-88+25+10,Y+53-5-8));
	this->addChild(proomID);
	
	//���÷�������LABEL��С
	CCSize roomnamesize=CCSize(40,15);
	//��ʼ����������LABEL
	CCLabelTTF* proomname = CCLabelTTF::labelWithString(roomname.c_str(),roomnamesize,CCTextAlignmentLeft,"arial",14);
	//���÷�������LABELλ�ò�����
	proomname->setPosition(ccp(X-88+63+20,Y+53-15-7));
	this->addChild(proomname);
	//��ʼ���������LABEL
	CCLabelTTF* proomclassname = CCLabelTTF::labelWithString(roomname.c_str(),roomnamesize,CCTextAlignmentLeft,"arial",14);
	//���÷������LABELλ�ò�����
	proomclassname->setPosition(ccp(X-88+63+20,Y+53-40-7));
	this->addChild(proomclassname);
	//���õ�ǰ�����LABEL��С
	CCSize usernumsize=CCSize(20,25);
	//��ʼ��������LABEL
	CCLabelTTF* pnowusernum = CCLabelTTF::labelWithString(inttostr(nowusernum).c_str(),usernumsize,CCTextAlignmentLeft,"tahoma",25);
	//���õ�ǰ�����LABELλ�ò�����
	pnowusernum->setPosition(ccp(X-88+60+10,Y+53-70-7));
	this->addChild(pnowusernum);
	CCLabelTTF* ptemp = CCLabelTTF::labelWithString("/",usernumsize,CCTextAlignmentLeft,"tahoma",25);
	ptemp->setPosition(ccp(X-88+72+10,Y+53-70-7));
	this->addChild(ptemp);
	//��ʼ����������LABEL
	CCLabelTTF* pmaxusernum = CCLabelTTF::labelWithString(inttostr(maxusernum).c_str(),usernumsize,CCTextAlignmentLeft,"tahoma",25);
	//���÷�����LABELλ�ò�����
	pmaxusernum->setPosition(ccp(X-88+80+10,Y+53-70-7));
	this->addChild(pmaxusernum);
	//���ط������ͼƬ
	CCSprite* proomclassimg = CCSprite::spriteWithFile("image\\roomclass\\001.png");
	//����ͼƬ��ʾλ��
	proomclassimg->setPosition( ccp(X-88+5+25,Y+53-40-25) );
	this->addChild(proomclassimg);

}