
#define  BLOCK_COUNT 5	//���x���K�N�
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

//���巽��ķ���
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

int score = 0; //�֔�
int level = 0; //�ȼ�
int NextIndex = -1; //��һ���������
int BlockIndex = -1;	//��ǰ���������
int speed = 500;	//���巽����ٶ�

//���巽�����ɫ
int blockColor[BLOCK_COUNT] = {BLUE,CYAN,YELLOW,MAGENTA,BROWN};
int markColor[FACE_HEIGHT][FACE_WIDTH];	//������Ϸ���棬�̻��ķ�����ɫ
int face[FACE_HEIGHT][FACE_WIDTH];
//��ʼ�����K
int block[BLOCK_COUNT*4][BLOCK_HEIGHT][BLOCK_WIDTH] = {
	//I �ͷ��K
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

	 //L ��
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
	
	  //�� ��
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

	//T ��
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

	 //Z ��
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