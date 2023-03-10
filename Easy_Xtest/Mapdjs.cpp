#include<graphics.h>//����ͼ���ͷ�ļ�,����������C++
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include <tchar.h>
using namespace std;
#pragma comment(lib,"winmm.lib")//���ؾ�̬��
#define MAXVEX 18
#define INFINITY 10000
#define BUFFERSIZE 1024

typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

typedef struct {
	int vex[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes;
} MGraph;

void CreateMGraph(MGraph* G);	//�����ͳ�ʼ��ͼ
void ShortPath_Floyd(MGraph G, Patharc P, ShortPathTable D);	//Floyd�㷨
void PrintShortPath(MGraph G, Patharc P, ShortPathTable D, int i, int j);		//��ӡ
void test();

int button_judge(int x, int y, int(*r)[4]);	//��������Ƿ���17��������
void out(int a[], int num, int num1);		//������·����Ϣ
void huizhi();		//����ͼ��
void mes();			//������
void getmess(int a[]);		//���ƿ�ʼ������·�������
void write(int a);	//д�����յ�

int flag1 = 0, x = 0;//flag1��¼�Ƿ��������������յ㣬x��¼�˵������
int i, j;	//��¼�����յ��������Ϣ
int flag2 = 0;

void Floyd();

//Dijksra
int flag = 0;
void tangle();	//ͼ����Ϣ����
int begin();	//��ʼ������ɫ
void MYHWND();	//��ʾ��ʾ��
void func();	//��������
void time();	//������ʱ
void control();	//˵����������
void Dijksra();

void TU();
void BGM(int i);	//	�����Ͱ�ť����
int main()
{
	TU();
	return 0;
}

void TU()
{
	initgraph(1000, 600, NOMINIMIZE);
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "Control");		// ʹ�� Windows API �޸Ĵ�������
	IMAGE img;//����һ������ͼ��ı���
	loadimage(&img, "./mm.png", 1000, 600);//����ͼ��
	putimage(0, 0, &img);//�ڴ����д�ӡͼ��
	settextstyle(20, 0, "����");//����������ʽ���߶ȣ���ȣ����壩
	setbkmode(TRANSPARENT);	//�����屳����ɫ��Ϊ͸��
	settextcolor(BLUE);	//�����������ɫ/
	//setfillcolor(RGB(0, 128, 192));
	//solidrectangle(470, 270, 550, 310);
	outtextxy(480, 280, "Floyd");
	//solidrectangle(470, 320, 550, 360);
	outtextxy(480, 330, "Dijksra");
	outtextxy(480, 380, "Exit");

	BGM(1);	//��������

	while (1)
	{
		MOUSEMSG msg;//���ָ��
		msg = GetMouseMsg();//��ȡһ�������Ϣ
		switch (msg.uMsg)//ɸѡ�����Ϣ����
		{
		case WM_LBUTTONDOWN:
			if (msg.x >= 470 && msg.x <= 550 && msg.y >= 270 && msg.y <= 310)
			{
				
				BGM(2);
				Floyd();
			}
			if (msg.x >= 470 && msg.x <= 550 && msg.y >= 320 && msg.y <= 360)
			{
				BGM(2);
				Dijksra();
			}
			if (msg.x >= 470 && msg.x <= 550 && msg.y >= 370 && msg.y <= 410)
			{
				BGM(2);
				exit(1);
			}
			break;
		case WM_MOUSEMOVE://�ƶ���Ϣ
			if (msg.x >= 470 && msg.x <= 550 && msg.y >= 270 && msg.y <= 310)
			{
				
				settextcolor(WHITE);	//�����������ɫ
				outtextxy(480, 280, "Floyd");
			}
			else
			{
				settextcolor(BLUE);	//�����������ɫ
				outtextxy(480, 280, "Floyd");
				
			}
			if (msg.x >= 470 && msg.x <= 550 && msg.y >= 320 && msg.y <= 360)
			{
				
				settextcolor(WHITE);	//�����������ɫ
				outtextxy(480, 330, "Dijksra");
			}
			else
			{
				settextcolor(BLUE);	//�����������ɫ
				outtextxy(480, 330, "Dijksra");
			}
			if (msg.x >= 470 && msg.x <= 550 && msg.y >= 370 && msg.y <= 410)
			{
				
				settextcolor(WHITE);	//�����������ɫ
				outtextxy(480, 380, "Exit");
			}
			else
			{
				settextcolor(BLUE);	//�����������ɫ
				outtextxy(480, 380, "Exit");
			}
			break;
		}
	}
	cleardevice();
	getchar();
	//�رմ��ڣ�closegraph();
	closegraph();
}
void BGM(int i)
{
	if(i==1)
	{
		mciSendString("close  bkmusic ", NULL, 0, NULL);//�ر�֮ǰ���ŵı�����
		mciSendString("open .\\su.mp3 alias bkmusic", NULL, 0, NULL);
		//mciSendString("play bkmusic ", NULL, 0, NULL);//���������ļ�
		mciSendString("play bkmusic repeat", NULL, 0, NULL);
	}
	if(i==0)
		mciSendString("close  bkmusic ", NULL, 0, NULL);//�ر�֮ǰ���ŵı�����
	if (i == 2)
	{
		mciSendString("close  bkmusic ", NULL, 0, NULL);//�ر�֮ǰ���ŵı�����
		mciSendString("open .\\ji.mp3 alias bkmusic", NULL, 0, NULL);
		mciSendString("play bkmusic ", NULL, 0, NULL);//���������ļ�
	}
	if (i == 3 && flag2 == 0)
	{
		mciSendString("close  bkmusic ", NULL, 0, NULL);//�ر�֮ǰ���ŵı�����
		mciSendString("open .\\move.mp3 alias bkmusic", NULL, 0, NULL);
		mciSendString("play bkmusic ", NULL, 0, NULL);//���������ļ�
	}
}
void huizhi()
{
	setfillcolor(RGB(0, 255, 255));
	setrop2(R2_COPYPEN);
	settextcolor(BLACK);
	solidrectangle(750, 80, 850, 120);
	outtextxy(760, 90, "�������");
	solidrectangle(880, 80, 980, 120);
	outtextxy(890, 90, "�����յ�");
	outtextxy(760, 140, "��㣺");
	outtextxy(760, 180, "�յ㣺");
	solidrectangle(750, 220, 850, 260);
	outtextxy(760, 230, "�����·");
	solidrectangle(750, 280, 850, 320);
	outtextxy(780, 290, "����");
	solidrectangle(750, 340, 850, 380);
	outtextxy(780, 350, "�˳�");

	setfillcolor(BLACK);		//���þ��������ɫ
	settextcolor(WHITE);
	solidrectangle(300, 260, 360, 300);
	outtextxy(310, 270, "�人");
	solidrectangle(290, 170, 350, 210);
	outtextxy(300, 180, "֣��");
	solidrectangle(430, 170, 490, 210);
	outtextxy(440, 180, "����");
	solidrectangle(470, 260, 530, 300);
	outtextxy(480, 270, "�Ϻ�");
	solidrectangle(260, 340, 320, 380);
	outtextxy(270, 350, "����");
	solidrectangle(420, 360, 480, 400);
	outtextxy(430, 370, "�ϲ�");
	solidrectangle(520, 450, 580, 490);
	outtextxy(530, 460, "����");
	solidrectangle(280, 460, 340, 500);
	outtextxy(290, 470, "����");
	solidrectangle(380, 520, 440, 560);
	outtextxy(390, 530, "����");
	solidrectangle(160, 420, 220, 460);
	outtextxy(170, 430, "����");
	solidrectangle(100, 360, 160, 400);
	outtextxy(110, 370, "����");
	solidrectangle(60, 250, 120, 290);
	outtextxy(70, 260, "�ɶ�");
	solidrectangle(120, 150, 180, 190);
	outtextxy(130, 160, "����");
	solidrectangle(80, 80, 140, 120);
	outtextxy(90, 90, "����");
	solidrectangle(340, 40, 400, 80);
	outtextxy(350, 50, "����");
	solidrectangle(210, 50, 270, 90);
	outtextxy(220, 60, "����");
	solidrectangle(460, 80, 520, 120);
	outtextxy(470, 90, "���");

	//����
	setlinecolor(BLACK);
	settextcolor(BLACK);	 //�����������ɫ
	line(330, 260, 320, 210);//�人-֣��
	outtextxy(340, 225, "534");
	line(350, 190, 430, 190);//֣��-����
	outtextxy(390, 170, "349");
	line(460, 210, 500, 260);//����-�Ϻ�
	outtextxy(490, 220, "651");
	line(500, 300, 450, 360);//�Ϻ�-�ϲ�
	outtextxy(480, 320, "825");
	line(450, 400, 550, 450);//�ϲ�-����
	outtextxy(510, 410, "622");
	line(330, 300, 290, 340);//�人-����
	outtextxy(270, 310, "409");
	line(320, 360, 420, 380);//����-�ϲ�
	outtextxy(360, 350, "367");
	line(220, 430, 290, 380);//����-����
	outtextxy(240, 410, "672");
	line(290, 380, 310, 460);//����-����
	outtextxy(310, 420, "675");
	line(310, 500, 410, 520);//����-����
	outtextxy(360, 490, "140");
	line(260, 360, 160, 380);//����-����
	outtextxy(190, 350, "902");
	line(190, 420, 130, 400);//����-����
	outtextxy(170, 390, "607");
	line(90, 290, 130, 360);//�ɶ�-����
	outtextxy(120, 300, "967");
	line(90, 250, 150, 190);//�ɶ�-����
	outtextxy(140, 220, "842");
	line(180, 170, 290, 190);//����-֣��
	outtextxy(230, 160, "511");
	line(150, 150, 110, 120);//����-����
	outtextxy(140, 120, "676");
	line(320, 170, 370, 80);//֣��-����
	outtextxy(350, 120, "695");
	line(270, 70, 340, 60);//���ͺ���-����
	outtextxy(290, 45, "668");
	line(140, 100, 210, 70);//����-����
	outtextxy(150, 60, "1145");
	line(400, 60, 460, 100);//����-���
	outtextxy(430, 60, "137");
	line(490, 120, 460, 170);//���-����
	outtextxy(490, 140, "674");
}

