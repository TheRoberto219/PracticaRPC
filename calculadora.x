/* calculadora.x */
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
