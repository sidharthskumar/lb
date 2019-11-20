#include<stdio.h>
#include<string.h>
char productions[100][100]={
			    {'E','-','>','E','+','E','\0'},
			    {'E','-','>','E','*','E','\0'},
			    {'E','-','>','i','\0'},	         				   
			    {'E','-','>','(','E',')','\0'}
			   };
char handle[100][100]={{'E','+','E','\0'},
			{'E','*','E','\0'},
			{'i','\0'},
			{'(','E',')','\0'}
			};
int top=1;
void strreplace(char string[], char search[], char replace[]);
char search_handle(char handle[100]){
	for(int i=0;i<4;i++){
		char hi[100];
		strcpy(hi,productions[i]+3);
		if(strcmp(hi,handle)==0){
			return productions[i][0];
		}
	}
return '0';
}
void display(char stack[100]){
	
    
   
		printf("\n%s",stack);
}
void reduce(char stack[100]){
	//int i=top-1;
	//printf("\n %d",i);
	//int k=top-1;
	/*while(i>0&&top>1){
		
		char buf[100];int y=0;
		for(int pp=i;pp<=k;pp++){
			buf[y++]=stack[pp];

		}
		buf[y]='\0';
		char p=search_handle(buf);
		//printf("\n %s  %c",buf,p);
		if(p!='0'){
			//printf("\n %c",p);
			printf("\n %s  ",buf);
			top-=y;
			top++;
			stack[top-1]=p;
			i=top-1;
		}
		else {i--;}
		//printf("t %d ",top);
		
		
			
		
	}*/
	stack[top]='\0';
	for(int i=0;i<4;i++){
			strreplace(stack,handle[i],"E");
			
	}
	top=strlen(stack);
	//display(stack);
	
		
}

void parse(char expr[100]){
	char stack[100];
	int cur=0;
	
	stack[0]='$';
 
	while(cur<strlen(expr)){
		//shift
		//printf("hu");
		stack[top++]=expr[cur++];
		//reduce
		reduce(stack);
		//display(stack);
		
	}
	//printf("%c",stack[top-1]);
	//display(stack);
	if(stack[0]=='$'&&stack[1]=='E'&&stack[2]=='$')
	//if(stack[top-1]=='E' )
		printf("\n Accepted");
	else
		printf("\n Rejected");
}

void main(){
         
	char expr[100];
          printf("\ngrammer is \nE->E+E\nE->E*E\nE->(E)\nE->id\n"); 
         printf("Input string :\n");
         scanf("%s",expr);
          
	 printf("--------------------------------------------------------\nyou have entred the string %s\n",expr);
	int n=strlen(expr);
	expr[n]='$';
	expr[n+1]='\0';
	
	
	parse(expr);
		
}

void strreplace(char string[], char search[], char replace[]){
    char buffer[100];
    char*p = string;
    while((p=strstr(p, search))){
        strncpy(buffer, string, p-string);
        buffer[p-string] = '\0'; 
        strcat(buffer, replace);
        strcat(buffer, p+strlen(search));
        strcpy(string, buffer);
        p++;
    }
} 

