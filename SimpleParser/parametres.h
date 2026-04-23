#pragma once
#include <string>
#include <map>
#include "Rational.h"
namespace parameters {
	enum COMPARES {
		GREATER, SMALLER, EQUAL
	};

	enum RETURNTYPEDIVIDEPOLYNOMS {
		REMAINDER, QUOTIENT
	};

	inline std::string CHAR_DIVIDERS = { ' ', '\t' };
	inline std::string CHAR_END = { '\n', EOF };

	enum TokenType
	{
		X, PLUS, MINUS, MUL, DIV, POWER, OPENBACKET, CLOSEBACKET, ENDENUM, NUM, END, NOTYPE, ERRORTOKEN
	};

	struct Lexem {
		TokenType token;
		std::string value;
		Lexem() {
			token = NOTYPE;
			value = "";
		}
	};

	typedef std::map<long long, Rational> Polynom;
}