#include<stdio.h>
char map[21][21];
int n;

void flood(int x,int y){
    if(map[x][y]=='\0'||map[x][y]=='\n'||map[x][y]=='#'||x<0||y<0||x>n||y>n){
        return;
    }
    map[x][y]='#';

    flood(x-1,y);
    flood(x+1,y);
    flood(x,y+1);
    flood(x,y-1);
}

int main(){
    scanf("%d",&n);getchar();
    for (int i=0;i<n;i++){
        scanf("%[^\n]",map[i]);getchar();
        map[i][n]='\0';
    }
    int x=0,y=0;
    for (int i = 0; i < n; i++)
    {
        for(int k=0; k < n; k++){
            if(map[i][k] == 'D'){
                x = i,y=k;
                break;
            }
        }
    }
    flood(x,y);
    bool flag = true;
    for (int i=0;i<n;i++){
        int tmp=0;
        for(int k=0; k < n; k++){
            if(map[i][k] == '.'){
                tmp=1;
                flag = false;
                break;
            }
        }
        if (tmp==1){
            break;
        }
    }
    if(flag == false)puts("yes");
    else puts("no");

}