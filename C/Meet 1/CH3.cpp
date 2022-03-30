#include<stdio.h>
#include<string.h>
int main(){
    char string[101];
    scanf("%s",string);getchar();
    char sub[101];
    scanf("%s",sub);getchar();
    int sublen = strlen(sub);
    char out[101];
    strcpy(out,string);
    int number = 0;
    while (true)
    {
        char temp[101];
        strcpy(temp,string);
        bool valid = false;
        int idx=0;
        for (int i=0;temp[i]!='\0';i++){
            if (valid==true)
            {
                for (int k = 0; k<sublen ; k++)
                {
                    temp[idx]=' ';
                    idx--;
                }
                
                break;
            }
            idx=i;
            for(int k = 0;k<sublen;k++){
                if(temp[idx]==sub[k]){
                    if(k == sublen-1){
                        valid = true;
                        break;
                    }
                    idx++;
                }
                else{
                    break;
                }
            }
        }
        if (valid==false)
        {
            break;
        }
        
        char tmp[101];
        idx=0;
        for (int i=0;temp[i]!='\0';i++){
            if (temp[i]!=' ')
            {
                tmp[idx]=temp[i];
                idx++;
            }
            else continue;
        }
        tmp[idx]='\0';
        strcpy(string,tmp);
        string[idx]='\0';
        number++;
        printf("%d. %s\n",number,string);
    }
    printf("Total %s in %s: %d\n",sub,out,number);
}