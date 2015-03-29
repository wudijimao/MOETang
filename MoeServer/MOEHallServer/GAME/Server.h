#pragma once
#include <Windows.h>
#include "Ground.h"
#include "defines.h"
#include "myPlayer.h"
#include <iostream>
#include <time.h>
#include "../../MOEStruct/MessageStruct.h"
#include <time.h>
class GameServer
{

private:
	bool isGameStart;
	// ը��ʱ���������жϱ�ը·���ϵ����������Ӧ�Ĵ�����������ֹ����ɱ��������
	void BoomScan(int x, int y);
	//�����Ƿ�����Ҫը
	void GroundScan(void);
	//�ж������򸴻�����״ν�����Ϸ�ĸ��
	void JudgeDeath(void);
	//�����
	void Respawn(int pNum);
	//�ж���������Ƿ�Ե���
	void itemScan(void);
	//�ж���������Ƿ�����
	void plantbombScan(void);
	// �ж���������ƶ������
	void moveScan(void);
	int GameTime;
public:
	GameServer()
	:isGameStart(false)
	,GameTime(400*30)
	{}
	myPlayer player[8];
	int playerNum;//�ж������
	bool boom;
	Ground *ground;
	void setPlayer(PlayerType player[]);
	void Exit(string ID)
	{
		bool isExit = false;
		--playerNum;
		for (int i=0;i<playerNum;++i)
		{
			if (ID == player[i].playerID)
			{
				isExit = true;
			}
			if (isExit)
			{
				player[i] = player[i+1];
			}
		}
	}
	bool isStarted()
	{
		return isGameStart;
	}
public:
	int MaxBombLength;
	int MaxBomb;
	int MaxMoveSpeed;
	void StartGame(oneHouseMessage &Mes)
	{
		if (Mes.MapNo==-1)
		{
			srand(time(0));
			Mes.MapNo = rand()%2+1;
		}
		ground = new Ground(Mes.MapNo);//���õ�ͼ
		playerNum = Mes.PlayerNum;
		for (int i=0,j=0;i<Mes.PlayerNum;++j)
		{
			if (Mes.position[j]==1)
			{
				player[i] = myPlayer();
				player[i].playerID = Mes.playerMessage[j].ID;
				++i;
			}
		}
		isGameStart = true;
	}
	void EndGame()
	{
		isGameStart = false;
		delete ground;
	}
	bool pass();
	void Ssend(void);
	void uploadKeys(string ID,int Dir,int Space)
	{
		for (int i=0;i<playerNum;++i)
		{
			if (ID == player[i].playerID)
			{
				player[i].SetPlayerKeys(Dir,Space);
				return;
			}
		}
	}
};

