#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node
{
    char name[50];
    char description[100];
    int day;
    double duration;
    Node*next;
}*head,*tail;

Node* createnew(const char name[],const char description[],int day,double duration){
    Node *temp = (Node*)malloc(sizeof(Node));
    strcpy(temp->name,name);
    strcpy(temp->description,description);
    temp->day = day;
    temp->duration = duration;
    temp->next = NULL;
    return temp;
}

void push(const char name[],const char description[],int day,double duration){
    Node *temp = createnew(name,description,day,duration);
    if (!head)
    {
        head = tail = temp;
    }
    else {
        tail->next = temp;
        tail = temp;
    }
    return;
}

void add(){
    system("clear");
    char name[50]="\0";
    do{
        printf("Insert Activity Name :");
        scanf("%[^\n]",name);getchar();
        if(strlen(name)>0){
            break;
        }
    }while(true);

    char description[100] = "\0";
    do{
        printf("Insert Activity Description :");
        scanf("%[^\n]",description);getchar();
        if(strlen(description)>0){
            break;
        }
    }while(true);

    int day;
    do
    {
        printf("Day [1 - 7] : ");
        scanf("%d",&day);getchar();
        if(day>=1 && day<=7){
            break;
        }
    } while (true);
    
    double duration;
    do
    {
        printf("Duration : ");
        scanf("%lf",&duration);getchar();
        if(duration>0){
            break;
        }
    } while (true);

    push(name,description,day,duration);
    return;
}

void printday(int i){
    Node *curr = head;
    while (curr!=tail->next)
    {
        if(curr->day == i+1){
            int minute = (int)((curr->duration-(int)curr->duration)*60);
            printf("%s [%d hours %d minutes]\n",curr->name,(int)curr->duration,minute);
            printf("- %s\n\n",curr->description);
        }
        curr = curr->next;
    }
    return;
}

void view(){
    int day[7]={0};
    Node *curr = head;
    for (int i=0;curr!=tail->next;i++){
        day[(curr->day)-1]=1;
        curr = curr->next;
    }
    for (int i = 0; i < 7; i++)
    {
        if(day[i]==1){
            if(i==0){
                puts("Monday");
                puts("----------");
                printday(i);
            }
            else if(i==1){
                puts("Tuesday");
                puts("----------");
                printday(i);            
            }
            else if(i==2){
                puts("Wednesday");
                puts("----------");
                printday(i);
            }
            else if(i==3){
                puts("Thursday");
                puts("----------");
                printday(i);
            }
            else if(i==4){
                puts("Friday");
                puts("----------");
                printday(i);
            }
            else if(i==5){
                puts("Saturday");
                puts("----------");
                printday(i);
            }
            else if(i==6){
                puts("Monday");
                puts("----------");
                printday(i);
            }
        }

    }
    return;
}

void update(){
    system("clear");
    char string[50];
    Node *curr = head;
    do{
        printf("Choose Activity to Update [Type 'exit' to go back] : ");
        scanf("%[^\n]",string);getchar();
        if (strcmp(string,"exit")==0)
        {
            return;
        }
        
        bool valid = false;
        while (curr!=tail->next)
        {
            if(strcmp(curr->name,string)==0){
                valid = true;
                break;
            }
            curr = curr->next;
        }
        if (valid==true)
        {
            break;
        }
        
    }while(true);

    char name[50]="\0";
    do{
        printf("Activity Name :");
        scanf("%[^\n]",name);getchar();
        if(strlen(name)>0){
            break;
        }
    }while(true);

    char description[100] = "\0";
    do{
        printf("Activity Description :");
        scanf("%[^\n]",description);getchar();
        if(strlen(description)>0){
            break;
        }
    }while(true);

    double duration;
    do
    {
        printf("Duration : ");
        scanf("%lf",&duration);getchar();
        if(duration>0){
            break;
        }
    } while (true);

    strcpy(curr->name,name);
    strcpy(curr->description,description);
    curr->duration = duration;
    puts("Update Success...");
    puts("Press enter to continue...");getchar();
    return;
}

