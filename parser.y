%{
#include <iostream>
#include <string>
#include "Emitter.h"

extern Emitter* globalEmitter;

void yyerror(const char *s);
extern int yylex();
%}

%union {
	long long num_token;
	long long value;
}

%token <num_token> NUM
%token X PLUS MINUS MUL DIV POWER OPENBACKET CLOSEBACKET EOL

%left PLUS MINUS
%left MUL DIV IMPLICIT_MUL X OPENBACKET
%right POWER

%%
input:
	expr EOL {YYACCEPT;}
	;

bracket_expr:
	OPENBACKET expr CLOSEBACKET
	;

x_token:
	X {globalEmitter->pushX();}
	;
num:
	NUM {globalEmitter->pushNumber($1);}
	;

expr:
	expr PLUS expr {globalEmitter->addition();} |
	expr MINUS expr {globalEmitter->substraction();} |
	expr MUL expr {globalEmitter->multiplication();} |
	expr DIV expr {globalEmitter->division();} |
	expr POWER expr {globalEmitter->power();} |
	
	MINUS expr %prec IMPLICIT_MUL {
		globalEmitter->pushNumber(-1);
		globalEmitter->multiplication();
	} |
	PLUS expr %prec IMPLICIT_MUL |
	
	expr x_token %prec IMPLICIT_MUL {
		globalEmitter->multiplication();
	} |
	expr bracket_expr %prec IMPLICIT_MUL {
		globalEmitter->multiplication();
	} |
	

	expr x_token POWER expr %prec POWER {
		globalEmitter->power();
		globalEmitter->multiplication();
	} |
	expr bracket_expr POWER expr %prec POWER {
		globalEmitter->power();
		globalEmitter->multiplication();
	} |

	bracket_expr |
	num |
	x_token
	;
%%

void yyerror(const char *s) {
	std::cerr << "Parser error: " << s << "\n";
}

