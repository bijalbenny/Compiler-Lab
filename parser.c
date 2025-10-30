#include<stdio.h>
#include <string.h>

char expr[100];
 void parser(char *e){
    int len = strlen(e);
    int num=0,result=0,lastTerm=0;
    char op='+';

    for(int i=0;i<len;i++){
        char c = e[i];
        if(c>='0'&&c<='9'){
            num =num*10 + (c-'0');
        }
        if(c=='+'||c=='-'||c=='*'||c=='/'||i==len-1){
            
        
         if(op=='+'){
             result +=lastTerm;
             lastTerm=num;
         }
         else if(op=='-'){
             result +=lastTerm;
             lastTerm=-num;
         }
         else if(op=='*'){
             lastTerm*=num;
         }
         else if(op=='/'){
             lastTerm /=num;
         }
         op=c;
         num=0;

    }
   }   
   result+=lastTerm ;
   printf("Result : %d\n",result);
 }
int main() {
    printf("Enter the expression: "); 
    scanf("%s", expr);
    parser(expr);
    return 0;
 }
