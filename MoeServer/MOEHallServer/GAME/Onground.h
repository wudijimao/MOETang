#pragma once
enum groundType
{
	ground = 0,
	tree=1,
	redBlock,
	orangeBlock,
	water,
	colorfulBucket,
	grayBucket,
	//各种炮爆炸效果
	boomCross = 501,
	boomLeftRight,
	boomLeft,
	boomRight,
	boomTopBottom,
	boomTop,
	boomBottom
};

struct Onground
{
	int type;
	int blowType;//0穿过,1炸坏终止，2终止,3泡,4泡的动画效果
	int walkable;//0可穿过，1不可穿过 ,2 穿过即死
	int BLength;
	int LTime;
	//int BelongTo;
	void set(int Type)
	{
		type = Type;
		switch(Type)
		{
			//普通草地
		case groundType::ground:
			blowType = 0;
			walkable = 0;
			break;
			//砖块，不可炸碎
		case groundType::tree:
		case groundType::water:
			blowType = 2;
			walkable = 1;
			break;
			//砖块可炸碎
		case groundType::colorfulBucket:
		case  groundType::grayBucket:
		case  groundType::orangeBlock:
		case groundType::redBlock:
			blowType = 1;
			walkable = 1;
			break;
		case groundType::boomBottom:
		case groundType::boomCross:
		case groundType::boomLeft:
		case groundType::boomLeftRight:
		case groundType::boomRight:
		case groundType::boomTop:
		case groundType::boomTopBottom:
			blowType = 4;
			walkable = 2;
			LTime = 10;
			break;
		}
	}
	//void setBoom(int length)
	//{
	//	type = 3;
	//}
};
struct PlayerType
{
	int SkinID;
	int MoveSpeed;
    int BombLength;
	bool isDeath;
	int RespwanTime;
	int posX;
	int posY;
	int DeathScore;
	int BombMaxNow;
	int DirectionKey;
	int isSpaceDown;
	int BombType;
};

struct ResPoint
{
	int x;
	int y;
};