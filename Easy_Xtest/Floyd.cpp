#include<graphics.h>//包含图像库头文件,仅仅适用于C++
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include <tchar.h>
using namespace std;
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

void CreateMGraph(MGraph* G);	//构建和初始化图
void ShortPath_Floyd(MGraph G, Patharc P, ShortPathTable D);	//Floyd算法
void PrintShortPath(MGraph G, Patharc P, ShortPathTable D,int i,int j);		//打印
void test();

int button_judge(int x, int y, int(*r)[4]);	//返回鼠标是否在17个城市中
void out(int a[],int num,int num1);		//输出最短路的信息
void huizhi();		//绘制图形
void mes();			//鼠标操作
void getmess(int a[]);		//绘制开始与设置路径并点击
void write(int a);	//写起点和终点

int flag1 = 0,x=0;//flag1记录是否点击了设置起点和终点，x记录了点击次数
int i, j;	//记录起点和终点的数字信息

void Floyd();

//Dijksra
int flag = 0;
void tangle();	//图表信息加载
int begin();	//开始按键变色
void MYHWND();	//显示提示窗
void func();	//动画过程
void time();	//控制延时
void control();	//说明动画详情
void Dijksra();

int main()
{
	Floyd();
	return 0;
}

void huizhi()
{
	setfillcolor(RGB(0, 255, 255));
	setrop2(R2_COPYPEN);
	settextcolor(BLACK);
	solidrectangle(750, 80, 850, 120);
	outtextxy(760, 90, "设置起点");
	solidrectangle(880, 80, 980, 120);
	outtextxy(890, 90, "设置终点");
	outtextxy(760, 140, "起点：");
	outtextxy(760, 180, "终点：");
	solidrectangle(750, 220, 850, 260);
	outtextxy(760, 230, "求最短路");
	solidrectangle(750, 280, 850, 320);
	outtextxy(780, 290, "重置");
	solidrectangle(750, 340, 850, 380);
	outtextxy(780, 350, "退出");

	setfillcolor(BLACK);		//设置矩形填充颜色
	settextcolor(WHITE);
	solidrectangle(300, 260, 360, 300);
	outtextxy(310, 270, "武汉");
	solidrectangle(290, 170, 350, 210);
	outtextxy(300, 180, "郑州");
	solidrectangle(430, 170, 490, 210);
	outtextxy(440, 180, "徐州");
	solidrectangle(470, 260, 530, 300);
	outtextxy(480, 270, "上海");
	solidrectangle(260, 340, 320, 380);
	outtextxy(270, 350, "株州");
	solidrectangle(420, 360, 480, 400);
	outtextxy(430, 370, "南昌");
	solidrectangle(520, 450, 580, 490);
	outtextxy(530, 460, "福州");
	solidrectangle(280, 460, 340, 500);
	outtextxy(290, 470, "广州");
	solidrectangle(380, 520, 440, 560);
	outtextxy(390, 530, "深圳");
	solidrectangle(160, 420, 220, 460);
	outtextxy(170, 430, "柳州");
	solidrectangle(100, 360, 160, 400);
	outtextxy(110, 370, "贵阳");
	solidrectangle(60, 250, 120, 290);
	outtextxy(70, 260, "成都");
	solidrectangle(120, 150, 180, 190);
	outtextxy(130, 160, "西安");
	solidrectangle(80, 80, 140, 120);
	outtextxy(90, 90, "兰州");
	solidrectangle(340, 40, 400, 80);
	outtextxy(350, 50, "北京");
	solidrectangle(210, 50, 270, 90);
	outtextxy(220, 60, "呼特");
	solidrectangle(460, 80, 520, 120);
	outtextxy(470, 90, "天津");

	//连线
	setlinecolor(BLACK);
	settextcolor(BLACK);	 //设置字体的颜色
	line(330, 260, 320, 210);//武汉-郑州
	outtextxy(340, 225, "534");
	line(350, 190, 430, 190);//郑州-徐州
	outtextxy(390, 170, "349");
	line(460, 210, 500, 260);//徐州-上海
	outtextxy(490, 220, "651");
	line(500, 300, 450, 360);//上海-南昌
	outtextxy(480, 320, "825");
	line(450, 400, 550, 450);//南昌-福州
	outtextxy(510, 410, "622");
	line(330, 300, 290, 340);//武汉-株洲
	outtextxy(270, 310, "409");
	line(320, 360, 420, 380);//株洲-南昌
	outtextxy(360, 350, "367");
	line(220, 430, 290, 380);//柳州-株洲
	outtextxy(240, 410, "672");
	line(290, 380, 310, 460);//株洲-广州
	outtextxy(310, 420, "675");
	line(310, 500, 410, 520);//广州-深圳
	outtextxy(360, 490, "140");
	line(260, 360, 160, 380);//株洲-贵阳
	outtextxy(190, 350, "902");
	line(190, 420, 130, 400);//柳州-贵阳
	outtextxy(170, 390, "607");
	line(90, 290, 130, 360);//成都-贵阳
	outtextxy(120, 300, "967");
	line(90, 250, 150, 190);//成都-西安
	outtextxy(140, 220, "842");
	line(180, 170, 290, 190);//西安-郑州
	outtextxy(230, 160, "511");
	line(150, 150, 110, 120);//西安-兰州
	outtextxy(140, 120, "676");
	line(320, 170, 370, 80);//郑州-北京
	outtextxy(350, 120, "695");
	line(270, 70, 340, 60);//呼和浩特-北京
	outtextxy(290, 45, "668");
	line(140, 100, 210, 70);//兰州-呼特
	outtextxy(150, 60, "1145");
	line(400, 60, 460, 100);//北京-天津
	outtextxy(430, 60, "137");
	line(490, 120, 460, 170);//天津-徐州
	outtextxy(490, 140, "674");
}

