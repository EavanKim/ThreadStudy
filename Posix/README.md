## POSIX 스레드

**POSIX 스레드(POSIX Threads, 약어: PThread, Posix Threads for threads)**는 병렬적으로 작동하는 소프트웨어의 작성을 위해서 제공되는 표준 API다.

Pthread는 모든 유닉스 계열 POSIX 시스템에서, 일반적으로 이용되는 라이브러리이다. 유닉스 계열 운영 체제라 하면 리눅스, 솔라리스 등이 포함된다. Unix 시스템과는 다른 길을 걷고 있는 Windows 역시 여러가지 이유로 Pthread를 지원한다. 예를 들어 pthread-w32를 이용하면 윈도 상에서도 Pthread API의 subset 함수를 이용할 수 있다. pthread-w32는 redhat.com에서 얻을 수 있다. 

## 설명

Pthread는 C 프로그래밍 언어에서 사용할 수 있는 함수들의 모음으로 제공된다. Pthread 라이브러리에서 제공하는 함수는 pthread.h를 포함하여 호출할 수 있다.

자료형
- pthread_ t : 스레드 핸들러
- pthread_attr_t : 스레드 성질
Pthread는 스레드 제어를 위한 다양한 함수를 제공한다. 제공되는 함수의 목록은 Pthread API Reference에서 확인할 수 있다.

## 컴파일 옵션

Pthread 용 라이브러리를 링크해줘야 하기 때문에, -pthread 로 링크 옵션을 주어, 컴파일을 해주어야 한다.
'''
// simple 예제
gcc main.cpp -pthread -o main
'''


## 함수 설명
1. pthread_create(): thread 를 만들어주는 함수.

''' 
#include <pthread.h>

int pthread_create(pthread_t *restrict thread,
									const pthread_attr_t *restrict attr,
									void *(*start_routine)(void *),
									void *restrict arg);
''' 

- pthread_t *thread
	- 함수를 실행할 thread 변수의 포인터
  - pthread_t 변수가 아닌 그 포인터를 넘겨준다.
- const pthread_attr_t *restrict attr
	- thread의 실행권한을 의미 / 보통 NULL 을 넣는다.
- void *(*start_routine)(void *)
	- 함수의 포인터를 대입
	- void* 를 인자로 받고, void* 를 return 하는 함수.
- void *restrict arg
	- 함수의 인자 모음.


	
- Return Value
	- 성공했을 시, 0 실패시 Error Number 리턴.


2. Pthread_join()
3. '''
4. #include <pthread.h>
5. 
6. int pthread_join(pthread_t thread, void **value_ptr);
7. '''
- pthread_t
	- 실행 종료를 기다릴 pthread 핸들값.
- void **value_ptr
	- 실행이 끝난 함수의 반환값이 저장되는 포인터


- Return Value
	- 성공했을 시, 0 실패시 Error Number 리턴.