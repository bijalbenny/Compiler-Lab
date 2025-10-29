#include <stdio.h>
#include <string.h>

char expr[100];
char temp = 'Z';

void generateIntermediateCode(char *e) {
    char result = e[0];
    int len = strlen(e);
   // char temps[20];  // store temp replacements
   // for (int i = 0; i < len; i++) temps[i] = e[i];

    // handle * and /
    for (int i = 0; i < len; i++) {
        if (e[i] == '*' || e[i] == '/') {
            printf("%c := %c %c %c\n", temp, e[i - 1], e[i], e[i + 1]);
            e[i - 1] = temp;
            for (int j = i; j < len - 2; j++) e[j] = e[j + 2];
            len -= 2;
            temp--;
            i = -1;  // restart scanning
        }
    }

    // handle + and -
    for (int i = 0; i < len; i++) {
        if (e[i] == '+' || e[i] == '-') {
            printf("%c := %c %c %c\n", temp, e[i - 1], e[i], e[i + 1]);
            e[i - 1] = temp;
            for (int j = i; j < len - 2; j++) e[j] = e[j + 2];
            len -= 2;
            temp--;
            i = -1;  // restart scanning
        }
    }

    // final assignment
    printf("%c := %c\n", result, e[len - 1]);
}

int main() {
    printf("INTERMEDIATE CODE GENERATION\n");
    printf("Enter the expression: ");
    scanf("%s", expr);
    generateIntermediateCode(expr);
    return 0;
}

/*
✅ Example Output:
INTERMEDIATE CODE GENERATION
Enter the expression: w:a+b*c+d
Z := b * c
Y := a + Z
X := Y + d
w := X
*/
