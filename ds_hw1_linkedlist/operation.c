//operation.c
#include "operation.h"

void printnode(struct node *t)
{
    struct node *e;
    while (t)
    {
        printf("%d\t%p\n",t->number,t->next);
        e=t->next;
        t=e;
    }
}

struct node *addnode(struct node *t)
{
    struct node *i;
    i=malloc(sizeof(struct node));
    i->number=(rand()%1000);
    i->next=t;
    
    return i;
}

struct node *deletenode(struct node *q)
{
    int x;
    printf("enter the number want to delete:\n");
    scanf("%d",&x);
    putchar('\n');
    
    struct node *i,*j;
    i=q;
    j=q;
    
    while(j)
    {
        if(j->number == x)
        {
            if(i==j)
            {
                i=j->next;
                free(j);
                return i;
            }
            else
            {
                i->next=j->next;
                free (j);
                j=i->next;
                return q;
            }
        }
        i=j;
        j=i->next;
    }
    printf("can't find! retry!");
    return q;
}
