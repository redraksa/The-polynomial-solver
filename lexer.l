%{
#include <iostream>
#include <string>
#include "parser.tab.h"
%}

%option noyywrap
%option nounput
%option noinput

%%
[ \t]	;
\n	{return EOL;}
[1-9][0-9]*|0	{
			yylval.value = std::stoi(yytext);
			return NUM;
		}
"x"	{return X;} 
"+"	{return PLUS;}
"-" 	{return MINUS;}
"*"	{return MUL;}
"/"	{return DIV;}
"^"	{return POWER;}
"("	{return OPENBACKET;}
")"	{return CLOSEBACKET;}

.	{std::cerr << "Unknown character: " << yytext << "\n";}

%%
