/**
 * Manipula strings pra auxiliar tarefas como split
 *
 * Gustavo Viegas (3026), Bruno Marra (3029) e Heitor Passeado (3055)
 * @author Bruno Marra
 */

#ifndef manstring_hpp
#define manstring_hpp

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Explode uma string em diversos vetores de caracteres
 * @param  text      Texto a ser explodido
 * @param  delimiter Delimitador a ser explodido
 * @return           String explodida pelo delimitador
 */
string *explode(string text, char delimiter);

#endif /* manstring_hpp */
