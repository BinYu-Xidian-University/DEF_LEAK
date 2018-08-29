#include <stdio.h>
#include <stdlib.h>
typedef int elemType;
/************************************************************************/
/*                以下是关于线性表顺序存储操作的16种算法      */
/************************************************************************/
struct List{
    elemType *list;
    int size;
    int maxSize;
};
void againMalloc(struct List *L)
{   
    /* 空间扩展为原来的2倍，并由p指针所指向，原内容被自动拷贝到p所指向的存储空间 */
    elemType *p = realloc(L->list, (2+ L->maxSize) * sizeof(elemType));
	printf("malloc two ..\n");
    if(!p){    /* 分配失败则退出运行 */
        printf("存储空间分配失败！ ");
        exit(1);
    }
    L->list = p;    /* 使list指向新线性表空间 */
    L->maxSize = 2 + L->maxSize;    /* 把线性表空间大小修改为新的长度 */
}
/* 1.初始化线性表L，即进行动态存储空间分配并置L为一个空表 */
void initList(struct List *L, int ms)
{
    /* 检查ms是否有效，若无效的则退出运行 */
    if(ms <= 0){
        printf("MaxSize非法！ ");
        exit(1);    /* 执行此函数中止程序运行，此函数在stdlib.h中有定义 */
    }
    L->maxSize = ms;    /* 设置线性表空间大小为ms */
    L->size = 0;
    L->list = malloc(ms * sizeof(elemType));
	printf("malloc  ..\n");
    if(!L->list){
        printf("空间分配失败！ ");
        exit(1);
    }
    return;
}
/* 2.清除线性表L中的所有元素，释放存储空间，使之成为一个空表 */
void clearList(struct List *L)
{
    if(L->list != NULL){
        free(L->list);
		printf("free  ..\n");
        L->list = 0;
        L->size = L->maxSize = 0;
    }
    return;
}
/* 3.返回线性表L当前的长度，若L为空则返回０ */
int sizeList(struct List *L)
{
    return L->size;
}
/* 4.判定线性表L是否为空，若为空则返回1, 否则返回0 */
int emptyList(struct List *L)
{
    if(L->size ==0){
        return 1;
    }
    else{
        return 0;
    }
}
/* 5.返回线性表L中第pos个元素的值，若pos超出范围，则停止程序运行 */
elemType getElem(struct List *L, int pos)
{
    if(pos < 1 ||pos > L->size){    /* 若pos越界则退出运行 */
        printf("元素序号越界！ ");
        exit(1);
    }
    return L->list[pos - 1];    /* 返回线性表中序号为pos值的元素值 */
}
/* 6.顺序扫描（即遍历）输出线性表L中的每个元素 */
void traverseList(struct List *L)
{
    int i;
    for(i = 0; i < L->size; i++){
        printf("%d ", L ->list[i]);
    }
    printf("\n");
    return;
}
/* 7.从线性表L中查找值与x相等的元素，若查找成功则返回其位置，否则返回-1 */
int findList(struct List *L, elemType x)
{
    int i;
    for(i = 0; i < L->size; i++){
        if(L->list[i] == x){
            return i;
        }
    }
    return -1;
}
/* 8.把线性表L中第pos个元素的值修改为x的值，若修改成功返回1，否则返回0 */
int updatePosList(struct List *L, int pos, elemType x)
{
    if(pos < 1 ||  pos > L->size){    /* 若pos越界则修改失败 */
        return 0;
    }
    L->list[pos - 1] = x;
    return 1;
}
/* 9.向线性表L的表头插入元素x */
void inserFirstList(struct List *L, elemType x)
{
    int i;
    if(L->size == L->maxSize){
        againMalloc(L);
    }
    for(i = L->size - 1; i >= 0; i--){
        L->list[i + 1] = L ->list[i];
    }
    L->list[0] = x;
    L->size ++;
    return;
}
/* 10.向线性表L的表尾插入元素x */
void insertLastList(struct List *L, elemType x)
{
    if(L->size == L ->maxSize){    /* 重新分配更大的存储空间 */
        againMalloc(L);
    }
    L->list[L->size] = x;    /* 把x插入到表尾 */
    L->size++;    /* 线性表的长度增加１ */
    return;
}
/* 11.向线性表L中第pos个元素位置插入元素x，若插入成功返回１，否则返回０ */
int insertPosList(struct List *L, int pos, elemType x)
{
    int i;
    if(pos < 1 || pos > L->size + 1){    /* 若pos越界则插入失败 */
        return 0;
    }
    if(L->size == L->maxSize){    /* 重新分配更大的存储空间 */
        againMalloc(L);
    }
	
    for(i = L->size - 1; i >= pos - 1; i--){
        L->list[i + 1] = L->list[i];
    }
    L->list[pos - 1] = x;
    L->size++;
    return 1;
}
/* 12.向有序线性表L中插入元素x,　使得插入后仍然有序*/
void insertOrderList(struct List *L, elemType x)
{
    int i, j;
    /* 若数组空间用完则重新分配更大的存储空间 */
    if(L->size == L->maxSize){
        againMalloc(L);
    }
    /* 顺序查找出x的插入位置 */
    for(i = 0; i < L->size; i++){
        if(x < L->list[i]){
            break;
        }
    }
    /* 从表尾到下标i元素依次后移一个位置， 把i的位置空出来 */
    for(j = L->size - 1; j >= i; j--)
        L->list[j+1] = L->list[j];
    /* 把x值赋给下标为i的元素 */   
    L->list[i] = x;
    /* 线性表长度增加1 */
    L->size++;
    return;
}
/* 13.从线性表L中删除表头元素并返回它，若删除失败则停止程序运行 */
elemType deleteFirstList(struct List *L)
{
    elemType temp;
    int i;
    if(L ->size == 0){
        printf("线性表为空，不能进行删除操作！ ");
        exit(1);
    }
    temp = L->list[0];
    for(i = 1; i < L->size; i++)
        L->list[i-1] = L->list[i];
    L->size--;
    return temp;
}
/* 14.从线性表L中删除表尾元素并返回它，若删除失败则停止程序运行 */
elemType deleteLastList(struct List *L)
{
    if(L ->size == 0){
        printf("线性表为空，不能进行删除操作！ ");
        exit(1);
    }
    L->size--;
    return L ->list[L->size];        /* 返回原来表尾元素的值 */
}
/* 15.从线性表L中删除第pos个元素并返回它，若删除失败则停止程序运行 */
elemType deletePosList(struct List *L, int pos)
{
    elemType temp;
    int i;
    if(pos < 1 || pos > L->size){        /* pos越界则删除失败 */
        printf("pos值越界，不能进行删除操作！ ");
        exit(1);
    }
    temp = L->list[pos-1];
    for(i = pos; i < L->size; i++)
        L->list[i-1] = L->list[i];
    L->size--;
    return temp;
}
/* 16.从线性表L中删除值为x的第一个元素，若成功返回1，失败返回0 */
int deleteValueList(struct List *L, elemType x)
{
    int i, j;
    /* 从线性表中顺序查找出值为x的第一个元素 */
    for(i = 0; i < L->size; i++){
        if(L->list[i] == x){   
            break;
        }
    }
    /* 若查找失败，表明不存在值为x的元素，返回0 */
    if(i == L->size){
        return 0;
    }
    /* 删除值为x的元素L->list[i] */
    for(j = i + 1; j < L->size; j++){
        L->list[j-1] = L->list[j];
    }
    L->size--;
    return 1;
}
void main()
{
    int a[5];
    int i,flag;
    struct List L;
    initList(&L, 3);
    for(i = 0; i < 5; i++){
		scanf("%d",&a[i]);
        insertLastList(&L, a[i]);
    }
	scanf("%d",&flag);  //flag can be 1,2,3,4 
	if(flag==1)
    {
		insertPosList(&L, 5, 48); 	
	}
	if(flag==2)
    {
		insertPosList(&L, 5, 48); 	
		insertPosList(&L, 3, 64);
	}
	if(flag==3)
    {
		insertPosList(&L, 5, 48); 	
		insertPosList(&L, 3, 64);
		insertPosList(&L, 1, 34);
	}
	if(flag==4)
    {
		insertPosList(&L, 5, 48); 	
		insertPosList(&L, 3, 64);
		insertPosList(&L, 1, 34);
		insertPosList(&L, 6, 45);
	}
//	printf("size:%d\n",sizeList(&L));
    printf("%d \n", getElem(&L, 1));
    traverseList(&L);
    printf("%d \n", findList(&L, 10));
    updatePosList(&L, 3, 20);
    printf("%d \n", getElem(&L, 3));
    traverseList(&L);	
    deleteFirstList(&L);           
  	deleteFirstList(&L);
	deleteLastList(&L);             
	deleteLastList(&L);
	deletePosList(&L, 2);         
   	deletePosList(&L, 1);  
    printf("%d \n", sizeList(&L));
    printf("%d \n", emptyList(&L));
    traverseList(&L);
    clearList(&L);
    return 0;
}