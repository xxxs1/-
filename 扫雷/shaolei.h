
#define COWS 11//��������
#define ROMS 11//���̵�����
#define COUNT_MINE 9//�׵�����

//������
void setmine(int map[COWS][ROMS], int count_mine);

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