#include "mapread.h"
#include <fstream>
#include<iostream>
using namespace std;
void mapread::read(int s){
	string filename="map"+".txt";
	fstream f;
	char ch[240];
	f.open(filename);
	if(f){
		f.read((char*)ch,sizeof(ch));
		for(int i=0;i<15;i++)
		for(int j=0;j<15;j++){
		map[i][j]=(int)(ch[i*16+j]-48);
		}
	}
	f.close();

}
