/*      0------4
        |\     |
        | \    |
		1  \   |
		|   \  |
		|    \ |
		2     \3
*/
#include "stdio.h"
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *next;
}ArcNode;
typedef struct VNode{
	int data;
	ArcNode *firstarc;
}VNode;
int visited[5]={0,0,0,0,0};
int flag[5]={0},tmp=0;
CreateGraph(int n,VNode G[]){
	int i,e;
	int j;
	ArcNode *p,*q;
	printf("input the information of the vertex\n");
	for(i=0;i<n;i++){
		G[i].data=i;
	//	scanf("%d",&G[i]);
		G[i].firstarc=NULL;
	}
	for(i=0;i<n;i++)
	{
	//	printf("create the edges for the %dth vertex\n",i);
		j=0;
	//	scanf("%d",&e);
		while (j<3)
		{
			scanf("%d",&e);
			if(e==-1)
				break;
			p=(ArcNode*)malloc(sizeof(ArcNode));
	//		printf("malloc here...\n");
			p->next=NULL;
			p->adjvex=e;
			if(G[i].firstarc==NULL)
				G[i].firstarc=p;
			else
				q->next=p;
			q=p;
			if(e<0||e>4)
			{
				flag[i]=1;
				tmp=1;
			}
			j++;
		//	scanf("%d",&e);
		}
	}
}
int FirstAdj(VNode G[],int v)
{
	if(G[v].firstarc!=NULL) 
		return (G[v].firstarc)->adjvex;
	return -1;
}
int NextAdj(VNode G[],int v)
{
	ArcNode *p;
	p=G[v].firstarc;
	while(p!=NULL)
	{
		if(visited[p->adjvex])
			p=p->next;
		else
			return p->adjvex;
	}
	return -1;
}
void DFS(VNode G[],int v)
{
	int w;
//	printf("result is:\n");
	printf("%d ",G[v]);
	visited[v]=1;
	w=FirstAdj(G,v);
	while(w!=-1)
	{
		if(visited[w]==0)
			DFS(G,w);
		w=NextAdj(G,v);
	}
}
void main()
{
	int i;
	VNode G[5];
	ArcNode *p,*q;
	CreateGraph(5,G);
	if(tmp==0)
     	DFS(G,0);
	for (i=0;i<5;i++)
	{
	    p=G[i].firstarc;
		if(p!=NULL&&flag[i]==0)
		{
			while(p!=NULL) //删除每一条边信息
			{
				q=p;
				p=p->next;
				free(q);
				printf("free here...\n");
				q=NULL;
			}
		}
		else
		{
			printf("%d vertex has no edge or error input.\n",i);//没有分配
		}
	}
}