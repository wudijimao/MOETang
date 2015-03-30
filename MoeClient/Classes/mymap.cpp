#include "mymap.h"
using namespace cocos2d;
mymap::mymap(int mapt,int imap[15][15])
{
	maptype=mapt;
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
			thismap[i][j]=imap[i][j];
	showmap();
}
void mymap::showmap()
{
	CCSprite* pmapMain = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\main.png").c_str());
	pmapMain->setPosition(ccp(300,262));
	this->addChild(pmapMain);
	CCSprite* pSprite;
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++){
			int ch=thismap[i][j];
			int x=40*i+20; int y=525-35*j+17.5-35;
			switch (ch){
			case 1:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\tree.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 500:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\bomb.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 501:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\firemid.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 502:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\firelr.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 503:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\fireleft.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 504:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\fireright.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 505:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\firetb.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 506:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\firetop.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 507:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\firebuttom.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 2:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\redblock.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 3:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\orangeblock.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 4:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\water.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 5:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\colorstone.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			case 6:
				pSprite = CCSprite::create(("image\\map\\" + inttostr(maptype) + "\\graystone.png").c_str());
				pSprite->setPosition( ccp(x,y) );
				this->addChild(pSprite);
				break;
			default:break;
			}

		}

}