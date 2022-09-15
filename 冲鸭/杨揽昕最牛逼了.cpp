//#include<iostream>

//#include<string>  
//using namespace std;
#include<stdio.h>
#include <graphics.h>//esayx图形库
#include<mmsystem.h>//包含多媒体头文件
#include<easyx.h>
#include<math.h>
#include<string.h>
#include<conio.h>
//#include<conio.h>//使用getch（）

#pragma comment(lib,"Winmm.lib")
#define maxint 32767
//定义图的邻接矩阵
typedef struct {
	char vexs[100];//定点表
	int arcs[100][100];//方阵
	int vexnum, arcnum;//顶点值，边值
	int x[100], y[100];//顶点圆心坐标
}amgraph;//所有顶点的集合

//最小边的顶点集合
struct {
	char adjvex;//被指向的顶点
	int lowcost;//权值,=0 点属于被选出的集合
}closeedge[100];//下标变，指向顶点不变


void change()
{
	//获取窗口
	HWND hnd = GetHWnd();
	//设置窗口
	SetWindowText(hnd, "准备开始普里姆运算辣");
	//弹出窗口，提示用户操作
	MessageBox(hnd, "恭喜你中奖500w", "惊喜", MB_OKCANCEL);
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
	//打开音乐,向多媒体设备接口发送一个字符串，代表指令
	mciSendString("open ./卡农.mp3", 0, 0, 0);//    ./代表当前文件夹路径下
	//播放音乐
	mciSendString("play ./卡农.mp3", 0, 0, 0);//    ../表示当前文件夹的上一级目录
	//关闭音乐;
	//Sleep(3000);//延迟三秒
	//mciSendString("close .dylanf - 卡农（经典钢琴版）.MP3", 0, 0, 0);
}

//定位顶点
int locatvax(amgraph G, char v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v)
			return i;//寻找顶点v的编号
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
			settextstyle(30, 0, "楷体");
			setbkmode(TRANSPARENT);
			outtextxy(msg.x - 7, msg.y - 17, G.vexs[i]);
			break;
		}
	}
}

//创建邻阶矩阵
void create(amgraph& G) {
	int i, j, k;
	//输入顶点
	printf("please input the number of vex and arc seperate turn wist space key:\n");
	HWND hnd = GetHWnd();
	MessageBox(hnd, "请输入总顶点数和总边数", "提示", MB_OKCANCEL);
	scanf_s("%d %d", &G.vexnum, &G.arcnum);
	printf("\n");
	getchar();//吸收换行符 
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
		//	cin >> G.vexs[i];//输入顶点
		//鼠标消息
		MessageBox(hnd, "请在图上选择顶点位置", "提示", MB_OKCANCEL);
		draw_graph(G, i, 0);
		//	printf("%d %d", G.x[i], G.y[i]);
	}
	MessageBox(hnd, "你已完成对顶点的设置", "恭喜", MB_OKCANCEL);
	//cout << endl;
	printf("\n");

	//输入边(初始化,边设置为最大值）
	for (int i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.arcnum; j++)
		{
			G.arcs[i][j] = maxint;
		}

	//输入
	//cout << "please input the arc weight and the corresponding vaxs as 12  a b" << endl;//提示输入边的形式
	printf("please input the arc weight and the corresponding vaxs as 12  a b\n");
	MessageBox(hnd, "请输入权值及两点，形似12 a b", "提醒", MB_OKCANCEL);
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
		//	cin >> weight >> v1 >> v2;//输入权值及两个顶点
		i = locatvax(G, v1);
		j = locatvax(G, v2);
		//printf("%d %d %d %d %d %d\n", i, j, G.x[i], G.y[i], G.x[j], G.y[j]);
		G.arcs[i][j] = weight;
		G.arcs[j][i] = G.arcs[i][j];
		draw_line(G, i, j);
		//	cout<<v1<<v2<<G.arcs[i][j];
	}
	MessageBox(hnd, "你已完成对边的设置", "恭喜", MB_OKCANCEL);
}


