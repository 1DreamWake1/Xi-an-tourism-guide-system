#ifndef LOGIN_H
#define LOGIN_H

#define EXIT		 0					//�˳�����
#define ID_ROOT		 1					//root�û����û�ID
#define ID_USER		 2					//��ͨ�û����û�ID
#define BUFFER_SIZE	 50					//��������С

struct USER_MSG {						//�û������Ϣ�ṹ��
	char name[BUFFER_SIZE] = "\0";		//�û�����
	char passwd[BUFFER_SIZE] = "\0";	//�û�����
	char User_ID[BUFFER_SIZE] = "\0";	//�û�ID
};

int login(void);						//��¼���������õ�¼���棬���ص�¼�û����û�ID���Դ��б�root�û�����ͨ�û�
int check_name(struct USER_MSG*);		//�û���Ϣ��֤�����������û���Ϣ�Ľṹ��ָ�룬���������û�������1
void logout(void);						//�˳�

#endif
