#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

struct Account
{
    char email[100];
    char password[21];
    Account *next;
}*head,*tail;

struct Patient
{
    char id[6];
    char name[100];
    char prioritystring[25];
    int priority;
    Patient *next,*prev;
}*headpatient,*tailpatient;

struct History
{
    char id[6];
    char name[100];
    char status[15];
    History *next,*prev;
}*headhistory,*tailhistory;

int totalpatient = 4;

Patient* createnewpatient(const char id[],const char name[],const char prioritystring[],int priority){
    Patient* temp = (Patient*)malloc(sizeof(Patient));
    strcpy(temp->id,id);
    strcpy(temp->name,name);
    strcpy(temp->prioritystring,prioritystring);
    temp->priority = priority;
    temp->next = temp->prev = NULL;
    return temp;
}

void pushpatient(const char id[],const char name[],const char prioritystring[],int priority){
    Patient *temp = createnewpatient(id,name,prioritystring,priority);
    if(!headpatient){
        headpatient = tailpatient = temp;
    }
    else{
        if(priority > headpatient->priority){
            headpatient->prev = temp;
            temp->next = headpatient;
            headpatient = temp;
        }
        else if (priority <= tailpatient->priority){
            tailpatient->next = temp;
            temp->prev = tailpatient;
            tailpatient = temp;
        }
        else{
            Patient *curr = headpatient;
            while (curr->priority >= priority)
            {
                curr = curr->next;
            }
            temp->prev = curr->prev;
            temp->next = curr;
            curr->prev->next = temp;
            curr->prev = temp;
        }
    }
    return;
}

void pop(Patient **curr){
    if((*curr)==headpatient && (*curr)==tailpatient){
        free((*curr));
        headpatient = tailpatient = NULL;
    }
    else if ((*curr)==headpatient){
        Patient *temp = headpatient->next;
        (*curr)->next = temp->prev = NULL;
        free((*curr));
        headpatient = temp;
    }
    else if((*curr)==tailpatient){
        Patient *temp = tailpatient->prev;
        (*curr)->prev = temp->next = NULL;
        free((*curr));
        tailpatient = temp;
    }
    else{
        Patient *temp = (*curr)->prev;
        temp->next = (*curr)->next;
        (*curr)->next->prev = temp;
        (*curr)->next = (*curr)->prev = NULL;
        free((*curr));
    }
    return;
}

// loading for cross platform
void loading(int x){
    int delay = 1000;
    #ifdef _WIN32
    for (int i=0;i<x;i++){
        puts("Treat Patient");
        Sleep(delay);
    }
    #else
    for (int i=0;i<x;i++){
        puts("Treat Patient");
        usleep(delay*1000);
    }
    #endif
}

bool alive(int low,int high,int priority){
    int value = (rand()%(high - low+1))+low;
    if(priority == 3){
        if (value <=2)
        {
            return true;
        }
        else{
            return false;
        }
    }
    else if (priority == 2){
        if (value <=6)
        {
            return true;
        }
        else{
            return false;
        }
    }
    else {
        if (value <=9)
        {
            return true;
        }
        else{
            return false;
        }
    }
}

void allocate(){
    if (!headpatient)
    {
        return;
    }
    
    Patient *curr = headpatient;
    while (curr != NULL)
    {
        if(curr->priority == 3){
            loading(5);
        }
        else if (curr->priority == 2)
        {
            loading(3);
        }
        else if(curr->priority == 1){
            loading(2);
        }
        History* tmp = (History*)malloc(sizeof(History));
        strcpy(tmp->id,curr->id);
        strcpy(tmp->name,curr->name);
        if(alive(1,10,curr->priority)){
            strcpy(tmp->status,"Alive");
            printf("%s Alive\n",curr->name);
        }
        else{
            strcpy(tmp->status,"Death");
            printf("%s Death\n",curr->name);
        }
        if(!headhistory){
            headhistory = tailhistory = tmp;
        }
        else{
            tailhistory->next = tmp;
            tailhistory = tmp;
        }
        if (curr->next != NULL)
        {
            Patient *x = curr;
            x = x->next;
            pop(&curr);
            curr = x;
        }
        else{
            pop(&curr);
            curr = NULL;
        }
    }
    puts("Press enter to continue...");getchar();
}

void viewhistory(){
    system("clear");
    if (!headhistory)
    {
        return;
    }
    History *temp = headhistory;
    puts("=========================================================");
    puts("| ID    | Name                     | Alive              |");
    puts("=========================================================");
    while (temp!= tailhistory->next)
    {
        printf("| %-5s | %-24s | %-18s |\n",temp->id,temp->name,temp->status);
        temp = temp->next;
    }
    puts("=========================================================");
    puts(" ");
    puts("Press enter to continue...");getchar();
    return;
}

void adminmenu(){
    system("clear");
    puts("Hospital");
    puts("1. Allocate Patient");
    puts("2. View History");
    puts("3. Logout");
    printf("Choose : ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        allocate();
        break;
    case 2:
        viewhistory();
        break;
    case 3:
        return;
    default:
        break;
    }
    adminmenu();
}

void viewqueue(){
    if (!headpatient)
    {
        return;
    }
    Patient *temp = headpatient;
    puts("=========================================================");
    puts("| ID    | Name                     | Priority           |");
    puts("=========================================================");
    while (temp!= tailpatient->next)
    {
        printf("| %-5s | %-24s | %-18s |\n",temp->id,temp->name,temp->prioritystring);
        temp = temp->next;
    }
    puts("=========================================================");
    puts(" ");
    return;
}

