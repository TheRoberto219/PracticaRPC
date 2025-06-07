/* calculadora.x - Definición de la interfaz para la calculadora RPC */
/* Versión mejorada con todos los parámetros en una sola estructura */

struct operacion {
    float a;
    float b;
    char operador;
};

program CALCULADORA_PROG {
    version CALCULADORA_VERS {
        float calcular(operacion) = 1;
    } = 1;
} = 0x31234567;
