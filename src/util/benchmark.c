/**
 * Auxilia a contagem de tempo de execução de um trecho de código
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "benchmark.h"


// Converte uma métrica em sua sigla de descrição
const char* getMetricText(BenchmarkMetrics metric) {
	return (metric == SECONDS) ? "s" : (metric == MILISECONDS) ? "ms" : (metric == MICROSECONDS) ? "us" : "??";
}

// Inicializa a contagem de um benchmark
clock_t beginBenchmark(void) {
	cprintf(RED, "\n\t[STATS] Inciando análise de algoritmo... \n");
	return clock();
}

// Finaliza a contagem de execução de um algoritmo a partir de um tempo extraído anteriormente
void finishBenchmark(clock_t benchmarkStart, BenchmarkMetrics metric) {
	clock_t benchmarkFinish = clock();
	double metricPerSec = CLOCKS_PER_SEC / power(1000.0, metric);
	double result = (double) (benchmarkFinish - benchmarkStart) / metricPerSec;
	cprintf(RED, "\n\t[STATS] Fim da análise de algoritmo... \n");
	cprintf(RED, "\t[STATS] Tempo de execução: %.4lf %s\n", result, getMetricText(metric));
}

// Realiza a potencia
double power(double a, double b) {
	double result = 1;

	for (int i = 0; i < b; i++) {
		result *= a;
	}

	return result;
}
