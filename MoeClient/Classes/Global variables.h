#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include "MessageStruct.h"
#include "MOEClient.h"
extern SessionMessage recmsg1;
extern bool turnonmusic1;
extern bool turnonsound1;
extern bool isnoservertest;
extern string userID;
extern MOEClient roomclient;
extern HouseSimpleMessage mychoosehsm;
extern HallServerWorkload mychoosehsw;
extern int mychoosearea;
static string inttostr(int input)
{
	int change=input;
	char out[256];
	int dir=0;
	out[0]='\0';
	while(change>=10)
	{
		int c=change-change/10*10;
		out[dir]=c+48;
		dir++;
		change=change/10;
	}
	out[dir]=change+48;
	out[dir+1]='\0';
	char out2[256];
	for(int i=0;i<=dir;i++)
	{
		out2[i]=out[dir-i];
	}
	out2[dir+1]='\0';
	string output=string(out2);
	return output;
}
#endif