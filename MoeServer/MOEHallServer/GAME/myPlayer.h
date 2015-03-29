#pragma once
#include "Ground.h"
#include <string>
using namespace std;

class myPlayer
{
public:      
	myPlayer(void);
	myPlayer(PlayerType &inplayer);
public:
	string playerID;

	bool isDeath;	// 当前人物是否死亡 TRUE=死，FLASE=未死

	int RespwanTime;	// 人物死亡后复活的剩余时间

	int DeathScore;	// 死亡数

	int posX;	// 人物当前所在 X坐标

	int posY;	// 人物当前所在 Y坐标

	int SkinID;	// 人物的外形ID

	int MoveSpeed;	// 人物的行走速度 即每次按下方向键后x或y变更的大小

	int BombLength;	// 当前人物的泡的爆炸长度

	int BombPlanted;	// 当前人物已经埋了的泡数

	int BombMaxNow;	// 人物当前时刻可以埋的总泡数（剩余泡数=总泡数-已经埋泡数）
public:

	int getXinGround(void);	// 返回人物在地面数组中的X位置
	// 返回人物在地面数组中的X位置
	int myPlayer::getXinGround(int l);

	// 返回人物在地面数组中的Y位置
	int myPlayer::getYinGround(void);
	// 返回人物在地面数组中的Y位置
	int myPlayer::getYinGround(int l);

	void changeSkin(int SID);	// 更换皮肤

	void changeMoveSpeed(int MS);	// 改变移动速度

	void changeBombLength(int BL);	// 改变泡炸的长度

	void changeDeath(bool DOA);	// 改变人物的死亡/生存状态。TRUE=变为死亡，FALSE=变为活着。

	bool isInGame(void);	// 判断玩家是否激活 SkinID=-1未激活，其他=激活

	int getSkinID(void);	//返回人物外形ID

	int getMoveSpeed(void);	// 返回移动速度

	int getBombLength(void);	// 返回泡炸长度


	void SetPlayerKeys(int Direction,int Space)//// 表示当前人物按下了上下左右哪个按键，0=未按，1=↑按下，2=↓按下，3=←按下，4=→按下。 // 表示人物是否按下了空格键,0=未按,1=按下
	{
		DirectionKey = Direction;
		isSpaceDown = Space;
	}
	int DirectionKey;	// 表示当前人物按下了上下左右哪个按键，0=未按，1=↑按下，2=↓按下，3=←按下，4=→按下。

	int isSpaceDown;	// 表示人物是否按下了空格键,0=未按,1=按下

	int BombType;	//人物泡的外形

};

