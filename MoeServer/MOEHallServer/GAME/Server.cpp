#include "Server.h"
using namespace std;


 //炸泡时的搜索，判断爆炸路径上的情况并做相应的处理（消除，截止，击杀，穿过）,x为数组x坐标，y为数组y坐标，length为一个方向的搜索长度（即泡炸长度）
void GameServer::BoomScan(int x, int y)
{
	int aX=x;
	int aY=y;
	int limit;
	bool out;

	ground->GroundFloor[x][y].set(groundType::boomCross);
	//向右搜索-------------------------------------------------------------
	limit = 1;
	out = false;
	while(limit+x<=15&&limit<=ground->GroundFloor[x][y].BLength&&out!=true)//向右搜索
	{
		switch(ground->GroundFloor[x+limit][y].blowType)
		{
		case 0://空地或者有道具
			ground->GroundFloor[x+limit][y].set(groundType::boomLeftRight);
			break;
		case 1://可炸坏的障碍
			ground->GroundFloor[x+limit][y].set(groundType::ground);//则消除
			ground->GroundFloor[x+limit-1][y].set(groundType::boomRight);
			out=true;//爆炸到此截止
			break;
		case 2://不可炸坏的障碍
			out=true;//爆炸到此截止
			ground->GroundFloor[x+limit-1][y].set(groundType::boomRight);
			break;
		case 3://泡
			ground->GroundFloor[x+limit][y].set(groundType::ground);//则引爆
			BoomScan(x+limit,y);

		}
		++limit;
	}
	//向左搜索-------------------------------------------------------------
	limit = 1;
	out = false;
	while(x-limit>=0&&limit<=ground->GroundFloor[x][y].BLength&&out!=true)//向左搜索
	{
		switch(ground->GroundFloor[x-limit][y].blowType)
		{
		case 1://可炸坏的障碍
			ground->GroundFloor[x-limit][y].set(groundType::ground);;//则消除
			ground->GroundFloor[x-limit+1][y].set(groundType::boomLeft);
			out=true;//爆炸到此截止
			break;
		case 2://不可炸坏的障碍
			out=true;//爆炸到此截止
			ground->GroundFloor[x-limit+1][y].set(groundType::boomLeft);
			break;
		case 3://泡
			ground->GroundFloor[x-limit][y].set(groundType::ground);;//则引爆
			BoomScan(x-limit,y);
			break;
		case 0://空地或者有道具
			ground->GroundFloor[x-limit][y].set(groundType::boomLeftRight);
			break;
		}
		++limit;
	}
	//向上搜索-------------------------------------------------------------
	limit = 1;
	out = false;
	while(y-limit>=0&&limit<=ground->GroundFloor[x][y].BLength&&out!=true)
	{
		switch(ground->GroundFloor[x][y-limit].blowType)
		{
		case 1://可炸坏的障碍
			ground->GroundFloor[x][y-limit].set(groundType::ground);;//则消除
			ground->GroundFloor[x][y-limit+1].set(groundType::boomTop);
			out=true;//爆炸到此截止
			break;
		case 2://不可炸坏的障碍
			out=true;//爆炸到此截止
			ground->GroundFloor[x][y-limit+1].set(groundType::boomTop);
			break;
		case 3://泡
			ground->GroundFloor[x][y-limit].set(groundType::ground);//则引爆
			BoomScan(x,y-limit);
			break;
		case 0://空地或者有道具
			ground->GroundFloor[x][y-limit].set(groundType::boomTopBottom);
			break;
		}
		++limit;
	}
	//向下搜索-------------------------------------------------------------
	limit = 1;
	out = false;
	while(limit+y<=15&&limit<=ground->GroundFloor[x][y].BLength&&out!=true)//向右搜索
	{
		switch(ground->GroundFloor[x][y+limit].blowType)
		{
		case 1://可炸坏的障碍
			ground->GroundFloor[x][y+limit].set(groundType::ground);;//则消除
			ground->GroundFloor[x][y+limit-1].set(groundType::boomBottom);
			out=true;//爆炸到此截止
			break;
		case 2://不可炸坏的障碍
			out=true;//爆炸到此截止
			ground->GroundFloor[x][y+limit-1].set(groundType::boomBottom);
			break;
		case 3://泡
			ground->GroundFloor[x][y+limit].set(groundType::ground);;//则引爆
			BoomScan(x,y+limit);
			break;
		case 0://空地或者有道具
			ground->GroundFloor[x][y+limit].set(groundType::boomTopBottom);
			break;
		}
		++limit;
	}
}


