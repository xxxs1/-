#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include<windows.h>
#pragma comment(lib,"winmm.lib")
#define ROW 10  //��
#define COL 10 //��
#define NUM 10//�׵ĸ���
#define SIZE 50//ͼƬ�Ĵ�С

int count = 0;//ROW*COL-NUM=count

int map[ROW+2][COL+2];
IMAGE	img[12]; //img���鴢��12��ͼƬ


/*******��Ϸ��ʼ������*******/
void GameInit()
{ //�����������
	srand((unsigned int)time(NULL));
	//����ĸ���ֵ0
	for(int i=0; i<ROW+2;i++)
	{
		for (int j = 0; j < COL+2; j++)
		{
			map[i][j];
		}
	}
	//���� -1��ʾ�� NUM����
	int n = 0;
	while (n < NUM)
	{//����õ��к���
		int r = rand() % ROW +1;//1-ROW
		int c = rand() % COL +1;//1-COL
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			n++;
		}
	}
	//�����׵ķֲ����������Ϊ�׵�����
	for (int i = 0; i <= ROW; i++)
	{
		for (int j = 0; j <=COL; j++)
		{//������ά������Ϸ��
			if (map[i][j] != -1)//�Ҳ���Ϊ�׵�Ԫ��
			{    //�����Ź���
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (n = j - 1; n <= j + 1; n++)
					{
						if(map[m][n] == -1)//�ҵ�һ����
						{
							map[i][j]++;
						}
					}
				}
			}
		}
	}//�򵥵ļ���
	for (int i = 1; i < ROW + 1; i++) 
	{
		for (int j = 1; j < COL + 1; j++) 
		{
			map[i][j] += 20;
		}
	}
}
/*******���ƺ�����ӡ��ά�����е�����Ԫ��******/
void GameDraw()
{    //��ӡ��Ϸ��1-ROW   1-COL
	for (int i = 1;i<=ROW;i++)
	{
		for (int j = 1; j <=COL; j++)
		{
			printf("%2d ", map[i][j]);
			if (map[i][j] == -1)
			{
				putimage((j- 1) * SIZE, (i- 1) * SIZE, &img[9]);//��
			}
			else if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[map[i][j]]);//����
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[10]);//�հ�ͼƬ
			}
			else if (map[i][j] > 30)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[11]);//���ͼƬ
			}
		}
		printf("\n");
	}
}
void Openzero(int r,int c)
{//�ȴ����0
	map[r][c]-=20;
	count++;

	//ע�⣬�����������㡣 
	for (int m = r - 1; m <= r + 1; m++) {
		for (int n = c - 1; n <= c + 1; n++) {      //1.0   9����
			if (m>= 1 && m<=ROW && n>= 1 && n<=COL){//2.0   ��Ϸ��
				if (map[m][n] >= 19 && map[m][n] <= 28) {//3.0  �հ�
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
	//����һ�������Ϣ
	MOUSEMSG msg = {0};
	int r, c;
	while (1)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:   //����ɨ��  �հ�ͼƬ  19-28
			r = msg.y/ SIZE + 1;
			c = msg.x / SIZE + 1;

			if (map[r][c] >= 19 && map[r][c] <= 28)//�հ�
			{
				if (map[r][c] == 20)
				{
					Openzero(r, c);


				}//�㵽������
				else
				{
				map[r][c] -= 20;    //-1-8    
				count++;
				
				}
			}
			return map[r][c];//-1-8
			break;
		case WM_RBUTTONDOWN://���һ���հ�ͼƬ ȡ��һ�����ͼƬ
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
{//��һ��ͼ�δ���
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
	loadimage(&img[9], L"9.jpg", SIZE, SIZE);//����
	loadimage(&img[10], L"10.jpg", SIZE, SIZE);//�հ�
	loadimage(&img[11], L"11.jpg", SIZE, SIZE);//���
	/*********************************************
	Ԫ��           ͼƬ
	0-8            ����             +20       20-28
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
�����׵ķֲ������������Ϊ�׵�����
1.�����Ź���
2.�������ݱ�����ʱ��Խ��
3.������  ��Ϸ��
**********************************/