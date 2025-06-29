/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculadora_prog_1(char *host, float num1, float num2, char operador) {
    CLIENT *clnt;
    float *result;
    operacion op;
    
    // Configurar la estructura de operación
    op.a = num1;
    op.b = num2;
    op.operador = operador;
    
    // Crear el cliente RPC
    clnt = clnt_create(host, CALCULADORA_PROG, CALCULADORA_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }
    
    // Llamar al procedimiento remoto
    result = calcular_1(&op, clnt);
    if (result == NULL) {
        clnt_perror(clnt, "call failed");
        exit(1);
    }
    
    // Mostrar el resultado
    printf("Resultado: %.2f %c %.2f = %.2f\n", num1, operador, num2, *result);
    
    // Liberar recursos
    clnt_destroy(clnt);
}

int main(int argc, char *argv[]) {
    char *host;
    float num1, num2;
    char operador;
    
    // Verificar argumentos
    if (argc != 5) {
        printf("Uso: %s servidor num1 num2 operador\n", argv[0]);
        printf("Operadores permitidos: +, -, *, /\n");
        exit(1);
    }
    
    // Obtener argumentos
    host = argv[1];
    num1 = atof(argv[2]);
    num2 = atof(argv[3]);
    operador = argv[4][0]; // Tomar solo el primer carácter
    
    // Validar operador
    if (strchr("+-*/", operador) == NULL) {
        printf("Error: Operador no válido. Use +, -, * o /\n");
        exit(1);
    }
    
    // Verificar división por cero
    if (operador == '/' && num2 == 0.0) {
        printf("Error: No se puede dividir por cero\n");
        exit(1);
    }
    
    // Llamar a la función del cliente
    calculadora_prog_1(host, num1, num2, operador);
    
    return 0;
}
