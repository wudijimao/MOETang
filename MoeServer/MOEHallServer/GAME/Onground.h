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
	//�����ڱ�ըЧ��
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
	int blowType;//0����,1ը����ֹ��2��ֹ,3��,4�ݵĶ���Ч��
	int walkable;//0�ɴ�����1���ɴ��� ,2 ��������
	int BLength;
	int LTime;
	//int BelongTo;
	void set(int Type)
	{
		type = Type;
		switch(Type)
		{
			//��ͨ�ݵ�
		case groundType::ground:
			blowType = 0;
			walkable = 0;
			break;
			//ש�飬����ը��
		case groundType::tree:
		case groundType::water:
			blowType = 2;
			walkable = 1;
			break;
			//ש���ը��
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