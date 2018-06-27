#include "search_tree.h"
#include <stdio.h>
#include <stdlib.h>

//初始化二叉搜索树
void SearchTreeInit(SearchTreeNode** root)
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    *root = NULL;
}

//创建一个二叉搜索树的节点
SearchTreeNode* CreateNode(SearchTreeType value)
{
    SearchTreeNode* new_node = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

//销毁一个结点
void DestroyNode(SearchTreeNode* node)
{
    free(node);
}

//插入数据
void SearchTreeInsert(SearchTreeNode** root, SearchTreeType key) 
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)
    {
        *root = CreateNode(key);
        return;
    }
    if((*root)->data < key)
    {
        SearchTreeInsert(&(*root)->rchild,key);
    }else if((*root)->data > key)
    {
        SearchTreeInsert(&(*root)->lchild,key);
    }else
    {
        //相等的情况就直接舍弃掉好了
        return;
    }
}

//查找指定数据
SearchTreeNode* SearchTreeFind(SearchTreeNode* root, SearchTreeType to_find) 
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->data == to_find)
    {
        return root;
    }
    else if(root->data > to_find)
    {
        return SearchTreeFind(root->lchild,to_find);
    }else
    {
        return SearchTreeFind(root->rchild,to_find);
    }
}
//交换函数，仅在要删除结点左右子树都存在的时候需要调用
//  1.与左子树中的最大值交换
//  2.或者与右子树中的最小值交换
void Swap(SearchTreeType* a, SearchTreeType* b)
{
    SearchTreeType tmp = *a;
    *a = *b;
    *b = tmp;
}



void _SearchTreeRemove(SearchTreeNode** cur)
{
    if(cur == NULL)
    {
        return;
    }
    //1.要删除的节点是叶子节点，就直接释放，然后置空，注意要用二级指针接收
    if((*cur)->lchild == NULL && (*cur)->rchild == NULL)
    {
        free(*cur);
        *cur = NULL;
        return;
    }
    SearchTreeNode** to_delete = cur;
    //仅有左子树，就把左子树上移，因为是二级指针，所以直接解引用将其置空就好
    //仅有右子树，就把右子树上移
    if((*cur)->rchild == NULL )
    {
        to_delete = cur;
        *cur = (*cur)->lchild;
        free(*to_delete);
        return;
    }
    else if((*cur)->lchild == NULL )
    {
        to_delete = cur;
        *cur = (*cur)->lchild;
        free(*to_delete);
        return;
    }
    //3.要删除节点的左孩子和右孩子节点不是叶子节点，也就是说子树较多
    //      1.找到左子树中的最大值，
    //      2.将这个最大值与当前节点要被删除的值交换
    //      3.保证被删除的值处于一个叶子节点上
    else{
        to_delete = &(*cur)->lchild;
        while((*to_delete)->rchild != NULL)
        {
            *to_delete = (*to_delete)->rchild;
        }
        Swap(&(*cur)->data,&(*to_delete)->data);
        _SearchTreeRemove(to_delete);
    }
}
//删除指定值
void SearchTreeRemove(SearchTreeNode** root, SearchTreeType key) 
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)
    {
        //空的二叉搜索树
        return;
    }
    else{
        if((*root)->data == key)
        {
            _SearchTreeRemove(root);
            return;
        }
        else if(key < (*root)->data && (*root)->lchild != NULL)
        {
            SearchTreeRemove(&(*root)->lchild,key);
        }else if (key > (*root)->data && (*root)->rchild != NULL)
        {
            SearchTreeRemove(&(*root)->rchild,key);
        }
    }
}
//插入数据(非递归)
void SearchTreeInsertByLoop(SearchTreeNode** root, SearchTreeType key) 
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)//空树
    {
        *root = CreateNode(key);
        return;
    }
    SearchTreeNode* cur = *root;
    SearchTreeNode* parents = NULL;//用来保存父节点
    while(cur != NULL)
    {
        //规定二叉搜索树中不能出现重复的值
        if(cur->data == key)
        {
            return;
        }
        else if(key < cur->data)
        {
            parents = cur;
            cur = cur->lchild;
        }else
        {
            parents = cur;
            cur = cur->rchild;
        }
    }
    cur = CreateNode(key);
    if(key < parents->data)
    {
        parents->lchild = cur;
    }else
    {
        parents->rchild = cur;
    }
}

//查找指定数据(非递归)
SearchTreeNode* SearchTreeFindByLoop(SearchTreeNode* root, SearchTreeType to_find) 
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    SearchTreeNode* cur = root;
    while(cur != NULL)
    {
        if(cur->data == to_find)
        {
            return cur;
        }else if(to_find < cur->data)
        {
            cur = cur->lchild;
        }else
        {
            cur = cur->rchild;
        }
    }
    //cur == NULL 没找到
    return NULL;
}

