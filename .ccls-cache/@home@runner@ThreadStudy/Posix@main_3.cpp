#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/*
        SIMPLE PTHREAD ARGUMENT EXAMPLE
*/
void *print_sequence(void *args) {
	int i;
	int n = *(int *) args;
	for(int i =0; i<n;i++) {
		printf("args: %d\n",i);
	}
	return NULL;
}

int main() {
  pthread_t t1;
  int n = 10;
	int *p = &n;
	
  pthread_create(&t1, NULL, print_sequence, p);

	pthread_join(t1, NULL);

	return 0;
}