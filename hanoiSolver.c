#include <stdio.h>
#include <stdlib.h>

int i;

struct Move {//struct gia ta exw to move
    char source;
    char destination;
};

int header(int a){

    printf("\n");

    for(i = 0 ; i < a+1 ; i++){
        printf(" ");
    }

    printf("A");

    for(i = 0 ; i < 2*a ; i++){
        printf(" ");
    }

    printf("B");

    for(i = 0 ; i < 2*a ; i++){
        printf(" ");
    }

    printf("C\n\n");

    for(i = 0 ; i < a + 1 ; i++){
        printf(" ");
    }

    printf("|");

    for(i = 0 ; i < 2*a ; i++){
        printf(" ");
    }
    printf("|");

    for(i = 0 ; i < 2*a ; i++){
        printf(" ");
    }

    printf("|");

    for(i = 0 ; i < 2*a ; i++){
        printf(" ");
    }

    return 0 ;
}

int print_hanoi(int b , char hanoi[b][6 * b + 3]){

    header(b);

    for (int i = 0; i < b; i++) {
            printf("\n");
            for (int k = 0; k < 6 * b + 3; k++) {
                printf("%c", hanoi[i][k]);
            }
    }

    printf("\n");

    for(i = 0 ; i< 6 *b + 5 ; i++){
        printf("-");
    }

    printf("\n \n");
}

void solver(int n, char source, char aux, char dest, struct Move **moves, int *moveCount){//lunei to hanoi kai apothikeuei ta moves
    
    if (n == 1) {//gia ena disko

        *moves = realloc(*moves, (*moveCount + 1) * sizeof(struct Move));//1d array gia to move

        (*moves)[*moveCount].source = source;
        (*moves)[*moveCount].destination = dest;
        (*moveCount)++;
        return;
    }

    //epomenos diskos sto aux
    solver(n - 1, source, dest, aux, moves, moveCount);

    *moves = realloc(*moves, (*moveCount + 1) * sizeof(struct Move));

    //move tous upoloipous apo source sto dest
    (*moves)[*moveCount].source = source;
    (*moves)[*moveCount].destination = dest;
    (*moveCount)++;

    //move n-1 apo aux ston dest me aux authn thn fora ton source
    solver(n - 1, aux, source, dest, moves, moveCount);
}

