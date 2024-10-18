# pipex

## Descripción

Este proyecto va sobre el manejo de pipes en C, permitiendo la ejecución de múltiples comandos en la terminal de forma encadenada. La implementación replica el comportamiento del comando de shell `"< archivo1 comando1 | comando2 > archivo2"`.

## Tabla de Contenidos

| **Nombre**                         | **`pipex`**                               |
|-----------------------------------------------|-------------------------------------|
| **Archivos a entregar**                       | Makefile, *.h, *.c                 |
| **Makefile**                                  | NAME, all, clean, fclean, re       |
| **Argumentos**                                | archivo1 comando1 comando2 archivo2 |
| **Funciones autorizadas**                     | open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid , ft_printf|
| **Se permite usar libft**                     | Si                                 |

## Funcionalidades

- **Manejo de Archivos**: Lee de un archivo de entrada (`archivo1`) y escribe en un archivo de salida (`archivo2`).
- **Ejecución de Comandos**: Permite ejecutar dos o más comandos de shell con sus parámetros, utilizando pipes para conectar entradas y salidas.
- **Manejo de Errores**: Gestión minuciosa de errores para evitar caídas inesperadas del programa.
- **Múltiples Pipes**: Soporta la ejecución de múltiples comandos encadenados.
- **Here Documents**: Implementa la funcionalidad `here_doc` para redirigir texto desde la entrada estándar.

## Ejemplos de Uso

Ejecuta el programa de la siguiente manera:

```bash
./pipex archivo1 "comando1" "comando2" archivo2
```
Por ejemplo:
```bash
./pipex infile "ls -l" "wc -l" outfile
```
Esto será equivalente a:
```bash
<infile ls -l | wc -l >outfile
```
Otro ejmeplo:
```bash
$> ./pipex infile "grep a1" "wc -w" outfile
```
Deberá hacer lo mismo que:
```bash
“<infile grep a1 | wc -w >outfile”
```
## Requisitos

Tu proyecto debe cumplir los siguientes requisitos:

- Debes entregar un `Makefile` que compile tus archivos fuente. No debe hacer relink.
- Debes gestionar los errores minuciosamente. De ninguna forma tu programa debe salir de forma inesperada (segmentation fault, bus error, double free, y similares).
- Tu programa no debe tener fugas de memoria.
- Si tienes alguna duda, gestiona los errores como lo hace el comando de shell:
```bash
  <file1 cmd1 | cmd2 >file2
```
