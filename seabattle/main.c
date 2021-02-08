#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>


//-------------------------------------------------------------------------
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


typedef struct player{
    char name[100];
    int score;
} player;


//-------------------------------------------------------------------------
char *a=" WEC";
char *tempMap=" S";
int playersMap[2][10][10]={0};
bool playersCheck[2][10][10];
boat playersBoat[2][10];
bool flag=true;
char names[2][100];
int curT;
int playersExploded[2]={100,100};
int boatsNum[2]={10,10};
player players[1000];
int playersNum=0;
int scores[5] = {25,12,8,0,5};
int playersId[2];
bool finished=false;


//---------------------------------------------------------------------------
void printMap(int n);
bool checkPoint(point one,point two,point three);
bool checkBoat(int x,int y,boat *b,int pMap[10][10],int currP);
bool makeBoat(point i,point j,int ind,bool check[10][10],boat mBoat[10]);
void saveGame();
int loadGame();
void clearBoat(boat b,int pMap[10][10],int currP);
void start();
void update();
bool turn();
void createPM(bool check[10][10],boat pBoats[15],int n);
void createBM();
void printTempMap(int n);
point randomPoint();
void addPlayer(char name[100],int n);


int main() {
    start();
    update();
}


void printMap(int n){
    for(int j=0;j<10;j++) {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("|         |         |         |         |         |         |         |         |         |         |\n");
        printf("|");
        for (int i = 0; i < 10; i++) {
            printf("    %c    |",a[playersMap[n][j][i]]);
        }
        printf("\n");
        printf("|         |         |         |         |         |         |         |         |         |         |\n");
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
}

bool checkBoat(int x,int y,boat b[10],int pMap[10][10],int currP){
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
              clearBoat(b[i],pMap,currP);
            }
            return true;
        }
    }
    return false;
}

