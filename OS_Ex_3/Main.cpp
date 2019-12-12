#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h> 
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define get(type) (type *)malloc(sizeof(type))//分配空间

typedef struct list LIST; //文件的结构体 
struct list
{
	char listname[10];    //文件名长度
	int type;
	int length;         //文件长度
	int protect;        //保护模式，0为只读1为可读写
	int flag;           //标志
	char* content;      //文件所在用户 
	struct list* parent;
	struct list* child;
	struct list* next;
};

typedef struct usd USD; //用户的结构体 
struct usd
{
	char username[10];   //用户名长度
	LIST* list;  //文件 
	struct usd* next;
};

void creatuser();///新建用户
void displayusermenu();      //显示用户菜单
void userhelp();        //主界面帮助文件 
void displayuser();     //显示用户名
void selectuser();      //选择用户
void displayfilemenu();//显示文件管理目录 
void creatfile(LIST* qq, int flag);///创建文件
void deletefile(LIST* qq, int flag);///删除文件
void openfile();///打开文件
void readfile();  ///读取文件
void writefile(); ///写入文件
void closefile();///关闭文件
void displaylist();////显示文件列表 
void quit();///直接退出系统

USD* user = NULL, *currentuser = NULL;
LIST* list = NULL, *currentlist = NULL, *copylist = NULL;

int main()   //主函数
{
	displayusermenu();//最开始执行用户管理界面	
	return 0;

}

void displayusermenu()      /////显示用户菜单
{
	//	system("cls");////清屏
	int button;
	printf("\n--------文件管理系统----------\n");
	printf("--------功能选择-------\n\n");
	printf("1、新建用户\n");
	printf("2、选择用户\n");
	printf("3、帮助文档\n");
	printf("4、退出系统\n");
	printf("\t请按功能选择相应的操作:");
	scanf("%d", &button);
	switch (button)
	{
	case 1:
		creatuser();
		break;  //创建新用户
	case 2:
		selectuser();
		displayfilemenu();
		break;  //选择一个用户
	case 3:
		userhelp();///帮助
		getch();
		displayusermenu();
		break;
	case 4:
		system("cls");//退出
		printf("\n\n\n欢迎再次使用!!\n\n");
		getch();
		exit(0);
		break;
	}
}
void creatuser()   ///创建用户
{
	int i;
	char s;
	USD* p, *q = user;
	p = get(USD);
	for (i = 1; q != NULL; i++)q = q->next;     // i指示当前用户个数
	q = user;
	printf("\n创建一个新用户\n");
	printf("\n请输入用户名: ", i);
	scanf("%s", p->username);   //输入新用户的名字
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
		user = p;  //若user为空，则把P复给user
	}
	else  //若user不为空，则以有旧用户存在
	{
		while (q->next != NULL) {            //寻找最后一个用户
			if (strcmp(p->username, q->username) == 0) {             //比较，看系统是否已经存在该用户
				printf("\n出错，请重试！\n\n");  ///提示出错信息
				getchar(); getchar();
				displayusermenu();
			}
			q = q->next;
		}
		if (strcmp(p->username, q->username) == 0) {///检查提示重名并提示信息
			printf("\n该用户已经存在!无法创建该用户!\n\n");
			getchar(); getchar();
			displayusermenu();
		}
		q->next = p;        //继续寻找下一个字符		
	}
	printf("\n创建用户成功\n");  //输入下一个用户
	displayusermenu();
}

void selectuser()      //选择用户
{
	char n[10];
	USD* p = user;
	displayuser(); //显示用户列表 

	if (!p)
	{
		printf("\n请确认是否已经创建用户后重试，或重新创建用户!!!\n");   //没有用户
		getchar(); getchar();
		displayusermenu();
	}

	printf("\n\n请输入用户名:");
	scanf("%s", n);      //输入用户名
	while (p != NULL)
	{
		if (strcmp(p->username, n) == 0)        //逐个比较寻找用户
		{
			currentuser = p;      //找到对应用户，则把currentuser指向该用户
			currentlist = p->list; //把 currentlist指向该用户所对应的文件 
			printf("%s\n", currentlist->listname);
			return;
		}
		else
		{
			p = p->next;
		}
	}
	if (p == NULL)       //找不到用户
	{
		printf("\n\n该用户不存在!!!");
		getchar();
		displayusermenu();
	}
}

