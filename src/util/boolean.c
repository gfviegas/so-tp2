/**
 * Define um tipo de dados para booleanos, para restringir apenas inteiros 1 ou 0
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "boolean.h"

// Converte um inteiro para um valor booleano
boolean toBoolean(int number) {
	return (number) ? TRUE : FALSE;
}
