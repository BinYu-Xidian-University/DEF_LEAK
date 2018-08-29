#include "stdio.h"
typedef struct node{
	int number;
	int psw;
	struct node *next;
}LNode,*LinkList;
void insertList(LinkList *list,LinkList q,int e1,int e2)
{
	LinkList p;
	p=(LinkList)malloc(sizeof(LNode));
	printf("malloc....\n");
	p->number=e1;
	p->psw=e2;
	if (!*list)
	{
		*list=p;
		p->next=NULL;
	}
	else
	{
		p->next=q->next;
		q->next=p;
	}
}
void CreateJoseph(LinkList *jsp,int n)
{
	LinkList q=NULL,list=NULL;
	int i,e;
	printf("please input the passsword for people in the Joseph circle\n");
	for (i=0;i<n;i++)
	{
		scanf("%d",&e);
		insertList(&list,q,i+1,e);
		if(i==0)
			q=list;
		else
			q=q->next;
	}
	q->next=list;
	*jsp=list;
}
void exJoseph(LinkList *jsp,int m)
{
	LinkList p,q;
	int i;
	q=p=*jsp;
	while (q->next!=p)
	{
		q=q->next;
	}
	printf("the order of a column is\n");
	while (p->next!=p)
	{
		for (i=0;i<m-1;i++)
		{
			q=p;
			p=p->next;
		}
		q->next=p->next;
		printf("%d ",p->number);
		m=p->psw;
	//	free(p);
	//	printf("free....\n");
		p=q->next;
	}
	printf("\nthe last person in the circle is %d\n",p->number);
}
int main()
{
	LinkList jsp;
	int n,m;
	printf("please input number of the people in the Joseph circle\n");
	scanf("%d",&n);
	CreateJoseph(&jsp,n);
	printf("please input the first maximum number\n");
	scanf("%d",&m);
	exJoseph(&jsp,m);
	return 0;
}