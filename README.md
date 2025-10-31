# Tarea 2 - Scheduler con Lottery Scheduling
**Rama correspondiente:** 'envi_gaca_t2'

En esta tarea se modificó  xv6 para implementar un nuevo algoritmo de planificación basado en **Lottery Scheduling**, reemplazando la lógica original del *scheduler* de tipo round-robin.

Cada proceso en el sistema posee una cantidad de “tickets” que determinan su probabilidad de ser elegido para ejecutar.  
De esta forma, los procesos con más tickets tienen mayor probabilidad de recibir CPU.

# Explicación de las modificaciones realizadas

**proc.h:** Se añadieron dos nuevos campos dentro de la estructura struct proc (int tickets y int run_slices) debido a que son necesarios para implementar el algoritmo de Lottery Scheduling. tickets representa la cantidad de tickets que posee cada proceso y run_slices permite llevar un conteo estadístico de cuántas veces el proceso fue seleccionado por el scheduler.

**proc.c:** Se agregaron las siguientes lineas

p->tickets = 100;      
if (p->tickets < 1)
  p->tickets = 1;
p->run_slices = 0;

Esto asegura que todo nuevo proceso creado posea incialmente una cantidad válida de tickets (pr defecto es 100) y que su contador comience en 0. Esto es para que el scheduler tenga valores definidos cuando el proceso pasa a RUNNABLE.

También se realizo una modificacíon del scheduler (), en el cual se reemplazó el planificador raound-robin por una version basada en Lottery Scheduling para la tarea.

Además, se implementó una función auxiliar para generar números pseudoaleatorios usando LCG. Esto reemplaza la política deterministica del planificador por una probabilística con el objetivo de mantener al equidad entre procesos

**sysproc.c:** Se añadio una nueva llamada al sistema (sys_settickets), lo cual permite modificar la cantidad de tickets en los procesos en el espacio de user.

**syscall.h:** Se añadio la constante SYS_tickets con el número 24, esto permite que el kernel identifique la llamada cuando es utilizada por el usuario.

**syscall.c:** Se creo una nueva declaración externa (sys_settickets(void)), y se registro la nueva syscall dentro de la tabla syscalls[] para relacionar los números de llamadas con las funciones del kernel. Esto permite que sys_settickets() se ejecute correctamente al ejectuar ecall con el número 24

**user.h:** Aquí se añadió el prototipo de la función de usuario (int settickets(int)) para exponer la llamada al sistema settickets a los programas de usuario para que pueda ser utilizada

**usys.pl:** Se añadio una linea (entry("settickets")). Esto es lo que le permite al usuario invocar la syscall.

**demo.c:** Este programa se creo para poder probar el funcionamiento del nuevo scheduler. se puede ejecutar llamando a demo dentro de xv6.

# Posibles problemas de este tipo de Scheduler

**Incertidumbre en la asignación de CPU:** Dado que la selección del proceso es aleatoria (aunque ponderada por los tickets), no existe garantía de que cada proceso reciba la fracción esperada de CPU en intervalos cortos

**Starvation:** Un proceso con pocos tickets podría no ser elegido durante mucho tiempo si tiene mala suerte en la lotería, especialmente si otros procesos tienen una cantidad considerablemente mayor de tickets. Cabe mencionar que esto solo sería un problema a corto plazo, ya que al largo plazo el sistema tiende a equilibrarse.

**Complejidad de implementación:** Comparado con Round Robin, Lottery Scheduling requiere manejar generación de números aleatorios, mantenimiento de la suma total de tickets y actualización dinámica de tickets si la prioridad de los procesos varía.

**Inequidad al bloquear procesos:** Si un proceso bloquea frecuentemente, puede desperdiciar sus tickets, afectando a la equidad de prioridad, sin embargo, se pueden implementar mecanismos adicionales como redistribución de tickets para compensar.