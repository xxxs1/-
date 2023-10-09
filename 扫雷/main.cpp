#include<stdio.h>
#include"shaolei.h"
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<time.h>
#include<Windows.h>
#include<iostream>
#include <algorithm> // 必须包含这个头文件才能使用std::fill
using namespace std;
IMAGE img[12];//储存图片

int level=0;//定义关卡
int old_level = 0;

// 初始化
int map[COWS][ROMS] = { 0 };//初始化棋盘
int cut = COWS * ROMS - COUNT_MINE;//判断棋盘上还有几个雷
int ECOWS= COWS - 8;
int EROMS = ROMS - 8;
int MCOWS = COWS - 4;
int MROMS = ROMS - 4;

//布置雷
void setmine( int map[COWS][ROMS],int count_mine)
{
	int i, j, a, b;
	int count = count_mine;//雷的数量
	
		int x, y;//x,y坐标
		switch (level)
		{
		case 0:
			while (count)
			{
				x = rand() % 7;
				y = rand() % 11;
				if (map[x][y] == 0)
				{
					map[x][y] = -1;
					count--;
				}
			}
			
			//确定雷附近的数
			for (i = 0; i < ECOWS; i++)
			{
				for (j = 0; j < EROMS; j++)
				{
					if (map[i][j] == -1)
					{
						for (a = i - 1; a <= i + 1; a++)
						{
							for (b = j - 1; b <= j + 1; b++)
							{
								if ((a >= 0 && a <= ECOWS && b >= 0 && b <= EROMS) && map[a][b] != -1)
									map[a][b]++;
							}
						}
							
					}
				}
			}
			show(map);
			//数据的加密
			for (i = 0; i < ECOWS; i++)
			{
				for (j = 0; j < EROMS; j++)
				{
					map[i][j] += 20;
				}
			}
			break;
			
			
		case 1:

			while (count)
			{
				x = rand() % 11;
				y = rand() % 15;
				if (map[x][y] == 0)
				{
					map[x][y] = -1;
					count--;
				}
			}
		
			//确定雷附近的数
			for (i = 0; i < MCOWS; i++)
			{
				for (j = 0; j < MROMS; j++)
				{
					if (map[i][j] == -1)
					{
						for (a = i - 1; a <= i + 1; a++)
						{
							for (b = j - 1; b <= j + 1; b++)
							{
								if ((a >= 0 && a <= MCOWS && b >= 0 && b <= MROMS) && map[a][b] != -1)
									map[a][b]++;
							}
						}
							
					}
				}
			}
			//数据的加密
			for (i = 0; i < MCOWS; i++)
			{
				for (j = 0; j < MROMS; j++)
				{
					map[i][j] += 20;
				}
			}
			break;
		case 2:

			while (count)
			{
				x = rand() % 15;
				y = rand() % 20;
				if (map[x][y] == 0)
				{
					map[x][y] = -1;
					count--;
				}
			}
		

			//确定雷附近的数
			for (i = 0; i < COWS; i++)
			{
				for (j = 0; j < ROMS; j++)
				{
					if (map[i][j] == -1)
					{
						for (a = i - 1; a <= i + 1; a++)
						{
							for (b = j - 1; b <= j + 1; b++)
							{
								if ((a >= 0 && a <= COWS && b >= 0 && b <= ROMS) && map[a][b] != -1)
									map[a][b]++;
							}

						}
							
					}
				}
			}
			//数据的加密
			for (i = 0; i < COWS; i++)
			{
				for (j = 0; j <ROMS; j++)
				{
					map[i][j] += 20;
				}
			}
			break;
	
		default:
			break;
		}
	
	

	
	return;
}


