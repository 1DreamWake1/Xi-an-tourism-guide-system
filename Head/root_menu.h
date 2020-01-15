#ifndef ROOT_MENU_H
#define ROOT_MENU_H

#include<read_map.h>
#include<login.h>
#include<graphics.h>

#define MAX_USER 5																	//����û���

void show_root_menu(struct SCENIC*);												//��ʾroot�û��Ĺ���˵�����
void add_user(void);																//�����û�
void delete_user(void);																//ɾ���û�
void change_passwd(void);															//�����û�����
void show_adj(struct SCENIC*);														//��ʾͼ
void delete_scenic(struct SCENIC*);													//ɾ������
void add_scenic(struct SCENIC*);													//���Ӿ���
void init_map_msg(void);															//ʹ�ñ��ݵġ�map_msg.txt��
void Prim(struct SCENIC*);															//��Prim�㷨����С������

#endif
