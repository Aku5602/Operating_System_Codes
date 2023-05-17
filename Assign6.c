//Threads and mutexlock and reader writer.
//pthread_join(th[i].t,NULL), pthread_create(&th[i].t, NULL, read, (void *)&th[i]).
//pthread_mutex-t r_mutex, rw_mutex;  r=>readcount lock,rw=>balance lock
//pthread_mutex_init(&), pthread_mutex_lock(), pthread_mutex_unlock();

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t r_mutex;
pthread_mutex_t rw_mutex;

int readcount = 0;
int balance = 30;

struct threads {
  int pid;
  pthread_t t;
  int cost;
};

void * write(void * args) {
  struct threads *th = (struct threads *)args;
  pthread_mutex_lock(&rw_mutex);
  balance = balance + th->cost;
  printf("Balance = %d",balance);
  pthread_mutex_unlock(&rw_mutex);
  return NULL;
}

void * read(void * args) {
  struct threads *th = (struct threads *)args;
  pthread_mutex_lock(&rw_mutex);
  balance = balance + th->cost;
  printf("Balance = %d",balance);
  pthread_mutex_unlock(&rw_mutex);
  return NULL;
}



int main() {

  pthread_mutex_init(&r_mutex,NULL);
  pthread_mutex_init(&rw_mutex,NULL);
  //Create thread
  struct threads th;
  th.pid = 1;
  th.cost = 20;
  pthread_create(&th.t,NULL,write,(void *)&th);
  
  pthread_join(th.t,NULL);
  
  
  return 0;
}

