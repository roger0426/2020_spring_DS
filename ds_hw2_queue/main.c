//
//  main.c
//  datastucture hw1
//
//  Created by Chang Chung Che on 2020/4/1.
//  Copyright c 2020 Chang Chung Che. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void linearqueue(void);                                                             //phototype functions
    void printarray(int sizelq, int front, int rear, int lq[]);
void circuilarqueue(void);
void linkedlistcircularqueue(void);
    struct node;
    void printlinkedlist(int size, struct node *t, int front, int rear);


int main(int argc, const char * argv[])                                             //main function
{
    int n=1;
    while (n)
    {
        int choice = 0;
        printf("###############################\nPlease select your choice \n");    //main function choice
        printf(" 1.Linear Queue \n 2.Circular Queue \n 3.Linked List \n 4.Exit\n\n");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1:
                linearqueue();
                break;
            case 2:
                circuilarqueue();
                break;
            case 3:
                linkedlistcircularqueue();
                break;
            case 4:
                return 0;
            default:
                printf("Error! Please re-enter\n\n");
                choice = 0;
        }
    }
    return 0;
}

void printarray(int size, int front, int rear, int array[])                         //print the lq array
{
    int i;
    for (i=0; i < size; i++)
    {
        printf("[%d] ",array[i]);
    }
    printf("\nFront : %d\tRear : %d\n\n",front,rear);
}

void linearqueue()                                                                  //linear queue function
{
    printf("\n@@ linearqueue @@\n");
    
    int sizelq = 0 ,funclq;
    int front = 0, rear = 0;
    int insert = 0;
    
    printf("Enter the size:\n");                                                    //user enter the size of lq
    scanf("%d",&sizelq);
    putchar('\n');
    
    int lq[sizelq];
    int i;
    for (i = 0; i<sizelq; i++)                                                  //initialize lq array
    {
        lq[i] = 0;
    }
    
    printf("Linear Queue: ");
    printarray(sizelq, front, rear, lq);
    
    printf(" 1.insertion\n 2.Deletion\n 3.Exit\n");                                 //user enter the function of lq
    
    int r = 1;
    while (r)
    {
        if (front == rear && rear == sizelq - 1 )                                   //lq space detection
        {
            printf("\n##The linear queue can't be used!!!\n");
            //getchar();getchar();
            printf("Linear Queue: ");
            printarray(sizelq, front, rear, lq);
            break;
        }
        
        printf("Enter your choice:\t");
        scanf("%d",&funclq);
        
        switch (funclq)
        {
            case 1:                                                                 //lq insertion
                if (rear == sizelq - 1)
                {
                    printf("##Queue is already full!!!\n\n");
                }
                else
                {
                    printf("Enter an element:\t");
                    scanf("%d",&insert);
                    putchar('\n');
                    lq[rear + 1 ] = insert;
                    //lq[rear + 1] = rand()%10+1;
                    rear ++;
                }
                printf("Linear Queue: ");
                printarray(sizelq, front, rear, lq);
                break;
                
            case 2:                                                                 //lq deletion
                if (rear == front)
                {
                    printf("##Queue is already empty!!!\n\n");
                }
                else
                {
                    printf("Deleted element:\t\"%d\"\n",lq[front + 1]);
                    lq[front + 1 ] = 0;
                    front++;
                    printf("Linear Queue: ");
                    printarray(sizelq, front, rear, lq);
                }
                break;
                
            case 3:                                                                 //exit
                r=0;
                printf("Linear Queue: ");
                printarray(sizelq, front, rear, lq);
                break;
                
            default:                                                                //error, user re-enter
                printf("Error! Please re-enter\n");
                break;
        }
    }
    r = 1;
}

