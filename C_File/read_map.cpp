#include<stdlib.h>
#include<read_map.h>
#include<graphics.h>

//���ļ��ж�ȡ������Ϣ������ľ����ڽӱ���
void Read_Map(struct SCENIC *scenic)
{
	FILE* msg = NULL;																//��ȡ��map_msg.txt�����ļ�ָ��
	FILE* p_introduce = NULL;														//��ȡ��introduce.txt�����ļ�ָ��
	struct NODE *p, *q;																//�����ڽӱ�ʱ�õĹ���ָ��
	int count;																		//������
	extern int num_node;															//ȫ�ֱ�������¼������

	fopen_s(&msg, "../Data/map_msg.txt", "r");										//���ļ���map_msg.txt��
	if (msg == NULL)
		exit(0);
	for (count = 0; (EOF != fscanf_s(msg, "%s", (scenic+count)->name, UNIT_SIZE) && count < MAX_NODE); count++)	//��ȡ��map_msg.txt���ļ������뾰������
	{
		fscanf_s(msg, "%d", &((scenic + count)->x));								//���뾰���X����
		fscanf_s(msg, "%d", &((scenic + count)->y));								//���뾰���Y����
		fscanf_s(msg, "%s", (scenic + count)->introduction, UNIT_SIZE);				//���뾰������ļ���·��
		fscanf_s(msg, "%s", (scenic + count)->picture, UNIT_SIZE);					//���뾰��ͼƬ�ļ���·��
		fopen_s(&p_introduce, (scenic + count)->introduction, "r");					//�򿪽����ļ�
		if (p_introduce == NULL)
			exit(0);
		fscanf_s(p_introduce, "%s", (scenic + count)->idt, 12 * UNIT_SIZE);			//����������ļ�����
		fclose(p_introduce);														//�رվ�������ļ�
		for (q = p = (scenic + count)->head = (struct NODE*)malloc(sizeof(struct NODE)); TRUE;)					//�����ڽӵ㣬����Ȩ
		{
			if (p == NULL)
				exit(0);
			fscanf_s(msg, "%d", &(p->adjvex));							//�����ڽӵ㣨����
			fscanf_s(msg, "%f", &(p->weight));							//���뻡��Ȩ��
			if (p->adjvex == 0)											//�������ڽӵ�
			{
				q->next = NULL;											//���һ���ڵ��ַ����Ϊ��ָ��
				free(p);												//�ͷŵ��սڵ�
				break;
			}
			q = p;														//��qָ�������һ���ڵ��ַ
			p->next = (struct NODE*)malloc(sizeof(struct NODE));		//������һ���ڽӵ㣨����
			p = p->next;
		}
	}
	num_node = count;													//��¼������
	fclose(msg);														//�رա�map_msg.txt�����ļ�ָ��
	return ;
}

//�������ӡ�map_msg.txt���͡�introduce.txt���������Ϣ
void Check_Read_Map(struct SCENIC *scenic)
{
	struct NODE* t;
	extern int num_node;

	for (int i = 0; i < num_node; i++)
	{
		printf("%-2d %s %d %d %s %s\n", i + 1, (scenic + i)->name, (scenic + i)->x, (scenic + i)->y, (scenic + i)->introduction, (scenic + i)->picture);
		//printf("%s\n", (scenic + i)->idt);
		t = (scenic + i)->head;
		while (t != NULL)
		{
			printf("	(%d %.2f)", t->adjvex, t->weight);
			t = t->next;
		}
		putchar(10);
	}
}
