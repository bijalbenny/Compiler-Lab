%{
    #include <stdio.h>
    #include <ctype.h>
%}

%%
abc {
    printf("ABC");
}

. {
    putchar(yytext[0]);
}
%%

int main(){
    printf("Enter string\n");
    yylex();
    printf("Converted: ");
    return 0;
}

int yywrap() {return 1;}
