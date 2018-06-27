#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int HashFunction(KeyType key)
{
    return key % HashMaxSize;
}

//创建元素结点(因为是链表存储)
KeyValue* CreateNode(KeyType key,ValueType value)
{
    KeyValue* new_node = (KeyValue*)malloc(sizeof(KeyValue));
    if(new_node == NULL)
    {
        return NULL;
    }
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

//初始化
void HashInit(HashTable* ht, HashFunc func)
{
    if(ht == NULL)
    {
        return;
    }
    ht->size = 0;
    ht->func = func;
    size_t i = 0;
    for(; i < HashMaxSize; i++)
    {
        ht->data[i] = NULL;
    }
}

void _HashDestroy(KeyValue* to_destroy)
{
    KeyValue* cur = to_destroy->next;
    free(to_destroy);
    if(cur != NULL)
    {
        _HashDestroy(cur);
    }
}
//销毁哈希表
void HashDestroy(HashTable* ht)
{
    if(ht == NULL)
    {
        return;
    }
    size_t i = 0;
    for(; i < HashMaxSize; i++)
    {
        if(ht->data[i] != NULL)
        {
            _HashDestroy(ht->data[i]);
            ht->data[i] = NULL;
        }
    }
}

//插入元素
void HashInsert(HashTable* ht, KeyType key, ValueType value)
{
    if(ht == NULL)
    {
        return;
    }
    if(ht->size >= HashMaxSize*10)
    {
        return;
    }
    //1.先通过哈希函数求出当前元素在哈希表中的下标 offset
    size_t offset = ht->func(key);
    //2.在 offset 处头插入新元素，也就是新结点
    //3.如果当前链表中存在与插入元素相同的 key 值，则直接返回，插入失败
    KeyValue* cur = ht->data[offset]; 
    while(cur != NULL)
    {
        if(cur->key == key)
        {
            return;
        }
        cur = cur->next;
    }
    KeyValue* new_node = CreateNode(key,value);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
    ++ht->size;
}

//查找指定元素
KeyValue* HashFind(HashTable* ht, KeyType key)
{
    if(ht == NULL)
    {
        return NULL;
    }   
    //1.先通过哈希函数找到当前 key 在哈希表中的下标
    size_t offset = ht->func(key);
    //2.找到以后遍历链表，找到就返回，找不到就退出
    KeyValue* cur = ht->data[offset];
    while(cur != NULL)
    {
        if(cur->key == key)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void DestroyNode(KeyValue* node)
{
    free(node);
}
//删除指定元素
void HashRemove(HashTable* ht, KeyType key)
{
    if(ht == NULL)
    {
        return;
    }
    //1.先通过哈希函数求出哈希表的下标 offset
    size_t offset = ht->func(key);
    KeyValue* prev = NULL;
    KeyValue* cur = ht->data[offset];
    while(cur != NULL)
    {
    //2.在该位置的链表中找到该元素
    //3.先保存前一个节点，才能删除当前要删除的结点
        if(cur->key == key && prev == NULL)
        {
            ht->data[offset] = cur->next;
            free(cur);
            return;
        }
        else if(cur->key == key && prev != NULL)
        {
            prev->next = cur->next;
            DestroyNode(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    return;
}


////////////////////////////////////////
///////TEST  PART//////////////////////
////////////////////////////////////////

void PrintHashTable(HashTable* ht, const char* msg)
{
    if(ht == NULL || msg == NULL)
    {
        return;
    }
    printf("%s\n",msg);
    size_t i = 0;
    for(; i < HashMaxSize; i++)
    {
        KeyValue* cur = ht->data[i]; 
        while(cur != NULL)
        {
            printf("[%d %d] ",cur->key,cur->value);
            cur = cur->next;
        }
    }
    printf("\n");
}

void TestInsert()
{
    TESTHEAD;
    HashTable ht;
    HashInit(&ht,HashFunction);
    HashInsert(&ht,1,10);
    HashInsert(&ht,1,15);
    HashInsert(&ht,2,20);
    HashInsert(&ht,1001,100);
    HashInsert(&ht,1002,101);
    PrintHashTable(&ht,"插入四个元素");
}

void TestFind()
{
    TESTHEAD;
    HashTable ht;
    HashInit(&ht,HashFunction);
    HashInsert(&ht,1,10);
    HashInsert(&ht,1,15);
    HashInsert(&ht,2,20);
    HashInsert(&ht,1001,100);
    HashInsert(&ht,1002,101);
    KeyValue* cur = HashFind(&ht,1001);
    printf("except 100, actural %d \n",cur->value);
}
void TestRemove()
{
    TESTHEAD;
    HashTable ht;
    HashInit(&ht,HashFunction);
    HashInsert(&ht,1,10);
    HashInsert(&ht,1,15);
    HashInsert(&ht,2,20);
    HashInsert(&ht,1001,100);
    HashInsert(&ht,1002,101);
    HashRemove(&ht,1001);
    PrintHashTable(&ht,"删除一个元素");
}
void TestHashDestroy()
{
    TESTHEAD;
    HashTable ht;
    HashInit(&ht,HashFunction);
    HashInsert(&ht,1,10);
    HashInsert(&ht,1,15);
    HashInsert(&ht,2,20);
    HashInsert(&ht,1001,100);
    HashInsert(&ht,1002,101);
    HashDestroy(&ht);
    PrintHashTable(&ht,"销毁哈希表");
}

int main()
{
    TestInsert();
    TestFind();
    TestRemove();
    TestHashDestroy();
    return 0;
}