void GameServer::JudgeDeath(void)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if(player[i].isDeath==true)//如果人已经死亡
		{
			if(player[i].RespwanTime==0)//如果死亡时间到0
			{
				player[i].isDeath=false;//就重生
				Respawn(i);
				//在此添加人物重生函数
			}
			else//死亡时间没到0
			{
				player[i].RespwanTime--;//复活剩余时间减1
			}
		}
		else//人物未死亡
		{
			if(ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type==501||ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type==502||ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type==503||ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type==504||ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type==505||ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type==506)
			{
				player[i].changeDeath(true);
			}
		}
	}
}


void GameServer::setPlayer(PlayerType inplayer[])
{
	for(int i=0;i<8;i++)
	{
		player[i] = myPlayer(inplayer[i]);//????真的能用吗
	}
}

//是否有泡要炸
void GameServer::GroundScan(void)
{
	boom=false;//是否有泡炸=没有
	int i,j;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
		{
			if(ground->GroundFloor[i][j].blowType==3)
			{
				if(ground->GroundFloor[i][j].LTime==0)//如果爆炸剩余时间为0
				{
					BoomScan(i, j);//炸
					boom=true;//有泡炸了
				}
				else//否则
				{
					ground->GroundFloor[i][j].LTime--;//爆炸剩余时间减1
				}
			}
			if (ground->GroundFloor[i][j].blowType==4)
			{
				if(ground->GroundFloor[i][j].LTime==0)//如果爆炸剩余时间为0
				{
					ground->GroundFloor[i][j].set(groundType::ground);
				}
				else//否则
				{
					ground->GroundFloor[i][j].LTime--;//爆炸剩余时间减1
				}
			}
		}

}


void GameServer::Respawn(int pNum)
{
	int i=pNum;
	if(player->DeathScore==0)
	{
		player[pNum].isDeath=false;//设置状态为 存活
		player[pNum].posX=ground->rPoint[i].x;//设置当前人物位置X坐标
		player[pNum].posY=ground->rPoint[i].y;//设置当前人物位置Y坐标
		ground->GroundFloor[player[pNum].getXinGround()][player[pNum].getYinGround()].type=i+1;//设置当前地面数组对应位置为该人物
	}
	else
	{
		srand((unsigned)time(0));
		i=rand()%8;//随机1-8位置复活
		player[pNum].isDeath=false;
		player[pNum].posX=ground->rPoint[i].x;
		player[pNum].posY=ground->rPoint[i].y;
		//ground->GroundFloor[player[pNum].getXinGround()][player[pNum].getYinGround()].type=i+1;
	}
}

void GameServer::itemScan(void)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if (!player[i].isDeath)
		{
			switch(ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type)
			{
			case SPEED:
				if(player[i].MoveSpeed<MaxMoveSpeed)
					player[i].MoveSpeed++;
				else 
					player[i].MoveSpeed=MaxMoveSpeed;
			case LENGTH:
				if(player[i].BombLength<MaxBombLength)
					player[i].BombLength++;
				else
					player[i].BombLength=MaxBombLength;
			case BOMBNUM:
				if(player[i].BombMaxNow<MaxBomb)
					player[i].BombMaxNow++;
				else
					player[i].BombMaxNow=MaxBomb;
			}
		}
	}
}

