//
//  function.c
//  ds_hw3_huffmancode
//
//  Created by Chang Chung Che on 2020/5/10.
//  Copyright © 2020 Chang Chung Che. All rights reserved.
//

#include "function.h"

struct listnode *minheap(struct listnode *data, int size)
{
    int top = 0, i;
    int left, llim, rlim;
    int conti = 1;
    struct listnode *head, *frontpreva, *preva, *prevb, *lnode, *rnode;
    
    if (data == NULL)
    {
        return NULL;
    }
    
    llim = size / 2;                            //set the upper limit of the leftchild/rightchild
    rlim = (size - 1) / 2;
    
    head = data;
    preva = head;
    prevb = head;
    frontpreva = head;
    if (head->next != NULL)
    {
        lnode = head->next;
        rnode = lnode->next;
    }
    else
    {
        lnode = rnode = NULL;
    }
    
    int j;
    for (j = size - 1; j > 0; j--)
    {

        top = 1;
        
        while (lnode != NULL || rnode != NULL)
        {
            lnode = head;
            rnode = head;
            prevb = head;
            frontpreva = head;
            preva = head;
            
            for (i = top; i > 1; i--)                       //set all the pointer to the right position
            {
                preva = preva->next;
            }

            for (i = top - 1; i > 1; i--)
            {
                frontpreva = frontpreva->next;
            }
            
            for (left = top * 2 - 2; left > 0; left --)
            {
                prevb = prevb->next;
            }
            
            if (top > llim)
            {
                lnode = NULL;
            }
            else
            {
                lnode = prevb->next;
            }
            
            
            if (top > rlim)
            {
                rnode = NULL;
            }
            else
            {
                rnode = lnode->next;
            }
            
            if (lnode != NULL)
            {
                if (preva->freq > lnode->freq)          //compare with the leftchild
                {
                    if (top == 1)
                    {
                        head = lnode;                       //switch with left node(first)
                        lnode->next = preva;
                        preva->next = rnode;
                        lnode = prevb;
                        prevb = preva;
                    }
                    else
                    {
                        frontpreva->next = lnode;           //switch with left node(except first)
                        lnode->next = preva->next;
                        prevb->next = preva;
                        preva->next = rnode;
                    }
                    top = 0;
                    preva = head;
                    break;
                }
            }
            
            if (rnode != NULL)
            {
                if (preva->freq > rnode->freq)          //compare with the rightchild
                {
                    if (top == 1)
                    {
                        head = rnode;                       //switch with left node(first)
                        preva->next = rnode->next;
                        rnode->next = lnode;
                        lnode->next = preva;
                    }
                    else
                    {
                        struct listnode *backpreva = preva->next;
                        preva->next = rnode->next;
                        rnode->next = backpreva;
                        frontpreva->next = rnode;
                        lnode->next = preva;
                    }
                    top = 0;
                    preva = head;
                }
            }
            
            int l = 0, r = 0;
            if(lnode != NULL)
            {
                l = lnode->freq;
            }
            if(rnode != NULL)
            {
                r = rnode->freq;
            }
            
            if (preva == NULL || (l == 0 && r == 0))
            {
                conti = 0;
            }

            top ++;
        }
    }
    return head;
}
void printlist(struct listnode *print)
{
    while(print)
    {
        printf("%c %d     ", print->symbol, print->freq);
//        printf("%c", print->symbol);
        print = print->next;
    }
    putchar('\n');
}
struct listnode *pushlistnode(struct listnode *head, int size, int freq, struct treenode *node)
{
    
    struct listnode *curr = malloc(sizeof(struct listnode));
    struct listnode *new = malloc(sizeof(struct listnode));
    
    if (head != NULL)
    {
            curr = head->next;

            if (head->next == NULL)
            {
                curr = head;
            }
    }
    int i;
    for (i = 0; i < size - 2; i++)
    {
        curr = curr->next;
    }
    
    curr->next = new;
    new->freq = freq;
    new->symbol = '0';
    new->next = NULL;
    new->node = node;
    
