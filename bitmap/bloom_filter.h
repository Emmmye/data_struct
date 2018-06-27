#pragma once

#include "bitmap.h"
#define HashFuncMax 2
typedef size_t (*HashFunc)(const char* str);

typedef struct BloomFilter{
    Bitmap bm;
    HashFunc func[HashFuncMax];
}BloomFilter;

//初始化布隆过滤器
void BloomFilterInit(BloomFilter* bf,size_t Capacity,HashFunc func[]);
//销毁布隆过滤器
void BloomFilterDestroy(BloomFilter* bf);
//往布隆过滤器中插入数据
void BloomFilterInsert(BloomFilter* bf,const char* str);
//在布隆过滤器中查找数据
int BloomFilterFind(BloomFilter* bf,const char* str);
