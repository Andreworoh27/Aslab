#include<stdio.h>
int main(){
    int a,b;
    scanf("%d %d",&a,&b);
    bool flag = false;
    int counter = 0;
    while (flag==false)
    {
        if(a==0 && b!=0){
            flag = true;
            counter++;
            break;
        }
        if(a > b){
            a = a-b;
        }
        else if (b > a){
            b = b - a;
        }
        else{
            a = 0;
        }
        counter++;
    }
    printf("%d\n",counter);
}