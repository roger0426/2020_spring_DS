//main.c
#include "operation.h"

int main()
{
    struct node *A,*C;
    
    A=malloc(sizeof(struct node));
    A->number=0;
    A->next=NULL;
    C=A;
    
    printf("enter 1 : add new node\nenter 2 : delete node\nenter 0 : exit\n");
    
    int p=0;
    do
    {
        scanf("%d",&p);
        putchar('\n');
        
        switch(p)
        {
            case 0:    break;
                
            case 1:
            {
                C=addnode(C);
                printnode(C);
                break;
            }
                
            case 2:
            {
                C=deletenode(C);
                printnode(C);
                break;
            }
            
            default:
            {
                printf("error\n");
                break;
            }
        }
    }while(p);
    
    printf("__________________\n");
    printnode(C);
    
    //system ("PAUSE");
    return 0;
}
