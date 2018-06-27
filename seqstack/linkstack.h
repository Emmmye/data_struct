#pragma once


#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef char LinkListType;

typedef struct LinkListStack{
    struct LinkListStack* next;//指针域，指向下一个节点的指针
    LinkListType data;//数据域，用来存放数据
}LinkListStack;

//初始化栈
void LinkListStackInit(LinkListStack** head);

//入栈
void LinkListStackPush(LinkListStack** head,LinkListType value);

//出栈
void LinkListStackPop(LinkListStack** head);

//销毁栈
void DestroyNode(LinkListStack* node);

//创建新节点
LinkListStack* CreateNode(LinkListType value);

//取栈顶元素
int LinkListStackGetTop(LinkListStack* head,LinkListType* value);

