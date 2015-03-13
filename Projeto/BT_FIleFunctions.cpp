#include <stdio.h>
#include <stdlib.h>
#include "bt.h"

int insert(FILE **BTidx, int root, int key, int upKey) {
    if (root == -1) {
        upKey = key;
        return 1;
    } else {
        PAGE *newPage = (PAGE*) malloc (PAGESIZE);
        fseek(*BTidx, root, SEEK_SET);
        fread(newPage, PAGESIZE, 1, *BTidx);
        
                
    }
}
