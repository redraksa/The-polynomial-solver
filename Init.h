#pragma once
#include <iostream>

#include "parametres.h"

using namespace parameters;

class Init
{
public:
    static const std::string getValue(const TokenType& tokenType) {
		switch (tokenType)
		{
		case X:
			return "x";
		case PLUS: 
			return "+";
		case MINUS: 
			return "-";
		case MUL: 
			return "*";
		case DIV: 
			return "/";
		case POWER:
			return "^";
		case OPENBACKET:
			return "(";
		case CLOSEBACKET:
			return ")";
		default:
			break;
		}

		return "";
    }
};

