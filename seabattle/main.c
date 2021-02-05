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
    point one;
    point second;

} boat;

char *a="WCE";
int firstP[10][10]={0};
int secondP[10][10]={0};
boat firstB[15];
boat secondB[15];

void printMap();
void checkBoat();
void makeBoat();


int main() {




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