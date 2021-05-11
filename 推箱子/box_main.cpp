#include <iostream>
#include <string>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include "box.h"

//�������M���Ų�ͬ�NĈDƬ
IMAGE img[ALL];

struct _POS man;
struct _POS dec;
int steps = 0;

//�[��؈D��0-����1-�ذ壬2-����Ŀ�ĵأ�3-С�ˣ�4-���ӣ�5-����Ŀ�ĵ�
int map[][12] = {{0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,1,0,1,1,1,1,1,1,1,0,0},
				 {0,1,4,1,0,2,1,0,2,1,0,0},
				 {0,1,0,1,0,1,0,0,1,1,1,0},
				 {0,1,0,2,0,1,1,4,1,1,1,0},
				 {0,1,1,1,0,3,1,1,1,4,1,0},
				 {0,1,2,1,1,4,1,1,1,1,1,0},
				 {0,1,0,0,1,0,1,1,0,0,1,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0}};

//��׃����
void changeProp(int x,int y,enum PROP pro){
	map[x][y] = pro;
	putimage(WIDTH_MOVE+IMG_SIZE*y,HEIGTH_MOVE+IMG_SIZE*x,&img[map[x][y]]);
}

//�Д��[���Ƿ�Y��
bool gameOver(){
	for(int i=0; i<MAP_LINE; i++){
		for(int j=0; j<MAP_COLUMN; j++){
			if(map[i][j] == BOX_DEC){
				return false;
			}
			if(dec.x == man.x && dec.y == man.y){
				return false;
			}
		}
	}
	return true;
}