void mes()
{
	int r[22][4] = { {300, 260, 360, 300},{290, 170, 350, 210},{430, 170, 490, 210},{470, 260, 530, 300},{260, 340, 320, 380},
		{420, 360, 480, 400},{520, 450, 580, 490},{280, 460, 340, 500},{380, 520, 440, 560},{160, 420, 220, 460},{100, 360, 160, 400},
		{60, 250, 120, 290},{120, 150, 180, 190},{80, 80, 140, 120},{340, 40, 400, 80},{210, 50, 270, 90},{460, 80, 520, 120} };
	int event = 0;
	while (true)
	{
		MOUSEMSG msg;//���ָ��
		settextcolor(WHITE);
		msg = GetMouseMsg();//��ȡһ�������Ϣ
		switch (msg.uMsg)//ɸѡ�����Ϣ����
		{
		case WM_MOUSEMOVE://�ƶ���Ϣ
			setrop2(R2_XORPEN);
			setfillcolor(RGB(255, 128, 64));
			if (button_judge(msg.x, msg.y, r) != 0)
			{
				
				if (event != button_judge(msg.x, msg.y, r))
				{
					BGM(3);
					event = button_judge(msg.x, msg.y, r);//��¼��һ�δ����İ�ť
					solidrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//�����Σ�X1,Y1,X2,Y2��
				}
			}
			else
			{
				if (event != 0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				{
					solidrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN://������
			if (msg.x >= 750 && msg.x <= 850 && msg.y >= 340 && msg.y <= 380)
			{
				BGM(2);
				BGM(0);
				setfillcolor(WHITE);
				settextcolor(BLACK);
				solidrectangle(750, 340, 850, 380);
				outtextxy(780, 350, "�˳�");
				TU();
				//exit(1);
			}
			if (msg.x >= 750 && msg.x <= 850 && msg.y >= 80 && msg.y <= 120)
			{
				flag2 = 1;
				BGM(2);
				setrop2(R2_WHITE);
				settextcolor(BLACK);
				solidrectangle(750, 80, 850, 120);
				outtextxy(760, 90, "�������");
				flag1 = 1;
			}
			if (msg.x >= 880 && msg.x <= 980 && msg.y >= 80 && msg.y <= 120)
			{
				if (flag1 != 1 && flag1 != 2)
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "�����������", "���棡", MB_ICONEXCLAMATION);//��Ϣ�򵯳����ú���
				}
				else if (flag1 == 1) {
					BGM(2);
					setrop2(R2_WHITE);
					settextcolor(BLACK);
					solidrectangle(880, 80, 980, 120);
					outtextxy(890, 90, "�����յ�");
					flag1 = 2;
				}
			}
			if (msg.x >= 750 && msg.x <= 850 && msg.y >= 220 && msg.y <= 260)
			{
				if (flag1 == 0)
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "��ѡ�������յ㣡", "���棡", MB_ICONEXCLAMATION);//��Ϣ�򵯳����ú���
					break;
				}
				BGM(2);
				setrop2(R2_WHITE);
				settextcolor(BLACK);
				solidrectangle(750, 220, 850, 260);
				outtextxy(760, 230, "�����·");
				test();
			}
			if (flag1 == 0)
			{
				continue;
			}
			if (msg.x >= 750 && msg.x <= 850 && msg.y >= 280 && msg.y <= 320)
			{
				BGM(2);
				setrop2(R2_WHITE);
				settextcolor(BLACK);
				solidrectangle(750, 280, 850, 320);
				outtextxy(780, 290, "����");
				setrop2(R2_COPYPEN);
				setfillcolor(BROWN);
				solidrectangle(620, 420, 1000, 500);
				clearrectangle(620, 500, 760, 600);
				clearrectangle(810, 140, 890, 160);
				clearrectangle(810, 160, 890, 220);
				flag1 = flag2 = 0;
				huizhi();
			}
			if (msg.x >= 300 && msg.x <= 360 && msg.y >= 260 && msg.y <= 300)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(310, 270, "�人");
				write(5);
			}
			if (msg.x >= 290 && msg.x <= 350 && msg.y >= 170 && msg.y <= 210)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(300, 180, "֣��");
				write(4);
			}
			if (msg.x >= 430 && msg.x <= 490 && msg.y >= 170 && msg.y <= 210)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(440, 180, "����");
				write(9);

			}
			if (msg.x >= 470 && msg.x <= 530 && msg.y >= 260 && msg.y <= 300)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(480, 270, "�Ϻ�");
				write(10);

			}
			if (msg.x >= 260 && msg.x <= 320 && msg.y >= 340 && msg.y <= 380)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(270, 350, "����");
				write(6);

			}
			if (msg.x >= 420 && msg.x <= 480 && msg.y >= 360 && msg.y <= 400)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(430, 370, "�ϲ�");
				write(11);

			}
			if (msg.x >= 520 && msg.x <= 580 && msg.y >= 450 && msg.y <= 490)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(530, 460, "����");
				write(12);

			}
			if (msg.x >= 280 && msg.x <= 340 && msg.y >= 460 && msg.y <= 500)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(290, 470, "����");
				write(7);

			}
			if (msg.x >= 380 && msg.x <= 440 && msg.y >= 520 && msg.y <= 560)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(390, 530, "����");
				write(8);

			}
			if (msg.x >= 160 && msg.x <= 220 && msg.y >= 420 && msg.y <= 460)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(170, 430, "����");
				write(3);

			}
			if (msg.x >= 100 && msg.x <= 160 && msg.y >= 360 && msg.y <= 400)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(110, 370, "����");
				write(2);

			}
			if (msg.x >= 60 && msg.x <= 120 && msg.y >= 250 && msg.y <= 290)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(70, 260, "�ɶ�");
				write(1);

			}
			if (msg.x >= 120 && msg.x <= 180 && msg.y >= 150 && msg.y <= 190)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(130, 160, "����");
				write(0);

			}
			if (msg.x >= 80 && msg.x <= 140 && msg.y >= 80 && msg.y <= 120)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(90, 90, "����");
				write(13);

			}
			if (msg.x >= 340 && msg.x <= 400 && msg.y >= 40 && msg.y <= 80)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(350, 50, "����");
				write(15);

			}
			if (msg.x >= 210 && msg.x <= 270 && msg.y >= 50 && msg.y <= 90)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(220, 60, "����");
				write(14);

			}
			if (msg.x >= 460 && msg.x <= 520 && msg.y >= 80 && msg.y <= 120)
			{
				BGM(2);
				settextcolor(BROWN);
				outtextxy(470, 90, "���");
				write(16);

			}
			break;
		default:
			break;
		}
	}
}

