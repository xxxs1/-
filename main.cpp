#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include<windows.h>
#pragma comment(lib,"winmm.lib")
#define ROW 10  //行
#define COL 10 //列
#define NUM 10//雷的个数
#define SIZE 50//图片的大小

int count = 0;//ROW*COL-NUM=count

int map[ROW+2][COL+2];
IMAGE	img[12]; //img数组储存12张图片


/*******游戏初始化函数*******/
void GameInit()
{ //随机数的种子
	srand((unsigned int)time(NULL));
	//数组的赋初值0
	for(int i=0; i<ROW+2;i++)
	{
		for (int j = 0; j < COL+2; j++)
		{
			map[i][j];
		}
	}
	//布雷 -1表示雷 NUM个雷
	int n = 0;
	while (n < NUM)
	{//随机得到行和列
		int r = rand() % ROW +1;//1-ROW
		int c = rand() % COL +1;//1-COL
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			n++;
		}
	}
	//根据雷的分布填充其他不为雷的数据
	for (int i = 0; i <= ROW; i++)
	{
		for (int j = 0; j <=COL; j++)
		{//遍历二维数组游戏区
			if (map[i][j] != -1)//找不到为雷的元素
			{    //遍历九宫格
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (n = j - 1; n <= j + 1; n++)
					{
						if(map[m][n] == -1)//找到一个雷
						{
							map[i][j]++;
						}
					}
				}
			}
		}
	}//简单的加密
	for (int i = 1; i < ROW + 1; i++) 
	{
		for (int j = 1; j < COL + 1; j++) 
		{
			map[i][j] += 20;
		}
	}
}
/*******绘制函数打印二维数组中的所有元素******/
void GameDraw()
{    //打印游戏区1-ROW   1-COL
	for (int i = 1;i<=ROW;i++)
	{
		for (int j = 1; j <=COL; j++)
		{
			printf("%2d ", map[i][j]);
			if (map[i][j] == -1)
			{
				putimage((j- 1) * SIZE, (i- 1) * SIZE, &img[9]);//雷
			}
			else if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[map[i][j]]);//数字
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[10]);//空白图片
			}
			else if (map[i][j] > 30)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[11]);//标记图片
			}
		}
		printf("\n");
	}
}
void Openzero(int r,int c)
{//先打开这个0
	map[r][c]-=20;
	count++;

	//注意，辅助区都是零。 
	for (int m = r - 1; m <= r + 1; m++) {
		for (int n = c - 1; n <= c + 1; n++) {      //1.0   9宫格
			if (m>= 1 && m<=ROW && n>= 1 && n<=COL){//2.0   游戏区
				if (map[m][n] >= 19 && map[m][n] <= 28) {//3.0  空白
					if (map[m][n]!= 20) 
					{
						map[m][n] -= 20;
						count++;
					}
					else
					{
						Openzero(m, n);
					}
				}
			}
		}
	}
}
int PlayGame()
{
	//定义一个鼠标消息
	MOUSEMSG msg = {0};
	int r, c;
	while (1)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:   //翻开扫雷  空白图片  19-28
			r = msg.y/ SIZE + 1;
			c = msg.x / SIZE + 1;

			if (map[r][c] >= 19 && map[r][c] <= 28)//空白
			{
				if (map[r][c] == 20)
				{
					Openzero(r, c);


				}//点到的是零
				else
				{
				map[r][c] -= 20;    //-1-8    
				count++;
				
				}
			}
			return map[r][c];//-1-8
			break;
		case WM_RBUTTONDOWN://标记一个空白图片 取消一个标记图片
			r = msg.y / SIZE + 1;
			c = msg.x/ SIZE + 1;
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] += 50;     //>30
			}
			else if (map[r][c] > 30)
			{
				map[r][c] -= 50;
			}
			return map[r][c];
			break;
		}
	}
}
int main()
{//打开一个图形窗口
	HWND hwnd = initgraph(ROW * SIZE, COL * SIZE, SHOWCONSOLE);

	mciSendString(L"open music.mp3 alias music", 0, 0, 0);
	mciSendString(L"play music", 0, 0, 0);
	loadimage(&img[0],L"0.jpg", SIZE, SIZE);
	loadimage(&img[1],L"1.jpg", SIZE, SIZE);
	loadimage(&img[2],L"2.jpg", SIZE, SIZE);
	loadimage(&img[3],L"3.jpg", SIZE, SIZE);
	loadimage(&img[4],L"4.jpg", SIZE, SIZE);
	loadimage(&img[5],L"5.jpg", SIZE, SIZE);
	loadimage(&img[6],L"6.jpg", SIZE, SIZE);
	loadimage(&img[7],L"7.jpg", SIZE, SIZE);
	loadimage(&img[8],L"8.jpg", SIZE, SIZE);
	loadimage(&img[9], L"9.jpg", SIZE, SIZE);//；雷
	loadimage(&img[10], L"10.jpg", SIZE, SIZE);//空白
	loadimage(&img[11], L"11.jpg", SIZE, SIZE);//标记
	/*********************************************
	元素           图片
	0-8            数字             +20       20-28
	-1              img[9]          +20       19
	19-28           img[10]
	 >30            img[11]
	 ************************************************/
	GameInit();
	
	while (1) {
		GameDraw(); 
		

	if (PlayGame() == -1)
	{
		GameDraw();
		MessageBox(hwnd, L"false!!!!!",L"", MB_OK);
		break;
	}
	if (ROW * COL - NUM == count)
	{
		GameDraw();
		MessageBox(hwnd, L"YOU WIN!!!",L"", MB_OK);
		break;
	}
	}
	closegraph();
	return 0;
}
/*********************************
根据雷的分布区填充其他不为雷的数据
1.遍历九宫格，
2.边上数据遍历的时候，越界
3.辅助区  游戏区
**********************************/