//导入图片
void PictureInput()
{
	int i;
	char str[50];//用一个数组来储存图片地址
	for (i = 0; i <= 11; i++)
	{
		sprintf_s(str, "./image/%d.jpg", i);
		loadimage(&img[i], str, 30, 30);
	}
}
//棋盘界面的绘制
void gamedraw()
{		
	int i, j;
	switch (level)
	{
	case 0:	
		for (i = 0; i < ECOWS; i++)
		{
			for (j = 0; j < EROMS; j++)
			{
				if (map[i][j] >= 0 && map[i][j] <= 8)
					putimage(j * 30 + 260, i * 30 + 150, &img[map[i][j]]);//	heigh	:	putimage(j * 30+140, i * 30+150, &img[map[i][j]]);
																		 //		meduim  :	putimage(j * 30+200, i * 30+150, &img[map[i][j]]);		
				else if (map[i][j] == -1)
				{
					putimage(j * 30 + 260, i * 30 + 150, &img[9]);
				}
				else if (map[i][j] > 8 && map[i][j] <= 28)
					putimage(j * 30 + 260, i * 30 + 150, &img[10]);
				else
					putimage(j * 30 + 260, i * 30 + 150, &img[11]);
			}
		}
		break;
	case 1:
		for (i = 0; i < MCOWS; i++)
		{
			for (j = 0; j < MROMS; j++)
			{
				if (map[i][j] >= 0 && map[i][j] <= 8)
					putimage(j * 30 + 200, i * 30 + 150, &img[map[i][j]]);//	heigh	:	putimage(j * 30+140, i * 30+150, &img[map[i][j]]);
				//		meduim  :	putimage(j * 30+200, i * 30+150, &img[map[i][j]]);		
				else if (map[i][j] == -1)
				{
					putimage(j * 30 + 200, i * 30 + 150, &img[9]);
				}
				else if (map[i][j] > 8 && map[i][j] <= 28)
					putimage(j * 30 + 200, i * 30 + 150, &img[10]);
				else
					putimage(j * 30 + 200, i * 30 + 150, &img[11]);
			}
		}
		break;
	case 2:
		for (i = 0; i < COWS; i++)
		{
			for (j = 0; j < ROMS; j++)
			{
				if (map[i][j] >= 0 && map[i][j] <= 8)
					putimage(j * 30 + 140, i * 30 + 150, &img[map[i][j]]);//	heigh	:	putimage(j * 30+140, i * 30+150, &img[map[i][j]]);
				//		meduim  :	putimage(j * 30+200, i * 30+150, &img[map[i][j]]);		
				else if (map[i][j] == -1)
				{
					putimage(j * 30 + 140, i * 30 + 150, &img[9]);
					
				}
				else if (map[i][j] > 8 && map[i][j] <= 28)
					putimage(j * 30 + 140, i * 30 + 150, &img[10]);
				else
					putimage(j * 30 + 140, i * 30 + 150, &img[11]);
			}
		}
		break;
		
	default:
		break;
		
	}
	
	return;
}

