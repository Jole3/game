#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include "Tetris.h"

void clearBlock(int  x,int y){
	setcolor(BLACK);
	setfont(23,0,"����");

	for(int i=0; i<BLOCK_HEIGHT; i++){
		for(int j=0; j<BLOCK_WIDTH; j++){
			outtextxy(x+j*UNIT_SIZE,y+i*UNIT_SIZE,"��");
		}
	}
}

//���ָ��λ�ã�ָ������ķ���
void clearBlock(int x,int y, block_dir dir){
	int id = BlockIndex*4 + dir;
	y += START_Y;
	setcolor(BLACK);
	setfont(23,0,"����");

	for(int i=0; i<BLOCK_HEIGHT; i++){
		for(int j=0; j<BLOCK_WIDTH; j++){
			if(block[id][i][j] == 1){
				outtextxy(x+j*UNIT_SIZE,y+i*UNIT_SIZE,"��");
			}
		}
	}
}

void drawBlock(int  x,int y){
	setcolor(blockColor[NextIndex]);
	setfont(23,0,"����");

	for(int i=0; i<BLOCK_HEIGHT; i++){
		for(int j=0; j<BLOCK_WIDTH; j++){
			if(block[4*NextIndex][i][j] == 1){
				outtextxy(x+j*UNIT_SIZE,y+i*UNIT_SIZE,"��");
			}
		}
	}
}

void drawBlock(int x,int y,int index,block_dir dir){
	setcolor(blockColor[index]);
	setfont(23,0,"����");
	int id = index * 4 + dir;

	for(int i=0; i<BLOCK_HEIGHT; i++){
		for(int j=0; j<BLOCK_WIDTH; j++){
			if(block[id][i][j] == 1){
				outtextxy(x+j*UNIT_SIZE,y+i*UNIT_SIZE,"��");
			}
		}
	}
}

//��һ�����K
void nextBlock(void){
	int x = 391;
	int y = 71;
	clearBlock(x,y);

	srand(time(NULL));
	NextIndex = rand() % BLOCK_COUNT;

	drawBlock(x,y);
}

//�gӭ����
void welcome(){
	initgraph(550,660);

	//�@ȡ��ǰ����
	HWND win = GetHWnd();
	SetWindowText(win,_T("����˹����"));

	setcolor(WHITE);
	setfont(40,0,_T("΢���ź�"));
	outtextxy(205,200,_T("����˹����"));

	setfont(22,0,_T("����"));
	outtextxy(175,300,_T("��̴Ӷ���˹���鿪ʼ��"));

	Sleep(2000);
}

//��ʼ���[�����
void initGame(){
	char str[16];
	cleardevice();	//�����Ļ
	setcolor(WHITE);

	rectangle(27,27,336,635);
	rectangle(29,29,334,633);
	rectangle(370,50,515,195);

	setfont(24,0,_T("����"));
	outtextxy(405,215,_T("��һ��"));

	setcolor(RED);
	outtextxy(405,280,_T("����"));
	sprintf(str,"%d",score);	//������׃���D�Q���ַ���
	outtextxy(415,310,str);

	outtextxy(405,375,_T("�ȼ�"));
	sprintf(str,"%d",level);
	outtextxy(425,405,str);

	setcolor(LIGHTBLUE);
	outtextxy(390,475,_T("����˵����"));
	outtextxy(390,500,_T("������ת"));
	outtextxy(390,525,_T("��������"));
	outtextxy(390,550,_T("��������"));
	outtextxy(390,575,_T("��������"));
	outtextxy(390,600,_T("�ո���ͣ"));
}

//�жϷ����Ƿ����ƶ�
bool moveAble(int x0, int y0, move_dir moveDir, block_dir blockDir){
	bool re = true;
	int id = BlockIndex*4 + blockDir;
	//���巽������Ͻ�����Ϸ�����Ӧ���к���
	int x = (y0 - minY)/UNIT_SIZE;
	int y = (x0 - minX)/UNIT_SIZE;

	if(moveDir == MOVE_DOWN){
		for(int i=0; i<BLOCK_HEIGHT; i++){
			for(int j=0; j<BLOCK_WIDTH; j++){
				if(block[id][i][j] == 1 &&
					(x+i+1 >= 30 || face[x+i+1][y+j] == 1)){
					re = false;
				}
			}
		}
	}else if(moveDir == MOVE_LEFT){
		for(int i=0; i<BLOCK_HEIGHT; i++){
			for(int j=0; j<BLOCK_WIDTH; j++){
				if(block[id][i][j] == 1 &&
					(y+j == 0 || face[x+i][y+j-1] == 1)){
					re = false;
				}
			}
		}
	}else if(moveDir == MOVE_RIGHT){
		for(int i=0; i<BLOCK_HEIGHT; i++){
			for(int j=0; j<BLOCK_WIDTH; j++){
				if(block[id][i][j] == 1 &&
					(y+j+1 >= 15 || face[x+i][y+j+1] == 1)){
					re = false;
				}
			}
		}
	}

	return re;
}

