#include<graphics.h>
#include<string.h>
#include<stdio.h>
#include<login.h>

//��¼���������õ�¼���棬���ص�¼�û����û�ID���Դ��б�root�û�����ͨ�û�
int login()
{
	MOUSEMSG mouse;												//�����ȡ�����Ϣ�Ľṹ�����
	IMAGE bg_img;												//���屳��ͼƬ�ṹ�����
	RECT r = { 0, 0, 570, 399 };								//��ʾ��������
	char passwd[BUFFER_SIZE];									//�û����������
	struct USER_MSG user_msg;									//����洢�û���Ϣ�Ľṹ��
	int count;													//�����������������

	initgraph(600, 400);										//�򿪵�¼����
	loadimage(&bg_img, _T("../Picture/login3.jpg"));			//��ȡ����ͼƬ
	putimage(0, 0, &bg_img);									//��ʾ����ͼƬ
	outtextxy(490, 350, _T("��    ����V1.0"));					//��ʾ�汾��������Ϣ
	outtextxy(490, 370, _T("�����ˣ�������"));					//��ʾ�汾��������Ϣ
	//rectangle(195,335,270,375);								//����¼����ť�Ĵ�����Χ
	//rectangle(300,335,375,375);								//���˳�����ť�Ĵ�����Χ
	for (mouse = GetMouseMsg(); true; Sleep(10),mouse = GetMouseMsg())
	{
		if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 195 && mouse.x <= 270) && (mouse.y >= 335 && mouse.y <= 375))
			break;												//�����¡���¼���󣬽����¼����
		else if ((mouse.uMsg == WM_LBUTTONDOWN) && (mouse.x >= 300 && mouse.x <= 375) && (mouse.y >= 335 && mouse.y <= 375))
			return EXIT;										//�����¡��˳������˳�����
	}
	
	loadimage(&bg_img, _T("../Picture/login2.jpg"));			//��ȡ����ͼƬ
	putimage(0, 0, &bg_img);									//��ʾ����ͼƬ
	InputBox(user_msg.name, BUFFER_SIZE, _T("�������û������ο�ֱ�ӵ����ȷ����"));//�û������û���
	if (user_msg.name[0] == '\0')
	{
		drawtext(_T("��ӭ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		Sleep(1000);												//��ʱ
		closegraph();												//�رյ�¼��
		return ID_USER;
	}
	while (0 == check_name(&user_msg))							//���������û����Ƿ����
		InputBox(user_msg.name, BUFFER_SIZE, _T("���û������ڣ������������û���"));
	for (count = 0; TRUE; count++)								//�������벢���
	{
		InputBox(passwd, BUFFER_SIZE, _T("����������(��3�λ���)"));
		if (count >= 3)											//����������󳬹���������
			return EXIT;
		if (0 == strcmp(passwd, user_msg.passwd))
			break;
	}
	char welcome[BUFFER_SIZE] = "Welcome ";						//���延ӭ��Ϣ
	strcat_s(welcome, BUFFER_SIZE, user_msg.name);				//���û�����ӵ���ӭ��Ϣ�в���ʾ
	drawtext(_T(welcome), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1000);												//��ʱ
	closegraph();												//�رյ�¼��
	if (0 == strcmp(user_msg.name, _T("root")))					//�жϵ�¼�û��Ƿ�Ϊroot
		return ID_ROOT;
	else
		return ID_USER;
}

//�û���Ϣ��֤�����������û���Ϣ�Ľṹ��ָ�룬���������û�������1
int check_name(struct USER_MSG* user_msg)
{
	FILE* fp;													//�����ļ�ָ�룬��ȡpasswd.txt�ļ�
	struct USER_MSG temp;										//����洢�ļ����м�ṹ�����
	
	fopen_s(&fp, "../Data/passwd.txt", "r");					//��passwd.txt�ļ�
	if (fp == NULL)
		exit(0);
	while (EOF != fscanf_s(fp, "%s", temp.name, BUFFER_SIZE))	//�����û���
	{			
		fscanf_s(fp, "%s", temp.passwd, BUFFER_SIZE);			//��������
		fscanf_s(fp, "%s", temp.User_ID, BUFFER_SIZE);			//�����û�ID
		if (0 == strcmp(user_msg->name, temp.name))				//�û���ƥ��ɹ�
		{
			strcpy_s(user_msg->passwd, temp.passwd);			//�����뷵��
			fclose(fp);											//�ر��ļ�
			return 1;
		}
	}
	fclose(fp);													//�ر��ļ�
	return 0;													//û�д��û�
}

//�˳�
void logout()
{
	initgraph(600, 400);										//��������
	loadimage(NULL, _T("../Picture/login2.jpg"));				//������ʾ����ͼƬ
	RECT r = { 0, 0, 570, 399 };								//��ʾ��������
	drawtext(_T("See You!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1500);												//��ʱ
	closegraph();												//�رմ���
	return;
}
