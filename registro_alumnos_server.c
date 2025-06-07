#include "registro_alumnos.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_REGISTROS 100

static alumno registros[MAX_REGISTROS];
static int total_registros = 0;

bool_t *registrar_alumno_1_svc(alumno *argp, struct svc_req *rqstp) {
    static bool_t result;
    
    if(total_registros < MAX_REGISTROS) {
        registros[total_registros] = *argp;
        total_registros++;
        result = TRUE;
        printf("Alumno registrado: %d %s %s\n", argp->id, argp->nombre, argp->apellido);
    } else {
        result = FALSE;
    }
    
    return &result;
}

resultado_busqueda *buscar_alumno_1_svc(busqueda *argp, struct svc_req *rqstp) {
    static resultado_busqueda result;
    int i, count = 0;
    
    // Primera pasada: contar coincidencias
    for(i = 0; i < total_registros; i++) {
        if((argp->id == -1 || registros[i].id == argp->id) &&
           (argp->nombre == NULL || strstr(registros[i].nombre, argp->nombre)) &&
           (argp->apellido == NULL || strstr(registros[i].apellido, argp->apellido)) &&
           (argp->curso == NULL || strstr(registros[i].curso, argp->curso))) {
            count++;
        }
    }
    
    // Asignar memoria para los resultados
    result.cantidad = count;
    result.datos.datos_val = (alumno *)malloc(count * sizeof(alumno));
    result.datos.datos_len = count;
    
    // Segunda pasada: llenar resultados
    count = 0;
    for(i = 0; i < total_registros; i++) {
        if((argp->id == -1 || registros[i].id == argp->id) &&
           (argp->nombre == NULL || strstr(registros[i].nombre, argp->nombre)) &&
           (argp->apellido == NULL || strstr(registros[i].apellido, argp->apellido)) &&
           (argp->curso == NULL || strstr(registros[i].curso, argp->curso))) {
            result.datos.datos_val[count++] = registros[i];
        }
    }
    
    return &result;
}

bool_t *actualizar_alumno_1_svc(alumno *argp, struct svc_req *rqstp) {
    static bool_t result = FALSE;
    int i;
    
    for(i = 0; i < total_registros; i++) {
        if(registros[i].id == argp->id) {
            registros[i] = *argp;
            result = TRUE;
            printf("Alumno actualizado: %d\n", argp->id);
            break;
        }
    }
    
    return &result;
}

bool_t *eliminar_alumno_1_svc(int *argp, struct svc_req *rqstp) {
    static bool_t result = FALSE;
    int i, j;
    
    for(i = 0; i < total_registros; i++) {
        if(registros[i].id == *argp) {
            for(j = i; j < total_registros - 1; j++) {
                registros[j] = registros[j+1];
            }
            total_registros--;
            result = TRUE;
            printf("Alumno eliminado: %d\n", *argp);
            break;
        }
    }
    
    return &result;
}
