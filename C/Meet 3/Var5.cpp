#include<stdio.h>
int map[9][9];
bool horizontal(){
    for (int i=0;i<9;i++){
        int arr[9]={0};
        for (int k=0;k<9;k++){
            arr[map[i][k]-1]++;
        }
        for (int k=0;k<9;k++){
            if(arr[k]>1 || arr[k]==0){
                return false;
            }
        }
    }
    return true;
}

bool vertical(){
    for (int i=0;i<9;i++){
        int arr[9]={0};
        for (int k=0;k<9;k++){
            arr[map[k][i]-1]++;
        }
        for (int k=0;k<9;k++){
            if(arr[k]>1 || arr[k]==0){
                return false;
            }
        }
    }
    return true;
}

bool grid(){
    for (int i=0;i<9;i+=3){
        for (int j=0;j<9;j+=3){
            int arr[9]={0};
            for (int x=i;x<i+3;x++){
                for (int y=j;y<j+3;y++){
                    arr[map[x][y]-1]++;
                }
            }
            for (int k=0;k<9;k++){
                if(arr[k]>1 || arr[k]==0){
                    return false;
                }
            }
        }
    }
    return true;
}

int main(){
    for (int i=0;i<9;i++){
        for (int k=0;k<9;k++){
            scanf("%d",&map[i][k]);
        }
    }
    // validation check
    if(horizontal() && vertical() && grid()){
        puts("yes");
    }
    else puts("no");
    
}