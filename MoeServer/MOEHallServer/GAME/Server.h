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
	// 炸泡时的搜索，判断爆炸路径上的情况并做相应的处理（消除，截止，击杀，穿过）
	void BoomScan(int x, int y);
	//搜索是否有泡要炸
	void GroundScan(void);
	//判断死亡或复活（包含首次进入游戏的复活）
	void JudgeDeath(void);
	//复活函数
	void Respawn(int pNum);
	//判断所有玩家是否吃道具
	void itemScan(void);
	//判断所有玩家是否埋泡
	void plantbombScan(void);
	// 判断所有玩家移动的情况
	void moveScan(void);
	int GameTime;
public:
	GameServer()
	:isGameStart(false)
	,GameTime(400*30)
	{}
	myPlayer player[8];
	int playerNum;//有多少玩家
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
		ground = new Ground(Mes.MapNo);//设置地图
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

