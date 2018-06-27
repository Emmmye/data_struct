#include"linkstack.h"


void LinkListStackInit(LinkListStack** head)
{
    if(head==NULL){
        //非法输入
        return;
    }
    *head=NULL;
}

//因为链表中的节点都是一块独立的内存空间，所以在进行创建栈或者插入操作时，就需要开辟新的内存空间
//并分配给每个节点，因为堆上开辟的空间是不连续的，所以节点与节点之间需要一个next指针来连接起来
LinkListStack* CreateNode(LinkListType value)
{
    LinkListStack* newNode = (LinkListStack*)malloc(sizeof(LinkListStack));
    newNode->next = NULL;
    newNode->data = value;
    return newNode;
}

//封装free函数，实现单个节点的销毁，如果想一次性销毁整个栈，需要遍历链表，依次释放每个节点空间才可以
void DestroyNode(LinkListStack* node)
{
    free(node);
}
/*尾插时间复杂度为O(n),不推荐
void LinkListStackPush(LinkListStack** head,LinkListType value)
{
    if(head==NULL){
        //非法输入
        return;
    }
    if(*head==NULL){
        //空链表
        *head = CreateNode(value);
    }else{
    LinkListStack* cur = *head;
    while(cur->next!=NULL){
        cur=cur->next;
    }
    cur->next = CreateNode(value);
    }
}
*/
//头插时间复杂度为O(1),推荐
void LinkListStackPush(LinkListStack** head,LinkListType value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(*head==NULL)
    {
        //空栈
        *head = CreateNode(value);
        return;
    }
    LinkListStack* cur = CreateNode(value);
    cur->next = *head;
    *head = cur;
}

/*尾删的时间复杂度为O(n),不推荐
void LinkListStackPop(LinkListStack** head)
{
    if(head==NULL){
        //非法输入
        return;
    }
    if(*head==NULL){
        //空链表
        return;
    }
    if((*head)->next==NULL){
        DestroyNode(*head);
        *head==NULL;
        return;
    }
    LinkListStack* cur = *head;
    LinkListStack* end = *head;
    while(cur->next!=NULL)
    {
        end = cur;
        cur=cur->next;
    }
    DestroyNode(cur);
    end->next=NULL;
}*/
//头删时间复杂度为O(1),推荐
void LinkListStackPop(LinkListStack** head)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    if(*head==NULL)
    {
        //空栈
        return;
    }
    LinkListStack* cur = *head;
    *head=(*head)->next;
    DestroyNode(cur);
}
/*
//尾插法的栈顶元素为尾部元素,时间复杂度为O(n),不推荐
LinkListStack* LinkListStackGetTopPushBack(LinkListStack* head)
{
    if(head==NULL){
        //空链表
        return NULL; 
    }
    LinkListStack* cur = head;
    while(cur->next!=NULL){
        cur=cur->next;
    }
    return cur;
}*/
//头插法的栈顶元素为头指针指向的元素,时间复杂度为O(1),推荐
int LinkListStackGetTop(LinkListStack* head,LinkListType* value)
{
    if(head==NULL){
        //空链表
        return 0; 
    }
    *value = head->data;
    return 1;
}
void LinkListStackPrintChar(LinkListStack* head,const char* msg)
{
    if(head==NULL){
        //空链表
        return;
    }
    LinkListStack* cur = head;
    while(cur!=NULL){
        printf("[%c|%p]  ",cur->data,cur);
        cur=cur->next;
    }
    printf("\n");
    printf("%s\n",msg);
}


void MinLinkListStackPush(LinkListStack** head,LinkListType value)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    if(*head==NULL)
    {
        //空栈
        LinkListStackPush(head,value);//第一个插入的元素即为当前栈最小的元素，所以插入两次
        LinkListStackPush(head,value);
        return;
    }
    LinkListType Min = (*head)->data;
    LinkListStackPush(head,value);
    if (Min < value)
    {
        LinkListStackPush(head,Min);
    }
    else
    {
        LinkListStackPush(head,value);
    }
 //   printf("%c  \n", (*head)->data);
 //   printf("%c  \n", (*head)->next->data);
}

void MinLinkListStackPop(LinkListStack** head)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    if(*head==NULL)
    {
        //空栈
        return;
    }
    LinkListStackPop(head);
    if(*head==NULL)
        return;
    LinkListStackPop(head);
}


int MinReturnLinkListStack(LinkListStack* head,LinkListType* value)
{
    if(head==NULL){
        //空链表
        return 0; 
    }
    *value = head->data;
    return 1;
}


int main()
{
    LinkListStack* head;
    LinkListStackInit(&head);
    MinLinkListStackPush(&head,'a');
    MinLinkListStackPush(&head,'c');
    MinLinkListStackPush(&head,'b');
    LinkListType value;
    int ret = LinkListStackGetTop(head,&value);
    printf("ret: except: 1 , real: %d \n",ret);
    printf("value: except: a ,real: %c \n",value);
    MinLinkListStackPop(&head);
     ret = LinkListStackGetTop(head,&value);
    printf("ret: except: 1 , real: %d \n",ret);
    printf("value: except: a ,real: %c \n",value);
    MinLinkListStackPop(&head);
}
