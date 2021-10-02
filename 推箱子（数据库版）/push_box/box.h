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

//���x�����Ƅӵķ���
#define KEY_UP    'w'
#define KEY_DOWN  's'
#define KEY_LEFT  'a'
#define KEY_RIGHT 'd'
#define QUIET	  'q'

#define isValid(pos)  pos.x>=0 && pos.x<MAP_LINE && pos.y>=0 && pos.y <MAP_COLUMN

//�˵�λ��
struct _POS {
	int x;
	int y;
};

//ö�e����
enum PROP {
	WALL,
	FLOOER,
	BOX_DEC,
	MAN,
	BOX,
	HIT,
	ALL
};

//ö�e����
enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct _useInfo{
	int id;			//�û�id
	string name;	//�û���
	string pwd;		//����
	int levelID;	//�ؿ�id
}useInfo;

typedef struct _levelInfo {
	int id;			 //�ؿ�id
	string name;	 //�ؿ�����
	int map_row;	 //��ͼ����
	int map_column;  //��ͼ����
	string map_data; //��ͼ����
	int next_level;	 //��һ��id
}levelInfo;