    if (head == NULL)
    {
        return new;
    }
    return head;
}
struct listnode *poplistnode(struct listnode *node)
{
    struct listnode *a = node->next;
    free(node);
    return a;
}
struct listnode *newlistnode(struct listnode *head, int symbol, int freq)
{
    struct listnode *new = malloc(sizeof(struct listnode));
    new->freq = freq;
    new->symbol = symbol;
    new->next = head;
    new->node = NULL;
    return new;
}

struct treenode *newtreenode(int symbol, int freq)
{
    struct treenode *new = malloc(sizeof(struct treenode));
    new->freq = freq;
    new->symbol = symbol;
    new->leftchild = NULL;
    new->rightchild = NULL;
    return new;
}
void preorderprint(struct treenode *root)
{
    printf("%d ", root->freq);
    
    if (root->leftchild != NULL)
    {
        preorderprint(root->leftchild);
    }
    
    if (root->rightchild != NULL)
    {
        preorderprint(root->rightchild);
    }
}
void inorderprint(struct treenode *root)
{
    if (root->leftchild != NULL)
    {
        inorderprint(root->leftchild);
    }
    
    printf("%d ", root->freq);
    
    if (root->rightchild != NULL)
    {
        inorderprint(root->rightchild);
    }
}
void postorderprint(struct treenode *root)
{
    if (root->leftchild != NULL)
    {
        postorderprint(root->leftchild);
    }
    
    if (root->rightchild != NULL)
    {
        postorderprint(root->rightchild);
    }
    
    printf("%d ", root->freq);
}
int maxdeep(struct treenode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int left = maxdeep(root->leftchild);
    int right = maxdeep(root->rightchild);
    
    return ((left > right ? left : right) + 1);
}

void huffmancode(struct treenode *root, struct listnode *result)
{
    if(root->leftchild != NULL)                     //turn left if leftchild exist
    {
        result = newlistnode(result, '1', 0);
        
        root->leftchild->code = result;
        huffmancode(root->leftchild, result);
    }
    
    result = result->next;
    
    if(root->rightchild != NULL)                     //turn left if leftchild exist
    {
        result = newlistnode(result, '0', 0);
        
        root->rightchild->code = result;
        huffmancode(root->rightchild, result);
    }
}

void printhuffmancode(struct treenode *root)
{
    struct listnode *hcode = root->code;
    if (root->leftchild != NULL)
    {
        printhuffmancode(root->leftchild);
    }
    if (root->rightchild != NULL)
    {
        printhuffmancode(root->rightchild);
    }
    
    if (root->leftchild == NULL && root->rightchild == NULL)            //print the code when it;s a leaf
    {
        printf("%c %d:\t", root->symbol, root->freq);
        char print[10];
        
        int size = 0, i = 0;
        for (i = 0; i < 10; i++)
        {
            print[i] = 0;
        }
        i = 0;
        while (hcode != NULL)
        {
            print[size] = hcode->symbol;
            hcode = hcode->next;
            size++;
        }
        for (i = size - 1; i >= 0; i--)
        {
            printf("%c", print[i]);
        }
        putchar('\n');
    }
}

struct listnode *invertlist(struct listnode *head)
{
    struct listnode *ptr = head, *tmp = NULL;                   //invert the linked list
    
    while(ptr->next != NULL)
    {
        head = ptr->next;
        ptr->next = tmp;
        tmp = ptr;
        ptr = head;
    }
    ptr->next = tmp;
    return head;
}

void huffmandecoder(struct treenode *head, struct listnode *code)
{
    struct treenode *curr;
    while (code != NULL)
    {
        curr = head;
        while (curr->leftchild != NULL && curr->rightchild != NULL)         //stop and print while get to a leaf
        {
            if (code == NULL)
            {
                printf("error!!\n");
                break;
            }
            if (code->symbol == '1')
            {
                if(curr->leftchild == NULL)
                {
                    printf("error!!\n");
                }
                else
                {
                    curr = curr->leftchild;
                }
            }
            else if(code->symbol == '0')
            {
                if(curr->rightchild == NULL)
                {
                    printf("error!!\n");
                }
                else
                {
                    curr = curr->rightchild;
                }
            }
            code = code->next;
        }
        printf("%c, ",curr->symbol);
    }
    printf("\n\n");
}
