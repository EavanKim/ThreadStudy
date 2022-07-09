#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>

/*
	SIMPLE HELLOWORLD FOR PTHREAD	
*/
void* HelloWorld(void* args)
{
  int i;
  std::cout << "Hello, World !" << std::endl;
  return NULL;
}

int main(int argc, char** argv)
{
  pthread_t t1;

  pthread_create(&t1, NULL, HelloWorld, NULL);
  pthread_join(t1, NULL);

  return 0;
}