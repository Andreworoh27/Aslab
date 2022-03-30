#include<stdio.h>
int main(){
    int arr[30]={-1};
    int input,mod;
    scanf("%d %d",&input,&mod);
    int idx=0;
    for (int i=mod;i<=input;i+=mod){
        arr[idx]=i;
        idx++;
    }
    for(int i=29;i>=0;i--){
        if(arr[i]>0){
            if(i==0){
                printf("%d\n",arr[i]);
            }
            else printf("%d ",arr[i]);
        }
        else continue;
    }
}