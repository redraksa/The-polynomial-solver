
#include <string>
#include <iostream>
#include "Parser.h"
#include "Emitter.h"
#include "ResultPrinter.h"

int main()
{
    Parser parser;
    parser.translate();
    Emitter emitter(parser.getStackLexem());
    emitter.trasmittion();
    ResultPrinter resultPrinter(emitter.getResult());
    resultPrinter.printResult();
    return 0;
}

