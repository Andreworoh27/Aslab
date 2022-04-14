#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
    char name[21],title[26];
    int mnt,hour,scnd;
    Node *left,*right;
}*Baseroot;

struct Nodeduration
{
    char name[21],title[26];
    int mnt,hour,scnd;
    Nodeduration *left,*right;
}*BaserootDuration;
int hourtemp,mnttemp,scndtemp;

Node* createnew(const char *name,const char *title,int hour,int mnt,int scnd){
    Node *tmp = (Node*)malloc(sizeof(Node));
    strcpy(tmp->name,name);
    strcpy(tmp->title,title);
    tmp->hour = hour;
    tmp->mnt = mnt;
    tmp->scnd = scnd;
    return tmp;
}

Nodeduration* createnewduration(const char *name,const char *title,int hour,int mnt,int scnd){
    Nodeduration *tmp = (Nodeduration*)malloc(sizeof(Nodeduration));
    strcpy(tmp->name,name);
    strcpy(tmp->title,title);
    tmp->hour = hour;
    tmp->mnt = mnt;
    tmp->scnd = scnd;
    return tmp;
}

Node* push(Node* root, const char *name,const char *title,int hour,int mnt,int scnd){
    if(!root){
        return createnew(name,title,hour,mnt,scnd);
    }
    else if(strcmp(root->title,title)>0){
        root->left = push(root->left,name,title,hour,mnt,scnd);
    }
    else if(strcmp(root->title,title)<0){
        root->right = push(root->right,name,title,hour,mnt,scnd);
    }
    return root;
}

Nodeduration* pushduration(Nodeduration* root, const char *name,const char *title,int hour,int mnt,int scnd){
    if(!root){
        return createnewduration(name,title,hour,mnt,scnd);
    }
    else if((root->hour*60*60)+(root->mnt*60)+root->scnd > (hour*60*60)+(mnt*60)+scnd){
        root->left = pushduration(root->left,name,title,hour,mnt,scnd);
    }
    else if((root->hour*60*60)+(root->mnt*60)+root->scnd < (hour*60*60)+(mnt*60)+scnd){
        root->right = pushduration(root->right,name,title,hour,mnt,scnd);
    }
    return root;
}

bool search(const char title[],Node* root){
    if(!root){
        return false;
    }
    else if(strcmp(root->title,title)==0){
        hourtemp = root->hour;
        mnttemp = root->mnt;
        scndtemp = root->scnd;
        return true;
    }
    else if(strcmp(root->title,title)>=0){
        return search(title,root->left);
    }
    else if(strcmp(root->title,title)<=0){
        return search(title,root->right);
    }
    return false;
}

void insert(){
    char name[21],title[26];
    int mnt,hour,scnd;
    do
    {
        bool valid = true;
        printf("Insert Artist [ 3-20 character | not contains number ] : ");
        scanf("%[^\n]",name);getchar();
        for (int i = 0; i < strlen(name); i++)
        {
            if (name[i]>='0' && name[i]<='9')
            {
                valid = false;
                break;
            }
            
        }
        if (valid == true && strlen(name)>=3 && strlen(name)<=20) break;
    } while (true);
    
    do
    {
        printf("Insert Title [ 3-25 character ] : ");
        scanf("%[^\n]",title);getchar();
        if (search(title,Baseroot)==false && strlen(title)>=3 && strlen(title)<=25)
        {
            break;
        }
        
    } while (true);
    
    do
    {
        printf("Insert Duration hour [ 0 - 24 ] : ");
        scanf("%d",&hour);getchar();
        if (hour>=0 && hour<=24)
        {
            break;
        }
    } while (true);
    
    do
    {
        printf("Insert Duration minute [ 0 - 60 ] : ");
        scanf("%d",&mnt);getchar();
        if (mnt>=0 && mnt<=60)
        {
            break;
        }
    } while (true);

    do
    {
        printf("Insert Duration second [ 0 - 60 ] : ");
        scanf("%d",&scnd);getchar();
        if(hour == 0 && mnt ==0){
            if (scnd>=1 && scnd<=60)
            {
                break;
            }
            puts("The duration min. 1 second!");
        }
        else{
            if (scnd>=0 && scnd<=60)
            {
                break;
            }
        }
    } while (true);

    Baseroot=push(Baseroot,name,title,hour,mnt,scnd);
    BaserootDuration = pushduration(BaserootDuration,name,title,hour,mnt,scnd);
}

void sortbytitle(Node *root){
    if(!root){
        return;
    }
    else if(root) {

        sortbytitle(root->left);
        printf("| %-27s | %-24s | %02d:%02d:%02d |\n", root->title, root->name, root->hour,root->mnt,root->scnd);
        sortbytitle(root->right);
    }
}

void sortbyduration(Nodeduration *root){
    if(!root){
        return;
    }
    else if(root) {

        sortbyduration(root->right);
        printf("| %-27s | %-24s | %02d:%02d:%02d |\n",root->title, root->name, root->hour,root->mnt,root->scnd);
        sortbyduration(root->left);
    }
}

