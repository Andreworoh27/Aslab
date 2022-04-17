void rewritefile(const char *codeorigin,int quantitadd){
    if(!headCart){
        return;
    }
    char path[150];
    strcpy(path,"./UserCarts/");
    strcat(path,loginemail);
    strcat(path,".txt");
    path[strlen(path)]='\0';
    char code[50][10],name[50][100];
    double price[50];
    int quantity[50],counter=0,same[40]={0},samecount = 0;
    FILE *fp = fopen(path,"r");
    if (fp == NULL){

    }
    else{
        for (int i=0;!(feof(fp));i++){
            fscanf(fp,"%[^#]#%[^#]#$%lf#%d\n",code[i],name[i],&price[i],&quantity[i]);
            printf("%s %s %.2lf %d\n",code[i],name[i],price[i],quantity[i]);
            if(strcmp(codeorigin,code[i])==0){
                same[samecount]=i;
                samecount++;
            }
            counter++;
        }
        fclose(fp);
    }

    fp = fopen(path,"w");
    Cart*curr = headCart;
    while (curr != NULL)
    {
        bool valid = true;
        for (int i = 0; i < counter; i++)
        {
            if(strcmp(code[i],curr->code)==0){
                printf("%s\n",code[i]);
                valid = false;
                break;
            }
        }
        if(valid == true){
            fprintf(fp,"%s#%s#$%.2lf#%d\n",curr->code,curr->name,curr->price,curr->quantity);
        }
        curr = curr->next;
    }
    fclose(fp);

    if (counter>0)
    {
        fp = fopen(path,"a");
        int idx=0;
        for (int i = 0; i < counter; i++)
        {
            if (i==same[idx])
            {
                quantity[i]+=quantitadd;
                idx++;
            }
            fprintf(fp,"%s#%s#$%.2lf#%d\n",code[i],name[i],price[i],quantity[i]);   
        }
        fclose(fp);
    }
    return;
}

Cart* createnewcart(const char *code,const char *name,const double price,int quantity){
    Cart *temp = (Cart*)malloc(sizeof(Cart));
    strcpy(temp->code,code);
    strcpy(temp->name,name);
    temp->price = price;
    temp->quantity = quantity;
    temp->next = temp->prev = NULL;
    return temp;
}

bool searchcart(const char *code){
    Cart*curr = headCart;
    while (curr != tailCart->next)
    {
        if (strcmp(code,curr->code)==0)
        {
            return true;
            break;
        }
        curr = curr->next;
    }
    return false;
}

void pushcart(const char *code,const char *name,double price,int quantity){
    Cart *temp = createnewcart(code,name,price,quantity);
    if (!headCart)
    {
        headCart = tailCart = temp;
    }
    else{
        if(searchcart(code)){
            puts("item quantity in cart will be added");
            Cart*curr = headCart;
            while (curr != tailCart->next)
            {
                if (strcmp(code,curr->code)==0)
                {
                    curr->quantity+=quantity;
                    break;
                }
                curr = curr->next;
            }
        }
        else if(quantity>=headCart->quantity){
            headCart->prev = temp;
            temp->next = headCart;
            headCart = temp;
        }
        else if (quantity<=tailCart->quantity){
            tailCart->next = temp;
            temp->prev = tailCart;
            tailCart = temp;
        }
        else{
            Cart *curr = headCart;
            while (curr->quantity >= quantity)
            {
                curr = curr->next;
            }
            temp->prev = curr->prev;
            temp->next = curr;
            curr->prev->next = temp;
            curr->prev = temp;
        }
    }
    
}

Product* createnewproduct(const char *code,const char *name,const double price){
    Product *temp = (Product*)malloc(sizeof(Product));
    strcpy(temp->code,code);
    strcpy(temp->name,name);
    temp->price = price;
    temp->next = temp->prev = NULL;
    return temp;
}

void pushproduct(int idx,const char *code,const char *name,const double price){
    Product* temp = createnewproduct(code,name,price);
    if (!headProduct[idx])
    {
        headProduct[idx]=tailProduct[idx]=temp;
    }
    else{
        tailProduct[idx]->next = temp;
        temp->prev = tailProduct[idx];
        tailProduct[idx]= temp;
    }
    
}

