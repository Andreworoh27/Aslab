Account* createnew(const char *email,const char *username,const char *password){
    Account *temp = (Account*)malloc(sizeof(Account));
    strcpy(temp->email,email);
    strcpy(temp->username,username);
    strcpy(temp->password,password);
    temp->left = temp->right = NULL;
    return temp;
}

Account* push(Account *root,const char *email,const char *username,const char *password){
    if(!root){
        return createnew(email,username,password);
    }
    else if (strcmp(root->email,email)>0){
        root->left = push(root->left,email,username,password);
    }
    else if (strcmp(root->email,email)<0){
        root->right = push(root->right,email,username,password);
    }
    return root;
}

bool searchemail(const char *email){
    FILE *fp = fopen("./UserData/LoginData.txt","r");
    if(fp == NULL){
        return false;
    }
    char test[150];
    fscanf(fp,"%s",test);
    if (test[0]==0)
    {
        return false;
    }
    char temp[100];
    for (int i=0;!(feof(fp));i++){
        char emailtmp[50];
        fscanf(fp,"%[^#]#%[^#]#%[^\n]\n",emailtmp,temp,temp);
        if(strcmp(email,emailtmp)==0){
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

void regis(){
    char email[100];
     do{
        puts("Email [ ends with @gmail.com and unique ] : ");
        scanf("%[^\n]",email);getchar();
        char valid[]="@gmail.com",temp[11];
        int idx = 0;
        for (int i = (strlen(email)-1)-9; i < strlen(email); i++)
        {
            temp[idx] = email[i];
            idx++;
        }
        temp[idx]='\0';
        if(strcmp(valid,temp)==0 && !searchemail(email)){
            break;
        }
        if(searchemail(email)){
            puts("Email already exist");
        }
        puts("");
    }while(true);

    char username[11];
    do{
        puts("Username [ 3 - 10 characters ] : ");
        scanf("%[^\n]",username);getchar();
        if (strlen(username)>=3 && strlen(username)<=10){
            break;
        }
        puts("");
    }while(true);

    char password[11];
    do{
        puts("Password [ 5 - 10 characters & alphabet ] : ");
        scanf("%[^\n]",password);getchar();
        bool valid = true;
        printf("%s\n",password);
        for (int i=0;i<strlen(password);i++){
            if(!((password[i]>='a'&& password[i]<='z') || (password[i]>='A'&& password[i]<='Z') || (password[i]>='0'&& password[i]<='9'))){
                valid = false;
                break;
            }
        }
        if (valid == true)
        {
            break;
        }
        puts("");
        for (int i=0;i<strlen(password);i++){
            password[i]='\0';
        }
    }while(true);
    BaseRoot=push(BaseRoot,email,username,password);
    FILE *fp = fopen("./UserData/LoginData.txt","a");
    fprintf(fp,"%s#%s#%s\n",email,username,password);
    fclose(fp);
    puts("Registered Successfully");
    puts("Press Enter to continue...");getchar();
}

Login* createnewlogin(const char *email,const char *password){
    Login *temp = (Login*)malloc(sizeof(Login));
    strcpy(temp->email,email);
    strcpy(temp->password,password);
    temp->next = NULL;
    return temp;
}

void pushlogin(int idx,const char *name,const char *pass){
    Login* temp = createnewlogin(name,pass);
    if (!headLogin[idx])
    {
        headLogin[idx]=tailLogin[idx]=temp;
        return;
    }
    tailLogin[idx]->next = temp;
    tailLogin[idx] = temp; 
    return;
}

void login(){
    char validate[225];
    FILE *fp1 = fopen("./UserData/LoginData.txt","r");
    fscanf(fp1,"%s",validate);
    if (validate[0]==0)
    {
        fclose(fp1);
        puts("There is no account!");
        return;
    }
    fclose(fp1);
    puts("Login");
    puts("=========");
    char email[100],password[11],username[50];
    bool emailcheck= false,passwordcheck= false;
    int idx=0;
    do
    {
        FILE *fp = fopen("./UserData/LoginData.txt","r");
        printf("Email   : ");
        scanf("%[^\n]",email);getchar();
        for (int i=0;!(feof(fp));i++){
            char emailtmp[100];
            fscanf(fp,"%[^#]#%[^#]#%[^\n]\n",emailtmp,validate,validate);
            if(strcmp(email,emailtmp)==0){
                emailcheck = true;
                idx = i;
                break;
            }
        }
        if(emailcheck == true){
            fclose(fp);
            break;
        }
        fclose(fp);
        puts("email doesn't exist");
    } while (true);
    
    printf("Password    : ");
    scanf("%[^\n]",password);getchar();
    FILE *fp = fopen("./UserData/LoginData.txt","r");
    for (int i=0;!(feof(fp));i++){
            char passwordtmp[50];
            fscanf(fp,"%[^#]#%[^#]#%[^\n]\n",validate,username,passwordtmp);
            if(strcmp(password,passwordtmp)==0 && idx == i){
                passwordcheck = true;
                strcpy(loginusername,username);
                break;
            }
            else{
                break;
            }
        }
    fclose(fp);

    if(passwordcheck == true && emailcheck == true){
        idx = djb2(email);
        pushlogin(idx,email,password);
        strcpy(loginemail,email);
        puts("Login Successfull");
        puts("Press enter to continue...");getchar();
        homepage();
    }
    else{
        puts("Wrong credentials");
        puts("Press enter to continue...");getchar();
    }    
    return;
}

// void printacc(Account *root){
//     if (root)
//     {
//         printacc(root->left);
//         printf("Email       : %s\n",root->email);
//         printf("Username    : %s\n",root->username);
//         printf("Password    : %s\n\n\n",root->password);
//         printacc(root->right);
//     }
// }