#include<stdlib.h>
#include<stdio.h>
struct node{
	int data;
	struct node* next1;
};
void getNode(node *n)
{
	scanf("%d",&(n->data));
	n->next1=NULL;
}
node* creatList()
{
	node* creatList_head;
	creatList_head=(node *)malloc(sizeof(node));
	if(creatList_head!=NULL)
	{
		getNode(creatList_head);
	}
	else
	{
		printf("create the list fail!\n");
	}
	return creatList_head;
}
void deleteList(node*h)
{
	node *deleteList_head;
	int count=0;
	while(count==0 || h!=NULL)
	{
		count=count+1;
		deleteList_head=h;
		h=h->next1;
		free(deleteList_head);
	}
}
void printList(node*h)
{
	int count=0;
	while(count==0 || h!=NULL)
	{
		count=count+1;
		printf("%d",h->data);
		h=h->next1;
	}
}
int numOfNode(node*h)
{
	int numofNode_i=0;
	int count=0;
	while(count=0 || h!=NULL)
	{
		count=count+1;
		numofNode_i=numofNode_i+1;
		h=h->next1;
	}
	return numofNode_i;
}
int insertNode(node**h,node *newNode,int index)
{
	int insertNode_flag=1;
	int insertNode_num;
	insertNode_num=numOfNode(*h);
	if(index<1 || index>insertNode_num+1)
	{
		return 0;
	}
	else
	{
		if(index==1)
		{
			newNode->next1=*h;
			*h=newNode;
		}
		else
		{
			node* insertNode_2_4_head=*h;
			int insertNode_2_4_i;;
			insertNode_2_4_i=2;
			while(insertNode_2_4_i<index)
			{
				insertNode_2_4_head=insertNode_2_4_head->next1;
				insertNode_2_4_i=insertNode_2_4_i+1;
			}
			newNode->next1=insertNode_2_4_head->next1;
			insertNode_2_4_head->next1=newNode;
		}
	}
	return insertNode_flag;
}
int deleteNode(node**h,int index)
{
	int deleteNode_flag=1;
	int deleteNode_num;
	deleteNode_num=numOfNode(*h);
	if(index<1 || index>deleteNode_num)
	{
		deleteNode_flag=0;
	}
	else
	{
		if(index==1)
		{
			node *deleteNode_2_3_head=* h;
			*h=(* h)->next1;
            free(deleteNode_2_3_head);
		}
		else
		{
			node *deleteNode_2_4_head=* h;
			node *deleteNode_2_4_temp;
			int deleteNode_2_4_i;
            deleteNode_2_4_i=2;
			while(deleteNode_2_4_i<index)
			{
				deleteNode_2_4_head=deleteNode_2_4_head->next1;
				deleteNode_2_4_i=deleteNode_2_4_i+1;
				
			};
			deleteNode_2_4_temp=deleteNode_2_4_head->next1;
			deleteNode_2_4_head->next1=deleteNode_2_4_temp->next1;
			free(deleteNode_2_4_temp);
		}
	}
	return deleteNode_flag;
}
int main()
{
	node *main_head;
	node *newNode;
	int index;
	int temp ;
	
	printf("create a new list\n");
    main_head=creatList();
	if(main_head!=NULL)
	{
		printf("create a new list!\n");
	}
	else
	{
		return 0;
	}
	temp=numOfNode(main_head);
	printf ("The node number of the list:",temp,"\n");
	printf ("the attibute of the node in the list:\n");
	printList(main_head);
	printf ("\n\n");
	printf ("create a new node and insert it\n");
	newNode=(node *)malloc(sizeof(node));
	getNode(newNode);
	/*temp = numOfNode(main_head);
	printf ("the node number of the list:",temp,"\n");
	printf ("please input the situation of the node:");*/
	scanf("%d",&index);
	if(!(insertNode(&main_head,newNode,index))) 
	{
		printf ("insert fail!\n");
	}
	temp= numOfNode(main_head);
	printf ("The node number of the list:",temp,"\n");
	printf ("the attibute of the node in the list:\n");
	printList(main_head);
	printf ("\n\n");
	printf ("create a new node and insert it\n");
	newNode=(node *)malloc(sizeof(node));
	getNode(newNode);
	temp = numOfNode(main_head);
	printf ("the node number of the list:",temp,"\n");
	printf ("please input the insert situation of the node:");
	scanf("%d",&index);
	if(!(insertNode(&main_head,newNode,index))) 
	{
		printf ("insert fail!\n");
	}
	temp = numOfNode(main_head);
	printf ("The node number of the list:",temp,"\n");
	printf ("the attibute of the node in the list:\n");
	printList(main_head);
	printf ("\n\n");
	temp = numOfNode(main_head);
	printf ("the node number of the list:",temp,"\n");
	printf ("please input the delete situation of the node:");
	scanf("%d",&index);
	if(!(deleteNode(&main_head,index)))  
	{
		printf ("delete fail!\n");
	}
	
	temp = numOfNode(main_head);
	printf ("The node number of the list:",temp,"\n");
	printf ("the attibute of the node in the list:\n");
	printList(main_head);
	printf ("\n\n");
	deleteList(main_head);
	system("pause");
	return 1;
}