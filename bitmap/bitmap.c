#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
//初始化位图
void BitmapInit(Bitmap* bm,size_t Capaticy)
{
    if(bm == NULL)
    {
        return;
    }
    bm->Capacity = Capaticy;
    size_t size = Capaticy/sizeof(BitmapType)*8 + 1;
    bm->data = (BitmapType*)malloc(sizeof(BitmapType)*size);
    memset(bm->data,0,sizeof(BitmapType)*size);
}
//销毁位图
void BitmapDestroy(Bitmap* bm)
{
    if(bm == NULL)
    {
        return;
    }
    free(bm->data);
}
void GetOffset(size_t index,int* n , int* offset)
{
    if(n == NULL || offset == NULL)
    {
        return;
    }
    *n = index/sizeof(BitmapType)*8;//算出是数组中的第几个元素
    *offset = index%sizeof(BitmapType)*8;
}

//将某一位设置为1
void BitmapSet(Bitmap* bm, size_t index)
{
    if(bm == NULL || index >= bm->Capacity )
    {
        return;
    }
    int n = 0;
    int offset = 0;
    GetOffset(index,&n,&offset);
    bm->data[n] = bm->data[n] | (0x1<<offset);
}
//测试某一位是否为1
int BitmapTest(Bitmap* bm, size_t index)
{
    if(bm == NULL || index >= bm->Capacity )
    {
        return 0;
    }
    int n = 0;
    int offset = 0;
    GetOffset(index,&n,&offset);
    int ret = bm->data[n] & (0x1<<offset);
    return ret > 0? 1 : 0;
}
//将某一位设置为0
void BitmapSetEmpty(Bitmap* bm, size_t index)
{
    if(bm == NULL || index >= bm->Capacity)
    {
        return;
    }
    int n = 0;
    int offset = 0;
    GetOffset(index,&n,&offset);
    bm->data[n] = bm->data[n] & ~(0x1<<offset);
}
//将位图设置为全1
void BitmapFull(Bitmap* bm)
{
    if(bm == NULL)
    {
        return;
    }
    size_t size = bm->Capacity/sizeof(BitmapType)*8 + 1;
    size_t i = 0;
    for(; i < size ; ++i)
    {
        bm->data[i] = bm->data[i] | (0xFFFFFFFF);
    }
}
//将位图设置为全0
void BitmapEmpty(Bitmap* bm)
{
    if(bm == NULL)
    {
        return;
    }
    size_t size = bm->Capacity/sizeof(BitmapType)*8 + 1;
    memset(bm->data,0,sizeof(BitmapType)*size);
}


///////////////////////////////////////////
////////TEST PART//////////////////////////
//////////////////////////////////////////


void TestSet()
{
    TESTHEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    int ret = BitmapTest(&bm,50);
    printf("excepted 1 , actual %d \n",ret);
    ret = BitmapTest(&bm,10);
    printf("excepted 0 , actual %d \n",ret);
}
void TestSetEmpty()
{
    TESTHEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    int ret = BitmapTest(&bm,50);
    printf("excepted 1 , actual %d \n",ret);
    BitmapSetEmpty(&bm,50);
    ret = BitmapTest(&bm,50);
    printf("excepted 0 , actual %d \n",ret);
}
void TestFull()
{
    TESTHEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapFull(&bm);
    int ret = BitmapTest(&bm,50);
    printf("excepted 1 , actual %d \n",ret);
    ret = BitmapTest(&bm,10);
    printf("excepted 1 , actual %d \n",ret);
    ret = BitmapTest(&bm,90);
    printf("excepted 1 , actual %d \n",ret);
    BitmapSetEmpty(&bm,50);
    ret = BitmapTest(&bm,50);
    printf("excepted 0 , actual %d \n",ret);
}
void TestEmpty()
{
    TESTHEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapFull(&bm);
    int ret = BitmapTest(&bm,50);
    printf("excepted 1 , actual %d \n",ret);
    ret = BitmapTest(&bm,10);
    printf("excepted 1 , actual %d \n",ret);
    ret = BitmapTest(&bm,90);
    printf("excepted 1 , actual %d \n",ret);
    BitmapEmpty(&bm);
    ret = BitmapTest(&bm,50);
    printf("excepted 0 , actual %d \n",ret);
    ret = BitmapTest(&bm,10);
    printf("excepted 0 , actual %d \n",ret);
    ret = BitmapTest(&bm,90);
    printf("excepted 0 , actual %d \n",ret);
}
//int main()
//{
//    TestSet();
//    TestSetEmpty();
//    TestFull();
//    TestEmpty();
//    return 0;
//}
