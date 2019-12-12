#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h> 
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define get(type) (type *)malloc(sizeof(type))//����ռ�

typedef struct list LIST; //�ļ��Ľṹ�� 
struct list
{
	char listname[10];    //�ļ�������
	int type;
	int length;         //�ļ�����
	int protect;        //����ģʽ��0Ϊֻ��1Ϊ�ɶ�д
	int flag;           //��־
	char* content;      //�ļ������û� 
	struct list* parent;
	struct list* child;
	struct list* next;
};

typedef struct usd USD; //�û��Ľṹ�� 
struct usd
{
	char username[10];   //�û�������
	LIST* list;  //�ļ� 
	struct usd* next;
};

void creatuser();///�½��û�
void displayusermenu();      //��ʾ�û��˵�
void userhelp();        //����������ļ� 
void displayuser();     //��ʾ�û���
void selectuser();      //ѡ���û�
void displayfilemenu();//��ʾ�ļ�����Ŀ¼ 
void creatfile(LIST* qq, int flag);///�����ļ�
void deletefile(LIST* qq, int flag);///ɾ���ļ�
void openfile();///���ļ�
void readfile();  ///��ȡ�ļ�
void writefile(); ///д���ļ�
void closefile();///�ر��ļ�
void displaylist();////��ʾ�ļ��б� 
void quit();///ֱ���˳�ϵͳ

USD* user = NULL, *currentuser = NULL;
LIST* list = NULL, *currentlist = NULL, *copylist = NULL;

int main()   //������
{
	displayusermenu();//�ʼִ���û��������	
	return 0;

}

void displayusermenu()      /////��ʾ�û��˵�
{
	//	system("cls");////����
	int button;
	printf("\n--------�ļ�����ϵͳ----------\n");
	printf("--------����ѡ��-------\n\n");
	printf("1���½��û�\n");
	printf("2��ѡ���û�\n");
	printf("3�������ĵ�\n");
	printf("4���˳�ϵͳ\n");
	printf("\t�밴����ѡ����Ӧ�Ĳ���:");
	scanf("%d", &button);
	switch (button)
	{
	case 1:
		creatuser();
		break;  //�������û�
	case 2:
		selectuser();
		displayfilemenu();
		break;  //ѡ��һ���û�
	case 3:
		userhelp();///����
		getch();
		displayusermenu();
		break;
	case 4:
		system("cls");//�˳�
		printf("\n\n\n��ӭ�ٴ�ʹ��!!\n\n");
		getch();
		exit(0);
		break;
	}
}
void creatuser()   ///�����û�
{
	int i;
	char s;
	USD* p, *q = user;
	p = get(USD);
	for (i = 1; q != NULL; i++)q = q->next;     // iָʾ��ǰ�û�����
	q = user;
	printf("\n����һ�����û�\n");
	printf("\n�������û���: ", i);
	scanf("%s", p->username);   //�������û�������
	LIST* l = list;
	l = get(LIST);
	strcpy(l->listname, p->username);
	l->next = NULL;
	l->type = 1;
	l->parent = NULL;
	l->child = NULL;
	p->list = l;
	p->next = NULL;
	if (user == NULL)
	{
		user = p;  //��userΪ�գ����P����user
	}
	else  //��user��Ϊ�գ������о��û�����
	{
		while (q->next != NULL) {            //Ѱ�����һ���û�
			if (strcmp(p->username, q->username) == 0) {             //�Ƚϣ���ϵͳ�Ƿ��Ѿ����ڸ��û�
				printf("\n���������ԣ�\n\n");  ///��ʾ������Ϣ
				getchar(); getchar();
				displayusermenu();
			}
			q = q->next;
		}
		if (strcmp(p->username, q->username) == 0) {///�����ʾ��������ʾ��Ϣ
			printf("\n���û��Ѿ�����!�޷��������û�!\n\n");
			getchar(); getchar();
			displayusermenu();
		}
		q->next = p;        //����Ѱ����һ���ַ�		
	}
	printf("\n�����û��ɹ�\n");  //������һ���û�
	displayusermenu();
}