//�L�Y������D
void gameOverScren(IMAGE *bg,bool quiet){
	if(quiet){
		IMAGE victory;
		putimage(0,0,bg);
		loadimage(&victory,_T("victory.png"),VICTORY_WIDTH,VICTORY_HEIGTH,true);	//���d�����DƬ
		putimage(96,161,&victory);

		settextcolor(WHITE);
		settextstyle(25,0,"����");
		//�L�u����
		RECT rc = {0,0,BG_WIDTH,BG_HEIGTH-VICTORY_HEIGTH-161};
		//�@ʾ���֣���ֱ���У�ˮƽ���У������@ʾ��ͬһ��
		drawtext(_T("��ϲ������˵�һ�P��δ����m"),&rc,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}else{
		IMAGE defeat;
		putimage(0,0,bg);
		loadimage(&defeat,_T("defeat.jpg"),DEFEAT_WIDTH,DEFEAT_HEIGTH,true);	//���d�����DƬ
		putimage(122,163,&defeat);	

		settextcolor(WHITE);
		settextstyle(25,0,"����");
		//�L�u����
		RECT rc = {0,0,BG_WIDTH,BG_HEIGTH-DEFEAT_HEIGTH-163};
		//�@ʾ���֣���ֱ���У�ˮƽ���У������@ʾ��ͬһ��
		drawtext(_T("���Ĳ������^��40����"),&rc,DT_CENTER | DT_VCENTER | DT_SINGLELINE);	
	}	
}

//������������[��
void controlGame(enum direction direct){
	struct _POS preMan = man;
	struct _POS preBox = man;
	struct _POS preHit = man;

	switch(direct){
		case UP:
			preMan.x--;
			preBox.x-=2;
			preHit.x-=2;
			break;
		case DOWN:
			preMan.x++;
			preBox.x+=2;
			preHit.x+=2;
			break;
		case LEFT:
			preMan.y--;
			preBox.y-=2;
			preHit.y-=2;
			break;
		case RIGHT:
			preMan.y++;
			preBox.y+=2;
			preHit.y+=2;
			break;
	}
	
	//�Д�С��ǰ���ǲ��ǵذ�
	if(isValid(preMan) && map[preMan.x][preMan.y] == FLOOER){
		if(dec.x == man.x && dec.y == man.y){
			changeProp(preMan.x,preMan.y,MAN);
			changeProp(man.x,man.y,BOX_DEC);
			man = preMan;
			steps++;
		}else{
			changeProp(preMan.x,preMan.y,MAN);
			changeProp(man.x,man.y,FLOOER);
			man = preMan;
			steps++;
		}
	}else if(isValid(preMan) && map[preMan.x][preMan.y] == BOX){	//�Д�С��ǰ���ǲ�������
		if(map[preBox.x][preBox.y] == FLOOER){	//�Д�����ǰ�ǲ��ǵذ�
			if(dec.x == man.x && dec.y == man.y){
				changeProp(preMan.x,preMan.y,MAN);
				changeProp(man.x,man.y,BOX_DEC);
				changeProp(preBox.x,preBox.y,BOX);
				man = preMan;
				steps++;
			}else{
				changeProp(preBox.x,preBox.y,BOX);
				changeProp(preMan.x,preMan.y,MAN);
				changeProp(man.x,man.y,FLOOER);
				man = preMan;
				steps++;
			}
		}else if(map[preBox.x][preBox.y] == BOX_DEC){	//�Д�����ǰ�ǲ�������Ŀ�ĵ�
				changeProp(preBox.x,preBox.y,HIT);
				changeProp(preMan.x,preMan.y,MAN);
				changeProp(man.x,man.y,FLOOER);
				man = preMan;
				steps++;
		}
	}else if(isValid(preMan) && map[preMan.x][preMan.y] == BOX_DEC){	//�Д���ǰ���ǲ�������Ŀ�ĵ�
		changeProp(preMan.x,preMan.y,MAN);
		changeProp(man.x,man.y,FLOOER);
		man = preMan;
		dec = preMan;
		steps++;
	}else if(isValid(preMan) && map[preMan.x][preMan.y] == HIT){		//�Д���ǰ���ǲ��������ѽ��Ƅӵ���Ŀ�ĵ�
		if(map[preHit.x][preHit.y] == FLOOER){		//�Д��ѽ��Ƅӵ���Ŀ�ĵص�����ǰ��λ���ǲ��ǵذ�
			changeProp(preMan.x,preMan.y,MAN);
			changeProp(man.x,man.y,FLOOER);
			changeProp(preHit.x,preHit.y,BOX);
			man = preMan;
			dec = preMan;
			steps++;
		}
	}
}

int main(void){
	
	IMAGE bg_img;	//�����DƬ����

	initgraph(BG_WIDTH,BG_HEIGTH);	//��ʼ�����ڴ�С
	loadimage(&bg_img,_T("blackground.bmp"),BG_WIDTH,BG_HEIGTH,true);	//���d�����DƬ
	putimage(0,0,&bg_img);	//�шDƬ�ŵ�������

	//���d�����˵ȈDƬ
	loadimage(&img[WALL],_T("wall_right.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[FLOOER],_T("floor.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[BOX_DEC],_T("des.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[MAN],_T("man.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[BOX],_T("box.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[HIT],_T("box.bmp"),IMG_SIZE,IMG_SIZE,true);

	//�����؈D��ͬ�rӛ������ڵ�λ��
	for(int i=0; i<MAP_LINE; i++){
		for(int j=0; j<MAP_COLUMN; j++){
			if(map[i][j] == MAN){				
				man.x = i;
				man.y = j;
			}
			putimage(WIDTH_MOVE+IMG_SIZE*j,HEIGTH_MOVE+IMG_SIZE*i,&img[map[i][j]]);
		}
	}
	dec.x = man.x - 1;
	dec.y = man.y - 1;

	//�Дఴ���I�P�ķ����I
	bool quiet = false;
	do{
		if(_kbhit()){
			char ch = _getch();	//�@ȡ�I�P���µ�ֵ���D�Q��char��ĸ
			if(ch == KEY_UP){
				controlGame(UP);
			}else if(ch == KEY_DOWN){
				controlGame(DOWN);
			}else if(ch == KEY_LEFT){
				controlGame(LEFT);
			}else if(ch == KEY_RIGHT){
				controlGame(RIGHT);
			}else if(ch == QUIET){
				quiet = true;
			}

			/*if(steps > 40){
				break;
			}*/
			if(gameOver()){
				quiet = true;
			}
		}
		Sleep(100);
	}while(quiet == false);

	gameOverScren(&bg_img,quiet);

	system("pause");

	closegraph();

	return 0;
	
}