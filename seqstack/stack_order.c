

#include"seqstack.h"
// 返回1 表示能够变换成功
// 返回2 表示不能变换成功


int StackOrder(char input[], size_t input_size, char output[], size_t output_size)
{
    SeqStack stack;
    SeqStackInit(&stack);
    // 循环的把 input 的元素入栈
    size_t i = 0;
    size_t output_index = 0;
    // 取栈顶元素，和output_index指向的元素比较
    for(i=0;i<input_size;i++)
    {
    //    如果不相等，就继续将 input 元素入栈
        SeqStackPush(&stack,input[i]);
        SeqStackType value;
        int ret = SeqStackFindTop(&stack,&value);
        if(ret == 0)
        {
            break;
        }
    //    如果相等
    //      1> output_index向后移
    //      2> 把栈顶元素出栈
    //      3> 循环的比较栈顶元素和 output_index 指向的值
        while(value == output[output_index])
        {
            if(output_index>=output_size)
            {
                //output 序列已经遍历完，进行最终审判
                break;
            }
            output_index++;
            SeqStackPop(&stack);
            ret = SeqStackFindTop(&stack,&value);
            if(ret == 0)
            {
                break;
            }
        }
    }
    // 如果最后栈为空并且 output_index 指向 output 数组的最后一个元素的下一个元素，就认为能够变换得到
    // 否则就是无法变换得到
    if(stack.size==0&&output_index==output_size)
    {
        return 1;
    }
    return 0;
    
}

int main()
{
    char input[]= {'a','b','c','d','e'};
    char output[]={'c','b','a','d','e'};
    int ret = StackOrder(input,sizeof(input),output,sizeof(output));
    printf("ret expected: 1 , actural: %d \n",ret);
    return 0;
}
