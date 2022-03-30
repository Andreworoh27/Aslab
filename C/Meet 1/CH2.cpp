#include<stdio.h>
int main(){
    int x;
    scanf("%d",&x);
    int sum = x;
    while (x>=2)
    {
        int sisa;
        sisa = x%2;
        x = x/2;
        sum+=x;
        x+=sisa;
    }
    printf("%d\n",sum);
}