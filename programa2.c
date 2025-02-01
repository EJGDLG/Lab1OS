#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <archivo_origen> <archivo_destino>\n", argv[0]);
        return 1;
    }

    int origen = open(argv[1], O_RDONLY);
    if (origen < 0) {
        perror("Error al abrir archivo de origen");
        return 1;
    }

    int destino = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destino < 0) {
        perror("Error al abrir archivo de destino");
        close(origen);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesLeidos;

    while ((bytesLeidos = read(origen, buffer, BUFFER_SIZE)) > 0) {
        write(destino, buffer, bytesLeidos);
    }

    close(origen);
    close(destino);

    printf("Archivo copiado con éxito.\n");
    return 0;
}