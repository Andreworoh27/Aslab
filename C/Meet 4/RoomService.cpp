#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data
{
    int number;
    char status[15] = "Empty";
    char pic[16]="-";
    char purpose[45];
}Room[32];

void ViewClass(){
    puts("+======+==========+=================+================================================+");
    printf("| %-4s | %-8s | %-15s | %-46s |\n","Room","Status","PIC","Purpose");
    puts("+======+==========+=================+================================================+");
    for (int i=0;i<32;i++){
        printf("| %-3d  | %-8s | %-15s | %-46s |\n",Room[i].number,Room[i].status,Room[i].pic,Room[i].purpose);
    }
    puts("+======+==========+=================+================================================+");
}

void BorrowRoom(){
    int count=0;
    for (int i=0;i<32;i++){
        if(strcmp(Room[i].status,"Borrowed")==0){
            count++;
        }
    }

    if (count==32)
    {
        puts("No available room");
        return;
    }

    puts("+======+==========+=================+================================================+");
    printf("| %-4s | %-8s | %-15s | %-46s |\n","Room","Status","PIC","Purpose");
    puts("+======+==========+=================+================================================+");
    for (int i=0;i<32;i++){
        if(strcmp(Room[i].status,"Borrowed")!=0){
            printf("| %-3d  | %-8s | %-15s | %-46s |\n",Room[i].number,Room[i].status,Room[i].pic,Room[i].purpose);
        }
    }
    puts("+======+==========+=================+================================================+");

    int num=0;
    do{
        char input[5];
        int tmp=0;
        printf("Please input the room [0 - cancel]: ");
        scanf("%s",input);getchar();
        input[strlen(input)]='\0';
        if(!(input[0]>='0' && input[0]<='9')){
            puts("Room is not existed");
            continue;
        }
        for (int i=0;input[i]!='\0';i++){
            tmp*=10;
            tmp+=input[i]-'0';
        }
        if(tmp == 0){
            return;
        }
        bool valid = false;
        for (int i=0;i<32;i++){
            if(tmp == Room[i].number && strcmp(Room[i].status,"Borrowed")!=0 ){
                valid = true;
                break;
            }
        }
        
        if (valid == true){
            num = tmp;
            break;
        }
        else{
            puts("Room is not existed");
        }

    }while(true);

    char name[16];
    do
    {
        printf("Please input the borrower name : ");
        char tmp[16];
        scanf("%[^\n]",tmp);getchar();
        if(strlen(tmp)>=2 && strlen(tmp)<=15){
            strcpy(name,tmp);
            break;
        }
        else{
            puts("Name's lenght must more or equal to 2 and less than 15");
        }
    } while (true);
    
    char purpose[45];
    do{
        printf("Please input the purpose : ");
        char tmp[45];
        scanf("%[^\n]",tmp);getchar();
        bool flag = false;
        int start = 0;
        int counter = 0;
        for (int i = 0; i<=strlen(tmp) ; i++)
        {
            if(tmp[i]>='a' && tmp[i]<='z'){
                start = 1;
            }
            if(start == 1){
                if (tmp[i]==' ' || tmp[i]=='\0')
                {
                    counter++;
                }
                
            }
            if(counter == 2){
                flag = true;
                break;
            }
        }
        if (counter == 2){
            flag = true;
        }
        if(strlen(tmp)>=5 && strlen(tmp)<=44 && flag == true){
            strcpy(purpose,tmp);
            break;
        }
        else if (flag == false){
            puts("Purpose must at least 2 words");
        }
        else{
            puts("Purpose's lenght must more or equal to 5 and less than 45");
        }
    }while (true);
    
    for (int i = 0; i < 32; i++)
    {
        if(Room[i].number == num){
            strcpy(Room[i].pic,name);
            strcpy(Room[i].purpose,purpose);
            strcpy(Room[i].status,"Borrowed");
        }
    }
    FILE *fp = fopen("./usage.txt","a");
    fprintf(fp,"\n%d#%s#%s",num,name,purpose);
    fclose(fp);
}

