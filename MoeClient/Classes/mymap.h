#ifndef MYMAP_H
#define MYMAP_H
#include "cocos2d.h"
#include "mapread.h"
class mymap:public cocos2d::CCLayer
{
public:
	mymap(int mapt,int imap[15][15]);
	void showmap();
	void selectmap(int);
private:
	int thismap[15][15];
	cocos2d::CCSprite* truemap[15][15];
	int maptype;
};

#endif