void circuilarqueue()                                                               //circular queue (cq) function
{
    printf("\n@@ circuilarqueue @@\n");
    
    int sizecq = 0, funccq, fround = 0, rround = 0;
    int front = 0, rear = 0;
    int insert = 0;
    
    printf("Enter the size:\n");                                                    //user enter the size of cq
    scanf("%d",&sizecq);
    int cq[sizecq];
    
    int i;
    for (i=0; i<sizecq; i++)                                                        //initialize cq array
    {
        cq[i] = 0;
    }
    
    printf(" 1.insertion\n 2.Deletion\n 3.Exit\n");
    
    int r = 1;
    while (r) {
        printf("Enter your choice:\t");                                               //user enter the function of cq
        scanf("%d",&funccq);
        
        switch (funccq)
        {
            case 1:                                                                 //cq insertion
                if (((rear == front - 1) && ((fround % 2) ^ (rround % 2))) || ((front == 0) && (rear == sizecq - 1)))
                {
                    printf("##Queue is already full!!!\n\n");
                    printf("Circular Queue: ");
                    printarray(sizecq, front, rear, cq);
                    break;
                }
                
                if(rear == sizecq - 1)                                             //makes array circular
                {
                    rear = 0;
                    rround ++;
                }
                else
                {
                    rear ++;
                }
                printf("Enter an element:\t");
                scanf("%d",&insert);
                cq[rear] = insert;
                //cq[rear] = rand()%10+1;
                printf("Circular Queue: ");
                printarray(sizecq, front, rear, cq);
                break;
                
            case 2:                                                                 //cq deletion
                if ((rear == front) && !((fround % 2) ^ (rround % 2)))
                {
                    printf("##Queue is already empty!!!\n\n");
                    printf("Circular Queue: ");
                    printarray(sizecq, front, rear, cq);
                    break;
                }
                if(front == sizecq - 1)                                             //makes array circular
                {
                    front = -1;
                    fround ++;
                }
                front ++;
                printf("Deleted element:\t\"%d\"\n",cq[front]);
                cq[front] = 0;
                printf("Circular Queue: ");
                printarray(sizecq, front, rear, cq);
                break;
                
            case 3:                                                                 //exit
                r=0;
                printf("Circular Queue: ");
                printarray(sizecq, front, rear, cq);
                putchar('\n');
                break;
                
            default:                                                                //error user re-enter
                printf("Error! Please re-enter\n");
                break;
        }
    }
    r = 1;
}


struct node                                                                         //define linked list node
{
    int num;
    struct node *next;
};

void printlinkedlist(int size, struct node *t, int front, int rear)                 //print circular queue in linked list
{
    struct node *e;
    int i;
    for (i=0; i < size; i++)
    {
        //printf("%p ",t);
        printf("[%d] ",t->num);
        //printf("%p\n",t->next);
        e = t->next;
        t = e;
    }
    printf("\nFront : %d\tRear : %d\n\n",front,rear);
}

void linkedlistcircularqueue()                                                      //linked list cq (llcq) function
{
    int sizellcq, count = 0;
    int front = 0, rear = 0;
    int funcllcq;
    int insert;
    
    printf("\n@@ linkedlist @@\n");
    
    struct node *thead, *ttail, *vhead, *vtail;

    vtail = malloc(sizeof(struct node));                                            //initialize nodes
    vtail->num = 0;
    vtail->next = NULL;
    ttail = vtail;
    thead = vtail;
    
    printf("Enter the size:");                                                      //user enter the size of llcq
    scanf("%d",&sizellcq);
    
    int i;
    for (i=0; i < (sizellcq - 1); i++)                                              //creat the queue in linked list
    {
        ttail = malloc(sizeof(struct node));
        ttail->num = 0;
        ttail->next = thead;
        thead = ttail;
    }
    ttail = vtail;
    ttail->next = thead;
    vtail = thead;
    vhead = thead;

    printf("Circular Queue: ");
    printlinkedlist(sizellcq, thead, front, rear);
    
    printf(" 1.insertion\n 2.Deletion\n 3.Exit\n");
    
    int r = 1;
    while (r)
    {
        printf("Enter your choice:");                                               //user enter the function of llcq
        scanf("%d",&funcllcq);
        
        switch (funcllcq)
        {
            case 1:                                                                 //llcq insert
                if (count == sizellcq - 1)
                {
                    printf("##Queue is already full!!!\n\n");
                    printf("Circular Queue: ");
                    printlinkedlist(sizellcq, thead, front, rear);
                    break;
                }
                printf("Enter an element:");
                scanf("%d",&insert);
                putchar('\n');
                if (rear == sizellcq - 1)
                {
                    rear = -1 ;
                }
                
                vhead = vhead->next;
                vhead->num = insert;
                //vhead->num = rand()%10+1;
                count ++;
                rear ++;
                printf("Circular Queue: ");
                printlinkedlist(sizellcq, thead, front, rear);
                //printf("\nrear: \n%d",rear);
                break;
                
            case 2:                                                                 //lqcc delete
                if (count == 0)
                {
                    printf("##Queue is already empty!!!\n\n");
                    printf("Circular Queue: ");
                    printlinkedlist(sizellcq, thead, front, rear);
                    break;
                }
                vtail = vtail->next;
                printf("Deleted element:\t\"%d\"\n", vtail->num);
                vtail->num = 0;
                if (front == sizellcq - 1)
                {
                    front = -1;
                }
                front++;
                count--;
                printf("Circular Queue: ");
                printlinkedlist(sizellcq, thead, front, rear);
                break;

            case 3:                                                                 //exit
                r=0;
                printf("Circular Queue: ");
                printlinkedlist(sizellcq, thead, front, rear);
                putchar('\n');
                break;
                
            default:                                                                //error user re-enter
                printf("Error! Please re-enter\n");
                break;
        }
    }
}
