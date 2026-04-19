#pragma once
#include <iostream>

inline std::string CHAR_DIVIDERS = { ' ', '\t' };
inline std::string CHAR_END = { '\n', EOF };

enum TokenType
{
    X, PLUS, MINUS, MUL, DIV, POWER, OPENBACKET, CLOSEBACKET, ENDENUM, NUM, END, NOTYPE, ERRORTOKEN
};

class Init
{
public:
    static const std::string getValue(const TokenType& tokenType) {
		switch (tokenType)
		{
		case X:
			return "x";
			//break;
		case PLUS: 
			return "+";
			//break;
		case MINUS: 
			return "-";
			//break;
		case MUL: 
			return "*";
			//break;
		case DIV: 
			return "/";
			//break;
		case POWER:
			return "^";
		case OPENBACKET:
			return "(";
		case CLOSEBACKET:
			return ")";
		default:
			return "";
			break;
		}
    }
};

