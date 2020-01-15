#ifndef MAP_H
#define MAP_H

#include<read_map.h>

#define R 10													//鼠标触发信息圆半径
#define INFINITE_FLOAT	0XFFFF									//表示弧为无穷远

struct DIJ {													//Dijkstra 算法所用结构体
	int flag = 0;												//标志该点是否为最短路径
	float journey = INFINITE_FLOAT;								//记录最短路径的路程
	int route[MAX_NODE] = { -1 };								//记录路径，存入路径上的点的下标，以-1为结束
};

void show_user_map(struct SCENIC*);								//显示非root用户地图界面
bool in_circle(int, int, int, int);								//检测鼠标坐标是否在景点信息显示有效范围内（半径为R的圆）,m 为鼠标坐标，s 为圆心坐标
void Dijkstra(struct SCENIC*, int);								//用Dijkstra算法找最短路径
int chose_node(struct SCENIC*);									//返回鼠标点击的景点值，从0开始
void find_way(struct SCENIC*);									//寻找最短路径

#endif
