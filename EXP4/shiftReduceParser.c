#include<stdio.h>
#include<string.h>

int inputIndex = 0, checkIndex = 0, stackIndex = 0, i = 0, j = 0, inputLength = 0;
char input[16], actionStr[20], stack[15], shiftAction[10];

void reduce();

void main() {
    puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id");
    puts("enter input string ");
    scanf("%s", input);
    inputLength = strlen(input);
    strcpy(shiftAction, "SHIFT->");
    puts("stack \t input \t action");

    for (inputIndex = 0, stackIndex = 0; j < inputLength; inputIndex++, stackIndex++, j++) {
        if (input[j] == 'i' && input[j + 1] == 'd') {
            stack[stackIndex] = input[j];
            stack[stackIndex + 1] = input[j + 1];
            stack[stackIndex + 2] = '\0';
            input[j] = ' ';
            input[j + 1] = ' ';
            printf("\n$%s\t%s$\t%sid", stack, input, shiftAction);
            reduce();
        } else {
            stack[stackIndex] = input[j];
            stack[stackIndex + 1] = '\0';
            input[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbols", stack, input, shiftAction);
            reduce();
        }
    }
    if (strcmp(stack, "E") == 0 && strspn(input, " ") == inputLength) {
        printf("\n$%s\t%s$\tACCEPT\n", stack, input);
    }
}

void reduce() {
    strcpy(actionStr, "REDUCE TO E");

    for (checkIndex = 0; checkIndex < inputLength; checkIndex++)
        if (stack[checkIndex] == 'i' && stack[checkIndex + 1] == 'd') {
            stack[checkIndex] = 'E';
            stack[checkIndex + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stack, input, actionStr);
            j++;
        }

    for (checkIndex = 0; checkIndex < inputLength; checkIndex++)
        if (stack[checkIndex] == 'E' && stack[checkIndex + 1] == '+' && stack[checkIndex + 2] == 'E') {
            stack[checkIndex] = 'E';
            stack[checkIndex + 1] = '\0';
            stack[checkIndex + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stack, input, actionStr);
            stackIndex = stackIndex - 2;
        }

    for (checkIndex = 0; checkIndex < inputLength; checkIndex++)
        if (stack[checkIndex] == 'E' && stack[checkIndex + 1] == '*' && stack[checkIndex + 2] == 'E') {
            stack[checkIndex] = 'E';
            stack[checkIndex + 1] = '\0';
            stack[checkIndex + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stack, input, actionStr);
            stackIndex = stackIndex - 2;
        }

    for (checkIndex = 0; checkIndex < inputLength; checkIndex++)
        if (stack[checkIndex] == '(' && stack[checkIndex + 1] == 'E' && stack[checkIndex + 2] == ')') {
            stack[checkIndex] = 'E';
            stack[checkIndex + 1] = '\0';
            stack[checkIndex + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stack, input, actionStr);
            stackIndex = stackIndex - 2;
        }

}
