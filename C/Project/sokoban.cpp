#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// global Variable :
char map[10][10];
int x,y,target,total_move=0,TargetTempX[3]={0},TargetTempY[3]={0};
int x_target[3]={0},y_target[3]={0},TargetTempBoxX[3]={0},TargetTempBoxY[3]={0};
int target_flag=0; 
int target_flag_box = 0;
struct player
{
    char name[30];
    int move;
}Player1[100],Player2[100],Player3[100];

// functions :
int main();
void Generator(FILE *fp);
void menu();
void Game();
void ViewScore();
void Level1();
void Level2();
void Level3();
void MoveInput(int level);
void Move(char input);
void win(int level);
void sort(player P[],int total);
void reset(int level);
void Printmap();


int main(){
    menu();
}

// game menu and main menu :
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
        system("cls");
        Game();
        break;
    case 2:
        system("cls");
        ViewScore();
        menu();
        break;
    case 0:
        puts("Thank you for playing");
        exit(1);
    default:
        puts("Invalid Input");
        menu();
        break;
    }
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
        system("cls");
        Level1();
        MoveInput(1);
        break;
    case 2:
        system("cls");
        Level2();
        MoveInput(2);
        break;
    case 3:
        system("cls");
        Level3();
        MoveInput(3);
        break;
    case 0:
        system("cls");
        menu();
        break;
    default:
        puts("invalid input");
        system("cls");
        Game();
        break;
    }
    
}

// Leveling function :
void Level1(){
    FILE *fp = fopen("./map1.txt","r");
    Generator(fp);
    fclose(fp);
}

void Level2(){
    FILE *fp = fopen("./map2.txt","r");
    Generator(fp);
    fclose(fp);
}

void Level3(){
    FILE *fp = fopen("./map3.txt","r");
    Generator(fp);
    fclose(fp);
}