void ReturnRoom(){
    int count=0;
    for (int i=0;i<32;i++){
        if(strcmp(Room[i].status,"Borrowed")==0){
            count++;
        }
    }

    if (count==0)
    {
        puts("No room to return");
        return;
    }

    puts("+======+==========+=================+================================================+");
    printf("| %-4s | %-8s | %-15s | %-46s |\n","Room","Status","PIC","Purpose");
    puts("+======+==========+=================+================================================+");
    for (int i=0;i<32;i++){
        if(strcmp(Room[i].status,"Borrowed")==0){
            printf("| %-3d  | %-8s | %-15s | %-46s |\n",Room[i].number,Room[i].status,Room[i].pic,Room[i].purpose);
        }
    }
    puts("+======+==========+=================+================================================+");

    int num=0;
    do{
        char input[5];
        int tmp=0;
        printf("Please input the room [0 - cancel]: ");
        scanf("%s",input);getchar();
        input[strlen(input)]='\0';
        if(!(input[0]>='0' && input[0]<='9')){
            puts("Room is not existed");
            continue;
        }
        for (int i=0;input[i]!='\0';i++){
            tmp*=10;
            tmp+=input[i]-'0';
        }
        if(tmp == 0){
            return;
        }
        bool valid = false;
        // bool occupied = false;
        for (int i=0;i<32;i++){
            if(tmp == Room[i].number && strcmp(Room[i].status,"Borrowed")==0 ){
                valid = true;
                break;
            }
        }
        
        if (valid == true){
            num = tmp;
            break;
        }
        else{
            puts("Room is not existed");
        }

    }while(true);

    printf("%d\n",num);
    for (int i = 0; i < 32; i++)
    {
        if(Room[i].number == num){
            strcpy(Room[i].pic,"-");
            strcpy(Room[i].purpose," ");
            strcpy(Room[i].status,"Empty");
            break;;
        }
    }
    FILE *fp = fopen("./usage.txt","w");
    int start=0;
    for ( int i = 0; i < 32; i++)
    {
        if(strcmp(Room[i].status,"Borrowed")==0){
            if(start==0){
                fprintf(fp,"%d#%s#%s",Room[i].number,Room[i].pic,Room[i].purpose);
                start=1;
            }
            else{
                fprintf(fp,"\n%d#%s#%s",Room[i].number,Room[i].pic,Room[i].purpose);
            }
        }
    }
    fclose(fp);
}

void menu(){
    puts("SLC Room Service");
    puts("==================");
    puts("1. View Class List");
    puts("2. Borrow Room");
    puts("3. Return Room");
    puts("4. Exit");
    printf("> ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        system("cls");
        ViewClass();
        puts("press enter to continue...");getchar();
        system("cls");
        menu();
        break;
    case 2:
        system("cls");
        BorrowRoom();
        system("cls");
        menu();
        break;
    case 3:
        system("cls");
        ReturnRoom();
        system("cls");
        menu();
    case 4:
        puts("thank you for playing");
        exit(1);
    default:
        break;
    }
}

void generate(){
    FILE *fp = fopen("./room.txt","r");
    for (int i=0;i<32;i++){
        int temp;
        fscanf(fp,"%d\n",&temp);
        Room[i].number = temp;
    }
    fclose(fp);
    fp = fopen("./usage.txt","r");
    for (int i = 0; !(feof(fp)); i++)
    {
        int num;
        char pic[30];
        char usage[100];
        fscanf(fp,"%d#%[^#]#%[^\n]\n",&num,pic,usage);
        pic[strlen(pic)]='\0';
        usage[strlen(usage)]='\0';
        for(int i=0;i<32;i++){
            if(Room[i].number == num){
                strcpy(Room[i].pic,pic);
                strcpy(Room[i].purpose,usage);
                strcpy(Room[i].status,"Borrowed");
                Room[i].status[strlen(Room[i].status)]='\0';
                break;
            }
        }
    }
    fclose(fp);
}

int main(){
    generate();
    menu();
}