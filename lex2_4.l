%{
    #include <stdio.h>
    int vowel = 0;
    int cons = 0;
%}

%%
[aeiouAEIOU] {
    vowel++;
}

[a-zA-Z] {
    cons++;
}
%%


int main(){
    printf("Enter string\n");
    yylex();
    printf("Number of vowels: %d\n",vowel);
    printf("Number of consonants: %d\n",cons);
    return 0;
}

int yywrap() {return 1;}
