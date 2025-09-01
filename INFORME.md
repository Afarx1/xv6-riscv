# INFORME.MD

## Instalación de xv6

1. Clonamos el repositorio desde GitHub: https://github.com/Afarx1/xv6-riscv.git

2. Instalamos dependencias necesarias: sudo apt install make/qemu-system-misc/bc/gcc-riscv62-linux-gnu

3. Verificamos la versión de QEMU (necesaria >= 7.2)

4. Se ejecutó 'make qemu' y el sistema xv6 se inició correctamente

## Problemas encontrados

- Error: `fatal: destination path 'xv6-riscv' already exists`
- Fix: eliminar o acceder al directorio existente

- Error: `ERROR: Need qemu version >= 7.2`
- Fix: ctualizar Ubuntu y reinstalar QEMU manualmente

- Error: `make: gcc: No such file or directory`
- Fix:  instalar `build-essential`

## Confirmación

xv6 está funcionando correctamente. Se puede compilar y ejecutar con `make qemu`.

