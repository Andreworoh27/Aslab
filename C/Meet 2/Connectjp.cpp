#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct winner{
    char name[50];
    int move=0;
}Player[100];

char map[7][11];
int move=0;
int Player_idx=0;

void ResetMap(){
    for(int i=0;i<6;i++){
        for (int j=0;j<10;j++){
            map[i][j]=' ';
        }
        map[i][10]='\0';
    }
    
}

void Printmap(){
    int idx=0;
    for (int i=0;i<14;i++){
        if(i%2==0){
            puts("-----------------------------------------");
        }
        else{
            if(i==13){
                for(int j=0;j<10;j++){
                    printf("| %d ",j);
                }
                printf("|\n");
                continue;
            }
            for(int j=0;j<10;j++){
                printf("| %c ",map[idx][j]);
            }
            printf("|\n");
            idx++;
        }
    }
}

int generate_random(int lower, int upper){
    srand(time(0)); 
    return (rand() % (upper - lower + 1)) + lower;
}

void npc(){
    int input = generate_random(0,9);
    int idx=5;
    while(true){
        if(map[idx][input]==' '){
            map[idx][input] = 'P';
            break;
        }
        else{
            idx--;
        }
    }
}

int winner(){
    int counter_j=0,counter_p=0;
    for(int i=0;i<10;i++){
        for (int j=0;j<6;j++){
            // player win
            // vertikal
            if((map[j][i]=='J' && map[j+1][i]=='J' && map[j+2][i]=='J' && map[j+3][i]=='J') || (map[j][i]=='J' && map[j-1][i]=='J' && map[j-2][i]=='J' && map[j-3][i]=='J')){
                return 1;
            }
            // horizontal
            else if ((map[j][i]=='J' && map[j][i+1]=='J' && map[j][i+2]=='J' && map[j][i+3]=='J') || (map[j][i]=='J' && map[j][i+1]=='J' && map[j][i+2]=='J' && map[j][i+3]=='J')){
                return 1;
            }
            // diagonal kanan atas
            else if(map[j][i]=='J' && map[j-1][i+1]=='J' && map[j-2][i+2]=='J' && map[j-3][i+3]=='J'){
                return 1;
            }
            // digaonal kanan bawah
            else if(map[j][i]=='J' && map[j+1][i+1]=='J' && map[j+2][i+2]=='J' && map[j+3][i+3]=='J'){
                return 1;
            }
            // diagonal kiri atas 
            else if(map[j][i]=='J' && map[j-1][i-1]=='J' && map[j-2][i-2]=='J' && map[j-3][i-3]=='J'){
                return 1;
            }
            // diagonal kiri bawah
            else if(map[j][i]=='J' && map[j-1][i+1]=='J' && map[j-2][i+2]=='J' && map[j-3][i+3]=='J'){
                return 1;
            }

            //npc win
            if((map[j][i]=='P' && map[j+1][i]=='P' && map[j+2][i]=='P' && map[j+3][i]=='P') || (map[j][i]=='P' && map[j-1][i]=='P' && map[j-2][i]=='P' && map[j-3][i]=='P')){
                return 1;
            }
            // horizontal
            else if ((map[j][i]=='P' && map[j][i+1]=='P' && map[j][i+2]=='P' && map[j][i+3]=='P') || (map[j][i]=='P' && map[j][i+1]=='P' && map[j][i+2]=='P' && map[j][i+3]=='P')){
                return 1;
            }
            // diagonal kanan atas
            else if(map[j][i]=='P' && map[j-1][i+1]=='P' && map[j-2][i+2]=='P' && map[j-3][i+3]=='P'){
                return 1;
            }
            // digaonal kanan bawah
            else if(map[j][i]=='P' && map[j+1][i+1]=='P' && map[j+2][i+2]=='P' && map[j+3][i+3]=='P'){
                return 1;
            }
            // diagonal kiri atas 
            else if(map[j][i]=='P' && map[j-1][i-1]=='P' && map[j-2][i-2]=='P' && map[j-3][i-3]=='P'){
                return 1;
            }
            // diagonal kiri bawah
            else if(map[j][i]=='P' && map[j-1][i+1]=='P' && map[j-2][i+2]=='P' && map[j-3][i+3]=='P'){
                return 1;
            }
        }
        counter_j=0,counter_p=0;
    }
    return -1;
}

void play(){
    Printmap();
    int input;
    do{
        puts("Input col to fill (0-9)");
        printf(">> ");
        scanf("%d",&input);getchar();
        if(input<0 || input>9){
            puts("input must between 0 - 9");
        }
    }while(input<0 || input>9);
    
    int idx=5;
    while(true){
        if(map[idx][input]==' '){
            map[idx][input] = 'J';
            break;
        }
        else{
            idx--;
        }
    }
    npc();
    int win = winner();
    move++;
    if(win == 1){
        Printmap();
        puts("Congratulations, you win! Press enter to continue");getchar();
        char name[91];
        do{
            printf("(Input Name (5-90 chars|may not only contain whitespace)) >> ");
            char temp[1000];
            strcpy(temp,"\0");
            scanf("%[^\n]",temp);getchar();
            int space=0;
            bool lolos = false;
            for(int i=0;temp[i]!='\0';i++){
                if(temp[i]==' '){
                    space++;
                }
            }
            if(space>4){
                lolos=true;
            }
            if(!(lolos == true|| strlen(temp)<5 || strlen(temp)>90)){
                strcpy(name,temp);
                break;
            }
        }while(true);
        strcpy(Player[Player_idx].name,name);
        Player[Player_idx].move=move;
        Player_idx++;
        move=0;
        return;
    }
    else if (win == 0){
        puts("you lose, press enter to continue...");getchar();
        return;
    }
    else{
        play();
    }
}

void Scoreboard(){
    if(Player_idx==0){
        puts("There is no score yet.");
        puts("Press enter to continue...");getchar();
        return;
    }
    puts("| Player name                                                     |  Moves |");
    puts("|--------------------------------------------------------------------------|");
    for(int i=0;i<Player_idx;i++){
        printf("| %-63s |   %d    |\n",Player[i].name,Player[i].move);
    }
}

void menu(){
    puts("Welcome to Connect JP, what do you want to do?");
    puts("1. Play");
    puts("2. How to Play");
    puts("3. Scoreboard");
    puts("4. Exit");
    printf(">> ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        ResetMap();
        play();
        menu();
        break;
    case 2:
        printf("Connect JP is a board game, in which the you will play with 'J' and bot(your opponent) will play with 'P', and then take turns dropping 'J' and 'P' tokens into the grid. The pieces fall straight down, occupying the lowest available space within the column. The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's own tokens. Press enter to continue... \n");getchar();
        menu();
        break;
    case 3:
        Scoreboard();
        menu();
    case 4:
        puts("Thank you for playing");
        exit(1);
    default:
        puts("Invalid move");
        menu();
        break;
    }
}

int main(){
    menu();
}