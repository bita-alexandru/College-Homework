%{
#include <stdio.h>
#include "y.tab.h"
%}
%option noyywrap
digit [0-9]
uint {digit}+
int {digit}+
float ({uint}[.]){digit}*
char [a-zA-Z]
string \"[^\"]*\"
bool false|true
id {char}({char}|{digit}|[_])*
numar {int}|{float}
sir \'{char}\'|{string}|{bool}
%%
``(.*|\n) ;

@structures {return STRUCTURI;}
@global {return GLOBAL;}
@functions {return FUNCTII;}
@main {return MAIN;}

~Eval {return EVAL;}


\?|\! {yylval.charval = yytext[0]; return VARCONST;}
int|float|char|string|bool {yylval.strval = strdup(yytext); return TIP;}
struct {return STRUCT;}

func {return FUNC;}
return {return RETURN;}

if {return IF;}
else {return ELSE;}
while {return WHILE;}
for {return FOR;}

start {return FOR_START;}
stop {return FOR_STOP;}
step {return FOR_STEP;}

and {return AND;}
or {return OR;}
xor {return XOR;}
not {return NOT;}
== {return EQ;}
\>= {return GE;}
\<= {return LE;}
\> {return GT;}
\< {return LT;}

concat {return CONCAT;}
copy {return COPY;}

print {return PRINT;}

\<{uint}\> {
    yytext[0] = '0';
    yytext[yyleng-1] = '\0';
    yylval.intval = atoi(yytext); return DIMENSIUNE;
    }
:= {return ATRIBUIRE;}
{numar} {yylval.numval = atof(yytext); return NUMAR;}
{sir} {yylval.strval = strdup(yytext); return SIR;}

\+ {return ADD;}
- {return SUB;}
\/ {return DIV;}
\* {return MUL;}

: {return SELECTOR;}

{id} {yylval.strval = strdup(yytext); return ID;}

[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
