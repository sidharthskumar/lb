#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char a[20],action[10],input[20],stk[20];
int i,j,k,n,z;
void check();

int main(){

  printf("\ngrammer is \nE->E+E\nE->E*E\nE->(E)\nE->id\n");    // Production
  printf("Input string :\n");
  scanf("%s",a);
  printf("you have entred the string %s\n",a);
  n = strlen(a);
  printf("\n%s\n",input);
  //printf("%d\n",n);
 // printf("STACK\tINPUT\t\tACTION\t\n");
  strcpy(input,a);

  for(i=0,j=0,k=0;input[i]!='\0';i++,j++,k++){
    if(input[i] == 'i' && input[i+1] == 'd'){
      stk[j] = input[i];
      stk[j+1] = input[i+1];
      //stk[j+2] = '\0';
      input[i] = ' ';
      input[i+1] = ' ';
      //printf("$%s\t%s$\tShift->id\n",stk,input);
      check();
     
    }
    else {
      if(input[i] == '+' ||input[i] == '*' ||input[i] == '(' ||input[i] == ')'){
      stk[j] = input[i];
      //printf(" input here is %c\n",input[i]);
      input[i] = ' ';
      stk[j+1] = ' ';
      if(stk[j] == ')'){
        check();
      }
     // printf("$%s\t%s$\tShift->%c\n",stk,input,stk[j]);
      }
    }
  }
  //printf("Elements in stack are %s",stk);
  if(!strcmp(stk,"E\0"))
{
//printf("\nAccepted");

}
  else
//printf("\nNot Accepted");
  return 0;
}


void check(){
  int flag=1;
  if(flag=1){
  for(z=0;z<n;z++){
    flag=0;
    if(stk[z] == 'i' && stk[z+1] == 'd'){
      //reducing id to E
      flag=1;
      stk[z] = 'E';
      stk[z+1] = ' ';
    //  printf("$%s\t%s$\tReduce to E by E->id\n",stk,input);
      j--;
    }
    if(stk[z] == 'E' && stk[z+1] == '+' && stk[z+2] == 'E'){
      //production E->E+E
      flag=1;
      stk[z] = 'E';
      stk[z+1] = ' ';
      stk[z+2] = ' ';
     // printf("$%s\t%s$\tReduce to E by E->E+E\n",stk,input);
      i=i-2;
    }
    if(stk[z] == 'E' && stk[z+1] == '*' && stk[z+2] == 'E'){
      //production E->E*E
      flag=1;
      stk[z] = 'E';
      stk[z+1] = ' ';
      stk[z+2] = ' ';
     // printf("$%s\t%s$\tReduce to E by E->E*E\n",stk,input);
      i=i-2;
    }
    if(stk[z] == '(' && stk[z+1] == 'E' && stk[z+2] == ')'){
      //production E->(E)
      flag=1;
      stk[z] = 'E';
      stk[z+1] = ' ';
      stk[z+2] = ' ';
     // printf("$%s\t%s$\tReduce to E by E->(E)\n",stk,input);
      i=i-2;
    }
  }
}
}
