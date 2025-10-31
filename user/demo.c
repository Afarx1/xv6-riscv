// demo para mostrar tarea 2

// user/demo.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  const int N = 10;
  int i;
  for (i = 0; i < N; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("fork failed\n");
      exit(1);
    }
    if (pid == 0) {
      // child
      int tickets = 50 * (i + 1); // 50,100,150,...
      settickets(tickets);
      // run work for a while
      for (long j = 0; j < 100000000L; j++) {
        // little busy work to consume CPU and allow scheduler to count slices
        if (j % 10000000L == 0) {
          // occasional print—comment out to reduce noise
          // printf("child %d working j=%ld\n", getpid(), j);
        }
      }
      // exit child
      exit(0);
    }
    // parent continues to fork next child
  }

  // parent: wait for children to finish
  for (i = 0; i < N; i++) {
    wait(0);
  }

  printf("demo: all children finished\n");
  exit(0);
}
