#include<stdio.h>
#include<string.h>

// Global Variables
int nt,t,top=0;
char s[50],NT[10],T[10],l[10][10],tr[10][10],table[10][10];
char production[30][30] = {"E->E+T","E->T","T->T*F","T->F","F->(E)","F->a"};

//Input Function

int searchNonTerminal(char a)
{
 int i;
 for(i=0;i<nt;i++)
 {
    if(NT[i]==a)
    return i;
 }
 return -1;
}
int searchTerminal(char a)
{
 int i;
 for(i=0;i<t;i++)
 {
    if(T[i]==a)
    return i;
}
return -1;
}
void push(char a)
{
 s[top]=a;
 top++;
}
char pop()
{
 top--;
 return s[top];
}
void leading(int a,int b)
{
 if(l[a][b]=='f')
 {
    l[a][b]='t';
    push(T[b]);
    push(NT[a]);
 }
}
void trailing(int a,int b)
{
 if(tr[a][b]=='f')
 {
    tr[a][b]='t';
    push(T[b]);
    push(NT[a]);
 } 
}


void printTable(){
    printf(" ");
     for(int i=0;i<t+1;i++)
     {
         printf("   %c",T[i]);
     }
     printf("\n");
     for(int i=0;i<t;i++)
     {
         printf("%c",T[i]);
         for(int j=0;j<t;j++)
         {
             printf("   %c",table[i][j]);
         }
         printf("\n");
     }
}


void main()
{
 int i,s,k,j,n = 6;
 char b,c;

 nt=0;
 t=0;
 for(i=0;i<n;i++)
 {
 if((searchNonTerminal(production[i][0]))==-1)
 NT[nt++]=production[i][0];
 }
 for(i=0;i<n;i++)
 {
  for(j=3;j<strlen(production[i]);j++)
  {
   if(searchNonTerminal(production[i][j])==-1)
   {
     if(searchTerminal(production[i][j])==-1)
     T[t++]=production[i][j]; 
   }
  }
 }
 for(i=0;i<nt;i++)
 {
  for(j=0;j<t;j++)
    l[i][j]='f';
 }
 for(i=0;i<nt;i++)
 {
  for(j=0;j<t;j++)
    tr[i][j]='f'; 
 }
 for(i=0;i<nt;i++)
 {
  for(j=0;j<n;j++)
  {
   if(production[j][0]==NT[i])
   {
     if(searchTerminal(production[j][3])!=-1)
     leading(searchNonTerminal(production[j][0]),searchTerminal(production[j][3]));
     else
     {
      for(k=3;k<strlen(production[j]);k++)
      {
        if(searchNonTerminal(production[j][k])==-1)
        {
         leading(searchNonTerminal(production[j][0]),searchTerminal(production[j][k]));
         break;
        }
      }
    }
   }
  } 
 }
 while(top!=0)
 {
  b=pop();
  c=pop();
   for(s=0;s<n;s++)
  {
   if(production[s][3]==b)
   leading(searchNonTerminal(production[s][0]),searchTerminal(c));
  }
 }
 for(i=0;i<nt;i++)
 {
  printf("Leading[%c]\t{",NT[i]);
  for(j=0;j<t;j++)
  {
   if(l[i][j]=='t')
   printf("%c,",T[j]);
  }
  printf("}\n"); 
 }


 top=0;
 for(i=0;i<nt;i++)
 {
  for(j=0;j<n;j++)
  {
   if(production[j][0]==NT[i])
   {
    if(searchTerminal(production[j][strlen(production[j])-1])!=-1)
    trailing(searchNonTerminal(production[j][0]),searchTerminal(production[j][strlen(production[j])-1]));
    else
    {
     for(k=(strlen(production[j])-1);k>=3;k--)
     {
      if(searchNonTerminal(production[j][k])==-1)
       {
         trailing(searchNonTerminal(production[j][0]),searchTerminal(production[j][k]));
         break;
       }
     }
    }
   }
  }
 }
 while(top!=0)
 {
  b=pop();
  c=pop();
  for(s=0;s<n;s++)
  {
   if(production[s][3]==b)
   trailing(searchNonTerminal(production[s][0]),searchTerminal(c));
  }
 }
 for(i=0;i<nt;i++)
 {
  printf("Trailing[%c]\t{",NT[i]);
  for(j=0;j<t;j++)
  {
  if(tr[i][j]=='t')
  printf("%c,",T[j]);
  }
  printf("}\n");
 }
 t++;
 T[t-1]='$';
 for(i=0;i<n;i++)
 {
     for(j=3;j<strlen(production[i])-1;j++)
     {
         if(searchTerminal(production[i][j])!=-1 && searchTerminal(production[i][j+1])!=-1)
         {
             table[searchTerminal(production[i][j])][searchTerminal(production[i][j+1])]='=';
         }
         if((j<=strlen(production[i])-2) && (searchTerminal(production[i][j])!=-1) && (searchTerminal(production[i][j+2])!=-1))
         {
             table[searchTerminal(production[i][j])][searchTerminal(production[i][j+2])]='=';
         }
         if(searchTerminal(production[i][j])!=-1 && searchNonTerminal(production[i][j+1])!=-1)
         {
             for(k=0;k<t;k++)
             {
                 if(l[searchNonTerminal(production[i][j+1])][k]=='t')
                   table[searchTerminal(production[i][j])][k]='<';
             }
         }
         if(searchNonTerminal(production[i][j])!=-1 && searchTerminal(production[i][j+1])!=-1)
         {
             for(k=0;k<t;k++)
             {
                 if(tr[searchNonTerminal(production[i][j])][k]=='t')
                   table[k][searchTerminal(production[i][j+1])]='>';
             }
         }
     }
 } 
for(i=0;i<t;i++)
 {
     if(l[searchNonTerminal('E')][i]=='t')
     {
         table[t-1][i]='<';
     }
     if(tr[searchNonTerminal('E')][i]=='t')
     {
         table[i][t-1]='>';
     }
 }



 printTable();
// //printing table
//      printf(" ");
//      for(i=0;i<t+1;i++)
//      {
//          printf("   %c",T[i]);
//      }
//      printf("\n");
//      for(i=0;i<t;i++)
//      {
//          printf("%c",T[i]);
//          for(j=0;j<t;j++)
//          {
//              printf("   %c",table[i][j]);
//          }
//          printf("\n");
//      }
}
