#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int min=100000000;
    int valid = 0;
    for(int i=0;i<n;i++){
        int temp=0;
        int flag =0;
        for(int k=i+1;k<n;k++){
            if(arr[k] == arr[i]){
                temp++;
                flag=1; 
                break;
            }
            else temp++;
        }
        if(temp < min && flag ==1){
            valid = 1;
            min = temp;
        }
    }
    if (valid == 0) printf("-1\n");
    else printf("%d\n",min);
}