//找最小值，即这一行上最小的值
int MIN(amgraph G)
{
	int i;
	int index = -1;//之后返回的值,最小边对应的序号
	int MIN = maxint;//临时最小值=最大值进行对比
	for (int i = 0; i < G.vexnum; i++)
	{
		if (MIN > closeedge[i].lowcost && closeedge[i].lowcost != 0)//找出最小的，不在同一个集合的
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

//prim算法
void prim(amgraph G, char u) //u为起始顶点
{
	int k, j, i, q = 0;
	char u0, v0;
	k = locatvax(G, u);//寻找到u的编号
	for (j = 0; j < G.vexnum; ++j)//进行遍历（遍历次数）
	{
		if (j != k) {
			//初始化closeedge
			closeedge[j].adjvex = u;//顶点为u,将u对应的边变为
			closeedge[j].lowcost = G.arcs[k][j];//所有u对应的顶点所对应的权值
		}
		//对于每一行加入一个点，最短边的集合矩阵
	}
	closeedge[k].lowcost = 0;//放入集合u,不会再有G.arcs[i][j]比他小了（closeedge【i】不变了）
	//从k出发
	setfillcolor(RGB(138, 226, 138));
	fillcircle(G.x[k], G.y[k], 20);
	Sleep(500);
	//	MOUSEMSG msg = GetMouseMsg();
	for (i = 1; i < G.vexnum; i++)
	{
		//更新k
	//	tc(G, k);
	//	cout<<k<<endl;
		k = MIN(G);//找出顶点k所连接的另一个顶点序号
		u0 = closeedge[k].adjvex;//顶点k
		v0 = G.vexs[k];//另一个顶点
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
		///更新close edge数组
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[k][j] < closeedge[j].lowcost)
			{
				closeedge[j].adjvex = G.vexs[k];//换邻接点
				closeedge[j].lowcost = G.arcs[k][j];//换权值
			}
		}
		setfillcolor(RGB(138, 226, 138));
		fillcircle(G.x[k], G.y[k], 20);
		Sleep(2000);
	}
	//	cout << q << endl;
	//char t = '0';
	//t = '0' +q;
	//settextstyle(40, 0, "楷体");
	//settextcolor(RGB(166, 96, 41));
	//outtextxy(340, 500,t);
	printf("%d\n", q);
}
int main()
{
	initgraph(680, 750, SHOWCONSOLE);//创建窗口,确定窗口大小,显示控制台
	playBGM();
	//setbkcolor(WHITE);
	//cleardevice();
	IMAGE img;//定义图片变量
	//loadimage(&img, "C:\\Users\\86182\\source\\repos\\Project3/酒醉的蝴蝶.JPG");//加载图片，把图片保存在定义的变量中load
	loadimage(&img, "./酒醉的蝴蝶.JPG");//loadimage(&img, "./酒醉的蝴蝶.JPG",250,250);//将图片大小变为250*250
	putimage(0, 0, &img);//输出图片
	change();
	//setbkcolor(YELLOW);//通过颜色设置背景
	//cleardevice();//清屏
	//绘制文字
	settextcolor(RGB(251, 114, 153));//设置文字颜色
	//fillrectangle(50, 50, 550, 100);//画矩形,左上角坐标与右下角坐标
	// char arr[]="姐就是女王"；//定义字符串
	// int width=300/2-textwidth(arr)/2;//宽度一半减去求字符串长度，所占像素个宽度，字符串第一个字位置x坐标确定
	// int height=50/2-textheight(arr)/2;//高度一半减去求字符串高度，字符串第一层位置高度确定
	// outtextxy(width+200,height+50,arr);//框宽加间隔——字符串起始x，宽高加间隔——字符串起始高度
	//设置文字样式，大小，字体
	settextstyle(50, 0, "楷体");//高度（大小），宽度，<字体>
	//消去文字背景（设置背景模式）
	setbkmode(TRANSPARENT);//transparent透明
	outtextxy(200, 50, "普里姆运算");//x,y,"",指定位置输出字符串
	amgraph G;
	create(G);
	Sleep(1000);
	//	cout << endl;
	printf("\n");
	prim(G, 'a');
	//	cout << endl;
	printf("\n");
	_getch();
	closegraph();//关闭窗口
	getchar();//防止闪退
	return 0;
}