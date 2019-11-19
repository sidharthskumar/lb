//nfatodfa

#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int a[10];
}st1;
int isIn(int *a,int key){
	for(int i=0;a[i]!=-1;i++){
		if(key==a[i]){
			return 1;
		}
	}
	return 0;
}
void copyarr(int *a,int *b){
	int i=0;
	a[0]=-1;
	for(i=0;b[i]!=-1;i++){
		a[i]=b[i];
	}
	a[i]=-1;
}
void unite(int *a,int k){
	int i;
	for(i=0;a[i]!=-1;i++){
		if(a[i]==k){
			return;
		}
	}
	a[i]=k;
	a[i+1]=-1;
	
}
int isUnique(st1 *a,st1 *b[],int n){
	int i,j,*temp,f=0,len;
	if(a->a[0]==1 && a->a[1]==-1){
		return 0;
	}	
	for(i=0;i<n;i++){		
		temp=b[i]->a;
		f=0;
		if(a->a[0]==-1 && temp[0]==-1){
			//printf("TEster1");
			return 0;
		}		
		for(j=0;a->a[j]!=-1;j++){
			if(isIn(temp,a->a[j])){
				continue;
			}
			f=1;
			break;
		}
		if(f==0){
			for(len=0;temp[len]!=-1;len++);
			if(len==j){
				//printf("TEster1");
				return 0;
			}
			
		}
	}
	return 1;
}
void main(){
	//int *q[100];	
	int i,j,temp,n,ni,k,rsize,head=0,tail=0,count=0,newind;
	st1 mat[12][10],opstates[12],opresults[12][10],*sttemp,*q[100];
	char ilist[100];
	printf("Enter the number of states in NFA::");
	scanf("%d",&n);
	printf("Enter number of inputs::");
	scanf("%d",&ni);
	printf("Enter the input characters::\n");
	for(i=0;i<ni;i++){
		scanf("\n%c",&ilist[i]);
	}
	for(i=0;i<n;i++){
		for(j=0;j<ni;j++){
			printf("Enter outputs of d(%d,%c)\n",i+1,ilist[j]);
			
			k=0;
			while(1){
				scanf("\n%d",&temp);
				if(temp==-1){
					mat[i][j].a[k]=-1;
					break;
				}
				mat[i][j].a[k]=temp;
				k+=1;				
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<ni;j++){
			printf("\nF(%d,%c) = {",i+1,ilist[j]);
			for(k=0;mat[i][j].a[k]!=-1;k++){
				printf("%d ",mat[i][j].a[k]);
			
			}
			printf("}");
		}
	}
	opstates[0].a[0]=1;
	opstates[0].a[1]=-1;
	for(i=0;i<ni;i++){
		copyarr(opresults[0][i].a,mat[0][i].a);
		if(isUnique(&(opresults[0][i]),q,tail)){
			q[tail]=&(opresults[0][i]);
			tail+=1;
		}
	}
	count=1;
	while(head<tail){
		printf("%d %d\n",head,tail);
		sttemp=q[head];
		head+=1;
		copyarr(opstates[count].a,sttemp->a);		
		for(i=0;i<ni;i++){
			opresults[count][i].a[0]=-1;
			for(j=0;sttemp->a[j]!=-1;j++){
				newind=sttemp->a[j]-1;								
				for(k=0;mat[newind][i].a[k]!=-1;k++){					
					unite(opresults[count][i].a,mat[newind][i].a[k]);
					//printf("%d ",mat[newind][i].a[k]);
				}				
				
			}
			if(isUnique(&(opresults[count][i]),q,tail)){
				
				q[tail]=&(opresults[count][i]);
				tail+=1;
			}			

		}
		count+=1;		
	}
	printf("\n\n");
	for(i=0;i<count;i++){		
		for(j=0;j<ni;j++){
			printf("D(");
			for(k=0;opstates[i].a[k]!=-1;k++){
				printf("%d,",opstates[i].a[k]);			
			}
			if(opstates[i].a[0]==-1){
				printf("dead state,");
			}		
			printf("%c) = ",ilist[j]);
			if(opresults[i][j].a[0]==-1){
				printf("dead state \n");
				continue;
			}
			printf("{");
			for(k=0;opresults[i][j].a[k]!=-1;k++){
				printf("%d ",opresults[i][j].a[k]);
			}
			printf("}\n");
		}
		printf("\n\n");		
	}	
	
}