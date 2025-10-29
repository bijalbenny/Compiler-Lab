#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp1, *fp2;
    char op[3], arg1[10], arg2[10], result[10], fname[100];

    printf("Enter input file name: ");
    scanf("%s", fname);

    fp1 = fopen(fname, "r");
    if (!fp1) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    fp2 = fopen("output.txt", "w");
    if (!fp2) {
        printf("Error: Cannot create output file.\n");
        fclose(fp1);
        return 1;
    }

    while (fscanf(fp1, "%s %s %s %s", op, arg1, arg2, result) == 4) {
        fprintf(fp2, "\nMOV R0,%s", arg1);

        if (strcmp(op, "+") == 0)
            fprintf(fp2, "\nADD R0,%s", arg2);
        else if (strcmp(op, "-") == 0)
            fprintf(fp2, "\nSUB R0,%s", arg2);
        else if (strcmp(op, "*") == 0)
            fprintf(fp2, "\nMUL R0,%s", arg2);
        else if (strcmp(op, "/") == 0)
            fprintf(fp2, "\nDIV R0,%s", arg2);
        else if (strcmp(op, "=") == 0) {
            fprintf(fp2, "\nMOV %s,R0", result);
            continue;
        }

        fprintf(fp2, "\nMOV %s,R0", result);
    }

    fclose(fp1);
    fclose(fp2);
    printf("Conversion completed. Check output.txt\n");
    return 0;
}
