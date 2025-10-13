#include <stdio.h>
#include <string.h>

#define MAX 20

char states[MAX][10];
char from[MAX][10], input[MAX][5], to[MAX][10];
int t;

// To avoid duplicate states in closure
int inClosure(char closure[][10], int count, char *state) {
    for (int i = 0; i < count; i++)
        if (strcmp(closure[i], state) == 0)
            return 1;
    return 0;
}

// Recursive function to find epsilon closure
void epsilonClosure(char *state, char closure[][10], int *count) {
    if (!inClosure(closure, *count, state)) {
        strcpy(closure[*count], state);
        (*count)++;
    }

    for (int i = 0; i < t; i++) {
        if (strcmp(from[i], state) == 0 && strcmp(input[i], "e") == 0) {
            if (!inClosure(closure, *count, to[i])) {
                epsilonClosure(to[i], closure, count);
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of states: ");
    scanf("%d", &n);

    printf("Enter the states: ");
    for (int i = 0; i < n; i++)
        scanf("%s", states[i]);

    printf("Enter the number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from input to):\n");
    printf("Use 'e' for epsilon transitions\n");
    for (int i = 0; i < t; i++)
        scanf("%s %s %s", from[i], input[i], to[i]);

    // Compute epsilon closure for each state
    for (int i = 0; i < n; i++) {
        char closure[MAX][10];
        int count = 0;

        epsilonClosure(states[i], closure, &count);

        printf("\nEpsilon closure of %s = { ", states[i]);
        for (int j = 0; j < count; j++)
            printf("%s ", closure[j]);
        printf("}");
    }

    printf("\n");
    return 0;
}
