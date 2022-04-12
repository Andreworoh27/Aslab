#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data
{
    /* data */
};

void regis(){
    char email[100];
    do{
        puts("Email [ ends with @gmail.com and unique ] : ");
        scanf("%[^\n]",email);getchar();
    }while(true);

    char username[11];
    do{
        puts("Password [ 3 - 10 characters ] : ");
        scanf("%[^\n]",username);getchar();
    }while(true);

    char password[11];
    do{
        puts("Password [ 5 - 10 characters & alphabet ] : ");
        scanf("%[^\n]",password);getchar();
    }while(true);

    puts("Registered Successfully");
    puts("Press Enter to continue...");getchar();
}

void login(){

}

void menu(){
    puts("Welcome to ShoPAI");
    puts("==================");
    puts("1. Login");
    puts("2. Register");
    puts("3. Exit");
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
}

int main(){
    menu();
}