void view(){
    system("clear");
    if (!Baseroot)
    {
        puts("There is no music yet...");getchar();
        return;
    }
    puts("View Music");
    puts("1. Sort by Title (Ascending)");
    puts("2. Sort by Duration (Descending)");
    puts("3. Exit");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        puts("==============================+==========================+===========");
        puts("| Title                       | Artist                   | Duration |");
        puts("==============================+==========================+===========");
        sortbytitle(Baseroot);
        puts("==============================+==========================+===========");
        puts("Press enter to continue...");getchar();
        break;
    case 2:
        puts("==============================+==========================+===========");
        puts("| Title                       | Artist                   | Duration |");
        puts("==============================+==========================+===========");
        sortbyduration(BaserootDuration);
        puts("==============================+==========================+===========");
        puts("Press enter to continue...");getchar();
        break;
    case 3:
        return;
    default:
        break;
    }
    view();
}

Node* inorder(Node *root){
    Node* curr = root ->right;
    while (curr && curr->left)
    {
        curr=curr->left;
    }
    return curr;
}

Node* remove(const char title[],Node *root){
    if(!root){
        return root;
    }
    else if (strcmp(root->title,title)>0){
        root->left = remove(title,root->left);
    }
    else if (strcmp(root->title,title)<0){
        root->right = remove(title,root->right);
    }
    else{
        if(!root->left || !root->right){
            Node *newnode = root->left ? root->left : root->right;
            root->left = root->right = NULL;
            free(root);
            root=NULL;
            return newnode;
        }
        else{
            Node *newnode = inorder(root);
            strcpy(root->name,newnode->name);
            strcpy(root->title,newnode->title);
            root->hour = newnode->hour;
            root->mnt = newnode->mnt;
            root->scnd = newnode->scnd;
            root->left = remove(newnode->title,root->left);
        }
    }
    return root;
}

Nodeduration* inorder2(Nodeduration *root){
    Nodeduration* curr = root ->right;
    while (curr && curr->left)
    {
        curr=curr->left;
    }
    return curr;
}

Nodeduration* remove2(int time,Nodeduration *root){
    if(!root){
        return root;
    }
    else if ((root->hour*60*60)+(root->mnt*60)+root->scnd > time){
        root->left = remove2(time,root->left);
    }
    else if ((root->hour*60*60)+(root->mnt*60)+root->scnd < time){
        root->right = remove2(time,root->right);
    }
    else{
        if(!root->left || !root->right){
            Nodeduration *newnode = root->left ? root->left : root->right;
            root->left = root->right = NULL;
            free(root);
            root=NULL;
            return newnode;
        }
        else{
            Nodeduration *newnode = inorder2(root);
            strcpy(root->name,newnode->name);
            strcpy(root->title,newnode->title);
            root->hour = newnode->hour;
            root->mnt = newnode->mnt;
            root->scnd = newnode->scnd;
            root->left = remove2((newnode->hour*60*60)+(newnode->mnt*60)+newnode->scnd,root->left);
        }
    }
    return root;
}

void removemusic(){
    system("clear");
    if (!Baseroot)
    {
        puts("There is no music yet...");getchar();
        return;
    }
    puts("==============================+==========================+===========");
    puts("| Title                       | Artist                   | Duration |");
    puts("==============================+==========================+===========");
    sortbytitle(Baseroot);
    puts("==============================+==========================+===========");
    printf("Input Music Title to be deleted [0 to cance] : ");
    char string[50];
    scanf("%[^\n]",string);getchar();
    if(strcmp(string,"0")==0){
        return;
    }
    else{
        if(search(string,Baseroot)){
            Baseroot = remove(string,Baseroot);
            BaserootDuration = remove2((hourtemp*60*60)+(mnttemp*60)+scndtemp,BaserootDuration);
            puts("==============================+==========================+===========");
            puts("| Title                       | Artist                   | Duration |");
            puts("==============================+==========================+===========");
            sortbytitle(Baseroot);
            puts("==============================+==========================+===========");
            puts("press enter to continue...");getchar();
        }
        else{
            puts("Song doesn't exist");
            puts("press enter to continue...");getchar();
        }
        removemusic();
    }
}

void menu(){
    system("clear");
    puts("=======================");
    puts("        Spoofy         ");
    puts("=======================");
    puts("1. Insert New Music !");
    puts("2. View My Music List !");
    puts("3. Delete Music !");
    puts("4. Exit !");
    puts("=======================");
    printf("Input [1-4] : ");
    int input;
    scanf("%d",&input);getchar();
    switch (input)
    {
    case 1:
        insert();
        break;
    case 2:
        view();
        break;
    case 3:
        removemusic();
        break;
    case 4:
        exit(1);
    default:
        break;
    }
    menu();
}

int main(){
    menu();
}