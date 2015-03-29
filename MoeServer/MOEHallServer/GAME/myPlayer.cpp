#include "myPlayer.h"
#include "Server.h"
#include "defines.h"


myPlayer::myPlayer(PlayerType &inplayer)
{
	changeSkin(inplayer.SkinID);
	changeBombLength(inplayer.BombLength);
	changeMoveSpeed(inplayer.MoveSpeed);
	isDeath=inplayer.isDeath;
	RespwanTime=inplayer.RespwanTime;
	posX=inplayer.posX;
	posY=inplayer.posY;
	DeathScore=inplayer.DeathScore;
	BombMaxNow=inplayer.BombMaxNow;
	DirectionKey=inplayer.DirectionKey;
	isSpaceDown=inplayer.isSpaceDown;
	BombType=inplayer.BombType;
}

myPlayer::myPlayer(void)
	: SkinID(0)
	, MoveSpeed(1)
	, BombLength(5)
	, isDeath(true)
	, RespwanTime(0)
	, posX(0)
	, posY(0)
	, DeathScore(0)
	, BombMaxNow(3)
	, DirectionKey(0)
	, isSpaceDown(0)
	, BombType(500)
{
}

// ��������ID
int myPlayer::getSkinID(void)
{
	return SkinID;
}


// �����ƶ��ٶ�
int myPlayer::getMoveSpeed(void)
{
	return MoveSpeed;
}


// ������ը����
int myPlayer::getBombLength(void)
{
	return BombLength;
}


// ���������ڵ��������е�Xλ��
int myPlayer::getXinGround(void)
{
	int pos;
	pos=posX/5;
	return pos;
}
// ���������ڵ��������е�Xλ��
int myPlayer::getXinGround(int l)
{
	int pos;
	pos=(posX +l)/5;
	return pos;
}


// ���������ڵ��������е�Yλ��
int myPlayer::getYinGround(void)
{
	int pos;
	pos=posY/5;
	return pos;
}
// ���������ڵ��������е�Yλ��
int myPlayer::getYinGround(int l)
{
	int pos;
	pos=(posY+l)/5;
	return pos;
}


// ����Ƥ��
void myPlayer::changeSkin(int SID)
{
	SkinID=SID;
}


// �ı��ƶ��ٶ�
void myPlayer::changeMoveSpeed(int MS)
{
	MoveSpeed=MS;
}


// �ı���ը�ĳ���
void myPlayer::changeBombLength(int BL)
{
	BombLength=BL;
}


// �ı����������/����״̬��TRUE=��Ϊ������FALSE=��Ϊ���š�
void myPlayer::changeDeath(bool DOA)
{
	if(DOA==true)
	{
		isDeath=true;
		RespwanTime=5*30;
		DeathScore++;
		posX = -2000000;
	}
	else{
		isDeath=false;
	}
}


// ��¼����Ƿ񼤻� TRUE���FALSEδ����
bool myPlayer::isInGame(void)
{
	if(SkinID==-1)
	{
		return false;
	}
	return true;
}