void selectuser()      //ѡ���û�
{
	char n[10];
	USD* p = user;
	displayuser(); //��ʾ�û��б� 

	if (!p)
	{
		printf("\n��ȷ���Ƿ��Ѿ������û������ԣ������´����û�!!!\n");   //û���û�
		getchar(); getchar();
		displayusermenu();
	}

	printf("\n\n�������û���:");
	scanf("%s", n);      //�����û���
	while (p != NULL)
	{
		if (strcmp(p->username, n) == 0)        //����Ƚ�Ѱ���û�
		{
			currentuser = p;      //�ҵ���Ӧ�û������currentuserָ����û�
			currentlist = p->list; //�� currentlistָ����û�����Ӧ���ļ� 
			printf("%s\n", currentlist->listname);
			return;
		}
		else
		{
			p = p->next;
		}
	}
	if (p == NULL)       //�Ҳ����û�
	{
		printf("\n\n���û�������!!!");
		getchar();
		displayusermenu();
	}
}

void displayfilemenu()                  //��ʾ�ļ���������˵�
{
	int choice;
	LIST* p = currentlist;
	printf("\n��ã���ӭ�����ļ�����ϵͳ\n", currentuser->username);//��ʾ��Ϣ
	printf("\n  ��ǰ���ļ�·��:");//����Ŀ¼��ַ
	do {
		printf("<%s", p->listname);
		p = p->parent;
	} while (p != NULL);
	printf(" ----------------- ����ѡ��-------------\n\n");//�˵�
	printf("1���½��ļ� \n");
	printf("2��ɾ���ļ� \n");
	printf("3�����ļ� \n");
	printf("4�������ļ� \n");
	printf("5��д���ļ� \n");
	printf("6���ر��ļ� \n");
	printf("7����ʾ�ļ��б� \n");
	printf("8�������û�����˵�\n");
	printf("9���˳�ϵͳ \n");
	printf(" ----------------------------------------\n\n");
	printf("������ѡ����Ӧ�Ĳ��� ");
	scanf("%d", &choice);
	printf("\n");
	switch (choice)//switch���
	{
	case 1:
		creatfile(currentlist, 0);
		break;     //�����ļ�
	case 2:
		deletefile(currentlist, 0);
		break;              //ɾ���ļ�
	case 3:
		openfile();
		break;        //���ļ�
	case 4:
		readfile();
		displayfilemenu();
		break;          //�����ļ�
	case 5:
		writefile();
		displayfilemenu();
		break;      //д���ļ�
	case 6:
		closefile();
		break;      //�ر��ļ�
	case 7:
		displaylist();///��ʾ�ļ�
		getch();
		displayfilemenu();
		break;
	case 8:
		displayusermenu();
		break;     //�˳����������û�����˵�
	case 9:
		quit();
		break;
	default:
		printf("\n\n�����������!����������!!!\n");
		getch();
		displayfilemenu();
		break;      //�Ƿ����룬�����ļ�����˵���������
	}
}

void displayuser()     //��ʾ�û���
{
	int i = 0;
	USD* temp = user;
	printf("\n  �û��б����£�\n");
	while (temp != NULL)
	{
		i++;
		printf("  * NO.%d: %s *\n", i, temp->username);
		temp = temp->next;
	}
	if (user == NULL)
	{
		printf(" \n��ϵͳ�����û�!");
	}
	printf("\n\n");
}

