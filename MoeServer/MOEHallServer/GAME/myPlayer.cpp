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

// 返回外形ID
int myPlayer::getSkinID(void)
{
	return SkinID;
}


// 返回移动速度
int myPlayer::getMoveSpeed(void)
{
	return MoveSpeed;
}


// 返回泡炸长度
int myPlayer::getBombLength(void)
{
	return BombLength;
}


// 返回人物在地面数组中的X位置
int myPlayer::getXinGround(void)
{
	int pos;
	pos=posX/5;
	return pos;
}
// 返回人物在地面数组中的X位置
int myPlayer::getXinGround(int l)
{
	int pos;
	pos=(posX +l)/5;
	return pos;
}


// 返回人物在地面数组中的Y位置
int myPlayer::getYinGround(void)
{
	int pos;
	pos=posY/5;
	return pos;
}
// 返回人物在地面数组中的Y位置
int myPlayer::getYinGround(int l)
{
	int pos;
	pos=(posY+l)/5;
	return pos;
}


// 更换皮肤
void myPlayer::changeSkin(int SID)
{
	SkinID=SID;
}


// 改变移动速度
void myPlayer::changeMoveSpeed(int MS)
{
	MoveSpeed=MS;
}


// 改变泡炸的长度
void myPlayer::changeBombLength(int BL)
{
	BombLength=BL;
}


// 改变人物的死亡/生存状态。TRUE=变为死亡，FALSE=变为活着。
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


// 记录玩家是否激活 TRUE激活，FALSE未激活
bool myPlayer::isInGame(void)
{
	if(SkinID==-1)
	{
		return false;
	}
	return true;
}




