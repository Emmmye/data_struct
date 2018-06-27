

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef char LinkListType;
typedef struct LinkListQueue{
    LinkListType data;
    struct LinkListQueue* next;
}LinkListQueue;

LinkListQueue* CreateNode(LinkListType value)
{
    LinkListQueue* newNode = (LinkListQueue*)malloc(sizeof(LinkListQueue));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void LinkListInit(LinkListQueue** head)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    *head = NULL;
}

void DestroyNode(LinkListQueue* node)
{
    free(node);
}

void LinkListQueuePush(LinkListQueue** head,LinkListType value)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    if(*head==NULL)
    {
        //空队列
        *head = CreateNode(value);
        return;
    }
    LinkListQueue* cur = *head;
    while(cur->next!=NULL)
    {
        cur=cur->next;
    }
    cur->next = CreateNode(value);
}

void LinkListQueuePop(LinkListQueue** head)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    if(*head==NULL)
    {
        //空队列
        return;
    }
    LinkListQueue* cur = *head;
    *head = (*head)->next;
    DestroyNode(cur);
}
int LinkListQueueGetTop(LinkListQueue* head,LinkListType* value)
{
    if(head==NULL)
    {
        //空队列
        return 0;
    }
    *value = head->data;
    return 1;
}
void LinkListQueuePrintChar(LinkListQueue* head,const char* msg)
{
    if(head==NULL)
    {
        //空队列
        return;
    }
    LinkListQueue* cur = head;
    while(cur!=NULL)
    {
        printf("[%c|%p] ",cur->data,cur);
        cur=cur->next;
    }
    printf("\n");
    printf("%s\n",msg);
}
int main()
{
    LinkListQueue* head = NULL;
    LinkListQueuePush(&head,'a');
    LinkListQueuePush(&head,'b');
    LinkListQueuePush(&head,'c');
    LinkListQueuePush(&head,'d');
    LinkListQueuePrintChar(head,"尝试四个元素入队列");
    LinkListType value;
    int ret = LinkListQueueGetTop(head,&value);
    printf("ret: except: 1 ,real: %d \n",ret);
    printf("value: except: a ,real: %c \n",value);
    LinkListQueuePop(&head);
    LinkListQueuePop(&head);
    printf("\n");
    LinkListQueuePrintChar(head,"尝试两个元素出队列");
    LinkListQueuePop(&head);
    LinkListQueuePop(&head);
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
