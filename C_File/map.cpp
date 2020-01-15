#include<graphics.h>
#include<map.h>
#include<math.h>
#include<stdio.h>

//显示非root用户地图界面
void show_user_map(struct SCENIC *scenic)
{
	IMAGE map_img;															//定义图片结构体变量，存放地图
	IMAGE pic;																//存放景点照片
	MOUSEMSG mouse;															//定义鼠标信息结构体
	RECT rect = { 0,30,500,300 };											//定义景点介绍显示框
	extern int num_node;													//全局变量，景点个数
	int count = 0;															//计数器

	initgraph(1366, 900);													//初始化绘图框
	loadimage(&map_img, _T("../Picture/Xi'an_map1.jpg"));					//读入地图图片
	putimage(0, 0, &map_img);												//显示地图图片

	setfillcolor(RED);														//设置景点标记为红色
	while (TRUE)
	{
		mouse = GetMouseMsg();												//获取鼠标当前信息
		for (count = 0; count < num_node; count++)							//遍历查看鼠标是否在景点区域
		{
			if (in_circle(mouse.x, mouse.y, (scenic + count)->x, (scenic + count)->y))
			{
				outtextxy(0, 0, (scenic + count)->name);					//显示景点名称
				drawtext((scenic + count)->idt, &rect, DT_WORDBREAK);		//显示景点介绍
				loadimage(&pic, (scenic + count)->picture);					//加载景点照片
				putimage(0, 500, &pic);										//显示景点照片
				FlushMouseMsgBuffer();										//清空鼠标信息
				Sleep(500);													//延时显示				
				break;
			}
			else
			{
				cleardevice();												//清屏
				putimage(0, 0, &map_img);									//显示地图图片
			}
		}
		for (count = 0; count < num_node; count++)							//标记出所有景点
			fillcircle((scenic + count)->x, (scenic + count)->y, 5);
		if (mouse.uMsg == WM_LBUTTONDOWN)
		{
			if ((mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
				break;														//退出
			else if ((mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 560 && mouse.y <= 620))
			{
				find_way(scenic);											//寻路
				initgraph(1366, 900);										//初始化绘图框
				loadimage(&map_img, _T("../Picture/Xi'an_map1.jpg"));		//读入地图图片
				setfillcolor(RED);											//设置景点标记为红色
			}
		}
	}
	closegraph();

	return;
}

//检测鼠标坐标是否在景点信息显示有效范围内（半径为R的圆）,m 为鼠标坐标，s 为圆心坐标
bool in_circle(int m_x, int m_y, int s_x, int s_y)
{
	double l = 0.0;															//鼠标坐标到圆心的距离
	int x = m_x - s_x;
	int y = m_y - s_y;
	l = pow(x, 2) + pow(y, 2);												//计算鼠标坐标到圆心的距离的平方
	return (l > pow(R, 2) ? FALSE : TRUE);
}

//用Dijkstra算法找最短路径
void Dijkstra(struct SCENIC *scenic, int v0)
{
	struct DIJ dij[MAX_NODE];												//Dijkstra 算法所用结构体
	struct DIJ temp;														//跳板
	struct NODE* p = NULL;													//遍历邻接表所用指针
	extern int num_node;													//全局变量，记录景点数目
	int count = 0, i = 0, j = 0, k = 0;										//计数器
	MOUSEMSG mouse;															//定义鼠标信息结构体
	IMAGE map_img;															//定义图片结构体变量，存放地图
	IMAGE pic;																//存放景点照片
	RECT rect = { 0,30,500,300 };											//定义景点介绍显示框
	char float_str[10] = "\0";												//存放由float转化出的字符串，最短路程
	char shoutest[UNIT_SIZE] = "最短路程为：";								//输出最短路程用

	for (count = 0; count < MAX_NODE; count++)								//结构体初始化
	{
		dij[count].flag = 0;
		dij[count].journey = INFINITE_FLOAT;
		for (i = 0; i < MAX_NODE; i++)
			dij[count].route[i] = -1;
	}
	dij[v0].flag = 1;														//出发地v0初始化
	dij[v0].journey = 0.0;
	dij[v0].route[0] = v0;
	dij[v0].route[1] = -1;
	temp = dij[v0];
	for (i = 0; i < num_node - 1; i++)										//开始Dijkstra算法
	{
		for (j = 0; temp.route[j] != -1; j++)								//找到新的踏板
			continue;
		if (j != 0)
			j--;
		for (p = (scenic + temp.route[j])->head; p != NULL; p = p->next)	//遍历邻接表
		{																	//更新dij结构体
			if ((0 == dij[p->adjvex - 1].flag) && (temp.journey + p->weight < dij[p->adjvex - 1].journey))
			{
				dij[p->adjvex - 1].journey = temp.journey + p->weight;		//更新路程
				for (k = 0; temp.route[k] != -1; k++)						//更新路径
					dij[p->adjvex - 1].route[k] = temp.route[k];
				dij[p->adjvex - 1].route[k] = p->adjvex - 1;
				dij[p->adjvex - 1].route[k + 1] = -1;						//路径更新结束
			}
		}
		for (count = 0; count < num_node; count++)
			if (dij[count].flag == 0)
				break;
		for (j = count; count < num_node; count++)							//寻找新的踏板，路程最小的
		{
			if ((0 == dij[count].flag) && (dij[count].journey < dij[j].journey))
				j = count;
		}
		dij[j].flag = 1;													//已经找到一条最短路径
		temp = dij[j];														//初始化新的踏板temp
	}																		//Dijkstra 算法结束
	setlinecolor(BLUE);														//设置划线颜色为蓝
	setfillcolor(RED);														//设置填充颜色为红
	loadimage(&map_img, _T("../Picture/Xi'an_map2.jpg"));					//读入地图图片
	while (1)
	{
		mouse = GetMouseMsg();												//获取鼠标当前信息	
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
			return;															//鼠标左键按下退出
		for (count = 0; count < num_node; count++)							//遍历查看鼠标是否在景点区域
		{
			if (in_circle(mouse.x, mouse.y, (scenic + count)->x, (scenic + count)->y))
			{
				outtextxy(0, 0, (scenic + count)->name);					//显示景点名称
				drawtext((scenic + count)->idt, &rect, DT_WORDBREAK);		//显示景点介绍
				loadimage(&pic, (scenic + count)->picture);					//加载景点照片
				putimage(0, 500, &pic);										//显示景点照片
				for (i = j = 0; dij[count].route[i] != -1; i++)				//显示最短路径
				{
					fillcircle((scenic + dij[count].route[i])->x, (scenic + dij[count].route[i])->y, 10);
					line((scenic + dij[count].route[j])->x, (scenic + dij[count].route[j])->y, (scenic + dij[count].route[i])->x, (scenic + dij[count].route[i])->y);
					j = i;													//记录上一个点
				}
				_gcvt_s(float_str, 10, (double)dij[count].journey,4);		//将最短路程转换为字符串
				strcat_s(shoutest, float_str);								//拼接最短路程信息
				outtextxy(1000, 30, shoutest);								//显示最短路程信息
				strcpy_s(shoutest, _T("最短路程为："));						//复位
				FlushMouseMsgBuffer();										//清空鼠标信息
				Sleep(250);													//延时显示				
				break;
			}
			else
			{
				cleardevice();												//清屏
				putimage(0, 0, &map_img);									//显示地图图片
			}
		}
		for (count = 0; count < num_node; count++)							//标记出所有景点
			fillcircle((scenic + count)->x, (scenic + count)->y, 5);
	}
	return ;
}

//返回鼠标点击的景点值，从0开始
int chose_node(struct SCENIC* scenic)
{
	MOUSEMSG mouse;															//定义鼠标信息结构体
	IMAGE pic;																//存放景点照片
	IMAGE map_img;															//定义图片结构体变量，存放地图
	RECT rect = { 0,30,500,300 };											//定义景点介绍显示框
	extern int num_node;													//全局变量，景点个数
	int count = 0;															//计数器

	loadimage(&map_img, _T("../Picture/Xi'an_map2.jpg"));					//读入地图图片
	setfillcolor(RED);														//设置景点标记为红色
	while (TRUE)
	{
		outtextxy(1250, 0, _T("请选择点!"));									//输出提示文字
		mouse = GetMouseMsg();												//获取鼠标当前信息	
		if (mouse.uMsg == WM_LBUTTONDOWN)									//鼠标左键按下
		{
			if ((mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
				return -1;													//点击“退出”，返回-1
			else
				for (count = 0; count < num_node; count++)					//遍历查看鼠标是否在景点区域
					if (in_circle(mouse.x, mouse.y, (scenic + count)->x, (scenic + count)->y))
						return count;										//返回鼠标点击的景点
		}
		else
		{
			Sleep(10);														//延时放抖
			FlushMouseMsgBuffer();											//清空鼠标信息
		}
		for (count = 0; count < num_node; count++)							//遍历查看鼠标是否在景点区域
		{
			if (in_circle(mouse.x, mouse.y, (scenic + count)->x, (scenic + count)->y))
			{
				outtextxy(0, 0, (scenic + count)->name);					//显示景点名称
				drawtext((scenic + count)->idt, &rect, DT_WORDBREAK);		//显示景点介绍
				loadimage(&pic, (scenic + count)->picture);					//加载景点照片
				putimage(0, 500, &pic);										//显示景点照片
				FlushMouseMsgBuffer();										//清空鼠标信息
				Sleep(250);													//延时显示				
				break;
			}
			else
			{
				cleardevice();												//清屏
				putimage(0, 0, &map_img);									//显示地图图片
			}	
		}
		for (count = 0; count < num_node; count++)							//标记出所有景点
			fillcircle((scenic + count)->x, (scenic + count)->y, 5);
	}
}

//寻找最短路径
void find_way(struct SCENIC* scenic)
{
	int v0 = 0;																//记录开始节点

	initgraph(1366, 900);													//初始化绘图框
	loadimage(NULL, _T("../Picture/Xi'an_map2.jpg"));						//读入地图图片

	v0 = chose_node(scenic);
	Dijkstra(scenic, v0);													//寻找最短路径
	closegraph();															//关闭框
	return;
}
