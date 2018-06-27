#pragma once

#include <stddef.h>
//键值对
typedef int KeyType;
typedef int ValueType;

typedef int (*HashFunc)(KeyType key);

//哈希表中元素的状态
typedef enum State{
    EMPTY,//当前点是空的
    VALUE,//当前点是有元素的
    DELETED//当前点已被删除，也可以当做空了
}State;

#define HashMaxSize 1000
#define TESTHEAD printf("\n===============[%s]==============\n",__FUNCTION__);

//将键值对存放于结构体中
typedef struct KeyValue{
    KeyType key;
    ValueType value;
    State state;
}KeyValue;
//哈希表
typedef struct HashTable{
    KeyValue data[HashMaxSize];
    size_t size;
    HashFunc func;
}HashTable;

//哈希表初始化
void HashInit(HashTable* ht ,HashFunc func);

//销毁哈希表
void HashDestroy(HashTable* ht);

//往哈希表插入元素
void HashInsert(HashTable* ht, KeyType key, ValueType value);

//查找指定元素
KeyValue* HashFind(HashTable* ht, KeyType key);

//删除指定元素
void HashRemove(HashTable* ht, KeyType key);

