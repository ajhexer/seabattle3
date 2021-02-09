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
char names[2][100];
int curT;
int playersExploded[2]={10,10};
player players[1000];
int playersNum=0;
int scores[5] = {25,12,8,0,5};
int playersId[2];
bool finished=false;
int lens[2];

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
void autoPM(bool check[10][10],boat pBoats[10],int n);



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
        }else if(checkPoint(b[i].first, b[i].second, temp)){
             b[i].explodedB+=1;
            if(b[i].explodedB >= b[i].size){
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
        mBoat[ind].size=j.y-i.y+1;
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
        mBoat[ind].size=j.x-i.x+1;

    }else{
        return false;
    }
}
bool checkPoint(point one,point two,point three){
    if((one.x==two.x)&&(one.x==three.x)&&(three.y>=one.y)&&(three.y<=two.y)){
        return true;
    }else if((one.y==two.y)&&(one.y==three.y)&&(three.x>=one.x)&&(three.x<=two.x)){
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
        players[playersId[1-currP]].score+=scores[abs(one.y-two.y)];

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
        players[playersId[1-currP]].score+=scores[abs(one.x-two.x)];

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
        if(two.x<9&&two.y>0){
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
            }else if(temb==3){
                printf("There is no available user!!\n\n");
                start();
            }
            for (int i = 0; i < playersNum; i++) {
                printf("%d. Name: %s Score: %d\n", i+1,players[i].name, players[i].score);
            }
            scanf("%d",&n);
            strcpy(names[0],players[n].name);
            lens[0]=strlen(names[0]);
            playersId[0]=n;

        }else if(n==2){
            printf("Enter first player name: \n");
            scanf("%s",names[0]);
            lens[0]=strlen(names[0]);
            addPlayer(names[0],0);


        }

        printf("1. Choose from available users\n2. New user\n");
        scanf("%d",&n);
        if(n==1){
            int temb =loadGame();
            if(temb==0){
                printf("Cannot find data\n");
                start();
            }else if(temb==3){
                printf("There is no available user!!\n\n");
                start();
            }
            for (int i = 0; i < playersNum; i++) {
                printf("%d. Name: %s Score: %d\n", i+1,players[i].name, players[i].score);
            }
            scanf("%d",&n);
            strcpy(names[1],players[n].name);
            lens[1]=strlen(names[1]);
            playersId[1]=n;

        }else if(n==2){
            printf("Enter second player name: \n");
            scanf("%s",names[1]);
            lens[1]=strlen(names[1]);
            addPlayer(names[1],1);

        }
        printf("1. Auto generate map\n2. Manual\n");
        scanf("%d",&n);
        if(n==1){
            autoPM(playersCheck[0],playersBoat[0],0);

        }else{
            createPM(playersCheck[0],playersBoat[0],0);

        }
        printf("1. Auto generate map\n2. Manual\n");
        scanf("%d",&n);
        if(n==1){
            autoPM(playersCheck[1],playersBoat[1],1);

        }else{
            createPM(playersCheck[1],playersBoat[1],1);

        }
    }else if(n==2){
        printf("1. Choose from available users\n2. New user\n");
        scanf("%d",&n);
        if(n==1){
            int temb =loadGame();
            if(temb==0){
                printf("Cannot find data\n");
                start();
            }else if(temb==3){
                printf("There is no available user!!\n\n");
                start();
            }
            for (int i = 0; i < playersNum; i++) {
                printf("%d. Name: %s Score: %d\n", i+1,players[i].name, players[i].score);
            }
            scanf("%d",&n);
            strcpy(names[0],players[n].name);
            lens[0]=strlen(names[0]);
            playersId[0]=n;

        }else if(n==2){
            printf("Enter first player name: \n");
            scanf("%s",names[0]);
            lens[0]=strlen(names[0]);
            addPlayer(names[0],0);


        }
        names[1][0]='B';
        names[1][1]='O';
        names[1][2]='T';
        lens[1]=strlen(names[1]);
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
        }else if(temb==3){
            printf("There is no last game!\n\n");
            start();
        }else{
            printMap(1-curT);
            return;
        }
    }else if(n==4){
        int temb =loadGame();
        if(temb==0){
            printf("Cannot find data\n");
            start();
        }else if(temb==3){
            printf("ScoreBoard is empty!!\n\n");
            start();

        }else {


            for (int i = 0; i < playersNum; i++) {
                printf("%d. Name: %s Score: %d\n", i+1,players[i].name, players[i].score);
            }
            printf("\n\n");
            start();
        }

    }else if(n==5){
        exit(-1);
    }
}
void createPM(bool check[10][10],boat pBoats[10],int n){
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
        while(playersMap[temp][s.x][s.y]){
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
    }if(playersMap[temp][s.x][s.y]){
        printMap(temp);
        return true;
    }else if(playersCheck[temp][s.x][s.y]){
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
    if(playersExploded[0]==0){
        printf("Player %s won the game",names[1]);
        finished=true;
        saveGame();
    }else if(playersExploded[1]==0){
        printf("Player %s won the game",names[0]);
        finished=true;
        saveGame();
    }else{
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
        i.x=k;j.x=k;i.y=k%2==0 ? 0 : 7;j.y=k%2==0 ? 2 : 9;
        makeBoat(i,j,k,playersCheck[1],playersBoat[1]);

    }
    for(int k=3;k<6;k++){
        i.x=k;j.x=k;i.y=k%2==0 ? 0 : 8;j.y=k%2==0 ? 1 : 9;
        makeBoat(i,j,k,playersCheck[1],playersBoat[1]);

    }
    for(int k=6;k<10;k++){
        i.x=k;j.x=k;i.y=k%2==0 ? 0 : 9;j.y=k%2==0 ? 0 : 9;
        makeBoat(i,j,k,playersCheck[1],playersBoat[1]);

    }
}

int loadGame(){
    FILE * svd = fopen("C:/seabattle3/seabattle/saved.bin","rb");
    if(svd==NULL){
        fclose(svd);
        return 0;
    }
    fseek(svd,0,SEEK_END);
    if(ftell(svd)==0){
        fclose(svd);
        return 3;
    }
    fseek(svd,0,SEEK_SET);
    fread(&finished,sizeof(bool),1,svd);
    if(finished){
        fread(&playersNum,sizeof(int),1,svd);
        fread(players,sizeof(player),playersNum,svd);
        fclose(svd);
        return 1;
    }
    fread(&playersNum,sizeof(int),1,svd);
    fread(players,sizeof(player),playersNum,svd);
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
    fread(lens,sizeof(int),2,svd);
    for(int i=0;i<2;i++){
        fread(names[i],sizeof(char),lens[i],svd);
    }
    fread(&curT,sizeof(int),1,svd);
    fread(playersExploded,sizeof(int),2,svd);
    fread(playersId,sizeof(int),2,svd);
    fclose(svd);
    return 2;


}
void saveGame(){

    FILE * svd = fopen("C:/seabattle3/seabattle/saved.bin","wb");
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
    fwrite(lens,sizeof(int),2,svd);
    for(int i=0;i<2;i++){
        fwrite(names[i],sizeof(char),lens[i],svd);
    }
    fwrite(&curT,sizeof(int),1,svd);
    fwrite(playersExploded,sizeof(int),2,svd);
    fwrite(playersId,sizeof(int),2,svd);
    fclose(svd);
}
point randomPoint() {
    point a;
    srand(time(0));
    a.x = (int)(rand()%10);
    a.y = (int)(rand()%10);

}
void addPlayer(char name[100],int n){
    strcpy(players[playersNum].name,name);
    players[playersNum].score = 0;
    playersId[n]=playersNum;
    playersNum++;
}
void autoPM(bool check[10][10],boat pBoats[10],int n){
    point i;
    point j;
    i.x=0;i.y=0;j.x=0;j.y=4;
    makeBoat(i,j,0,check,pBoats);
    printTempMap(n);
    for(int k=1;k<3;k++){
        i.x=k;j.x=k;i.y=k%2==0 ? 0 : 7;j.y=k%2==0 ? 2 : 9;
        makeBoat(i,j,k,check,pBoats);
    }
    for(int k=3;k<6;k++){
        i.x=k;j.x=k;i.y=k%2==0 ? 0 : 8;j.y=k%2==0 ? 1 : 9;
        makeBoat(i,j,k,check,pBoats);
    }
    for(int k=6;k<10;k++){
        i.x=k;j.x=k;i.y=k%2==0 ? 0 : 9;j.y=k%2==0 ? 0 : 9;
        makeBoat(i,j,k,check,pBoats);
        printTempMap(n);
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


