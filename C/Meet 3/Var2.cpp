#include<stdio.h>
int main(){
    int money,price,discount,minimum;
    scanf("%d %d %d %d",&money,&price,&discount,&minimum);
    int counter =0;
    while (true)
    {
        if(price - discount >= minimum){
            price-=discount;
        }
        else if (price - discount < minimum){
            price = minimum;
        }
        if(money-price>=0){
            money-=price;
            counter++;
        }
        else break;
    }
    printf("%d\n",counter);
}  