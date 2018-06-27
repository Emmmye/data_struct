#include "bloom_filter.h"
#include <stdio.h>

size_t BKDRHash(const char *str)  
{  
    size_t hash = 0;  
    size_t ch = 0;
    while ( ch = (size_t)*str++)  
    {         
        hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..  
        // 有人说将乘法分解为位运算及加减法可以提高效率，如将上式表达为：hash = hash << 7 + hash << 1 + hash + ch;  
        // 但其实在Intel平台上，CPU内部对二者的处理效率都是差不多的，  
        // 我分别进行了100亿次的上述两种运算，发现二者时间差距基本为0（如果是Debug版，分解成位运算后的耗时还要高1/3）；  
        // 在ARM这类RISC系统上没有测试过，由于ARM内部使用Booth's Algorithm来模拟32位整数乘法运算，它的效率与乘数有关：  
        // 当乘数8-31位都为1或0时，需要1个时钟周期  
        // 当乘数16-31位都为1或0时，需要2个时钟周期  
        // 当乘数24-31位都为1或0时，需要3个时钟周期  
        // 否则，需要4个时钟周期  
        // 因此，虽然我没有实际测试，但是我依然认为二者效率上差别不大          
    }  
    return hash;  
}  
size_t SDBMHash(const char *str)  
{  
    size_t hash = 0;
    size_t ch;
    while ( ch = (size_t)*str++)  
    {  
        hash = 65599 * hash + ch;         
        //hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
    }  
    return hash;  
}  
//初始化布隆过滤器
void BloomFilterInit(BloomFilter* bf,size_t Capacity,HashFunc func[])
{
    if(bf == NULL)
    {
        return;
    }
    BitmapInit(&bf->bm,Capacity);
    bf->func[0] = func[0];
    bf->func[1] = func[1];
}
//销毁布隆过滤器
void BloomFilterDestroy(BloomFilter* bf)
{
    if(bf == NULL)
    {
        return;
    }
    BitmapDestroy(&bf->bm);
}
//往布隆过滤器中插入数据
void BloomFilterInsert(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        return;
    }
    size_t i = 0;
    for(; i < HashFuncMax; ++i)
    {
        size_t hash = bf->func[i](str)%(bf->bm.Capacity);
        BitmapSet(&bf->bm,hash);
    }
}
//在布隆过滤器中查找数据
int BloomFilterFind(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        return 0;
    }
    size_t i = 0;
    for(; i < HashFuncMax; ++i)
    {
        size_t hash = bf->func[i](str)%(bf->bm.Capacity);
        int ret = BitmapTest(&bf->bm,hash);
        if(ret == 0)
        {
            return 0;
        }
    }
    return 1;
}


////////////////////////////////////////////////////
/////////////TEST    PART///////////////////////////
////////////////////////////////////////////////////

void TestInit()
{
    TESTHEAD;
    BloomFilter bf;
    HashFunc func[2] = {BKDRHash,SDBMHash};
    BloomFilterInit(&bf,100,func);
    printf("excepted %p ,actual %p \n",func[0],bf.func[0]);
    printf("excepted %p ,actual %p \n",func[1],bf.func[1]);
}

void Test_Insert_Find()
{
    TESTHEAD;
    BloomFilter bf;
    HashFunc func[2] = {BKDRHash,SDBMHash};
    BloomFilterInit(&bf,100,func);
    BloomFilterInsert(&bf,"haha");
    int ret = BloomFilterFind(&bf,"haha");
    printf("excepted 1 ,actual %d \n",ret);
    ret = BloomFilterFind(&bf,"hehe");
    printf("excepted 0 ,actual %d \n",ret);
}

int main()
{
    TestInit();
    Test_Insert_Find();
    return 0;
}
