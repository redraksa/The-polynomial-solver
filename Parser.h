#pragma once
#include <iostream>
#include "Lexer.h"
#include <queue>

#include "parametres.h"

using namespace parameters;

class Parser {
private:
    Lexem nextLexem;
 
    Lexer lexer;
    std::queue<Lexem> stackLexem;

    void match(TokenType token) {
        if (nextLexem.token == token) {
            nextLexem = lexer.getLexem();
        }
        else {
            throw std::runtime_error(std::string("Expected type of token \'") +
                Init::getValue(token) + std::string("\', but there are symbol \'") + nextLexem.value + std::string("\'"));
        }
    }

    void unar() {
        if (nextLexem.token == PLUS) {
            match(PLUS);
            power();

        }
        else if (nextLexem.token == MINUS) {
            Lexem curLexem1 = nextLexem;
            match(MINUS);
            pushToken("0");
            Lexem curLexem2;
            curLexem2.token = NUM;
            curLexem2.value = "0";
            pushToken(curLexem2);
            power();
            pushToken(Init::getValue(MINUS));
            pushToken(curLexem1);
        }
        else
        {
            power();
        }
    }

    void factor() {
        if (nextLexem.token == NUM) {
            pushToken(nextLexem.value);
            pushToken(nextLexem);
            match(NUM);
        }
        else if (nextLexem.token == X) {
            pushToken(nextLexem.value);
            pushToken(nextLexem);
            match(X);
        }
        else if (nextLexem.token == OPENBACKET) {
            match(OPENBACKET);
            expr();
            match(CLOSEBACKET);
        }
        else {
            throw std::runtime_error(std::string("Expected number, but there are \'") +
                nextLexem.value + std::string("\'"));
        }

    }

    void expr() {
        term();
        while (nextLexem.token == PLUS || nextLexem.token == MINUS) {
            if (nextLexem.token == PLUS) {
                Lexem curLexem = nextLexem;
                match(PLUS);
                term();
                pushToken(Init::getValue(PLUS));
                pushToken(curLexem);
            }
            else if (nextLexem.token == MINUS) {
                Lexem curLexem = nextLexem;
                match(MINUS);
                term();
                pushToken(Init::getValue(MINUS));
                pushToken(curLexem);
            }
        }
    }

    void term() {
        unar();
        while (nextLexem.token == MUL || nextLexem.token == DIV || nextLexem.token == OPENBACKET || nextLexem.token == X) {
            if (nextLexem.token == MUL) {
                Lexem curLexem = nextLexem;
                match(MUL);
                unar();
                pushToken(Init::getValue(MUL));
                pushToken(curLexem);
            }
            else if (nextLexem.token == DIV) {
                Lexem curLexem = nextLexem;
                match(DIV);
                unar();
                pushToken(Init::getValue(DIV));
                pushToken(curLexem);
            }
            else if (nextLexem.token == OPENBACKET || nextLexem.token == X) {
                unar();
                pushToken(Init::getValue(MUL));
                Lexem curLexem;
                curLexem.token = MUL;
                curLexem.value = "*";
                pushToken(curLexem);
            }
        }
        
    }

    void power() {
        factor();
        if (nextLexem.token == POWER) {
            Lexem curLexem = nextLexem;
            match(POWER);
            power();
            pushToken(Init::getValue(POWER));
            pushToken(curLexem);
        }
    }

    void pushToken(const std::string& token) {
        std::cout << "\'" << token << "\' ";
    }

    void pushToken(const Lexem& lexem) {
        stackLexem.push(lexem);
    }
public:

    void translate() {
        std::cout << "Input expression: ";
        nextLexem = lexer.getLexem();

        try {
            expr();
            if (nextLexem.token != ERRORTOKEN) {
                if (nextLexem.token == END) {
                    std::cout << "\nSUCCESS\n";
                }
                else {
                    std::cout << "\nFailure";
                }
            }
            else {
                std::cout << "\nInvalid Token: " << nextLexem.value;
            }

        }
        catch (const std::exception& e) {
            std::cerr << "\nERROR: " << e.what() << "\n";
        }
    }

    std::queue<Lexem> getStackLexem() const {
        return stackLexem;
    }
};

