/**
 * Manipula strings pra auxiliar tarefas como split
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Bruno Marra
 */

#include "manstring.hpp"

// Explode uma string em diversos vetores de caracteres
string *explode(string text, char delimiter) {
    // Vetor de strings pra salvar os tokens
    vector<string> tokens;

    stringstream check1(text);
    string intermediate;

    // Enquanto conseguir pegar linhas pelo delimitador
    while (getline(check1, intermediate, delimiter)) {
        tokens.push_back(intermediate);
    }

    string *program = new string[tokens.size()];

    // Preenchendo o programa com os tokens
    for (size_t i = 0; i < tokens.size(); i++)
        program[i] = tokens[i];

    return program;
}
