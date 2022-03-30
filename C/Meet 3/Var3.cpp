#include<stdio.h>
#include<string.h>
int main(){
    int n;
    scanf("%d",&n);getchar();
    char string[n][101];
    for (int i=0;i<n;i++){
        scanf("%s",string[i]);getchar();
    }
    char input[101];
    scanf("%s",input);getchar();
    bool valid = true;
    for (int i = 0; i < n; i++)
    {
        int counter = 0;
        int flag = 0;
        int idx=0;
        for (int k=0;input[k]!='\0';k++){
            if(idx == strlen(string[i])){
                if(strlen(input)-strlen(string[i])>=1){
                    flag = 1;
                    break;
                }
                break;
            }
            if(counter>1){
                flag =1;
                break;
            }
            if(input[k]!=string[i][idx]){
                counter++;
            }
            idx++;
        }
        printf("%d\n",counter);
        if (flag == 1 ){
            valid = false;
        }
        else if (flag ==0){
            valid = true;
        }
    }

    if(valid == false){
        puts("no");
    }
    else puts("yes");
}