/**
 * Auxilia a contagem de tempo de execução de um trecho de código
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef benchmark_h
#define benchmark_h

#include <stdio.h>

#include <time.h>
#include "logger.h"

/**
 * Enumerador das métricas disponíveis (s, ms, us)
 */
typedef enum BenchmarkMetrics {
	SECONDS,
	MILISECONDS,
	MICROSECONDS
} BenchmarkMetrics;

/**
 * Converte uma métrica em sua sigla de descrição
 * @param  metric Métrica a ter sua sigla extraída
 * @return        String com o valor da sigla da métrica
 */
const char* getMetricText(BenchmarkMetrics metric);

/**
 * Inicializa a contagem de um benchmark
 * @return  Tempo onde o clock foi contabilizado
 */
clock_t beginBenchmark(void);

/**
 * Finaliza a contagem de execução de um algoritmo a partir de um tempo
 * extraído anteriormente.
 * @param benchmarkStart Tempo de clock do início do benchmark
 * @param metric         Métrica para imprimir o resultado
 */
void finishBenchmark(clock_t benchmarkStart, BenchmarkMetrics metric);

/**
 * Realiza a potencia
 * @param  a expoente
 * @param  b base
 * @return   resultado da operação
 */
double power(double a, double b);

#endif /* benchmark_h */