void displayfilemenu()                  //显示文件管理操作菜单
{
	int choice;
	LIST* p = currentlist;
	printf("\n你好，欢迎进入文件管理系统\n", currentuser->username);//提示信息
	printf("\n  当前的文件路径:");//接入目录地址
	do {
		printf("<%s", p->listname);
		p = p->parent;
	} while (p != NULL);
	printf(" ----------------- 功能选择-------------\n\n");//菜单
	printf("1、新建文件 \n");
	printf("2、删除文件 \n");
	printf("3、打开文件 \n");
	printf("4、读出文件 \n");
	printf("5、写入文件 \n");
	printf("6、关闭文件 \n");
	printf("7、显示文件列表 \n");
	printf("8、返回用户管理菜单\n");
	printf("9、退出系统 \n");
	printf(" ----------------------------------------\n\n");
	printf("按功能选择相应的操作 ");
	scanf("%d", &choice);
	printf("\n");
	switch (choice)//switch语句
	{
	case 1:
		creatfile(currentlist, 0);
		break;     //创建文件
	case 2:
		deletefile(currentlist, 0);
		break;              //删除文件
	case 3:
		openfile();
		break;        //打开文件
	case 4:
		readfile();
		displayfilemenu();
		break;          //读出文件
	case 5:
		writefile();
		displayfilemenu();
		break;      //写入文件
	case 6:
		closefile();
		break;      //关闭文件
	case 7:
		displaylist();///显示文件
		getch();
		displayfilemenu();
		break;
	case 8:
		displayusermenu();
		break;     //退出，返回上用户管理菜单
	case 9:
		quit();
		break;
	default:
		printf("\n\n你的输入有误!请重新输入!!!\n");
		getch();
		displayfilemenu();
		break;      //非法输入，返回文件管理菜单重新输入
	}
}

void displayuser()     //显示用户名
{
	int i = 0;
	USD* temp = user;
	printf("\n  用户列表如下：\n");
	while (temp != NULL)
	{
		i++;
		printf("  * NO.%d: %s *\n", i, temp->username);
		temp = temp->next;
	}
	if (user == NULL)
	{
		printf(" \n该系统暂无用户!");
	}
	printf("\n\n");
}

void creatfile(LIST* qq, int flag)        //创建文件
{
	LIST* temp;
	LIST* p = qq->child;
	LIST* q;
	temp = get(LIST);
loop:
	q = qq->child;
	if (flag == 0)
	{
		printf("\n创建一个新文件\n");
		printf("\n请输入新建文件名: ");     //输入文件名
	}

	scanf("%s", temp->listname);
	while (q != NULL)
	{
		if (strcmp(temp->listname, q->listname) == 0)
		{
			printf("\n有重名文件!请重新输入!");
			goto loop;
		}
		q = q->next;
	}
	temp->content = NULL;
	printf("\n文件属性: 0、只读Read\t  1、读和写Read&Write");     //设置保护模式
	printf("\n\n请选择文件属性： ");
	scanf("%d", &temp->protect);
	if (temp->protect != 0 && temp->protect != 1)
	{
		printf("\n\n你所选择的文件属性有误!请重新输入文件属性： ");
		scanf("%d", &temp->protect);
	}
	if (flag == 0)
	{
		printf("\n请输入该文件的长度: ");        //设置文件长度，供写入文件时会用到
		scanf("%d", &temp->length);
	}
	if (flag == 0)
		temp->type = 0; //0为文件
	else temp->type = 1;
	temp->flag = 0;     //文件默认为关闭状态，以后需要时再打开
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
	printf("创建文件成功！\n\n");

	getchar();
	displayfilemenu();
}
void deletefile(LIST* qq, int flag)      //删除文件(夹)
{
	char n[10];
	LIST* p = qq->child;
	LIST* pre = NULL;
	if (flag == 0)
	{
		printf("\n[删除一个文件]\n");
		printf("\n请输入要删除的文件名: ");
	}
	else
	{
		printf("\n[删除文件夹]\n");
		printf("\n请输入要删除的文件夹名: ");
	}
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0))
		{
			if (pre == NULL)  //第一个节点
			{
				qq->child = p->next; free(p);
				printf("\n\n文件%s已删除成功!!!\n", n);
			}
			else
			{
				pre->next = p->next;  //把前一个指针的NEXT指向N当前指针的NEXT，则删除该文件
				printf("\n\n文件%s已删除成功!!!\n", n);
				free(p);
			}
			break;
		}
		else if ((strcmp(p->listname, n) == 0) && (p->type == 1))
		{
			if (pre == NULL)  //第一个节点
			{
				qq->child = p->next; free(p);
				printf("\n\n文件夹%s已经成功删除!!!\n", n);
			}
			else
			{
				pre->next = p->next;  //把前一个指针的NEXT指向N当前指针的NEXT，则删除该文件
				printf("\n\n文件夹%s已经成功删除!!!\n", n);
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
	if (p == NULL && flag == 0)      //该文件不存在
		printf("\n\n找不到该文件!");
	else if (p == NULL && flag == 1) printf("\n\n找不到该文件夹!\n");
	getchar();
	getchar();
	displayfilemenu();
}

void openfile() ////打开文件
{
	char n[10];
	LIST* p = currentlist->child;
	printf("\n[打开一个文件]\n");
	printf("\n请输入要打开的文件名: ");//输入文件名
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 0))//比较文件以寻找要打开的文件
		{
			p->flag = 1;
			printf("\n文件%s成功打开!!!\n", n);
			break;
		}
		else if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 1))
		{
			printf("\n文件%s打开已经!!!\n", n);
			break;
		}
		p = p->next;
	}
	if (p == NULL)
	{
		printf("\n\n找不到该文件!\n");
	}
	getchar();
	getchar();
	displayfilemenu();
}

