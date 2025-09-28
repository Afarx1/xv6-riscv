# INFORME TAREA 1

## Funcionamiento de llamadas al sistema

### getppid(void)
Retorna la ID del proceso padre del proceso que lo invoca.
### getancestor(int)
Retorna la ID del proceso indicado en el parámetro.

- getancestor(0): retorna el mismo proceso.
- getancestor(1): retorna el padre.
- getancestor(2): retorna el abuelo.
- Si el parámetro no es válido, retorna -1.

## Modificaciones realizadas
- En /kernel/sysproc.c se agregaron las funcionalidades de las llamadas al sistema getppid(void) y getancestor(int).
- En /kernel/syscall.h se definieron los números de syscall para las nuevas llamadas al sistema.
- En /kernel/syscall.c se declararon y registraron las nuevas llamadas.

- En /user/user.h se agregaron las nuevas llamadas.
- En /user/usys.pl se agregaron las nuevas llamadas.
- Se creó yosoytupadre.c en /user.
- Se agregó yosoytupadre.c a MAKEFILE.

## Dificultades y resolución
1.
```kernel/sysproc.c: In function ‘sys_getancestor’:
kernel/sysproc.c:115:6: error: void value not ignored as it ought to be
  115 |   if(argint(0, &n) < 0)
      |      ^~~~~
make: *** [<builtin>: kernel/sysproc.o] Error 1
```
Resolución: En xv6-riscv, la función argint no retorna nada (void), sino que escribe directamente en la variable. Por lo tanto, el compilador retorna “void value not ignored as it ought to be”.

2.
```$ yosoytupadre
Mi PID: 3
3 yosoytupadre: unknown sys call 23
getancestor(0) = -1
3 yosoytupadre: unknown sys call 23
getancestor(1) = -1
3 yosoytupadre: unknown sys call 23
getancestor(2) = -1
3 yosoytupadre: unknown sys call 23
getancestor(3) = -1
```
Resolución: Se resolvió tras un reinicio de dispositivo y la adición de la siguiente línea: ``extern struct proc *initproc;`` en /kernel/sysproc.c