void viewproduct(){
    FILE *fp=fopen("./Products/ProductList.txt","r");
    char code[50][10],name[50][100];
    double price[50];
    int nomor = 1,counter = 1;
    int idx;
    for (int i = 0;!(feof(fp)); i++)
    {
        fscanf(fp,"%[^#]#%[^#]#$%lf\n",code[i],name[i],&price[i]);
        printf("[%2d.] | %-7s | %-40s | $%.2lf\n",nomor,code[i],name[i],price[i]);
        if(nomor%10==0){
            printf("\n%d %d\n",nomor,counter);
            bool no=false,next=false;
            do{
                printf("Do you want to add any of the product to you cart [Yes | No | Next] (case insensitive) : ");
                char input[10];
                scanf("%s",input);getchar();
                for(int j=0;j<strlen(input);j++){
                    input[j]=toupper(input[j]);
                }
                if (strcmp(input,"NEXT")==0)
                {
                    next = true;
                    break;
                }
                else if (strcmp(input,"NO")==0)
                {
                    no = true;
                    break;
                }
                else if (strcmp(input,"YES")==0)
                {
                    int number;
                    do
                    {
                        printf("Enter The product's number [ 1-10 ] : ");
                        scanf("%d",&number);getchar();
                        if(number>=1 && number<=10){
                            number = (counter-10)+(number-1);
                            number = abs(number);
                            break;
                        }
                    } while (true);
                    int quantitiy;
                    do
                    {
                        printf("Enter The product's quantity [ > 0 ] : ");
                        scanf("%d",&quantitiy);getchar();
                        if(quantitiy>=1){
                            break;
                        }
                    } while (true);
                    
                    pushcart(code[number],name[number],price[number],quantitiy);
                    rewritefile(code[number],quantitiy);
                }
            }while(true);
            if(no == true){
                return;
            }
            else if (next == true){
                nomor = 1;
                counter++;
                continue;
            }
        }
        nomor++,counter++;
    }
    fclose(fp);
}

void generateproduct(){
    FILE *fp=fopen("./Products/ProductList.txt","r");
    char code[50][10],name[50][100];
    double price[50];
    int idx;
    for (int i = 0;!(feof(fp)); i++)
    {
        fscanf(fp,"%[^#]#%[^#]#$%lf\n",code[i],name[i],&price[i]);
        idx = djb2(code[i]);
        pushproduct(idx,code[i],name[i],price[i]);
    }
    // for(int i=0;i<SIZE;i++){
    //     printf("table %d: \n",i);
    //     Product *curr = headProduct[i];
    //     while (curr != tailProduct[i]->next)
    //     {
    //         printf("%s %s $%.2lf\n",curr->code,curr->name,curr->price);
    //         curr = curr->next;
    //     }
    //     printf("\n\n");
    // }
}

