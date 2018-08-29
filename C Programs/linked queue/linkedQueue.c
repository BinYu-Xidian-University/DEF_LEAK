//LinkQueue.c  
  
//带头节点的链式队列  
#include <stdio.h>  
#include <stdlib.h>  
#define    OK 1  
#define ERROR 0  
#define OVERFLOW -2  
typedef char elemType;//元素类型  
  
typedef struct _QNode  
{  
elemType data;  
struct _QNode *next;  
}QNode;//节点类型  
  
typedef struct  
{  
QNode *front;//  
QNode *rear;  
}LinkQueue;//队列类型  
  
//初始化队列  
int InitQueue(LinkQueue *q)  
{  
q->front=q->rear=(QNode *)malloc(sizeof(QNode)); 
printf("malloc...\n");  
if(!q->front) exit(OVERFLOW);  
q->front->next=NULL;  
return OK;  
}  
//销毁队列  
int DestroyQueue(LinkQueue *q)  
{  
while(q->front)  
{  
q->rear=q->front->next;  
free(q->front);  
q->front=q->rear;  
}  
return OK;  
}  
//队尾插入元素e  
int EnQueue(LinkQueue *q,elemType e)  
{  
QNode *p=(QNode *)malloc(sizeof(QNode));  
printf("malloc...\n"); 
if(!p) exit(OVERFLOW);  
p->data=e;  
p->next=NULL;  
q->rear->next=p;  
q->rear=p;  
return OK;  
}  
//删除队头元素，并打印其值  
int DeQueue(LinkQueue *q)  
{  
QNode *p=q->front->next;//因为带头节点，所以队头是头节点的后一个元素  
if(q->front==q->rear) return ERROR;  
//printf("已删除队头元素%c\n",p->data);  
q->front->next=p->next;  
if(q->rear==p) q->rear=q->front;  
free(p);
printf("free...\n");   
return OK;  
}  
//遍历队列  
void TraverseQueue(LinkQueue *q)  
{  
QNode *p=q->front->next;  
if(q->front==q->rear)  
printf("队列为空\n");  
else  
{  
printf("队列中的元素为:\n");  
while(p!=q->rear)  
{  
printf(" %c",p->data);  
p=p->next;  
}  
printf(" %c",q->rear->data);  
printf("\n");  
}  
}  
  
void main()  
{  
	int n;
LinkQueue *q=(LinkQueue *)malloc(sizeof(LinkQueue)); 
printf("malloc...\n"); 
InitQueue(q);  
TraverseQueue(q);  
//printf("队尾插入元素.....\n");  
EnQueue(q,'a');  
EnQueue(q,'b');  
EnQueue(q,'c');  
EnQueue(q,'d'); 
EnQueue(q,'e'); 
EnQueue(q,'f'); 
EnQueue(q,'g'); 
EnQueue(q,'h'); 
EnQueue(q,'i'); 
EnQueue(q,'j'); 
 
TraverseQueue(q);  
//printf("删除队首元素...\n"); 
printf("please input n:(1-10)\n");
scanf("%d",&n);
if (n<=10)
{
	while (n>0)
	{
		DeQueue(q); 
		n--;
	}
}

TraverseQueue(q);  
} 