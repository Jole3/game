#include <iostream>
#include <string>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include "box.h"

//創建數組來存放不同種類的圖片
IMAGE img[ALL];

struct _POS man;
struct _POS dec;
int steps = 0;

//遊戲地圖：0-墻，1-地板，2-箱子目的地，3-小人，4-箱子，5-箱子目的地
int map[][12] = {{0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,1,0,1,1,1,1,1,1,1,0,0},
				 {0,1,4,1,0,2,1,0,2,1,0,0},
				 {0,1,0,1,0,1,0,0,1,1,1,0},
				 {0,1,0,2,0,1,1,4,1,1,1,0},
				 {0,1,1,1,0,3,1,1,1,4,1,0},
				 {0,1,2,1,1,4,1,1,1,1,1,0},
				 {0,1,0,0,1,0,1,1,0,0,1,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0}};

//改變道具
void changeProp(int x,int y,enum PROP pro){
	map[x][y] = pro;
	putimage(WIDTH_MOVE+IMG_SIZE*y,HEIGTH_MOVE+IMG_SIZE*x,&img[map[x][y]]);
}

//判斷遊戲是否結束
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

//繪結束界面圖
void gameOverScren(IMAGE *bg,bool quiet){
	if(quiet){
		IMAGE victory;
		putimage(0,0,bg);
		loadimage(&victory,_T("victory.png"),VICTORY_WIDTH,VICTORY_HEIGTH,true);	//加載背景圖片
		putimage(96,161,&victory);

		settextcolor(WHITE);
		settextstyle(25,0,"宋体");
		//繪製矩形
		RECT rc = {0,0,BG_WIDTH,BG_HEIGTH-VICTORY_HEIGTH-161};
		//顯示文字，垂直居中，水平居中，文字顯示在同一行
		drawtext(_T("恭喜您完成了第一關，未完待續"),&rc,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}else{
		IMAGE defeat;
		putimage(0,0,bg);
		loadimage(&defeat,_T("defeat.jpg"),DEFEAT_WIDTH,DEFEAT_HEIGTH,true);	//加載背景圖片
		putimage(122,163,&defeat);	

		settextcolor(WHITE);
		settextstyle(25,0,"宋体");
		//繪製矩形
		RECT rc = {0,0,BG_WIDTH,BG_HEIGTH-DEFEAT_HEIGTH-163};
		//顯示文字，垂直居中，水平居中，文字顯示在同一行
		drawtext(_T("您的步數超過了40步！"),&rc,DT_CENTER | DT_VCENTER | DT_SINGLELINE);	
	}	
}

//控制人物，操作遊戲
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
	
	//判斷小人前面是不是地板
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
	}else if(isValid(preMan) && map[preMan.x][preMan.y] == BOX){	//判斷小人前面是不是箱子
		if(map[preBox.x][preBox.y] == FLOOER){	//判斷箱子前是不是地板
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
		}else if(map[preBox.x][preBox.y] == BOX_DEC){	//判斷箱子前是不是箱子目的地
				changeProp(preBox.x,preBox.y,HIT);
				changeProp(preMan.x,preMan.y,MAN);
				changeProp(man.x,man.y,FLOOER);
				man = preMan;
				steps++;
		}
	}else if(isValid(preMan) && map[preMan.x][preMan.y] == BOX_DEC){	//判斷人前面是不是箱子目的地
		changeProp(preMan.x,preMan.y,MAN);
		changeProp(man.x,man.y,FLOOER);
		man = preMan;
		dec = preMan;
		steps++;
	}else if(isValid(preMan) && map[preMan.x][preMan.y] == HIT){		//判斷人前面是不是箱子已經移動到了目的地
		if(map[preHit.x][preHit.y] == FLOOER){		//判斷已經移動到了目的地的箱子前的位置是不是地板
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
	
	IMAGE bg_img;	//創建圖片對象

	initgraph(BG_WIDTH,BG_HEIGTH);	//初始化窗口大小
	loadimage(&bg_img,_T("blackground.bmp"),BG_WIDTH,BG_HEIGTH,true);	//加載背景圖片
	putimage(0,0,&bg_img);	//把圖片放到窗口上

	//加載墻，人等圖片
	loadimage(&img[WALL],_T("wall_right.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[FLOOER],_T("floor.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[BOX_DEC],_T("des.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[MAN],_T("man.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[BOX],_T("box.bmp"),IMG_SIZE,IMG_SIZE,true);
	loadimage(&img[HIT],_T("box.bmp"),IMG_SIZE,IMG_SIZE,true);

	//構建地圖，同時記錄人所在的位置
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

	//判斷按下鍵盤的方向鍵
	bool quiet = false;
	do{
		if(_kbhit()){
			char ch = _getch();	//獲取鍵盤按下的值，轉換為char字母
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