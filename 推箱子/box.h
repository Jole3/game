#define IMG_SIZE    61
#define BG_WIDTH    800
#define BG_HEIGTH   640
#define WIDTH_MOVE  34
#define HEIGTH_MOVE 45
#define MAP_LINE    9
#define MAP_COLUMN  12
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
struct _POS{
	int x;
	int y;
};

//ö�e����
enum PROP{
	WALL,
	FLOOER,
	BOX_DEC,
	MAN,
	BOX,
	HIT,
	ALL
};

//ö�e����
enum direction{
	UP,
	DOWN,
	LEFT,
	RIGHT
};