%{
#include <iostream>
#include <string>
#include "Emitter.h"

extern Emitter* globalEmitter;

void yyerror(const char *s);
extern int yylex();
%}

%union {
	int num_token;
	int value;
}

%token <num_token> NUM
%token X PLUS MINUS MUL DIV POWER OPENBACKET CLOSEBACKET EOL

%left PLUS MINUS
%left MUL DIV
%right POWER

%%
input:
	expr EOL {YYACCEPT;};
expr:
	expr PLUS expr {globalEmitter->addition();} |
	expr MINUS expr {globalEmitter->substraction();} |
	expr MUL expr {globalEmitter->multiplication();} |
	expr DIV expr {globalEmitter->division();} |
	NUM X {
		globalEmitter->pushNumber($1);
		globalEmitter->pushX();
		globalEmitter->multiplication();
	} |
	NUM OPENBACKET expr CLOSEBACKET {
		globalEmitter->pushNumber($1);
		globalEmitter->multiplication();
	} | 
	expr POWER expr {globalEmitter->power();} | 
	OPENBACKET expr CLOSEBACKET | 
	MINUS expr %prec POWER {
		globalEmitter->pushNumber(-1);
		globalEmitter->multiplication();
	} |
	PLUS expr %prec POWER |
	OPENBACKET expr CLOSEBACKET OPENBACKET expr CLOSEBACKET {globalEmitter->multiplication();} |
	NUM {globalEmitter->pushNumber($1);} |
	X {globalEmitter->pushX();}

;
%%

void yyerror(const char *s) {
	std::cerr << "Parser error: " << s << "\n";
}
