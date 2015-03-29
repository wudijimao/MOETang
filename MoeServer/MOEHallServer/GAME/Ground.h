#pragma once
#include "Onground.h"
#include <fstream>
#include <sstream>
using namespace std;
class Ground
{
public:
	// 地面数组
	Onground GroundFloor[15][15];
	//复活点
	ResPoint rPoint[8];
public:
	Ground(void);
	Ground(int MapNum)
	{
		loadMap(MapNum);
		for(int i=0;i<8;i++)
		{
			rPoint[i].x = 2;
			rPoint[i].y = 2;
		}
	}
private:
	void loadMap(int mapNo)
	{
		stringstream filename;
		filename <<"map"<< mapNo <<".txt";
		fstream f;
		char ch[240];
		f.open(filename.str());
		if(f){
			f.read((char*)ch,sizeof(ch));
			for(int i=0;i<15;i++)
				for(int j=0;j<15;j++){
					GroundFloor[i][j].set((int)(ch[i*16+j]-48));
				}
		}
		f.close();
	}
};

