#include "Server.h"
using namespace std;


 //ը��ʱ���������жϱ�ը·���ϵ����������Ӧ�Ĵ�����������ֹ����ɱ��������,xΪ����x���꣬yΪ����y���꣬lengthΪһ��������������ȣ�����ը���ȣ�
void GameServer::BoomScan(int x, int y)
{
	int aX=x;
	int aY=y;
	int limit;
	bool out;

	ground->GroundFloor[x][y].set(groundType::boomCross);
	//��������-------------------------------------------------------------
	limit = 1;
	out = false;
	while(limit+x<=15&&limit<=ground->GroundFloor[x][y].BLength&&out!=true)//��������
	{
		switch(ground->GroundFloor[x+limit][y].blowType)
		{
		case 0://�յػ����е���
			ground->GroundFloor[x+limit][y].set(groundType::boomLeftRight);
			break;
		case 1://��ը�����ϰ�
			ground->GroundFloor[x+limit][y].set(groundType::ground);//������
			ground->GroundFloor[x+limit-1][y].set(groundType::boomRight);
			out=true;//��ը���˽�ֹ
			break;
		case 2://����ը�����ϰ�
			out=true;//��ը���˽�ֹ
			ground->GroundFloor[x+limit-1][y].set(groundType::boomRight);
			break;
		case 3://��
			ground->GroundFloor[x+limit][y].set(groundType::ground);//������
			BoomScan(x+limit,y);

		}
		++limit;
	}
	//��������-------------------------------------------------------------
	limit = 1;
	out = false;
	while(x-limit>=0&&limit<=ground->GroundFloor[x][y].BLength&&out!=true)//��������
	{
		switch(ground->GroundFloor[x-limit][y].blowType)
		{
		case 1://��ը�����ϰ�
			ground->GroundFloor[x-limit][y].set(groundType::ground);;//������
			ground->GroundFloor[x-limit+1][y].set(groundType::boomLeft);
			out=true;//��ը���˽�ֹ
			break;
		case 2://����ը�����ϰ�
			out=true;//��ը���˽�ֹ
			ground->GroundFloor[x-limit+1][y].set(groundType::boomLeft);
			break;
		case 3://��
			ground->GroundFloor[x-limit][y].set(groundType::ground);;//������
			BoomScan(x-limit,y);
			break;
		case 0://�յػ����е���
			ground->GroundFloor[x-limit][y].set(groundType::boomLeftRight);
			break;
		}
		++limit;
	}
	//��������-------------------------------------------------------------
	limit = 1;
	out = false;
	while(y-limit>=0&&limit<=ground->GroundFloor[x][y].BLength&&out!=true)
	{
		switch(ground->GroundFloor[x][y-limit].blowType)
		{
		case 1://��ը�����ϰ�
			ground->GroundFloor[x][y-limit].set(groundType::ground);;//������
			ground->GroundFloor[x][y-limit+1].set(groundType::boomTop);
			out=true;//��ը���˽�ֹ
			break;
		case 2://����ը�����ϰ�
			out=true;//��ը���˽�ֹ
			ground->GroundFloor[x][y-limit+1].set(groundType::boomTop);
			break;
		case 3://��
			ground->GroundFloor[x][y-limit].set(groundType::ground);//������
			BoomScan(x,y-limit);
			break;
		case 0://�յػ����е���
			ground->GroundFloor[x][y-limit].set(groundType::boomTopBottom);
			break;
		}
		++limit;
	}
	//��������-------------------------------------------------------------
	limit = 1;
	out = false;
	while(limit+y<=15&&limit<=ground->GroundFloor[x][y].BLength&&out!=true)//��������
	{
		switch(ground->GroundFloor[x][y+limit].blowType)
		{
		case 1://��ը�����ϰ�
			ground->GroundFloor[x][y+limit].set(groundType::ground);;//������
			ground->GroundFloor[x][y+limit-1].set(groundType::boomBottom);
			out=true;//��ը���˽�ֹ
			break;
		case 2://����ը�����ϰ�
			out=true;//��ը���˽�ֹ
			ground->GroundFloor[x][y+limit-1].set(groundType::boomBottom);
			break;
		case 3://��
			ground->GroundFloor[x][y+limit].set(groundType::ground);;//������
			BoomScan(x,y+limit);
			break;
		case 0://�յػ����е���
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
		if(player[i].isDeath==true)//������Ѿ�����
		{
			if(player[i].RespwanTime==0)//�������ʱ�䵽0
			{
				player[i].isDeath=false;//������
				Respawn(i);
				//�ڴ����������������
			}
			else//����ʱ��û��0
			{
				player[i].RespwanTime--;//����ʣ��ʱ���1
			}
		}
		else//����δ����
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
		player[i] = myPlayer(inplayer[i]);//????���������
	}
}

//�Ƿ�����Ҫը
void GameServer::GroundScan(void)
{
	boom=false;//�Ƿ�����ը=û��
	int i,j;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
		{
			if(ground->GroundFloor[i][j].blowType==3)
			{
				if(ground->GroundFloor[i][j].LTime==0)//�����ըʣ��ʱ��Ϊ0
				{
					BoomScan(i, j);//ը
					boom=true;//����ը��
				}
				else//����
				{
					ground->GroundFloor[i][j].LTime--;//��ըʣ��ʱ���1
				}
			}
			if (ground->GroundFloor[i][j].blowType==4)
			{
				if(ground->GroundFloor[i][j].LTime==0)//�����ըʣ��ʱ��Ϊ0
				{
					ground->GroundFloor[i][j].set(groundType::ground);
				}
				else//����
				{
					ground->GroundFloor[i][j].LTime--;//��ըʣ��ʱ���1
				}
			}
		}

}


void GameServer::Respawn(int pNum)
{
	int i=pNum;
	if(player->DeathScore==0)
	{
		player[pNum].isDeath=false;//����״̬Ϊ ���
		player[pNum].posX=ground->rPoint[i].x;//���õ�ǰ����λ��X����
		player[pNum].posY=ground->rPoint[i].y;//���õ�ǰ����λ��Y����
		ground->GroundFloor[player[pNum].getXinGround()][player[pNum].getYinGround()].type=i+1;//���õ�ǰ���������Ӧλ��Ϊ������
	}
	else
	{
		srand((unsigned)time(0));
		i=rand()%8;//���1-8λ�ø���
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

//����ȫ����Ƿ��а��¿ո�� ����
void GameServer::plantbombScan(void)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if (!player[i].isDeath)
		{
			if(ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type==0&&player[i].isSpaceDown==1&&player[i].BombPlanted<player[i].BombMaxNow)//����ؿգ������ﰴ���˿ո�,������������δ�ﵽ����
			{
				player[i].BombPlanted++;//������������+1
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].type=player[i].BombType;//���ݣ�����Ϊ���ﵱǰ�����
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].BLength=player[i].BombLength;//�ݳ��ȸ�ֵ
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].LTime=5*30;//ʱ�丳ֵ5��*30֡
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].blowType=3;//������ʽ=��
				ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable=1;//ͨ����ʽ=����ͨ��
			}
		}
	}
}



 //�ж���������ƶ������
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
			//�������Ϊ��
			if(player[i].DirectionKey==RIGHT){
				limit=1;
				while(limit<=player[i].MoveSpeed&&player[i].posX<72)//��������
				{
					if (GameServer::ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable == 1 && player[i].getXinGround(2) == player[i].getXinGround())
					{
						player[i].posX++;
					}
					else
					{			
						switch(GameServer::ground->GroundFloor[player[i].getXinGround(2)][player[i].getYinGround()].walkable)
						{
						case 0://�ɴ���
							player[i].posX++;
							break;
						case 1://���ɴ���
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
			//�������Ϊ��
			if(player[i].DirectionKey==LEFT){
				limit=1;
				while(limit<=player[i].MoveSpeed&&player[i].posX>2)//��������
				{
					if (GameServer::ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable == 1 && player[i].getXinGround(-2) == player[i].getXinGround())
					{
						player[i].posX--;
					}
					else
					{				
					switch(ground->GroundFloor[player[i].getXinGround(-2)][player[i].getYinGround()].walkable)
					{
					case 0://�ɴ���
						player[i].posX--;
						break;
					case 1://���ɴ���
						break;
					case 2:
						player[i].changeDeath(true);
						break;
					}
					}
					limit++;
				}
			}
			//�������Ϊ��
			if(player[i].DirectionKey==DOWN){
				limit=1;
				while(limit<=player[i].MoveSpeed&&player[i].posY<72)//��������
				{
					if (GameServer::ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable == 1 && player[i].getYinGround() == player[i].getYinGround(2))
					{
						player[i].posY++;
					}
					else
					{
						switch(ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround(2)].walkable)
						{
						case 0://�ɴ���
							player[i].posY++;
							break;
						case 1://���ɴ���
							break;
						case 2:
							player[i].changeDeath(true);
							break;
						}
					}
					
					limit++;
				}
			}
			//�������Ϊ��
			if(player[i].DirectionKey==UP){
				limit=1;
				while(limit<=player[i].MoveSpeed&&player[i].posY>2)//��������
				{
					if (GameServer::ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround()].walkable == 1 && player[i].getYinGround() == player[i].getYinGround(-2))
					{
						player[i].posY--;
					}
					else
					{
						switch(ground->GroundFloor[player[i].getXinGround()][player[i].getYinGround(-2)].walkable)
						{
						case 0://�ɴ���
							player[i].posY--;
							break;
						case 1://���ɴ���
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

//----------------------����˷���ͻ���-----------
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