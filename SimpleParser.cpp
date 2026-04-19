
#include <iostream>
#include <stdexcept>
#include "Emitter.h"
#include "ResultPrinter.h"
#include "parser.tab.h"

Emitter* globalEmitter = nullptr;

extern int yyparse();

int main()
{
    Emitter emitter;
    globalEmitter = &emitter;
    
    std::cout << "Input expression: \n";
    try
    {
        if (yyparse() == 0) {
            emitter.normilizeAnswer();
            std::cout << "SUCCESS\n";
            std::cout << "Result: ";

            ResultPrinter resultPrinter(emitter.getResult());
	        resultPrinter.printResult();
	
        }
        else {
            std::cout << "Failure. Syntax error";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }

    return 0;
}

