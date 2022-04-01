#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// global Variable :
char map[10][10];
int x,y,target,total_move=0,TargetTempX,TargetTempY,TargetTempBoxX,TargetTempBoxY;
int x_target[5],y_target[5];
bool target_flag=false; 
bool target_flag_box = false;

// utilites :
void Generator(FILE *fp){
    fscanf(fp,"%d %d\n",&y,&x);
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
    for (int i=0;i<target;i++){
        map[y_target[i]][x_target[i]]='*';
    }
    map[x][y]='P';
}

void Printmap(){
    for(int i=0;strcmp(map[i],"\0")!=0;i++){
        printf("%s\n",map[i]);
    }
}

// Movement input and logic :
void Move(char input){
    bool tanda = false;
    if (target_flag==true){
        tanda = true;
    }
    if(input == 'S'){
        if(map[x+1][y]=='@'){
            if(map[x+2][y]=='*'){
                map[x+2][y] = '@';
                map[x+1][y] = 'P';
                map[x][y] = ' ';
                target_flag_box = true;
                TargetTempBoxX=x+2;
                TargetTempBoxY=y;
                target--;
            }
            else if (map[x+2][y]=='@'){
                return;
            }
            else if (map[x+2][y]!='#' && map[x+2][y]==' '){
                map[x+2][y]='@';
                map[x+1][y] = 'P';
                map[x][y] = ' ';
            }
            else if (map[x+2][y]=='#'){
                return;
            }
        }
        else if (map[x+1][y] == '*'){
            TargetTempX=x+1;
            TargetTempY=y;
            target_flag=true;
            map[x+1][y]='P';
            map[x][y]=' ';
        }
        else if (map[x+1][y] == ' '){
            map[x+1][y]='P';
            map[x][y]=' ';
        }
        else if (map[x+1][y] =='#'){
            puts("invalid");
            return;
        }
        x+=1;
    }
    else if(input == 'A'){
        if(map[x][y-1]=='@'){
            if(map[x][y-2]=='*'){
                map[x][y-2] = '@';
                map[x][y-1] = 'P';
                map[x][y] = ' ';
                target_flag_box = true;
                TargetTempBoxX=x;
                TargetTempBoxY=y-2;
                target--;
            }
            else if (map[x][y-2]=='@'){
                return;
            }
            else if (map[x][y-2]!='#' && map[x][y-2]==' '){
                map[x][y-2]='@';
                map[x][y-1] = 'P';
                map[x][y] = ' ';
            }
            else if (map[x][y-2]=='#'){
                return;
            }
        }
        else if (map[x][y-1] == '*'){
            TargetTempX=x;
            TargetTempY=y-1;
            target_flag=true;
            map[x][y-1]='P';
            map[x][y]=' ';
        }
        else if (map[x][y-1] == ' '){
            map[x][y-1]='P';
            map[x][y]=' ';
        }
        else if (map[x][y-1] =='#'){
            puts("invalid");
            return;
        }
        y-=1;
    }
    else if(input == 'W'){
        if(map[x-1][y]=='@'){
            if(map[x-2][y]=='*'){
                map[x-2][y] = '@';
                map[x-1][y] = 'P';
                map[x][y] = ' ';
                target_flag_box = true;
                TargetTempBoxX=x-2;
                TargetTempBoxY=y;
                target--;
            }
            else if (map[x-2][y]=='@'){
                return;
            }
            else if (map[x-2][y]!='#' && map[x-2][y]==' '){
                map[x-2][y]='@';
                map[x-1][y] = 'P';
                map[x][y] = ' ';
            }
            else if (map[x-2][y]=='#'){
                return;
            }
        }
        else if (map[x-1][y] == '*'){
            TargetTempX=x-1;
            TargetTempY=y;
            target_flag=true;
            map[x-1][y]='P';
            map[x][y]=' ';
        }
        else if (map[x-1][y] == ' '){
            map[x-1][y]='P';
            map[x][y]=' ';
        }
        else if (map[x-1][y] =='#'){
            puts("invalid");
            return;
        }
        x-=1;
    }
    else if(input == 'D'){
        if(map[x][y+1]=='@'){
            if(map[x][y+2]=='*'){
                map[x][y+2] = '@';
                map[x][y+1] = 'P';
                map[x][y] = ' ';
                target_flag_box = true;
                TargetTempBoxX=x;
                TargetTempBoxY=y+2;
                target--;
            }
            else if (map[x][y+2]=='@'){
                return;
            }
            else if (map[x][y+2]!='#' && map[x][y+2]==' '){
                map[x][y+2]='@';
                map[x][y+1] = 'P';
                map[x][y] = ' ';
            }
            else if (map[x][y+2]=='#'){
                return;
            }
        }
        else if (map[x][y+1] == '*'){
            TargetTempX=x;
            TargetTempY=y+1;
            target_flag=true;
            map[x][y+1]='P';
            map[x][y]=' ';
        }
        else if (map[x][y+1] == ' '){
            map[x][y+1]='P';
            map[x][y]=' ';
        }
        else if (map[x][y+1] =='#'){
            puts("invalid");
            return;
        }
        y+=1;
    }
    if (tanda == true){
        map[TargetTempX][TargetTempY] = '*';
        target_flag = false;
    }
    if (target_flag_box == true){
        if(map[TargetTempBoxX][TargetTempBoxY]==' '){
            map[TargetTempBoxX][TargetTempBoxY] = '*';
            target++;
            target_flag_box=false;
        }
    }
}

void MoveInput(){
    printf("Move: %d\n",total_move);
    Printmap();
    printf("Move [W A S D]\n");
    printf("Exit [ESC]\n");
    printf("Reset [Space]\n");
    printf("target left : %d\n",target);
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
        if(strcmp(input,"ESC")==0){
            return;
        }
        else if(strcmp(input,"W")==0){
            Move(input[0]);
        }
        else if (strcmp(input,"S")==0){
            Move(input[0]);
        }
        else if (strcmp(input,"A")==0){
            Move(input[0]);
        }
        else if (strcmp(input,"D")==0){
            Move(input[0]);
        }
    }
    MoveInput();
}

// Leveling function :
void Level1(){
    FILE *fp = fopen("./map1.txt","r");
    Generator(fp);
    MoveInput();
    fclose(fp);
}

void Level2(){
    FILE *fp = fopen("./map2.txt","r");
    Generator(fp);
    MoveInput();
    fclose(fp);
}

void Level3(){
    FILE *fp = fopen("./map3.txt","r");
    Generator(fp);
    MoveInput();
    fclose(fp);
}

// game menu and main menu :
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
    case 2:
        Level2();
        break;
    case 3:
        Level3();
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