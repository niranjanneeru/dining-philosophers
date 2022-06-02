#include <stdio.h>
#include "const.h"

void display(int id, int state){
    if(state == EATING){
        printf("Philosopher %d is Eating\n",id);
    }else if(state == THINKING){
        printf("Philosopher %d is Thinking\n",id);
    }else if(state == HUNGRY){
        printf("Philosopher %d is Hungry\n",id);
    }
}