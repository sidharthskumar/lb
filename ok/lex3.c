#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int isKeyword(char *tok){
	if(strcmp(tok,"void")==0 || strcmp(tok,"int")==0 || strcmp(tok,"float")==0 || strcmp(tok,"include")==0 || strcmp(tok,"define")==0){
		return 1;
	}
	return 0;
}
int isDelim(char *tok){
	if(tok[0]=='{' || tok[0]=='}' || tok[0]==';' || tok[0]=='(' || tok[0]==')'){
		return 1;
	} 
	return 0;
}
int isOp(char *tok){
	if(tok[0]=='+' || tok[0]=='-' || tok[0]=='/' || tok[0]=='*' || tok[0]=='=' || tok[0]==',' || tok[0]=='&' || tok[0]=='<' || tok[0]=='>'){
		return 1;
	}
	return 0;
} 
int isNum(char *tok){
	for(int i=0;tok[i]!='\0';i++){
		if(!isdigit(tok[i]) && tok[i]!='.'){
			return 0;
		}
	}
	return 1;
}
int isVar(char *tok){
	int f=1;
	if(isdigit(tok[0])){
		return 0;
	}	
	for(int i=0;tok[i]!='\0';i++){
		if(isdigit(tok[0]) && !isalpha(tok[0]) && tok[0]!='_'){
			return 0;
		}
	}
	return 1;

}
int nextWord(char *tok,char *s,int ind){
	int i=ind,j=0;
	while(s[i]!='\0'){
		
		if(s[i]=='"'){
			do{
				tok[j++]=s[i++];
			}while(s[i]!='"');
			tok[j]='"';
			tok[j+1]='\0';
			return i;
			
		}
		
		if(s[i]==' '){
			if(i==ind){
				tok[j]='\0';
				return i;
			}
			tok[j]='\0';
			return i-1;
		}
		if(s[i]==','){			
			if(j==0){				
				tok[j]=',';
				tok[j+1]='\0';
				return i;
			}
			else{				
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='#'){			
			if(j==0){				
				tok[j]='#';
				tok[j+1]='\0';
				return i;
			}
			else{				
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]==';'){
			if(i==ind){
				tok[j]=';';
				tok[j+1]='\0';
				return i;
			}
			else{
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='+'){
			if(i==ind){
				tok[j]='+';
				tok[j+1]='\0';
				return i;
			}
			else{
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='='){
			if(i==ind){
				tok[j]='=';
				tok[j+1]='\0';
				return i;
			}
			else{
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='>' || s[i]=='<'){
			if(i==ind){
				tok[j]=s[i];
				tok[j+1]='\0';
				return i;
			}
			else{
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='('){
			if(i==ind){
				tok[j]='(';
				tok[j+1]='\0';
				return i;
			}
			else{
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]==')'){
			if(i==ind){
				tok[j]=')';
				tok[j+1]='\0';
				return i;
			}
			else{
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='&'){
			if(i==ind){
				tok[j]='&';
				tok[j+1]='\0';
				return i;
			}
			else{
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='\n'){
			if(i==ind){				
				tok[j]='\0';
				return i;
			}
			else{				
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='{' || s[i]=='}'){
			if(i==ind){				
				tok[j]=s[i];
				tok[j+1]='\0';
				return i;
			}
			else{
				tok[j]='\0';
				return i-1;
			}
		}
		if(s[i]=='\0'){
			if(i==ind){				
				tok[j]='\0';				
				return -2;
			}
			else{					
				tok[j]='\0';
				return i-1;
			}
		}
		
		
		tok[j]=s[i];
		j+=1;
		i+=1;		 
	
	}
}
void main(){
	
	
	FILE *fp;
	int i,comment=0;
	char file[10000]="",ch[2],tok[100];
	fp=fopen("input.c","r");
	ch[1]='\0';
	i=0;	
	while((ch[0] = fgetc(fp)) != EOF){		
		strcat(file,ch);
		i+=1;
	}		
	file[i]='\0';
	i=0;
	while(file[i]!='\0'){					
		if(file[i]=='/'){//single line comment
			if(file[i+1]=='/'){				
				while(file[i]!='\n' && file[i]!='\0')
					i++;
			continue;
			}
			
		}
		if(file[i]=='/' && file[i+1]=='*'){//multiline comment			
			while(!(file[i]=='*' && file[i+1]=='/') && file[i]!='\0'){				
				i++;
			}
			i+=2;			
			continue;
		}		
		i=nextWord(tok,file,i);
		i++;
		if(1){
			if(tok[0]!='\0' && tok[0]!='\n'){
				if(tok[0]=='#'){
					printf("<%s,preprocessorDirective>\n",tok);
					continue;
				}	
				if(tok[0]=='"'){
					printf("<%s,literal>\n",tok);
					continue;
				}
				if(isNum(tok)){
					printf("<%s,literal>\n",tok);
					continue;	
				}
				if(isDelim(tok)){
					printf("<%s,delimiter>\n",tok);
					continue;
				}	
				if(isOp(tok)){
					printf("<%s,operator>\n",tok);
					continue;
				}
				if(isKeyword(tok)){
					printf("<%s,keyword>\n",tok);					
					continue;
				}
				if(isVar(tok)){
					printf("<%s,identifier>\n",tok);
					continue;
				}
				printf("<%s,ErrorToken>\n",tok);		
			
				}
			}
	}
}
      
