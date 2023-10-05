#include<stdio.h>
#include"shaolei.h"
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<time.h>
#include<Windows.h>

IMAGE img[12];//储存图片

// 初始化
int map[COWS][ROMS] = { 0 };//初始化棋盘
int cut = COWS * ROMS - COUNT_MINE;//判断棋盘上还有几个雷

//布置雷
void setmine(int map[COWS][ROMS], int count_mine)
{
	int i, j, a, b;
	int count = count_mine;//雷的数量
	while (count)
	{
		int x, y;
		x = rand() % 10;
		y = rand() % 10;
		if (map[x][y] == 0)
		{
			map[x][y] = -1;
			count--;
		}
	}
	for (i = 0; i < COWS; i++)
	{
		for (j = 0; j < ROMS; j++)
		{
			if (map[i][j] == -1)
			{
				for (a = i - 1; a <= i + 1; a++)
					for (b = j - 1; b <= j + 1; b++)
					{
						if ((a >= 0 && a <= COWS && b >= 0 && b <= ROMS) && map[a][b] != -1)
							map[a][b]++;
					}
			}
		}
	}
	//数据的加密
	for (i = 0; i < COWS; i++)
	{
		for (j = 0; j < ROMS; j++)
		{
			map[i][j] += 20;
		}
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
		loadimage(&img[i], str, 40, 40);
	}


}
//棋盘界面的绘制
void gamedraw() 
{
	int i, j;
	for (i = 0; i < COWS; i++)
	{
		for (j = 0; j < ROMS; j++)
		{
			if (map[i][j] >= 0 && map[i][j] <= 8)
				putimage(j * 40, i * 40, &img[map[i][j]]);
			else if (map[i][j] == -1)
			{
				putimage(j * 40, i * 40, &img[9]);
			}
			else if (map[i][j] > 8 && map[i][j] <= 28)
				putimage(j * 40, i * 40, &img[10]);
			else
				putimage(j * 40, i * 40, &img[11]);
		}
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
	MOUSEMSG msg = GetMouseMsg();//get鼠标信息
	int cow = msg.y / 40;
	int rom = msg.x / 40;
	if (msg.uMsg == WM_LBUTTONDOWN && map[cow][rom] >= 19)//鼠标左键落下
	{
		map[cow][rom] -= 20;
		if (map[cow][rom] == -1)
		{
			gameover(cow, rom);
		}
		if (map[cow][rom] >= 0 && map[cow][rom] <= 8)
		{
			cut--;
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
void gameover (int cow, int rom)
{
	putimage(rom * 40, cow * 40, &img[9]);
	MessageBox(NULL, "game over", "游戏结束", MB_OK);
	closegraph();
	system("Dos");
	return;
}

int main()
{
	initgraph(440, 440, 0);//设置一个窗口
	srand((unsigned)time(NULL));//随机数种子
	setmine(map, COUNT_MINE);//布置雷
	PictureInput();//导入图片
	show(map);//在控制台上打印棋盘

	while (cut)
	{
		gamedraw();//棋盘界面的绘制
		mouse();
	}
	if (cut == 0)
		MessageBox(NULL, "you win", "游戏结束", MB_OK);
	closegraph();



	return 0;
}