#include<graphics.h>
#include<map.h>
#include<math.h>
#include<stdio.h>

//��ʾ��root�û���ͼ����
void show_user_map(struct SCENIC *scenic)
{
	IMAGE map_img;															//����ͼƬ�ṹ���������ŵ�ͼ
	IMAGE pic;																//��ž�����Ƭ
	MOUSEMSG mouse;															//���������Ϣ�ṹ��
	RECT rect = { 0,30,500,300 };											//���徰�������ʾ��
	extern int num_node;													//ȫ�ֱ������������
	int count = 0;															//������

	initgraph(1366, 900);													//��ʼ����ͼ��
	loadimage(&map_img, _T("../Picture/Xi'an_map1.jpg"));					//�����ͼͼƬ
	putimage(0, 0, &map_img);												//��ʾ��ͼͼƬ

	setfillcolor(RED);														//���þ�����Ϊ��ɫ
	while (TRUE)
	{
		mouse = GetMouseMsg();												//��ȡ��굱ǰ��Ϣ
		for (count = 0; count < num_node; count++)							//�����鿴����Ƿ��ھ�������
		{
			if (in_circle(mouse.x, mouse.y, (scenic + count)->x, (scenic + count)->y))
			{
				outtextxy(0, 0, (scenic + count)->name);					//��ʾ��������
				drawtext((scenic + count)->idt, &rect, DT_WORDBREAK);		//��ʾ�������
				loadimage(&pic, (scenic + count)->picture);					//���ؾ�����Ƭ
				putimage(0, 500, &pic);										//��ʾ������Ƭ
				FlushMouseMsgBuffer();										//��������Ϣ
				Sleep(500);													//��ʱ��ʾ				
				break;
			}
			else
			{
				cleardevice();												//����
				putimage(0, 0, &map_img);									//��ʾ��ͼͼƬ
			}
		}
		for (count = 0; count < num_node; count++)							//��ǳ����о���
			fillcircle((scenic + count)->x, (scenic + count)->y, 5);
		if (mouse.uMsg == WM_LBUTTONDOWN)
		{
			if ((mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
				break;														//�˳�
			else if ((mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 560 && mouse.y <= 620))
			{
				find_way(scenic);											//Ѱ·
				initgraph(1366, 900);										//��ʼ����ͼ��
				loadimage(&map_img, _T("../Picture/Xi'an_map1.jpg"));		//�����ͼͼƬ
				setfillcolor(RED);											//���þ�����Ϊ��ɫ
			}
		}
	}
	closegraph();

	return;
}

//�����������Ƿ��ھ�����Ϣ��ʾ��Ч��Χ�ڣ��뾶ΪR��Բ��,m Ϊ������꣬s ΪԲ������
bool in_circle(int m_x, int m_y, int s_x, int s_y)
{
	double l = 0.0;															//������굽Բ�ĵľ���
	int x = m_x - s_x;
	int y = m_y - s_y;
	l = pow(x, 2) + pow(y, 2);												//����������굽Բ�ĵľ����ƽ��
	return (l > pow(R, 2) ? FALSE : TRUE);
}

//��Dijkstra�㷨�����·��
void Dijkstra(struct SCENIC *scenic, int v0)
{
	struct DIJ dij[MAX_NODE];												//Dijkstra �㷨���ýṹ��
	struct DIJ temp;														//����
	struct NODE* p = NULL;													//�����ڽӱ�����ָ��
	extern int num_node;													//ȫ�ֱ�������¼������Ŀ
	int count = 0, i = 0, j = 0, k = 0;										//������
	MOUSEMSG mouse;															//���������Ϣ�ṹ��
	IMAGE map_img;															//����ͼƬ�ṹ���������ŵ�ͼ
	IMAGE pic;																//��ž�����Ƭ
	RECT rect = { 0,30,500,300 };											//���徰�������ʾ��
	char float_str[10] = "\0";												//�����floatת�������ַ��������·��
	char shoutest[UNIT_SIZE] = "���·��Ϊ��";								//������·����

	for (count = 0; count < MAX_NODE; count++)								//�ṹ���ʼ��
	{
		dij[count].flag = 0;
		dij[count].journey = INFINITE_FLOAT;
		for (i = 0; i < MAX_NODE; i++)
			dij[count].route[i] = -1;
	}
	dij[v0].flag = 1;														//������v0��ʼ��
	dij[v0].journey = 0.0;
	dij[v0].route[0] = v0;
	dij[v0].route[1] = -1;
	temp = dij[v0];
	for (i = 0; i < num_node - 1; i++)										//��ʼDijkstra�㷨
	{
		for (j = 0; temp.route[j] != -1; j++)								//�ҵ��µ�̤��
			continue;
		if (j != 0)
			j--;
		for (p = (scenic + temp.route[j])->head; p != NULL; p = p->next)	//�����ڽӱ�
		{																	//����dij�ṹ��
			if ((0 == dij[p->adjvex - 1].flag) && (temp.journey + p->weight < dij[p->adjvex - 1].journey))
			{
				dij[p->adjvex - 1].journey = temp.journey + p->weight;		//����·��
				for (k = 0; temp.route[k] != -1; k++)						//����·��
					dij[p->adjvex - 1].route[k] = temp.route[k];
				dij[p->adjvex - 1].route[k] = p->adjvex - 1;
				dij[p->adjvex - 1].route[k + 1] = -1;						//·�����½���
			}
		}
		for (count = 0; count < num_node; count++)
			if (dij[count].flag == 0)
				break;
		for (j = count; count < num_node; count++)							//Ѱ���µ�̤�壬·����С��
		{
			if ((0 == dij[count].flag) && (dij[count].journey < dij[j].journey))
				j = count;
		}
		dij[j].flag = 1;													//�Ѿ��ҵ�һ�����·��
		temp = dij[j];														//��ʼ���µ�̤��temp
	}																		//Dijkstra �㷨����
	setlinecolor(BLUE);														//���û�����ɫΪ��
	setfillcolor(RED);														//���������ɫΪ��
	loadimage(&map_img, _T("../Picture/Xi'an_map2.jpg"));					//�����ͼͼƬ
	while (1)
	{
		mouse = GetMouseMsg();												//��ȡ��굱ǰ��Ϣ	
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
			return;															//�����������˳�
		for (count = 0; count < num_node; count++)							//�����鿴����Ƿ��ھ�������
		{
			if (in_circle(mouse.x, mouse.y, (scenic + count)->x, (scenic + count)->y))
			{
				outtextxy(0, 0, (scenic + count)->name);					//��ʾ��������
				drawtext((scenic + count)->idt, &rect, DT_WORDBREAK);		//��ʾ�������
				loadimage(&pic, (scenic + count)->picture);					//���ؾ�����Ƭ
				putimage(0, 500, &pic);										//��ʾ������Ƭ
				for (i = j = 0; dij[count].route[i] != -1; i++)				//��ʾ���·��
				{
					fillcircle((scenic + dij[count].route[i])->x, (scenic + dij[count].route[i])->y, 10);
					line((scenic + dij[count].route[j])->x, (scenic + dij[count].route[j])->y, (scenic + dij[count].route[i])->x, (scenic + dij[count].route[i])->y);
					j = i;													//��¼��һ����
				}
				_gcvt_s(float_str, 10, (double)dij[count].journey,4);		//�����·��ת��Ϊ�ַ���
				strcat_s(shoutest, float_str);								//ƴ�����·����Ϣ
				outtextxy(1000, 30, shoutest);								//��ʾ���·����Ϣ
				strcpy_s(shoutest, _T("���·��Ϊ��"));						//��λ
				FlushMouseMsgBuffer();										//��������Ϣ
				Sleep(250);													//��ʱ��ʾ				
				break;
			}
			else
			{
				cleardevice();												//����
				putimage(0, 0, &map_img);									//��ʾ��ͼͼƬ
			}
		}
		for (count = 0; count < num_node; count++)							//��ǳ����о���
			fillcircle((scenic + count)->x, (scenic + count)->y, 5);
	}
	return ;
}

//����������ľ���ֵ����0��ʼ
int chose_node(struct SCENIC* scenic)
{
	MOUSEMSG mouse;															//���������Ϣ�ṹ��
	IMAGE pic;																//��ž�����Ƭ
	IMAGE map_img;															//����ͼƬ�ṹ���������ŵ�ͼ
	RECT rect = { 0,30,500,300 };											//���徰�������ʾ��
	extern int num_node;													//ȫ�ֱ������������
	int count = 0;															//������

	loadimage(&map_img, _T("../Picture/Xi'an_map2.jpg"));					//�����ͼͼƬ
	setfillcolor(RED);														//���þ�����Ϊ��ɫ
	while (TRUE)
	{
		outtextxy(1250, 0, _T("��ѡ���!"));									//�����ʾ����
		mouse = GetMouseMsg();												//��ȡ��굱ǰ��Ϣ	
		if (mouse.uMsg == WM_LBUTTONDOWN)									//����������
		{
			if ((mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
				return -1;													//������˳���������-1
			else
				for (count = 0; count < num_node; count++)					//�����鿴����Ƿ��ھ�������
					if (in_circle(mouse.x, mouse.y, (scenic + count)->x, (scenic + count)->y))
						return count;										//����������ľ���
		}
		else
		{
			Sleep(10);														//��ʱ�Ŷ�
			FlushMouseMsgBuffer();											//��������Ϣ
		}
		for (count = 0; count < num_node; count++)							//�����鿴����Ƿ��ھ�������
		{
			if (in_circle(mouse.x, mouse.y, (scenic + count)->x, (scenic + count)->y))
			{
				outtextxy(0, 0, (scenic + count)->name);					//��ʾ��������
				drawtext((scenic + count)->idt, &rect, DT_WORDBREAK);		//��ʾ�������
				loadimage(&pic, (scenic + count)->picture);					//���ؾ�����Ƭ
				putimage(0, 500, &pic);										//��ʾ������Ƭ
				FlushMouseMsgBuffer();										//��������Ϣ
				Sleep(250);													//��ʱ��ʾ				
				break;
			}
			else
			{
				cleardevice();												//����
				putimage(0, 0, &map_img);									//��ʾ��ͼͼƬ
			}	
		}
		for (count = 0; count < num_node; count++)							//��ǳ����о���
			fillcircle((scenic + count)->x, (scenic + count)->y, 5);
	}
}

//Ѱ�����·��
void find_way(struct SCENIC* scenic)
{
	int v0 = 0;																//��¼��ʼ�ڵ�

	initgraph(1366, 900);													//��ʼ����ͼ��
	loadimage(NULL, _T("../Picture/Xi'an_map2.jpg"));						//�����ͼͼƬ

	v0 = chose_node(scenic);
	Dijkstra(scenic, v0);													//Ѱ�����·��
	closegraph();															//�رտ�
	return;
}
