%{
    #include <stdio.h>
    #include <ctype.h>

    int lines = 0,spaces = 0, words = 0,characters = 0,in_word = 0;
    
%}

%%
\n {
    lines++;
    characters++;
    in_word = 0;
}

[ \t]+ {
    spaces += yyleng;
    characters+= yyleng;
    in_word = 0;
}

[a-zA-Z0-9_] {
    characters ++;
    if(!in_word){
        words++;
        in_word = 1;
    }
}

. {
    characters++;
}
%%

int main(){
    yyin = fopen("myfile.txt","r");
    if(!yyin){
        perror("Error opening");
        return 1;
    }
    yylex();
    fclose(yyin);
    printf("This file contains:\n" );
    printf("%d lines\n",lines);
    printf("%d spaces\n",spaces);
    printf("%d characters\n",characters);
    printf("%d words\n",words);
    
}
int yywrap() {
    return 1;
}
