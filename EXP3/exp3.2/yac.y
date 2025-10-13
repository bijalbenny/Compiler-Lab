%{
    #include <stdio.h>
    int valid =1;
%}

%token letter digit

%%
start : letter s
s : letter s
| digit s
| 
;
%%

int yyerror() {
    printf("Not an identifier\n");
    valid = 0;
    return 0;
}
int main() {
    printf("Enter a name to test\n");
    yyparse();
    if(valid){
        printf("It is an identifier\n");
    }
}
