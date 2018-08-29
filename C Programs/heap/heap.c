#include <stdio.h>
#include <stdlib.h>

typedef int elemType;
/************************************************************************/
/*                    以下是关于堆顺序存储操作的5种算法                 */
/************************************************************************/
/* 定义堆的顺序存储类型 */
struct heap{
    elemType *heap;        /* 定义指向动态数组空间的指针 */
    int len;            /* 定义保存堆长度的变量 */
    int maxSize;        /* 用于保存初始化时所给的动态数组空间的大小 */
};


/* 1.初始化堆 */
void initHeap(struct heap *hbt, int ms)
{
    /* 检查ms的值是否有效 */
    if (ms <= 0){
        printf("数组长度参数非法！");
        exit(1);
    }
    
    /* 动态分配存储的数组空间 */
    hbt->heap = malloc(ms * sizeof(elemType));
    
    if (hbt->heap == NULL){
        printf("空间分配失败！");
        exit(1);
    }

    /* 设置maxSize域和len域的值 */
    hbt->maxSize = ms;
    hbt->len = 0;

    return;
}

/* 2.清除堆 */
void clearHeap(struct heap *hbt)
{
    if (hbt->heap != NULL){
        free(hbt->heap);
		printf("free ...\n");
        hbt->heap = NULL;
        hbt->len = 0;
        hbt->maxSize = 0;
    }

    return;
}

/* 3.检查一个堆是否为空 */
int emptyHeap(struct heap *hbt)
{
    if (0 == hbt->len){
        return 1;
    }else{
        return 0;
    }
}

/* 4.向堆中插入一个元素 */
void insertHeap(struct heap *hbt, elemType x)
{
    int i;
    /* 堆满时数组空间扩展为原来的2倍，
       原内容被自动拷贝到p所指向的存储空间中*/
    if (hbt->len == hbt->maxSize){
        elemType *p;
        p = realloc(hbt->heap,( 2 + hbt->maxSize )* sizeof(elemType));
		printf("realloc ...\n");
        if (p == NULL){
            printf("存储空间分配失败！");
            exit(1);
        }

        hbt->heap = p;        /* 堆数组空间指向新空间 */
        hbt->maxSize = 2 + hbt->maxSize;        /* 修改数组空间的大小 */
    }

    /* 向堆尾添加新元素 */
    hbt->heap[hbt->len] = x;
    hbt->len++;

    /* 用i指向待调整元素的位置，初始指向新元素所在的堆尾位置 */
    i = hbt->len - 1;

    /* 寻找新元素的最终位置，每次使双亲元素下移一层 */
    while (0 != i){
        int j = (i - 1) / 2;        /* j指向下标为i的元素的双亲 */
        /* 比较调整结束退出循环 */
        if (x >= hbt->heap[j]){        
            break;
        }
        hbt->heap[i] = hbt->heap[j];        /* 双亲元素下移 */
        i = j;
    }
    hbt->heap[i] = x;        /* 把新元素调整到最终位置 */

    return;
}

/* 5.从堆中删除元素 */
elemType deleteHeap(struct heap *hbt)
{
    elemType temp, x;
    int i, j;
    
    /* 若为空堆，则显示出错信息并退出运行 */
    if (0 == hbt->len){
        printf("堆已空，退出运行！");
        exit(1);
    }
    
    /* 将堆顶元素暂存在temp中以便返回 */
    temp = hbt->heap[0];
    hbt->len--;

    /* 若删除操作后变为空堆则返回 */
    if (0 == hbt->len){
        return temp;
    }

    /* 将待调整的堆尾元素暂存在x中，以便放入最终位置 */
    x = hbt->heap[hbt->len];
    /* 用i指向待调整元素的位置，初始指向堆顶位置 */
    i = 0;
    /* 用j指向i的左孩子位置，初始指向下标1的位置 */
    j = 2 * i + 1;
    /* 寻找待调整元素的最终位置，每次使孩子元素上移一层 */
    while (j <= hbt->len - 1){        /* 调整到孩子为空时止 */
        /* 若右孩子存在并且较小，应使j指向右孩子 */
        if ((j < hbt->len - 1) && (hbt->heap[j] > hbt->heap[j+1])){
            j++;
        }
        /* 若条件成立则调整结束，退出循环 */
        if (x <= hbt->heap[j]){
            break;
        }
        /* 孩子元素上移到双亲位置 */
        hbt->heap[i] = hbt->heap[j];
        /* 使i和j分别指向下一层结点 */
        i = j;
        j = 2 * i + 1;
    }
    /* 把待调整元素放到最终位置 */
    hbt->heap[i] = x;
    
    return temp;
}

/************************************************************************/

int main(void)
{
    int i, x;
    int a[10];// = {23, 56, 40, 62, 38, 55, 10, 16};
    struct heap b;

    initHeap(&b, 3);
    /* 向堆b中依次插入数组a中的每一个元素 */
    for (i = 0; i < 10; i++){
		scanf("%d",&a[i]);
		if (a[i]!=-1)
		{
			insertHeap(&b, a[i]);
		}
        else
			break;
    }

    while (!emptyHeap(&b)){
        x = deleteHeap(&b);
        printf("%d", x);
        if (!emptyHeap(&b)){
            printf(",");
        }
    }

    printf("");
    clearHeap(&b);

    return 0;
}