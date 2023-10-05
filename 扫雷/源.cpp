#include<stdio.h>
#include"shaolei.h"
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<time.h>
#include<Windows.h>

IMAGE img[12];//����ͼƬ

// ��ʼ��
int map[COWS][ROMS] = { 0 };//��ʼ������
int cut = COWS * ROMS - COUNT_MINE;//�ж������ϻ��м�����

//������
void setmine(int map[COWS][ROMS], int count_mine)
{
	int i, j, a, b;
	int count = count_mine;//�׵�����
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
	//���ݵļ���
	for (i = 0; i < COWS; i++)
	{
		for (j = 0; j < ROMS; j++)
		{
			map[i][j] += 20;
		}
	}
	return;
}


//����ͼƬ
void PictureInput()
{
	int i;
	char str[50];//��һ������������ͼƬ��ַ
	for (i = 0; i <= 11; i++)
	{
		sprintf_s(str, "./image/%d.jpg", i);
		loadimage(&img[i], str, 40, 40);
	}


}
//���̽���Ļ���
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

//�ڿ���̨�ϴ�ӡ������
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

void open(int cow, int rom)//�������
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
					open(i, j);//�ݹ���ʱ����Χû���׵ĵط�ը��
				}

			}

		}
	}
}
//��ȡ�����Ϣ
void mouse()
{
	MOUSEMSG msg = GetMouseMsg();//get�����Ϣ
	int cow = msg.y / 40;
	int rom = msg.x / 40;
	if (msg.uMsg == WM_LBUTTONDOWN && map[cow][rom] >= 19)//����������
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
	if (msg.uMsg == WM_RBUTTONDOWN)//����Ҽ�����
		if (map[cow][rom] >= 19 && map[cow][rom] <= 28)
			map[cow][rom] += 20;
		else if (map[cow][rom] > 28)
			map[cow][rom] -= 20;
	show(map);

}

// ��Ϸ�Ľ���
void gameover (int cow, int rom)
{
	putimage(rom * 40, cow * 40, &img[9]);
	MessageBox(NULL, "game over", "��Ϸ����", MB_OK);
	closegraph();
	system("Dos");
	return;
}

int main()
{
	initgraph(440, 440, 0);//����һ������
	srand((unsigned)time(NULL));//���������
	setmine(map, COUNT_MINE);//������
	PictureInput();//����ͼƬ
	show(map);//�ڿ���̨�ϴ�ӡ����

	while (cut)
	{
		gamedraw();//���̽���Ļ���
		mouse();
	}
	if (cut == 0)
		MessageBox(NULL, "you win", "��Ϸ����", MB_OK);
	closegraph();



	return 0;
}