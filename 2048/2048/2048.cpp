#include<iostream>
#include<conio.h>
#include<time.h>
#include<graphics.h>
using namespace std;
int map1[4][4] = { 0 };
void move1(int start, int mo, int fx)
{
	if (fx == 1)
		for (int a = 0; a < 4; a++)
		{
			int start_1 = start, start_2 = start + mo;
			while (start_2 >= 0 && start_2 < 4)
			{
				if (map1[a][start_2] == 0)
				{
					start_2 += mo;
					continue;
				}
				else if (map1[a][start_1] == 0)
				{
					map1[a][start_1] = map1[a][start_2];
				}
				else if (map1[a][start_2] == map1[a][start_1])
				{
					map1[a][start_1] = 2 * map1[a][start_1]; start_1 += mo;
				}
				else if (map1[a][start_2] != map1[a][start_1])
				{
					map1[a][start_1 = start_1 + mo] = map1[a][start_2];
					if (start_1 == start_2)
					{
						start_2 += mo; continue;
					}
				}
				map1[a][start_2] = 0; start_2 += mo;
			}
		}
	else if (fx == 0)
	{
		for (int a = 0; a < 4; a++)
		{
			int start_1 = start, start_2 = start + mo;
			while (start_2 >= 0 && start_2 < 4)
			{
				if (map1[start_2][a] == 0)
				{
					start_2 += mo;
					continue;
				}
				else if (map1[start_1][a] == 0)
				{
					map1[start_1][a] = map1[start_2][a];
				}
				else if (map1[start_2][a] == map1[start_1][a])
				{
					map1[start_1][a] = 2 * map1[start_1][a]; start_1 += mo;
				}
				else if (map1[start_2][a] != map1[start_1][a])
				{
					map1[start_1 = start_1 + mo][a] = map1[start_2][a];
					if (start_1 == start_2)
					{
						start_2 += mo; continue;
					}
				}
				map1[start_2][a] = 0; start_2 += mo;
			}
		}
	}
}
void print(int& max)
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout.width(5);
			if (max < map1[i][j])max = map1[i][j];
			cout << map1[i][j] << '|';
		}
		cout << '\n' << "----- ----- ----- -----" << '\n';
	}
	cout << " the bigest score: " << max << '\n';
}
void rands()
{
	srand(time(0));
	int i = rand() % 4;
	int j = rand() % 4;
	while (1)
	{
		if (map1[i][j] == 0)
		{
			map1[i][j] = rand() % 10 ? 2 : 4;
			break;
		}
		i = rand() % 4;
		j = rand() % 4;
	}
}
bool fill(int& gameflag) //flag判断游戏是否结束
{
	gameflag = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map1[i][j] == 0)
			{
				gameflag = 1;
				return false;
			}
			if (i < 3 && gameflag == 0)
			{
				if (map1[i][j] == map1[i + 1][j]) gameflag = 1;
			}
			if (j < 3 && gameflag == 0)
			{
				if (map1[i][j] == map1[i][j + 1]) gameflag = 1;
			}
		}
	}
	return true;
}
void keyDonw(int &flag)//小键盘建码值（上72	下80	左75	右77）
{
		char c = _getch();
		if (c == 75 || c == 77 || c == 72 || c == 80)
		{
			if (c == 75) //左
				move1(0, 1, 1);
			else if (c == 77) //右
				move1(3, -1, 1);
			else if (c == 72)  //上
				move1(0, 1, 0);
			else if (c == 80)  //下
				move1(3, -1, 0);
			if (!fill(flag))
				rands();
		}
}
IMAGE pic[13];
void load_pic()
{
	loadimage(&pic[0], "std\\0.bmp", 160, 160);
	loadimage(&pic[1], "std\\military_font_7_2.bmp", 160, 160);
	loadimage(&pic[2], "std\\military_font_7_4.bmp", 160, 160);
	loadimage(&pic[3], "std\\military_font_7_8.bmp", 160, 160);
	loadimage(&pic[4], "std\\military_font_7_16.bmp", 160, 160);
	loadimage(&pic[5], "std\\military_font_7_32.bmp", 160, 160);
	loadimage(&pic[6], "std\\military_font_7_64.bmp", 160, 160);
	loadimage(&pic[7], "std\\military_font_7_128.bmp", 160, 160);
	loadimage(&pic[8], "std\\military_font_7_256.bmp", 160, 160);
	loadimage(&pic[9], "std\\military_font_7_512.bmp", 160, 160);
	loadimage(&pic[10], "std\\military_font_7_1024.bmp", 160, 160);
	loadimage(&pic[11], "std\\military_font_7_2046.bmp", 160, 160);
	loadimage(&pic[12], "std\\gameover.bmp", 640, 640);
}
int bit(int n)
{
	int count = 0;
	if (n == 0)return 0;
	while (n!=1)
	{
		n >>= 1;
		count++;
	}
	return count;
}
void drow()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int b = bit(map1[i][j]);
			putimage(j*160, i*160, &pic[b], SRCAND);
		}
	}
}
void clear()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			map1[i][j] = 0;
}
int main()
{
	initgraph(640, 640);	//创建图形窗口
	int max = 0; 
	int gameflag = 1;
	load_pic();
	while (1)
	{
		
		cleardevice();//刷新
		loadimage(NULL, "std\\beijing.jpg", 640, 640);//NULL 不可以bmp文件
		BeginBatchDraw();
		drow();
		if (!gameflag)
		{
			BeginBatchDraw();
			putimage(0, 0, &pic[12], SRCAND);
			EndBatchDraw();
			while (_getch() != ' ');
			clear();
			gameflag = 1;
			cleardevice();
			loadimage(NULL, "std\\beijing.jpg", 640, 640);//NULL 不可以bmp文件
			drow();
		}
		EndBatchDraw();
		keyDonw(gameflag);
		//cout << gameflag;
	}
}