# TP1 - Concurrentes
Trabajo práctico N°1 de Tecnicas de Programación Concurrente (75.09 - FIUBA)

### Instrucciones para ejecutar:

Parandose en el directorio raiz se pueden usar los siguientes comandos para distintas cosas:

- `make all `: Compila el programa y genera un ejecutable llamado `observatory`
  - Ejemplo de uso:
    `make all`

- `make run`: Compila el programa y lo ejecuta, tiene tres parametros posibles: CAMERAS, DIMENSIONS Y DEBUGFILE, este ultimo es opcional y se usa si se quiere loguear la salida a un archivo.
  - Ejemplo de uso:
    `make run CAMERAS=5 DIMENSIONS=800 DEBUGFILE=log.txt` 
- `make clean`: Limpia el directorio de imagenes y borra el ejecutable generado.

### Imagenes:

Las imagenes se guardan en el subdirectorio `img`, el cual se crea automaticamente si no existe, las imagenes generadas tienen extension `.ppm` por lo que si se desean visualizar se debe contar con algun visualizar que las soporte(el visor por defecto debería funcionar).

### Finalización del programa:

Para finalizar el programa basta con lanzar Ctrl + C, el programa atrapa la señal SIGINT y termina de manera ordenada, puede suceder que tarde un poco en terminar, esto se debe a que el programa primero termina de procesar y generar la imagen que estaba creando y luego finaliza.

