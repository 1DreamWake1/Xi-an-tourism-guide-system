#include<graphics.h>
#include<string.h>
#include<stdio.h>
#include<login.h>

//登录函数，调用登录界面，返回登录用户的用户ID，以此判别root用户和普通用户
int login()
{
	MOUSEMSG mouse;												//定义获取鼠标信息的结构体变量
	IMAGE bg_img;												//定义背景图片结构体变量
	RECT r = { 0, 0, 570, 399 };								//显示框找中心
	char passwd[BUFFER_SIZE];									//用户输入的密码
	struct USER_MSG user_msg;									//定义存储用户信息的结构体
	int count;													//输入密码次数计数器

	initgraph(600, 400);										//打开登录窗口
	loadimage(&bg_img, _T("../Picture/login3.jpg"));			//获取背景图片
	putimage(0, 0, &bg_img);									//显示背景图片
	outtextxy(490, 350, _T("版    本：V1.0"));					//显示版本和作者信息
	outtextxy(490, 370, _T("制作人：刘传玺"));					//显示版本和作者信息
	//rectangle(195,335,270,375);								//“登录”按钮的触发范围
	//rectangle(300,335,375,375);								//“退出”按钮的触发范围
	for (mouse = GetMouseMsg(); true; Sleep(10),mouse = GetMouseMsg())
	{
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 195 && mouse.x <= 270) && (mouse.y >= 335 && mouse.y <= 375))
			break;												//当点下“登录”后，进入登录界面
		else if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 300 && mouse.x <= 375) && (mouse.y >= 335 && mouse.y <= 375))
			return EXIT;										//当点下“退出”后，退出程序
	}
	
	loadimage(&bg_img, _T("../Picture/login2.jpg"));			//获取背景图片
	putimage(0, 0, &bg_img);									//显示背景图片
	InputBox(user_msg.name, BUFFER_SIZE, _T("请输入用户名，游客直接点击“确定”"));//用户输入用户名
	if (user_msg.name[0] == '\0')
	{
		drawtext(_T("欢迎！"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		Sleep(1000);												//延时
		closegraph();												//关闭登录框
		return ID_USER;
	}
	while (0 == check_name(&user_msg))							//检测输入的用户名是否存在
		InputBox(user_msg.name, BUFFER_SIZE, _T("该用户不存在，请重新输入用户名"));
	for (count = 0; TRUE; count++)								//输入密码并检测
	{
		InputBox(passwd, BUFFER_SIZE, _T("请输入密码(共3次机会)"));
		if (count >= 3)											//密码输入错误超过容忍上线
			return EXIT;
		if (0 == strcmp(passwd, user_msg.passwd))
			break;
	}
	char welcome[BUFFER_SIZE] = "Welcome ";						//定义欢迎消息
	strcat_s(welcome, BUFFER_SIZE, user_msg.name);				//将用户名添加到欢迎消息中并显示
	drawtext(_T(welcome), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1000);												//延时
	closegraph();												//关闭登录框
	if (0 == strcmp(user_msg.name, _T("root")))					//判断登录用户是否为root
		return ID_ROOT;
	else
		return ID_USER;
}

//用户信息验证函数，接受用户信息的结构体指针，如果有这个用户，返回1
int check_name(struct USER_MSG* user_msg)
{
	FILE* fp;													//定义文件指针，读取passwd.txt文件
	struct USER_MSG temp;										//定义存储文件的中间结构体变量
	
	fopen_s(&fp, "../Data/passwd.txt", "r");					//打开passwd.txt文件
	if (fp == NULL)
		exit(0);
	while (EOF != fscanf_s(fp, "%s", temp.name, BUFFER_SIZE))	//读入用户名
	{			
		fscanf_s(fp, "%s", temp.passwd, BUFFER_SIZE);			//读入密码
		fscanf_s(fp, "%s", temp.User_ID, BUFFER_SIZE);			//读入用户ID
		if (0 == strcmp(user_msg->name, temp.name))				//用户名匹配成功
		{
			strcpy_s(user_msg->passwd, temp.passwd);			//将密码返回
			fclose(fp);											//关闭文件
			return 1;
		}
	}
	fclose(fp);													//关闭文件
	return 0;													//没有此用户
}

//退出
void logout()
{
	initgraph(600, 400);										//创建窗口
	loadimage(NULL, _T("../Picture/login2.jpg"));				//加载显示背景图片
	RECT r = { 0, 0, 570, 399 };								//显示框找中心
	drawtext(_T("See You!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1500);												//延时
	closegraph();												//关闭窗口
	return;
}
