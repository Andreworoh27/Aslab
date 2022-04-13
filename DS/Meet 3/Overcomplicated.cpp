#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 10
struct Data
{
    char string[25];
    Data*next;
}*head[SIZE],*tail[SIZE];

Data* createnew(const char string[]){
    Data* temp = (Data*)malloc(sizeof(Data));
    strcpy(temp->string,string);
    temp->next = NULL;
    return temp;
}
char answer[7];
char history[6][7];
int attemp = 0;

void green(){
    printf("\033[0;32m");
}

void yellow(){
    printf("\033[0;33m");
}

void resetcolor(){
    printf("\033[0m");
}

void reset(){
    attemp = 0;
    strcpy(answer,"\0");
    for (int i=0;i<6;i++){
        strcpy(history[i],"\0");
    }
}

unsigned long djb2(const char *str) {
    unsigned long hash = 5381;

    for(int i = 0; str[i] != '\0'; i++) {
        int c = int(str[i]);
        hash = ((hash << 5) + hash) + c;
    }

    return hash % SIZE;
}

void generate(){
    FILE *fp = fopen("./word.txt","r");
    while (!(feof(fp)))
    {
        char string[25];
        fscanf(fp,"%s\n",string);
        Data *temp = createnew(string);
        int index = djb2(string);
        if(!head[index]){
            head[index]=tail[index]=temp;
        }
        else{
            tail[index]->next = temp;
            tail[index] = temp;
        }
    }
}

void printhistory(){
    for(int idx =0;idx < attemp;idx++){
        for (int i=0;i<6;i++){
            if(history[idx][i]==answer[i]){
                green();
                printf("%c | ",history[idx][i]);
                resetcolor();
            }
            else {
                bool ada = false;
                for(int j=0;j<6;j++){
                    if (history[idx][j]==answer[i] && j != i){
                        yellow();
                        printf("%c | ",history[idx][j]);
                        resetcolor();
                        ada = true;
                        break;
                    }
                }
                if (ada == false){
                    printf("%c | ",history[idx][i]);
                }
            }
        }
        printf("\n\n");
    }
    puts("");
}

void play(){
    system("clear");
    printf("Attemp : %d\n",attemp+1);
    printhistory();
    char input[7];
    printf("answer lenght : %ld\n",strlen(answer));
    printf("Input word : ");
    scanf("%[^\n]",input);getchar();
    if(strlen(input)>6){
        puts("only 6 letter input");
    }
    else{
        if(strcmp(input,answer)==0){
            green();
            printf("%s\n",input);
            resetcolor();
            puts("You got the word!");
            puts("Press enter to continue...");getchar();
            return;
        }
        strcpy(history[attemp],input);
        for (int i=0;i<6;i++){
            if(input[i]==answer[i]){
                green();
                printf("%c | ",input[i]);
                resetcolor();
            }
            else {
                bool ada = false;
                for(int j=0;j<6;j++){
                    if (input[j]==answer[i] && j != i){
                        yellow();
                        printf("%c | ",input[j]);
                        resetcolor();
                        ada = true;
                        break;
                    }
                }
                if (ada == false){
                    printf("%c | ",input[i]);
                }
            }
        }
        attemp++;
        puts("");
        if(attemp >= 6){
            puts("You didn't get the word! It was...");
            puts("SPROUT");
            puts("Press enter to continue...");getchar();
            return;
        }
        else{
            puts("You didn't get the word! It was...");
            puts("Next Attemp!");
            puts("Press enter to continue...");getchar();
        }
    }
    printf("\n\n");
    play();
}

int randomizer(int high,int low){
    return (rand()%(high - low+1))+low;
}

void word(){
    int idx = randomizer(9,0);
    int counter = 0;
    Data *curr = head[idx];
    while (curr!=NULL)
    {
        counter++;
        curr = curr->next;
    }
    int idx2 = randomizer(counter,0);
    curr = head[idx];
    for (int i = 0; i < idx2-1; i++)
    {
        curr = curr->next;    
    }
    strcpy(answer,curr->string);
}

void menu(){
    system("clear");
    puts("OVERCOMPLICATED WORDLE");
    puts("1. Play");
    puts("2. Exit");
    printf("Choose : ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        word();
        play();
        reset();
        break;
    case 2:
        exit(1);
    default:
        break;
    }
    menu();
}

int main(){
    generate();
    srand(time(0));
    menu();
}