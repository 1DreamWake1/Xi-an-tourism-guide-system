#include<stdlib.h>
#include<read_map.h>
#include<graphics.h>

//从文件中读取景点信息到传入的景点邻接表中
void Read_Map(struct SCENIC *scenic)
{
	FILE* msg = NULL;																//读取“map_msg.txt”的文件指针
	FILE* p_introduce = NULL;														//读取“introduce.txt”的文件指针
	struct NODE *p, *q;																//创建邻接表时用的工具指针
	int count;																		//计数器
	extern int num_node;															//全局变量，记录景点数

	fopen_s(&msg, "../Data/map_msg.txt", "r");										//打开文件“map_msg.txt”
	if (msg == NULL)
		exit(0);
	for (count = 0; (EOF != fscanf_s(msg, "%s", (scenic+count)->name, UNIT_SIZE) && count < MAX_NODE); count++)	//读取“map_msg.txt”文件，读入景点名称
	{
		fscanf_s(msg, "%d", &((scenic + count)->x));								//读入景点的X坐标
		fscanf_s(msg, "%d", &((scenic + count)->y));								//读入景点的Y坐标
		fscanf_s(msg, "%s", (scenic + count)->introduction, UNIT_SIZE);				//读入景点介绍文件的路径
		fscanf_s(msg, "%s", (scenic + count)->picture, UNIT_SIZE);					//读入景点图片文件的路径
		fopen_s(&p_introduce, (scenic + count)->introduction, "r");					//打开介绍文件
		if (p_introduce == NULL)
			exit(0);
		fscanf_s(p_introduce, "%s", (scenic + count)->idt, 12 * UNIT_SIZE);			//将景点介绍文件读入
		fclose(p_introduce);														//关闭景点介绍文件
		for (q = p = (scenic + count)->head = (struct NODE*)malloc(sizeof(struct NODE)); TRUE;)					//读入邻接点，弧和权
		{
			if (p == NULL)
				exit(0);
			fscanf_s(msg, "%d", &(p->adjvex));							//读入邻接点（弧）
			fscanf_s(msg, "%f", &(p->weight));							//读入弧的权重
			if (p->adjvex == 0)											//读到空邻接点
			{
				q->next = NULL;											//最后一个节点地址域设为空指针
				free(p);												//释放掉空节点
				break;
			}
			q = p;														//用q指针跟踪上一个节点地址
			p->next = (struct NODE*)malloc(sizeof(struct NODE));		//创建下一个邻接点（弧）
			p = p->next;
		}
	}
	num_node = count;													//记录景点数
	fclose(msg);														//关闭“map_msg.txt”的文件指针
	return ;
}

//检测输出从“map_msg.txt”和“introduce.txt”读入的信息
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
