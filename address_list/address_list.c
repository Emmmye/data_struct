#include "address_list.h"
#include <assert.h>
#include <stdlib.h>
//菜单
void Menu()
{
    printf("--------------------------------\n");
    printf("------选择你要进行的操作:-------\n");
    printf("--1.添加联系人----2.删除联系人--\n");
    printf("--3.查找联系人----4.修改信息----\n");
    printf("--5.显示联系人----6.清空联系人--\n");
    printf("---------7.退出通讯录-----------\n");
    printf("--------------------------------\n");
}


//通讯录初始化
void AddressListInit(AddressList* head)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    head->capaity = 1000;
    head->data = (LinkMan*)malloc(head->capaity*sizeof(LinkMan));
    assert(head->data != NULL);
    head->size = 0;
}
//提供方法：
//如果当前通讯录满了，就要动态扩容
LinkMan* AddressListExpand(AddressList* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    LinkMan* new_head = (LinkMan*)malloc(2*head->capaity*sizeof(LinkMan)+sizeof(LinkMan));
    size_t i = 0;
    for(; i < head->size; i++)
    {
        new_head[i] = head->data[i];
    }
    free(head->data);
    return new_head;
}
//1. 添加联系人信息 
void AddressListPush(AddressList* head, LinkMan value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(head->size == head->capaity)
    {
        //通讯录满了
        head->data = AddressListExpand(head);
        head->capaity = 2*head->capaity+1;
    }
    head->data[head->size++] = value;
}
//2. 删除指定联系人信息 
void AddressListPop(AddressList* head, const char* name)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(head->size == 0)
    {
        //空的通讯录
        return;
    }
    size_t i = 0;
    for(; i<head->size;i++)
    {
        if(strcmp(head->data[i].name,name) == 0)
        {
            break;
        }
    }
    for(; i<head->size-1;i++)
    {
        head->data[i] = head->data[i+1];
    }
    head->size--;
    printf("删除成功\n");
}
//3. 查找指定联系人信息 
LinkMan* AddressListFind(AddressList* head, const char* name)
{
    if(head == NULL || name == NULL)
    {
        return NULL;
    }
    size_t  i = 0;
    for(; i<head->size; i++)
    {
        if(strcmp(head->data[i].name,name) == 0)
        {
            return &head->data[i];
        }
    }
    printf("该联系人不存在\n");
    return NULL;
}
//4. 修改指定联系人信息 
void AddressListRevise(AddressList* head, LinkMan new_value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    size_t i = 0;
    for(; i<head->size; i++)
    {
        if(strcmp(head->data[i].name,new_value.name) == 0)
        {
            head->data[i] = new_value;
            return;
        }
    }
    AddressListPush(head,new_value);
    return;
}
//5. 显示所有联系人信息 
void AddressListPrint(AddressList* head)
{
    if(head == NULL)
    {
        return;
    }
    size_t i = 0;
    for(; i < head->size ;i++)
    {
        printf("=========[%lu]========\n",i+1);
        LinkMan person = head->data[i];
        printf("[姓名]:%s \n",person.name);
        if(person.sex == 0)
        {
            printf("[性别]:男 \n");
        }else if(person.sex == 1)
        {
            printf("[性别]:女 \n");
        }else{
            printf("[性别]:未知\n");
        }
        printf("[年龄]:%lu \n",person.age);
        printf("[电话]:%lu \n",person.phone_number);
        printf("[住址]:%s \n",person.address);
        printf("\n");
    }
}
//6. 清空所有联系人 
void AddressListDestroy(AddressList* head)
{
    if(head == NULL)
    {
        return;
    }
    free(head->data);
    head->size = 0;
    head->capaity = 0;
}
//7. 以名字排序所有联系人
void AddressListSortByName(AddressList* head)
{
    if(head == NULL)
    {
        return;
    }
    size_t i = 0;
    LinkMan tmp;
    for(; i < head->size; i++)
    {
        size_t j = 0;
        for(; j < head->size - i - 1; j++)
        {
            if(strcmp(head->data[j].name,head->data[j+1].name) > 0)
            {
                tmp = head->data[j];
                head->data[j] = head->data[j+1];
                head->data[j+1] = tmp;
            }
        }
    }
}
//8.从文件中读取数据
void ReadFromText(AddressList* head)
{
    if( head == NULL )
    {
        return;
    }
    FILE* fp = fopen("./addr.txt","r+");
    if(fp == NULL)
    {
        return;
    }
    LinkMan person;
    int ret = fread(&person,sizeof(person),1,fp);
    while(ret)
    {
        head->data[head->size++] = person;
        ret = fread(&person,sizeof(person),1,fp);
    }
    
    fclose(fp);
}
//9.将数据添加进文件中
void WriteToText(AddressList* head)
{
    if(head == NULL)
    {
        return;
    }
    FILE* fp = fopen("./addr.txt","w");
    if(fp == NULL)
    {
        return;
    }
    size_t i = 0;
    for(; i<head->size;i++){
    LinkMan person = head->data[i];
    fwrite(&person,sizeof(person),1,fp);
    }
    fclose(fp);
}

