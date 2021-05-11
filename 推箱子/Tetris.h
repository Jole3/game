
#define  BLOCK_COUNT 5	//定義方塊種類
#define BLOCK_WIDTH  5
#define BLOCK_HEIGHT 5
#define UNIT_SIZE    20
#define FACE_WIDTH	 15
#define FACE_HEIGHT	 30
#define START_X		 130
#define START_Y		 30
#define KEY_UP		 72
#define KEY_LEFT	 75
#define KEY_DOWN	 80
#define KEY_RIGHT	 77
#define KEY_SPACE	 32
#define minX	30
#define minY	30

//定义方块的方向
typedef enum{
	BLOCK_UP,
	BLOCK_LEFT,
	BLOCK_DOWN,
	BLOCK_RIGHT
}block_dir;

typedef enum{
	MOVE_LEFT,
	MOVE_DOWN,
	MOVE_RIGHT
}move_dir;

int score = 0; //分數
int level = 0; //等級
int NextIndex = -1; //下一方块的种类
int BlockIndex = -1;	//当前方块的种类
int speed = 500;	//定义方块的速度

//定义方块的颜色
int blockColor[BLOCK_COUNT] = {BLUE,CYAN,YELLOW,MAGENTA,BROWN};
int markColor[FACE_HEIGHT][FACE_WIDTH];	//定义游戏界面，固化的方块颜色
int face[FACE_HEIGHT][FACE_WIDTH];
//初始化方塊
int block[BLOCK_COUNT*4][BLOCK_HEIGHT][BLOCK_WIDTH] = {
	//I 型方塊
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	 //L 型
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,1,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,1,0,0,0,
	 0,0,0,0,0},
	
	  //田 型
	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	//T 型
	{0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,0,0,0,
	 0,1,1,0,0,
	 0,1,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	 //Z 型
	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,1,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,1,0,0,0,
	 0,0,0,0,0},
};

void clearBlock(int  x,int y);
void clearBlock(int x,int y, block_dir dir);
void drawBlock(int  x,int y);
void drawBlock(int x,int y,int index,block_dir dir);
void nextBlock(void);
void welcome();
void initGame();
bool moveAble(int x0, int y0, move_dir moveDir, block_dir blockDir);
void faileGame();
void wait(int speed);
int rotatable(int x,int y,block_dir dir);
void mark(int x,int y,int blockIndex, block_dir dir);
void move();
void newBlock();
void down(int line);
void check();
void addScore(int lines);
void updateLevel();