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
			return "";
			break;
		}
    }
};

