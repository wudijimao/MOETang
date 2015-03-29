#ifndef MAP_READ_H
#define MAP_READ_H
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "Global variables.h"

class mapread
{
public:
	int map[15][15];
	void read(int);

};
#endif