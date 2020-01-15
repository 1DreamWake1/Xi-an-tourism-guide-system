#include<graphics.h>
#include<root_menu.h>
#include<map.h>
#include<stdio.h>

//��ʾroot�û��Ĺ���˵�����
void show_root_menu(struct SCENIC *scenic)
{
	MOUSEMSG mouse;																			//�����ȡ�����Ϣ�Ľṹ�����

	initgraph(600, 400);																	//��ʼ��ͼ�ο�
	loadimage(NULL, _T("../Picture/root_menu.jpg"));										//������ʾ�˵�ͼ
	while (1)
	{
		//rectangle(10, 70, 120, 120);														//�����괥����
		mouse = GetMouseMsg();																//��ȡ�����Ϣ
		if (mouse.uMsg == WM_LBUTTONDOWN)													//��갴��
		{
			if ((mouse.x >= 10 && mouse.x <= 120) && (mouse.y >= 15 && mouse.y <= 60))		//�����û�
			{
				add_user();
				initgraph(600, 400);														//����ͼ�ο�
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//�ؼ�����ʾ�˵�ͼ
			}
			else if ((mouse.x >= 10 && mouse.x <= 120) && (mouse.y >= 70 && mouse.y <= 120))//ɾ���û�
			{
				delete_user();
				initgraph(600, 400);														//����ͼ�ο�
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//�ؼ�����ʾ�˵�ͼ
			}
			else if ((mouse.x >= 10 && mouse.x <= 120) && (mouse.y >= 135 && mouse.y <= 180))//�޸�����
			{
				change_passwd();
				initgraph(600, 400);														//����ͼ�ο�
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//�ؼ�����ʾ�˵�ͼ
			}
			else if ((mouse.x >= 480 && mouse.x <= 580) && (mouse.y >= 15 && mouse.y <= 60))//�鿴��ͼ
			{
				show_user_map(scenic);
				initgraph(600, 400);														//����ͼ�ο�
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//�ؼ�����ʾ�˵�ͼ
			}
			else if ((mouse.x >= 480 && mouse.x <= 580) && (mouse.y >= 70 && mouse.y <= 120))//���Ӿ���
			{
				add_scenic(scenic);
				initgraph(600, 400);														//����ͼ�ο�
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//�ؼ�����ʾ�˵�ͼ
			}
			else if ((mouse.x >= 480 && mouse.x <= 580) && (mouse.y >= 135 && mouse.y <= 180))//ɾ������
			{
				delete_scenic(scenic);
				initgraph(600, 400);														//����ͼ�ο�
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//�ؼ�����ʾ�˵�ͼ
			}
			else if ((mouse.x >= 160 && mouse.x <= 225) && (mouse.y >= 330 && mouse.y <= 380))//��С������
			{
				Prim(scenic);
				initgraph(600, 400);														//����ͼ�ο�
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//�ؼ�����ʾ�˵�ͼ
			}
			else if ((mouse.x >= 305 && mouse.x <= 390) && (mouse.y >= 330 && mouse.y <= 380))//�˳�
				break;
			else if ((mouse.x >= 10 && mouse.x <= 120) && (mouse.y >= 190 && mouse.y <= 240))//��ʾͼ
			{
				show_adj(scenic);
				initgraph(600, 400);														//����ͼ�ο�
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//�ؼ�����ʾ�˵�ͼ
			}
			else if ((mouse.x >= 10 && mouse.x <= 65) && (mouse.y >= 360 && mouse.y <= 390))//��ʼ��
			{
				init_map_msg();
				exit(0);
			}
		}
		else
			Sleep(10);
	}
	closegraph();																			//�رտ�
	return ;
}

