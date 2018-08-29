#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int data_type;

typedef struct avl
{
	data_type data;
	int bf;//AVL树平衡因子（Banlance Factor）
	struct avl *lchild,*rchild;
}AVLNode,*AVL;

void AdjustLL(AVL *T)//左左调整
{
	AVL temp = (*T)->lchild;
	(*T)->lchild = temp->rchild;
	temp->rchild = (*T);
	*T = temp;
}

void AdjustRR(AVL *T)//右右调整   
{
	AVL temp = (*T)->rchild;
	(*T)->rchild = temp->lchild;
	temp->lchild = (*T);
	(*T) = temp;
}

void AdjustRL(AVL *T)//右左调整  
{
	AVL p1,p2;
	p1 = (*T)->rchild;
	p2 = p1->lchild;
	(*T)->rchild = p2->lchild;
	p1->lchild = p2->rchild;
	p2->lchild = (*T);
	p2->rchild = p1;
	(*T) = p2;
}

void AdjustLR(AVL *T)//左右调整
{
	AVL p1,p2;
	p1 = (*T)->lchild;
	p2 = p1->rchild;
	p1->rchild = p2->lchild;//p2左孩子连上p1的右孩子
	(*T)->lchild = p2->rchild;//p2右孩子连上(*T)的左孩子
	p2->lchild = p1;
	p2->rchild = (*T);
	(*T) = p2;
}

void LeftBanlance(AVL *T)// 左平衡处理：LL LR 情况
{
	AVL lc = (*T)->lchild,rc;
	switch(lc->bf)
	{
		case 1:	//LL情况
			(*T)->bf = 0;
			lc->bf = 0;
			AdjustLL(T);
			break;
		case 0:				//删除时需要，插入不需要
			(*T)->bf = 1;
			lc->bf = -1;
			AdjustLL(T);
			break;
		case -1: //LR情况
			rc = lc->rchild;
			switch(rc->bf)
			{
				case 1:
					(*T)->bf = -1;
					lc->bf = 0;
					break;
				case 0:
					(*T)->bf = 0;
					lc->bf = 0;
					break;
				case -1:
					(*T)->bf = 0;
					lc->bf = 1;
					break;
			}
			rc->bf = 0;
			AdjustLR(T);
			break;
	}
}

void RightBanlance(AVL *T)//右平衡处理：RR RL情况
{
	AVL rc = (*T)->rchild,lc;
	switch(rc->bf)
	{
		case -1:
			(*T)->bf  = 0;
			rc->bf = 0;
			AdjustRR(T);
			break;
		case 0:			//删除时需要，插入不需要
			(*T)->bf = -1;
			rc->bf = 1;
			AdjustRR(T);
			break;
		case 1:
			lc = rc->lchild;
			switch(lc->bf)
			{
				case 1:
					(*T)->bf = 0;
					rc->bf = -1;
					break;
				case 0:
					(*T)->bf = 0;
					rc->bf = 0;
					break;
				case -1:
					(*T)->bf = 1;
					rc->bf = 0;
					break;
			}
			lc->bf = 0;
			AdjustRL(T);
			break;
	}
}

int Insert(AVL *T,data_type data,int *taller)//插入
{
	AVL newnode,p;
	newnode = (AVL)malloc(sizeof(AVLNode));
	newnode->lchild = NULL;
	newnode->rchild = NULL;
	newnode->data = data;
	newnode->bf = 0;
	if((*T) == NULL)	//插入成功，子树变高
	{
		(*T) = newnode;
		*taller = 1;
	}
	else
	{
		if(data == (*T)->data)//数据已存在，不插入
		{
			*taller = 0;
			return 0;
		}
		else if(data < (*T)->data)//左子树中查找
		{
			if(Insert(&(*T)->lchild,data,taller) == 0)//插入失败
			{
				return 0;
			}
			if((*taller) == 1)		//插入成功且子树变高，对bf做相应修改以及平衡调整
			{
				switch((*T)->bf)
				{
					case 1:
						LeftBanlance(T);	//处理左平衡，插入操作平衡处理完，子树高度不变
						*taller = 0;
						break;
					case 0:
						(*T)->bf = 1;
						*taller = 1;
						break;
					case -1:
						(*T)->bf = 0;
						*taller = 0;
						break;
				}
			}
		}
		else//右子树中查找
		{
			if(Insert(&(*T)->rchild,data,taller) == 0)//插入失败
			{
				return 0;
			}
			if((*taller) == 1)
			{
				switch((*T)->bf)
				{
					case 1:
						(*T)->bf = 0;
						*taller = 0;
						break;
					case 0:
						(*T)->bf = -1;
						*taller = 1;
						break;
					case -1:
						RightBanlance(T);
						*taller = 0;
						break;
				}
			}
		}
	}
	return 1;
}

