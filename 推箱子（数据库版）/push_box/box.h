#pragma once
#include <string>

using namespace std;

#define IMG_SIZE    61
#define BG_WIDTH    800
#define BG_HEIGTH   640
#define WIDTH_MOVE  34
#define HEIGTH_MOVE 45
#define MAP_LINE    50
#define MAP_COLUMN  50
#define VICTORY_WIDTH  607
#define VICTORY_HEIGTH 318
#define DEFEAT_WIDTH 556
#define DEFEAT_HEIGTH 313

//定義人物移動的方向
#define KEY_UP    'w'
#define KEY_DOWN  's'
#define KEY_LEFT  'a'
#define KEY_RIGHT 'd'
#define QUIET	  'q'

#define isValid(pos)  pos.x>=0 && pos.x<MAP_LINE && pos.y>=0 && pos.y <MAP_COLUMN

//人的位置
struct _POS {
	int x;
	int y;
};

//枚舉道具
enum PROP {
	WALL,
	FLOOER,
	BOX_DEC,
	MAN,
	BOX,
	HIT,
	ALL
};

//枚舉方向
enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct _useInfo{
	int id;			//用户id
	string name;	//用户名
	string pwd;		//密码
	int levelID;	//关卡id
}useInfo;

typedef struct _levelInfo {
	int id;			 //关卡id
	string name;	 //关卡名字
	int map_row;	 //地图行数
	int map_column;  //地图列数
	string map_data; //地图数据
	int next_level;	 //下一关id
}levelInfo;