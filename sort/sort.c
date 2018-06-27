#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "seqstack.h"

//交换函数
void Swap(int *a , int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


////////////////////////////////////
//冒泡排序
//时间负责度:O(N^2)
//空间负责度:O(1)
//稳定性:稳定
///////////////////////////////////

//从后往前进行排序
void BubbleSort(int array[], size_t num)
{
    if(array == NULL || num <= 1)
    {
        return;
    }
    //[0,bound) 有序数组
    //[bound,num) 待排序数组
    size_t bound = 0;
    size_t j = num - 1;
    for(; bound < num - 1; ++bound)
    {
        for(j = num - 1; j > bound ; --j)
        {
            if(array[j] < array[j-1])
            {
                Swap(&array[j],&array[j-1]);
            }
        }
    }
}

///////////////////////////////////////
//选择排序
//时间复杂度:O(N^2)
//空间复杂度:O(1)
//稳定性:不稳定
//////////////////////////////////////
//打擂台！！！
void SelectSort(int array[] , size_t num)
{
    if(array == NULL || num <= 1)
        return;
    //[0,bound)有序数组
    //[bound,num)待排序数组
    size_t bound = 0;
    for(; bound < num ; ++bound)
    {
        size_t j = bound + 1;
        size_t king_bound = bound;
        for(; j < num ; ++j)
        {
            if(array[j] < array[king_bound])
                king_bound = j;
        }
        Swap(&array[bound],&array[king_bound]);
    }
}

////////////////////////////////////////
//堆排序
//时间复杂度:O(N*logN)
//空间复杂度:O(1)
//稳定性:不稳定
////////////////////////////////////////


void AdjustDown(int array[], size_t num, size_t parents)
{
    if(parents < 0 || parents >= num - 1)
        return;
    size_t child = 2*parents + 1;
    while(child > 0 && child < num)
    {
        if(child + 1 < num && array[child] < array[child + 1])
            child = child + 1;
        if(array[parents] < array[child])
        {
            Swap(&array[child], &array[parents]);
            parents = child;
            child = 2*parents + 1;
        }
        else
            break;
    }
}

void CreateHeap(int array[], size_t num)
{
    size_t i = num - 1;
    int parents = (num - 1 - 1)/2;
    for(; i >= 0 && parents >= 0 ; --i)
    {
        AdjustDown(array,num,parents);
        parents = (i - 1)/2;
    }
}

void HeapPop(int array[], size_t num)
{
    int i = num - 1;
    for(; i > 0; --i)
    {
        Swap(&array[i],&array[0]);
        AdjustDown(array,i,0);
    }
}
void HeapSort(int array[] , size_t num)
{
    if(array == NULL || num <= 1)
        return;
    CreateHeap(array,num);
    HeapPop(array,num);
}

/////////////////////////////////////////
//插入排序
//时间复杂度:O(N^2)
//空间复杂度:O(1)
//稳定性:稳定
//元素越少，效率越高
/////////////////////////////////////////

void InsertSort(int array[], size_t num)
{
    if(array == NULL || num <= 1)
        return;
    //[0,bound)排好序了
    //[bound,num)待排序数组
    size_t i = 1;
    size_t bound = 0;
    for(; i < num ; ++i)
    {
        int j = bound;
        int tmp = array[i];//待插入元素
        int insert = i;//待插入位置
        for(; j >= 0  ; j--)
        {
            if(array[i] < array[j])
                insert = j;
        }
        int x = i;
        for(; x > insert;--x)
        {
            array[x] = array[x-1];
        }
        array[insert] = tmp;
        bound++;
    }
}

//////////////////////////////////////////
//希尔排序
//时间复杂度:O(N^2)
//空间复杂度:O(1)
//稳定性:稳定
/////////////////////////////////////////


void ShellSort(int array[], size_t num)
{
    if(array == NULL || num <= 1)
        return;
    int gap = num/2;//步长
    while(gap)
    {
        size_t i = gap;
        for(; i < num ; i++)
        {
            int tmp = array[i];//待插入元素
            int insert = i;//待插入位置
            int j = i;
            for(; j >= 0; j-=gap)
            {
                if(array[j] > tmp)
                    insert = j;
            }
            int x = i;
            for(; x > insert ; x -= gap)
            {
                array[x] = array[x-gap];
            }
            array[insert] = tmp;
        }
        gap /= 2;
    }
}

/////////////////////////////////////////////////
//归并排序
//时间复杂度:O(N*logN)
//空间复杂度:O(N)
//稳定性:稳定
/////////////////////////////////////////////////

//合并
void  Merge(int array[], int beg, int mid, int end, int* tmp)
{
    int i = beg;
    int left = beg;
    int right = mid;
    while(left < mid && right < end)
    {
        if(array[left] <= array[right])
        {
            tmp[i++] = array[left++];
        }
        else
        {
            tmp[i++] = array[right++];
        }
    }
    while(left < mid)
        tmp[i++] = array[left++];
    while(right < end)
        tmp[i++] = array[right++]; 
    for(i = beg; i < end ; i++)
    {
        array[i] = tmp[i];
    }
}

//递归版
//分解
void _MergeSort(int array[], int beg, int end, int* tmp)
{
    if(end - beg <= 1)
        return;
    int mid = (beg + end)/2;
    _MergeSort(array,beg,mid,tmp);
    _MergeSort(array,mid,end,tmp);
    Merge(array,beg,mid,end,tmp);
}
//非递归版
void _MergeSortByLoop(int array[], int beg, int end, int* tmp)
{
    if(end - beg <= 1)
        return;
    int gap = 1;
    while(gap < end - beg)
    {
        int left = beg, mid = beg + gap , right = beg + 2*gap;
        while(right < end)
        {
            Merge(array,left,mid,right,tmp);
            left = right;
            mid = left + gap;
            right = mid + gap;
        }
        if(mid < end)
            Merge(array,left,mid,end,tmp);
        gap *= 2;
    }
}

void MargeSort(int array[], size_t num)
{
    if(array == NULL || num <= 1)
        return;
    int beg = 0;
    int end = num;
    int* tmp = (int*)malloc(sizeof(int)*num);
    _MergeSortByLoop(array,beg,end,tmp);
    free(tmp);
}

//////////////////////////////////////////////
//快速排序
//时间复杂度:O(N*logN), 最坏是O(N^2)
//空间复杂度:O(N)
//稳定性:不稳定
//////////////////////////////////////////////
//1.交换法

void _QuickSort(int array[], int beg, int end)
{
    if(end - beg <= 1)
        return;
    int key_value = array[end - 1];
    int left = beg;
    int right = end - 1 - 1;
    while(left < right)
    {
        while(array[left] < key_value && left < right)
            left++;
        while(array[right] > key_value && left < right)
            right--;
        Swap(&array[left],&array[right]);
    }
    Swap(&array[left],&array[end-1]);
    _QuickSort(array,beg,left);
    _QuickSort(array,left+1,end);
}
//2.挖坑法
void _QuickSortEx(int array[], int beg, int end)
{
    if(end - beg <= 1)
        return;
    int key_value = array[end - 1];
    int left = beg;
    int right = end - 1;
    while(left < right)
    {   
        while(left < right && array[left] < key_value)
            left++;
        if(left < right)
            array[right--] = array[left];
        while(left < right && array[right] > key_value)
            right--;
        if(left < right)
            array[left++] = array[right];
    }
    array[left] = key_value;
    _QuickSortEx(array,beg,left);
    _QuickSortEx(array,left+1,end);
}
//递归版
void QuickSort(int array[], int num)
{
    if(array == NULL || num <= 1)
        return;
    _QuickSort(array,0,num);
}
//非递归版
void QuickSortByLoop(int array[],int num)
{
    if(array == NULL || num <= 1)
        return;
    SeqStack stack;
    SeqStackInit(&stack);
    int left = 0;
    int right = num;
    SeqStackPush(&stack,right);
    SeqStackPush(&stack,left);
    while(1)
    {
        int ret = SeqStackFindTop(&stack,&left);
        if(ret <= 0)
            break;
        SeqStackPop(&stack);
        ret = SeqStackFindTop(&stack,&right);
        SeqStackPop(&stack);
        int end = right;
        int beg = left;
        right = end - 1 - 1;
        //可能栈中还有其他元素，所以要循环
        if(end - beg <= 1)
            continue;
        int key_value = array[end-1];
        while(left < right)
        {
            while(array[left] <= key_value && left < right)
                left++;
            while(array[right] > key_value && left < right)
                right--;
            Swap(&array[left],&array[right]);
        }
        Swap(&array[left],&array[end-1]);
        SeqStackPush(&stack,left);
        SeqStackPush(&stack,beg);
        SeqStackPush(&stack,end);
        SeqStackPush(&stack,left+1);
  }
}
//======================================================//
//===================TEST   PART========================//
//======================================================//


void Test()
{
    int array[] = {9,5,7,0,2,1,4,3,2};
    size_t i = 0;
    size_t size = sizeof(array)/sizeof(array[0]);
    for(; i < size ; ++i)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
    MargeSort(array,size);
    for(i = 0; i < size ; ++i)
    {
        printf("%d ",array[i]);
    }
    printf("\n");

}


int main()
{
    Test();
    return 0;
}
