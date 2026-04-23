%{
#include <iostream>
#include <string>
#include <stdexcept>
#include "parser.tab.hpp"
%}

%option noyywrap
%option nounput
%option noinput

%%
[ \t]		;
\n		{
			return EOL;
		}
[1-9][0-9]*|0	{
			try {
				yylval.value = std::stoll(yytext);
				return NUM;
			}
			catch (const std::out_of_range& e) {
				throw std::out_of_range("Number is too large: " + std::string(yytext));
			}
			catch (const std::exception& e) {
				throw std::runtime_error("Invalid number: " + std::string(yytext));
			}
		}
"x"		{return X;} 
"+"		{return PLUS;}
"-" 		{return MINUS;}
"*"		{return MUL;}
"/"		{return DIV;}
"^"		{return POWER;}
"("		{return OPENBACKET;}
")"		{return CLOSEBACKET;}

.		{std::cerr << "Unknown character: " << yytext << "\n";}

%%
