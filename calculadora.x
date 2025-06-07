/* calculadora.x - Definición de la interfaz para la calculadora RPC */

const MAX_OP = 1;

struct operandos {
    double a;
    double b;
};

program CALCULADORA {
    version CALCULADORA_V1 {
        double calcular(operandos, char) = 1;
    } = 1;
} = 0x20000001;
