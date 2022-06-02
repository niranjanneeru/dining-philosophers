#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "network.h"
# include <semaphore.h>

sem_t mutex;
#define MAX 5

int ports[] = {8001, 8002, 8003, 8004, 8005};
int pid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int compute_left_fork(int id){
    return id;
}

int compute_right_fork(int id){
    return (id+1)%MAX;
}

void test(int id, int * state, int left, int right){
    if(*state != HUNGRY) return;
    int res_left  = acquire_fork(id,left,ports[left]);
    if(res_left != GRANTED) return;
    int res_right = acquire_fork(id,right, ports[right]);
    if(res_right != GRANTED){
        release_fork(id,left,ports[left]);
        return;
    }
    *state = EATING;
    display(id,*state);
    sleep(rand()%3+2);
}

void take_fork(int id, int * state, int left, int right){
    if(*state != HUNGRY){
        *state = HUNGRY;
        display(id,*state);
    }
    sem_wait(&mutex);
    test(id,state,left,right);
    sem_post(&mutex);
    sleep(rand()%3+2);
}

void put_fork(int id, int * state, int left, int right){
    sem_wait(&mutex);
    if(*state != THINKING){
        *state=THINKING;
        display(id,*state);
    }
    release_fork(id,left,ports[left]);
    release_fork(id,right,ports[right]);
    sleep(rand()%3+2);
    sem_post(&mutex);
}

void philosopher_start(int id){
    int state = THINKING;
    display(id,state);
    int left = compute_left_fork(id);
    int right = compute_right_fork(id);
    while(TRUE){
        take_fork(id, &state, left, right);
        put_fork(id, &state, left, right);
    }
}

void fork_start(int id){
    printf("Fork %d\n",id);
    int fork_id = fork_network_call(id, ports[id]);
    int state = AVAILABLE;
    int command, philosopher;
    while (TRUE){
        // int clientfd = accept(fork_id, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        int clientfd = accept(fork_id, NULL, NULL);
        if (clientfd < 0) {
		    perror("Accept Failed");
		    exit(EXIT_FAILURE);
	    }
        read(clientfd, &command, sizeof(command));
        read(clientfd, &philosopher, sizeof(philosopher));
        if(command == REQUEST){
            if(state == AVAILABLE){
                state = OCCUPIED;
                command = GRANTED;
                write(clientfd, &command, sizeof(command));
            }else{
                command = REJECTED;
                write(clientfd, &command, sizeof(command));
            }
        }else if(command == RELEASE){
            state = AVAILABLE;
            command = GRANTED;
            write(clientfd, &command, sizeof(command));
        }
    }
}

int main() {
    sem_init(&mutex, 1, 1);
    if(pid[0]=fork()==0){
        fork_start(0);
        exit(EXIT_SUCCESS);
    }else if(pid[1]=fork()==0){
        fork_start(1);
        exit(EXIT_SUCCESS);
    }else if(pid[2]=fork()==0){
        fork_start(2);
        exit(EXIT_SUCCESS);
    }else if(pid[3]=fork()==0){
        fork_start(3);
        exit(EXIT_SUCCESS);
    }else if(pid[4]=fork()==0){
        fork_start(4);
        exit(EXIT_SUCCESS);
    }

    sleep(2);

    if(pid[5]=fork()==0){
        philosopher_start(0);
        exit(EXIT_SUCCESS);
    }else if(pid[6]=fork()==0){
        philosopher_start(1);
        exit(EXIT_SUCCESS);
    }else if(pid[7]=fork()==0){
        philosopher_start(2);
        exit(EXIT_SUCCESS);
    }else if(pid[8]=fork()==0){
        philosopher_start(3);
        exit(EXIT_SUCCESS);
    }else if(pid[9]=fork()==0){
        philosopher_start(4);
        exit(EXIT_SUCCESS);
    }
    sleep(60);
    for(int i = 0; i< 10;i++){
        kill(pid[i],SIGQUIT);
    }
    wait(NULL);
    return 0;
}
