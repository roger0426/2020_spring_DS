//
//  operation.h
//  struct 新增刪除-2
//
//  Created by Chang Chung Che on 2018/12/28.
//  Copyright © 2018 Chang Chung Che. All rights reserved.
//

//operation.h
#ifndef operation_h
#define operation_h

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int number;
    struct node *next;
};

void printnode(struct node *t);
struct node *addnode(struct node *t);
struct node *deletenode(struct node *q);

#endif /* operation_h */