// Movement input and logic :
void MoveInput(int level){
    do{
    system("cls");
    if(target == 0){
        win(level);
        break;
    }
    printf("Move: %d\n",total_move);
    Printmap();
    printf("Move [W A S D]\n");
    printf("Exit [ESC]\n");
    printf("Reset [Space]\n");
    printf("target left : %d\n",target);
    puts("Player = 'P' || Box = '@' || Target = 'X' || Wall = '#'");
    printf("input : ");
    char input[4];
    scanf("%[^\n]",input);getchar();
    if (strcmp(input," ")==0){
        reset(level);
    }
    else{
        input[strlen(input)]='\0';
        for(int i=0;input[i]!='\0';i++){
            input[i]=toupper(input[i]);
        }
        if(strcmp(input,"ESC")==0){
            puts("Are you sure want to exit? (y|n) ? ");
            printf(">> ");
            char in;
            scanf("%c",&in);getchar;
            in = toupper(in);
            if(in=='Y') {
                reset(level);
                break;
            }
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
    }while (true);
    menu();
}

void Move(char input){
    bool tanda = false;
    if (target_flag>0){
        tanda = true;
    }
    if(input == 'S'){
        if(map[x+1][y]=='@'){
            if(map[x+2][y]=='*'){
                map[x+2][y] = '@';
                map[x+1][y] = 'P';
                map[x][y] = ' ';
                target_flag_box++;
                for (int i = 0; i < 3; i++)
                {
                    if(TargetTempBoxX[i]==0 && TargetTempBoxY[i]==0){
                        TargetTempBoxX[i]=x+2;
                        TargetTempBoxY[i]=y;
                        target--;
                        break;
                    }
                }
                
                
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
            for (int i = 0; i < 3; i++)
            {
                if(TargetTempX[i]==0 && TargetTempY[i]==0){
                    TargetTempX[i]=x+1;
                    TargetTempY[i]=y;
                    break;
                }
            }
            target_flag++;
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
                target_flag_box++;
                for (int i = 0; i < 3; i++)
                {
                    if(TargetTempBoxX[i]==0 && TargetTempBoxY[i]==0){
                        TargetTempBoxX[i]=x;
                        TargetTempBoxY[i]=y-2;
                        target--;
                        break;
                    }
                }
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
            for (int i = 0; i < 3; i++)
            {
                if(TargetTempX[i]==0 && TargetTempY[i]==0){
                    TargetTempX[i]=x;
                    TargetTempY[i]=y-1;
                    break;
                }
            }
            target_flag++;
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
                target_flag_box++;
                for (int i = 0; i < 3; i++)
                {
                    if(TargetTempBoxX[i]==0 && TargetTempBoxY[i]==0){
                        TargetTempBoxX[i]=x-2;
                        TargetTempBoxY[i]=y;
                        target--;
                        break;
                    }
                }
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
            for (int i = 0; i < 3; i++)
            {
                if(TargetTempX[i]==0 && TargetTempY[i]==0){
                    TargetTempX[i]=x-1;
                    TargetTempY[i]=y;
                    break;
                }
            }
            target_flag++;
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
                target_flag_box++;
                for (int i = 0; i < 3; i++)
                {
                    if(TargetTempBoxX[i]==0 && TargetTempBoxY[i]==0){
                        TargetTempBoxX[i]=x;
                        TargetTempBoxY[i]=y+2;
                        target--;
                        break;
                    }
                }
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
            for (int i = 0; i < 3; i++)
            {
                if(TargetTempX[i]==0 && TargetTempY[i]==0){
                    TargetTempX[i]=x;
                    TargetTempY[i]=y+1;
                    break;
                }
            }
            target_flag++;
            map[x][y+1]='P';
            map[x][y]=' ';
        }
        else if (map[x][y+1] == ' '){
            map[x][y+1]='P';
            map[x][y]=' ';
        }
        else if (map[x][y+1] =='#'){
            return;
        }
        y+=1;
    }
    if (tanda == true){
        for (int i=0;i<3;i++){
            if(map[TargetTempX[i]][TargetTempY[i]]==' '){
                map[TargetTempX[i]][TargetTempY[i]] = '*';
                target_flag--;
                TargetTempX[i] = TargetTempY[i] = 0;
            }
        }
    }
    if (target_flag_box > 0){
        for (int i=0;i<3;i++){
            if(map[TargetTempBoxX[i]][TargetTempBoxY[i]]==' '){
                map[TargetTempBoxX[i]][TargetTempBoxY[i]] = '*';
                target++;
                target_flag_box--;
                TargetTempBoxX[i] = TargetTempBoxY[i] = 0;
            }
        }
    }
    total_move++;
}

// Winner input:
void win(int level){
    char name[31];
    puts("You win");
    printf("You use %d move(s)\n",total_move);
    puts("Press enter to continue...");getchar();
    do
    {
        char temp[100];
        printf("Input Name : ");
        scanf("%[^\n]",temp);getchar();
        int counter = 0;
        bool start = false;
        for (int i=0;temp[i]!='\0';i++){
            if(start == false){
                if(temp[i]!=' '){
                    start = true;
                    continue;
                }
            }
            else{
                counter++;
            }

        }
        if(counter>=3 && counter<=30){
            strcpy(name,temp);
            break;
        }
    } while (true);
    if(level==1){
        FILE *fp = fopen("./score1.txt","a");
        fprintf(fp,"%s#%d\n",name,total_move);
        fclose(fp);
    }
    else if (level==2){
        FILE *fp = fopen("./score2.txt","a");
        fprintf(fp,"%s#%d\n",name,total_move);
        fclose(fp);
    }
    else if (level==3){
        FILE *fp = fopen("./score3.txt","a");
        fprintf(fp,"%s#%d\n",name,total_move);
        fclose(fp);
    }
}

// Print leaderboard :
void ViewScore(){
    int total_player=0;
    FILE *fp;
    fp = fopen("./score1.txt","r");
    puts("Level 1:");
    if (!fp)
    {
        puts("No data");
    }
    else{
        puts("################################################");
        puts("| No. | Name                           | Score |");
        puts("################################################");
        for (int i = 0; !(feof(fp)); i++)
        {
            fscanf(fp,"%[^#]#%d\n",Player1[i].name,&Player1[i].move);
            total_player++;
        }
        sort(Player1,total_player);
        for (int i = 0; i < total_player; i++)
        {
            printf("| %-3d | %-30s | %-5d |\n",i+1,Player1[i].name,Player1[i].move);
        }
        
        puts("################################################");
        total_player=0;
    }
    puts("");
    fclose(fp);

    fp = fopen("./score2.txt","r");
    puts("Level 2:");
    if (!fp)
    {
        puts("No data");
    }
    else{
        puts("################################################");
        puts("| No. | Name                           | Score |");
        puts("################################################");
        for (int i = 0; !(feof(fp)); i++)
        {
            fscanf(fp,"%[^#]#%d\n",Player2[i].name,&Player2[i].move);
            total_player++;
        }
        sort(Player2,total_player);
        for (int i = 0; i < total_player; i++)
        {
            printf("| %-3d | %-30s | %-5d |\n",i+1,Player2[i].name,Player2[i].move);
        }
        
        puts("################################################");
        total_player=0;
    }
    puts("");
    fclose(fp);

    fp = fopen("./score3.txt","r");
    puts("Level 3:");
    if (!fp)
    {
        puts("No data");
    }
    else{
        puts("################################################");
        puts("| No. | Name                           | Score |");
        puts("################################################");
        for (int i = 0; !(feof(fp)); i++)
        {
            fscanf(fp,"%[^#]#%d\n",Player3[i].name,&Player3[i].move);
            total_player++;
        }
        sort(Player3,total_player);
        for (int i = 0; i < total_player; i++)
        {
            printf("| %-3d | %-30s | %-5d |\n",i+1,Player3[i].name,Player3[i].move);
        }
        
        puts("################################################");
        total_player=0;
    }
    puts("");
    fclose(fp);
}

// Utilities:
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

void sort(player P[],int total){
    for (int i=0;i<total-1;i++){
        for (int j=0;j<total-1-i;j++){
            if (P[j].move>P[j+1].move){
                int temp;
                temp= P[j+1].move;
                P[j+1].move=P[j].move;
                P[j].move=temp;

                char tmp[31];
                strcpy(tmp,P[j+1].name);
                strcpy(P[j+1].name,P[j].name);
                strcpy(P[j].name,tmp);
            }
        }
    }
}

void Printmap(){
    for(int i=0;strcmp(map[i],"\0")!=0;i++){
        printf("%s\n",map[i]);
    }
}

void reset(int level){
    for (int i=0;i<10;i++){
        strcpy(map[i],"\0");
    }
    switch (level)
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
    }
    for (int i=0 ; i < 3; i++)
    {
        TargetTempBoxX[i]=TargetTempBoxY[i]=0;
        x_target[i]={0},y_target[i]=0;
        TargetTempX[i]=TargetTempY[i]=0;
    }
    target_flag=false; 
    target_flag_box = 0;
    total_move = 0;
}