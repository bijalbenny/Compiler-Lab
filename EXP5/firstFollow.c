#include <stdio.h>
#include <string.h>
#include <ctype.h>

char p[20][20];
int n;

void first(char c, int v[], int r[]) {
    if (!isupper(c)) {
        r[c] = 1;
        return;
    }
    v[c] = 1;

    for (int i = 0; i < n; i++) {
        if (p[i][0] == c) {
            char x = p[i][2];

            if (x == '#')
                r['#'] = 1;
            else if (!isupper(x))
                r[x] = 1;
            else if (!v[x])
                first(x, v, r);
        }
    }
}

void follow(char c, int v[], int r[]) {
    if (p[0][0] == c)
        r['$'] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 2; p[i][j]; j++) {
            if (p[i][j] == c) {
                char x = p[i][j + 1];

                if (x) {
                    int f[256] = {0}, vv[256] = {0};
                    first(x, vv, f);

                    for (int k = 0; k < 256; k++)
                        if (f[k] && k != '#')
                            r[k] = 1;

                    if (f['#'] && p[i][0] != c && !v[p[i][0]]) {
                        v[p[i][0]] = 1;
                        follow(p[i][0], v, r);
                    }
                } 
                else if (p[i][0] != c && !v[p[i][0]]) {
                    v[p[i][0]] = 1;
                    follow(p[i][0], v, r);
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g. E=TR):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", p[i]);

    int d[256] = {0};
    printf("\n--- FIRST ---\n");

    for (int i = 0; i < n; i++) {
        char c = p[i][0];
        if (d[c]) continue;
        d[c] = 1;

        int f[256] = {0}, v[256] = {0};
        first(c, v, f);

        printf("FIRST(%c): ", c);
        for (int j = 0; j < 256; j++)
            if (f[j])
                printf("%c ", j);
        printf("\n");
    }

    memset(d, 0, sizeof(d));
    printf("\n--- FOLLOW ---\n");

    for (int i = 0; i < n; i++) {
        char c = p[i][0];
        if (d[c]) continue;
        d[c] = 1;

        int f[256] = {0}, v[256] = {0};
        follow(c, v, f);

        printf("FOLLOW(%c): ", c);
        for (int j = 0; j < 256; j++)
            if (f[j])
                printf("%c ", j);
        printf("\n");
    }

    return 0;
}
