#include<stdio.h>
#include<string.h>

char productions[6][10] = {"E->E+T","E->T","T->T*F","T->F","F->(E)","F->a"};
char non_terminals[]={'E','T','F'};
char terminals[] = {'+','*','(',')','a','$'};
char leading[3][10]; // initialise to null
char trailing[3][10]; // initialise to null

int lead_union[3][3];
int trail_union[3][3];

char operator_table[6][6];

// Initialise Leadning and Trailing
void init(){
    for(int i=0;i<3;i++){
        for(int j=0;j<10;j++){
            leading[i][j] = '\0';
            trailing[i][j] = '\0';
        }
    }
}


// Check if character is a terminal
int checkTerminal(char ter){
    
    for(int i=0;i<5;i++){
        if(terminals[i] == ter){
            return 1;
        }
    }
    return 0;
}

int checkNonTer(char ch){
    for(int i=0;i<3;i++){
           if( non_terminals[i] == ch){
               return 1;
           }
    }

    return 0;
}

int search_nonter(char non){
    switch(non){
        case 'E' : return 0;
        case 'T' : return 1;
        case 'F' : return 2;
    }
}

int check_present(char arr[], char ch){
    for(int i=0; arr[i] != '\0';i++){
        if(arr[i] == ch){
            return 1;
        }
    }
    return 0;
}

void fun_union(char arr1[],char arr2[]){
    int final_index = strlen(arr1);
    for(int i=0;arr1[i] != '\0';i++){
        for(int j=0;arr2[j] != '\0';j++){
            if(check_present(arr1,arr2[j]) != 1){
                arr1[final_index++] = arr2[j];
            }
        }
    }
    arr1[final_index] = '\0';
}


void leading_trailing(){
    int lead_index,trail_index,final_index;
    for(int i=0;i<3;i++){
        lead_index=0;trail_index=0;
        for(int j=0;j<6;j++){
            
            if(non_terminals[i] == productions[j][0]){   // E->E+T  check only E and +  i.e 3 & 4 index
                 if(strlen(productions[j]) == 4 && !checkTerminal(productions[j][3])){   // E->T
                     lead_union[i][search_nonter(productions[j][3])] = 1;
                     trail_union[i][search_nonter(productions[j][3])] = 1;
                     continue;
                 }
                 
                 if( checkTerminal(productions[j][3])){  //F->(E)
                       leading[i][lead_index++] = productions[j][3];
                 }
                 else{   // E->E+T
                     leading[i][lead_index++] = productions[j][4];
                     if(productions[j][3] != non_terminals[i]){
                          lead_union[i][search_nonter(productions[j][3])] = 1;
                          
                     }
                 }
                 final_index = strlen(productions[j]) - 1;

                 if(checkTerminal(productions[j][final_index])){ //F->(E)
                     trailing[i][trail_index++] =  productions[j][final_index];
                 }
                 else{
                     trailing[i][trail_index++] = productions[j][final_index-1];
                     if( productions[i][final_index] != non_terminals[i]){
                         trail_union[i][search_nonter(productions[j][final_index])] = 1;
                     }
                 } 
            }
        }

        leading[i][lead_index] = '\0';
        trailing[i][trail_index] = '\0';

    }
    lead_union[0][2] = 1;
    trail_union[0][2] = 1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(lead_union[i][j] == 1){
                fun_union(leading[i],leading[j]);
            }
            if(trail_union[i][j] == 1){
                fun_union(trailing[i],trailing[j]);
            }
        }
    }


}

int ter_index(char ch){
    switch(ch){
        case '+': return 0;
        case '*': return 1;
        case '(': return 2;
        case ')': return 3;
        case 'a': return 4;
        default: return -1;

    }

    
}


void create_operator_table(){
    for(int i=0;leading[0][i] != '\0';i++){
        operator_table[5][ter_index(leading[0][i])] = '<';
    }

    for(int j=0;trailing[0][j] != '\0';j++){
        operator_table[ter_index(trailing[0][j])][5] = '>';
    }

    operator_table[ter_index('(')][ter_index(')')] = '=';

    for(int i=0;i<6;i++){
        for(int j=3;  productions[i][j] != '\0';j++){
            if(ter_index(productions[i][j])>= 0){
                if(checkNonTer(productions[i][j+1])){
                      int symbol = search_nonter(productions[i][j+1]);
                      for(int index = 0;leading[symbol][index] != '\0';index++){
                          operator_table[ter_index(productions[i][j])][ter_index(leading[symbol][index])] = '<';
                      }
                }
                if(checkNonTer(productions[i][j-1])){
                      int symbol = search_nonter(productions[i][j-1]);
                      for(int index = 0;trailing[symbol][index] != '\0';index++){
                          operator_table[ter_index(trailing[symbol][index] )][ter_index(productions[i][j])] = '>';
                      }
                }
            }
        }
    }
}

// void print_infomal(){
//     printf("\n");
//     for(int i=0;i<6;i++){
//         for(int j=0;j<6;j++){
//             printf("%c ",operator_table[i][j]);
//         }
//         printf("\n");
//     }
// }

void print_table(){
    printf("   ");
    for(int i=0;terminals[i] != '\0' ;i++){
        printf("%c  ",terminals[i]);
    }
    printf("\n");

    for(int i=0;i<6;i++){
        printf("%c  ",terminals[i]);
        for(int j=0;j<6;j++){
        printf("%c  ",operator_table[i][j]);
        }
        printf("\n");
    }
}
void print(){
    printf("Leading Matrix :- \n");
    for(int i=0;i<3;i++){
        for(int j=0;leading[i][j] != '\0';j++){
            printf("%c ",leading[i][j]);
        }
        printf("\n");
    }

    printf("Trailing Matrix :- \n");

     for(int i=0;i<3;i++){
        for(int j=0;trailing[i][j] != '\0';j++){
            printf("%c ",trailing[i][j]);
        }
        printf("\n");
    }

}

void main(){
    leading_trailing();
    print();
    create_operator_table();
    print_table();
    //print_infomal();
}



