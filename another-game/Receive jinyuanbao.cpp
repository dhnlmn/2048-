#include<graphics.h>
#include<iostream>
#include<time.h>
#include<string>
#include<conio.h>
#define NUM 20
using namespace std;
/*��Ԫ����Ϸ
ͼ�λ����
ͼ�ο�����easyX��
����ͷ�ļ�#include<graphics.h>
1.ͼ�λ�����
initgraph(800, 600);	//����ͼ�δ���
setbkcolor(RGB(255, 0, 255))//���ñ�����ɫ
cleardevice();		//ˢ��
closegraph();		//�رմ���
2.������ͼ����
IMAGE img;			//����ͼƬ����
loadimage(&img, "ͼƬ·��")��	//����ͼƬ
putimage(0, 0, &img��SRCAND);	//������ͼƬ
putimage(0, 0, &img��SRCPAINT);	//������ͼƬ
3.��������
ͨ�����̵ļ�λ�����ߵ��ƶ�����
ѡ������������ж�
С���̽���ֵ����72	��80	��75	��77��
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
4.��ӱ�������
#include<mmsystem.h>			//��ý��ͷ�ļ�
#pragma comment(lib,"winmm.lib")	//���ؾ�̬��
mciSendString("open 1.mp3");		//������
mciSendString("play 1.mp3 repeat");	//ѭ����������
5.�������
settextcolor(RGB(0, 255, 255));		//����������ɫ
settextstyle(20, 0, "");		//�������ַ��
outtextxy(810, 100, "����������ƾ۱����ƶ���Ԫ��");//��ʾ����*/
//�۱���
struct
{
	int x, y;
}potpos={400,580};
//Ԫ��
struct
{
	int x, y; //����
	int  movey;//�ٶ�
	int grade;//����
}moneypos[NUM];
//��ʼ��Ԫ��
void init_money(int i)
{
	moneypos[i].x = rand() % 700;
	moneypos[i].y = rand() % 250+20;
	moneypos[i].grade = 10;
	moneypos[i].movey = 0;
}
//����ͼƬ����
IMAGE pot[2], money[2];
//����ͼƬ
void loadSource()
{
	//�۱���
	loadimage(&pot[0],"source\\potY.bmp", 240, 70);//�۱����С
	loadimage(&pot[1], "source\\pot.bmp", 240, 70);
	//Ԫ��
	loadimage(&money[0], "source\\moneyY.bmp", 40, 40);
	loadimage(&money[1], "source\\money.bmp", 40, 40); //Ԫ����С
}
//���۱���
void drowpot()
{
	putimage(potpos.x,potpos.y,&pot[0],SRCAND);//������ͼ
	putimage(potpos.x, potpos.y, &pot[1], SRCPAINT);//������ͼ
}
//��Ԫ��
void drowMoney()
{
	for (int i = 0; i < NUM; i++)
	{
		putimage(moneypos[i].x, moneypos[i].y, &money[0], SRCAND);//������ͼ
		putimage(moneypos[i].x, moneypos[i].y, &money[1], SRCPAINT);//������ͼ
	}
}
//����
void keyDown()
{
	if (_kbhit()) {
		char useKey = _getch();//�����ַ���
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
//��Ԫ��
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
	settextstyle(25, 0, "����");
	settextcolor(YELLOW);
	outtextxy(820, 100, grade.c_str());
	outtextxy(820, 200, sum.c_str());
}
void menu()
{
	setlinestyle(PS_SOLID,3);//�������,����3
	setlinecolor(RED);
	line(750, 0, 750, 800);
	//�������
	settextstyle(25, 0, "����");
	settextcolor(YELLOW);
	outtextxy(800, 10, "��Ԫ����Ϸ");
	outtextxy(760, 100, "����:");
	outtextxy(760, 200, "����:");
	outtextxy(760, 300, "ʱ�䣺2019/4/18");
}
int main()
{
	srand(time(0));
	initgraph(1000, 640);	//����ͼ�δ���
	for (int i = 0; i < NUM; i++)
	{
		init_money(i);
	}
	loadSource();
	while (1)
	{
		BeginBatchDraw();
		cleardevice();//ˢ��
		menu();
		drowpot();
		loadimage(NULL, "source\\moneyTree.png", 800, 640);
		drowMoney();
		//Ԫ������
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
	setbkcolor(RGB(255, 0, 255));//���ñ�����ɫ
	closegraph();		//�رմ���
}