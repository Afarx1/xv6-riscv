# Tarea 3 - Protección de Lectura en XV6
**Rama correspondiente:** 'envi_gaca_t3'

En esta tarea se modificó xv6 para implementar un mecanismo de **protección de memoria** que permite marcar regiones de memoria como "solo escritura", eliminando el permiso de lectura mientras se mantiene el permiso de escritura.

Este tipo de protección es útil en la industria criptográfica para manejar claves secretas y datos sensibles, evitando que el sistema o posibles atacantes puedan leer estos datos, pero permitiendo su escritura.

El mecanismo implementado modifica directamente los bits de las entradas de la tabla de páginas (PTE) para controlar los permisos de acceso a nivel de hardware.

## Explicación de las modificaciones realizadas

**syscall.h:** Se añadieron dos nuevas constantes `SYS_mrdprotect` con el número 25 y `SYS_munrdprotect` con el número 26. Esto permite que el kernel identifique estas llamadas al sistema cuando son invocadas por programas de usuario.

**syscall.c:** Se crearon las declaraciones externas `sys_mrdprotect(void)` y `sys_munrdprotect(void)`, y se registraron ambas syscalls dentro de la tabla `syscalls[]` para relacionar los números de llamadas con las funciones del kernel. Esto permite que ambas funciones se ejecuten correctamente al invocar ecall con los números 25 y 26 respectivamente.

**sysproc.c:** Se implementaron las funciones `sys_mrdprotect()` y `sys_munrdprotect()` que actúan como wrappers de las llamadas al sistema. Estas funciones obtienen los argumentos del espacio de usuario (dirección y longitud) y llaman a las funciones principales de protección.

Además, se implementaron las funciones principales:
- **`mrdprotect(uint64 addr, int len)`**: Recorre la tabla de páginas del proceso actual y limpia el bit `PTE_R` (permiso de lectura) en cada PTE del rango especificado, manteniendo los demás bits intactos (escritura, ejecución, usuario, válido).
- **`munrdprotect(uint64 addr, int len)`**: Restaura el bit `PTE_R` en las páginas previamente protegidas, permitiendo nuevamente la lectura.

Ambas funciones realizan validaciones exhaustivas: verifican la alineación de la dirección a página, que `len` sea positivo, que las direcciones pertenezcan al espacio de usuario, y que todas las páginas del rango estén mapeadas y sean válidas.

**defs.h:** Se añadieron los prototipos de las funciones `int mrdprotect(uint64, int)` y `int munrdprotect(uint64, int)` en la sección correspondiente a funciones de memoria virtual, permitiendo que estas funciones sean accesibles desde otros archivos del kernel.

**user.h:** Se añadieron los prototipos de las funciones de usuario `int mrdprotect(void*, int)` y `int munrdprotect(void*, int)` para exponer las llamadas al sistema a los programas de usuario.

**usys.pl:** Se añadieron las líneas `entry("mrdprotect")` y `entry("munrdprotect")`. Esto genera automáticamente los stubs en lenguaje ensamblador que permiten al usuario invocar estas syscalls desde el espacio de usuario.

**rdprotect_test.c:** Este programa se creó para probar el funcionamiento del mecanismo de protección. El test reserva una página de memoria, escribe un valor, aplica la protección contra lectura con `mrdprotect()`, verifica que la escritura aún funciona, e intenta leer (lo cual debería provocar un page fault). Finalmente, restaura los permisos con `munrdprotect()`. Se puede ejecutar llamando a `rdprotect_test` dentro de xv6.

**Makefile:** Se agregó `$U/_rdprotect_test\` a la lista de programas de usuario (`UPROGS`) para que el programa de prueba sea compilado y esté disponible en el sistema.

## Resultado esperado

Al ejecutar `rdprotect_test`, el programa debe:
1. Proteger exitosamente la página con `mrdprotect()`
2. Permitir la escritura en la página protegida
3. Generar un page fault (error `scause 0xf`) al intentar leer la página protegida
4. El mensaje "esto NO debería imprimirse" no debe aparecer, confirmando que la protección funcionó

El page fault es el comportamiento esperado y demuestra que la protección de lectura está funcionando correctamente.