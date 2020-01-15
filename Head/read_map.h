#ifndef READ_MAP_H
#define READ_MAP_H

#include<graphics.h>
#include<stdio.h>

#define UNIT_SIZE 50											//��λ��С
#define MAX_NODE  20											//�ڽӱ��С�����洢���ٸ�������Ϣ

//�ڽӱ��ڽӽ��ṹ��
struct NODE {
	int adjvex = 0;												//�ڽӵ�
	float weight = 0.0;											//�û���Ȩ��
	struct NODE* next = NULL;
};
//�ڽӱ�Ľṹ������
struct SCENIC {
	char name[UNIT_SIZE] = "\0";								//��������
	int x = 0, y = 0;											//��ͼ�е�����
	char introduction[UNIT_SIZE] = "\0";						//��������ļ�·��
	char idt[12 * UNIT_SIZE] = "\0";							//������ܣ�����600KB�ռ䣬�������300������
	char picture[UNIT_SIZE] = "\0";								//����ͼƬ�ļ�·��
	struct NODE* head = NULL;									//�ڽӵ�ͷָ��
};

void Read_Map(struct SCENIC*);									//���ļ��ж�ȡ������Ϣ������ľ����ڽӱ���
void Check_Read_Map(struct SCENIC*);							//�������ӡ�map_msg.txt���͡�introduce.txt���������Ϣ

#endif
