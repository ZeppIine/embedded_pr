#include <stdio.h>
#include "pr1_common.h"

void timesTable(int x){
    for(int i = 1; i < 10; i++){
        printf("%d X %d = %d\n", i, x, x * i);
    }
}