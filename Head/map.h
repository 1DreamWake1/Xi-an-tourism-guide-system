#ifndef MAP_H
#define MAP_H

#include<read_map.h>

#define R 10													//��괥����ϢԲ�뾶
#define INFINITE_FLOAT	0XFFFF									//��ʾ��Ϊ����Զ

struct DIJ {													//Dijkstra �㷨���ýṹ��
	int flag = 0;												//��־�õ��Ƿ�Ϊ���·��
	float journey = INFINITE_FLOAT;								//��¼���·����·��
	int route[MAX_NODE] = { -1 };								//��¼·��������·���ϵĵ���±꣬��-1Ϊ����
};

void show_user_map(struct SCENIC*);								//��ʾ��root�û���ͼ����
bool in_circle(int, int, int, int);								//�����������Ƿ��ھ�����Ϣ��ʾ��Ч��Χ�ڣ��뾶ΪR��Բ��,m Ϊ������꣬s ΪԲ������
void Dijkstra(struct SCENIC*, int);								//��Dijkstra�㷨�����·��
int chose_node(struct SCENIC*);									//����������ľ���ֵ����0��ʼ
void find_way(struct SCENIC*);									//Ѱ�����·��

#endif
