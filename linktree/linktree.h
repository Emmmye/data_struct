#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef char LinkTreeType;

typedef struct LinkTree{
    struct LinkTree* lchild;
    struct LinkTree* rchild;
    struct LinkTree* next;
    struct LinkTree* prev;
    LinkTreeType data;
}LinkTree;

LinkTree* CreataNode(LinkTreeType value);

LinkTree* LinkTreeCreate(LinkTreeType array[], size_t size, LinkTreeType null_node);

void LinkTreeToLink(LinkTree* root);

void PreOrderLinkTree(LinkTree* root);