void creatfile(LIST* qq, int flag)        //�����ļ�
{
	LIST* temp;
	LIST* p = qq->child;
	LIST* q;
	temp = get(LIST);
loop:
	q = qq->child;
	if (flag == 0)
	{
		printf("\n����һ�����ļ�\n");
		printf("\n�������½��ļ���: ");     //�����ļ���
	}

	scanf("%s", temp->listname);
	while (q != NULL)
	{
		if (strcmp(temp->listname, q->listname) == 0)
		{
			printf("\n�������ļ�!����������!");
			goto loop;
		}
		q = q->next;
	}
	temp->content = NULL;
	printf("\n�ļ�����: 0��ֻ��Read\t  1������дRead&Write");     //���ñ���ģʽ
	printf("\n\n��ѡ���ļ����ԣ� ");
	scanf("%d", &temp->protect);
	if (temp->protect != 0 && temp->protect != 1)
	{
		printf("\n\n����ѡ����ļ���������!�����������ļ����ԣ� ");
		scanf("%d", &temp->protect);
	}
	if (flag == 0)
	{
		printf("\n��������ļ��ĳ���: ");        //�����ļ����ȣ���д���ļ�ʱ���õ�
		scanf("%d", &temp->length);
	}
	if (flag == 0)
		temp->type = 0; //0Ϊ�ļ�
	else temp->type = 1;
	temp->flag = 0;     //�ļ�Ĭ��Ϊ�ر�״̬���Ժ���Ҫʱ�ٴ�
	temp->child = NULL;
	temp->next = NULL;
	temp->parent = currentlist;
	if (p == NULL)
	{
		qq->child = temp;
	}
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = temp;
	}
	printf("�����ļ��ɹ���\n\n");

	getchar();
	displayfilemenu();
}
void deletefile(LIST* qq, int flag)      //ɾ���ļ�(��)
{
	char n[10];
	LIST* p = qq->child;
	LIST* pre = NULL;
	if (flag == 0)
	{
		printf("\n[ɾ��һ���ļ�]\n");
		printf("\n������Ҫɾ�����ļ���: ");
	}
	else
	{
		printf("\n[ɾ���ļ���]\n");
		printf("\n������Ҫɾ�����ļ�����: ");
	}
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0))
		{
			if (pre == NULL)  //��һ���ڵ�
			{
				qq->child = p->next; free(p);
				printf("\n\n�ļ�%s��ɾ���ɹ�!!!\n", n);
			}
			else
			{
				pre->next = p->next;  //��ǰһ��ָ���NEXTָ��N��ǰָ���NEXT����ɾ�����ļ�
				printf("\n\n�ļ�%s��ɾ���ɹ�!!!\n", n);
				free(p);
			}
			break;
		}
		else if ((strcmp(p->listname, n) == 0) && (p->type == 1))
		{
			if (pre == NULL)  //��һ���ڵ�
			{
				qq->child = p->next; free(p);
				printf("\n\n�ļ���%s�Ѿ��ɹ�ɾ��!!!\n", n);
			}
			else
			{
				pre->next = p->next;  //��ǰһ��ָ���NEXTָ��N��ǰָ���NEXT����ɾ�����ļ�
				printf("\n\n�ļ���%s�Ѿ��ɹ�ɾ��!!!\n", n);
				free(p);
			}
			break;
		}
		else
		{
			pre = p;
			p = p->next;
		}

	}
	if (p == NULL && flag == 0)      //���ļ�������
		printf("\n\n�Ҳ������ļ�!");
	else if (p == NULL && flag == 1) printf("\n\n�Ҳ������ļ���!\n");
	getchar();
	getchar();
	displayfilemenu();
}

void openfile() ////���ļ�
{
	char n[10];
	LIST* p = currentlist->child;
	printf("\n[��һ���ļ�]\n");
	printf("\n������Ҫ�򿪵��ļ���: ");//�����ļ���
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 0))//�Ƚ��ļ���Ѱ��Ҫ�򿪵��ļ�
		{
			p->flag = 1;
			printf("\n�ļ�%s�ɹ���!!!\n", n);
			break;
		}
		else if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 1))
		{
			printf("\n�ļ�%s���Ѿ�!!!\n", n);
			break;
		}
		p = p->next;
	}
	if (p == NULL)
	{
		printf("\n\n�Ҳ������ļ�!\n");
	}
	getchar();
	getchar();
	displayfilemenu();
}