/*
若等于，则删除,并且高度降低，在递归回溯时对父元素bf做相应修改
若小于，向左边递归，若大于，向右边递归
只有当删除成功，且树高度降低时，做bf相应修改，否则结束函数。*/

int Delete(AVL *T,data_type data,int *shorter)//删除
{
	if((*T) == NULL)
	{
		return 0;
	}
	else if(data == (*T)->data)		//删除  此处删除算法原理同二叉搜索树
	{
		AVL temp = (*T);
		if((*T)->lchild == NULL)
		{
			(*T) = (*T)->rchild;
			free(temp);
			*shorter = 1;
		}
		else if((*T)->rchild == NULL)
		{
			(*T) = (*T)->lchild;
			free(temp);
			*shorter = 1;
		}
		else
		{
			AVL p = (*T)->lchild;
			while(p->rchild)
			{
				p = p->rchild;
			}
			temp->data = p->data;
			Delete(&(temp->lchild),p->data,shorter);
		}
	}
	else if(data < (*T)->data)		//左子树中继续查找
	{
		if(!Delete(&((*T)->lchild),data,shorter))//删除失败直接return 0
		{
			return 0;
		}
		if(*shorter)	//左子树中结点删除成功,并且子树高度降低
		{
			switch((*T)->bf)
			{
				case 1:
					(*T)->bf = 0;
					*shorter = 1;
					break;
				case 0:				//子树高度不降低的特殊情况:即左右都有结点，删除一个不影响子树高度
					(*T)->bf = -1;
					*shorter = 0;
					break;
				case -1:
					if((*T)->rchild->bf == 0)//删除时的特殊情况：右孩子结点bf为0，子树高度不变
					{
						*shorter = 0;
					}
					else
					{
						*shorter = 1;
					}
					RightBanlance(T);		//处理右平衡
					break;
			}
		}
	}
	else				//右子树中继续查找
	{
		if(!Delete(&(*T)->rchild,data,shorter))
		{
			return 0;
		}
		if(*shorter)	
		{
			switch((*T)->bf)
			{
				case 1:
					if((*T)->lchild->bf == 0)
					{
						*shorter = 0;
					}
					else
					{
						*shorter = 1;
					}
					LeftBanlance(T);
					break;
				case 0:
					(*T)->bf = 1;
					*shorter = 0;
					break;
				case -1:
					(*T)->bf = 0;
					*shorter = 1;
					break;
			}
		}
	}
	return 1;
}

int GetDeepth(AVL T)//求结点深度
{
	int max,hl,hr;
	if(T == NULL)
	{
		return 0;
	}
	else
	{
		hl = GetDeepth(T->lchild);
		hr = GetDeepth(T->rchild);
		return max = (hl>hr?hl:hr)+1;
	}
}

void DispTree(AVL T,int deepth,char ch) //按凹入表显示二叉树
{
	int i;
    if(T)
    {
        for(i = 0;i < deepth + 1;i++)
        {
            printf("---");
        }
        printf("+%d(%c)(%d)\n",T->data,ch,T->bf);
        DispTree(T->lchild,--deepth,'L');
        DispTree(T->rchild,deepth,'R');
    }
}

void Inorder(AVL T)//中序遍历
{
	if(T)
	{
		Inorder(T->lchild);
		printf("%d ",T->data);
		Inorder(T->rchild);
	}
}

void CreateAVL(AVL *T)//创建二叉树，调用插入算法创建
{
	int deepth,taller;
	data_type data;
	char ch;
	printf("请输入要创建的二叉搜索树的数据(数据之间用空格隔开,输入完毕按回车)：");
	do
	{
		taller = 0;
		scanf("%d",&data);
		ch = getchar();
		Insert(T,data,&taller);
		deepth = GetDeepth(*T);
		DispTree(*T,deepth,'R');
		puts("");
	}
	while (ch != 10);
}

int main()
{
	int deepth,taller,select,shorter;
	data_type data;
	AVL T;
	T = NULL;

	//CreateAVL(&T);
	//deepth = GetDeepth(T);
	//Inorder(T);

	//插入第一个数据
	taller = 0;
	printf("请输入要插入的数据：");
	scanf("%d",&data);
	Insert(&T,data,&taller);
	deepth = GetDeepth(T);
	DispTree(T,deepth,'R');
	puts("");
	Inorder(T);

	//插入第二个数据
	taller = 0;
	printf("请输入要插入的数据：");
	scanf("%d",&data);
	Insert(&T,data,&taller);
	deepth = GetDeepth(T);
	DispTree(T,deepth,'R');
	puts("");
	Inorder(T);

	//插入第三个数据
	taller = 0;
	printf("请输入要插入的数据：");
	scanf("%d",&data);
	Insert(&T,data,&taller);
	deepth = GetDeepth(T);
	DispTree(T,deepth,'R');
	puts("");
	Inorder(T);

	return 0;
}

/*13 87 39 90 45 52 46 78 28 71 76 29 56 19 83 92 48 81 95 99 20*/