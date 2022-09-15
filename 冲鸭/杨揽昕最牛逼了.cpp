//#include<iostream>

//#include<string>  
//using namespace std;
#include<stdio.h>
#include <graphics.h>//esayxͼ�ο�
#include<mmsystem.h>//������ý��ͷ�ļ�
#include<easyx.h>
#include<math.h>
#include<string.h>
#include<conio.h>
//#include<conio.h>//ʹ��getch����

#pragma comment(lib,"Winmm.lib")
#define maxint 32767
//����ͼ���ڽӾ���
typedef struct {
	char vexs[100];//�����
	int arcs[100][100];//����
	int vexnum, arcnum;//����ֵ����ֵ
	int x[100], y[100];//����Բ������
}amgraph;//���ж���ļ���

//��С�ߵĶ��㼯��
struct {
	char adjvex;//��ָ��Ķ���
	int lowcost;//Ȩֵ,=0 �����ڱ�ѡ���ļ���
}closeedge[100];//�±�䣬ָ�򶥵㲻��


void change()
{
	//��ȡ����
	HWND hnd = GetHWnd();
	//���ô���
	SetWindowText(hnd, "׼����ʼ����ķ������");
	//�������ڣ���ʾ�û�����
	MessageBox(hnd, "��ϲ���н�500w", "��ϲ", MB_OKCANCEL);
}

void draw_line(amgraph G, int i, int j)
{
	//	printf("%d %d %d %d %d %d",i,j, G.x[i], G.y[i], G.x[j], G.y[j]);
	line(G.x[i], G.y[i], G.x[j], G.y[j]);
	int a = G.arcs[i][j];
	char b;
	b = '0' + a;
	int X, Y;
	X = (G.x[i] + G.x[j]) / 2;
	Y = (G.y[i] + G.y[j]) / 2;
	outtextxy(X, Y, b);
	//printf("%d %d\n", X, Y);
}

void playBGM()
{
	//������,���ý���豸�ӿڷ���һ���ַ���������ָ��
	mciSendString("open ./��ũ.mp3", 0, 0, 0);//    ./����ǰ�ļ���·����
	//��������
	mciSendString("play ./��ũ.mp3", 0, 0, 0);//    ../��ʾ��ǰ�ļ��е���һ��Ŀ¼
	//�ر�����;
	//Sleep(3000);//�ӳ�����
	//mciSendString("close .dylanf - ��ũ��������ٰ棩.MP3", 0, 0, 0);
}

//��λ����
int locatvax(amgraph G, char v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v)
			return i;//Ѱ�Ҷ���v�ı��
	}
	return -1;
}

void draw_graph(amgraph& G, int i, int k)
{
	while (1) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			G.x[i] = msg.x;
			G.y[i] = msg.y;
			//printf("%d %d\n", G.x[i], G.y[i]);
			setfillcolor(RGB(203, 149, 248));
			fillcircle(msg.x, msg.y, 20);
			settextcolor(RGB(45, 196, 205));
			settextstyle(30, 0, "����");
			setbkmode(TRANSPARENT);
			outtextxy(msg.x - 7, msg.y - 17, G.vexs[i]);
			break;
		}
	}
}

//�����ڽ׾���
void create(amgraph& G) {
	int i, j, k;
	//���붥��
	printf("please input the number of vex and arc seperate turn wist space key:\n");
	HWND hnd = GetHWnd();
	MessageBox(hnd, "�������ܶ��������ܱ���", "��ʾ", MB_OKCANCEL);
	scanf_s("%d %d", &G.vexnum, &G.arcnum);
	printf("\n");
	getchar();//���ջ��з� 
//	cout << "please input the number of vex and arc seperate turn wist space key:" << endl;
//	cin >> G.vexnum >> G.arcnum;
//	cout << endl;

//	cout << "please input the name of vaxs:" << endl;
	printf("please input the name of vaxs:\n");
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("please input the %d name of vex :\n", (i + 1));
		scanf_s("%c", &G.vexs[i]);
		getchar();
		//	cout << "please input the " << (i + 1) << " name of vex" << endl;
		//	cin >> G.vexs[i];//���붥��
		//�����Ϣ
		MessageBox(hnd, "����ͼ��ѡ�񶥵�λ��", "��ʾ", MB_OKCANCEL);
		draw_graph(G, i, 0);
		//	printf("%d %d", G.x[i], G.y[i]);
	}
	MessageBox(hnd, "������ɶԶ��������", "��ϲ", MB_OKCANCEL);
	//cout << endl;
	printf("\n");

	//�����(��ʼ��,������Ϊ���ֵ��
	for (int i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.arcnum; j++)
		{
			G.arcs[i][j] = maxint;
		}

	//����
	//cout << "please input the arc weight and the corresponding vaxs as 12  a b" << endl;//��ʾ����ߵ���ʽ
	printf("please input the arc weight and the corresponding vaxs as 12  a b\n");
	MessageBox(hnd, "������Ȩֵ�����㣬����12 a b", "����", MB_OKCANCEL);
	for (k = 0; k < G.arcnum; k++)
	{
		int weight;
		char v1, v2;
		printf("please input the weight and two vex of %d arc\n", k + 1);
		scanf_s("%d", &weight);
		getchar();
		v1 = getchar();
		getchar();
		v2 = getchar();
		getchar();
		//	cout << "please input the weight and two vex of " << (k + 1) << " arc" << endl;
		//	cin >> weight >> v1 >> v2;//����Ȩֵ����������
		i = locatvax(G, v1);
		j = locatvax(G, v2);
		//printf("%d %d %d %d %d %d\n", i, j, G.x[i], G.y[i], G.x[j], G.y[j]);
		G.arcs[i][j] = weight;
		G.arcs[j][i] = G.arcs[i][j];
		draw_line(G, i, j);
		//	cout<<v1<<v2<<G.arcs[i][j];
	}
	MessageBox(hnd, "������ɶԱߵ�����", "��ϲ", MB_OKCANCEL);
}


