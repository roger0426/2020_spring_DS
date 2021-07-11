//
//  main.c
//  ds hw3 Huffman
//
//  Created by Chang Chung Che on 2020/4/21.
//  Copyright © 2020 Chang Chung Che. All rights reserved.
//

//#include <stdio.h>
//#include <stdlib.h>

#include "function.h"

int main(int argc, const char * argv[])
{
    int inssize = 0, realsize = 0;
    int i = 0, j = 0;
    
    int insert[150];
    int input;
    
    printf("Input symbol (char):");
    while ((input = getchar()) != '\n')                               //receive the symbol input
    {
        if (input != ' ')
        {
            insert[inssize] = input;
            inssize++;
        }
    }
    
    int data[inssize][2];
    for (i = 0; i < inssize; i++)
    {
        data[i][0] = 0;
        data[i][1] = 0;
    }
    
    realsize = 1;
    for (i = 0; i < inssize; i++)                           //count for each ASCII
    {
        for(j = 0; j < realsize; j++)
        {
            if (i == 0)
            {
                data[j][0] = insert[i];
                data[j][1]++;
                break;
            }
            else if (insert[i] == data[j][0])
            {
                data[j][1]++;
                break;
            }
            else if(j == realsize - 1)
            {
                realsize ++;
                data[j + 1][0] = insert[i];
                data[j + 1][1]++;
                break;
            }
        }
    }
    
    for (int i = 0; i < realsize; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
                if((data[j][0] > data[i][0]))                      //sort in ASCII
            {
                int temp = data[j][1];                                    //exchange freq
                data[j][1] = data[i][1];
                data[i][1] = temp;

                temp = data[j][0];                                        //exchange symbol
                data[j][0] = data[i][0];
                data[i][0] = temp;
            }
        }
    }
    
    printf("\nYour input size [int]:\t%d", realsize);                 //prob.1 print
    printf("\nYour inout symbol [char]:\t\t");
    for (i = 0; i < realsize; i++)
    {
        printf("%c ", data[i][0]);
    }
    printf("\nYour inout frequency [int]:\t");
    for (i = 0; i < realsize; i++)
    {
        printf("%d ", data[i][1]);
    }
    printf("\n==================================\n");               //prob.2
    
    int top = 1;
    int left, right;
    
    left = 2*top;
    right = 2*top + 1;
    
    while ((left <= realsize) || (right <= realsize))               //min-heap data (array)
    {
        if ((data[top-1][1] > data[left-1][1]) && (left <= realsize))
        {
            int t = data[top-1][1];
            data[top-1][1] = data[left-1][1];
            data[left-1][1] = t;

            t = data[top-1][0];
            data[top-1][0] = data[left-1][0];
            data[left-1][0] = t;

            top = 0;
        }
        else if((data[top-1][1] > data[right-1][1]) && (right <= realsize))
        {
            int t = data[top-1][1];
            data[top-1][1] = data[right-1][1];
            data[right-1][1] = t;

            t = data[top-1][0];
            data[top-1][0] = data[right-1][0];
            data[right-1][0] = t;

            top = 0;
        }
        top++;
        left = 2*top;
        right = 2*top + 1;
    }
    
    
    int k = 2, q = 0;
    printf("\n\nMinHeap tree:\n");                                   //print MinHeap tree
    for (j =0; j<realsize; j++)
    {
        printf("%c %d\t\t", data[j][0], data[j][1]);
        if(!((j + 2)%k))
        {
            printf("\n");
            k = k*2;
            q++;
        }
    }
    printf("\n\nMax level:%d\n\n", q);
    
    printf("==================================\n\n");               //prob.2
    
    struct listnode *head;                                          //put data in the linked list
    head = newlistnode(NULL, data[realsize - 1][0], data[realsize - 1][1]);
    for (i = realsize - 2; i >= 0; i--)
    {
        head = newlistnode(head, data[i][0], data[i][1]);
    }
    head = minheap(head, realsize);                                 //min-heap data(linked list)
    
    struct treenode *huffroot, *root, *lchild, *rchild;
    huffroot = NULL;
    
    putchar('\n');
    int newfreq = 0;
    i = realsize;
    while(i > 1)                                    //build the huffman tree(pop, min-heap, pop, min-heap, push to the end, minheap)
    {
        root = newtreenode('0', (head->freq + head->next->freq));  //^
        if (i == realsize)
        {
            huffroot = root;
        }
        
        newfreq = head->freq;
        if (head->node != NULL)
        {
            lchild = head->node;
        }
        else
        {
            lchild = newtreenode(head->symbol, head->freq);
        }
        head = poplistnode(head);
        head = minheap(head, i - 1);

        newfreq += head->freq;
        if (head->node != NULL)
        {
            rchild = head->node;
        }
        else
        {
            rchild = newtreenode(head->symbol, head->freq);
        }
        head = poplistnode(head);
        head = minheap(head, i - 2);

        root->leftchild = lchild;
        root->rightchild = rchild;

        i--;
        head = pushlistnode(head, i - 1, newfreq, root);
        head = minheap(head, i);
    }
    huffroot = head->node;
    
    
    printf("preorder\n");                                     //print in preorder, inorder, postorder
    preorderprint(huffroot);
    printf("\n");
    
    printf("\ninorder\n");
    inorderprint(huffroot);
    printf("\n");
    
    printf("\npostorder\n");
    postorderprint(huffroot);
    printf("\n");
    
    printf("\nmax deep:\t%d\n", maxdeep(huffroot) - 1);           //max level
    
    printf("number of node:\t%d\n", realsize * 2 - 1);          //number of node
    
    printf("==================================\n\n");       //prob.3
    
    
    huffmancode(huffroot, NULL);                                //code the huffman tree leaves
    
    printf("HUffman code:\n");
    printhuffmancode(huffroot);
    
    printf("==================================\n\n");       //prob.4
    
    struct listnode *insertcode = NULL;
    
    printf("Input huffman code(binary):\t");
    
    while ((input = getchar()) != '\n')                         //receive the huffman code
    {
        if (input != ' ')
        {
            insertcode = newlistnode(insertcode, input, 0);
        }
    }
    
    insertcode = invertlist(insertcode);                        //fix the code sequence
    
    printf("your decoded answer:\t");
    huffmandecoder(huffroot, insertcode);                       //decode the huffman code
    getchar();
    return 0;
}

