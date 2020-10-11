#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
using namespace std;
int choice;
char bottle;
/// <summary>
/// ui
/// </summary>
void ui1() {
	settextstyle(50, 50, _T("common"));
	outtextxy(400, 400, _T("贪吃蛇"));
	settextstyle(15, 15, _T("common"));
	outtextxy(700, 600, _T("请按回车以继续....."));
	int op=0;
	while (op != 13) {
		if (_kbhit() != 0) {
			op = _getch();
		}
	}
}
void ui2(int choice) {
	settextstyle(20, 20, _T("common"));
	for (int i = 1; i <= 5; i++) {
		if (i== choice) {
			settextcolor(RED);
			setlinecolor(RED);
		}
		else {
			settextcolor(WHITE);
			setlinecolor(WHITE);
		}
		rectangle(400, i * 120 , 600, i * 120 + 70);
		switch (i) {
		case 1:outtextxy(420, i * 120 + 30, _T("开始游戏")); break;
		case 2:outtextxy(420, i * 120 + 30, _T("难度大小")); break;
		case 3:outtextxy(420, i * 120 + 30, _T("载入进度")); break;
		case 4:outtextxy(420, i * 120 + 30, _T("游戏说明")); break;
		case 5:outtextxy(420, i * 120 + 30, _T("退出游戏")); break;
		}
	}
}
void f1() {
	//settextcolor(WHITE);
	//setlinecolor(WHITE);
	for (int i = 1; i <= 50; i++) {
		for (int j = 1; j <= 50; j++) {
			//cout<<""
		}
	}
	int op = 1;
	while (op != 27) {
		if (_kbhit() != 0) {
			op = _getch();
		}
	}
}


void f2() {

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
	case 1:f1(); break;
	case 2:f2(); break;
	case 3:f3(); break;
	case 4:f4(); break;
	case 5:exit(0); break;
	}
}
int main(){
	initgraph(1000, 1000);
	ui1();
	choice = 1;
	while (bottle != 27) {
		BeginBatchDraw();
		cleardevice();
		if (_kbhit() != 0)bottle=_getch();
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
		else if (bottle == 27)exit(0);
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