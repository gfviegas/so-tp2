#include "manstring.hpp"

string *explode(string text, char delimiter) {
    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(text);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, delimiter)) {
        tokens.push_back(intermediate);
    }

    string *program = new string[tokens.size()];

    // Printing the token vector
    for (int i = 0; i < tokens.size(); i++)
        program[i] = tokens[i];

    return program;
}
