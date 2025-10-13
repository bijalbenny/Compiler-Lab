%{
    #include <stdio.h>
    #include <stdlib.h>
    #define YYSTYPE double
%}

%token DIGIT ID NL
%left '-' '+'
%left '*' '/'

%%

stmt:ID '=' exp NL {
    printf("Valid expression\n");
}
|exp NL {
    printf("Valid expression\n");
};
exp :exp '+' exp
|exp '-' exp
|exp '*' exp
|exp '/' exp
|'(' exp ')'
|ID
|DIGIT
;

%%

int yyerror(char *msg){
    printf("Invalid string\n");
}
void main(){
    printf("Enter the expression:\n");
    yyparse();
}