//�ж���Ϸ�Ƿ����
void faileGame(){
	if(!moveAble(START_X,START_Y,MOVE_DOWN,BLOCK_UP)){
		setcolor(WHITE);
		setfont(45,0,"����");
		outtextxy(75,300,"Game Over!");
		Sleep(1000);
		system("pause");
		closegraph();

		exit(0);
	}
}

void wait(int speed){
	int count = speed/10;
	for(int i=0; i<count; i++){
		Sleep(10);
		if(kbhit()){
			return;
		}
	}
}

//�жϷ����Ƿ������ת��ָ����dir����
int rotatable(int x,int y,block_dir dir){
	int id = BlockIndex * 4 + dir;
	int x0 = (y-minY)/20;
	int y0 = (x-minX)/20;
	if(!moveAble(x,y,MOVE_DOWN,dir)){
		return 0;
	}

	for(int i=0; i<BLOCK_HEIGHT; i++){
		for(int j=0; j<BLOCK_WIDTH; j++){
			if(block[id][i][j] == 1 &&
				y0+j<0 || y0+j >=15 || face[x0+i][y0+j] == 1){
				return 0;
			}
		}
	}
	return 1;
}

//�̻�����
void mark(int x,int y,int blockIndex, block_dir dir){
	int id = blockIndex * 4 + dir;
	int y2 = (x - minX)/UNIT_SIZE;
	int x2 = (y - minY)/UNIT_SIZE;

	for(int i=0; i<BLOCK_HEIGHT; i++){
		for(int j=0; j<BLOCK_WIDTH; j++){
			if(block[id][i][j] == 1){
				face[x2+i][y2+j] = 1;
				markColor[x2+i][y2+j] = blockColor[blockIndex];
			}
		}
	}
}

//���齵��
void move(){
	int x = START_X;
	int y = START_Y;
	int initSpeed = speed;
	int k = 0;	//���巽�������Ϸ����߿�ľ���
	block_dir dir = BLOCK_UP;
	faileGame();

	while(1){
		if(kbhit()){
			int key = getch();
			if(key == KEY_SPACE){
				getch();
			}
		}
		clearBlock(x,k,dir);

		if(kbhit()){
			int key = getch();
			if(key == KEY_UP){	//��ת����
				block_dir nextDir = (block_dir)((dir+1) % 4);	//������ת�����һ��λ��
				if(rotatable(x,y+k,nextDir)){
					dir = nextDir;
				}
			}else if(key == KEY_DOWN){
				initSpeed = 50;
			}else if(key == KEY_LEFT){
				if(moveAble(x,y+k+20,MOVE_LEFT,dir)){
					x -= UNIT_SIZE;
				}
			}else if(key == KEY_RIGHT){
				if(moveAble(x,y+k+20,MOVE_RIGHT,dir)){
					x += UNIT_SIZE;
				}
			}
		}

		k += 20;
		drawBlock(x,y+k,BlockIndex,dir);

		wait(initSpeed);
		

		//�̻�
		if(!moveAble(x,y+k,MOVE_DOWN,dir)){
			mark(x,y+k,BlockIndex,dir);
			break;
		}
	}
	
}

//��Ϸ��������·���
void newBlock(){
	BlockIndex = NextIndex;
	drawBlock(START_X,START_Y);
	Sleep(100);
	nextBlock();
	move();
}

//�����У��������ƶ�
void down(int line){
	for(int i=line; i>0; i--){
		for(int j=0; j<FACE_WIDTH;j++){
			if(face[i-1][j]){
				face[i][j] = 1;
				markColor[i][j] = markColor[i-1][j];
				setcolor(markColor[i][j]);
				outtextxy(j*UNIT_SIZE+minY,i*UNIT_SIZE+minX,"��");
			}else{
				face[i][j] = 0;
				setcolor(BLACK);
				outtextxy(j*UNIT_SIZE+minY,i*UNIT_SIZE+minX,"��");
			}
		}
	}

	setcolor(BLACK);
	//������ϵķ���
	for(int j=0; j<FACE_WIDTH; j++){
		face[0][j] = 0;
		outtextxy(j*UNIT_SIZE+minY,minX,"��");
	}
}

//�ӷ�
void addScore(int lines){
	char str[32] = {0};
	score += 10*lines;
	sprintf(str,"%d",score);
	setcolor(RED);
	outtextxy(415,310,str);
}

//���µȼ�
void updateLevel(){
	char str[32] = {0};
	level = score /50;
	sprintf(str,"%d",level);
	setcolor(RED);
	outtextxy(425,405,str);

	speed = 500 - level*100;
	if(speed <= 100){
		speed = 100;
	}
}

//�ж��Ƿ������������
void check(){
	int i,j;
	int clearLine = 0;	//��������������
	for(i=FACE_HEIGHT-1; i>=0; i--){
		for(j=0; j<FACE_WIDTH && face[i][j]; j++);

		if(j>=15){
			down(i);
			i++;
			clearLine++;
		}
	}
	addScore(clearLine);
	updateLevel();
}

int main(){
	welcome();
	initGame();
	nextBlock();

	Sleep(500);
	memset(face,0,sizeof(face));

	while(1){
		newBlock();
		check();
	}

	system("pause");
	return 0;
}