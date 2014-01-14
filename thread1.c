#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include  <pthread.h>

void *thread_function(void *arg);

char message[] = "hello world";

int main(){
  int res;
  pthread_t a_thread;
  void *thread_res;

  res = pthread_create(&a_thread, NULL, thread_function, (void *)message);

  if (res != 0){
    perror("Thread creation failed.\n");
    exit(EXIT_FAILURE);
  }
  printf("waiting for the thread to fininsh...\n");
  res = pthread_join(a_thread, &thread_res);

  if (res != 0){
    perror("Thread join failed.\n");
    exit(EXIT_FAILURE);
  }
  
  printf("Thread joined, it returned %s\n", (char*)thread_res);
  printf("Message is now %s\n", message);
  exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){
  printf("thread function running, argument is %s\n", (char*) arg);
  sleep(3);
  strcpy(message, "Bye");
  pthread_exit("Thanks\n");
}
