#pragma once
//上下左右
# define LEFT 0x4b
# define RIGHT 0x4d
# define DOWN 0x50
# define UP 0x48
//地图元素
//--可击碎，砖块类，不可穿过
# define TREE 101			//树
# define REDBRICK 102		//红砖块
# define GREEDBRICK 103		//绿砖块
//--不可击碎，石头类，不可穿过
# define WATER 201			//水
# define WHITESTONE 202		//白石头
# define GRAYSTONE 203		//灰石头
//--不可击碎，泡，不可穿过
# define REDBOMB 301		//红泡
# define BLUEBOMB 302		//蓝泡
# define BLACKBOMB 303		//黑泡
//--不可击碎，道具，可穿过
# define SPEED 401			//行走速度增加道具
# define LENGTH 402			//泡炸长度增加道具
# define BOMBNUM 403		//埋泡数量增加道具
//--不可击碎，爆炸效果，可穿过
# define BOOMEFFECTLR 501		//爆炸视觉效果--左右路径
# define BOOMEFFECTLEND 502		//爆炸视觉效果--左收尾
# define BOOMEFFECTREND 503		//爆炸视觉效果--右收尾
# define BOOMEFFECTUD 504		//爆炸视觉效果--上下路径
# define BOOMEFFECTUEND 505		//爆炸视觉效果--上收尾
# define BOOMEFFECTDEND 506		//爆炸视觉效果--下收尾


//--不可击碎，复活点，不可穿过


#define Frame 30