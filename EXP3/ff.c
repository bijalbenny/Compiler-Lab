#include <stdio.h>
#include <string.h>
#include <ctype.h>

char productions[20][20];  // To store all grammar productions
int productionCount;       // Number of productions

// Function to find FIRST set of a given symbol
void findFirst(char symbol, int visited[], int firstSet[]) {
    if (!isupper(symbol)) {  // if terminal, directly add to FIRST
        firstSet[symbol] = 1;
        return;
    }
    visited[symbol] = 1;

    for (int i = 0; i < productionCount; i++) {
        if (productions[i][0] == symbol) {
            char nextSymbol = productions[i][2];

            if (nextSymbol == '#')  // epsilon
                firstSet['#'] = 1;
            else if (!isupper(nextSymbol))  // terminal
                firstSet[nextSymbol] = 1;
            else if (!visited[nextSymbol])  // non-terminal
                findFirst(nextSymbol, visited, firstSet);
        }
    }
}

// Function to find FOLLOW set of a given symbol
void findFollow(char symbol, int visited[], int followSet[]) {
    if (productions[0][0] == symbol)
        followSet['$'] = 1;  // add $ for start symbol

    for (int i = 0; i < productionCount; i++) {
        for (int j = 2; productions[i][j]; j++) {
            if (productions[i][j] == symbol) {
                char nextSymbol = productions[i][j + 1];

                if (nextSymbol) {
                    int tempFirst[256] = {0}, tempVisited[256] = {0};
                    findFirst(nextSymbol, tempVisited, tempFirst);

                    for (int k = 0; k < 256; k++)
                        if (tempFirst[k] && k != '#')
                            followSet[k] = 1;

                    if (tempFirst['#'] && productions[i][0] != symbol && !visited[productions[i][0]]) {
                        visited[productions[i][0]] = 1;
                        findFollow(productions[i][0], visited, followSet);
                    }
                } 
                else if (productions[i][0] != symbol && !visited[productions[i][0]]) {
                    visited[productions[i][0]] = 1;
                    findFollow(productions[i][0], visited, followSet);
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &productionCount);

    printf("Enter productions (e.g. E=TR):\n");
    for (int i = 0; i < productionCount; i++)
        scanf("%s", productions[i]);

    int done[256] = {0};

    printf("\n--- FIRST ---\n");
    for (int i = 0; i < productionCount; i++) {
        char nonTerminal = productions[i][0];
        if (done[nonTerminal]) continue;
        done[nonTerminal] = 1;

        int firstSet[256] = {0}, visited[256] = {0};
        findFirst(nonTerminal, visited, firstSet);

        printf("FIRST(%c): ", nonTerminal);
        for (int j = 0; j < 256; j++)
            if (firstSet[j])
                printf("%c ", j);
        printf("\n");
    }

    memset(done, 0, sizeof(done));

    printf("\n--- FOLLOW ---\n");
    for (int i = 0; i < productionCount; i++) {
        char nonTerminal = productions[i][0];
        if (done[nonTerminal]) continue;
        done[nonTerminal] = 1;

        int followSet[256] = {0}, visited[256] = {0};
        findFollow(nonTerminal, visited, followSet);

        printf("FOLLOW(%c): ", nonTerminal);
        for (int j = 0; j < 256; j++)
            if (followSet[j])
                printf("%c ", j);
        printf("\n");
    }

    return 0;
}
