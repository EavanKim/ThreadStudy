#include <pthread.h>
#include <stdio.h>

/*
        SIMPLE PTHREAD EXAMPLE
*/
void *foo(void *args) {
	int i;
	for(int i =0; i<100;i++) {
		printf("I'm FOO\n");
	}
	return NULL;
}

void *bar(void *args) {
	int i;
	for(int i =0; i<100;i++) {
		printf("I'm BAR\n");
	}
	return NULL;
}

int main() {
  pthread_t t1, t2;
  int i;

  pthread_create(&t1, NULL, foo, NULL);
  pthread_create(&t2, NULL, bar, NULL);

  for (int i = 0; i < 100; i++) {
		printf("i'm main\n");
  }

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}