//�����û�
void add_user()
{
	USER_MSG temp[MAX_USER];																//��š�passwd.txt���ļ��е���Ϣ
	USER_MSG user_msg;																		//�����û���Ϣ�ṹ��
	FILE* fp = NULL;																		//����򿪡�passwd.txt���ļ���ָ��
	RECT r = { 0, 0, 570, 399 };															//��ʾ��������
	char pass[BUFFER_SIZE] = "";															//��֤��������
	int num_user = 0;																		//��¼�û���

	initgraph(600, 400);																	//��ʼ��ͼ�ο�
	loadimage(NULL, _T("../Picture/login2.jpg"));											//������ʾ����ͼ
	for (int i = 0; i < MAX_USER; i++)														//temp ��ʼ������warring
	{
		strcpy_s(temp[i].name, "");
		strcpy_s(temp[i].passwd, "");
		strcpy_s(temp[i].User_ID, "");
	}
	fopen_s(&fp, "../Data/passwd.txt", "r");												//��ֻ����ʽ�򿪡�passwd.txt��
	if (fp == NULL)
		exit(0);
	while (EOF != fscanf_s(fp, "%s", temp[num_user].name, BUFFER_SIZE))						//����passwd.txt�������ڴ�
	{
		fscanf_s(fp, "%s", temp[num_user].passwd, BUFFER_SIZE);
		fscanf_s(fp, "%s", temp[num_user].User_ID, BUFFER_SIZE);
		num_user++;
	}
	fclose(fp);
	if (num_user >= MAX_USER)																//�û����������ﵽ�򳬹�MAX_USER
	{
		drawtext(_T("�û���Ŀ�Ѵ����ֵ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//����������Ϣ
		Sleep(1500);																		//��ʱ��ʾ��Ϣ
		closegraph();																		//�رմ���
		return;																				//�˳�����û�
	}
	InputBox(user_msg.name, BUFFER_SIZE, _T("�������û���"));									//��һ�������û���
	while (check_name(&user_msg))															//�û����Ѵ��ڣ���������
		InputBox(user_msg.name, BUFFER_SIZE, _T("���û����Ѵ��ڣ������������û���"));
	InputBox(user_msg.passwd, BUFFER_SIZE, _T("����������"));									//�����û�����
	InputBox(pass, BUFFER_SIZE, _T("������һ��"));											//��֤�û�����
	while (0 != strcmp(user_msg.passwd, pass))
	{
		InputBox(user_msg.passwd, BUFFER_SIZE, _T("�������벻ͬ��������һ��"));				//�����û�����
		InputBox(pass, BUFFER_SIZE, _T("������һ��"));										//��֤�û�����
	}
	fopen_s(&fp, "../Data/passwd.txt", "a+");												//��׷����ʽ�򿪡�passwd.txt��
	if (fp == NULL)
		exit(0);
	fprintf_s(fp, "\n%s %s 2", user_msg.name, user_msg.passwd);								//��passwd.txt��д��������û���Ϣ
	fclose(fp);																				//�رա�passwd.txt���ļ�ָ��
	drawtext(_T("�û������ɹ���"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				//������Ϣ
	Sleep(1500);																			//��ʱ��ʾ��Ϣ
	closegraph();																			//�رմ���
	return;
}

//ɾ���û�
void delete_user()
{
	FILE* fp = NULL;																		//�ļ�ָ��
	USER_MSG user_msg;																		//���Ҫɾ���û����û���
	USER_MSG temp[MAX_USER];																//��š�passwd.txt���ļ��е���Ϣ
	RECT r = { 0, 0, 570, 399 };															//��ʾ��������
	RECT rect = { 0,0,100,300 };															//������ʾ�����û��Ŀ�
	int num_user = 0;																		//��¼�û���
	char name_list[MAX_USER * BUFFER_SIZE] = "User List:\n";								//��ŵ�ǰ�û�����

	initgraph(600, 400);																	//��ʼ��ͼ�ο�
	loadimage(NULL, _T("../Picture/login2.jpg"));											//������ʾ����ͼ
	for (int i = 0; i < MAX_USER; i++)														//temp ��ʼ������warring
	{
		strcpy_s(temp[i].name, "");
		strcpy_s(temp[i].passwd, "");
		strcpy_s(temp[i].User_ID, "");
	}
	fopen_s(&fp, "../Data/passwd.txt", "r");												//��ֻ����ʽ�򿪡�passwd.txt��������Ϣ�����ڴ�
	if (fp == NULL)
		exit(0);
	while (EOF != fscanf_s(fp, "%s", temp[num_user].name, BUFFER_SIZE))						//����passwd.txt�������ڴ�
	{
		fscanf_s(fp, "%s", temp[num_user].passwd, BUFFER_SIZE);
		fscanf_s(fp, "%s", temp[num_user].User_ID, BUFFER_SIZE);
		num_user++;
	}
	fclose(fp);
	for (int i = 0; i < num_user; i++)														//�����û��б�
	{
		strcat_s(name_list, temp[i].name);
		strcat_s(name_list, "    ");
	}
	drawtext(name_list, &rect, DT_WORDBREAK);												//��ʾ�û��б�
	InputBox(user_msg.name, BUFFER_SIZE, _T("������Ҫɾ�����û����û���"));						//��һ������Ҫɾ�����û����û���
	while (0 == check_name(&user_msg))														//�û��������ڣ���������
		InputBox(user_msg.name, BUFFER_SIZE, _T("���û������ڣ������������û���"));
	if (0 == strcmp(user_msg.name, "root"))													//root �û�����ɾ
	{
		drawtext(_T("������ɾ��root�û�"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//������Ϣ
		Sleep(1500);																		//��ʱ��ʾ��Ϣ
		closegraph();																		//�رմ���
		return;
	}
	fopen_s(&fp, "../Data/passwd.txt", "w+");												//��д����ʽ�򿪡�passwd.tx��,�������Ϣ
	if (fp == NULL)
		exit(0);
	fprintf(fp, "root root 1");																//����д��root��Ϣ
	for (int count = 1; count < num_user - 1; count++)
	{
		if (0 == strcmp(temp[count].name, user_msg.name))
			count++;
		fprintf_s(fp, "\n%s %s 2", temp[count].name, temp[count].passwd);
	}
	fclose(fp);																				//�رա�passwd.txt���ļ�ָ��
	drawtext(_T("�û�ɾ���ɹ���"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				//������Ϣ
	Sleep(1500);																			//��ʱ��ʾ��Ϣ
	closegraph();																			//�رմ���
	return;
}

//�����û�����
void change_passwd()
{
	FILE* fp = NULL;																		//�ļ�ָ��
	USER_MSG user_msg;																		//���Ҫ����������û����û���
	USER_MSG temp[MAX_USER];																//��š�passwd.txt���ļ��е���Ϣ
	RECT r = { 0, 0, 570, 399 };															//��ʾ��������
	RECT rect = { 0,0,100,300 };															//������ʾ�����û��Ŀ�
	int num_user = 0;																		//��¼�û���
	char pass[BUFFER_SIZE] = "";															//��֤��������
	char name_list[MAX_USER * BUFFER_SIZE] = "User List:\n";								//��ŵ�ǰ�û�����

	initgraph(600, 400);																	//��ʼ��ͼ�ο�
	loadimage(NULL, _T("../Picture/login2.jpg"));											//������ʾ����ͼ
	for (int i = 0; i < MAX_USER; i++)														//temp ��ʼ������warring
	{
		strcpy_s(temp[i].name, "");
		strcpy_s(temp[i].passwd, "");
		strcpy_s(temp[i].User_ID, "");
	}
	fopen_s(&fp, "../Data/passwd.txt", "r");												//��ֻ����ʽ�򿪡�passwd.txt��������Ϣ�����ڴ�
	if (fp == NULL)
		exit(0);
	while (EOF != fscanf_s(fp, "%s", temp[num_user].name, BUFFER_SIZE))						//����passwd.txt�������ڴ�
	{
		fscanf_s(fp, "%s", temp[num_user].passwd, BUFFER_SIZE);
		fscanf_s(fp, "%s", temp[num_user].User_ID, BUFFER_SIZE);
		num_user++;
	}
	fclose(fp);
	for (int i = 0; i < num_user; i++)														//�����û��б�
	{
		strcat_s(name_list, temp[i].name);
		strcat_s(name_list, "    ");
	}
	drawtext(name_list, &rect, DT_WORDBREAK);												//��ʾ�û��б�
	InputBox(user_msg.name, BUFFER_SIZE, _T("������Ҫ����������û����û���"));					//��һ������Ҫɾ�����û����û���
	while (0 == check_name(&user_msg))														//�û��������ڣ���������
		InputBox(user_msg.name, BUFFER_SIZE, _T("���û������ڣ������������û���"));
	fopen_s(&fp, "../Data/passwd.txt", "w+");												//��д����ʽ�򿪡�passwd.tx��,�������Ϣ
	if (fp == NULL)
		exit(0);
	InputBox(user_msg.passwd, BUFFER_SIZE, _T("����������"));									//�����û�����
	InputBox(pass, BUFFER_SIZE, _T("������һ��"));											//��֤�û�����
	while (0 != strcmp(user_msg.passwd, pass))
	{
		InputBox(user_msg.passwd, BUFFER_SIZE, _T("�������벻ͬ��������һ��"));				//�����û�����
		InputBox(pass, BUFFER_SIZE, _T("������һ��"));										//��֤�û�����
	}
	if (0 == strcmp(user_msg.name, "root"))													//���ĵ���root����
	{
		char root_pass[UNIT_SIZE] = "root ";
		strcat_s(root_pass, user_msg.passwd);
		strcat_s(root_pass, " 1");
		fprintf(fp, root_pass);
	}
	else
		fprintf(fp, "root root 1");															//����д��root��Ϣ
	for (int count = 1; count < num_user; count++)
	{
		if (0 == strcmp(temp[count].name, user_msg.name))
			strcpy_s(temp[count].passwd, user_msg.passwd);									//�������븲�Ǿ�����
		fprintf_s(fp, "\n%s %s 2", temp[count].name, temp[count].passwd);
	}
	fclose(fp);																				//�رա�passwd.txt���ļ�ָ��
	drawtext(_T("������ĳɹ���"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				//������Ϣ
	Sleep(1500);																			//��ʱ��ʾ��Ϣ
	closegraph();																			//�رմ���
	return;
}

//��ʾͼ
void show_adj(struct SCENIC* scenic)
{
	MOUSEMSG mouse;															//���������Ϣ�ṹ��
	RECT rect = { 0,0,0,0 };												//·����ʾ��
	struct NODE* p = NULL;													//�����ڽӱ��õ�ָ��
	extern int num_node;													//ȫ�ֱ������������
	int count = 0;															//������
	char s[UNIT_SIZE] = "\0";												//������

	initgraph(1366, 900);													//��ʼ����ͼ��
	loadimage(NULL, _T("../Picture/Xi'an_map2.jpg"));						//���ر���ͼ
	setlinecolor(BLUE);														//���û�����ɫΪ��
	setfillcolor(RED);														//���������ɫΪ��
	for (count = 0; count < num_node; count++)
	{
		fillcircle((scenic + count)->x, (scenic + count)->y, 10);			//��ǳ����о���
		outtextxy((scenic + count)->x, (scenic + count)->y, (scenic + count)->name);//��ʾ��������
		for (p = (scenic + count)->head; p != NULL; p = p->next)			//����
		{
			line((scenic + count)->x, (scenic + count)->y, (scenic + p->adjvex - 1)->x, (scenic + p->adjvex - 1)->y);
			_gcvt_s(s, UNIT_SIZE, (double)p->weight, 4);					//��·��ת��Ϊ�ַ���
			if ((scenic + count)->x < (scenic + p->adjvex - 1)->x)
				rect = { (scenic + count)->x - 8,(scenic + count)->y,(scenic + p->adjvex - 1)->x + 8, (scenic + p->adjvex - 1)->y };
			else
				rect = { (scenic + p->adjvex - 1)->x - 8, (scenic + p->adjvex - 1)->y,(scenic + count)->x + 8,(scenic + count)->y };
			drawtext(s, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);								//��ʾ·��
		}
	}
		
	while (1)
	{
		mouse = GetMouseMsg();												//��ȡ��굱ǰ��Ϣ	
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
			break;															//�����������˳�				
	}
	closegraph();
	return;
}

//ɾ������
void delete_scenic(struct SCENIC* scenic)
{
	int v0 = 0;																//��¼Ҫɾ���ľ���
	RECT r = { 0, 0, 570, 399 };											//��ʾ��������
	FILE* fp = NULL;														//�ļ�ָ�룬�򿪡�map_msg.txt��
	struct NODE* p = NULL;													//�����ڽӱ���
	extern int num_node;													//ȫ�ֱ�������¼������

	closegraph();															//�رմ���
	initgraph(1366,900);													//�ؿ�����
	v0 = chose_node(scenic);												//��ȡҪɾ�����λ��
	fillcircle((scenic + v0)->x, (scenic + v0)->y, R);						//���Ҫɾ���ľ���

	if (v0 == -1)															//ֱ���˳�
	{
		closegraph();
		return;
	}
	else
	{
		closegraph();														//�رմ���
		fopen_s(&fp, "../Data/map_msg.txt", "w");							//�򿪡�map_msg.txt���������
		if (fp == NULL)
			exit(0);
		for (int i = 0; i < num_node; i++)
		{
			if (i == v0)													//Ҫɾ���ľ���ֱ������
				continue;
			else
			{
				fprintf_s(fp, "%s %d %d %s %s", (scenic + i)->name, (scenic + i)->x, (scenic + i)->y, (scenic + i)->introduction, (scenic + i)->picture);
				for (p = (scenic + i)->head; p != NULL; p = p->next)		//�����ڽӱ�����
				{
					if (p->adjvex - 1 == v0)								//�ڽӵ�Ҫɾ���ľ���
						continue;
					else if (p->adjvex - 1 < v0)
						fprintf_s(fp, " %d %.1f", p->adjvex, p->weight);
					else if (p->adjvex - 1 > v0)
						fprintf_s(fp, " %d %.1f", p->adjvex - 1, p->weight);
				}
			}
			fprintf(fp, " %d %.1f\n",0,0.0);								//���뻻��
		}
		fclose(fp);																//�رա�map_msg.txt��
		num_node--;																//����������һ
		initgraph(600, 400);													//�ؿ�����
		loadimage(NULL, _T("../Picture/login2.jpg"));							//������ʾ����ͼ
		drawtext(_T("ɾ���ɹ���"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//������Ϣ
		Read_Map(scenic);
		Sleep(1000);															//��ʾ��ʱ
		closegraph();
	}
	return;
}

//���Ӿ���
void add_scenic(struct SCENIC* scenic)
{
	MOUSEMSG mouse;															//���������Ϣ�ṹ��
	RECT r = { 0, 0, 570, 399 };											//��ʾ��������
	FILE* fp = NULL;														//�򿪡�pam_msg.txt�����ļ�ָ��
	struct NODE* p = NULL, * q = NULL;										//�����ڽӱ���
	struct NODE* t = NULL;													//�����ڽӱ���
	extern int num_node;													//ȫ�ֱ�������¼������
	char wei[UNIT_SIZE] = "\0";												//������

	
	closegraph();															//�رմ���
	if (num_node == MAX_NODE)												//����������
	{
		initgraph(600, 400);													//��ʼ����
		loadimage(NULL, _T("../Picture/login2.jpg"));							//������ʾ����ͼ
		drawtext(_T("�������Ѵ����ֵ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//������Ϣ
		Sleep(1500);															//��ʱ��ʾ
		closegraph();															//�رտ�
		return;
	}
	initgraph(1366, 900);													//�ؿ�����
	loadimage(NULL, _T("../Picture/Xi'an_map2.jpg"));						//���ر���ͼ
	setlinecolor(BLUE);														//���û�����ɫΪ��
	setfillcolor(RED);														//���������ɫΪ��
	for (int count = 0; count < num_node; count++)
	{
		fillcircle((scenic + count)->x, (scenic + count)->y, 10);			//��Ǿ��㣬��ʾ��������
		outtextxy((scenic + count)->x, (scenic + count)->y, (scenic + count)->name);
	}
	outtextxy(1000, 0, _T("����������¾����ڵ�ͼ�ϵ�λ��"));					//��ʾ��ʾ��Ϣ
	Sleep(500);
	while (TRUE)															//��ȡ�¾��������
	{
		mouse = GetMouseMsg();												//��ȡ��굱ǰ��Ϣ	
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
		{
			closegraph();
			return;															//��������˳���
		}
		else if((mouse.uMsg == WM_LBUTTONDOWN) && !((mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710)))
		{
			setfillcolor(GREEN);											//���������ɫΪ��
			fillcircle(mouse.x, mouse.y, R);								//����½��
			break;															//��ȡ���¾�������
		}
		Sleep(10);
	}
	(scenic + num_node)->x = mouse.x;										//�����¾����x����
	(scenic + num_node)->y = mouse.y;										//�����½���y����
	(scenic + num_node)->head = (struct NODE*)malloc(sizeof(struct NODE));	//�����һ���ڽӱ�ռ�
	for (q = p = (scenic + num_node)->head; TRUE; p = p->next)
	{
		if (p == NULL)
			exit(0);
		p->adjvex = chose_node(scenic) + 1;									//ѡ���ڽӵ�
		if (p->adjvex == 0)													//������˳�
		{
			if ((scenic + num_node)->head == p)								//û������ڽӵ�
			{
				closegraph();												//�رտ�
				initgraph(600, 400);										//��ʼ����
				loadimage(NULL, _T("../Picture/login2.jpg"));				//���ر���ͼ
				drawtext(_T("����ʧ�ܣ�"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//������Ϣ
				Sleep(1500);												//��ʱ��ʾ
				Read_Map(scenic);											//�ָ�������Ϣ
				closegraph();												//�رտ�
				return;
			}
			else															//�����ɹ�
			{
				free(p);													//�ͷŵ����һ���ս��
				q->next = NULL;												//ά���ڽӱ�
				break;
			}
		}
		InputBox(wei, BUFFER_SIZE, _T("������·�̣�"));						//����·��
		p->weight = (float)atof(wei);										//���ַ���ת��Ϊfloat����Ȩֵ
		for (t = (scenic + p->adjvex - 1)->head; t->next != NULL; t = t->next)//�ҵ��ڽӵ�����һ�����
			continue;
		t->next = (struct NODE*)malloc(sizeof(struct NODE));				//�������ڽӵ�
		if (t->next == NULL)
			exit(0);
		t->next->adjvex = num_node + 1;										//ά���ڽӵ�λ��
		t->next->weight = p->weight;										//ά������Ȩֵ
		t->next->next = NULL;												//ά��
		q = p;																//��q������һ���
		p->next = (struct NODE*)malloc(sizeof(struct NODE));				//�����µĿռ�
	}
	InputBox((scenic + num_node)->name, BUFFER_SIZE, _T("�������¾��������"));//��������
	InputBox((scenic + num_node)->introduction, BUFFER_SIZE, _T("�������¾�������ļ���·��(���·��)"));//��������ļ�·��
	InputBox((scenic + num_node)->picture, BUFFER_SIZE, _T("�������¾�����Ƭ��·��(���·��)"));//������Ƭ·��
	fopen_s(&fp, (scenic + num_node)->introduction, "r");					//�򿪽����ļ�
	if (fp == NULL)
		exit(0);
	fscanf_s(fp, "%s", (scenic + num_node)->idt, 12 * UNIT_SIZE);			//�������
	fclose(fp);																//�رս����ļ�
	num_node++;																//��������һ
	fopen_s(&fp, "../Data/map_msg.txt", "w");								//��д����ʽ�򿪡�map_msg.txt���������
	if (fp == NULL)
		exit(0);
	for (int i = 0; i < num_node; i++)										//���¡�map_msg.txt���ļ�
	{
		fprintf_s(fp, "%s %d %d %s %s", (scenic + i)->name, (scenic + i)->x, (scenic + i)->y, (scenic + i)->introduction, (scenic + i)->picture);
		for (t = (scenic + i)->head; t != NULL; t = t->next)
			fprintf_s(fp, " %d %.1f", t->adjvex, t->weight);
		fprintf_s(fp, " %d %.1f\n", 0, 0.0);
	}
	fclose(fp);																//�رա�map_msg.txt��
	closegraph();															//�رտ�
	initgraph(600, 400);													//��ʼ����
	loadimage(NULL, _T("../Picture/login2.jpg"));							//������ʾ����ͼ
	drawtext(_T("�����ɹ���"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//������Ϣ
	Sleep(1500);															//��ʱ��ʾ
	closegraph();															//�رտ�

	return;
}

//ʹ�ñ��ݵġ�map_msg.txt��
void init_map_msg()
{
	FILE* msg = NULL;																//�ļ�ָ��
	RECT r = { 0, 0, 570, 399 };													//��ʾ��������
	struct NODE* p = NULL, * q = NULL;												//�����ڽӱ�
	extern int num_node;															//ȫ�ֱ�������¼������
	struct SCENIC* scenic;

	scenic = (struct SCENIC*)malloc(MAX_NODE * sizeof(struct SCENIC));
	if (scenic == NULL)
		exit(0);
	fopen_s(&msg, "../Backup/map_msg.txt", "r");									//�򿪱��ݡ�map_msg.txt��
	if (msg == NULL)
		exit(0);
	for (int count = 0; (EOF != fscanf_s(msg, "%s", (scenic + count)->name, UNIT_SIZE) && count < MAX_NODE); count++)	//��ȡ��map_msg.txt���ļ������뾰������
	{
		fscanf_s(msg, "%d", &((scenic + count)->x));								//���뾰���X����
		fscanf_s(msg, "%d", &((scenic + count)->y));								//���뾰���Y����
		fscanf_s(msg, "%s", (scenic + count)->introduction, UNIT_SIZE);				//���뾰������ļ���·��
		fscanf_s(msg, "%s", (scenic + count)->picture, UNIT_SIZE);					//���뾰��ͼƬ�ļ���·��
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
	fclose(msg);															//�رձ��ݡ�map_msg.txt��
	fopen_s(&msg, "../Data/map_msg.txt", "w");								//�򿪡�map_msg.txt��
	if (msg == NULL)
		exit(0);
	for (int i = 0; i < 18; i++)											//���¡�map_msg.txt���ļ�
	{
		fprintf_s(msg, "%s %d %d %s %s", (scenic + i)->name, (scenic + i)->x, (scenic + i)->y, (scenic + i)->introduction, (scenic + i)->picture);
		for (p = (scenic + i)->head; p != NULL; p = p->next)
			fprintf_s(msg, " %d %.1f", p->adjvex, p->weight);
		fprintf_s(msg, " %d %.1f\n", 0, 0.0);
	}
	closegraph();															//�رտ�
	initgraph(600, 400);													//��ʼ����
	loadimage(NULL, _T("../Picture/login2.jpg"));							//���ر���ͼ
	drawtext(_T("��ʼ���ɹ�����������������"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//������Ϣ
	Sleep(1500);															//��ʱ��ʾ
	closegraph();															//�رտ�
	return;
}

//��Prim�㷨����С������
void Prim(struct SCENIC* scenic)
{
	int flag[MAX_NODE];														//�ý���Ƿ��Ѿ�������С������
	extern int num_node;													//ȫ�ֱ�������¼������
	MOUSEMSG mouse;															//���������Ϣ�ṹ��
	RECT rect = { 0,0,0,0 };												//·����ʾ��
	struct NODE* p = NULL;													//�����ڽӱ��õ�ָ��
	struct NODE temp = { 0,0XFFFF,NULL };									//����С
	char s[UNIT_SIZE] = "\0";												//������
	int i = 0, j = 0;														//������

	initgraph(1366, 900);													//��ʼ����ͼ��
	loadimage(NULL, _T("../Picture/Xi'an_map2.jpg"));						//���ر���ͼ
	setlinecolor(BLUE);														//���û�����ɫΪ��
	setfillcolor(RED);														//���������ɫΪ��
	for (int count = 0; count < num_node; count++)
	{
		fillcircle((scenic + count)->x, (scenic + count)->y, 10);			//��ǳ����о���
		outtextxy((scenic + count)->x, (scenic + count)->y, (scenic + count)->name);//��ʾ��������
		for (p = (scenic + count)->head; p != NULL; p = p->next)			//����
		{
			line((scenic + count)->x, (scenic + count)->y, (scenic + p->adjvex - 1)->x, (scenic + p->adjvex - 1)->y);
			_gcvt_s(s, UNIT_SIZE, (double)p->weight, 4);					//��·��ת��Ϊ�ַ���
			if ((scenic + count)->x < (scenic + p->adjvex - 1)->x)
				rect = { (scenic + count)->x - 8,(scenic + count)->y,(scenic + p->adjvex - 1)->x + 8, (scenic + p->adjvex - 1)->y };
			else
				rect = { (scenic + p->adjvex - 1)->x - 8, (scenic + p->adjvex - 1)->y,(scenic + count)->x + 8,(scenic + count)->y };
			drawtext(s, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);								//��ʾ·��
		}
	}
	setlinecolor(GREEN);													//���û�����ɫΪ��ɫ
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	for (i = 0; i < MAX_NODE; i++)											//��ʼ��
		flag[i] = 0;
	flag[0] = 1;															//�ӵ����λ�ÿ�ʼ
	for (int count = 0; count < num_node - 1; count++)						//��num_node-1����
	{
		temp = { 0,0XFFFF,NULL };
		for (i = j = 0; i < num_node; i++)
		{
			if (flag[i] == 1)
			{
				for (p = (scenic + i)->head; p != NULL; p = p->next)
				{
					if (flag[p->adjvex - 1] == 1)
						continue;
					else
					{
						if (p->weight < temp.weight)
						{
							temp.adjvex = p->adjvex;
							temp.weight = p->weight;
							j = i;
						}
					}
				}
			}
		}
		if (temp.adjvex == 0)
			temp.adjvex++;
		flag[temp.adjvex - 1] = 1;
		line((scenic + j)->x, (scenic + j)->y, (scenic + temp.adjvex - 1)->x, (scenic + temp.adjvex - 1)->y);
	}
	setlinecolor(BLUE);														//���û�����ɫΪ��
	while (1)
	{
		mouse = GetMouseMsg();												//��ȡ��굱ǰ��Ϣ	
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
			break;															//�����������˳�				
	}
	closegraph();
	return;
}
