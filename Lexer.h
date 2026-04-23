#pragma once
#include <iostream>
#include <string>
#include "Init.h"

#include "parametres.h"

using namespace parameters;

class Lexer
{
private:
    Lexem lexem;
    char lookahead;

    void nextLexem() {
        lookahead = std::cin.get();

        while (CHAR_DIVIDERS.find(lookahead) != std::string::npos) {
            lookahead = std::cin.get();
        }

        if (CHAR_END.find(lookahead) != std::string::npos) {
            lexem.value = "\0";
            lexem.token = END;
            return;
        }

        if (std::isdigit(lookahead)) {
            lexem.token = NUM;
            long long num = lookahead - '0';
            while (std::isdigit(std::cin.peek())) {
                lookahead = std::cin.get();
                num = num * 10ll + (lookahead - '0');
            }
            lexem.value = std::to_string(num);
            return;
        }

        lexem.value = std::string(1, lookahead);

        for (int i = 0; i < TokenType::ENDENUM; ++i) {
            std::string expectedString = Init::getValue(static_cast<TokenType>(i));
            if (expectedString == lexem.value) {
                lexem.token = static_cast<TokenType>(i);
                return;
            }
        }

        lexem.token = ERRORTOKEN;
            
    }

public:
	Lexer() : lexem{}, lookahead('\0') {}

    const Lexem& getLexem() {
        nextLexem();
        return lexem;
    }
};

