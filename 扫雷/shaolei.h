#pragma once

#define COWS 16//棋盘行数
#define ROMS 20//棋盘的列数
#define COUNT_MINE 9//雷的数量

//布置雷
void setmine( int map[COWS][ROMS],int count_mine);

// 游戏的结束
void gameover(int cow, int rom);

//导入图片
void PictureInput();
//棋盘界面的绘制
void gamedraw();
//在控制台上打印出棋盘
void show(int map[COWS][ROMS]);

//左键解密
void open(int cow, int rom);

//获取鼠标信息和其对应的功能
void mouse();

int  HeighLevel();
int Medium();
int Elem();