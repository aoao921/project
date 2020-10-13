#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<iostream>
using namespace std;
int choice;
char bottle;
int difficult;
int map[26][26];
/// <summary>
/// ui
/// </summary>

void ui1() {
	settextstyle(50, 50, _T("common"));
	outtextxy(400, 400, _T("贪吃蛇"));
	settextstyle(15, 15, _T("common"));
	outtextxy(700, 600, _T("请按回车以继续....."));
	int op = 0;
	while (op != 13) {
		if (_kbhit() != 0) {
			op = _getch();
		}
	}
}
void ui2(int choice) {
	settextstyle(20, 20, _T("common"));
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
void mapchushi(int* p, int x, int y)
{
	if (x == 1 || x == 25)*p = 1;
	else if (y == 1 || y == 25)*p = 1;
	else *p = 0;
	if (x == 20 && y == 20)*p=2;
	if (x == 15 && y == 15)*p = 2;
	if (x == 10 && y == 15)*p = 3;
}
void drawmap(int map[26][26],int *x,int *y) {
	for (int i = 1; i <= 25; i++) {
		for (int j = 1; j <= 25; j++) {
			switch (map[i][j]) {
			case 0:setfillcolor(WHITE); break;//空地
			case 1:setfillcolor(YELLOW); break;//墙
			case 2:setfillcolor(RED); break;//食物
			case 3:setfillcolor(BLUE); break;//炸弹
			}
			if (map[i][j] > 100)
				setfillcolor(GREEN);
			if(*x==i&&*y==j)setfillcolor(BLACK);
			solidrectangle(20 * i, 20 * j, 20 * i + 20, 20 * j + 20);
		}

	}
}
void endgame() {
	cleardevice();
	FlushBatchDraw();
	settextstyle(50, 50, _T("common"));
	outtextxy(100, 100, _T("游戏结束"));
	outtextxy(600, 600, _T("得分："));
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
//w1,a2,s3,d4;
void move(int map[26][26], int direction, int* s_x, int* s_y, int* length) {
	switch (direction) {
	case 1:*s_y -= 1; break;
	case 2:*s_x -= 1; break; 
	case 3:*s_y += 1; break;
	case 4:*s_x += 1; break;
	}
	int* p = &map[*s_x][*s_y];

	if (*p == 1)endgame(); //触墙
	else if (*p > 100)endgame();//吃自己
	else if (*p == 2) {
		change(map, 1);
		*length += 1;
		//吃到食物长度加1
	}
	else if (*p == 3) {
		change(map, -*length / 2);
		*length -= *length / 2;
	}
	*p = 101 + *length;
	change(map, -1);
}
void f1(int diffcult) {
	//settextcolor(WHITE);
	//setlinecolor(WHITE);
	for (int i = 1; i <= 25; i++) {
		for (int j = 1; j <= 25; j++) {
			int* p = &map[i][j];
			mapchushi(p, i, j);
		}
	}
	s.headx = 10;
	s.heady = 10;
	s.length = 5;
	s.dirction = 1;
	bottle = 0;
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
		move(map, s.dirction, &s.headx, &s.heady, &s.length);
		//cleardevice();
		//Sleep(1);
		drawmap(map, &s.headx, &s.heady);
		FlushBatchDraw();
		Sleep(200);
	}

	int op = 1;
	while (op != 27) {
		if (_kbhit() != 0)
			op = _getch();
	}
}
void f2(int *p) {//难度界面
	char bottle = 0;
	while (bottle != 27) {
		//BeginBatchDraw();
		//cleardevice();
		if (_kbhit() != 0)bottle = _getch();
		if (bottle == 'w' && choice != 1) {
			choice--;
			bottle = 0;
			continue;
		}
		else if (bottle == 's' && choice != 3) {
			choice++;
			bottle = 0;
			continue;
		}
		else if (bottle == '27')exit(0);
		else if (bottle == '13') {
			*p= choice; return;
		}
	for (int i = 1; i <= 3; i++) {
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
		case 1:outtextxy(420, i * 120 + 30, _T("简单")); break;
		case 2:outtextxy(420, i * 120 + 30, _T("中等")); break;
		case 3:outtextxy(420, i * 120 + 30, _T("困难")); break;
		}
	}
	}//cleardevice();
	//BeginBatchDraw();
	//EndBatchDraw();
	/*int op = 1;
	while (op != 27) {
		if (_kbhit() != 0) {
			op = _getch();
		}
	}*/
	//difficult = choice;
}
void f3() {

}
void f4() {
	//BeginBatchDraw();
	//cleardevice();
	settextstyle(15, 15, _T("common"));
	outtextxy(10, 10, _T("这是一个用c++语言开发的贪吃蛇游戏,"));
	outtextxy(700, 700, _T("按ESC返回"));
	//EndBatchDraw();
	//Sleep(10000);
	int op = 1;
	while (op != 27) {
		if (_kbhit() != 0) {
			op = _getch();
		}
	}

}
void turnto(int choice) {
	//cleardevice();
	switch (choice) {
	case 1:f1(difficult); break;
	case 2:f2(&difficult); break;
	case 3:f3(); break;
	case 4:f4(); break;
	case 5:exit(0); break;
	}
}
int main() {
	initgraph(1000, 1000);
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
		//else if (bottle == 27)exit(0);
		else if (bottle == 13) {
			cleardevice();
			EndBatchDraw();
			turnto(choice);
			bottle = 0;
			continue;
		}
		ui2(choice);
		EndBatchDraw();
		//Sleep(33);
	}

	//Sleep(10000);
}