void readfile()     //�����ļ�
{
	char n[10];
	LIST* p = currentlist->child;
	printf("\n[��ȡһ���ļ�]\n");
	printf("\n\n������Ҫ�����ļ���: ");
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 1))//�Ƚ�
		{
			printf("\n�ļ�%s������:%s", p->listname, p->content);
			getchar(); getchar();
			return;
		}
		p = p->next;
	}
	printf("\n\n���ļ�ʧ��,��ȷ�ϸ��ļ��Ƿ��Ѿ��򿪻��ļ��Ƿ����!\n");
	getchar();
	getchar();
}

void writefile()      //д���ļ�
{
	char n[10], *temp;
	LIST* p = currentlist->child;
	printf("\n[д���ļ�]\n");
	printf("\n������Ҫд���ļ���: ");
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0))
		{
			if (p->flag == 0)
			{
				printf("\n�ļ�δ�򿪣��޷�д��!�뽫�ļ��ô�״̬!!!\n"); getchar(); getchar(); system("cls");
			}
			else if (p->protect == 0)
			{
				printf("\n\n��������!���ļ�����д!!!\n");    //���ļ����ƶ�д
				getchar();
				return;
			}
			else
			{
				temp = (char*)malloc(sizeof(char) * p->length);
				printf("\n\n�������ļ�����(length<=%d):\n\n\t", p->length);
				scanf("%s", temp);
				p->content = temp;
				getchar();
			}
			return;
		}
		p = p->next;
	}
	printf("\n\n���ļ�������!��ȡʧ��!!!\n");//��ʾ
	getchar();
	getchar();
}

void closefile()     //�ر��ļ�
{
	char n[10];
	LIST* p = currentlist->child;
	printf("\n[�ر�һ���ļ�]\n");
	printf("\n������Ҫ�رյ��ļ���: ");
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 1))//Ѱ����Ҫ�ļ�
		{
			p->flag = 0;
			printf("\n�ļ�%s�رճɹ�.\n", n);
			break;
		}
		else if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 0))
		{
			printf("\n�ļ�%s�Ѿ��ر�.\n", n);
			break;
		}
		p = p->next;
	}
	if (p == NULL)
	{
		printf("\n\n�Ҳ������ļ�!\n");
	}
	getchar();
	getchar();
	displayfilemenu();/////�����ļ�����˵�
}

void displaylist()////��ʾ�ļ�
{
	LIST* p = currentlist->child;
	if (p == NULL)
	{
		printf("\n���û�û���κ��ļ�\n\n");
		return;
	}
	else
	{
		printf("\n��ǰ�û��µ��ļ�Ϊ��\n");
		printf("\n�ļ���\t\t�ļ�����\n");
	}
	while (p != NULL)
	{
		if (p->type == 0)
			printf("\n%s�ļ�\t\t%d\n", p->listname, p->protect);
		p = p->next;
	}
	printf("\n -----------------------------------------------------------\n\n");

}

void userhelp()//����
{
	printf("\n  ----------[�û�������������֧��]-------------\n\n");

	printf("1���½��û���ÿ�ο����½�һ���û�\n\n");
	printf("2��ѡ���û���ѡ��һ���û������ļ�����\n\n");
	printf("3�������ĵ����ṩ�����������Ϣ\n\n");
	printf("4���˳�ϵͳ���˳�ģ���ļ�����ϵͳ\n\n");
	printf("  --------------------------------------------------\n\n");
}
void quit()///ֱ���˳�
{
	char c;
	printf("\nȷ��ֱ���˳���(Y/N):");
	scanf("%s", &c);
	printf("\n");
	if (c == 'Y' || c == 'y')
	{
		printf("\n\nллʹ��!�ټ�!!!\n\n");
		getch();
		exit(0);
	}
	else
		displayfilemenu();
}

