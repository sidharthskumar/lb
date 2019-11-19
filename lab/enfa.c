#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct{

	int i,f;
	char inp;
	
}triplet;

typedef struct{

	int state[10];
	
}st1;

void ddfs(int a,triplet *triplets, int *visited,int n,int n2,int *res,int *pos){
	
	res[*(pos)]=a;
	(*pos)++;
	visited[a]=1;
	
	for(int i=0;i<n;i++){
		if(triplets[i].i==a && triplets[i].inp=='e'){
			if(visited[triplets[i].f]==0){
				ddfs(triplets[i].f,triplets,visited,n,n2,res,pos);
			}
		}
	}
}

int isIn(int a,int arr[100],int n){
	
	for(int i=0;i<n;i++){
		if(arr[i]==a){
			return 1;
		}
	}
	return 0;
	
}

void getUnion(int *a,int b){	
	int i;
	
	for(i=0;a[i]!=-1;i++){
		if(a[i]==b){
			return;
		}
	}
	a[i]=b;
	a[i+1]=-1;
	
}

void main(){
	triplet a[100];
	st1 finmat[10][10];
	int temp,i=0,j,n2,n,stlist[100],visited[100],eclos[15][15],ni,k=0,t1=0,t2=0,x=0,y=0;
	char ilist[5];
	printf("Enter number of inputs::");
	scanf("%d",&ni);
	printf("Enter the input characters::\n");
	
	for(i=0;i<ni;i++){
		scanf("\n%c",&ilist[i]);
	}
	
	printf("Enter transition function elements(use 'e' for epsilon, enter -1 for initial state to end input)\n\n");
	
	i=0;
	do{
		printf("Initial state:: ");
		scanf("%d",&temp);
		if(temp!=-1)
			a[i].i=temp;
		else
			break;
		printf("Input:: ");
		scanf("\n%c",&(a[i].inp));
		printf("Final State:: ");
		scanf("%d",&(a[i].f));
		i++;
	}while(1);
	
	n=i;
	for(i=0;i<n;i++){
		printf("F(%d,%c) = %d\n",a[i].i,a[i].inp,a[i].f);
	}
	
	j=0;
	for(i=0;i<n;i++){
		if(!isIn(a[i].i,stlist,j)){
			stlist[j]=a[i].i;
			j+=1;
		}
		if(!isIn(a[i].f,stlist,j)){
			stlist[j]=a[i].f;
			j+=1;
		}
	}
	
	n2=j;
	for(i=0;i<n2;i++){
		for(j=0;j<n2;j++){
			visited[stlist[j]]=0;
		}		
		j=0;
		ddfs(stlist[i],a,visited,n,n2,eclos[stlist[i]],&j);
		eclos[stlist[i]][j]=-1;		
	}

	for(i=0;i<n2;i++){
		printf("\n%d:: ",stlist[i]);
		for(j=0;eclos[stlist[i]][j]!=-1;j++){
			printf("%d ",eclos[stlist[i]][j]);
		}
	}
	
	for(i=0;i<n2;i++){
		for(j=0;j<ni;j++){
			finmat[stlist[i]][j].state[0]=-1;		
			for(k=0;eclos[stlist[i]][k]!=-1;k++){
				t1=eclos[stlist[i]][k];
				for(x=0;x<n;x++){
					if(a[x].i==t1 && a[x].inp==ilist[j]){
						t2=a[x].f;
						for(y=0;eclos[t2][y]!=-1;y++){
							getUnion(finmat[stlist[i]][j].state,eclos[t2][y]);
						}
					}
				}
			}
		}		
	}
	
	printf("\n\n\n\n\n");
	
	for(i=0;i<n2;i++){		
		for(j=0;j<ni;j++){
			printf("D(%d,%c)= ",stlist[i],ilist[j]);
			for(k=0;finmat[stlist[i]][j].state[k]!=-1;k++){
				printf("%d ",finmat[stlist[i]][j].state[k]);
			}
			printf("\t");
		}
		printf("\n");
	}
}
