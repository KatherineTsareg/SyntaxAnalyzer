%{

#include "grammar.gen.h"
#define yylex checker_lex
#include <vector>
#include <string>

std::vector<std::string> sequence;

%}


COMMENT "#".*"\n"
MULTILINECOMMENT "+-"(.|\n)*"-+"
INT ("+"|"-")?(("0"|[1-9][0-9]*))
FLOAT ({INT})"."([0-9]+)((e|E)("+"|"-")?("0"|([1-9][0-9]*)))?
FUNCTIONID [A-Z]+
BOOL True|False
STRING \".*\"
TYPENAME Int|Float|Bool|Char|String
ID [a-zA-Z][a-zA-Z0-9]*
CHAR \'.\'
OPEN ("\n"[ \t]*)?"{"[ \t]*"\n"
/*CLOSE ("\n"[ \t]*)?"}"[ \t]*"\n")*/
CLOSE "}"[ \t]*"\n"


/* Опция, необходимая для языков с препроцессорами и #include,
   в нашем случае не нужна */
%option noyywrap

%%
"Return" sequence.push_back("RETURN");
"List" sequence.push_back("LIST");
"Of" sequence.push_back("OF");
"Main" sequence.push_back("MAIN");
"Function" sequence.push_back("FUNCTION");
"Read" sequence.push_back("READ");
"Print" sequence.push_back("PRINT");
"Do" sequence.push_back("DO");
"While" sequence.push_back("WHILE");
"For" sequence.push_back("FOR");
"Else" sequence.push_back("ELSE");
"Elif" sequence.push_back("ELIF");
"If" sequence.push_back("IF");
"Or" sequence.push_back("OR");
"And" sequence.push_back("AND");
"Const" sequence.push_back("CONST");
{TYPENAME} sequence.push_back("TYPENAME");
{FLOAT}	sequence.push_back("FLOAT");
{INT}	sequence.push_back("INT");
{CHAR}	sequence.push_back("CHAR");
{BOOL}	sequence.push_back("BOOL");
{STRING} sequence.push_back("STRING");
{FUNCTIONID} sequence.push_back("FUNCTIONID");
{ID} sequence.push_back("ID");
"<=" sequence.push_back("<=");
"<" sequence.push_back("<");
">=" sequence.push_back(">=");
">" sequence.push_back(">");
"==" sequence.push_back("==");
"!=" sequence.push_back("!=");
"!" sequence.push_back("!");
"=" sequence.push_back("=");
"+" sequence.push_back("+");
"-" sequence.push_back("-");
"*" sequence.push_back("*");
"/" sequence.push_back("/");
"%" sequence.push_back("%");
"+=" sequence.push_back("+=");
"-=" sequence.push_back("-=");
"*=" sequence.push_back("*=");
"/=" sequence.push_back("/=");
"%=" sequence.push_back("%=");
{COMMENT} ;
{MULTILINECOMMENT} ;
{OPEN} sequence.push_back("OPEN");
{CLOSE} sequence.push_back("CLOSE");
"{" sequence.push_back("{");
"}" sequence.push_back("}");
"(" sequence.push_back("(");
")" sequence.push_back(")");
"[" sequence.push_back("[");
"]" sequence.push_back("]");
"," sequence.push_back(",");
"\'" sequence.push_back("\'");
"\"" sequence.push_back("\"");

"\n" sequence.push_back("\n");
[ \t]+ );
