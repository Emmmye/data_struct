#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define FOR_MAZE
//#define TESTHEAD printf("======================[%s]======================\n",__FUNCTION__);
//#ifdef FOR_MAZE;
struct TreeNode;

typedef struct Point{
    int row;
    int col;
}Point;
typedef int SeqStackType;

typedef struct SeqStack{
     SeqStackType* data;//长度到了最大值时就malloc一段新的内存，所以用指针指向的内存来存储顺序表中的数据
    size_t size;//有效长度
    size_t capacity;//原有的内存可容纳的最大长度
}SeqStack;

//初始化栈
void SeqStackInit(SeqStack* seq);
//销毁栈
void SeqStackDestroy(SeqStack* seq);
//扩容函数
//1.malloc一块更大的内存空间
//2.将原内存空间里的数据拷贝到新的内存空间中
//3.释放掉原内存空间，将指针指向新的内存
SeqStackType* SeqStackExpand(SeqStack* seq);
//往栈中插入数据
void SeqStackPush(SeqStack* seq,SeqStackType value);
//删除数据
void SeqStackPop(SeqStack* seq);
//取出栈顶元素
//1.通过一个输出型参数 value 实现，将栈顶元素的值赋给value，因为是地址传递，所以外部实参的值也被修改了
//2.成功返回1，失败返回0
int SeqStackFindTop(SeqStack* Seq,SeqStackType* value);

//将 cur_path 中的值赋值到 short_path 中
void SeqStackAssgin(SeqStack* cur_path,SeqStack* short_path);


//通常栈是不允许进行遍历的
//但是如果是进行调试或者测试，这个是例外
//因此在这里的函数虽然进行了遍历，但是仅用于调试
void SeqStackDebugPrint(SeqStack* stack,const char* msg);

