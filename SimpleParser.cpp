
#include <iostream>
#include <stdexcept>
#include "Emitter.h"
#include "ResultPrinter.h"
#include "parser.tab.hpp"

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
    catch (const std::out_of_range& e) {
	std::cerr << "Value error: " << e.what() << "\n";
	return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Runtime error: " << e.what() << "\n";
	return 1;
    }
    catch (...) {
	std::cerr << "Uknown error!\n";
	return 1;
    }
    return 0;
}

