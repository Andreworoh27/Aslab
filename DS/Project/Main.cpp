#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#define SIZE 10
struct Account
{
    char email[100];
    char username[11];
    char password[11];
    Account *left, *right;
}*BaseRoot;

struct Login
{
    char email[100];
    char password[11];
    Login*next;
}*headLogin[SIZE],*tailLogin[SIZE];

struct Product
{
    char code[10];
    char name[100];
    double price;
    Product*next,*prev;
}*headProduct[SIZE],*tailProduct[SIZE];


struct Cart
{
    char code[10];
    char name[100];
    double price;
    int quantity;
    Cart*next,*prev;
}*headCart,*tailCart;

char loginemail[100];
char loginusername[100];

unsigned long djb2(const char *str) {
    unsigned long hash = 5381;

    for(int i = 0; str[i] != '\0'; i++) {
        int c = int(str[i]);
        hash = ((hash << 5) + hash) + c;
    }

    return hash % SIZE;
}

#include "HomePage.h"
void homepage(){
    system("clear");
    generateproduct();
    puts("Welcome to ShoPAI");
    puts("==================");
    puts("1. View Product");
    puts("2. Search Products");
    puts("3. Manage Cart");
    puts("4. View Transaction History");
    puts("5. Exit");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        system("clear");
        viewproduct();
        break;
    case 2:
        system("clear");
        searchproduct();
        break;
    case 3:
        system("clear");
        managecart();
        puts("Press enter to continue...");getchar();        
        break;
    case 4:
        system("clear");
        viewhistory();
        puts("Press enter to continue...");getchar();                
    case 5:
        popallcart();
        return;
    default:
        break;
    }
    homepage();
}

#include "LandingPage.h"
void landingpage(){
    system("clear");
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
    landingpage();
}

int main(){
    srand(time(NULL));
    landingpage();
    // homepage();
}