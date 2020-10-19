#include<stdio.h>
#include<graphics.h>//easyx函数头文件
#include<Windows.h>
#include<conio.h>
#include<iostream>
#include<fstream> 
#include <string>
#include<time.h>
#include<algorithm>
using namespace std;
int choice;
char bottle;
int map[26][26];
void save(int rank[6], int score) {
	if (score > rank[0])rank[0] = score;
	sort(rank, rank + 6);
	ofstream fout("D:\\save.txt", ios::out);	//调用构造函数打开文件
	for (int i = 1; i <=5; i++)
	{
		fout << rank[i]<<" ";
	}
	ifstream fin("D:\\save.txt", ios::in);	//文件以输入方式打开
	for (int i = 1; i <=5; i++)
	{
		fin >> rank[i];
	}
	fout.close();
}
void drawrank(int rank[6], int score) {
	settextstyle(20, 20, _T("楷体"));
	char s[10];
		for (int i = 5; i >=1; i--) {
			settextcolor(WHITE);
			sprintf_s(s, "%d", rank[i]);
			outtextxy(120, 350 + 50 * i, *s);
		}
}
void ui1() {
	settextstyle(60, 60, _T("楷体"));
	outtextxy(290, 400, _T("贪吃蛇"));
	settextstyle(15, 15, _T("common"));
	outtextxy(490, 500, _T("ha1.0版"));
	outtextxy(700, 600, _T("请按回车以继续....."));
	int op = 0;
	while (op != 13) {
		if (_kbhit() != 0) {
			op = _getch();
		}
	}
}
void ui2(int choice) {
	settextstyle(20, 20, _T("楷体"));
	for (int i = 1; i <= 5; i++) {
		if (i == choice) {
			settextcolor(RED);
			setlinecolor(RED);
		}
		else {
			settextcolor(WHITE);
			setlinecolor(WHITE);
		}
		rectangle(400, i * 120, 600, i * 120 + 70);
		switch (i) {
		case 1:outtextxy(420, i * 120 + 30, _T("开始游戏")); break;
		case 2:outtextxy(420, i * 120 + 30, _T("难度大小")); break;
		case 3:outtextxy(420, i * 120 + 30, _T("载入进度")); break;
		case 4:outtextxy(420, i * 120 + 30, _T("游戏说明")); break;
		case 5:outtextxy(420, i * 120 + 30, _T("退出游戏")); break;
		}
	}

}
void newmapfood(int map[26][26]) {
	int x = (rand() % 24) + 2;
	int y = (rand() % 24) + 2;
	if (x != 1 && y != 1 && x != 25 && y != 25)
		map[x][y] = 2;//随机食物
}
void newmapbomb(int map[26][26]) {
	int x = (rand() % 23) + 2;
	int y = (rand() % 23) + 2;
	if (x != 1 && y != 1 && x != 25 && y != 25)
		map[x][y] = 3;//随机炸弹
}
void newmapgrass(int map[26][26]) {
	int x = (rand() % 24) + 2;
	int y = (rand() % 24) + 2;
	if (x != 1 && y != 1 && x != 25 && y != 25)
		map[x][y] = 4;//随机毒草
}
void mapchushi(int* p, int x, int y)//初始化地图，固定一些毒草炸弹
{
	if (x == 1 || x == 25)*p = 1;
	else if (y == 1 || y == 25)*p = 1;
	else if (x == 3 && y == 4)*p = 2;
	else if (x == 6 && y == 8)*p = 3;
	else if (x == 9 && y == 12)*p = 4;
	else *p = 0;
}
void newmap() {
	newmapfood(map);
	newmapbomb(map);
	newmapgrass(map);
}
void drawmap(int map[26][26], int* x, int* y,int score) {
	settextstyle(27, 27, _T("楷体"));
	settextcolor(WHITE);
	outtextxy(620,600 , _T("目前得分："));
	char s[10];
	sprintf_s(s, "%d", score);
	outtextxy(860, 605, *s);
	for (int i = 1; i <= 25; i++) {
		for (int j = 1; j <= 25; j++) {
			switch (map[i][j]) {
			case 0:setfillcolor(WHITE); break;//空地
			case 1:setfillcolor(YELLOW); break;//墙
			case 2:setfillcolor(GREEN); break;//食物
			case 3:setfillcolor(BLACK); break;//炸弹
			case 4:setfillcolor(BLUE); break;//毒草
			}
			if (map[i][j] > 100)
				setfillcolor(GREEN);//蛇身
			if (*x == i && *y == j)setfillcolor(BLACK);
			solidrectangle(20 * i, 20 * j, 20 * i + 20, 20 * j + 20);
		}
	}
	
}
void endgame(int rank[6],int score) {
	cleardevice();
	FlushBatchDraw();
	save(rank, score);
	char s[10];
	sprintf_s(s, "%d",score);
	settextcolor(WHITE);
	settextstyle(50, 50, _T("楷体"));
	outtextxy(100, 100, _T("游戏结束"));
	outtextxy(500, 500, _T("得分："));
	outtextxy(750, 500, *s);
	settextstyle(40, 40, _T("楷体"));
	outtextxy(100, 350, _T("排行榜:"));
	drawrank(rank,score);
	FlushBatchDraw();
	int op = 1;
	while (op != 27) {
		if (_kbhit() != 0) {
			op = _getch();
		}
	}
	exit(0);
}
struct snake {
	int headx;
	int heady;
	int length;
	int dirction;
}; snake s;
//w1,a2,s3,d4;
void change(int map[26][26], int l) {
	for (int i = 1; i <= 26; i++) {
		for (int j = 1; j <= 26; j++) {
			int* p = &map[i][j];
			if (*p > 100) {
				*p += l;
				if (*p <= 100) *p = 0;
			}
		}
	}
}
//w1,a2,s3,d4;方向
int score = 0;
void move(int map[26][26], int direction, int* s_x, int* s_y, int* length,int *score,int rank[6]) {
	int* point = score;
	switch (direction) {
	case 1:*s_y -= 1; break;
	case 2:*s_x -= 1; break;
	case 3:*s_y += 1; break;
	case 4:*s_x += 1; break;
	}
	int* p = &map[*s_x][*s_y];
	
	if (*p == 1)endgame(rank,*point); //触墙
	else if (*p > 100)endgame(rank,*point);//吃自己
	else if (*p == 2) {
		change(map, 1);
		*length += 1;
		*point+=1;
		newmapfood(map);
		//吃到食物长度加1
	}
	else if (*p == 3) {
		change(map, -*length / 2);
		*length -= *length / 2;
		*point -= 5;
		if (*point < 0) {
			endgame(rank, 0);
		}
		if (*length <= 0)endgame(rank,*point);
		newmapbomb(map);
		newmapbomb(map);
	}
	else if (*p == 4) {//毒草长度减一
		change(map, -1);
		*length -= 1;
		*point -= 2;
		if(*point<0){
			endgame(rank, 0);
		}
		if (*length <= 0)endgame(rank,*point);
		newmapgrass(map);
		newmapgrass(map);
	}
	*p = 101 + *length;
	change(map, -1);
	cleardevice();
	drawmap(map, &s.headx, &s.heady,*point);
}
void f1(int rank[6],int difficult) {
	cleardevice();
	for (int i = 1; i <= 25; i++) {
		for (int j = 1; j <= 25; j++) {
			int* p = &map[i][j];
			mapchushi(p, i, j);
		}
	}
	newmap();
	s.headx = 10;
	s.heady = 10;
	s.length = 7;
	s.dirction = 1;
	bottle = 0;
	cleardevice();
	//w1,a2,s3,d4;
	while (bottle != 27)
	{
		if (_kbhit() != 0)bottle = _getch();
		if (bottle == 'a') {
			if (s.dirction == 4)continue;
			s.dirction = 2;
		}
		else if (bottle == 'w') {
			if (s.dirction == 3)continue;
			s.dirction = 1;
		}
		else if (bottle == 'd') {
			if (s.dirction == 2)continue;
			s.dirction = 4;
		}
		else if (bottle == 's') {
			if (s.dirction == 1)continue;
			s.dirction = 3;
		}
		move(map, s.dirction, &s.headx, &s.heady, &s.length, &score,rank);
		FlushBatchDraw();
		Sleep(300 / difficult);//难度控制
	}
	int op = 1;
	while (op != 27) {
		if (_kbhit() != 0)
			op = _getch();
	}
}
void f2(int rank[6]) {//难度界面
	char bottle = 0;
	int diff = 2;
	while (bottle != 27) {
		if (_kbhit() != 0)bottle = _getch();
		if (bottle == 13) {
			f1(rank,diff); return;
		}
		else if (bottle == 'w' && diff != 1) {
			diff--;
			bottle = 0;
			continue;
		}
		else if (bottle == 's' && diff!= 3) {
			diff++;
			bottle = 0;
			continue;
		}
		else if (bottle == 27)exit(0);
		 
		for (int i = 1; i <= 3; i++) {
			if (i == diff) {
				settextcolor(RED);
				setlinecolor(RED);
			}
			else {
				settextcolor(WHITE);
				setlinecolor(WHITE);
			}
			rectangle(400, i * 120, 600, i * 120 + 70);
			switch (i) {
			case 1:outtextxy(420, i * 120 + 30, _T("简单")); break;
			case 2:outtextxy(420, i * 120 + 30, _T("中等")); break;
			case 3:outtextxy(420, i * 120 + 30, _T("困难")); break;
			}
		}EndBatchDraw();
	}

}
//未完成的存档环节
void f3() {

}
//游戏说明函数
void f4() {
	settextstyle(25, 25, _T("楷体"));
	outtextxy(10, 10, _T("   这是一个用c++语言开发的贪吃蛇游戏,"));
	outtextxy(10, 45, _T("绿色代表食物，黑色代表炸弹，紫色代表"));
	outtextxy(10, 80, _T("毒草。吃一个食物会加一分，吃炸弹会长度"));
	outtextxy(10, 115, _T("减半并扣5分，吃毒草会长度减一并扣2分。"));
	outtextxy(10, 150, _T("   您可以选择三种难度来体验游戏。"));
	outtextxy(700, 700, _T("按ESC返回"));
	int op = 1;
	while (op != 27) {
		if (_kbhit() != 0) {
			op = _getch();
		}
	}
}
//中转站函数
void turnto(int rank[6],int choice) {
	switch (choice) {
	case 1:f1(rank,1); break;
	case 2:f2(rank); break;
	case 3:f3(); break;
	case 4:f4(); break;
	case 5:exit(0); break;
	}
}
int main() {
	srand(time(NULL));
	initgraph(1000, 1000);
	int rank[6];
	//初始化
	for (int i = 1; i <= 5; i++) {
		rank[i] = 0;
	}
	ifstream fin("D:\\save.txt", ios::in);	//从硬盘到内存
	if (!fin)
	{
		save(rank,0);	
	}
	else
	{
		for (int i = 1; i <= 5; i++)
		{
			fin >> rank[i];
		}
		sort(rank, rank + 6);
	}
	ui1();
	choice = 1;
	while (bottle != 27) {
		BeginBatchDraw();
		cleardevice();
		if (_kbhit() != 0)bottle = _getch();
		if (bottle == 'w' && choice != 1) {
			choice--;
			bottle = 0;
			continue;
		}
		else if (bottle == 's' && choice != 5) {
			choice++;
			bottle = 0;
			continue;
		}
		else if (bottle == 13) {
			cleardevice();
			EndBatchDraw();
			turnto(rank,choice);
			bottle = 0;
			continue;
		}
		ui2(choice);
		EndBatchDraw();
	}
}