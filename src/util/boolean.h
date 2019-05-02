/**
 * Define um tipo de dados para booleanos, para restringir apenas inteiros 1 ou 0
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef boolean_h
#define boolean_h

#include <stdlib.h>

// 0 = FALSE, 1 = TRUE
typedef enum {FALSE, TRUE} boolean;

/**
 * Converte um inteiro para um valor booleano
 * @param  number Inteiro a ter o seu valor convertido
 * @return        Valor booleano convertido a partir do inteiro fornecido
 */
boolean toBoolean(int number);

#endif /* boolean_h */
