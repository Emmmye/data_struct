#include"seqstack.h"


#define ROW 6
#define COL 6



int i = 2;
typedef struct Maze{
    int maze[ROW][COL];
}Maze;


void MazeInit(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    int data[ROW][COL] = {
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,1,1,0},
        {0,0,1,0,1,0},
        {1,1,1,0,0,0},
        {0,0,1,0,0,0}
    };
    int i = 0;
    for(; i<ROW; i++){
        int j = 0;
        for(; j<COL; j++)
        {
            maze->maze[i][j] = data[i][j];
        }
    }
}

void MazePrint(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    int i = 0;
    for(; i<ROW; i++)
    {
        int j = 0;
        for(; j<COL; j++){
            printf("%2d ",maze->maze[i][j]);
        }
        printf("\n");
    }
}


//////////////////////////////
//////////////////////////////
int Canstay(Maze* maze , SeqStackType cur)
{
    if(maze == NULL)
    {
        //非法输入
        return 0;
    }
    if(cur.row<0 || cur.row>=ROW || cur.col<0 || cur.col>=COL)
    {
        return 0;
    }
    if(maze->maze[cur.row][cur.col] == 1)
    {
        return 1;
    }
    return 0;
}

int IsExit(Maze* maze,SeqStackType cur , SeqStackType entry)
{
    if(maze == NULL)
    {
        return 0;
    }
    if(cur.row == entry.row && cur.col == entry.col)
    {
        return 0;
    }
    if(cur.row == 0 || cur.row == ROW-1 || cur.col == 0 || cur.col == COL-1)
    {
        return 1;
    }
    return 0;
}

void mask(Maze* maze,SeqStackType cur)
{
    maze->maze[cur.row][cur.col] = i++;
}
void GetPathByLoop(Maze* maze,SeqStackType entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    //创建一个栈，并将其初始化，这个栈相当于递归实现中的调用栈，保存着走过的路径
    SeqStack stack;
    SeqStackInit(&stack);
    //判断入口合不合法,如果不合法，就退出
    if(!Canstay(maze,entry))
    {
        printf("参数非法\n");
        return;
    }
    //  如果合法，标记入口点，并将其入栈
    mask(maze,entry);
    SeqStackPush(&stack,entry);
    //进入循环，取当前栈顶元素
    while(stack.size)
    {
        //判断栈顶元素是不是出口，如果是，就直接函数返回
        SeqStackType cur;
        int ret = SeqStackFindTop(&stack,&cur);
        if(IsExit(maze,cur,entry))
        {
            SeqStackPop(&stack);
            SeqStackFindTop(&stack,&cur);
            i--;
        }
        //  如果不是，就按照顺时针方向判断四个点
        //如果可以落脚，就标记当前点，并将其入栈，立刻进入下一次循环
        //上
        SeqStackType up;
        up.row = cur.row-1;
        up.col = cur.col;
        if(Canstay(maze,up)){
            mask(maze,up);
            SeqStackPush(&stack,up);
            continue;
        }
        //右
        SeqStackType right;
        right.row = cur.row;
        right.col = cur.col+1;
        if(Canstay(maze,right)){
            mask(maze,right);
            SeqStackPush(&stack,right);
            continue;
        }
        //下
        SeqStackType down;
        down.row = cur.row+1;
        down.col = cur.col;
        if(Canstay(maze,down)){
            mask(maze,down);
            SeqStackPush(&stack,down);
            continue;
        }
        //左
        SeqStackType left;
        left.row = cur.row;
        left.col = cur.col-1;
        if(Canstay(maze,left)){
            mask(maze,left);
            SeqStackPush(&stack,left);
            continue;
        }
        //如果四个相邻的点都不能落脚，就将当前的点出栈
        SeqStackPop(&stack);
        i--;
    }
}

//////////////////////////////////////////////////
//  Round 3 如果迷宫有多条路径，找到其中的最短路径
//////////////////////////////////////////////////



void MazeInitShortPath(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    int data[ROW][COL] = {
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,1,1,0},
        {0,0,1,0,1,1},
        {1,1,1,0,0,0},
        {0,0,1,0,0,0}
    };
    int i = 0;
    for(; i<ROW; i++){
        int j = 0;
        for(; j<COL; j++)
        {
            maze->maze[i][j] = data[i][j];
        }
    }
}

void _GetShortPath(Maze* maze, SeqStackType cur, SeqStackType entry,SeqStack* cur_path,SeqStack* short_path)
{
    //1.判断当前点能不能落脚
    if(!Canstay(maze, cur))
    {
        return;
    }
    //2.如果能落脚，标记当前点，并将当前点插入cur_path栈中
    mask(maze,cur);
    SeqStackPush(cur_path,cur);
    //3.判定当前点是不是出口
    if(IsExit(maze,cur,entry))
    {
    //   a)如果当前点是出口，说明找到了一条路径，就拿当前路径和 short_path 中的路径进行对比
    //     如果当前路径比 short_path 短，或者 short_path 本身就是空栈，就用当前路径代替 short_path
        if(cur_path->size < short_path->size || short_path->size == 0)
        {
            printf("找到了一条短路径！\n");
            //将 cur_path 中的值赋值到 short_path 中
            SeqStackAssgin(cur_path,short_path);
        }
    //   b)如果当前路径没有比 short_path 短就要尝试去找其他路径(进行回溯)，在回溯之前，也要把
    //     cur_path 栈顶元素也出栈
            SeqStackPop(cur_path);
            i--;
            return;
    }
    //4.当前点不是出口，尝试探测四个方向
    SeqStackType up = cur;
    up.row = cur.row - 1;
    _GetShortPath(maze,up,entry,cur_path,short_path);

    SeqStackType right = cur;
    right.col = cur.col + 1;
    _GetShortPath(maze,right,entry,cur_path,short_path);

    SeqStackType down = cur;
    down.row = cur.row + 1;
    _GetShortPath(maze,down,entry,cur_path,short_path);

    SeqStackType left = cur;
    left.col = cur.col - 1;
    _GetShortPath(maze,left,entry,cur_path,short_path);
    //5.如果四个方向都递归的探测过了，就可以进行出栈，然后回溯，同时 cur_path 也要出栈，回溯到上一个点 
    //
    SeqStackPop(cur_path);
    i--;
    return;
}


//尝试找到所有的路径，然后从所有的路径中筛选出最短的一条
//实现递归版本 
void GetShortPath(Maze* maze,SeqStackType entry)
{
    //和从一个数组中找到最小的数字是一个思路
    SeqStack cur_path;//当前路径
    SeqStack short_path;//最短路径
    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);
    _GetShortPath(maze,entry,entry,&cur_path,&short_path);
    //打印栈中的内容
    SeqStackDebugPrint(&short_path,"最短路径是:");
}



void Test()
{
    Maze maze;
    MazeInit(&maze);
    MazePrint(&maze);
    SeqStackType entry;
    entry.row = 0;
    entry.col = 2;
    GetPathByLoop(&maze,entry);
    printf("\n");
    MazePrint(&maze);
}

void Test2()
{
    Maze maze;
    MazeInit(&maze);
    MazePrint(&maze);
    SeqStackType entry;
    entry.row = 0;
    entry.col = 2;
    GetShortPath(&maze,entry);
    printf("\n");
    MazePrint(&maze);
}

int main()
{
    Test2();
    return 0;
}