void readfile()     //读出文件
{
	char n[10];
	LIST* p = currentlist->child;
	printf("\n[读取一个文件]\n");
	printf("\n\n请输入要读的文件名: ");
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 1))//比较
		{
			printf("\n文件%s内容是:%s", p->listname, p->content);
			getchar(); getchar();
			return;
		}
		p = p->next;
	}
	printf("\n\n读文件失败,请确认该文件是否已经打开或文件是否存在!\n");
	getchar();
	getchar();
}

void writefile()      //写入文件
{
	char n[10], *temp;
	LIST* p = currentlist->child;
	printf("\n[写入文件]\n");
	printf("\n请输入要写的文件名: ");
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0))
		{
			if (p->flag == 0)
			{
				printf("\n文件未打开，无法写入!请将文件置打开状态!!!\n"); getchar(); getchar(); system("cls");
			}
			else if (p->protect == 0)
			{
				printf("\n\n操作受限!该文件不能写!!!\n");    //该文件限制读写
				getchar();
				return;
			}
			else
			{
				temp = (char*)malloc(sizeof(char) * p->length);
				printf("\n\n请输入文件内容(length<=%d):\n\n\t", p->length);
				scanf("%s", temp);
				p->content = temp;
				getchar();
			}
			return;
		}
		p = p->next;
	}
	printf("\n\n该文件不存在!获取失败!!!\n");//提示
	getchar();
	getchar();
}

void closefile()     //关闭文件
{
	char n[10];
	LIST* p = currentlist->child;
	printf("\n[关闭一个文件]\n");
	printf("\n请输入要关闭的文件名: ");
	scanf("%s", n);
	while (p != NULL)
	{
		if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 1))//寻找需要文件
		{
			p->flag = 0;
			printf("\n文件%s关闭成功.\n", n);
			break;
		}
		else if ((strcmp(p->listname, n) == 0) && (p->type == 0) && (p->flag == 0))
		{
			printf("\n文件%s已经关闭.\n", n);
			break;
		}
		p = p->next;
	}
	if (p == NULL)
	{
		printf("\n\n找不到该文件!\n");
	}
	getchar();
	getchar();
	displayfilemenu();/////返回文件管理菜单
}

void displaylist()////显示文件
{
	LIST* p = currentlist->child;
	if (p == NULL)
	{
		printf("\n此用户没有任何文件\n\n");
		return;
	}
	else
	{
		printf("\n当前用户下的文件为：\n");
		printf("\n文件名\t\t文件类型\n");
	}
	while (p != NULL)
	{
		if (p->type == 0)
			printf("\n%s文件\t\t%d\n", p->listname, p->protect);
		p = p->next;
	}
	printf("\n -----------------------------------------------------------\n\n");

}

void userhelp()//帮助
{
	printf("\n  ----------[用户管理界面帮助与支持]-------------\n\n");

	printf("1、新建用户：每次可以新建一个用户\n\n");
	printf("2、选择用户：选择一个用户进行文件操作\n\n");
	printf("3、帮助文档：提供本界面帮助信息\n\n");
	printf("4、退出系统：退出模拟文件管理系统\n\n");
	printf("  --------------------------------------------------\n\n");
}
void quit()///直接退出
{
	char c;
	printf("\n确认直接退出？(Y/N):");
	scanf("%s", &c);
	printf("\n");
	if (c == 'Y' || c == 'y')
	{
		printf("\n\n谢谢使用!再见!!!\n\n");
		getch();
		exit(0);
	}
	else
		displayfilemenu();
}

