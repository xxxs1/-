#pragma once

#define COWS 16//��������
#define ROMS 20//���̵�����
#define COUNT_MINE 9//�׵�����

//������
void setmine( int map[COWS][ROMS],int count_mine);

// ��Ϸ�Ľ���
void gameover(int cow, int rom);

//����ͼƬ
void PictureInput();
//���̽���Ļ���
void gamedraw();
//�ڿ���̨�ϴ�ӡ������
void show(int map[COWS][ROMS]);

//�������
void open(int cow, int rom);

//��ȡ�����Ϣ�����Ӧ�Ĺ���
void mouse();

int  HeighLevel();
int Medium();
int Elem();