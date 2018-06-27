

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef char LinkListType;
typedef struct LinkListQueue{
    LinkListType data;
    struct LinkListQueue* next;
}LinkListQueue;

//创建节点
LinkListQueue* CreateNode(LinkListType value);

//初始化
void LinkListInit(LinkListQueue* head);

//销毁节点
void DestroyNode(LinkListQueue* node);

//入队列
void LinkListQueuePush(LinkListQueue** head,LinkListType value);

//出对列
void LinkListQueuePop(LinkListQueue** head);

//取队首元素
int LinkListQueueGetTop(LinkListQueue* head,LinkListType* value);
void LinkListQueuePrintChar(LinkListQueue* head,const char* msg);
