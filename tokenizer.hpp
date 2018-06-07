#pragma once

#include "Liste.hpp"
#include <string>

// wrapper for strtok()
class Tokenizer {
protected:
    int _pos;
    Liste<std::string> _tokens;

public:
    Tokenizer(std::string data, std::string separators);
    int countTokens();
    std::string nextToken();
    bool hasMoreTokens();
};