void searchproduct(){
    int index;
    printf("Enter the products that you're looking for : ");
    char string[100];
    scanf("%[^\n]",string);getchar();
    int nomor = 1;
    char code[50][10],name[50][100];
    double price[50];
    bool ada = false;
    for (int i = 0; i < SIZE; i++)
    {
        if (headProduct[i]!=NULL)
        {
            Product *curr = headProduct[i];
            while (curr != NULL)
            {
                if (strcasestr(curr->name,string)){
                    bool valid = true;
                    for (int i = 0; i < nomor; i++)
                    {
                        if(strcmp(code[i],curr->code)==0){
                            valid = false;
                            break;
                        }
                    }
                    if(valid == true){
                        strcpy(code[nomor-1],curr->code);
                        strcpy(name[nomor-1],curr->name);
                        price[nomor-1]=curr->price; 
                        printf("[%2d.] | %-7s | %-40s | $%.2lf\n",nomor,curr->code,curr->name,curr->price);
                        nomor++;
                    }
                    ada = true;
                }
                curr = curr->next;
            }
        }
    }

    if (ada == false)
    {
        puts("We're sorry but the product that you're looking for doesn't seem to exist yet...");getchar();
        return;
    }
    

    do
    {
        printf("Do you want to add any of the product to you cart [Yes | No ] (case insensitive) : ");
        char input[10];
        scanf("%s",input);getchar();
        for(int j=0;j<strlen(input);j++){
            input[j]=toupper(input[j]);
        }
        if (strcmp(input,"NO")==0)
        {
            return;
        }
        else if (strcmp(input,"YES")==0)
        {
            int number;
            do
            {
                printf("Enter The product's number [ 1-%d ] : ",nomor-1);
                scanf("%d",&number);getchar();
                if(number>=1 && number<nomor){
                    number-=1;
                    break;
                }
            } while (true);
            int quantitiy;
            do
            {
                printf("Enter The product's quantity [ > 0 ] : ");
                scanf("%d",&quantitiy);getchar();
                if(quantitiy>=1){
                    break;
                }
            } while (true);
            pushcart(code[number],name[number],price[number],quantitiy);
            rewritefile(code[number],quantitiy);
            break;
        }
    } while (true);
    return;
}

int generate_random(int low,int high){
    return (rand()%(high - low+1))+low;
}

void checkout(const char code[][10],const char name[][100],int quantitiy[],int counter){
    char path[150];
    strcpy(path,"./TransactionHeader/");
    strcat(path,loginemail);
    strcat(path,".txt");
    path[strlen(path)]='\0';
    FILE *fp = fopen(path,"a");
    char id[7];
    id[0]='T';
    id[1]='R';
    id[2]='-';
    id[3]=generate_random(0,9)+'0';
    id[4]=generate_random(0,9)+'0';
    id[5]=generate_random(0,9)+'0';
    id[6]='\0';

    char date[50];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date,"%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(fp,"%s#%s#%s\n",id,loginusername,date);
    fclose(fp);

    char path2[150];
    strcpy(path2,"./TransactionDetails/");
    strcat(path2,id);
    strcat(path2,".txt");
    fp = fopen(path2,"a");
    for (int i = 0; i < counter; i++)
    {
        fprintf(fp,"%s#%s#%d\n",id,code[i],quantitiy[i]);
    }
    fclose(fp);

    char path3[150];
    strcpy(path3,"./UserCarts/");
    strcat(path3,loginemail);
    strcat(path3,".txt");
    fopen(path3,"w");
    fprintf(fp,"");
    fclose(fp);
}

void remove(){
    char path[150];
    strcpy(path,"./UserCarts/");
    strcat(path,loginemail);
    strcat(path,".txt");
    path[strlen(path)]='\0';
    char code[50][10],name[50][100];
    double price[50];
    int quantity[50],counter=0;
    FILE *fp = fopen(path,"r");
    if (fp == NULL){
    }
    else{
        for (int i=0;!(feof(fp));i++){
            fscanf(fp,"%[^#]#%[^#]#$%lf#%d\n",code[i],name[i],&price[i],&quantity[i]);
            printf("%s %s %.2lf %d\n",code[i],name[i],price[i],quantity[i]);
            counter++;
        }
        fclose(fp);
    }
    int input;
    do
    {
        printf("Which product do you want to delete [ 1-%d ] : ",counter);
        scanf("%d",&input);getchar();
        if(input>=1 && input<=counter){
            input-=1;
            break;
        }
    } while (true);

    fp = fopen(path,"w");
    for (int i=0;i<counter;i++){
        if(i!=input){
            fprintf(fp,"%s#%s#$%.2lf#%d\n",code[i],name[i],price[i],quantity[i]);
        }
    }
    fclose(fp);
}