bool makeBoat(point i,point j,int ind,bool check[10][10],boat mBoat[10]){
    if(i.x==j.x){
        for(int b=i.y;b<=j.y;b++){
            if(check[i.x][b]){
                return false;
            }
        }
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
            if(check[b][i.y]){
                return false;
            }
        }
        for(int b=i.x;b<=j.x;b++){
            check[b][i.y]=1;
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
    if((one.x==two.x)&&(one.x==three.x)&&(three.y>=one.y&&three.y<=two.y)){
        return true;
    }else if((one.y==two.y)&&(one.y==three.y)&&(three.x>=one.x&&three.x<=two.x)){
        return true;
    }else{
        return false;
    }
}

void clearBoat(boat b,int pMap[10][10],int currP){
    point one=b.first;
    point two=b.second;
    playersExploded[currP]--;
    if(one.x==two.x){
        players[playersId[1-currP]].score+=abs(one.y-two.y);

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
        players[playersId[1-currP]].score+=abs(one.x-two.x);

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
    printf("1. Play with a Friend\n2. Play with bot\n3. Load last game\n4. Score Board\n5. Exit\n");
    scanf("%d",&n);
    if(n==1){
        printf("1. Choose from available users\n2. New user\n");
        scanf("%d",&n);
        if(n==1){
            int temb =loadGame();
            if(temb==0){
                printf("Cannot find data\n");
                start();
            }
            for (int i = 0; i < playersNum; i++) {
                printf("%d. Name: %s Score: %d", n,players[i].name, players[i].score);
            }
            scanf("%d",&n);
            strcpy(names[0],players[n].name);
            playersId[0]=n;

        }else if(n==2){
            printf("Enter first player name: \n");
            scanf("%s",names[0]);
            addPlayer(names[0],0);


        }

        printf("1. Choose from available users\n2. New user\n");
        scanf("%d",&n);
        if(n==1){
            int temb =loadGame();
            if(temb==0){
                printf("Cannot find data\n");
                start();
            }
            for (int i = 0; i < playersNum; i++) {
                printf("%d. Name: %s Score: %d", n,players[i].name, players[i].score);
            }
            scanf("%d",&n);
            strcpy(names[1],players[n].name);
            playersId[1]=n;

        }else if(n==2){
            printf("Enter second player name: \n");
            scanf("%s",names[1]);
            addPlayer(names[1],1);

        }
        createPM(playersCheck[0],playersBoat[0],0);
        createPM(playersCheck[1],playersBoat[1],1);


    }else if(n==2){
        printf("Enter your name: \n");
        scanf("%s",names[0]);
        names[1][0]='B';
        names[1][1]='O';
        names[1][2]='T';
        createPM(playersCheck[0],playersBoat[0],0);
        createBM();

    }else if(n==3){
        int temb =loadGame();
        if(temb==0){
            printf("Cannot find data\n");
            start();
        }else if(temb==1){
            printf("The last game if finished\n");
            start();
        }
    }else if(n==4){
        int temb =loadGame();
        if(temb==0){
            printf("Cannot find data\n");
            start();
            }else {


            for (int i = 0; i < playersNum; i++) {
                printf("Name: %s Score: %d", players[i].name, players[i].score);
            }
        }

    }else if(n==5){
        exit(-1);
    }
}
void createPM(bool check[10][10],boat pBoats[15],int n){
    point one,two;
    printf("Enter positions for ship of size 5: \n");
    scanf("%d %d",&one.x,&one.y);
    scanf("%d %d",&two.x,&two.y);
    makeBoat(one,two,0,check,pBoats);
    printTempMap(n);


    for(int i=1;i<3;i++){
        printf("Enter positions for ship of size 3: \n");
        scanf("%d %d",&one.x,&one.y);
        scanf("%d %d",&two.x,&two.y);
        makeBoat(one,two,i,check,pBoats);
        printTempMap(n);
    }
    for(int i=3;i<6;i++){
        printf("Enter positions for ship of size 2: \n");
        scanf("%d %d",&one.x,&one.y);
        scanf("%d %d",&two.x,&two.y);
        makeBoat(one,two,i,check,pBoats);
        printTempMap(n);


    }
    for(int i=6;i<10;i++){
        printf("Enter positions for ship of size 1: \n");
        scanf("%d %d",&one.x,&one.y);
        scanf("%d %d",&two.x,&two.y);
        makeBoat(one,two,i,check,pBoats);
        printTempMap(n);


    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

}
void printTempMap(int n){
    for(int j=0;j<10;j++) {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("|         |         |         |         |         |         |         |         |         |         |\n");
        printf("|");
        for (int i = 0; i < 10; i++) {
            printf("    %c    |",tempMap[playersCheck[n][j][i]]);
        }
        printf("\n");
        printf("|         |         |         |         |         |         |         |         |         |         |\n");
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
}


bool turn(){

    int temp = 1-curT;
    point s;
    if(strcmp(names[curT],"BOT")==0){
        s=randomPoint();
        while(!playersMap[temp][s.x][s.y]){
            s=randomPoint();
        }
        if(playersCheck[temp][s.x][s.y]){
            playersMap[temp][s.x][s.y]=2;
            checkBoat(s.x, s.y, playersBoat[temp], playersMap[temp], temp);
            printMap(temp);
            if(playersExploded[temp]==0){
                return false;
            }

            return true;

        }else{
            playersMap[temp][s.x][s.y]=1;
            printMap(temp);
            curT= 1-curT;
            return true;
        }

    }
    printf("%s now your turn\n",names[curT]);
    scanf("%d %d", &s.x, &s.y);
    if(s.x == -1){
        return false;
    }
    if(playersCheck[temp][s.x][s.y]){
        playersMap[temp][s.x][s.y]=2;
        checkBoat(s.x, s.y, playersBoat[temp], playersMap[temp], temp);
        printMap(temp);
        if(playersExploded[temp]==0){
            return false;
        }

        return true;

    }else{
        playersMap[temp][s.x][s.y]=1;
        printMap(temp);
        curT= 1-curT;
        return true;
    }
}

void update(){
    while(turn()){

    }
    if(playersExploded[0]==0||boatsNum[0]==0){
        printf("Player %s won the game",names[1]);
        flag=false;
        finished=true;
        saveGame();
    }else if(playersExploded[1]==0||boatsNum[1]==0){
        printf("Player %s won the game",names[0]);
        flag=false;
        finished=true;
        saveGame();
    }else{
        flag=false;
        finished=false;
        saveGame();
    }
}
void createBM(){
   point i;
   point j;
   i.x=0;i.y=0;j.x=0;j.y=4;
   makeBoat(i,j,0,playersCheck[1],playersBoat[1]);
   for(int k=1;k<3;k++){
       i.x=k;j.x=k;i.y=0;j.y=2;
       makeBoat(i,j,k,playersCheck[1],playersBoat[1]);
   }
   for(int k=3;k<6;k++){
       i.x=k;j.x=k;i.y=0;j.y=1;
       makeBoat(i,j,k,playersCheck[1],playersBoat[1]);
   }
   for(int k=6;k<10;k++){
       i.x=k;j.x=k;i.y=0;j.y=0;
       makeBoat(i,j,k,playersCheck[1],playersBoat[1]);
   }
}

int loadGame(){
    FILE * svd = fopen("E:/Dev/seabattle3/seabattle/saved.bin","rb");
    if(svd==NULL){
        return 0;
    }
    fread(&finished,sizeof(bool),1,svd);
    if(finished){
        fread(&playersNum,sizeof(int),1,svd);
        fread(players,sizeof(player),playersNum,svd);
        return 1;
    }
    for(int j=0;j<2;j++){
        for(int i=0;i<10;i++){
            fread(playersMap[j][i],sizeof(int),10,svd);
        }
    }
    for(int j=0;j<2;j++){
        for(int i=0;i<10;i++){
            fread(playersCheck[j][i],sizeof(int),10,svd);
        }
    }
    for(int i=0;i<2;i++){
        fread(playersBoat[i],sizeof(boat),10,svd);
    }
    for(int i=0;i<2;i++){
        fread(names[i],sizeof(char),strlen(names[i]),svd);
    }
    fread(&curT,sizeof(int),1,svd);
    fread(playersExploded,sizeof(int),2,svd);
    fread(boatsNum,sizeof(int),2,svd);
    fclose(svd);
    return 2;


}
void saveGame(){

    FILE * svd = fopen("E:/Dev/seabattle3/seabattle/saved.bin","wb");
    fwrite(&finished,sizeof(bool),1,svd);
    fwrite(&playersNum,sizeof(int),1,svd);
    fwrite(players,sizeof(player),playersNum,svd);
    for(int j=0;j<2;j++){
        for(int i=0;i<10;i++){
            fwrite(playersMap[j][i],sizeof(int),10,svd);
        }
    }
    for(int j=0;j<2;j++){
        for(int i=0;i<10;i++){
            fwrite(playersCheck[j][i],sizeof(int),10,svd);
        }
    }
    for(int i=0;i<2;i++){
        fwrite(playersBoat[i],sizeof(boat),10,svd);
    }
    for(int i=0;i<2;i++){
        fwrite(names[i],sizeof(char),strlen(names[i]),svd);
    }
    fwrite(&curT,sizeof(int),1,svd);
    fwrite(playersExploded,sizeof(int),2,svd);
    fwrite(boatsNum,sizeof(int),2,svd);
    fclose(svd);
}
point randomPoint() {
    point a;
    srand(time(0));
    a.x = (int)(rand()%10);
    a.y = (int)(rand()%10);

}
void addPlayer(char name[100],int n){
    strcmp(players[playersNum].name,name);
    players[playersNum].score = 0;
    playersId[n]=playersNum;
    playersNum++;
}