void remove(){
    system("clear");
    if (!head)
    {
        puts("There is no Activity!");
        puts("Press enter to continue...");getchar();
    }
    
    char string[50];
    Node *curr = head;
    do{
        printf("Choose Activity to delete [Type 'exit' to go back] : ");
        scanf("%[^\n]",string);getchar();
         if (strcmp(string,"exit")==0)
        {
            return;
        }
        bool valid = false;
        while (curr!=tail->next)
        {
            if(strcmp(curr->name,string)==0){
                valid = true;
                break;
            }
            curr = curr->next;
        }
        if (valid==true)
        {
            break;
        }
        
    }while(true);

    if (curr==head && curr ==tail)
    {
        free(curr);
        head = tail = NULL;
    }
    else if (curr == head){
        head = curr->next;
        curr ->next = NULL;
        free(curr);
    }
    else if (curr == tail){
        Node*temp = head;
        while (temp->next!=tail)
        {
            temp = temp->next;
        }
        tail = temp;
        tail->next = NULL;
        free(curr);
    }
    else{
        Node*temp = head;
        while (temp->next!=curr)
        {
            temp = temp->next;
        }
        temp->next = curr->next;
        curr->next = NULL;
        free(curr);
    }
    puts("Delete Success...");
    puts("Press enter to continue...");getchar();
    return;
}

void viewmenu(){
    system("clear");
    if (!head)
    {
        puts("No Activity Found!");
        puts("Press enter to continue...");getchar();
        return;
    }
    view();
    puts("1. Update Activity");
    puts("2. Delete Activity");
    puts("3. Back to main menu");
    printf(">> ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        update();
        break;
    case 2:
        remove();
        break;
    case 3:
        return;
    default:
        break;
    }
    viewmenu();
}

void printfile(int i,FILE **fp){
    Node *curr = head;
    while (curr!=tail->next)
    {
        if(curr->day == i+1){
            int minute = (int)((curr->duration-(int)curr->duration)*60);
            fprintf((*fp),"%s [%d hours %d minutes]\n",curr->name,(int)curr->duration,minute);
            fprintf((*fp),"- %s\n\n",curr->description);
        }
        curr = curr->next;
    }
    return;
}

void fileexport(){
    system("clear");
    if (!head)
    {
        puts("There is no Activity!");
        puts("Press enter to continue...");getchar();
        return;
    }
    int day[7]={0};
    Node *curr = head;
    for (int i=0;curr!=tail->next;i++){
        day[(curr->day)-1]=1;
        curr = curr->next;
    }
    FILE *fp = fopen("./Weekly Journal.txt","w");
    for (int i = 0; i < 7; i++)
    {
        if(day[i]==1){
            if(i==0){
                fprintf(fp,"Monday\n");
                fprintf(fp,"----------\n");
                printfile(i,&fp);
            }
            else if(i==1){
                fprintf(fp,"Tuesday\n");
                fprintf(fp,"----------\n");
                printfile(i,&fp);            
            }
            else if(i==2){
                fprintf(fp,"Wednesday\n");
                fprintf(fp,"----------\n");
                printfile(i,&fp);
            }
            else if(i==3){
                fprintf(fp,"Thursday\n");
                fprintf(fp,"----------\n");
                printfile(i,&fp);
            }
            else if(i==4){
                fprintf(fp,"Friday\n");
                fprintf(fp,"----------\n");
                printfile(i,&fp);
            }
            else if(i==5){
                fprintf(fp,"Saturday\n");
                fprintf(fp,"----------\n");
                printfile(i,&fp);
            }
            else if(i==6){
                fprintf(fp,"Monday\n");
                fprintf(fp,"----------\n");
                printfile(i,&fp);
            }
        }

    }
    fclose(fp);
    puts("Export Success!");
    puts("Press enter to continue...");getchar();
    return;
}
void menu(){
    system("clear");
    puts("Weekly Journal");
    puts("1. Add new Activity");
    puts("2. View Activity");
    puts("3. Export Activity to txt");
    puts("4. Exit");
    printf(">> ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        add();
        break;
    case 2:
        viewmenu();
        break;
    case 3:
        fileexport();
        break;
    case 4:
        puts("Thank you");
        exit(1);
    default:
        printf("Input Invalid");
        break;
    }
    menu();
}

int main(){
    menu();
}