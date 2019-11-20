#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int isDelimiter(char ch)
    {
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||  
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||  
        ch == '[' || ch == ']' || ch == '{' || ch == '}'||ch=='#')
        return 1;
    return 0;
    }
int ispo(char ch)
    {
    if (ch == '"')
        return 1;
    return 0;
    }
int isLiteral(char ch)
    {
    if (ch == '"')
        return 1;
    return 0;
    }
int validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||  
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||  
        str[0] == '9' || isDelimiter(str[0]) == 1)
        return 0;
    return 1;
}

int isKeyword(char* str)
{
    if ( !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "short") || !strcmp(str, "typedef")
        || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static")
        || !strcmp(str, "goto")||!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||  
        !strcmp(str, "break") ||  
         !strcmp(str, "continue") || !strcmp(str, "int")
        ||  !strcmp(str, "float")
        || !strcmp(str, "return") || !strcmp(str, "char")
        || !strcmp(str, "case")|| !strcmp(str, "include") || !strcmp(str, "printf") )
        return 1;
    return 0;
}  
int isHeader(char* str)
{
    if ( !strcmp(str, "stdio.h")
        || !strcmp(str, "conio.h") || !strcmp(str, "stdlib.h"))
  return 1;
    return 0;
}
 
int isInteger(char* str)
{
    int i, len = strlen(str);
 
    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return 0;
    }
    return 1;
}

int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '>' || ch == '<' ||  
        ch == '=')
        return 1;
    return 0;
}
char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));
 
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}
int isRealNumber(char* str)
{
    int i, len = strlen(str);
    int hasDecimal = 0;
 
    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||  
            (str[i] == '-' && i > 0))
            return 0;
        if (str[i] == '.')
            hasDecimal = 1;
    }
    return 1;
}
void lex(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);
    char cc,semi='"';
    while (right <= len && left <= right) {

        if (isDelimiter(str[right]) == 0)
            right++;
  if (isOperator(str[right]) == 1&& left == right) {
                printf("<'%c',operator>\n", str[right]);
right++;
            left = right;
}
        else if (isDelimiter(str[right]) == 1 && left == right)
{
             
   if (isDelimiter(str[right]) == 1)
printf("<'%c',delimiter>\n", str[right]);

 
            right++;
            left = right;
        }
else if (isDelimiter(str[right]) == 1 && left != right
                   || (right == len && left != right)) {
 if(ispo(str[left-1])==1){
while(ispo(str[right-1]!=1))
{
right++;
}
}
            char* subStr = subString(str, left, right - 1);
   
if (isHeader(subStr) == 1) {
                  printf("<'%s',headerfile>\n", subStr);  
left=right;

}
else if (isKeyword(subStr) == 1)
                printf("<'%s',keyword>\n", subStr);
 
          else if (isInteger(subStr) == 1)
                printf("<'%s',integer>\n", subStr);

else if(isLiteral(subStr[0]))
printf("<'%s',literal>\n", subStr);
         else if ((validIdentifier(subStr) == 1) && (isDelimiter(str[right - 1]) == 0) )
{//printf("<'%c',identifier>\n", subStr[0]);
//printf("%d\n",left);;
//printf("%d\n",right);
//printf("<'%c',identifier>\n", subStr[right - 1]);
printf("<'%s',identifier>\n", subStr);
}
          else if (validIdentifier(subStr) == 0 && isDelimiter(str[right - 1]) == 0) {
if(isRealNumber(subStr)==1){
printf("<'%s',Real Number>\n", subStr);
}
        else{
               printf("<'%s',not identifier>\n", subStr);
  left = right;
}
}
   
         left = right;

        }
    }
    return;
}
 
void main()
{
FILE * fptr;
        int i,n,temp;
        char str[100],data[100];
        char fname[20]="test.txt";
        char str1,d='/';

char str2[]="end\n";

/* fptr = fopen (fname,"w");
for(i = 0;strcmp(str,str2);i++)
{
fgets(str, sizeof str, stdin);
fputs(str, fptr);
}
fclose (fptr);  */
fptr = fopen (fname, "r");  

if ( fptr != NULL )
{
        char line [ 128 ];
        while ( strcmp(fgets ( line, sizeof line, fptr ),str2) )
        {
for(i=0;i<100;i++)
{
data[i]='\0';
}
for(i = 0; line[i] != '\n' && line[i] != '/'; ++i)
    {
        data[i] = line[i];
    }
//printf("\n%s\n\n",data);
if(!strcmp(&data[0],&d) && !strcmp(&data[1] ,&d))
{}
else
lex(data);  
       
        }
    printf("\n\n");
    fclose (fptr);
}
   
}
