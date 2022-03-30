#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char map[10][10];
int x,y,target,total_move=0;
int x_target[5],y_target[5];

void Generator(FILE *fp){
    fscanf(fp,"%d %d\n",&x,&y);
    fscanf(fp,"%d\n",&target);
    for (int i=0;i<target;i++){
        fscanf(fp,"%d %d\n",&x_target[i],&y_target[i]);
    }
    int end;
    for(int i=0;!(feof(fp));i++){
        fscanf(fp,"%[^\n]\n",map[i]);
        end=i;
    }
    strcpy(map[end+1],"\0");
}

void Printmap(){
    for(int i=0;strcmp(map[i],"\0")!=0;i++){
        printf("%s\n",map[i]);
    }
}

void Move(){
    printf("Move: %d\n",total_move);
    Printmap();
    printf("Move [W A S D]\n");
    printf("Exit [ESC]\n");
    printf("Reset [Space]\n");
    char input[4];
    scanf("%[^\n]",input);getchar();
    if (strcmp(input," ")==0){
        // reset();
    }
    else{
        input[strlen(input)]='\0';
        for(int i=0;input[i]!='\0';i++){
        input[i]=toupper(input[i]);
        }
        printf("%s\n",input);
        if(strcmp(input,"ESC")==0){
            // esc();
        }
        else if(strcmp(input,"W")==0){
            // up();
        }
        else if (strcmp(input,"S")==0){
            // down();
        }
        else if (strcmp(input,"A")==0){
            // left();
        }
        else{
            // right();
        }
    }
}

void Level1(){
    FILE *fp = fopen("./map1.txt","r");
    Generator(fp);
    Move();
    fclose(fp);
}

void Level2(){
    FILE *fp = fopen("./map2.txt","r");
    Generator(fp);
    Move();
    fclose(fp);
}

void Level3(){
    FILE *fp = fopen("./map3.txt","r");
    Generator(fp);
    Move();
    fclose(fp);
}

void Game(){
    puts("1. Level 1");
    puts("2. Level 2");
    puts("3. Level 3");
    puts("0. Exit");
    printf(">> ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        Level1();
        break;
    
    default:
        break;
    }
    
}

void menu(){
    puts("1. Game");
    puts("2. View Score");
    puts("0. Exit");
    printf(">> ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        Game();
        break;
    
    default:
        puts("Invalid Input");
        menu();
        break;
    }
}

int main(){
    menu();
}