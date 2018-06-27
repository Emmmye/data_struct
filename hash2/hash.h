#pragma once
#include <stddef.h>
#define HashMaxSize 1000
#define TESTHEAD printf("\n===============[%s]==============\n",__FUNCTION__);

typedef int KeyType;
typedef int ValueType;

//用拉链法的方式解决哈希冲突

typedef int (*HashFunc)(KeyType key);

//键值对的结构体(用链表来处理哈希冲突)
typedef struct KeyValue{
    KeyType key;
    ValueType value;
    struct KeyValue* next;
}KeyValue;

//哈希表
typedef struct HashTable{
    //如果链表带头结点的话，数组类型为结构体指针
    //如果链表不带头结点的话，数组类型为结构体变量
    KeyValue* data[HashMaxSize];
    size_t size;
    HashFunc func;
}HashTable;


//初始化
void HashInit(HashTable* ht, HashFunc func);

//销毁哈希表
void HashDestroy(HashTable* ht);

//插入元素
void HashInsert(HashTable* ht, KeyType key, ValueType value);

//查找指定元素
KeyValue* HashFind(HashTable* ht, KeyType key);

//删除指定元素
void HashRemove(HashTable* ht, KeyType key);