void getmess(int a[])
{
	int s = 0;
	settextcolor(RED);
	setlinecolor(RED);
	setrop2(R2_COPYPEN);
	while (a[s] != -2)
	{
		if (a[s] == 0 && a[s + 1] == 1 || a[s] == 1 && a[s + 1] == 0)
		{
			line(90, 250, 150, 190);//�ɶ�-����
			outtextxy(70, 260, "�ɶ�");
			outtextxy(130, 160, "����");
		}
		if (a[s] == 0 && a[s + 1] == 13 || a[s] == 13 && a[s + 1] == 0)
		{
			line(150, 150, 110, 120);//����-����
			outtextxy(130, 160, "����");
			outtextxy(90, 90, "����");
		}
		if (a[s] == 0 && a[s + 1] == 4 || a[s] == 4 && a[s + 1] == 0)
		{
			line(180, 170, 290, 190);//����-֣��
			outtextxy(130, 160, "����");
			outtextxy(300, 180, "֣��");
		}
		if (a[s] == 1 && a[s + 1] == 2 || a[s] == 2 && a[s + 1] == 1)
		{
			line(90, 290, 130, 360);//�ɶ�-����
			outtextxy(70, 260, "�ɶ�");
			outtextxy(110, 370, "����");
		}
		if (a[s] == 2 && a[s + 1] == 3 || a[s] == 3 && a[s + 1] == 2)
		{
			line(190, 420, 130, 400);//����-����
			outtextxy(110, 370, "����");
			outtextxy(170, 430, "����");
		}
		if (a[s] == 2 && a[s + 1] == 6 || a[s] == 6 && a[s + 1] == 2)
		{
			line(260, 360, 160, 380);//����-����
			outtextxy(270, 350, "����");
			outtextxy(110, 370, "����");
		}
		if (a[s] == 3 && a[s + 1] == 6 || a[s] == 6 && a[s + 1] == 3)
		{
			line(220, 430, 290, 380);//����-����
			outtextxy(270, 350, "����");
			outtextxy(170, 430, "����");
		}
		if (a[s] == 4 && a[s + 1] == 9 || a[s] == 9 && a[s + 1] == 4)
		{
			line(350, 190, 430, 190);//֣��-����
			outtextxy(300, 180, "֣��");
			outtextxy(440, 180, "����");
		}
		if (a[s] == 4 && a[s + 1] == 5 || a[s] == 5 && a[s + 1] == 4)
		{
			line(330, 260, 320, 210);//�人-֣��
			outtextxy(310, 270, "�人");
			outtextxy(300, 180, "֣��");
		}
		if (a[s] == 4 && a[s + 1] == 15 || a[s] == 15 && a[s + 1] == 4)
		{
			line(320, 170, 370, 80);//֣��-����
			outtextxy(300, 180, "֣��");
			outtextxy(350, 50, "����");
		}
		if (a[s] == 5 && a[s + 1] == 6 || a[s] == 6 && a[s + 1] == 5)
		{
			line(330, 300, 290, 340);//�人-����
			outtextxy(310, 270, "�人");
			outtextxy(270, 350, "����");
		}
		if (a[s] == 6 && a[s + 1] == 7 || a[s] == 7 && a[s + 1] == 6)
		{
			line(290, 380, 310, 460);//����-����
			outtextxy(270, 350, "����");
			outtextxy(290, 470, "����");
		}
		if (a[s] == 6 && a[s + 1] == 11 || a[s] == 11 && a[s + 1] == 6)
		{
			line(320, 360, 420, 380);//����-�ϲ�
			outtextxy(270, 350, "����");
			outtextxy(430, 370, "�ϲ�");
		}
		if (a[s] == 7 && a[s + 1] == 8 || a[s] == 8 && a[s + 1] == 7)
		{
			line(310, 500, 410, 520);//����-����
			outtextxy(290, 470, "����");
			outtextxy(390, 530, "����");
		}
		if (a[s] == 9 && a[s + 1] == 10 || a[s] == 10 && a[s + 1] == 9)
		{
			line(460, 210, 500, 260);//����-�Ϻ�
			outtextxy(440, 180, "����");
			outtextxy(480, 270, "�Ϻ�");
		}
		if (a[s] == 9 && a[s + 1] == 16 || a[s] == 16 && a[s + 1] == 9)
		{
			line(490, 120, 460, 170);//���-����
			outtextxy(470, 90, "���");
			outtextxy(440, 180, "����");
		}
		if (a[s] == 10 && a[s + 1] == 11 || a[s] == 11 && a[s + 1] == 10)
		{
			line(500, 300, 450, 360);//�Ϻ�-�ϲ�
			outtextxy(480, 270, "�Ϻ�");
			outtextxy(430, 370, "�ϲ�");
		}
		if (a[s] == 11 && a[s + 1] == 12 || a[s] == 12 && a[s + 1] == 11)
		{
			line(450, 400, 550, 450);//�ϲ�-����
			outtextxy(430, 370, "�ϲ�");
			outtextxy(530, 460, "����");
		}
		if (a[s] == 13 && a[s + 1] == 14 || a[s] == 14 && a[s + 1] == 13)
		{
			line(140, 100, 210, 70);//����-����
			outtextxy(90, 90, "����");
			outtextxy(220, 60, "����");
		}
		if (a[s] == 14 && a[s + 1] == 15 || a[s] == 15 && a[s + 1] == 14)
		{
			line(270, 70, 340, 60);//���ͺ���-����
			outtextxy(220, 60, "����");
			outtextxy(350, 50, "����");
		}
		if (a[s] == 15 && a[s + 1] == 16 || a[s] == 16 && a[s + 1] == 15)
		{
			line(400, 60, 460, 100);//����-���
			outtextxy(350, 50, "����");
			outtextxy(470, 90, "���");
		}
		s++;
	}
}

