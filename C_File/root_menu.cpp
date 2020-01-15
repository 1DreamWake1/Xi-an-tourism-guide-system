#include<graphics.h>
#include<root_menu.h>
#include<map.h>
#include<stdio.h>

//显示root用户的管理菜单界面
void show_root_menu(struct SCENIC *scenic)
{
	MOUSEMSG mouse;																			//定义获取鼠标信息的结构体变量

	initgraph(600, 400);																	//初始化图形框
	loadimage(NULL, _T("../Picture/root_menu.jpg"));										//加载显示菜单图
	while (1)
	{
		//rectangle(10, 70, 120, 120);														//检测鼠标触发框
		mouse = GetMouseMsg();																//获取鼠标信息
		if (mouse.uMsg == WM_LBUTTONDOWN)													//鼠标按下
		{
			if ((mouse.x >= 10 && mouse.x <= 120) && (mouse.y >= 15 && mouse.y <= 60))		//增加用户
			{
				add_user();
				initgraph(600, 400);														//重启图形框
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//重加载显示菜单图
			}
			else if ((mouse.x >= 10 && mouse.x <= 120) && (mouse.y >= 70 && mouse.y <= 120))//删除用户
			{
				delete_user();
				initgraph(600, 400);														//重启图形框
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//重加载显示菜单图
			}
			else if ((mouse.x >= 10 && mouse.x <= 120) && (mouse.y >= 135 && mouse.y <= 180))//修改密码
			{
				change_passwd();
				initgraph(600, 400);														//重启图形框
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//重加载显示菜单图
			}
			else if ((mouse.x >= 480 && mouse.x <= 580) && (mouse.y >= 15 && mouse.y <= 60))//查看地图
			{
				show_user_map(scenic);
				initgraph(600, 400);														//重启图形框
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//重加载显示菜单图
			}
			else if ((mouse.x >= 480 && mouse.x <= 580) && (mouse.y >= 70 && mouse.y <= 120))//增加景点
			{
				add_scenic(scenic);
				initgraph(600, 400);														//重启图形框
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//重加载显示菜单图
			}
			else if ((mouse.x >= 480 && mouse.x <= 580) && (mouse.y >= 135 && mouse.y <= 180))//删除景点
			{
				delete_scenic(scenic);
				initgraph(600, 400);														//重启图形框
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//重加载显示菜单图
			}
			else if ((mouse.x >= 160 && mouse.x <= 225) && (mouse.y >= 330 && mouse.y <= 380))//最小生成数
			{
				Prim(scenic);
				initgraph(600, 400);														//重启图形框
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//重加载显示菜单图
			}
			else if ((mouse.x >= 305 && mouse.x <= 390) && (mouse.y >= 330 && mouse.y <= 380))//退出
				break;
			else if ((mouse.x >= 10 && mouse.x <= 120) && (mouse.y >= 190 && mouse.y <= 240))//显示图
			{
				show_adj(scenic);
				initgraph(600, 400);														//重启图形框
				loadimage(NULL, _T("../Picture/root_menu.jpg"));							//重加载显示菜单图
			}
			else if ((mouse.x >= 10 && mouse.x <= 65) && (mouse.y >= 360 && mouse.y <= 390))//初始化
			{
				init_map_msg();
				exit(0);
			}
		}
		else
			Sleep(10);
	}
	closegraph();																			//关闭框
	return ;
}

