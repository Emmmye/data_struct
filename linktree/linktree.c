#include "linktree.h"

LinkTree* CreateNode(LinkTreeType value)
{
    LinkTree* newNode = (LinkTree*)malloc(sizeof(LinkTree));
    newNode->data = value;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

LinkTree* _LinkTreeCreate(LinkTreeType array[],size_t size,size_t* index,LinkTreeType null_node)
{
    if(index == NULL)
    {
        return NULL;
    }
    if(*index >= size)
    {
        return NULL;
    }
    if(array[*index]==null_node)
    {
        return NULL;
    }
    LinkTree* newNode = CreateNode(array[*index]);
    (*index)++;
    newNode->lchild = _LinkTreeCreate(array,size,index,null_node);
    (*index)++;
    newNode->rchild = _LinkTreeCreate(array,size,index,null_node);
    return newNode;
}

LinkTree* LinkTreeCreate(LinkTreeType array[],size_t size, LinkTreeType null_node)
{
    size_t index = 0;
    return _LinkTreeCreate(array,size,&index,null_node);
}

void _LinkTreeToLink(LinkTree* root, LinkTree** old)
{
   if(old == NULL || root == NULL)
   {
       return;
   }
   //处理根节点
   if((*old) != NULL)
   {
       root->prev = *old;
       (*old)->next = root;
   }
   *old = root;
   //处理左子树
   _LinkTreeToLink(root->lchild,old);
   //处理右子树
   _LinkTreeToLink(root->rchild,old);
   return;
}

void LinkTreeListPrint(LinkTree* root)
{
    if(root == NULL)
    {
        return;
    }
    LinkTree* cur = root;
    while(cur != NULL)
    {
        printf("%c ",cur->data);
        cur=cur->next;
    }
}

void LinkTreeToLink(LinkTree* root)
{
    LinkTree* old = NULL;
    _LinkTreeToLink(root,&old);
}

void PreOrderLinkTree(LinkTree* root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%c ",root->data);
    PreOrderLinkTree(root->lchild);
    PreOrderLinkTree(root->rchild);
}

void TestLinkTreeCreate()
{
    LinkTree* root = NULL;
    LinkTreeType array[] = "abd##e##c#f##";
    root = LinkTreeCreate(array,strlen(array),'#');
    printf("前序遍历结果:  ");
    PreOrderLinkTree(root);
    printf("\n");
}
void TestTreeToLink()
{
    LinkTree* root = NULL;
    LinkTreeType array[] = "abd##e##c#f##";
    root = LinkTreeCreate(array,strlen(array),'#');
    LinkTreeToLink(root);
    printf("前序遍历结果:  ");
    LinkTreeListPrint(root);
    printf("\n");
}

int main()
{
    TestLinkTreeCreate();
    TestTreeToLink();
    return 0;
}
