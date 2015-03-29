#include "enterroom.h"
using namespace cocos2d;
enterroom::enterroom()
{
	numplayer=1;
	roomname="test";
	roomnum=123;
	roomid=-1;
	roomtype=1;
	maxplayer=8;
	numplayer=8;
	playernamestr[0]="aaaaa";playernamestr[1]="bbbbb";playernamestr[2]="ccccc";playernamestr[3]="dddddgg";
	playernamestr[4]="eeeee";playernamestr[5]="fffff";playernamestr[6]="ggggg";playernamestr[7]="hhhhh";
	playerbody[0]=1;playerbody[1]=1;playerbody[2]=1;playerbody[3]=1;playerbody[4]=1;playerbody[5]=1;playerbody[6]=1;playerbody[7]=1;
	ishost=true;
	showroom();
}
enterroom::enterroom(bool host,oneHouseMessage inohm,ServerMessage insm)
{
	time=0;
	roomserver=insm;
	ishost=host;
	ohm=inohm;
	roomname=ohm.HouseName;
	roomnum=ohm.HouseNo;
	roomid=ohm.MapNo;
	roomtype=ohm.MapType;
	maxplayer=ohm.MaxPlayer;
	numplayer=ohm.PlayerNum;
	for(int i=0;i<8;i++)
	{
		if(ohm.position[i]==1){
			playernamestr[i]=ohm.playerMessage[i].ID;
			playerbody[i]=ohm.playerMessage[i].userBody;
			playerhead[i]=ohm.playerMessage[i].userHead;
			playerbomb[i]=ohm.playerMessage[i].userBomb;
		}
	}
	showroom();
	this->schedule(schedule_selector(cr::update) );
}
//��ʾ��������
void enterroom::showroom()
{
	//����������
	CCSprite* proomMain=CCSprite::spriteWithFile("image\\form\\enterroom_main.png");
	//�趨��������ʾλ�ò������layer��
    proomMain->setPosition(ccp(400,300));
	this->addChild(proomMain);
	if(turnonmusic1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music\\M10.mp3", true);
	showplayername();
	showbutton();
	showplayers();
}
//��ʾ�������
void enterroom::showplayername()
{
	//����������ִ�С
	CCSize mysize=CCSize(104,17);
	for(int i=0;i<8;i++)
	{
		if(isnoservertest==false)
			if(ohm.position[i]==0)
				continue;
		if(i<4)
		{
			playername[i] = CCLabelTTF::labelWithString(playernamestr[i].c_str(),mysize,CCTextAlignmentLeft,"arial",14);
			playername[i]->setPosition(ccp(125*i+75,600-90));
			this->addChild(playername[i]);
		}
		else
		{
			playername[i] = CCLabelTTF::labelWithString(playernamestr[i].c_str(),mysize,CCTextAlignmentLeft,"arial",14);
			playername[i]->setPosition(ccp(125*(i-4)+75,600-460));
			this->addChild(playername[i]);
		}
	}
}
//��ʾ���
void enterroom::showplayers()
{
	for(int i=0;i<8;i++)
	{
		if(isnoservertest==false)
			if(ohm.position[i]==0)
				continue;
		player[i]=CCSprite::spriteWithFile(("image\\player\\"+inttostr(playerbody[i])+"\\down1.png").c_str());
		if(i<4)
			player[i]->setPosition(ccp(125*i+75,600-90-50));
		else
			player[i]->setPosition(ccp(125*(i-4)+75,600-460+70));
		this->addChild(player[i]);
	}
}
//��ʾ���ְ�ť
void enterroom::showbutton()
{
	//������ʼ��ťͼƬ
	CCMenuItemImage *pstartItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\enterroom_start.png","image\\button\\enterroom_start_selected.png","image\\button\\enterroom_start_disable.png",this,menu_selector(enterroom::start));
	//���ÿ�ʼ��ťλ��
	if(ishost==false)
		pstartItem->setIsEnabled(false);
	pstartItem->setPosition(ccp(600,45));
	//��Ӳ˵���������
	CCMenu* pstartMenu = CCMenu::menuWithItems(pstartItem, NULL);
    pstartMenu->setPosition(CCPointZero);
    this->addChild(pstartMenu);
	//�����˳���ťͼƬ
	CCMenuItemImage *pexitItem=CCMenuItemImage::itemFromNormalImage(
		"image\\button\\ca_exit.png","image\\button\\ca_exit_selected.png",this,menu_selector(enterroom::exitgame));
	//�����˳���ťλ��
	pexitItem->setPosition(ccp(740,45));
	//��Ӳ˵���������
	CCMenu* pexitMenu = CCMenu::menuWithItems(pexitItem, NULL);
    pexitMenu->setPosition(CCPointZero);
    this->addChild(pexitMenu);
	//�������Ƽ��������ʾ
	CCSize roomdirsize=CCSize(104,17);
	CCLabelTTF* roomdir=CCLabelTTF::labelWithString((inttostr(roomnum)+"    "+roomname).c_str(),roomdirsize,CCTextAlignmentLeft,"arial",15);
	roomdir->setPosition(ccp(100,600-52));
	this->addChild(roomdir);
	//����������ʾ
	CCSize roomnamesize=CCSize(160,23);
	CCLabelTTF* roomnamestr=CCLabelTTF::labelWithString("room name:",roomnamesize,CCTextAlignmentLeft,"arial",20);
	roomnamestr->setPosition(ccp(610,600-295));
	this->addChild(roomnamestr);
	//�趨������С
	CCSize Inputsize=CCSize(115,25);
	//�趨�����������ɫ
	ccColor3B mycolor=ccc3(0,0,0);
	//�趨�������������
	char font_family[]="Thonburi";
	//�趨��������ִ�С
	float font_size=25;
	//��ʼ���������������
	if(ishost==false){
		CCLabelTTF* roomnameshow=CCLabelTTF::labelWithString(roomname.c_str(),Inputsize,CCTextAlignmentLeft,"arial",font_size);
		roomnameshow->setPosition(ccp(640,600-325));
		this->addChild(roomnameshow);
	}
	else{
		roomnameinput=CCTextFieldTTF::textFieldWithPlaceHolder(roomname.c_str(),Inputsize,CCTextAlignmentLeft,font_family,font_size);
		roomnameinput->setColor(mycolor);
		roomnameinput->setPosition(ccp(640,600-325));
		roomnameinput->attachWithIME();
		this->addChild(roomnameinput);
		//�趨ȷ����ťλ��
		CCMenuItemImage *penterItem=CCMenuItemImage::itemFromNormalImage(
			"image\\button\\determine.png","image\\button\\determine_selected.png",this,menu_selector(enterroom::changeroomname));
		//����ȷ����ťλ��
		penterItem->setPosition(ccp(720,600-325));
		//��Ӳ˵���������
		CCMenu* penterMenu = CCMenu::menuWithItems(penterItem, NULL);
		penterMenu->setPosition(CCPointZero);
		this->addChild(penterMenu);
	}
}
//�����ʼ��ťʱ����
void enterroom::start(CCObject* pSender)
{
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	MOEClient gameclient=MOEClient(roomserver.port,roomserver.IP);
	SessionMessage recmsg=recmsg1;
	gameclient.Send(recmsg);
	CheckMessage chkmsg2;
	gameclient.Recv(chkmsg2);
	if(chkmsg2.IsOk)
	{
		NumberSend num1;
		num1.num=1;
		CheckMessage chkmsg1;
		gameclient.Send(num1);
			NumberSend num2;
			num2.num=5;
			gameclient.Send(num2);
			gameclient.Recv(chkmsg1);
			int trytime=0;
			while(!chkmsg1.IsOk)
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
				chkmsg1.IsOk=chkmsgt.IsOk;
			}
			if(chkmsg1.IsOk)
			{
				ClientMapMessage cmm1;
				gameclient.Recv(cmm1);
				startgame* game=new startgame(roomserver,cmm1,ohm);
				this->removeAllChildrenWithCleanup(true);
				this->unschedule(schedule_selector(enterroom::update));
				this->addChild(game);
			}
			if(trytime==20){
				message* mymsg=new message("start game failed");
				this->addChild(mymsg);
			}
		}
	}
