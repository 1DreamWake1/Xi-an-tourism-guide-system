#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<login.h>
#include<map.h>
#include<read_map.h>
#include<root_menu.h>

int ID = ID_USER;															//全局变量，登录用户权限标志
int num_node = 0;															//全局变量，记录景点数

int main()
{
	struct SCENIC* scenic = NULL;
	
	scenic = (struct SCENIC*)malloc(MAX_NODE * sizeof(struct SCENIC));		//申请邻接表的空间
	if (scenic == NULL)
		exit(0);
	Read_Map(scenic);														//将“map_msg.txt”中的信息读入结构体，邻接表
	//Check_Read_Map(scenic);												//检测输出从“map_msg.txt”和“introduce.txt”读入的信息
		
	while (TRUE)
	{
		ID = login();														//登录，记录登录用户的权限信息
		if (ID == ID_USER)													//登录者为普通用户
			show_user_map(scenic);
		else if (ID == ID_ROOT)												//登录者为root用户
			show_root_menu(scenic);
		else if (ID == EXIT)												//退出程序
			break;
	}
	logout();																//显示退出窗口
	
	return 0;
}
