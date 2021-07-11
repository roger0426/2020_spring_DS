//
//  function.h
//  ds_hw3_huffmancode
//
//  Created by Chang Chung Che on 2020/5/10.
//  Copyright © 2020 Chang Chung Che. All rights reserved.
//

#ifndef function_h
#define function_h

#include <stdio.h>
#include <stdlib.h>

struct listnode
{
    int freq;
    char symbol;
    struct listnode *next;
    struct treenode *node;
};

struct treenode
{
    int freq;
    char symbol;
    struct listnode *code;
    struct treenode *leftchild;
    struct treenode *rightchild;
};

void printlist(struct listnode *print);

struct listnode *poplistnode(struct listnode *node);
struct listnode *pushlistnode(struct listnode *head, int size, int freq, struct treenode *node);
struct listnode *newlistnode(struct listnode *head, int symbol, int freq);

struct listnode *minheap(struct listnode *data, int size);


struct treenode *newtreenode(int symbol, int freq);
void preorderprint(struct treenode *root);
void inorderprint(struct treenode *root);
void postorderprint(struct treenode *root);

int maxdeep(struct treenode *root);

void huffmancode(struct treenode *root, struct listnode *result);
void huffmandecoder(struct treenode *head, struct listnode *code);

void printhuffmancode(struct treenode *root);
struct listnode *invertlist(struct listnode *head);

#endif /* function_h */