//����Сֵ������һ������С��ֵ
int MIN(amgraph G)
{
	int i;
	int index = -1;//֮�󷵻ص�ֵ,��С�߶�Ӧ�����
	int MIN = maxint;//��ʱ��Сֵ=���ֵ���жԱ�
	for (int i = 0; i < G.vexnum; i++)
	{
		if (MIN > closeedge[i].lowcost && closeedge[i].lowcost != 0)//�ҳ���С�ģ�����ͬһ�����ϵ�
		{
			MIN = closeedge[i].lowcost;
			index = i;
		}
	}
	//	cout<<index<<endl;
	return index;
}

//void tc(amgraph G, int k)
//{
//	while (1) {
//		setfillcolor(RGB(138, 226, 138));
//		fillcircle(G.x[k], G.y[k], 20);
//		break;
//	}
//}

//prim�㷨
void prim(amgraph G, char u) //uΪ��ʼ����
{
	int k, j, i, q = 0;
	char u0, v0;
	k = locatvax(G, u);//Ѱ�ҵ�u�ı��
	for (j = 0; j < G.vexnum; ++j)//���б���������������
	{
		if (j != k) {
			//��ʼ��closeedge
			closeedge[j].adjvex = u;//����Ϊu,��u��Ӧ�ı߱�Ϊ
			closeedge[j].lowcost = G.arcs[k][j];//����u��Ӧ�Ķ�������Ӧ��Ȩֵ
		}
		//����ÿһ�м���һ���㣬��̱ߵļ��Ͼ���
	}
	closeedge[k].lowcost = 0;//���뼯��u,��������G.arcs[i][j]����С�ˣ�closeedge��i�������ˣ�
	//��k����
	setfillcolor(RGB(138, 226, 138));
	fillcircle(G.x[k], G.y[k], 20);
	Sleep(500);
	//	MOUSEMSG msg = GetMouseMsg();
	for (i = 1; i < G.vexnum; i++)
	{
		//����k
	//	tc(G, k);
	//	cout<<k<<endl;
		k = MIN(G);//�ҳ�����k�����ӵ���һ���������
		u0 = closeedge[k].adjvex;//����k
		v0 = G.vexs[k];//��һ������
		int a, b;
		a = locatvax(G, v0);
		b = locatvax(G, u0);
		q = q + G.arcs[a][b];
		//	cout << u0 << endl;
		//	cout << v0 << endl;
		//	cout << "arc : " << u0 << "-->" << v0 << endl;
		printf("arc %c --> %c\n", u0, v0);
		setlinecolor(RED);
		draw_line(G, a, b);
		closeedge[k].lowcost = 0;
		///����close edge����
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[k][j] < closeedge[j].lowcost)
			{
				closeedge[j].adjvex = G.vexs[k];//���ڽӵ�
				closeedge[j].lowcost = G.arcs[k][j];//��Ȩֵ
			}
		}
		setfillcolor(RGB(138, 226, 138));
		fillcircle(G.x[k], G.y[k], 20);
		Sleep(2000);
	}
	//	cout << q << endl;
	//char t = '0';
	//t = '0' +q;
	//settextstyle(40, 0, "����");
	//settextcolor(RGB(166, 96, 41));
	//outtextxy(340, 500,t);
	printf("%d\n", q);
}
int main()
{
	initgraph(680, 750, SHOWCONSOLE);//��������,ȷ�����ڴ�С,��ʾ����̨
	playBGM();
	//setbkcolor(WHITE);
	//cleardevice();
	IMAGE img;//����ͼƬ����
	//loadimage(&img, "C:\\Users\\86182\\source\\repos\\Project3/����ĺ���.JPG");//����ͼƬ����ͼƬ�����ڶ���ı�����load
	loadimage(&img, "./����ĺ���.JPG");//loadimage(&img, "./����ĺ���.JPG",250,250);//��ͼƬ��С��Ϊ250*250
	putimage(0, 0, &img);//���ͼƬ
	change();
	//setbkcolor(YELLOW);//ͨ����ɫ���ñ���
	//cleardevice();//����
	//��������
	settextcolor(RGB(251, 114, 153));//����������ɫ
	//fillrectangle(50, 50, 550, 100);//������,���Ͻ����������½�����
	// char arr[]="�����Ů��"��//�����ַ���
	// int width=300/2-textwidth(arr)/2;//���һ���ȥ���ַ������ȣ���ռ���ظ���ȣ��ַ�����һ����λ��x����ȷ��
	// int height=50/2-textheight(arr)/2;//�߶�һ���ȥ���ַ����߶ȣ��ַ�����һ��λ�ø߶�ȷ��
	// outtextxy(width+200,height+50,arr);//���Ӽ�������ַ�����ʼx����߼Ӽ�������ַ�����ʼ�߶�
	//����������ʽ����С������
	settextstyle(50, 0, "����");//�߶ȣ���С������ȣ�<����>
	//��ȥ���ֱ��������ñ���ģʽ��
	setbkmode(TRANSPARENT);//transparent͸��
	outtextxy(200, 50, "����ķ����");//x,y,"",ָ��λ������ַ���
	amgraph G;
	create(G);
	Sleep(1000);
	//	cout << endl;
	printf("\n");
	prim(G, 'a');
	//	cout << endl;
	printf("\n");
	_getch();
	closegraph();//�رմ���
	getchar();//��ֹ����
	return 0;
}