#include<stdio.h>
#include<stdlib.h>
typedef char ShareStackType;


#define SizeMax 100

//实现两个栈共享一个数组
//一个栈的栈顶在数组头部(左栈)
//另一个栈的栈顶在数组的尾部(右栈)
//当两个栈的栈底接触时，说明数组已经满了，也就是两个栈满了
typedef struct ShareStack{
    ShareStackType data[SizeMax];
    size_t size_left;//控制左栈的大小
    size_t size_right;//控制右栈的大小
}ShareStack;


void ShareStackInit(ShareStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    stack->size_left = 0;
    stack->size_right = SizeMax-1;
}

void ShareStackLeftPush(ShareStack* stack,ShareStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size_left==stack->size_right-1)
    {
        //两个栈都满了
        return;
    }
    stack->data[stack->size_left++] = value;
}

void ShareStackRightPush(ShareStack* stack,ShareStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size_left==stack->size_right-1)
    {
        //两个栈都满了
        return;
    }
    stack->data[stack->size_right--] = value;
}

void ShareStackLeftPop(ShareStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size_left == 0)
    {
        //左栈是空的
        return;
    }
    stack->size_left--;
}

void ShareStackRightPop(ShareStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size_right == SizeMax-1)
    {
        //右栈是空的
        return;
    }
    stack->size_right++;
}


void ShareStackLeftPrintChar(ShareStack* stack,const char* msg)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    int i = 0;
    for(;i<stack->size_left;i++)
    {
        printf("[%c] ",stack->data[i]);
    }
    printf("\n");
    printf("[%s] \n",msg);
}
void ShareStackRightPrintChar(ShareStack* stack,const char* msg)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    int i = SizeMax-1;
    for(;i>stack->size_right;i--)
    {
        printf("[%c] ",stack->data[i]);
    }
    printf("\n");
    printf("[%s] \n",msg);
}


void Test()
{
    ShareStack stack;
    ShareStackInit(&stack);
    ShareStackLeftPush(&stack,'a');
    ShareStackLeftPush(&stack,'b');
    ShareStackLeftPush(&stack,'c');
    ShareStackLeftPush(&stack,'d');
    ShareStackLeftPrintChar(&stack,"尝试入左栈四个元素");
    ShareStackLeftPop(&stack);
    ShareStackLeftPop(&stack);
    ShareStackLeftPrintChar(&stack,"尝试出左栈两个元素");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    ShareStackRightPush(&stack,'A');
    ShareStackRightPush(&stack,'B');
    ShareStackRightPush(&stack,'C');
    ShareStackRightPush(&stack,'D');
    ShareStackRightPrintChar(&stack,"尝试入右栈四个元素");
    ShareStackRightPop(&stack);
    ShareStackRightPop(&stack);
    ShareStackRightPrintChar(&stack,"尝试出右栈两个元素");
}

int main()
{
    Test();
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
