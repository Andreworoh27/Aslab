#include<stdio.h>
int main(){
    int tc;
    scanf("%d",&tc);getchar();
    int point=0;
    for (int i=0;i<tc;i++){
        char C;
        scanf("%c",&C);getchar();
        C >= 'a' && C <='z' ? C-=32:C=C;
        if (C=='W')
        {
            point+=3;
        }
        else if (C == 'D'){
            point++;
        }
    }
    printf("%d\n",point);
}