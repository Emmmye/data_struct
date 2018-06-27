#include "seqqueue.h"
#include <stdio.h>
typedef struct QueueStack{
    SeqQueue queue1;
    SeqQueue queue2;
}QueueStack;


void QueueStackInit(QueueStack* head)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    SeqQueueInit(&head->queue1);
    SeqQueueInit(&head->queue2);
}


void QueueStackPush(QueueStack* head,SeqQueueType value)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    if(head->queue1.size==0)
    {
        SeqQueuePush(&head->queue2,value);
    }
    else
    {
        SeqQueuePush(&head->queue1,value);
    }
}

void QueueStackPop(QueueStack* head)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    if(head->queue1.size == 0 && head->queue2.size == 0)
    {
        //两个队列都为空
        return;
    }
    //要把 from 中的元素倒腾到 to 中
    SeqQueue* from = NULL;
    SeqQueue* to = NULL;
    if(head->queue1.size>0){
        from = &head->queue1;
        to = &head->queue2;
    }else{
        from = &head->queue2;
        to = &head->queue1;
    }
    while(1)
    {
        if(from->size==1)
        {
            //停止倒腾，此时 from 的队首元素就是栈顶元素
            break;
        }
        SeqQueueType value;
        SeqQueueGetTop(from,&value);
        SeqQueuePop(from);
        SeqQueuePush(to,value);
    }
    //把最后一个元素删除掉
    SeqQueuePop(from);
}


int QueueStackGetTop(QueueStack* head,SeqQueueType* value)
{
    if(head == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(head->queue1.size==0&&head->queue2.size==0)
    {
        return 0;
    }
    SeqQueue* from = NULL;
    SeqQueue* to = NULL;
    if(head->queue1.size>0){
        from = &head->queue1;
        to = &head->queue2;
    }else{
        from = &head->queue2;
        to = &head->queue1;
    }
    while(1)
    {
        int ret = SeqQueueGetTop(from,value);
        if(ret == 0)
        {
            break;
        }
        SeqQueuePop(from);
        SeqQueuePush(to,*value);
    }
    return 1;
}


void Test()
{
    QueueStack head;
    QueueStackInit(&head);
    QueueStackPush(&head,'a');
    QueueStackPush(&head,'b');
    QueueStackPush(&head,'c');
    QueueStackPush(&head,'d');
    SeqQueueType value;
    int ret = QueueStackGetTop(&head,&value);
    printf("ret: except: 1 , real: %d \n",ret);
    printf("value: except: d , real: %c \n",value);
    QueueStackPop(&head);
     ret = QueueStackGetTop(&head,&value);
    printf("ret: except: 1 , real: %d \n",ret);
    printf("value: except: c , real: %c \n",value);
}

int main()
{
    Test();
    return 0;
}