//打印个体
void PrintLinkMan(LinkMan* person)
{   
    if(person == NULL)
    {
        printf("显示失败\n");
        return;
    }
    printf("[姓名]:%s \n",person->name);
    if(person->sex == 0)
    {
        printf("[性别]:男 \n");
    }else if(person->sex == 1)
    {
        printf("[性别]:女 \n");
    }else{
        printf("[性别]:未知\n");
    }
    printf("[年龄]:%lu \n",person->age);
    printf("[电话]:%lu \n",person->phone_number);
    printf("[住址]:%s \n",person->address);
    printf("\n");
}
/////////////////////////////////////////////////////////////////
//////////TEST      PART////////////////////////////////////////
////////////////////////////////////////////////////////////////
#if 0

//1.添加 2.删除 3.查找 4.修改 5.显示 6.清空 7.排序
#endif
int main()
{
    int select = 0;
    AddressList adder;
    AddressListInit(&adder);
    char buf_name[NAME_MAX] = {0};
    LinkMan person;
    LinkMan* p;
    ReadFromText(&adder);
    while(1)
    {
        system("clear");
        Menu();
        printf("请做出你的选择: ");
        scanf("%d",&select);
        switch(select)
        {
        case 1:
            printf("请输入姓名: ");
            scanf("%s",person.name);
            printf("请选择性别: 男 0, 女 1, 未知 2     ");
            scanf("%d",&person.sex);
            printf("请输入年龄: ");
            scanf("%lu",&person.age);
            printf("请输入电话号码: ");
            scanf("%lu",&person.phone_number);
            printf("请输入家庭住址: ");
            scanf("%s",person.address);
            AddressListPush(&adder,person);
            WriteToText(&adder);
            memset(person.name,0,sizeof(person.name));
            memset(person.address,0,sizeof(person.address));
            break;
        case 2:
            printf("请输入删除的联系人的姓名:");
            scanf("%s",buf_name);
            AddressListPop(&adder,buf_name);
            WriteToText(&adder);
            break;
        case 3:
            printf("请输入你要查找的联系人的姓名:");
            scanf("%s",buf_name);
            p = AddressListFind(&adder,buf_name);
            PrintLinkMan(p);
            break;
        case 4:
            printf("请输入你要修改信息的联系人姓名:");
            scanf("%s",person.name);
            printf("请选择性别: 男 0, 女 1, 未知 2     ");
            scanf("%d",&person.sex);
            printf("请输入年龄: ");
            scanf("%lu",&person.age);
            printf("请输入电话号码: ");
            scanf("%lu",&person.phone_number);
            printf("请输入家庭住址: ");
            scanf("%s",person.address);
            AddressListRevise(&adder,person);
            memset(person.name,0,sizeof(person.name));
            memset(person.address,0,sizeof(person.address));
            break;
            WriteToText(&adder);
            //1.添加 2.删除 3.查找 4.修改 5.显示 6.清空 7.退出
        case 5:
            AddressListSortByName(&adder);
            AddressListPrint(&adder); 
            sleep(5);
            break;
        case 6:
            AddressListDestroy(&adder);
            printf("清空成功\n");
            break;
        case 7:
            return 0;
        default:
            printf("输入错误\n");
            break;
        }
    }
    return 0;
}
