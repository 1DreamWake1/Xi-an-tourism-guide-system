#ifndef ROOT_MENU_H
#define ROOT_MENU_H

#include<read_map.h>
#include<login.h>
#include<graphics.h>

#define MAX_USER 5																	//最大用户数

void show_root_menu(struct SCENIC*);												//显示root用户的管理菜单界面
void add_user(void);																//增加用户
void delete_user(void);																//删除用户
void change_passwd(void);															//更改用户密码
void show_adj(struct SCENIC*);														//显示图
void delete_scenic(struct SCENIC*);													//删除景点
void add_scenic(struct SCENIC*);													//增加景点
void init_map_msg(void);															//使用备份的“map_msg.txt”
void Prim(struct SCENIC*);															//用Prim算法求最小生成树

#endif
