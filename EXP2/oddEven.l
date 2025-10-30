%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

[0-9]+      {
                int n = atoi(yytext);
                if (n % 2 == 0)
                    printf("%d is Even\n", n);
                else
                    printf("%d is Odd\n", n);
            }

[ \t\n]+    { /* Ignore whitespace */ }

.           { printf("Invalid input: %s\n", yytext); }

%%

int main() {
    printf("Enter a number: \n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