//检索全玩家是否有按下空格键 埋泡
void GameServer::plantbombScan(void)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if (!player[i].isDeath)
		{
			if(ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type==0&&player[i].isSpaceDown==1&&player[i].BombPlanted<player[i].BombMaxNow)//如果地空，且人物按下了空格,且人物埋泡数未达到上限
			{
				player[i].BombPlanted++;//该人物埋泡数+1
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type=player[i].BombType;//埋泡，类型为人物当前泡外观
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].BLength=player[i].BombLength;//泡长度赋值
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].LTime=5*30;//时间赋值5秒*30帧
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].blowType=3;//引爆方式=泡
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable=1;//通过方式=不可通过
			}
		}
	}
}



 //判断所有玩家移动的情况
void GameServer::moveScan(void)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if (player[i].isDeath)
		{
			continue;
		}
		if(player[i].DirectionKey!=0)
		{
			int limit=1;
			//如果按键为→
			if(player[i].DirectionKey==RIGHT){
				limit=1;
				while(limit<=player[i].MoveSpeed&&player[i].posX<72)//向右搜索
				{
					if (GameServer::ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable == 1 && player[i].getXinGround(2) == player[i].getXinGround())
					{
						player[i].posX++;
					}
					else
					{			
						switch(GameServer::ground->GroundFloor[player[i].getXinGround(2)][player[i].getYinGround()].walkable)
						{
						case 0://可穿过
							player[i].posX++;
							break;
						case 1://不可穿过
							player[i].posX=player[i].posX;
							break;
						case 2:
							player[i].changeDeath(true);
							break;
						}
					}
					limit++;
				}
			}
			//如果按键为←
			if(player[i].DirectionKey==LEFT){
				limit=1;
				while(limit<=player[i].MoveSpeed&&player[i].posX>2)//向左搜索
				{
					if (GameServer::ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable == 1 && player[i].getXinGround(-2) == player[i].getXinGround())
					{
						player[i].posX--;
					}
					else
					{				
					switch(ground->GroundFloor[player[i].getXinGround(-2)][player[i].getYinGround()].walkable)
					{
					case 0://可穿过
						player[i].posX--;
						break;
					case 1://不可穿过
						break;
					case 2:
						player[i].changeDeath(true);
						break;
					}
					}
					limit++;
				}
			}
			//如果按键为↓
			if(player[i].DirectionKey==DOWN){
				limit=1;
				while(limit<=player[i].MoveSpeed&&player[i].posY<72)//向下搜索
				{
					if (GameServer::ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable == 1 && player[i].getYinGround() == player[i].getYinGround(2))
					{
						player[i].posY++;
					}
					else
					{
						switch(ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround(2)].walkable)
						{
						case 0://可穿过
							player[i].posY++;
							break;
						case 1://不可穿过
							break;
						case 2:
							player[i].changeDeath(true);
							break;
						}
					}
					
					limit++;
				}
			}
			//如果按键为↑
			if(player[i].DirectionKey==UP){
				limit=1;
				while(limit<=player[i].MoveSpeed&&player[i].posY>2)//向上搜索
				{
					if (GameServer::ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable == 1 && player[i].getYinGround() == player[i].getYinGround(-2))
					{
						player[i].posY--;
					}
					else
					{
						switch(ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround(-2)].walkable)
						{
						case 0://可穿过
							player[i].posY--;
							break;
						case 1://不可穿过
							player[i].posY=player[i].posY;
							break;
						case 2:
							player[i].changeDeath(true);
							break;
						}
					}
					
					limit++;
				}
			}
		}
	}

}

//----------------------服务端发向客户端-----------
void GameServer::Ssend(void)
{
	ground->GroundFloor;
	for(int i=0;i<8;i++)
	{
		player[i].DeathScore;
		player[i].isDeath;
		player[i].posX;
		player[i].posY;
		player[i].RespwanTime;
		player[i].SkinID;
	}
}

bool GameServer::pass()
{
	if (isGameStart&&GameTime>0)
	{
		GroundScan();
		moveScan();
		itemScan();
		plantbombScan();
		JudgeDeath();
		--GameTime;
	}
	else if (GameTime<=0)
	{
		return false;
	}
	else
	{
		Sleep(1000);
	}
	return true;
}