void insert(){
    system("clear");
    totalpatient++;
    char id[6];
    char name[100];
    char prioritystring[25];
    int priority;

    id[0]='P';
    id[1]='A';
    if (totalpatient<10)
    {
        id[2]='0';
        id[3]='0';
        id[4]=totalpatient+'0';
    }
    else if(totalpatient>=10 && totalpatient<100){
        id[2]='0';
        id[3]=(totalpatient/10)+'0';
        id[4]=(totalpatient%10)+'0';
    }
    else if(totalpatient>=100){
        id[2]=(totalpatient/100)+'0';
        id[3]=((totalpatient%100)/10)+'0';
        id[4]=(totalpatient%10)+'0';
    }
    id[5]='\0';

    printf("Input Name : ");
    scanf("%[^\n]",name);getchar();

    do
    {
        printf("Input Priority [ Good | Serious | Critical ] : ");
        scanf("%[^\n]",prioritystring);getchar();
        if(strcmp(prioritystring,"Good") == 0 || strcmp(prioritystring,"Serious") == 0 || strcmp(prioritystring,"Critical") == 0 ){
            break;
        }
    } while (true);
    
    if(strcmp(prioritystring,"Good") == 0){
        priority = 1;
    }
    else if (strcmp(prioritystring,"Serious") == 0){
        priority = 2;
    }
    else if (strcmp(prioritystring,"Critical") == 0){
        priority = 3;
    }

    pushpatient(id,name,prioritystring,priority);
    return;
}

void update(){
    system("clear");
    viewqueue();
    char name[100];
    char id[6];
    char prioritystring[25];
    bool valid = false;
    int priority;
    Patient *curr = headpatient;
    do
    {
        printf("Input ID : ");
        scanf("%[^\n]",id);getchar();
        while (curr!=tailpatient->next)
        {
            if(strcmp(curr->id,id)==0){
                valid = true;
                break;
            }
            curr = curr->next;
        }
    } while (valid==false);
    printf("Input Name : ");
    scanf("%[^\n]",name);getchar();
    printf("Input Priority [ Good | Serious | Critical ] : ");
    scanf("%[^\n]",prioritystring);getchar();
    if(strcmp(prioritystring,"Good") == 0){
        priority = 1;
    }
    else if (strcmp(prioritystring,"Serious") == 0){
        priority = 2;
    }
    else if (strcmp(prioritystring,"Critical") == 0){
        priority = 3;
    }
    pop(&curr);
    pushpatient(id,name,prioritystring,priority);
    return;
}

void receptionistmenu(){
    system("clear");
    viewqueue();
    puts("");
    puts("Hospital");
    puts("1. Insert Patient");
    puts("2. Update Patient");
    puts("3. Logout");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        insert();
        break;
    case 2:
        update();
        break;
    case 3:
        return;
    default:
        break;
    }
    receptionistmenu();
}

Account* createnewaccount(const char email[],const char password[]){
    Account *temp = (Account*)malloc(sizeof(Account));
    strcpy(temp->email,email);
    strcpy(temp->password,password);
    temp->next = NULL;
    return temp;
}

void pushaccount(const char email[],const char password[]){
    Account *temp = createnewaccount(email,password);
    if(!head){
        head = tail = temp;
    }
    else{
        tail->next = temp;
        tail = temp;
    }
    return;
}

void regis(){
    system("clear");
    char email[100];
    do
    {
        printf("Email [ must end with @binus.ac.id ] : ");
        scanf("%[^\n]",email);getchar();
        char valid[]="@binus.ac.id",temp[13];
        int idx = 0;
        for (int i = (strlen(email)-1)-11; i < strlen(email); i++)
        {
            temp[idx] = email[i];
            idx++;
        }
        temp[idx]='\0';
        if(strcmp(valid,temp)==0){
            break;
        }
    } while (true);

    char passsword[100];
    do
    {
        printf("Input Password [ 8 - 20 characters ]: ");
        scanf("%[^\n]",passsword);getchar();
        if(strlen(passsword)>=8 && strlen(passsword)<=20){
            break;
        }
    } while (true);
    pushaccount(email,passsword);
    return;
}

void login(){
    system("clear");
    char email[100];
    char passsword[100];
    printf("Input Email : ");
    scanf("%[^\n]",email);getchar();
    printf("Input Password : ");
    scanf("%[^\n]",passsword);getchar();
    Account *temp = head;
    bool admin = false;
    bool valid = false;
    while (temp != NULL)
    {
        if(strcmp(temp->email,email)==0 && strcmp(temp->password,passsword)==0){
            if(strcmp(temp->email,"admin")==0 && strcmp(temp->password,"admin123")==0){
                admin = true;
            }
            valid = true;
            break;
        }
        temp = temp->next;
    }
    if(valid == true){
        if(admin == true){
            adminmenu();
        }
        else{
            receptionistmenu();
        }
    }
    else{
        login();
    }
    return;
}

void menu(){
    system("clear");
    puts("Hospital");
    puts("1. Login");
    puts("2. Register");
    puts("3. Exit");
    printf(">> ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        login();
        break;
    case 2:
        regis();
        break;
    case 3:
        exit(1);
    default:
        break;
    }
    menu();
}

int main(){
    srand(time(0));
    pushaccount("admin","admin123");
    menu();
}