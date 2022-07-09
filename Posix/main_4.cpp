#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/*
        SIMPLE PTHREAD MULTI ARGUMENT EXAMPLE
*/
typedef struct
{
	int n;
	int m;
} thread_args;

void *print_sequence(void *args) {
	thread_args *arg = (thread_args*)args;
	int n = arg->n;
	int m = arg->m;
	int i=0;

	for(i = n; i<m;i++)
		{
			printf("number : %d\n",i);
		}
	return NULL;
}

int main() {
  pthread_t t1;
  thread_args v = {10,30};
	
  pthread_create(&t1, NULL, print_sequence, &v);

	pthread_join(t1, NULL);

	return 0;
}