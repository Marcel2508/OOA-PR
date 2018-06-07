#include "tokenizer.hpp"
#include <string>
#include <cstring>
using namespace std;

// -------------------------------------------------------------------
Tokenizer::Tokenizer(string data, string separators) {
    _pos = 0;
    char *dat = (char *) data.c_str();
    char *sep = (char *) separators.c_str();

    char *tok = strtok(dat, sep);
    while (tok != 0) {
        _tokens.append(string(tok));
        tok = strtok(0, sep);
    }
}

// -------------------------------------------------------------------
int Tokenizer::countTokens() {
    return _tokens.size();
}

// -------------------------------------------------------------------
string Tokenizer::nextToken() {
    return _tokens.getValueAt(_pos++);
}

// -------------------------------------------------------------------
bool Tokenizer::hasMoreTokens() {
    return _pos < _tokens.size();
}