void write(int a)
{
	settextcolor(BLACK);
	if (flag1 == 1)
	{
		switch (a)
		{
		case 0:
			i = 0;
			outtextxy(810, 140, "����");
			break;
		case 1:
			i = 1;
			outtextxy(810, 140, "�ɶ�");
			break;
		case 2:
			i = 2;
			outtextxy(810, 140, "����");
			break;
		case 3:
			i = 3;
			outtextxy(810, 140, "����");
			break;
		case 4:
			i = 4;
			outtextxy(810, 140, "֣��");
			break;
		case 5:
			i = 5;
			outtextxy(810, 140, "�人");
			break;
		case 6:
			i = 6;
			outtextxy(810, 140, "����");
			break;
		case 7:
			i = 7;
			outtextxy(810, 140, "����");
			break;
		case 8:
			i = 8;
			outtextxy(810, 140, "����");
			break;
		case 9:
			i = 9;
			outtextxy(810, 140, "����");
			break;
		case 10:
			i = 10;
			outtextxy(810, 140, "�Ϻ�");
			break;
		case 11:
			i = 11;
			outtextxy(810, 140, "�ϲ�");
			break;
		case 12:
			i = 12;
			outtextxy(810, 140, "����");
			break;
		case 13:
			i = 13;
			outtextxy(810, 140, "����");
			break;
		case 14:
			i = 14;
			outtextxy(810, 140, "����");
			break;
		case 15:
			i = 15;
			outtextxy(810, 140, "����");
			break;
		case 16:
			i = 16;
			outtextxy(810, 140, "���");
			break;
		}
	}
	else if (flag1 == 2)
	{
		switch (a)
		{
		case 0:
			j = 0;
			outtextxy(810, 180, "����");
			break;
		case 1:
			j = 1;
			outtextxy(810, 180, "�ɶ�");
			break;
		case 2:
			j = 2;
			outtextxy(810, 180, "����");
			break;
		case 3:
			j = 3;
			outtextxy(810, 180, "����");
			break;
		case 4:
			j = 4;
			outtextxy(810, 180, "֣��");
			break;
		case 5:
			j = 5;
			outtextxy(810, 180, "�人");
			break;
		case 6:
			j = 6;
			outtextxy(810, 180, "����");
			break;
		case 7:
			j = 7;
			outtextxy(810, 180, "����");
			break;
		case 8:
			j = 8;
			outtextxy(810, 180, "����");
			break;
		case 9:
			j = 9;
			outtextxy(810, 180, "����");
			break;
		case 10:
			j = 10;
			outtextxy(810, 180, "�Ϻ�");
			break;
		case 11:
			j = 11;
			outtextxy(810, 180, "�ϲ�");
			break;
		case 12:
			j = 12;
			outtextxy(810, 180, "����");
			break;
		case 13:
			j = 13;
			outtextxy(810, 180, "����");
			break;
		case 14:
			j = 14;
			outtextxy(810, 180, "����");
			break;
		case 15:
			j = 15;
			outtextxy(810, 180, "����");
			break;
		case 16:
			j = 16;
			outtextxy(810, 180, "���");
			break;
		}
	}
}

void out(int a[], int num, int num1)
{
	settextcolor(BLACK);
	setfillcolor(BROWN);
	setrop2(R2_COPYPEN);
	solidrectangle(620, 420, 1000, 500);  //����������·��Ϣ���ο�
	int t = 0;
	string s[17] = { "����","�ɶ�","����","����","֣��","�人","����","����","����","����","�Ϻ�","�ϲ�" ,"����","����","���ͺ���" ,"����","���" };
	string s1;
	while (t < num)
	{
		s1 += s[a[t]];
		if (t < num - 1)
			s1 += "->";
		t++;
	}
	const char* s2 = s1.data();
	outtextxy(620, 440, s2);
	outtextxy(620, 500, "·�����ȣ�");
	char num2[10];
	sprintf_s(num2, "%d", num1);
	outtextxy(710, 500, num2);
}