void update(){
    char path[150];
    strcpy(path,"./UserCarts/");
    strcat(path,loginemail);
    strcat(path,".txt");
    path[strlen(path)]='\0';
    char code[50][10],name[50][100];
    double price[50];
    int quantity[50],counter=0;
    FILE *fp = fopen(path,"r");
    if (fp == NULL){
    }
    else{
        for (int i=0;!(feof(fp));i++){
            fscanf(fp,"%[^#]#%[^#]#$%lf#%d\n",code[i],name[i],&price[i],&quantity[i]);
            printf("%s %s %.2lf %d\n",code[i],name[i],price[i],quantity[i]);
            counter++;
        }
        fclose(fp);
    }
    int input;
    do
    {
        printf("Which product do you want to update [ 1-%d ] : ",counter);
        scanf("%d",&input);getchar();
        if(input>=1 && input<=counter){
            input-=1;
            break;
        }
    } while (true);

    do
    {
        int quantityinput;
        printf("Enter the new quantity [ >0 ] : ");
        scanf("%d",&quantityinput);getchar();
        if(quantityinput>0){
            quantity[input]=quantityinput;
            break;
        }
    } while (true);
    
    fp = fopen(path,"w");
    for (int i=0;i<counter;i++){
        fprintf(fp,"%s#%s#$%.2lf#%d\n",code[i],name[i],price[i],quantity[i]);
    }
    fclose(fp);
}

void managecart(){
    char path[150];
    strcpy(path,"./UserCarts/");
    strcat(path,loginemail);
    strcat(path,".txt");
    FILE *fp = fopen(path,"r");
    if (fp==NULL)
    {
        puts("no item");getchar();
        return;
    }
    
    char code[50][10],name[50][100];
    double price[50];
    int quantity[50],counter=0;

    for (int i=0;!(feof(fp));i++){
        fscanf(fp,"%[^#]#%[^#]#$%lf#%d\n",code[i],name[i],&price[i],&quantity[i]);
        printf("%-7s | %-50s | %.2lf %d\n",code[i],name[i],price[i],quantity[i]);
        counter++;
    }
    fclose(fp);

    do
    {
        printf("What do you want to do? [ Update | Delete | Checkout | Exit ] (case insensitive) : ");
        char input[15];
        scanf("%s",input);getchar();
        for (int i=0;i<strlen(input);i++){
            input[i]=tolower(input[i]);
        }
        if (strcmp(input,"checkout")==0){
            checkout(code,name,quantity,counter);
            break;
        }
        else if (strcmp(input,"delete")==0){
            remove();
            break;
        }
        else if (strcmp(input,"update")==0){
            update();
            break;
        }
    } while (true);
    return;
}

void viewhistory(){
    char path[150];
    strcpy(path,"./TransactionHeader/");
    strcat(path,loginemail);
    strcat(path,".txt");
    FILE *fp = fopen(path,"r");
    for (int i = 0; !(feof(fp)); i++)
    {
        char code[10],uname[50],date[100];
        fscanf(fp,"%[^#]#%[^#]#%[^\n]\n",code,uname,date);
        printf("[%2d.] | %-7s | %-20s | %s |\n",i+1,code,uname,code);
    }
    fclose(fp);
    return;
}

// utilities :
Cart* popheadcart(){
    if(!headCart){
        return NULL;
    }
    else if(headCart = tailCart){
        free(headCart);
        headCart = NULL;
        return NULL;
    }
    else{
        Cart *temp = headCart->next;
        free(headCart);
        temp->prev = NULL;
        headCart = temp;
        return headCart;
    }
}

void popallcart(){
    if(!headCart){
        return;
    }
    Cart *curr = headCart;
    while (curr != NULL)
    {
        curr = popheadcart();
    }
    
}
void updatecart(){
    popallcart();
    char path[150];
    strcpy(path,"./UserCarts/");
    strcat(path,loginemail);
    strcat(path,".txt");
    FILE *fp = fopen(path,"r");
    char code[50][10],name[50][100];
    double price[50];
    int quantity[50];
    int nomor = 1,counter = 1;
    int idx;
    for (int i = 0;!(feof(fp)); i++)
    {
        fscanf(fp,"%[^#]#%[^#]#$%lf\n",code[i],name[i],&price[i]);
        pushcart(code[i],name[i],price[i],quantity[i]);
    }
    fclose(fp);
}