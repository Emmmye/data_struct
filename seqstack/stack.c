#include"seqstack.h"

//用两个栈实现一个队列
typedef struct StackQueue{
    //input用于入队列的场景
     SeqStack input;
    //output用于出队列和返回队首元素的场景
     SeqStack output;
}StackQueue;


void StackQueueInit(StackQueue* head)
{
    if(head==NULL)
    {
        return;
    }
    SeqStackInit(&head->input);
    SeqStackInit(&head->output);
}
void StackQueuePush(StackQueue* head,SeqStackType value)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    while(1)//将output里的所有元素都倒腾到input中
    {
        SeqStackType Output;
        int ret = SeqStackFindTop(&head->output,&Output);
        if(ret==0)
        {
            break;
        }
        SeqStackPush(&head->input,Output);
        SeqStackPop(&head->output);
    }
    SeqStackPush(&head->input,value);
}

void StackQueuePop(StackQueue* head)
{
    if(head==NULL)
    {
        //非法输入
        return;
    }
    while(1)//将input里的所有元素都倒腾到output中
    {
        SeqStackType Input;
        int ret = SeqStackFindTop(&head->input,&Input);
        if(ret==0)
        {
            break;
        }
        SeqStackPush(&head->output,Input);
        SeqStackPop(&head->input);
    }
    SeqStackPop(&head->output);//此时2号栈的栈顶元素就相当于新队列的队首元素
}

int StackQueueGetTop(StackQueue* head,SeqStackType* value)
{
    if(head==NULL||value==NULL)
    {
        //非法输入
        return 0;
    }
    while(1)
    {
        SeqStackType top;
        int ret = SeqStackFindTop(&head->input,&top);
        if(ret==0)
        {
            break;
        }
        SeqStackPush(&head->output,top);
        SeqStackPop(&head->input);
    }
    return SeqStackFindTop(&head->output,value);
}

void DestroyQueue(StackQueue* head)
{
    SeqStackDestroy(&head->input);
    SeqStackDestroy(&head->output);
}
void Test()
{
    StackQueue head;
    StackQueueInit(&head);
    StackQueuePush(&head,'a');
    StackQueuePush(&head,'b');
    SeqStackType value;
    int ret = StackQueueGetTop(&head,&value);
    printf("ret: except: 1 , real: %d \n",ret);
    printf("value: except: a , real: %c \n",value);
    StackQueuePop(&head);
    ret = StackQueueGetTop(&head,&value);
    printf("ret: except: 1 , real: %d \n",ret);
    printf("value: except: b , real: %c \n",value);
}

int main()
{
    Test();
    return 0;
}
