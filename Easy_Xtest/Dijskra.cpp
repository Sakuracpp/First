#include<stdio.h>
#include<graphics.h>//����ͼ���ͷ�ļ�,����������C++
#include<conio.h>
#include<math.h>
int flag = 0;
void tangle();	//ͼ����Ϣ����
int begin();	//��ʼ������ɫ
void MYHWND();	//��ʾ��ʾ��
void func();	//��������
void time();	//������ʱ
void control();	//˵����������
int main()
{
	//����һ�����ڣ�initgraph();
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
	setfillcolor(RGB(0,128,192));		//���þ��������ɫ
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
	setlinecolor(RGB(128,128,255));
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
					setfillcolor(LIGHTRED);
					setrop2(R2_COPYPEN);
					solidrectangle(580, 90, 660, 130);
					outtextxy(580, 100, "����ʼ��");
					MYHWND();
					flag = 1;
				}
				if (msg.x >= 680 && msg.x <= 760 && msg.y >= 90 && msg.y <= 130)
				{
					int a;
					a=begin();
					if (a == 1)
					{
						control();
						tangle();
						func();
					}
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
	return 0;
}

int  begin()
{
	setfillcolor(LIGHTRED);
	setrop2(R2_COPYPEN);
	solidrectangle(680, 90, 760, 130);
	outtextxy(700, 100, "��ʼ");
	if (flag == 0)
	{
		HWND hWnd = GetHWnd();
		MessageBox(hWnd, "�������������յ�", "���棡", MB_ICONEXCLAMATION);//��Ϣ�򵯳����ú���
		setfillcolor(RGB(0, 128, 192));
		setrop2(R2_COPYPEN);
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
	setrop2(R2_COPYPEN);
	setlinecolor(BLACK);
	setrop2(R2_COPYPEN);
	fillrectangle(520,180,760,500);
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
	InputBox(s, 10, "������Դ��","��Դ�����·����Dijskra��");
	while (!(s[0]>='A'&&s[0]<='G'))
	{
		HWND hWnd = GetHWnd();
		MessageBox(hWnd, "���벻�Ϸ�", "���棡", MB_ICONEXCLAMATION);//��Ϣ�򵯳����ú���
		InputBox(s, 10, "������Դ��", "��Դ�����·����Dijskra��");
	}
	outtextxy(120, 400,"��ʼ��");
	outtextxy(180, 400,s);
	InputBox(s, 10, "�������յ�", "��Դ�����·����Dijskra��");
	while (!(s[0] >= 'A' && s[0] <= 'G'))
	{
		HWND hWnd = GetHWnd();
		MessageBox(hWnd, "���벻�Ϸ�", "���棡", MB_ICONEXCLAMATION);//��Ϣ�򵯳����ú���
		InputBox(s, 10, "�������յ�", "��Դ�����·����Dijskra��");
	}
	outtextxy(120, 440, "�յ㣺");
	outtextxy(180, 440,s);
	
}

void func()
{
	time();
	setfillcolor(RED);
	setrop2(R2_COPYPEN);
	solidcircle(40, 250, 20);
	outtextxy(35, 240, "A");
	fillrectangle(520,220,600,260);
	outtextxy(550, 230, "A");
	clearrectangle(600, 220, 680, 260);
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
	fillrectangle(600, 220, 680, 260);
	outtextxy(630, 230, "0");

	time();
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	solidcircle(130, 340, 20);	//E
	outtextxy(125, 330, "E");
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");

	time();
	setlinecolor(RED);
	setrop2(R2_COPYPEN);
	line(40, 250, 130, 160);	//A-B
	line(40, 250, 130, 340);	//A-E
	line(40, 250, 220, 250);	//A-D
	clearrectangle(600, 260, 680, 300);
	setlinecolor(BLACK);
	setrop2(R2_COPYPEN);
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
	fillrectangle(600, 260, 680, 300);
	outtextxy(610, 270, "12<��");
	outtextxy(710, 270, "A");
	clearrectangle(600, 340, 680, 380);
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
	fillrectangle(600, 340, 680, 380);
	outtextxy(610, 350, "16<��");
	outtextxy(710, 350, "A");
	clearrectangle(600, 380, 680, 420);
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
	fillrectangle(600, 380, 680, 420);
	outtextxy(620, 390, "6<��");
	outtextxy(710, 390, "A");

	time();
	setfillcolor(RGB(255, 128,0));
	solidcircle(40, 250, 20);	//A
	outtextxy(35, 240, "A");
	fillrectangle(520, 220, 600, 260);
	outtextxy(550, 230, "A");
	clearrectangle(600, 260, 680, 300);
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
	fillrectangle(600, 260, 680, 300);
	outtextxy(630, 270, "12");
	clearrectangle(600, 340, 680, 380);
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
	fillrectangle(600, 340, 680, 380);
	outtextxy(630, 350, "16");
	clearrectangle(600, 380, 680, 420);
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
	fillrectangle(600, 380, 680, 420);
	outtextxy(630, 390, "6");
	setlinecolor(RGB(128, 128, 255));
	setrop2(R2_COPYPEN);
	line(40, 250, 130, 160);	//A-B
	line(40, 250, 130, 340);	//A-E
	line(40, 250, 220, 250);	//A-D
	setfillcolor(RGB(0, 128, 192));
	setrop2(R2_COPYPEN);
	solidcircle(130, 160, 20);	//B
	outtextxy(125, 150, "B");
	solidcircle(130, 340, 20);	//E
	outtextxy(125, 330, "E");
	solidcircle(220, 250, 20);	//D
	outtextxy(215, 240, "D");
	

	time();
	setfillcolor(RED);
	setrop2(R2_COPYPEN);
	setlinecolor(BLACK);
	setrop2(R2_COPYPEN);
	solidcircle(130, 340, 20);	//E
	outtextxy(125, 330, "E");
	fillrectangle(520, 380, 600, 420);
	outtextxy(550, 390, "E");

	time();
	setfillcolor(WHITE);
	setrop2(R2_COPYPEN);
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
	setfillcolor(RGB(255,128,0));
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
	outtextxy(120,480,"��㵽�յ�����·����");

	time();
	setlinecolor(RED);
	rectangle(690,470,750,490);
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