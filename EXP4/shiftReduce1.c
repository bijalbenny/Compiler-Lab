#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_STACK 50
#define MAX_INPUT 50
#define MAX_RHS 10

// Grammar rule structure
typedef struct {
    char lhs;           // Left-hand side
    char rhs[MAX_RHS];  // Right-hand side
} Rule;

Rule grammar[MAX_RULES];
int ruleCount = 0;

char stack[MAX_STACK];
char input[MAX_INPUT];
int stackIndex = 0;
int inputIndex = 0;
int inputLength = 0;

// Function to check if top of stack matches a grammar RHS
int tryReduce() {
    for (int r = 0; r < ruleCount; r++) {
        int rhsLen = strlen(grammar[r].rhs);
        if (rhsLen <= stackIndex) {
            // Compare top of stack with RHS
            if (strncmp(&stack[stackIndex - rhsLen], grammar[r].rhs, rhsLen) == 0) {
                stackIndex -= rhsLen;
                stack[stackIndex++] = grammar[r].lhs;
                stack[stackIndex] = '\0';
                printf("$%s\t%s$\tREDUCE %c->%s\n", stack, input + inputIndex, grammar[r].lhs, grammar[r].rhs);
                return 1; // Reduction done
            }
        }
    }
    return 0; // No reduction possible
}

int main() {
    int n;
    printf("Enter number of grammar rules: ");
    scanf("%d", &n);
    ruleCount = n;

    printf("Enter grammar rules (format: LHS RHS, e.g., E E+E or E id):\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c %s", &grammar[i].lhs, grammar[i].rhs);
    }

    printf("Enter input string: ");
    scanf("%s", input);
    inputLength = strlen(input);

    printf("\nStack\t  Input\t  Action\n");

    while (inputIndex < inputLength) {
        // Check for multi-character terminal "id"
        if (input[inputIndex] == 'i' && input[inputIndex + 1] == 'd') {
            // Shift 'id' as a whole
            stack[stackIndex++] = 'i';
            stack[stackIndex++] = 'd';
            stack[stackIndex] = '\0';
            inputIndex += 2;
            printf("$%s\t%s$\tSHIFT id\n", stack, input + inputIndex);
        } else {
            // Shift single character
            stack[stackIndex++] = input[inputIndex++];
            stack[stackIndex] = '\0';
            printf("$%s\t%s$\tSHIFT\n", stack, input + inputIndex);
        }

        // Reduce as much as possible
        while (tryReduce());
    }

    // Final reductions after all input consumed
    while (tryReduce());

    // Accept if stack has single start symbol
    if (stackIndex == 1 && stack[0] == grammar[0].lhs) {
        printf("$%s\t$\tACCEPT\n", stack);
    } else {
        printf("Parsing failed.\n");
    }

    return 0;
}