int button_judge(int x, int y, int(*r)[4])
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
	if (x > r[3][0] && x<r[3][2] && y>r[3][1] && y < r[3][3])return 4;
	if (x > r[4][0] && x<r[4][2] && y>r[4][1] && y < r[4][3])return 5;
	if (x > r[5][0] && x<r[5][2] && y>r[5][1] && y < r[5][3])return 6;
	if (x > r[6][0] && x<r[6][2] && y>r[6][1] && y < r[6][3])return 7;
	if (x > r[7][0] && x<r[7][2] && y>r[7][1] && y < r[7][3])return 8;
	if (x > r[8][0] && x<r[8][2] && y>r[8][1] && y < r[8][3])return 9;
	if (x > r[9][0] && x<r[9][2] && y>r[9][1] && y < r[9][3])return 10;
	if (x > r[10][0] && x<r[10][2] && y>r[10][1] && y < r[10][3])return 11;
	if (x > r[11][0] && x<r[11][2] && y>r[11][1] && y < r[11][3])return 12;
	if (x > r[12][0] && x<r[12][2] && y>r[12][1] && y < r[12][3])return 13;
	if (x > r[13][0] && x<r[13][2] && y>r[13][1] && y < r[13][3])return 14;
	if (x > r[14][0] && x<r[14][2] && y>r[14][1] && y < r[14][3])return 15;
	if (x > r[15][0] && x<r[15][2] && y>r[15][1] && y < r[15][3])return 16;
	if (x > r[16][0] && x<r[16][2] && y>r[16][1] && y < r[16][3])return 17;
	return 0;
}

