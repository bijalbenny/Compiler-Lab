%{
    #include <stdio.h>
    int k=0,n=0,i=0,o=0,num=0;
%}

%%
(if|else|for) {
    printf("%s is keyword\n",yytext);
    k++;
    n++;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("%s is an identifier\n",yytext);
    i++;
    n++;
}

"+"|"-"|"*"|"/" {
    printf("%s is an operator\n",yytext);
    o++;
    n++;
}

[0-9]+ {
    printf("%s is a number\n",yytext);
    num++;
    n++;
}

"\t"|"\n" {}
(.) {}
<<EOF>> {return 0;}
%%

int main(){
    printf("Enter input text\n");
    yylex();
    return 0;
}
int yywrap() {}
