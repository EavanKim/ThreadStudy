#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
void* thread_routine(void *arg){
        pthread_t tid;
 
        tid=pthread_self();
 
        int i=0;
        printf("\ttid:%x\n",(unsigned int)tid);
        while(i<10){
                printf("\tnew thread:%d\n",i);
                i++;
                sleep(1);
        }
}
 
int main(){
        pthread_t thread;
 
        pthread_create(&thread,NULL,thread_routine, NULL);
 
        int i=0;
        printf("tid:%x\n",(unsigned int)pthread_self());
        while(i<5){
                printf("main:%d\n",i);
                i++;
                sleep(1);
        }
}