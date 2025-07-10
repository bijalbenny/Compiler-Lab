#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
  char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
  };
  for (int i = 0; i < 32; ++i) {
    if (strcmp(keywords[i], buffer) == 0)
      return 1;
  }
  return 0;
}

int main() {
  char ch, buffer[20], operators[] = "+-*/%=<>&|!", separators[] = "();{}[],";
  FILE *fp;
  int i, j = 0;
  int in_single_line_comment = 0, in_multi_line_comment = 0;

  fp = fopen("inp.txt", "r");
  if (fp == NULL) {
    printf("Error while opening the file\n");
    exit(0);
  }

  while ((ch = fgetc(fp)) != EOF) {
    // Check for start of comment
    if (ch == '/') {
      char next = fgetc(fp);
      if (next == '/') {
        in_single_line_comment = 1;
        continue;
      } else if (next == '*') {
        in_multi_line_comment = 1;
        continue;
      } else {
        ungetc(next, fp);  // Not a comment, put it back
      }
    }

    // Check for end of comments
    if (in_single_line_comment && ch == '\n') {
      in_single_line_comment = 0;
      continue;
    }
    if (in_multi_line_comment && ch == '*') {
      char next = fgetc(fp);
      if (next == '/') {
        in_multi_line_comment = 0;
        continue;
      } else {
        ungetc(next, fp);
      }
    }

    if (in_single_line_comment || in_multi_line_comment)
      continue;

    // Check for operators
    for (i = 0; operators[i] != '\0'; ++i) {
      if (ch == operators[i]) {
        printf("%c is operator\n", ch);
        break;
      }
    }

    // Check for separators
    for (i = 0; separators[i] != '\0'; ++i) {
      if (ch == separators[i]) {
        printf("%c is separator\n", ch);
        break;
      }
    }

    // Build token (identifier or keyword)
    if (isalnum(ch) || ch == '.') {
      buffer[j++] = ch;
    } else if ((ch == ' ' || ch == '\n' || ch == '\t') && j != 0) {
      buffer[j] = '\0';
      j = 0;
      if (isKeyword(buffer))
        printf("%s is keyword\n", buffer);
      else
        printf("%s is an identifier\n", buffer);
    }
  }

  // Final buffer check in case file doesn't end with whitespace
  if (j != 0) {
    buffer[j] = '\0';
    if (isKeyword(buffer))
      printf("%s is keyword\n", buffer);
    else
      printf("%s is an identifier\n", buffer);
  }

  fclose(fp);
  return 0;
}