//增加用户
void add_user()
{
	USER_MSG temp[MAX_USER];																//存放“passwd.txt”文件中的信息
	USER_MSG user_msg;																		//定义用户信息结构体
	FILE* fp = NULL;																		//定义打开“passwd.txt”文件的指针
	RECT r = { 0, 0, 570, 399 };															//显示框找中心
	char pass[BUFFER_SIZE] = "";															//验证创建密码
	int num_user = 0;																		//记录用户数

	initgraph(600, 400);																	//初始化图形框
	loadimage(NULL, _T("../Picture/login2.jpg"));											//加载显示背景图
	for (int i = 0; i < MAX_USER; i++)														//temp 初始化，防warring
	{
		strcpy_s(temp[i].name, "");
		strcpy_s(temp[i].passwd, "");
		strcpy_s(temp[i].User_ID, "");
	}
	fopen_s(&fp, "../Data/passwd.txt", "r");												//以只读形式打开“passwd.txt”
	if (fp == NULL)
		exit(0);
	while (EOF != fscanf_s(fp, "%s", temp[num_user].name, BUFFER_SIZE))						//将“passwd.txt”读入内存
	{
		fscanf_s(fp, "%s", temp[num_user].passwd, BUFFER_SIZE);
		fscanf_s(fp, "%s", temp[num_user].User_ID, BUFFER_SIZE);
		num_user++;
	}
	fclose(fp);
	if (num_user >= MAX_USER)																//用户数已满，达到或超过MAX_USER
	{
		drawtext(_T("用户数目已达最大值！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//反馈错误消息
		Sleep(1500);																		//延时显示消息
		closegraph();																		//关闭窗口
		return;																				//退出添加用户
	}
	InputBox(user_msg.name, BUFFER_SIZE, _T("请输入用户名"));									//第一次输入用户名
	while (check_name(&user_msg))															//用户名已存在，重新输入
		InputBox(user_msg.name, BUFFER_SIZE, _T("该用户名已存在，请重新输入用户名"));
	InputBox(user_msg.passwd, BUFFER_SIZE, _T("请输入密码"));									//设置用户密码
	InputBox(pass, BUFFER_SIZE, _T("请再输一次"));											//验证用户密码
	while (0 != strcmp(user_msg.passwd, pass))
	{
		InputBox(user_msg.passwd, BUFFER_SIZE, _T("两次输入不同，请再试一次"));				//设置用户密码
		InputBox(pass, BUFFER_SIZE, _T("请再输一次"));										//验证用户密码
	}
	fopen_s(&fp, "../Data/passwd.txt", "a+");												//以追加形式打开“passwd.txt”
	if (fp == NULL)
		exit(0);
	fprintf_s(fp, "\n%s %s 2", user_msg.name, user_msg.passwd);								//向“passwd.txt”写入新添的用户信息
	fclose(fp);																				//关闭“passwd.txt”文件指针
	drawtext(_T("用户创建成功！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				//反馈消息
	Sleep(1500);																			//延时显示消息
	closegraph();																			//关闭窗口
	return;
}

//删除用户
void delete_user()
{
	FILE* fp = NULL;																		//文件指针
	USER_MSG user_msg;																		//存放要删除用户的用户名
	USER_MSG temp[MAX_USER];																//存放“passwd.txt”文件中的信息
	RECT r = { 0, 0, 570, 399 };															//显示框找中心
	RECT rect = { 0,0,100,300 };															//定义显示所有用户的框
	int num_user = 0;																		//记录用户数
	char name_list[MAX_USER * BUFFER_SIZE] = "User List:\n";								//存放当前用户名单

	initgraph(600, 400);																	//初始化图形框
	loadimage(NULL, _T("../Picture/login2.jpg"));											//加载显示背景图
	for (int i = 0; i < MAX_USER; i++)														//temp 初始化，防warring
	{
		strcpy_s(temp[i].name, "");
		strcpy_s(temp[i].passwd, "");
		strcpy_s(temp[i].User_ID, "");
	}
	fopen_s(&fp, "../Data/passwd.txt", "r");												//以只读形式打开“passwd.txt”，将信息读入内存
	if (fp == NULL)
		exit(0);
	while (EOF != fscanf_s(fp, "%s", temp[num_user].name, BUFFER_SIZE))						//将“passwd.txt”读入内存
	{
		fscanf_s(fp, "%s", temp[num_user].passwd, BUFFER_SIZE);
		fscanf_s(fp, "%s", temp[num_user].User_ID, BUFFER_SIZE);
		num_user++;
	}
	fclose(fp);
	for (int i = 0; i < num_user; i++)														//创建用户列表
	{
		strcat_s(name_list, temp[i].name);
		strcat_s(name_list, "    ");
	}
	drawtext(name_list, &rect, DT_WORDBREAK);												//显示用户列表
	InputBox(user_msg.name, BUFFER_SIZE, _T("请输入要删除的用户的用户名"));						//第一次输入要删除的用户的用户名
	while (0 == check_name(&user_msg))														//用户名不存在，重新输入
		InputBox(user_msg.name, BUFFER_SIZE, _T("该用户不存在，请重新输入用户名"));
	if (0 == strcmp(user_msg.name, "root"))													//root 用户不可删
	{
		drawtext(_T("不可以删除root用户"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//反馈消息
		Sleep(1500);																		//延时显示消息
		closegraph();																		//关闭窗口
		return;
	}
	fopen_s(&fp, "../Data/passwd.txt", "w+");												//以写入形式打开“passwd.tx”,并清空信息
	if (fp == NULL)
		exit(0);
	fprintf(fp, "root root 1");																//单独写入root信息
	for (int count = 1; count < num_user - 1; count++)
	{
		if (0 == strcmp(temp[count].name, user_msg.name))
			count++;
		fprintf_s(fp, "\n%s %s 2", temp[count].name, temp[count].passwd);
	}
	fclose(fp);																				//关闭“passwd.txt”文件指针
	drawtext(_T("用户删除成功！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				//反馈消息
	Sleep(1500);																			//延时显示消息
	closegraph();																			//关闭窗口
	return;
}

//更改用户密码
void change_passwd()
{
	FILE* fp = NULL;																		//文件指针
	USER_MSG user_msg;																		//存放要更改密码的用户的用户名
	USER_MSG temp[MAX_USER];																//存放“passwd.txt”文件中的信息
	RECT r = { 0, 0, 570, 399 };															//显示框找中心
	RECT rect = { 0,0,100,300 };															//定义显示所有用户的框
	int num_user = 0;																		//记录用户数
	char pass[BUFFER_SIZE] = "";															//验证创建密码
	char name_list[MAX_USER * BUFFER_SIZE] = "User List:\n";								//存放当前用户名单

	initgraph(600, 400);																	//初始化图形框
	loadimage(NULL, _T("../Picture/login2.jpg"));											//加载显示背景图
	for (int i = 0; i < MAX_USER; i++)														//temp 初始化，防warring
	{
		strcpy_s(temp[i].name, "");
		strcpy_s(temp[i].passwd, "");
		strcpy_s(temp[i].User_ID, "");
	}
	fopen_s(&fp, "../Data/passwd.txt", "r");												//以只读形式打开“passwd.txt”，将信息读入内存
	if (fp == NULL)
		exit(0);
	while (EOF != fscanf_s(fp, "%s", temp[num_user].name, BUFFER_SIZE))						//将“passwd.txt”读入内存
	{
		fscanf_s(fp, "%s", temp[num_user].passwd, BUFFER_SIZE);
		fscanf_s(fp, "%s", temp[num_user].User_ID, BUFFER_SIZE);
		num_user++;
	}
	fclose(fp);
	for (int i = 0; i < num_user; i++)														//创建用户列表
	{
		strcat_s(name_list, temp[i].name);
		strcat_s(name_list, "    ");
	}
	drawtext(name_list, &rect, DT_WORDBREAK);												//显示用户列表
	InputBox(user_msg.name, BUFFER_SIZE, _T("请输入要更改密码的用户的用户名"));					//第一次输入要删除的用户的用户名
	while (0 == check_name(&user_msg))														//用户名不存在，重新输入
		InputBox(user_msg.name, BUFFER_SIZE, _T("该用户不存在，请重新输入用户名"));
	fopen_s(&fp, "../Data/passwd.txt", "w+");												//以写入形式打开“passwd.tx”,并清空信息
	if (fp == NULL)
		exit(0);
	InputBox(user_msg.passwd, BUFFER_SIZE, _T("请输入密码"));									//设置用户密码
	InputBox(pass, BUFFER_SIZE, _T("请再输一次"));											//验证用户密码
	while (0 != strcmp(user_msg.passwd, pass))
	{
		InputBox(user_msg.passwd, BUFFER_SIZE, _T("两次输入不同，请再试一次"));				//设置用户密码
		InputBox(pass, BUFFER_SIZE, _T("请再输一次"));										//验证用户密码
	}
	if (0 == strcmp(user_msg.name, "root"))													//更改的是root密码
	{
		char root_pass[UNIT_SIZE] = "root ";
		strcat_s(root_pass, user_msg.passwd);
		strcat_s(root_pass, " 1");
		fprintf(fp, root_pass);
	}
	else
		fprintf(fp, "root root 1");															//单独写入root信息
	for (int count = 1; count < num_user; count++)
	{
		if (0 == strcmp(temp[count].name, user_msg.name))
			strcpy_s(temp[count].passwd, user_msg.passwd);									//用新密码覆盖旧密码
		fprintf_s(fp, "\n%s %s 2", temp[count].name, temp[count].passwd);
	}
	fclose(fp);																				//关闭“passwd.txt”文件指针
	drawtext(_T("密码更改成功！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				//反馈消息
	Sleep(1500);																			//延时显示消息
	closegraph();																			//关闭窗口
	return;
}

//显示图
void show_adj(struct SCENIC* scenic)
{
	MOUSEMSG mouse;															//定义鼠标信息结构体
	RECT rect = { 0,0,0,0 };												//路程显示框
	struct NODE* p = NULL;													//遍历邻接表用的指针
	extern int num_node;													//全局变量，景点个数
	int count = 0;															//计数器
	char s[UNIT_SIZE] = "\0";												//缓冲区

	initgraph(1366, 900);													//初始化绘图框
	loadimage(NULL, _T("../Picture/Xi'an_map2.jpg"));						//加载背景图
	setlinecolor(BLUE);														//设置划线颜色为蓝
	setfillcolor(RED);														//设置填充颜色为红
	for (count = 0; count < num_node; count++)
	{
		fillcircle((scenic + count)->x, (scenic + count)->y, 10);			//标记出所有景点
		outtextxy((scenic + count)->x, (scenic + count)->y, (scenic + count)->name);//显示景点名称
		for (p = (scenic + count)->head; p != NULL; p = p->next)			//连线
		{
			line((scenic + count)->x, (scenic + count)->y, (scenic + p->adjvex - 1)->x, (scenic + p->adjvex - 1)->y);
			_gcvt_s(s, UNIT_SIZE, (double)p->weight, 4);					//将路程转换为字符串
			if ((scenic + count)->x < (scenic + p->adjvex - 1)->x)
				rect = { (scenic + count)->x - 8,(scenic + count)->y,(scenic + p->adjvex - 1)->x + 8, (scenic + p->adjvex - 1)->y };
			else
				rect = { (scenic + p->adjvex - 1)->x - 8, (scenic + p->adjvex - 1)->y,(scenic + count)->x + 8,(scenic + count)->y };
			drawtext(s, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);								//显示路程
		}
	}
		
	while (1)
	{
		mouse = GetMouseMsg();												//获取鼠标当前信息	
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
			break;															//鼠标左键按下退出				
	}
	closegraph();
	return;
}

//删除景点
void delete_scenic(struct SCENIC* scenic)
{
	int v0 = 0;																//记录要删除的景点
	RECT r = { 0, 0, 570, 399 };											//显示框找中心
	FILE* fp = NULL;														//文件指针，打开“map_msg.txt”
	struct NODE* p = NULL;													//遍历邻接表用
	extern int num_node;													//全局变量，记录景点数

	closegraph();															//关闭窗口
	initgraph(1366,900);													//重开窗口
	v0 = chose_node(scenic);												//获取要删除点的位置
	fillcircle((scenic + v0)->x, (scenic + v0)->y, R);						//标记要删除的景点

	if (v0 == -1)															//直接退出
	{
		closegraph();
		return;
	}
	else
	{
		closegraph();														//关闭窗口
		fopen_s(&fp, "../Data/map_msg.txt", "w");							//打开“map_msg.txt”，并清空
		if (fp == NULL)
			exit(0);
		for (int i = 0; i < num_node; i++)
		{
			if (i == v0)													//要删除的景点直接跳过
				continue;
			else
			{
				fprintf_s(fp, "%s %d %d %s %s", (scenic + i)->name, (scenic + i)->x, (scenic + i)->y, (scenic + i)->introduction, (scenic + i)->picture);
				for (p = (scenic + i)->head; p != NULL; p = p->next)		//保存邻接表内容
				{
					if (p->adjvex - 1 == v0)								//邻接到要删除的景点
						continue;
					else if (p->adjvex - 1 < v0)
						fprintf_s(fp, " %d %.1f", p->adjvex, p->weight);
					else if (p->adjvex - 1 > v0)
						fprintf_s(fp, " %d %.1f", p->adjvex - 1, p->weight);
				}
			}
			fprintf(fp, " %d %.1f\n",0,0.0);								//加入换行
		}
		fclose(fp);																//关闭“map_msg.txt”
		num_node--;																//景点总数减一
		initgraph(600, 400);													//重开窗口
		loadimage(NULL, _T("../Picture/login2.jpg"));							//加载显示背景图
		drawtext(_T("删除成功！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//反馈消息
		Read_Map(scenic);
		Sleep(1000);															//显示延时
		closegraph();
	}
	return;
}

//增加景点
void add_scenic(struct SCENIC* scenic)
{
	MOUSEMSG mouse;															//定义鼠标信息结构体
	RECT r = { 0, 0, 570, 399 };											//显示框找中心
	FILE* fp = NULL;														//打开“pam_msg.txt”的文件指针
	struct NODE* p = NULL, * q = NULL;										//遍历邻接表用
	struct NODE* t = NULL;													//遍历邻接表用
	extern int num_node;													//全局变量，记录景点数
	char wei[UNIT_SIZE] = "\0";												//缓冲区

	
	closegraph();															//关闭窗口
	if (num_node == MAX_NODE)												//景点数已满
	{
		initgraph(600, 400);													//初始化框
		loadimage(NULL, _T("../Picture/login2.jpg"));							//加载显示背景图
		drawtext(_T("景点数已达最大值"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//反馈消息
		Sleep(1500);															//延时显示
		closegraph();															//关闭框
		return;
	}
	initgraph(1366, 900);													//重开窗口
	loadimage(NULL, _T("../Picture/Xi'an_map2.jpg"));						//加载背景图
	setlinecolor(BLUE);														//设置划线颜色为蓝
	setfillcolor(RED);														//设置填充颜色为红
	for (int count = 0; count < num_node; count++)
	{
		fillcircle((scenic + count)->x, (scenic + count)->y, 10);			//标记景点，显示景点名称
		outtextxy((scenic + count)->x, (scenic + count)->y, (scenic + count)->name);
	}
	outtextxy(1000, 0, _T("请用鼠标点击新景点在地图上的位置"));					//显示提示消息
	Sleep(500);
	while (TRUE)															//获取新景点的坐标
	{
		mouse = GetMouseMsg();												//获取鼠标当前信息	
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
		{
			closegraph();
			return;															//点击到“退出”
		}
		else if((mouse.uMsg == WM_LBUTTONDOWN) && !((mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710)))
		{
			setfillcolor(GREEN);											//设置填充颜色为绿
			fillcircle(mouse.x, mouse.y, R);								//标记新结点
			break;															//获取到新景点坐标
		}
		Sleep(10);
	}
	(scenic + num_node)->x = mouse.x;										//保存新景点的x坐标
	(scenic + num_node)->y = mouse.y;										//保存新结点的y坐标
	(scenic + num_node)->head = (struct NODE*)malloc(sizeof(struct NODE));	//申请第一个邻接表空间
	for (q = p = (scenic + num_node)->head; TRUE; p = p->next)
	{
		if (p == NULL)
			exit(0);
		p->adjvex = chose_node(scenic) + 1;									//选择邻接点
		if (p->adjvex == 0)													//点击了退出
		{
			if ((scenic + num_node)->head == p)								//没有添加邻接点
			{
				closegraph();												//关闭框
				initgraph(600, 400);										//初始化框
				loadimage(NULL, _T("../Picture/login2.jpg"));				//加载背景图
				drawtext(_T("创建失败！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//反馈消息
				Sleep(1500);												//延时显示
				Read_Map(scenic);											//恢复景点信息
				closegraph();												//关闭框
				return;
			}
			else															//创建成功
			{
				free(p);													//释放掉最后一个空结点
				q->next = NULL;												//维护邻接表
				break;
			}
		}
		InputBox(wei, BUFFER_SIZE, _T("请输入路程："));						//输入路程
		p->weight = (float)atof(wei);										//将字符串转化为float存入权值
		for (t = (scenic + p->adjvex - 1)->head; t->next != NULL; t = t->next)//找到邻接点的最后一个结点
			continue;
		t->next = (struct NODE*)malloc(sizeof(struct NODE));				//增添新邻接点
		if (t->next == NULL)
			exit(0);
		t->next->adjvex = num_node + 1;										//维护邻接点位置
		t->next->weight = p->weight;										//维护弧的权值
		t->next->next = NULL;												//维护
		q = p;																//用q跟踪上一结点
		p->next = (struct NODE*)malloc(sizeof(struct NODE));				//申请新的空间
	}
	InputBox((scenic + num_node)->name, BUFFER_SIZE, _T("请输入新景点的名称"));//输入名称
	InputBox((scenic + num_node)->introduction, BUFFER_SIZE, _T("请输入新景点介绍文件的路径(相对路径)"));//输入介绍文件路径
	InputBox((scenic + num_node)->picture, BUFFER_SIZE, _T("请输入新景点照片的路径(相对路径)"));//输入照片路径
	fopen_s(&fp, (scenic + num_node)->introduction, "r");					//打开介绍文件
	if (fp == NULL)
		exit(0);
	fscanf_s(fp, "%s", (scenic + num_node)->idt, 12 * UNIT_SIZE);			//读入介绍
	fclose(fp);																//关闭介绍文件
	num_node++;																//景点数加一
	fopen_s(&fp, "../Data/map_msg.txt", "w");								//以写入形式打开“map_msg.txt”，并清空
	if (fp == NULL)
		exit(0);
	for (int i = 0; i < num_node; i++)										//更新“map_msg.txt”文件
	{
		fprintf_s(fp, "%s %d %d %s %s", (scenic + i)->name, (scenic + i)->x, (scenic + i)->y, (scenic + i)->introduction, (scenic + i)->picture);
		for (t = (scenic + i)->head; t != NULL; t = t->next)
			fprintf_s(fp, " %d %.1f", t->adjvex, t->weight);
		fprintf_s(fp, " %d %.1f\n", 0, 0.0);
	}
	fclose(fp);																//关闭“map_msg.txt”
	closegraph();															//关闭框
	initgraph(600, 400);													//初始化框
	loadimage(NULL, _T("../Picture/login2.jpg"));							//加载显示背景图
	drawtext(_T("创建成功！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//反馈消息
	Sleep(1500);															//延时显示
	closegraph();															//关闭框

	return;
}

//使用备份的“map_msg.txt”
void init_map_msg()
{
	FILE* msg = NULL;																//文件指针
	RECT r = { 0, 0, 570, 399 };													//显示框找中心
	struct NODE* p = NULL, * q = NULL;												//遍历邻接表
	extern int num_node;															//全局变量，记录景点数
	struct SCENIC* scenic;

	scenic = (struct SCENIC*)malloc(MAX_NODE * sizeof(struct SCENIC));
	if (scenic == NULL)
		exit(0);
	fopen_s(&msg, "../Backup/map_msg.txt", "r");									//打开备份“map_msg.txt”
	if (msg == NULL)
		exit(0);
	for (int count = 0; (EOF != fscanf_s(msg, "%s", (scenic + count)->name, UNIT_SIZE) && count < MAX_NODE); count++)	//读取“map_msg.txt”文件，读入景点名称
	{
		fscanf_s(msg, "%d", &((scenic + count)->x));								//读入景点的X坐标
		fscanf_s(msg, "%d", &((scenic + count)->y));								//读入景点的Y坐标
		fscanf_s(msg, "%s", (scenic + count)->introduction, UNIT_SIZE);				//读入景点介绍文件的路径
		fscanf_s(msg, "%s", (scenic + count)->picture, UNIT_SIZE);					//读入景点图片文件的路径
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
	fclose(msg);															//关闭备份“map_msg.txt”
	fopen_s(&msg, "../Data/map_msg.txt", "w");								//打开“map_msg.txt”
	if (msg == NULL)
		exit(0);
	for (int i = 0; i < 18; i++)											//更新“map_msg.txt”文件
	{
		fprintf_s(msg, "%s %d %d %s %s", (scenic + i)->name, (scenic + i)->x, (scenic + i)->y, (scenic + i)->introduction, (scenic + i)->picture);
		for (p = (scenic + i)->head; p != NULL; p = p->next)
			fprintf_s(msg, " %d %.1f", p->adjvex, p->weight);
		fprintf_s(msg, " %d %.1f\n", 0, 0.0);
	}
	closegraph();															//关闭框
	initgraph(600, 400);													//初始化框
	loadimage(NULL, _T("../Picture/login2.jpg"));							//加载背景图
	drawtext(_T("初始化成功！请重新启动程序"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//反馈消息
	Sleep(1500);															//延时显示
	closegraph();															//关闭框
	return;
}

//用Prim算法求最小生成树
void Prim(struct SCENIC* scenic)
{
	int flag[MAX_NODE];														//该结点是否已经加入最小生成树
	extern int num_node;													//全局变量，记录景点数
	MOUSEMSG mouse;															//定义鼠标信息结构体
	RECT rect = { 0,0,0,0 };												//路程显示框
	struct NODE* p = NULL;													//遍历邻接表用的指针
	struct NODE temp = { 0,0XFFFF,NULL };									//找最小
	char s[UNIT_SIZE] = "\0";												//缓冲区
	int i = 0, j = 0;														//计数器

	initgraph(1366, 900);													//初始化绘图框
	loadimage(NULL, _T("../Picture/Xi'an_map2.jpg"));						//加载背景图
	setlinecolor(BLUE);														//设置划线颜色为蓝
	setfillcolor(RED);														//设置填充颜色为红
	for (int count = 0; count < num_node; count++)
	{
		fillcircle((scenic + count)->x, (scenic + count)->y, 10);			//标记出所有景点
		outtextxy((scenic + count)->x, (scenic + count)->y, (scenic + count)->name);//显示景点名称
		for (p = (scenic + count)->head; p != NULL; p = p->next)			//连线
		{
			line((scenic + count)->x, (scenic + count)->y, (scenic + p->adjvex - 1)->x, (scenic + p->adjvex - 1)->y);
			_gcvt_s(s, UNIT_SIZE, (double)p->weight, 4);					//将路程转换为字符串
			if ((scenic + count)->x < (scenic + p->adjvex - 1)->x)
				rect = { (scenic + count)->x - 8,(scenic + count)->y,(scenic + p->adjvex - 1)->x + 8, (scenic + p->adjvex - 1)->y };
			else
				rect = { (scenic + p->adjvex - 1)->x - 8, (scenic + p->adjvex - 1)->y,(scenic + count)->x + 8,(scenic + count)->y };
			drawtext(s, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);								//显示路程
		}
	}
	setlinecolor(GREEN);													//设置划线颜色为绿色
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	for (i = 0; i < MAX_NODE; i++)											//初始化
		flag[i] = 0;
	flag[0] = 1;															//从第零号位置开始
	for (int count = 0; count < num_node - 1; count++)						//共num_node-1条边
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
	setlinecolor(BLUE);														//设置划线颜色为蓝
	while (1)
	{
		mouse = GetMouseMsg();												//获取鼠标当前信息	
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 1235 && mouse.x <= 1335) && (mouse.y >= 650 && mouse.y <= 710))
			break;															//鼠标左键按下退出				
	}
	closegraph();
	return;
}
