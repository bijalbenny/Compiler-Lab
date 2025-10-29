#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isKeyword(char *word) {
    char *keywords[] = {
        "auto","break","case","char","const","continue","default","do","double",
        "else","enum","extern","float","for","goto","if","int","long","register",
        "return","short","signed","sizeof","static","struct","switch","typedef",
        "union","unsigned","void","volatile","while"
    };
    for (int i = 0; i < 32; i++)
        if (strcmp(word, keywords[i]) == 0)
            return true;
    return false;
}

bool isOperator(char c)  { 
    return strchr("+-*/%=><!", c) != NULL; }
bool isSpecial(char c)   {
     return strchr("();{}[]", c) != NULL; }

bool isNumber(char *word) {
    for (int i = 0; word[i]; i++)
        if (!isdigit(word[i]) && word[i] != '.')
            return false;
    return true;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) return printf("Error: cannot open file\n"), 1;

    char ch, buffer[50];
    int j = 0;

    while ((ch = fgetc(fp)) != EOF) {
        // collect alphanumerics or decimal points
        if (isalnum(ch) || ch == '.')
         buffer[j++] = ch;
        else {
            if (j) { // end of a token
                buffer[j] = '\0';
                j = 0;
                if (isKeyword(buffer))      printf("[%s : Keyword]\n", buffer);
                else if (isNumber(buffer))  printf("[%s : Number]\n", buffer);
                else                        printf("[%s : Identifier]\n", buffer);
            }

            // handle comments
            if (ch == '/') {
                char next = fgetc(fp);
                if (next == '/') while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                else if (next == '*') {
                    while ((ch = fgetc(fp)) != EOF)
                        if (ch == '*' && fgetc(fp) == '/') break;
                } else ungetc(next, fp);
            }
            else if (isOperator(ch)) printf("[%c : Operator]\n", ch);
            else if (isSpecial(ch))  printf("[%c : Special Symbol]\n", ch);
        }
    }
    fclose(fp);
    return 0;
}