//删除指定值(非递归)
void SearchTreeRemoveByLoop(SearchTreeNode** root, SearchTreeType key) 
{
    if(root == NULL)
    {
        return;
    }
    if(*root == NULL)
    {
        return;
    }
    SearchTreeNode* to_delete = *root;
    SearchTreeNode* parents = NULL;
    //找到要删除元素的结点
    while(to_delete != NULL)
    {
        if(to_delete->data == key)
        {
            break;
        }else if(key < to_delete->data)
        {
            parents = to_delete;
            to_delete = to_delete->lchild;
        }else
        {
            parents = to_delete;
            to_delete = to_delete->rchild;
        }
    }
    if(to_delete == NULL)
    {
        //说明没找到，直接返回
        return;
    }
    //1.要删除的结点是叶子结点
    if(to_delete->lchild == NULL && to_delete->rchild == NULL)
    {
        //如果要删除的结点是根节点
        //意思是寻找删除结点的循环中，一进去就命中了，
        //所以此时要删除的结点是根节点，而父节点parents指向的是空
        if(to_delete == *root)
        {
            *root = NULL;
        }else
        {
            if(to_delete->data < parents->data)
            {
                parents->lchild = NULL;
            }else
            {
                parents->rchild = NULL;
            }
        }
        DestroyNode(to_delete);
    }
    //2.要删除的结点只有左子树，没有右子树
    if(to_delete->lchild != NULL && to_delete->rchild == NULL)
    {
        if(to_delete == *root)
        {
            *root = to_delete->lchild;
        }
        else
        {
            if(to_delete->data < parents->data)
            {
                parents->lchild = to_delete->lchild;
            }else
            {
                parents->rchild = to_delete->lchild;
            }
        }
        DestroyNode(to_delete);
    }
    //3.要删除的结点只有右子树，没有左子树
    else if(to_delete->rchild != NULL && to_delete->lchild == NULL)
    {
        if(to_delete == *root)
        {
            *root = to_delete->rchild;
        }
        else{
            if(to_delete->data < parents->data)
            {
                parents->lchild = to_delete->rchild;
            }
            else
            {
                parents->rchild = to_delete->rchild;
            }
        }
        DestroyNode(to_delete);
    }
    //4.要删除的结点左右子树都有
    else
    {
        SearchTreeNode* max = to_delete->lchild;
    //  a)找到左子树中的最大值
    //  即使parents为空，parents也会先指向to_delete，to_delete是不为空的
        parents = to_delete;
        while(max->rchild != NULL)
        {
            parents = max;
            max = max->rchild;
        }
    //  b)将最小值赋给要删除的结点
        to_delete->data = max->data;
        if(max->data < parents->data)
        {
            parents->rchild = max->lchild;
        }
        else
        {
            parents->lchild = max->lchild;
        }
        DestroyNode(max);
    //  c)将最小值所在的结点删除
    }
}

//////////////////////////////////////////////////
///////////////TEST  PART/////////////////////////
//////////////////////////////////////////////////

void Preorder(SearchTreeNode* root)
{
    if(root == NULL)
        return;
    printf("%c ",root->data);
    Preorder(root->lchild);
    Preorder(root->rchild);
}
void Inorder(SearchTreeNode* root)
{
    if(root == NULL)
        return;
    Inorder(root->lchild);
    printf("%c ",root->data);
    Inorder(root->rchild);
}

void SearchTreeNodePrintChar(SearchTreeNode* root, const char* msg)
{
    if(root == NULL || msg == NULL)
    {
        return;
    }
    printf("%s \n",msg);
    printf("\n");
    printf("前序遍历结果为: ");
    Preorder(root);
    printf("\n");
    printf("中序遍历结果为: ");
    Inorder(root);
    printf("\n");
}

void TestInit()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    printf("except NULL , actural %p \n",root);
}
void TestInsert()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'g');
    SearchTreeNodePrintChar(root,"插入七个元素");
}
void TestFind()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeNodePrintChar(root,"插入五个元素");
    SearchTreeNode* cur = SearchTreeFind(root,'a');
    if(cur != NULL)
    {
        printf("except a ,actural %c \n",cur->data);
    }
}
void TestRemove()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'g');
    SearchTreeNodePrintChar(root,"插入七个元素");
    SearchTreeRemove(&root,'g');
    SearchTreeNodePrintChar(root,"删除一个指定元素");
}
void TestInsertByLoop()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsertByLoop(&root,'d');
    SearchTreeInsertByLoop(&root,'c');
    SearchTreeInsertByLoop(&root,'e');
    SearchTreeInsertByLoop(&root,'a');
    SearchTreeInsertByLoop(&root,'b');
    SearchTreeNodePrintChar(root,"插入五个元素");
}
void TestFindByLoop()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsertByLoop(&root,'d');
    SearchTreeInsertByLoop(&root,'c');
    SearchTreeInsertByLoop(&root,'e');
    SearchTreeInsertByLoop(&root,'a');
    SearchTreeInsertByLoop(&root,'b');
    SearchTreeNode* cur = SearchTreeFindByLoop(root,'a');
    if(cur != NULL)
    {
        printf("except a ,actural %c \n",cur->data);
    }
}
void TestRemoveByLoop()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'g');
    SearchTreeNodePrintChar(root,"插入七个元素");
    SearchTreeRemoveByLoop(&root,'c');
    SearchTreeNodePrintChar(root,"删除一个指定元素");
}
int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    TestInsertByLoop();
    TestFindByLoop();
    TestRemoveByLoop();
    return 0;
}
