/******************************************************** 
 *                    串的简单模式匹配                  *
 ********************************************************/ 

#include <stdio.h>
#include <stdlib.h>

/* 定义单链表结构体 */
struct node
{
    char ch;
    struct node *next;
};

/* 初始化单链表 */
void init(struct node **h)
{
    *h = (struct node*)malloc(sizeof(struct node));
    (*h)->next = NULL;
    return;
}

/* 将x结点插入到链表后 */
void append(struct node *p, int x)
{
    struct node *s;

    s = (struct node*)malloc(sizeof(struct node));
    s->ch = x;
    s->next = NULL;
    /* 移动到表尾 */
    while (p->next != NULL)
    {
        p = p->next;
    }
    
    p->next = s;
    
    return;
}

void display(struct node *p)
{
    printf("You typed string is: ");
    while (p->next != NULL)
    {
        printf("%c", p->next->ch);
        p = p->next;
    }
    printf("\n");

    return;
}

int main(int argc, char *argv[])
{
    struct node *t, *s;    /* s为主串, t为模式串 */
    struct node *sNext, *p, *q;
    int i, x = 0;
    
    init(&s);
    printf("Please type main string: ");
    while (x != ' ')
    {
        x = getchar();
        if (x != ' ')
        {
            append(s, x);        /* 添加到表尾 */
        }
    }
    display(s);
    
    init(&t);
    printf("Please type substring: ");
    x = 0;
    while (x != ' ')
    {
        x = getchar();
        if (x != ' ')
        {
            append(t, x);        /* 添加到表尾 */
        }
    }
    display(t);
    
    /* 初始化 */
    sNext = s->next;
    p = sNext;
    q = t->next;
    i = 1;        
    /* 从开始字符进行比较 */
    while ((p->next != NULL) && (q->next != NULL))
    {
        /* 进行匹配检验 */
        if (p->ch == q->ch)
        {
            p = p->next;
            q = q->next;
        }
        else    
        {
            sNext = sNext->next;
            p = sNext;        /* 指向主串中的下一个 */
            q = t->next;    /* 指针后退重新开始匹配 */
            i++;        /* 记录位置 */
        }
    }
    /* 输出结果 */
    if ((q->next) == NULL && (t->next->ch == s->next->ch))
    {
        printf("match position: %d", i);
    }
    else
    {
        printf("Not match!");
    }
    printf("\n");
    
    return 0;
}