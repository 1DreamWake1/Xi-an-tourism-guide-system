#ifndef LOGIN_H
#define LOGIN_H

#define EXIT		 0					//退出程序
#define ID_ROOT		 1					//root用户的用户ID
#define ID_USER		 2					//普通用户的用户ID
#define BUFFER_SIZE	 50					//缓冲区大小

struct USER_MSG {						//用户身份信息结构体
	char name[BUFFER_SIZE] = "\0";		//用户姓名
	char passwd[BUFFER_SIZE] = "\0";	//用户密码
	char User_ID[BUFFER_SIZE] = "\0";	//用户ID
};

int login(void);						//登录函数，调用登录界面，返回登录用户的用户ID，以此判别root用户和普通用户
int check_name(struct USER_MSG*);		//用户信息验证函数，接受用户信息的结构体指针，如果有这个用户，返回1
void logout(void);						//退出

#endif