//在控制台上打印出棋盘
void show(int map[COWS][ROMS])
{
	int i, j;
	for (i = 0; i < COWS; i++)
	{
		for (j = 0; j < ROMS; j++)
		{
			printf(" %2d", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void open(int cow, int rom)//左键解密
{

	if (map[cow][rom] == 0)
	{
		for (int i = cow - 1; i <= cow + 1; i++)
		{
			for (int j = rom - 1; j <= rom + 1; j++)
			{
				if ((i >= 0 && i < 11 && j >= 0 && j < 11) && map[i][j] > 19)
				{
					map[i][j] -= 20;
					cut--;
					open(i, j);//递归来时将周围没有雷的地方炸开
				}

			}

		}
	}
}
//获取鼠标信息
void mouse()
{
	int cow, rom;
	MOUSEMSG msg = GetMouseMsg();//get鼠标信息

	if (level == 0)
	{
		cow = (msg.y - 150) / 30;
		rom = (msg.x - 260) / 30;
	}
	else if (level == 1)
	{

		cow = (msg.y - 150) / 30;
		rom = (msg.x - 200) / 30;

	}
	else
	{
		cow = (msg.y - 150) / 30;
		rom = (msg.x - 140) / 30;
	}


		if (msg.uMsg == WM_LBUTTONDOWN && map[cow][rom] >= 19)//鼠标左键落下
		{
			map[cow][rom] -= 20;

			if (map[cow][rom] >= 0 && map[cow][rom] <= 8)
			{
				cut--;
			}
			if (map[cow][rom] == -1)
			{
				gameover(cow, rom);
			}
			open(cow, rom);
		}
		if (msg.uMsg == WM_RBUTTONDOWN)//鼠标右键落下
			if (map[cow][rom] >= 19 && map[cow][rom] <= 28)
				map[cow][rom] += 20;
			else if (map[cow][rom] > 28)
				map[cow][rom] -= 20;
		show(map);
}

// 游戏的结束
void gameover(int cow, int rom)
{
	switch (level)
	{
	case 0:
		putimage(rom * 30+260, cow * 30+150, &img[9]);
		break;
	case 1:
		putimage(rom * 30 + 200, cow * 30 + 150, &img[9]);
		break;
	case 2:
		putimage(rom * 30 + 140, cow * 30 + 150, &img[9]);
		break;
	}

	MessageBox(NULL, "game over", "游戏结束", MB_OK);
	closegraph();
	return;
}

int Level_option()
{


	MOUSEMSG msg = GetMouseMsg();//get鼠标信息
	int x = msg.x;
	int y = msg.y;
	
	switch (level)
	{
		case 0:
			printf("%d\n%d\n%d\n", level, x, y);
			if (msg.uMsg == WM_LBUTTONDOWN && ((x >= 380 && x <= 470) && (y >= 80 && y <= 110)))
			{
				level = 1;
				cleardevice();
			
				Medium();
				
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && ((x >= 510 && x <= 600) && (y >= 80 && y <= 110)))
			{
				level = 2;
				cleardevice();
			
				HeighLevel();
			}
			else
				break;

		case 1:

			printf("%d\n%d\n%d\n", level, x, y);
			if (msg.uMsg == WM_LBUTTONDOWN && ((x >= 210 && x <= 310) && (y >= 80 && y <= 110)))
			{
				level = 0;
				cleardevice();
		
				Elem();
			}

			else if (msg.uMsg == WM_LBUTTONDOWN && ((x >= 550 && x <= 660) && (y >= 80 && y <= 110)))
			{
				level = 2;
				cleardevice();
				
				HeighLevel();
			}
			else
				break;

		case 2:
			printf("%d\n%d\n%d\n", level, x, y);
			if (msg.uMsg == WM_LBUTTONDOWN && ((x >= 150 && x <= 320) && (y >= 70 && y <= 100)))
			{
				level = 0;
				cleardevice();
	
				Elem();
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && ((x >= 350 && x <= 520) && (y >= 70 && y <= 100)))
			{
				level = 1;
				cleardevice();
				
				Medium();
			}
			else
				break;
	default:
		break;
	}
	return 0;
}



int  HeighLevel()
{
	// 设置指定区域的背景颜色为灰色
	
	setfillcolor(LIGHTGRAY);
	solidrectangle(150, 70, 320, 100);
	solidrectangle(350, 70, 520, 100);
	solidrectangle(550, 70, 720, 100);
	settextstyle(8, 8, 0);
	setbkmode(TRANSPARENT);
	outtextxy(220, 80, _T("简单"));
	outtextxy(420, 80, _T("中等"));
	outtextxy(620, 80, _T("高等"));

	line(120, 50, 120, 650);
	line(760, 50, 760, 650);
	line(120, 50, 760, 50);
	line(120, 650, 760, 650);

	return 0;
}

int Medium()
{	
	// 设置指定区域的背景颜色为灰色

	setfillcolor(LIGHTGRAY);
	solidrectangle(210, 80, 310, 110);
	solidrectangle(380, 80, 490, 110);
	solidrectangle(550, 80, 660, 110);
	settextstyle(6, 6, 0);
	setbkmode(TRANSPARENT);
	outtextxy(250, 90, _T("简单"));
	outtextxy(420, 90, _T("中等"));
	outtextxy(590, 90, _T("高等"));

	line(180, 50, 180, 550);
	line(700, 50, 700, 550);
	line(180, 50, 700, 50);
	line(180, 550, 700, 550);

	return 0;
}

int Elem()
{

	setfillcolor(LIGHTGRAY);
	solidrectangle(260, 80, 340, 110);
	solidrectangle(380, 80, 470, 110);
	solidrectangle(510, 80, 600, 110);
	settextstyle(5, 5, 0);
	setbkmode(TRANSPARENT);
	outtextxy(300, 90, _T("简单"));
	outtextxy(410, 90, _T("中等"));
	outtextxy(530, 90, _T("高等"));

	line(240, 50, 240, 460);
	line(640, 50, 640, 460);
	line(240, 50, 640, 50);
	line(240, 460, 640, 460);
	
	return 0;
}

int main()
{
		initgraph(880,680, EX_SHOWCONSOLE);//设置一个窗口，440，440    EX_SHOWCONSOLE
		setbkcolor(DARKGRAY); // 设置背景颜色为浅灰色
		cleardevice(); // 清空窗口并填充背景颜色

		//HeighLevel();//16*20
		//Medium();//12*16
		Elem();//8*12
		PictureInput();//导入图片
		srand((unsigned)time(NULL));//随机数种子
		setmine(map,COUNT_MINE);//布置雷
		//show(map);//在控制台上打印棋盘

		while (cut)
		{

			Level_option();
			mouse();
			if (level != old_level)
			{
				for (int i = 0; i < COWS; i++)
				{
					for (int j = 0; j < ROMS; j++)
					{
						map[i][j] = 0;
					}
				}
				setmine(map, COUNT_MINE);
				old_level = level;
			}
			show(map);
			gamedraw();//棋盘界面的绘制
		}
		if (cut == 0)
			MessageBox(NULL, "you win", "游戏结束", MB_OK);
		closegraph();
	return 0;
}