/**
 * Definição de tipos pra facilitar a identificação das políticas de escalonamento
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef politics_hpp
#define politics_hpp

/**
 * ENUM pra definir se o escalonamento é preemptivo ou não
 */
enum class Preemptiveness {
    PREEMPTIVE,
    NON_PREEMPTIVE
};

/**
 * Tipos de escalonamento disponíveis.
 */
enum class Politics {
    PRIORITY_DEFAULT, // Definido pelo professor
    SHORTEST,
    LEAST_USED
};

#endif /* politics_hpp */
