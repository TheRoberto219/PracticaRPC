#include "registro_alumnos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrar_alumno(alumno a) {
    printf("ID: %d\n", a.id);
    printf("Nombre: %s\n", a.nombre);
    printf("Apellido: %s\n", a.apellido);
    printf("Edad: %d\n", a.edad);
    printf("Curso: %s\n", a.curso);
    printf("-------------------\n");
}

void registrar(CLIENT *clnt) {
    alumno a;
    bool_t *result;
    
    printf("ID: "); scanf("%d", &a.id);
    printf("Nombre: "); scanf("%s", a.nombre);
    printf("Apellido: "); scanf("%s", a.apellido);
    printf("Edad: "); scanf("%d", &a.edad);
    printf("Curso: "); scanf("%s", a.curso);
    
    result = registrar_alumno_1(&a, clnt);
    if(result == NULL) {
        clnt_perror(clnt, "call failed");
        return;
    }
    
    printf("Registro %s\n", *result ? "exitoso" : "fallido");
}

void buscar(CLIENT *clnt) {
    busqueda b;
    resultado_busqueda *result;
    
    memset(&b, 0, sizeof(b));
    b.id = -1; // Valor por defecto
    
    printf("Buscar por:\n");
    printf("1. ID\n2. Nombre\n3. Apellido\n4. Curso\n0. Terminar\n");
    
    int opcion;
    do {
        printf("Opción: "); scanf("%d", &opcion);
        switch(opcion) {
            case 1: printf("ID: "); scanf("%d", &b.id); break;
            case 2: printf("Nombre: "); scanf("%s", b.nombre); break;
            case 3: printf("Apellido: "); scanf("%s", b.apellido); break;
            case 4: printf("Curso: "); scanf("%s", b.curso); break;
        }
    } while(opcion != 0);
    
    result = buscar_alumno_1(&b, clnt);
    if(result == NULL) {
        clnt_perror(clnt, "call failed");
        return;
    }
    
    printf("\nResultados encontrados: %d\n", result->cantidad);
    for(int i = 0; i < result->cantidad; i++) {
        mostrar_alumno(result->datos.datos_val[i]);
    }
}

void actualizar(CLIENT *clnt) {
    alumno a;
    bool_t *result;
    
    printf("ID del alumno a actualizar: "); scanf("%d", &a.id);
    printf("Nuevo nombre: "); scanf("%s", a.nombre);
    printf("Nuevo apellido: "); scanf("%s", a.apellido);
    printf("Nueva edad: "); scanf("%d", &a.edad);
    printf("Nuevo curso: "); scanf("%s", a.curso);
    
    result = actualizar_alumno_1(&a, clnt);
    if(result == NULL) {
        clnt_perror(clnt, "call failed");
        return;
    }
    
    printf("Actualización %s\n", *result ? "exitosa" : "fallida");
}

void eliminar(CLIENT *clnt) {
    int id;
    bool_t *result;
    
    printf("ID del alumno a eliminar: "); scanf("%d", &id);
    
    result = eliminar_alumno_1(&id, clnt);
    if(result == NULL) {
        clnt_perror(clnt, "call failed");
        return;
    }
    
    printf("Eliminación %s\n", *result ? "exitosa" : "fallida");
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    char *host;
    int opcion;
    
    if(argc != 2) {
        printf("Uso: %s servidor\n", argv[0]);
        exit(1);
    }
    
    host = argv[1];
    clnt = clnt_create(host, REGISTRO_ALUMNOS, REGISTRO_ALUMNOS_V1, "tcp");
    if(clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }
    
    do {
        printf("\nSistema de Registro de Alumnos\n");
        printf("1. Registrar alumno\n");
        printf("2. Buscar alumno\n");
        printf("3. Actualizar alumno\n");
        printf("4. Eliminar alumno\n");
        printf("0. Salir\n");
        printf("Opción: "); scanf("%d", &opcion);
        
        switch(opcion) {
            case 1: registrar(clnt); break;
            case 2: buscar(clnt); break;
            case 3: actualizar(clnt); break;
            case 4: eliminar(clnt); break;
        }
    } while(opcion != 0);
    
    clnt_destroy(clnt);
    return 0;
}