void CreateMGraph(MGraph* G) {
	int i, j, k;

	// ��ʼ��ͼ
	G->numVertexes = 17;
	for (i = 0; i < G->numVertexes; ++i) {
		G->vex[i] = i;
	}
	for (i = 0; i < G->numVertexes; ++i) {
		for (j = 0; j < G->numVertexes; ++j) {
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1] = 842;
	G->arc[0][4] = 511;
	G->arc[0][13] = 676;

	G->arc[1][2] = 967;

	G->arc[2][3] = 607;
	G->arc[2][6] = 902;

	G->arc[3][6] = 672;

	G->arc[4][5] = 534;
	G->arc[4][9] = 349;
	G->arc[4][15] = 695;

	G->arc[5][6] = 409;

	G->arc[6][7] = 675;
	G->arc[6][11] = 367;

	G->arc[7][8] = 140;

	G->arc[9][10] = 651;
	G->arc[9][16] = 674;

	G->arc[10][11] = 825;

	G->arc[11][12] = 622;

	G->arc[13][14] = 1145;

	G->arc[14][15] = 668;

	G->arc[15][16] = 137;

	// ���öԳ�λ��Ԫ��ֵ
	for (i = 0; i < G->numVertexes; ++i) {
		for (j = i; j < G->numVertexes; ++j) {
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

void ShortPath_Floyd(MGraph G, Patharc P, ShortPathTable D) {
	int i, j, k;
	// ����ѭ������ʼ��P, D
	for (i = 0; i < G.numVertexes; ++i) {
		for (j = 0; j < G.numVertexes; ++j) {
			D[i][j] = G.arc[i][j];
			P[i][j] = j;
		}
	}
	// ����ѭ��, Floyd algorithm
	for (k = 0; k < G.numVertexes; ++k) {
		for (i = 0; i < G.numVertexes; ++i) {
			for (j = 0; j < G.numVertexes; ++j) {
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = P[i][k];
				}
			}
		}
	}
}

void PrintShortPath(MGraph G, Patharc P, ShortPathTable D, int i, int j) {
	int k, t = 0;
	int* a = new int[20];
	while (t != 20)
	{
		a[t] = -2;
		t++;
	}
	t = 0;
	a[t++] = i;
	k = P[i][j];
	while (k != j) {
		a[t++] = k;
		k = P[k][j];
	}
	a[t++] = j;
	getmess(a);
	out(a, t, D[i][j]);
}

void test()
{
	MGraph G;
	Patharc P;
	ShortPathTable D;
	CreateMGraph(&G);
	ShortPath_Floyd(G, P, D);
	PrintShortPath(G, P, D, i, j);
}

void Floyd()
{
	initgraph(1000, 600);
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "ͼ�����·-Floyd");		// ʹ�� Windows API �޸Ĵ�������
	setbkcolor(BROWN);		//���ñ�������ɫ
	cleardevice();
	settextcolor(WHITE);	//�����������ɫ
	settextstyle(20, 0, "����");//����������ʽ���߶ȣ���ȣ����壩
	setbkmode(TRANSPARENT);	//�����屳����ɫ��Ϊ͸��

	huizhi();
	mes();

	getchar();
	//�رմ��ڣ�closegraph();
	closegraph();
}


void Dijksra()
{
	initgraph(840, 600);
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "ͼ�����·-Dijskra");		// ʹ�� Windows API �޸Ĵ�������
	setbkcolor(RGB(240, 255, 255));		//���ñ�������ɫ
	cleardevice();
	setlinecolor(RGB(128, 128, 255));
	setrop2(R2_COPYPEN);
	settextcolor(BROWN);	//�����������ɫ
	settextstyle(20, 0, "����");//����������ʽ���߶ȣ���ȣ����壩
	setbkmode(TRANSPARENT);	//�����屳����ɫ��Ϊ͸��
	//����
	outtextxy(580, 40, "ͼ�����·(Dijskra)");	//�������
	setfillcolor(RGB(0, 128, 192));		//���þ��������ɫ
	setrop2(R2_COPYPEN);
	solidrectangle(680, 90, 760, 130);	//���ƾ��Σ���ʼ��
	outtextxy(700, 100, "��ʼ");
	solidrectangle(580, 90, 660, 130);	//���ƾ��Σ�����ʼ�գ�
	outtextxy(580, 100, "����ʼ��");
	solidrectangle(460, 90, 540, 130);	//���ƾ��Σ�����ʼ�գ�
	outtextxy(480, 100, "�˳�");
	//���ƻ���ͼ��
	setfillcolor(RGB(0, 128, 192));	//����Բ�ε������ɫ
	setrop2(R2_COPYPEN);
	solidcircle(40, 250, 20);	//A
	outtextxy(35, 240, "A");
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	solidcircle(130, 340, 20);	//E
	outtextxy(125, 330, "E");
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");
	solidcircle(320, 160, 20);	//C
	outtextxy(315, 150, "C");
	solidcircle(320, 340, 20);	//F
	outtextxy(315, 330, "F");
	solidcircle(440, 250, 20);	//G
	outtextxy(435, 240, "G");
	//����
	setlinecolor(RGB(128, 128, 255));
	setrop2(R2_COPYPEN);
	line(40, 250, 130, 160);	//A-B
	line(40, 250, 130, 340);	//A-E
	line(40, 250, 220, 250);	//A-D
	line(130, 160, 220, 250);	//B-D
	line(130, 340, 220, 250);	//E-D
	line(130, 160, 320, 160);	//B-C
	line(220, 250, 320, 160);	//D-C
	line(220, 250, 320, 340);	//D-F
	line(320, 160, 320, 340);	//C-F
	line(320, 160, 440, 250);	//C-G
	line(320, 340, 440, 250);	//F-G
	line(130, 340, 320, 340);	//E-F
	//дȨֵ
	outtextxy(60, 180, "12");
	outtextxy(70, 300, "6");
	outtextxy(120, 230, "16");
	outtextxy(215, 140, "10");
	outtextxy(180, 195, "7");
	outtextxy(250, 195, "6");
	outtextxy(260, 300, "2");
	outtextxy(300, 240, "11");
	outtextxy(390, 190, "3");
	outtextxy(390, 290, "4");
	outtextxy(225, 320, "8");
	outtextxy(160, 280, "5");

	while (true)
	{
		ExMessage msg = { 0 };
		if (peekmessage(&msg, EM_MOUSE));//��������Ϣ
		{
			switch (msg.message)//ɸѡ�����Ϣ����
			{
			case WM_LBUTTONDOWN://�����Ϣ
				if (msg.x >= 580 && msg.x <= 660 && msg.y >= 90 && msg.y <= 130)
				{
					BGM(3);
					setfillcolor(LIGHTRED);
					solidrectangle(580, 90, 660, 130);
					outtextxy(580, 100, "����ʼ��");
					MYHWND();
					flag = 1;
				}
				if (msg.x >= 680 && msg.x <= 760 && msg.y >= 90 && msg.y <= 130)
				{
					BGM(3);
					int a;
					a = begin();
					if (a == 1)
					{
						control();
						tangle();
						func();
					}
				}
				if (msg.x >= 460 && msg.x <= 540 && msg.y >= 90 && msg.y <= 130)
				{
					BGM(3);
					BGM(0);
					TU();
				}
				break;
			default:
				break;
			}
		}
	}
	getchar();
	//�رմ��ڣ�closegraph();
	closegraph();
}

int  begin()
{
	setfillcolor(LIGHTRED);
	solidrectangle(680, 90, 760, 130);
	outtextxy(700, 100, "��ʼ");
	if (flag == 0)
	{
		HWND hWnd = GetHWnd();
		MessageBox(hWnd, "�������������յ�", "���棡", MB_ICONEXCLAMATION);//��Ϣ�򵯳����ú���
		setfillcolor(RGB(0, 128, 192));
		solidrectangle(680, 90, 760, 130);	//���ƾ��Σ���ʼ��
		outtextxy(700, 100, "��ʼ");
		return 0;
	}
	else
		return 1;
}

void control()
{
	HWND hWnd = GetHWnd();
	MessageBox(hWnd, "��ɫ����ǰ�ڵ���ѡ�����·\n���ߴ����ɫ�ڵ�ǰ�����·��ýڵ���һ�������·\n��ɫ��ʾ��ɫ�ڵ�ĺ�˵�\n��ɫ�����Ѿ���ɵ����·�Ľڵ�\n���ȷ����ʼ", "TIPS��", MB_ICONINFORMATION);//��Ϣ�򵯳����ú���
}

void time()
{
	Sleep(750);
}

void tangle()
{
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	fillrectangle(520, 180, 760, 500);
	setlinecolor(BLACK);
	//��������������
	line(600, 180, 600, 500);
	line(680, 180, 680, 500);
	//���ϵ���7������
	line(520, 220, 760, 220);
	line(520, 260, 760, 260);
	line(520, 300, 760, 300);
	line(520, 340, 760, 340);
	line(520, 380, 760, 380);
	line(520, 420, 760, 420);
	line(520, 460, 760, 460);
	//д��ͼ������
	settextcolor(BLACK);	//�����������ɫ
	outtextxy(540, 190, "���");
	outtextxy(600, 190, "��̾���");
	outtextxy(690, 190, "ǰ�˵�");
	outtextxy(550, 230, "A");
	outtextxy(550, 270, "B");
	outtextxy(550, 310, "C");
	outtextxy(550, 350, "D");
	outtextxy(550, 390, "E");
	outtextxy(550, 430, "F");
	outtextxy(550, 470, "G");
	outtextxy(630, 230, "��");
	outtextxy(630, 270, "��");
	outtextxy(630, 310, "��");
	outtextxy(630, 350, "��");
	outtextxy(630, 390, "��");
	outtextxy(630, 430, "��");
	outtextxy(630, 470, "��");
}
void MYHWND()
{
	char s[10];
	InputBox(s, 10, "������Դ��", "��Դ�����·����Dijskra��");
	while (!(s[0] >= 'A' && s[0] <= 'G'))
	{
		HWND hWnd = GetHWnd();
		MessageBox(hWnd, "���벻�Ϸ�", "���棡", MB_ICONEXCLAMATION);//��Ϣ�򵯳����ú���
		InputBox(s, 10, "������Դ��", "��Դ�����·����Dijskra��");
	}
	outtextxy(120, 400, "��ʼ��");
	outtextxy(180, 400, s);
	InputBox(s, 10, "�������յ�", "��Դ�����·����Dijskra��");
	while (!(s[0] >= 'A' && s[0] <= 'G'))
	{
		HWND hWnd = GetHWnd();
		MessageBox(hWnd, "���벻�Ϸ�", "���棡", MB_ICONEXCLAMATION);//��Ϣ�򵯳����ú���
		InputBox(s, 10, "�������յ�", "��Դ�����·����Dijskra��");
	}
	outtextxy(120, 440, "�յ㣺");
	outtextxy(180, 440, s);

}

void func()
{
	time();
	setfillcolor(RED);
	solidcircle(40, 250, 20);
	outtextxy(35, 240, "A");
	fillrectangle(520, 220, 600, 260);
	outtextxy(550, 230, "A");
	clearrectangle(600, 220, 680, 260);
	setfillcolor(WHITE);
	fillrectangle(600, 220, 680, 260);
	outtextxy(630, 230, "0");

	time();
	setfillcolor(WHITE);
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	solidcircle(130, 340, 20);	//E
	outtextxy(125, 330, "E");
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");

	time();
	setlinecolor(RED);
	line(40, 250, 130, 160);	//A-B
	line(40, 250, 130, 340);	//A-E
	line(40, 250, 220, 250);	//A-D
	clearrectangle(600, 260, 680, 300);
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(600, 260, 680, 300);
	outtextxy(610, 270, "12<��");
	outtextxy(710, 270, "A");
	clearrectangle(600, 340, 680, 380);
	setfillcolor(WHITE);
	fillrectangle(600, 340, 680, 380);
	outtextxy(610, 350, "16<��");
	outtextxy(710, 350, "A");
	clearrectangle(600, 380, 680, 420);
	setfillcolor(WHITE);
	fillrectangle(600, 380, 680, 420);
	outtextxy(620, 390, "6<��");
	outtextxy(710, 390, "A");

	time();
	setfillcolor(RGB(255, 128, 0));
	solidcircle(40, 250, 20);	//A
	outtextxy(35, 240, "A");
	fillrectangle(520, 220, 600, 260);
	outtextxy(550, 230, "A");
	clearrectangle(600, 260, 680, 300);
	setfillcolor(WHITE);
	fillrectangle(600, 260, 680, 300);
	outtextxy(630, 270, "12");
	clearrectangle(600, 340, 680, 380);
	setfillcolor(WHITE);
	fillrectangle(600, 340, 680, 380);
	outtextxy(630, 350, "16");
	clearrectangle(600, 380, 680, 420);
	setfillcolor(WHITE);
	fillrectangle(600, 380, 680, 420);
	outtextxy(630, 390, "6");
	setlinecolor(RGB(128, 128, 255));
	line(40, 250, 130, 160);	//A-B
	line(40, 250, 130, 340);	//A-E
	line(40, 250, 220, 250);	//A-D
	setfillcolor(RGB(0, 128, 192));
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	solidcircle(130, 340, 20);	//E
	outtextxy(125, 330, "E");
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");


	time();
	setfillcolor(RED);
	setlinecolor(BLACK);
	solidcircle(130, 340, 20);	//E
	outtextxy(125, 330, "E");
	fillrectangle(520, 380, 600, 420);
	outtextxy(550, 390, "E");

	time();
	setfillcolor(WHITE);
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");
	solidcircle(320, 340, 20);	//F
	outtextxy(315, 330, "F");

	time();
	setlinecolor(RED);
	line(40, 250, 130, 340);	//A-E
	line(130, 340, 220, 250);	//E-D
	line(130, 340, 320, 340);	//E-F
	setlinecolor(BLACK);
	clearrectangle(600, 340, 680, 380);
	setfillcolor(WHITE);
	fillrectangle(600, 340, 680, 380);
	outtextxy(610, 350, "6+5<16");
	clearrectangle(600, 420, 680, 460);
	setfillcolor(WHITE);
	fillrectangle(600, 420, 680, 460);
	outtextxy(610, 430, "6+8<��");

	time();
	setfillcolor(RGB(255, 128, 0));
	solidcircle(130, 340, 20);	//E
	outtextxy(125, 330, "E");
	fillrectangle(520, 380, 600, 420);
	outtextxy(550, 390, "E");
	setlinecolor(RGB(128, 128, 255));
	line(40, 250, 130, 340);	//A-E
	line(130, 340, 220, 250);	//E-D
	line(130, 340, 320, 340);	//E-F
	setfillcolor(RGB(0, 128, 192));
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");
	solidcircle(320, 340, 20);	//F
	outtextxy(315, 330, "F");
	setlinecolor(BLACK);
	clearrectangle(600, 420, 680, 460);
	setfillcolor(WHITE);
	fillrectangle(600, 420, 680, 460);
	outtextxy(620, 430, "14");
	clearrectangle(680, 340, 760, 380);
	setfillcolor(WHITE);
	fillrectangle(680, 340, 760, 380);
	outtextxy(710, 350, "E");
	outtextxy(710, 430, "E");
	clearrectangle(600, 340, 680, 380);
	setfillcolor(WHITE);
	fillrectangle(600, 340, 680, 380);
	outtextxy(620, 350, "16");

	time();
	setfillcolor(RED);
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");
	fillrectangle(520, 340, 600, 380);
	outtextxy(550, 350, "D");

	time();
	setfillcolor(WHITE);
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	solidcircle(320, 160, 20);	//C
	outtextxy(315, 150, "C");
	solidcircle(320, 340, 20);	//F
	outtextxy(315, 330, "F");

	time();
	setfillcolor(RGB(0, 128, 192));
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	solidcircle(320, 160, 20);	//C
	outtextxy(315, 150, "C");
	solidcircle(320, 340, 20);	//F
	outtextxy(315, 330, "F");
	clearrectangle(600, 260, 680, 300);
	setfillcolor(WHITE);
	fillrectangle(600, 260, 680, 300);
	outtextxy(610, 270, "11+7>12");
	clearrectangle(600, 300, 680, 340);
	setfillcolor(WHITE);
	fillrectangle(600, 300, 680, 340);
	outtextxy(610, 310, "11+6<��");
	clearrectangle(600, 420, 680, 460);
	setfillcolor(WHITE);
	fillrectangle(600, 420, 680, 460);
	outtextxy(610, 430, "11+2<14");
	setlinecolor(RED);
	line(40, 250, 130, 340);	//A-E
	line(130, 160, 220, 250);	//B-D
	line(220, 250, 320, 160);	//D-C
	line(130, 340, 220, 250);	//E-D
	line(220, 250, 320, 340);	//D-F

	time();
	setfillcolor(RGB(255, 128, 0));
	setlinecolor(BLACK);
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");

	fillrectangle(520, 340, 600, 380);
	outtextxy(550, 350, "D");
	clearrectangle(600, 260, 680, 300);
	setfillcolor(WHITE);
	fillrectangle(600, 260, 680, 300);
	outtextxy(620, 270, "12");
	clearrectangle(600, 300, 680, 340);
	setfillcolor(WHITE);
	fillrectangle(600, 300, 680, 340);
	outtextxy(620, 310, "17");
	clearrectangle(600, 420, 680, 460);
	setfillcolor(WHITE);
	fillrectangle(600, 420, 680, 460);
	outtextxy(620, 430, "13");
	clearrectangle(680, 420, 760, 460);
	setfillcolor(WHITE);
	fillrectangle(680, 420, 760, 460);
	outtextxy(710, 430, "D");
	outtextxy(710, 310, "D");
	setlinecolor(RGB(128, 128, 255));
	line(40, 250, 130, 340);	//A-E
	line(130, 160, 220, 250);	//B-D
	line(220, 250, 320, 160);	//D-C
	line(130, 340, 220, 250);	//E-D
	line(220, 250, 320, 340);	//D-F

	time();
	setfillcolor(RED);
	setlinecolor(BLACK);
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	fillrectangle(520, 260, 600, 300);
	outtextxy(550, 270, "B");

	time();
	setfillcolor(WHITE);
	setlinecolor(RED);
	line(40, 250, 130, 160);	//A-B
	line(130, 160, 320, 160);	//B-C
	solidcircle(320, 160, 20);	//C
	outtextxy(315, 150, "C");
	setlinecolor(BLACK);
	clearrectangle(600, 300, 680, 340);
	setfillcolor(WHITE);
	fillrectangle(600, 300, 680, 340);
	outtextxy(600, 310, "12+10>17");

	time();
	setfillcolor(RGB(0, 128, 192));
	solidcircle(320, 160, 20);	//C
	outtextxy(315, 150, "C");
	setfillcolor(RGB(255, 128, 0));
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	fillrectangle(520, 260, 600, 300);
	outtextxy(550, 270, "B");
	clearrectangle(600, 300, 680, 340);
	setfillcolor(WHITE);
	fillrectangle(600, 300, 680, 340);
	outtextxy(620, 310, "17");
	setlinecolor(RGB(128, 128, 255));
	line(40, 250, 130, 160);	//A-B
	line(130, 160, 320, 160);	//B-C

	time();
	setfillcolor(RED);
	setlinecolor(BLACK);
	solidcircle(320, 340, 20);	//F
	outtextxy(315, 330, "F");
	fillrectangle(520, 420, 600, 460);
	outtextxy(550, 430, "F");

	time();
	setlinecolor(BLACK);
	clearrectangle(600, 300, 680, 340);
	setfillcolor(WHITE);
	fillrectangle(600, 300, 680, 340);
	outtextxy(600, 310, "13+11>17");
	clearrectangle(600, 460, 680, 500);
	setfillcolor(WHITE);
	fillrectangle(600, 460, 680, 500);
	outtextxy(610, 470, "13+4<��");
	setlinecolor(RED);
	line(40, 250, 130, 340);	//A-E
	line(130, 340, 220, 250);	//E-D
	line(220, 250, 320, 340);	//D-F
	line(320, 160, 320, 340);	//C-F
	line(320, 340, 440, 250);	//F-G

	time();
	setlinecolor(BLACK);
	clearrectangle(600, 300, 680, 340);
	setfillcolor(WHITE);
	fillrectangle(600, 300, 680, 340);
	outtextxy(620, 310, "17");
	clearrectangle(600, 460, 680, 500);
	setfillcolor(WHITE);
	fillrectangle(600, 460, 680, 500);
	outtextxy(620, 470, "17");
	outtextxy(710, 470, "F");
	setfillcolor(RGB(255, 128, 0));
	setlinecolor(BLACK);
	solidcircle(320, 340, 20);	//F
	outtextxy(315, 330, "F");
	fillrectangle(520, 420, 600, 460);
	outtextxy(550, 430, "F");
	setlinecolor(RGB(128, 128, 255));
	line(40, 250, 130, 340);	//A-E
	line(130, 340, 220, 250);	//E-D
	line(220, 250, 320, 340);	//D-F
	line(320, 160, 320, 340);	//C-F
	line(320, 340, 440, 250);	//F-G

	time();
	setfillcolor(RED);
	setlinecolor(BLACK);
	solidcircle(320, 160, 20);	//C
	outtextxy(315, 150, "C");
	fillrectangle(520, 300, 600, 340);
	outtextxy(550, 310, "C");


	time();
	setfillcolor(WHITE);
	solidcircle(440, 250, 20);	//G
	outtextxy(435, 240, "G");

	time();
	setlinecolor(BLACK);
	clearrectangle(600, 460, 680, 500);
	setfillcolor(WHITE);
	fillrectangle(600, 460, 680, 500);
	outtextxy(600, 470, "17+3>17");
	setlinecolor(RED);
	line(40, 250, 130, 340);	//A-E
	line(130, 340, 220, 250);	//E-D
	line(220, 250, 320, 160);	//D-C

	time();
	setlinecolor(BLACK);
	setfillcolor(RGB(255, 128, 0));
	solidcircle(320, 160, 20);	//C
	outtextxy(315, 150, "C");
	fillrectangle(520, 300, 600, 340);
	outtextxy(550, 310, "C");
	setlinecolor(RGB(128, 128, 255));
	line(40, 250, 130, 340);	//A-E
	line(130, 340, 220, 250);	//E-D
	line(220, 250, 320, 160);	//D-C
	setfillcolor(RGB(0, 128, 192));
	solidcircle(440, 250, 20);	//G
	outtextxy(435, 240, "G");
	setlinecolor(BLACK);
	clearrectangle(600, 460, 680, 500);
	setfillcolor(WHITE);
	fillrectangle(600, 460, 680, 500);
	outtextxy(620, 470, "17");

	time();
	setfillcolor(RED);
	solidcircle(440, 250, 20);	//G
	outtextxy(435, 240, "G");
	fillrectangle(520, 460, 600, 500);
	outtextxy(550, 470, "G");

	time();
	setfillcolor(RGB(255, 128, 0));
	solidcircle(440, 250, 20);	//G
	outtextxy(435, 240, "G");
	fillrectangle(520, 460, 600, 500);
	outtextxy(550, 470, "G");

	Sleep(1000);
	HWND hWnd = GetHWnd();
	MessageBox(hWnd, "����������ʾ�յ㵽�������·", "��ʾ", MB_ICONINFORMATION);//��Ϣ�򵯳����ú���
	setlinecolor(BLACK);
	outtextxy(120, 480, "��㵽�յ�����·����");

	time();
	setlinecolor(RED);
	rectangle(690, 470, 750, 490);
	outtextxy(120, 500, "A->");

	time();
	setlinecolor(BLACK);
	clearrectangle(680, 460, 760, 500);
	setfillcolor(WHITE);
	fillrectangle(680, 460, 760, 500);
	outtextxy(710, 470, "F");
	setlinecolor(RED);
	rectangle(690, 430, 750, 450);
	outtextxy(150, 500, "E->");

	time();
	setlinecolor(BLACK);
	clearrectangle(680, 420, 760, 460);
	setfillcolor(WHITE);
	fillrectangle(680, 420, 760, 460);
	outtextxy(710, 430, "D");
	setlinecolor(RED);
	rectangle(690, 350, 750, 370);
	outtextxy(180, 500, "D->");

	time();
	setlinecolor(BLACK);
	clearrectangle(680, 340, 760, 380);
	setfillcolor(WHITE);
	fillrectangle(680, 340, 760, 380);
	outtextxy(710, 350, "E");
	setlinecolor(RED);
	rectangle(690, 390, 750, 410);
	outtextxy(210, 500, "F->");

	time();
	setlinecolor(BLACK);
	clearrectangle(680, 380, 760, 420);
	setfillcolor(WHITE);
	fillrectangle(680, 380, 760, 420);
	outtextxy(710, 390, "A");
	outtextxy(240, 500, "G");
}