#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main(void) {
  int pid = getpid();
  printf("Mi PID: %d\n", pid);

  for (int i = 0; i < 4; i++) {
    int anc = getancestor(i);
    printf("getancestor(%d) = %d\n", i, anc);
  }

  exit(0);
}