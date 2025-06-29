/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */


#include "calculadora.h"
#include <math.h>

float *calcular_1_svc(operacion *argp, struct svc_req *rqstp) {
    static float result;
    
    switch(argp->operador) {
        case '+':
            result = argp->a + argp->b;
            break;
        case '-':
            result = argp->a - argp->b;
            break;
        case '*':
            result = argp->a * argp->b;
            break;
        case '/':
            if(argp->b != 0.0) {
                result = argp->a / argp->b;
            } else {
                result = NAN;
            }
            break;
        default:
            result = NAN;
    }
    
    return &result;
}
