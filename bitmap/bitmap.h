#pragma once
#include <unistd.h>

#define TESTHEAD printf("==============[%s]=============\n",__FUNCTION__);

typedef int BitmapType;
typedef struct Bitmap{
    BitmapType* data;
    size_t Capacity;
}Bitmap;

//初始化位图
void BitmapInit(Bitmap* bm,size_t Capaticy);
//销毁位图
void BitmapDestroy(Bitmap* bm);
//将某一位设置为1
void BitmapSet(Bitmap* bm, size_t index);
//将某一位设置为0
void BitmapSetEmpty(Bitmap* bm, size_t index);
//测试某一位是否为1
int BitmapTest(Bitmap* bm, size_t index);
//将位图设置为全1
void BitmapFull(Bitmap* bm);
//将位图设置为全0
void BitmapEmpty(Bitmap* bm);

