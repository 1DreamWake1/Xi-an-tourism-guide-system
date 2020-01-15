#ifndef READ_MAP_H
#define READ_MAP_H

#include<graphics.h>
#include<stdio.h>

#define UNIT_SIZE 50											//单位大小
#define MAX_NODE  20											//邻接表大小，最大存储多少个景点信息

//邻接表邻接结点结构体
struct NODE {
	int adjvex = 0;												//邻接点
	float weight = 0.0;											//该弧的权重
	struct NODE* next = NULL;
};
//邻接表的结构体数组
struct SCENIC {
	char name[UNIT_SIZE] = "\0";								//景点名称
	int x = 0, y = 0;											//地图中的坐标
	char introduction[UNIT_SIZE] = "\0";						//景点介绍文件路径
	char idt[12 * UNIT_SIZE] = "\0";							//景点介绍，开辟600KB空间，最多容纳300个汉字
	char picture[UNIT_SIZE] = "\0";								//景点图片文件路径
	struct NODE* head = NULL;									//邻接点头指针
};

void Read_Map(struct SCENIC*);									//从文件中读取景点信息到传入的景点邻接表中
void Check_Read_Map(struct SCENIC*);							//检测输出从“map_msg.txt”和“introduce.txt”读入的信息

#endif
