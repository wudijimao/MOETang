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

	bool isDeath;	// ��ǰ�����Ƿ����� TRUE=����FLASE=δ��

	int RespwanTime;	// ���������󸴻��ʣ��ʱ��

	int DeathScore;	// ������

	int posX;	// ���ﵱǰ���� X����

	int posY;	// ���ﵱǰ���� Y����

	int SkinID;	// ���������ID

	int MoveSpeed;	// ����������ٶ� ��ÿ�ΰ��·������x��y����Ĵ�С

	int BombLength;	// ��ǰ������ݵı�ը����

	int BombPlanted;	// ��ǰ�����Ѿ����˵�����

	int BombMaxNow;	// ���ﵱǰʱ�̿��������������ʣ������=������-�Ѿ���������
public:

	int getXinGround(void);	// ���������ڵ��������е�Xλ��
	// ���������ڵ��������е�Xλ��
	int myPlayer::getXinGround(int l);

	// ���������ڵ��������е�Yλ��
	int myPlayer::getYinGround(void);
	// ���������ڵ��������е�Yλ��
	int myPlayer::getYinGround(int l);

	void changeSkin(int SID);	// ����Ƥ��

	void changeMoveSpeed(int MS);	// �ı��ƶ��ٶ�

	void changeBombLength(int BL);	// �ı���ը�ĳ���

	void changeDeath(bool DOA);	// �ı����������/����״̬��TRUE=��Ϊ������FALSE=��Ϊ���š�

	bool isInGame(void);	// �ж�����Ƿ񼤻� SkinID=-1δ�������=����

	int getSkinID(void);	//������������ID

	int getMoveSpeed(void);	// �����ƶ��ٶ�

	int getBombLength(void);	// ������ը����


	void SetPlayerKeys(int Direction,int Space)//// ��ʾ��ǰ���ﰴ�������������ĸ�������0=δ����1=�����£�2=�����£�3=�����£�4=�����¡� // ��ʾ�����Ƿ����˿ո��,0=δ��,1=����
	{
		DirectionKey = Direction;
		isSpaceDown = Space;
	}
	int DirectionKey;	// ��ʾ��ǰ���ﰴ�������������ĸ�������0=δ����1=�����£�2=�����£�3=�����£�4=�����¡�

	int isSpaceDown;	// ��ʾ�����Ƿ����˿ո��,0=δ��,1=����

	int BombType;	//�����ݵ�����

};