int main(int argc, char *argv[]) {

    int b  ;
    //gia to ./a.exe 3
    int input = atoi(argv[1]); 
    b = input;
    //gia to ./a.exe 3

    struct Move *moves = NULL;
    int moveCount = 0;

    //INITIALIZE TOWER OF HANOI 
    char hanoi[b][6 * b + 3];

    for (int k = 0; k < b; k++) {
        
        for (int i = 0; i < 1 + b; i++) {
            hanoi[k][i] = ' ';
        }
        
        for (int i = b + 2; i < 3 * b + 2; i++) {
            hanoi[k][i] = ' ';
        }

        hanoi[k][3 * b + 2] = '|';

        for (int i = 3 * b + 3; i < 5 * b + 3; i++) {
            hanoi[k][i] = ' ';
        }

        hanoi[k][5 * b + 3] = '|';

        for (int i = 5 * b + 4 ; i <= 6 * b + 3 ; i++) {
            hanoi[k][i] = ' ' ;
        }

        int a = (k + 1) * 2;
        int ela_na_deis = k +48 ;

        if(ela_na_deis < 57){
        
            for(i  = 0 ; i < a - 1  ; i++){  
                hanoi[k][b + 1 - k + i] = k + 49;
            }

        }
        else{
            for (int i = 0; i < 19; i++) {
                hanoi[k][b + 1 - k + i] = '1' - i % 2;  //gia to 10
            }   
        }
        //kai kala gia na mhn exei perita kena alla den prepei na douleuei swsta
        for (int i = 6 * b + 4; i <= 6 * b + 3; i++) {
        hanoi[k][i] = '\0';
    }
    }
    //INITIALITATION FINISH 

    print_hanoi(b,hanoi);//initial print

    // call the solver function
    solver(b, 'A', 'B', 'C', &moves, &moveCount);
    
    //tower cords
    int tower_a = b + 1 ;
    int tower_b = 3 * b + 2;
    int tower_c = 5 * b + 3; 
    //tower cords

    //gia ta moves
    for (int i = 0; i < moveCount; i++){

        printf("\n%c -> %c\n", moves[i].source, moves[i].destination);

        // swap gia A -> B
        if (moves[i].source == 'A' && moves[i].destination == 'B') {
          for(int k = 0 ; k < b  ; k++){
            if(hanoi[k][tower_a] != '|'){
                for(int j = 0 ; j <= b - 1 ; j++){
                    if(hanoi[b - 1 - j][tower_b] == '|'){
                        //swap
                        for (int m = 0; m < ((k + 1) * 2) - 1; m++) {
                            if (hanoi[k][tower_a - k + m] != 'N') {
                                char temp = hanoi[k][tower_a - k + m];
                                hanoi[k][tower_a - k + m] = hanoi[b - 1 - j][tower_b - k + m];
                                hanoi[b - 1 - j][tower_b - k + m] = temp;
                            }
                        }                        
                        break;                         
                    }
                }break;
            }
          }
        }
        
        //swap gia A -> C
        if (moves[i].source == 'A' && moves[i].destination == 'C') {
          for(int k = 0 ; k < b  ; k++){
            if(hanoi[k][tower_a] != '|'){
                for(int j = 0 ; j <= b - 1 ; j++){
                    if(hanoi[b - 1 - j][tower_c] == '|'){
                        //swap
                        for (int m = 0; m < ((k + 1) * 2) - 1; m++) {
                            if (hanoi[k][tower_a - k + m] != 'N') {
                                char temp = hanoi[k][tower_a - k + m];
                                hanoi[k][tower_a - k + m] = hanoi[b - 1 - j][tower_c - k + m];
                                hanoi[b - 1 - j][tower_c - k + m] = temp;
                            }
                        }
                        break;                         
                    }
                }break;
            }
          }
        }
        //swap gia B -> C
        if (moves[i].source == 'B' && moves[i].destination == 'C') {
          for(int k = 0 ; k < b  ; k++){
            if(hanoi[k][tower_b] != '|'){
                for(int j = 0 ; j <= b - 1 ; j++){
                    if(hanoi[b - 1 - j][tower_c] == '|'){
                        //swap
                        for (int m = 0; m < ((k + 1) * 2) - 1; m++) {
                            if (hanoi[k][tower_b - k + m] != 'N') {
                                char temp = hanoi[k][tower_b - k + m];
                                hanoi[k][tower_b - k + m] = hanoi[b - 1 - j][tower_c - k + m];
                                hanoi[b - 1 - j][tower_c - k + m] = temp;
                            }
                        }
                        break;                         
                    }
                }break;
            }
          }
        }
        //swap gia B -> A 
        if (moves[i].source == 'B' && moves[i].destination == 'A') {
          for(int k = 0 ; k < b  ; k++){
            if(hanoi[k][tower_b] != '|'){
                for(int j = 0 ; j <= b - 1 ; j++){
                    if(hanoi[b - 1 - j][tower_a] == '|'){
                        //swap
                       for (int m = 0; m < ((k + 1) * 2) - 1; m++) {
                            if (hanoi[k][tower_b - k + m] != 'N') {
                                char temp = hanoi[k][tower_b - k + m];
                                hanoi[k][tower_b - k + m] = hanoi[b - 1 - j][tower_a - k + m];
                                hanoi[b - 1 - j][tower_a - k + m] = temp;
                            }
                        }
                        break;                         
                    }
                }break;
            }
          }
        }
        //swap gia C -> A
        if (moves[i].source == 'C' && moves[i].destination == 'A') {
          for(int k = 0 ; k < b  ; k++){
            if(hanoi[k][tower_c] != '|'){
                for(int j = 0 ; j <= b - 1 ; j++){
                    if(hanoi[b - 1 - j][tower_a] == '|'){
                        //swap
                        for (int m = 0; m < ((k + 1) * 2) - 1; m++) {
                            if (hanoi[k][tower_c - k + m] != 'N') {
                                char temp = hanoi[k][tower_c - k + m];
                                hanoi[k][tower_c - k + m] = hanoi[b - 1 - j][tower_a - k + m];
                                hanoi[b - 1 - j][tower_a - k + m] = temp;
                            }
                        }
                        break;                         
                    }
                }break;
            }
          }
        }
        //swap gia C -> B
        if (moves[i].source == 'C' && moves[i].destination == 'B') {
          for(int k = 0 ; k < b  ; k++){
            if(hanoi[k][tower_c] != '|'){
                for(int j = 0 ; j <= b - 1 ; j++){
                    if(hanoi[b - 1 - j][tower_b] == '|'){
                        //swap
                        for (int m = 0; m < ((k + 1) * 2) - 1; m++) {
                            if (hanoi[k][tower_c - k + m] != 'N') {
                                char temp = hanoi[k][tower_c - k + m];
                                hanoi[k][tower_c - k + m] = hanoi[b - 1 - j][tower_b- k + m];
                                hanoi[b - 1 - j][tower_b - k + m] = temp;
                            }
                        }
                        break;                         
                    }
                }break;
            }
          }
        }
        //print to hanoi se kathe move
        print_hanoi(b ,hanoi);
    }
    free(moves);
    return 0;
}
