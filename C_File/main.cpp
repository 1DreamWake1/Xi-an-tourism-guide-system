#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<login.h>
#include<map.h>
#include<read_map.h>
#include<root_menu.h>

int ID = ID_USER;															//ȫ�ֱ�������¼�û�Ȩ�ޱ�־
int num_node = 0;															//ȫ�ֱ�������¼������

int main()
{
	struct SCENIC* scenic = NULL;
	
	scenic = (struct SCENIC*)malloc(MAX_NODE * sizeof(struct SCENIC));		//�����ڽӱ�Ŀռ�
	if (scenic == NULL)
		exit(0);
	Read_Map(scenic);														//����map_msg.txt���е���Ϣ����ṹ�壬�ڽӱ�
	//Check_Read_Map(scenic);												//�������ӡ�map_msg.txt���͡�introduce.txt���������Ϣ
		
	while (TRUE)
	{
		ID = login();														//��¼����¼��¼�û���Ȩ����Ϣ
		if (ID == ID_USER)													//��¼��Ϊ��ͨ�û�
			show_user_map(scenic);
		else if (ID == ID_ROOT)												//��¼��Ϊroot�û�
			show_root_menu(scenic);
		else if (ID == EXIT)												//�˳�����
			break;
	}
	logout();																//��ʾ�˳�����
	
	return 0;
}