//�ı䷿������ʱ����
void enterroom::changeroomname(CCObject* pSender)
{
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	message* mymsg=new message("change roomname");
	this->addChild(mymsg);
}
//����˳���ťʱ����
void enterroom::exitgame(CCObject* pSender)
{
    // "close" menu item clicked
	if(turnonsound1==true)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound\\uiLeave.wav");
	MOEClient myclient=MOEClient(roomserver.port,roomserver.IP);
	SessionMessage recmsg=recmsg1;
	myclient.Send(recmsg);
	CheckMessage chkmsg;
	myclient.Recv(chkmsg);
	if(chkmsg.IsOk){
		NumberSend num2; num2.num=2;
		myclient.Send(num2);
		this->unschedule(schedule_selector(enterroom::update));
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
//ÿ֡ʱ����
void enterroom::update(ccTime dt)
{
	if(time!=10){time++;return;}
	time=0;
	MOEClient gameclient=MOEClient(roomserver.port,roomserver.IP);
	SessionMessage recmsg=recmsg1;
	gameclient.Send(recmsg);
	CheckMessage chkmsg;
	gameclient.Recv(chkmsg);
	if(chkmsg.IsOk)
	{
		NumberSend num3;
		num3.num=3;
		bool issendsuccess=gameclient.Send(num3);
		oneHouseMessage newohm;
		gameclient.Recv(newohm);
		ohm=newohm;
		roomname=ohm.HouseName;
		roomnum=ohm.HouseNo;
		roomid=ohm.MapNo;
		roomtype=ohm.MapType;
		maxplayer=ohm.MaxPlayer;
		numplayer=ohm.PlayerNum;
		for(int i=0;i<8;i++)
		{
			if(ohm.position[i]==1){
				playernamestr[i]=ohm.playerMessage[i].ID;
				playerbody[i]=ohm.playerMessage[i].userBody;
				playerhead[i]=ohm.playerMessage[i].userHead;
				playerbomb[i]=ohm.playerMessage[i].userBomb;
			}
		}
		if(ishost){
			showplayers();showplayername();}
		if(!ishost)
		{
			CheckMessage chkmsg1;
			NumberSend num2;
			num2.num=5;
			gameclient.Send(num2);
			gameclient.Recv(chkmsg1);
			if(chkmsg1.IsOk)
			{
					ClientMapMessage cmm1;
					gameclient.Recv(cmm1);
					startgame* game=new startgame(roomserver,cmm1,ohm);
					this->removeAllChildrenWithCleanup(true);
					this->unschedule(schedule_selector(enterroom::update));
					this->addChild(game);
			}
		}
	}
}