#/usr/local/bin/tcc -run -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *hello(void *param)
{
  int *id;
  
  id = (int*)param;
  printf("\t HELLO WORLD FROM THREAD #%d", *id);
  
  pthread_exit(0);
  return 0;
}

int join(int inloop)
{
  pthread_attr_t attr;
  pthread_t threads[NUM_THREADS];
  int rc, t, param[NUM_THREADS];

  pthread_attr_init(&attr);
  
  for(t = 0; t < NUM_THREADS; t++) {
    printf("RUTINE #%d\n", t);
    param[t] = t;

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    rc = pthread_create(&threads[t], &attr, hello, (void*)&param[t]);

    if (rc) {
      printf("ERROR %d\n", rc);
      return -1;
    }
    
    if (inloop) pthread_join(threads[t], 0);
  }

  if (!inloop) {
    for(t = 0; t < NUM_THREADS; t++) {
      pthread_join(threads[t], 0);
    }
  }
  
  return 0;
}

int main(int arg, char *argv[])
{
  int c, inloop;
  
  printf("[1] JOIN IN LOOP");
  printf("[2] JOIN OUT LOOP");
  while ((c = getchar()) != '\n');

    switch (c) {
        case '1':
            inloop = 1;
            break;
        case '2':
            inloop = 0;
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    join(inloop);

    return 0;
}
