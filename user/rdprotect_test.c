#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  char *addr = sbrk(0);
  if(sbrk(4096) < 0){
    printf("sbrk falló\n");
    exit(1);
  }

  addr[0] = 'Z';
  if (mrdprotect(addr, 1) < 0) {
    printf("mrdprotect falló\n");
    exit(1);
  }

  // Escritura aún permitida
  addr[0] = 'A';

  // Intento de lectura: debería fallar con un trap (page-fault) o similar.
  // Si el kernel aborta el proceso al acceder sin permiso, no esperamos que
  // esta printf aparezca.
  char c = addr[0];
  printf("Valor leído: %c (esto NO debería imprimirse)\n", c);

  if (munrdprotect(addr, 1) < 0) {
    printf("munrdprotect falló\n");
    exit(1);
  }

  printf("Protección revertida correctamente.\n");
  exit(0);
}