void mes()
{
	int r[22][4] = { {300, 260, 360, 300},{290, 170, 350, 210},{430, 170, 490, 210},{470, 260, 530, 300},{260, 340, 320, 380},
		{420, 360, 480, 400},{520, 450, 580, 490},{280, 460, 340, 500},{380, 520, 440, 560},{160, 420, 220, 460},{100, 360, 160, 400},
		{60, 250, 120, 290},{120, 150, 180, 190},{80, 80, 140, 120},{340, 40, 400, 80},{210, 50, 270, 90},{460, 80, 520, 120}};
	int event = 0;
	while (true)
	{
		MOUSEMSG msg;//鼠标指针
		settextcolor(WHITE);
		msg = GetMouseMsg();//获取一条鼠标消息
		switch (msg.uMsg)//筛选鼠标信息类型
		{
		case WM_MOUSEMOVE://移动信息
			setrop2(R2_XORPEN);
			setfillcolor(RGB(255, 128, 64));
			if (button_judge(msg.x, msg.y, r) != 0)
			{
				if (event != button_judge(msg.x, msg.y, r))
				{
					event = button_judge(msg.x, msg.y, r);//记录这一次触发的按钮
					solidrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					solidrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
				case WM_LBUTTONDOWN://左键点击
					if (msg.x >= 750 && msg.x <= 850 && msg.y >= 340 && msg.y <= 380)
					{
						setfillcolor(WHITE);
						settextcolor(BLACK);
						solidrectangle(750, 340, 850, 380);
						outtextxy(780, 350, "退出");
						exit(1);
					}
					if (msg.x >= 750 && msg.x <= 850 && msg.y >= 80 && msg.y <= 120)
					{
						setrop2(R2_WHITE);
						settextcolor(BLACK);
						solidrectangle(750, 80, 850, 120);
						outtextxy(760, 90, "设置起点");
						flag1 = 1;
					}
					if (msg.x >= 880 && msg.x <= 980 && msg.y >= 80 && msg.y <= 120)
					{
						if (flag1 != 1&&flag1!=2)
						{
							HWND hWnd = GetHWnd();
							MessageBox(hWnd, "请先设置起点", "警告！", MB_ICONEXCLAMATION);//消息框弹出设置函数
						}
						else if(flag1==1){
							setrop2(R2_WHITE);
							settextcolor(BLACK);
							solidrectangle(880, 80, 980, 120);
							outtextxy(890, 90, "设置终点");
							flag1 = 2;
						}
					}
					if (msg.x >= 750 && msg.x <= 850 && msg.y >= 220 && msg.y <= 260)
					{
						if (flag1 == 0)
						{
							HWND hWnd = GetHWnd();
							MessageBox(hWnd, "请选择起点和终点！", "警告！", MB_ICONEXCLAMATION);//消息框弹出设置函数
							break;
						}
						setrop2(R2_WHITE);
						settextcolor(BLACK);
						solidrectangle(750, 220, 850, 260);
						outtextxy(760, 230, "求最短路");
						test();
					}
					if (flag1 == 0)
					{
						continue;
					}
					if (msg.x >= 750 && msg.x <= 850 && msg.y >= 280 && msg.y <= 320 )
					{
						setrop2(R2_WHITE);
						settextcolor(BLACK);
						solidrectangle(750, 280, 850, 320);
						outtextxy(780, 290, "重置");
						setrop2(R2_COPYPEN);
						setfillcolor(BROWN);
						solidrectangle(620, 420, 1000, 500);
						clearrectangle(620, 500, 760, 600);
						clearrectangle(810, 140,890,160);
						clearrectangle(810, 160, 890, 220);
						huizhi();
					}
					if (msg.x >= 300 && msg.x <= 360 && msg.y >= 260 && msg.y <= 300)
				    { 
					settextcolor(BROWN);
					outtextxy(310, 270, "武汉");
					write(5);
				    }
			        if (msg.x >= 290 && msg.x <= 350 && msg.y >= 170 && msg.y <= 210)
				    {
					settextcolor(BROWN);
					
					outtextxy(300, 180, "郑州");
					write(4);
				    }
				    if (msg.x >= 430 && msg.x <= 490 && msg.y >= 170 && msg.y <= 210)
				    {
					 settextcolor(BROWN);
					 
					outtextxy(440, 180, "徐州");
					write(9);
					
				    }
				 if (msg.x >= 470 && msg.x <= 530 && msg.y >= 260 && msg.y <= 300)
				{
					 settextcolor(BROWN);
					 
					outtextxy(480, 270, "上海");
					write(10);
					
				}
				 if (msg.x >= 260 && msg.x <= 320 && msg.y >= 340 && msg.y <= 380)
				{
					 settextcolor(BROWN);
					 
					outtextxy(270, 350, "株州");
					write(6);
					
				}
			    if (msg.x >= 420 && msg.x <= 480 && msg.y >= 360 && msg.y <= 400)
				{
					settextcolor(BROWN);
					
					outtextxy(430, 370, "南昌");
					write(11);
					
				}
				 if (msg.x >= 520 && msg.x <= 580 && msg.y >= 450 && msg.y <= 490)
				{
					 settextcolor(BROWN);
					 
					outtextxy(530, 460, "福州");
					write(12);
					
				}
				 if (msg.x >= 280 && msg.x <= 340 && msg.y >= 460 && msg.y <= 500)
				{
					 settextcolor(BROWN);
					 
					outtextxy(290, 470, "广州");
					write(7);
					
				}
				 if (msg.x >= 380 && msg.x <= 440 && msg.y >= 520 && msg.y <= 560)
				{
					 settextcolor(BROWN);
					 
					outtextxy(390, 530, "深圳");
					write(8);
					
				}
				 if (msg.x >= 160 && msg.x <= 220 && msg.y >= 420 && msg.y <= 460)
				{
					 settextcolor(BROWN);
					 
					outtextxy(170, 430, "柳州");
					write(3);
					
				}
				 if (msg.x >= 100 && msg.x <= 160 && msg.y >= 360 && msg.y <= 400)
				{
					 settextcolor(BROWN);
					 
					outtextxy(110, 370, "贵阳");
					write(2);
					
				}
				 if (msg.x >= 60 && msg.x <= 120 && msg.y >= 250 && msg.y <= 290)
				{
					 settextcolor(BROWN);
					outtextxy(70, 260, "成都");
					write(1);
					
				}
				 if (msg.x >= 120 && msg.x <= 180 && msg.y >= 150 && msg.y <= 190)
				{
					 settextcolor(BROWN);
					outtextxy(130, 160, "西安");
					write(0);
					
				}
				 if (msg.x >= 80 && msg.x <= 140 && msg.y >= 80 && msg.y <= 120)
				 {
					 settextcolor(BROWN);
					 outtextxy(90, 90, "兰州");
					 write(13);
					 
				 }
				 if (msg.x >= 340 && msg.x <= 400 && msg.y >= 40 && msg.y <= 80)
				 {
					 settextcolor(BROWN);
					 outtextxy(350, 50, "北京");
					 write(15);
					 
				 }
				 if (msg.x >= 210 && msg.x <= 270 && msg.y >= 50 && msg.y <= 90)
				 {
					 settextcolor(BROWN);
					 outtextxy(220, 60, "呼特");
					 write(14);
					 
				 }
				 if (msg.x >= 460 && msg.x <= 520 && msg.y >= 80 && msg.y <= 120)
				 {
					 settextcolor(BROWN);
					 outtextxy(470, 90, "天津");
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
		if (a[s] == 0 && a[s + 1] == 1||a[s]==1&&a[s+1]==0)
		{
			line(90, 250, 150, 190);//成都-西安
			outtextxy(70, 260, "成都");
			outtextxy(130, 160, "西安");
		}
		 if (a[s] == 0 && a[s + 1] == 13 || a[s] == 13 && a[s + 1] == 0)
		{
			line(150, 150, 110, 120);//西安-兰州
			outtextxy(130, 160, "西安");
			outtextxy(90, 90, "兰州");
		}
		 if (a[s] == 0 && a[s + 1] == 4 || a[s] == 4 && a[s + 1] == 0)
		{
			line(180, 170, 290, 190);//西安-郑州
			outtextxy(130, 160, "西安");
			outtextxy(300, 180, "郑州");
		}
		 if (a[s] == 1 && a[s + 1] == 2 || a[s] == 2 && a[s + 1] == 1)
		{
			line(90, 290, 130, 360);//成都-贵阳
			outtextxy(70, 260, "成都");
			outtextxy(110, 370, "贵阳");
		}
		 if (a[s] == 2 && a[s + 1] == 3 || a[s] == 3 && a[s + 1] == 2)
		{
			line(190, 420, 130, 400);//柳州-贵阳
			outtextxy(110, 370, "贵阳");
			outtextxy(170, 430, "柳州");
		}
		 if (a[s] == 2 && a[s + 1] == 6 || a[s] == 6 && a[s + 1] == 2)
		{
			line(260, 360, 160, 380);//株洲-贵阳
			outtextxy(270, 350, "株州");
			outtextxy(110, 370, "贵阳");
		}
		 if (a[s] == 3 && a[s + 1] == 6 || a[s] == 6 && a[s + 1] == 3)
		{
			line(220, 430, 290, 380);//柳州-株洲
			outtextxy(270, 350, "株州");
			outtextxy(170, 430, "柳州");
		}
		 if (a[s] == 4 && a[s + 1] == 9 || a[s] == 9 && a[s + 1] == 4)
		{
			line(350, 190, 430, 190);//郑州-徐州
			outtextxy(300, 180, "郑州");
			outtextxy(440, 180, "徐州");
		}
		 if (a[s] == 4 && a[s + 1] == 5 || a[s] == 5 && a[s + 1] == 4)
		{
			line(330, 260, 320, 210);//武汉-郑州
			outtextxy(310, 270, "武汉");
			outtextxy(300, 180, "郑州");
		}
		 if (a[s] == 4 && a[s + 1] == 15 || a[s] == 15 && a[s + 1] == 4)
		{
			line(320, 170, 370, 80);//郑州-北京
			outtextxy(300, 180, "郑州");
			outtextxy(350, 50, "北京");
		}
		 if (a[s] == 5 && a[s + 1] == 6 || a[s] == 6 && a[s + 1] == 5)
		{
			line(330, 300, 290, 340);//武汉-株洲
			outtextxy(310, 270, "武汉");
			outtextxy(270, 350, "株州");
		}
		 if (a[s] == 6 && a[s + 1] == 7 || a[s] == 7 && a[s + 1] == 6)
		{
			line(290, 380, 310, 460);//株洲-广州
			outtextxy(270, 350, "株州");
			outtextxy(290, 470, "广州");
		}
		 if (a[s] == 6 && a[s + 1] == 11 || a[s] == 11 && a[s + 1] == 6)
		{
			line(320, 360, 420, 380);//株洲-南昌
			outtextxy(270, 350, "株州");
			outtextxy(430, 370, "南昌");
		}
		 if (a[s] == 7 && a[s + 1] == 8 || a[s] == 8 && a[s + 1] == 7)
		{
			line(310, 500, 410, 520);//广州-深圳
			outtextxy(290, 470, "广州");
			outtextxy(390, 530, "深圳");
		}
		 if (a[s] == 9 && a[s + 1] == 10 || a[s] == 10 && a[s + 1] == 9)
		{
			line(460, 210, 500, 260);//徐州-上海
			outtextxy(440, 180, "徐州");
			outtextxy(480, 270, "上海");
		}
		 if (a[s] == 9 && a[s + 1] == 16 || a[s] == 16 && a[s + 1] == 9)
		{
			line(490, 120, 460, 170);//天津-徐州
			outtextxy(470, 90, "天津");
			outtextxy(440, 180, "徐州");
		}
		 if (a[s] == 10 && a[s + 1] == 11 || a[s] == 11 && a[s + 1] == 10)
		{
			line(500, 300, 450, 360);//上海-南昌
			outtextxy(480, 270, "上海");
			outtextxy(430, 370, "南昌");
		}
		 if (a[s] == 11 && a[s + 1] == 12 || a[s] == 12 && a[s + 1] == 11)
		{
			line(450, 400, 550, 450);//南昌-福州
			outtextxy(430, 370, "南昌");
			outtextxy(530, 460, "福州");
		}
		 if (a[s] == 13 && a[s + 1] == 14 || a[s] == 14 && a[s + 1] == 13)
		{
			line(140, 100, 210, 70);//兰州-呼特
			outtextxy(90, 90, "兰州");
			outtextxy(220, 60, "呼特");
		}
		 if (a[s] == 14 && a[s + 1] == 15 || a[s] == 15 && a[s + 1] == 14)
		{
			line(270, 70, 340, 60);//呼和浩特-北京
			outtextxy(220, 60, "呼特");
			outtextxy(350, 50, "北京");
		}
		 if (a[s] == 15 && a[s + 1] == 16 || a[s] == 16 && a[s + 1] == 15)
		{
			line(400, 60, 460, 100);//北京-天津
			outtextxy(350, 50, "北京");
			outtextxy(470, 90, "天津");
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
			outtextxy(810, 140, "西安");
			break;
		case 1:
			i = 1;
			outtextxy(810, 140, "成都");
			break;
		case 2:
			i = 2;
			outtextxy(810, 140, "贵阳");
			break;
		case 3:
			i = 3;
			outtextxy(810, 140, "柳州");
			break;
		case 4:
			i = 4;
			outtextxy(810, 140, "郑州");
			break;
		case 5:
			i = 5;
			outtextxy(810, 140, "武汉");
			break;
		case 6:
			i = 6;
			outtextxy(810, 140, "株洲");
			break;
		case 7:
			i = 7;
			outtextxy(810, 140, "广州");
			break;
		case 8:
			i = 8;
			outtextxy(810, 140, "深圳");
			break;
		case 9:
			i = 9;
			outtextxy(810, 140, "徐州");
			break;
		case 10:
			i = 10;
			outtextxy(810, 140, "上海");
			break;
		case 11:
			i = 11;
			outtextxy(810, 140, "南昌");
			break;
		case 12:
			i = 12;
			outtextxy(810, 140, "福州");
			break;
		case 13:
			i = 13;
			outtextxy(810, 140, "兰州");
			break;
		case 14:
			i = 14;
			outtextxy(810, 140, "呼特");
			break;
		case 15:
			i = 15;
			outtextxy(810, 140, "北京");
			break;
		case 16:
			i = 16;
			outtextxy(810, 140, "天津");
			break;
		}
	}
	else if (flag1 == 2)
		{
			switch (a)
			{
			case 0:
				j = 0;
				outtextxy(810, 180, "西安");
				break;
			case 1:
				j = 1;
				outtextxy(810, 180, "成都");
				break;
			case 2:
				j = 2;
				outtextxy(810, 180, "贵阳");
				break;
			case 3:
				j = 3;
				outtextxy(810, 180, "柳州");
				break;
			case 4:
				j = 4;
				outtextxy(810, 180, "郑州");
				break;
			case 5:
				j = 5;
				outtextxy(810, 180, "武汉");
				break;
			case 6:
				j = 6;
				outtextxy(810, 180, "株洲");
				break;
			case 7:
				j = 7;
				outtextxy(810, 180, "广州");
				break;
			case 8:
				j = 8;
				outtextxy(810, 180, "深圳");
				break;
			case 9:
				j = 9;
				outtextxy(810, 180, "徐州");
				break;
			case 10:
				j = 10;
				outtextxy(810, 180, "上海");
				break;
			case 11:
				j = 11;
				outtextxy(810, 180, "南昌");
				break;
			case 12:
				j = 12;
				outtextxy(810, 180, "福州");
				break;
			case 13:
				j = 13;
				outtextxy(810, 180, "兰州");
				break;
			case 14:
				j = 14;
				outtextxy(810, 180, "呼特");
				break;
			case 15:
				j = 15;
				outtextxy(810, 180, "北京");
				break;
			case 16:
				j = 16;
				outtextxy(810, 180, "天津");
				break;
			}
	}
}

void out(int a[],int num,int num1)
{
	settextcolor(BLACK);
	setfillcolor(BROWN);
	setrop2(R2_COPYPEN);
	solidrectangle(620, 420, 1000, 500);  //绘制输出最短路信息矩形框
	int t = 0;
	string s[17] = {"西安","成都","贵阳","柳州","郑州","武汉","株洲","广州","深圳","徐州","上海","南昌" ,"福州","兰州","呼和浩特" ,"北京","天津"};
	string s1;
	while (t < num)
	{
		s1 += s[a[t]];
		if(t<num-1)
		s1 += "->";
		t++;
	}
	const char* s2 = s1.data();
	outtextxy(620, 440, s2);
	outtextxy(620,500,"路径长度：");
	char num2[10] ;
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

	// 初始化图
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

	// 设置对称位置元素值
	for (i = 0; i < G->numVertexes; ++i) {
		for (j = i; j < G->numVertexes; ++j) {
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

void ShortPath_Floyd(MGraph G, Patharc P, ShortPathTable D) {
	int i, j, k;
	// 二重循环，初始化P, D
	for (i = 0; i < G.numVertexes; ++i) {
		for (j = 0; j < G.numVertexes; ++j) {
			D[i][j] = G.arc[i][j];
			P[i][j] = j;
		}
	}
	// 三重循环, Floyd algorithm
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

void PrintShortPath(MGraph G, Patharc P, ShortPathTable D,int i,int j) {
	int k,t=0;
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
	PrintShortPath(G, P, D,i,j);
}

void Floyd()
{
	initgraph(1000, 600);
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "图的最短路-Floyd");		// 使用 Windows API 修改窗口名称
	setbkcolor(BROWN);		//设置背景的颜色
	cleardevice();
	settextcolor(WHITE);	//设置字体的颜色
	settextstyle(20, 0, "楷体");//设置字体形式（高度，宽度，字体）
	setbkmode(TRANSPARENT);	//把字体背景颜色设为透明

	huizhi();
	mes();

	getchar();
	//关闭窗口，closegraph();
	closegraph();
}

1.	void Dijkstra_minTree(MGraph G, int v0, int p[V], int D[V]) {
2.	int final[V];//为各个顶点配置一个标记值，用于确认该顶点是否已经找到最短路径
3.	//对各数组进行初始化
4.	for (int v = 0; v < G.vexnum; v++) {
5.	final[v] = 0;
6.	D[v] = G.arcs[v0][v];
7.	p[v] = 0;
8.	}
9.	//由于以v0位下标的顶点为起始点，所以不用再判断
10.	D[v0] = 0;
11.	final[v0] = 1;
12.	int k = 0;
13.	for (int i = 0; i < G.vexnum; i++) {
14.	int min = INFINITY;
15.	//选择到各顶点权值最小的顶点，即为本次能确定最短路径的顶点
16.	for (int w = 0; w < G.vexnum; w++) {
17.	if (!final[w]) {
18.	if (D[w] < min) {
19.	k = w;
20.	min = D[w];
21.	}
22.	}
23.	}
24.	//设置该顶点的标志位为1，避免下次重复判断
25.	final[k] = 1;
26.	//对v0到各顶点的权值进行更新
27.	for (int w = 0; w < G.vexnum; w++) {
28.	if (!final[w] && (min + G.arcs[k][w] < D[w])) {
29.	D[w] = min + G.arcs[k][w];
30.	p[w] = k;//记录各个最短路径上存在的顶点
31.	}
32.	}
33.	}
34.	}

