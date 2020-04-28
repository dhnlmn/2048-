#include<graphics.h>
#include<iostream>
#include<time.h>
#include<string>
#include<conio.h>
#define NUM 20
using namespace std;
/*接元宝游戏
图形化编程
图形库插件（easyX）
包含头文件#include<graphics.h>
1.图形化窗口
initgraph(800, 600);	//创建图形窗口
setbkcolor(RGB(255, 0, 255))//设置背景颜色
cleardevice();		//刷新
closegraph();		//关闭窗口
2.基本贴图技术
IMAGE img;			//定义图片变量
loadimage(&img, "图片路径")；	//加载图片
putimage(0, 0, &img，SRCAND);	//贴掩码图片
putimage(0, 0, &img，SRCPAINT);	//贴背景图片
3.按键操作
通过键盘的键位控制蛇的移动方向
选择语句做按键判断
小键盘建码值（上72	下80	左75	右77）
switch (userKey)
{
case 'a':
case 'A':
case 75:

	break;
case 'd':
case 'D':
case 77:

	break;
}
4.添加背景音乐
#include<mmsystem.h>			//多媒体头文件
#pragma comment(lib,"winmm.lib")	//加载静态库
mciSendString("open 1.mp3");		//打开音乐
mciSendString("play 1.mp3 repeat");	//循环播放音乐
5.文字输出
settextcolor(RGB(0, 255, 255));		//设置文字颜色
settextstyle(20, 0, "");		//设置文字风格
outtextxy(810, 100, "按方向键控制聚宝盆移动接元宝");//显示文字*/
//聚宝盆
struct
{
	int x, y;
}potpos={400,580};
//元宝
struct
{
	int x, y; //坐标
	int  movey;//速度
	int grade;//分数
}moneypos[NUM];
//初始化元宝
void init_money(int i)
{
	moneypos[i].x = rand() % 700;
	moneypos[i].y = rand() % 250+20;
	moneypos[i].grade = 10;
	moneypos[i].movey = 0;
}
//定义图片变量
IMAGE pot[2], money[2];
//加载图片
void loadSource()
{
	//聚宝盆
	loadimage(&pot[0],"source\\potY.bmp", 240, 70);//聚宝盆大小
	loadimage(&pot[1], "source\\pot.bmp", 240, 70);
	//元宝
	loadimage(&money[0], "source\\moneyY.bmp", 40, 40);
	loadimage(&money[1], "source\\money.bmp", 40, 40); //元宝大小
}
//画聚宝盆
void drowpot()
{
	putimage(potpos.x,potpos.y,&pot[0],SRCAND);//贴掩码图
	putimage(potpos.x, potpos.y, &pot[1], SRCPAINT);//贴掩码图
}
//画元宝
void drowMoney()
{
	for (int i = 0; i < NUM; i++)
	{
		putimage(moneypos[i].x, moneypos[i].y, &money[0], SRCAND);//贴掩码图
		putimage(moneypos[i].x, moneypos[i].y, &money[1], SRCPAINT);//贴掩码图
	}
}
//按键
void keyDown()
{
	if (_kbhit()) {
		char useKey = _getch();//输入字符；
		if (useKey == 75)
		{
			potpos.x -= 30;
			if (potpos.x <= 0)
				potpos.x = 0;
		}
		if (useKey == 77)
		{
			potpos.x += 30;
			if (potpos.x >= 750 - 240)
				potpos.x = 750 - 240;
		}
	}
}
//接元宝
int getMoney()
{
	static int sum = 0;
	for (int i = 0; i < NUM; i++)
	{
		if (moneypos[i].x >= potpos.x && moneypos[i].x <= 240 + potpos.y && moneypos[i].y >= 580)
		{
			init_money(i);
			sum++;
		}
	}
	return sum;
}
void showGrade(int n)
{		
	string sum,grade;
	sum = to_string(n);
	grade = to_string(n*10);
	settextstyle(25, 0, "楷体");
	settextcolor(YELLOW);
	outtextxy(820, 100, grade.c_str());
	outtextxy(820, 200, sum.c_str());
}
void menu()
{
	setlinestyle(PS_SOLID,3);//线条风格,像素3
	setlinecolor(RED);
	line(750, 0, 750, 800);
	//文字输出
	settextstyle(25, 0, "楷体");
	settextcolor(YELLOW);
	outtextxy(800, 10, "接元宝游戏");
	outtextxy(760, 100, "分数:");
	outtextxy(760, 200, "数量:");
	outtextxy(760, 300, "时间：2019/4/18");
}
int main()
{
	srand(time(0));
	initgraph(1000, 640);	//创建图形窗口
	for (int i = 0; i < NUM; i++)
	{
		init_money(i);
	}
	loadSource();
	while (1)
	{
		BeginBatchDraw();
		cleardevice();//刷新
		menu();
		drowpot();
		loadimage(NULL, "source\\moneyTree.png", 800, 640);
		drowMoney();
		//元宝下落
		for (int i = 0; i < NUM; i++)
		{
			moneypos[i].movey = 10;
			moneypos[i].y += moneypos[i].movey;
			if(moneypos[i].y>=640)init_money(i);
		}
		showGrade(getMoney());
		EndBatchDraw();
		keyDown();
	}
	setbkcolor(RGB(255, 0, 255));//设置背景颜色
	closegraph();		//关闭窗口
}