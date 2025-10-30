%{
    #include <stdio.h>
%}

%%
^0[01]*1$ {
    printf("valid string : %s\n",yytext);
}
^[^\n]*$ {
    printf("Invalid string : %s\n",yytext);
}
\n {}
%%

int main(){
    printf("Enter String\n");
    yylex();
}

int yywrap() {}
