#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct point{
    int x;
    int y;
}point;

typedef struct boat{
    int size;
    point first;
    point second;
    bool explode;
    int explodedB;

} boat;

char *a=" WEC";
int firstP[10][10]={0};
int secondP[10][10]={0};
bool first[10][10]={0};
bool second[10][10]={0};
boat firstB[15];
boat secondB[15];
bool flag=true;
char firstPName[100];
char secondPName[100];

void printMap();
bool checkPoint(point one,point two,point three);
bool checkBoat(int x,int y,boat *b,int pMap[10][10]);
bool makeBoat(point i,point j,int ind,bool check[10][10],boat mBoat[10]);
void saveGame();
void loadGame();
void clearBoat(boat b,int pMap[10][10]);
void start();
void update();
void turn();
void createPM(int map[10][10],bool check[10][10],boat pBoats[15]);
void createBM();


int main() {


    start();
//    while(flag){
//        update();
//    }



}


void printMap(){
    for(int j=0;j<10;j++) {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("|         |         |         |         |         |         |         |         |         |         |\n");
        printf("|");
        for (int i = 0; i < 10; i++) {
            printf("    %c    |",a[firstP[j][i]]);
        }
        printf("\n");
        printf("|         |         |         |         |         |         |         |         |         |         |\n");
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
}

bool checkBoat(int x,int y,boat b[10],int pMap[10][10]){
    point temp;
    temp.x=x;
    temp.y=y;
    for(int i=0;i<10;i++){
        if(b[i].explode){
            continue;
        }
        if(checkPoint(b[i].first, b[i].second, temp)){
            b[i].explodedB++;
            if(b[i].explodedB == b[i].size){
                b[i].explode=true;
                clearBoat(b[i],pMap);
            }
            return true;
        }
    }
    return false;
}

bool makeBoat(point i,point j,int ind,bool check[10][10],boat mBoat[10]){
    if(i.x==j.x){
        for(int b=i.y;b<=j.y;b++){
            check[i.x][b]=1;
        }
        mBoat[ind].first=i;
        mBoat[ind].second=j;
        mBoat[ind].explode=false;
        mBoat[ind].explodedB=0;
        mBoat[ind].size=i.y-j.y+1;
        return true;
    }else if(i.y==j.y){
        for(int b=i.x;b<=j.x;b++){
            check[b][i.y];
        }
        mBoat[ind].first=i;
        mBoat[ind].second=j;
        mBoat[ind].explode=false;
        mBoat[ind].explodedB=0;
        mBoat[ind].size=i.x-j.x+1;

    }else{
        return false;
    }
}
bool checkPoint(point one,point two,point three){
    if((one.x==two.x)&&(one.x=three.x)&&(three.y<=one.y&&three.y<=two.y)){
        return true;
    }else if((one.y==two.y)&&(one.y=three.y)&&(three.x<=one.x&&three.x<=two.x)){
        return true;
    }else{
        return false;
    }
}

void clearBoat(boat b,int pMap[10][10]){
    point one=b.first;
    point two=b.second;
    if(one.x==two.x){
        for(int i=one.y;i<=two.y;i++){
            pMap[one.x][i]=3;
            if(one.x>0){
                pMap[one.x-1][i]=1;

            }
            if(one.x<9){
                pMap[one.x+1][i]=1;
            }
        }
        if(one.y>0){
            pMap[one.x][one.y-1]=1;
        }
        if(two.y<9){
            pMap[two.x][two.y+1]=1;
        }
        if(one.x>0&&one.y>0){
            pMap[one.x-1][one.y-1]=1;
        }
        if(one.x<9&&one.y>0){
            pMap[one.x+1][one.y-1]=1;
        }
        if(two.x>0&&two.y<9){
            pMap[two.x-1][two.y+1]=1;
        }
        if(two.x<9&&two.y<9){
            pMap[two.x+1][two.y+1]=1;
        }


    }else if(one.y==two.y){

        for(int i=one.x;i<=two.x;i++){
            pMap[one.y][i]=3;
            if(one.y>0){
                pMap[i][one.y-1]=1;

            }
            if(one.y<9){
                pMap[i][one.y+1]=1;
            }
        }
        if(one.x>0){
            pMap[one.x-1][one.y]=1;

        }
        if(two.x<9){
            pMap[two.x+1][two.y]=1;
        }
        if(one.x>0&&one.y>0){
            pMap[one.x-1][one.y-1]=1;
        }
        if(one.x>0&&one.y<9){
            pMap[one.x-1][one.y+1]=1;
        }
        if(two.x<9&&two.y<0){
            pMap[two.x+1][two.y-1]=1;
        }
        if(two.x<9&&two.y<9){
            pMap[two.x+1][two.y+1]=1;
        }


    }
}


void start(){
    int n;
    printf("1. Play with a Friend\n2. Play with bot\n3. Load game\n4. Setting\n");
    scanf("%d",&n);
    if(n==1){
        printf("Enter first player name: \n");
        scanf("%s",firstPName);
        printf("Enter second player name: \n");
        scanf("%s",secondPName);
        createPM(firstP,first,firstB);
        createPM(secondP,second,secondB);


    }else if(n==2){
        printf("Enter your name: \n");
        scanf("%s",firstPName);
        secondPName[0]='B';
        secondPName[1]='O';
        secondPName[2]='T';
        createPM(firstP,first,firstB);

    }else if(n==3){

    }else if(n==4){

    }
}
void createPM(int map[10][10],bool check[10][10],boat pBoats[15]){
    point one,two;
    printf("Enter positions for ship of size 5: \n");
    scanf("%d %d",&one.x,&one.y);
    scanf("%d %d",&two.x,&two.y);
    makeBoat(one,two,0,check,pBoats);
    for(int i=1;i<3;i++){
        printf("Enter positions for ship of size 3: \n");
        scanf("%d %d",&one.x,&one.y);
        scanf("%d %d",&two.x,&two.y);
        makeBoat(one,two,i,check,pBoats);
    }
    for(int i=3;i<6;i++){
        printf("Enter positions for ship of size 2: \n");
        scanf("%d %d",&one.x,&one.y);
        scanf("%d %d",&two.x,&two.y);
        makeBoat(one,two,i,check,pBoats);
    }
    for(int i=6;i<10;i++){
        printf("Enter positions for ship of size 1: \n");
        scanf("%d %d",&one.x,&one.y);
        scanf("%d %d",&two.x,&two.y);
        makeBoat(one,two,i,check,pBoats);
    }

}
void creatBM(){



}





