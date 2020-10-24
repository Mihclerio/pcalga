#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int f[20][20],len=2, mancat=1, nr=0, gameOver=0;
char c='d';

struct snake{

    int x,y;

};

struct snake snk[400],mar;

void delay(double number_of_seconds)
{
    double milli_seconds=1000 * number_of_seconds;

    clock_t start_time=clock();

    while(clock()<start_time+milli_seconds);
}

void setMar()
{
    mancat=0;

    srand(time(NULL));

    while(1) {
        mar.x=rand()%20;
        mar.y=rand()%20;

        if(!f[mar.x][mar.y]) {
            f[mar.x][mar.y]=3;
            break;
        }
    }
}

void drawTable()
{
    for(int i=0;i<20;i++) {
        for(int j=0;j<20;j++) {
            switch(f[i][j]) {
                case 0:printf("~ "); break;
                case 1:printf("@ "); break;
                case 2:printf("# "); break;
                case 3:printf("X "); break;
            }
        }
        printf("\n");
    }
}

void sarpePas()
{
    struct snake last=snk[len-1];
    for(int i=len-1;i>0;i--)
        snk[i]=snk[i-1];

    switch(c) {
        case 'w':snk[0].x--; break;
        case 'd':snk[0].y++; break;
        case 's':snk[0].x++; break;
        case 'a':snk[0].y--; break;
    }

    if(snk[0].x<0 || snk[0].x==20 || snk[0].y<0 || snk[0].y==20) gameOver=1; else {
        if(f[snk[0].x][snk[0].y]==3) nr=1;

        if(nr) {
            nr=0;
            snk[len]=last;
            len++;
            mancat=1;
        }
    }

    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++)
            if(f[i][j]==2 || f[i][j]==1) f[i][j]=0;

    for(int i=1;i<len;i++)
        f[snk[i].x][snk[i].y]=2;

    if(!(snk[0].x<0 || snk[0].x==20 || snk[0].y<0 || snk[0].y==20)) f[snk[0].x][snk[0].y]=1;

    int cur=0;
    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++)
            if(f[i][j]==2) cur++;

    if(cur!=len-1) gameOver=1;
}

int main()
{
    snk[0].x=9;
    snk[0].y=9;
    f[9][9]=1;
    snk[1].x=9;
    snk[1].y=8;
    f[9][8]=2;
    while(1) {
        system("cls");

        if(mancat)
            setMar();

        drawTable();

        char aux;
        if ( kbhit() )
            aux=getch();
        if(aux=='a' || aux=='w' || aux=='d' || aux=='s') {
            if(!(c=='s' && aux=='w') && !(c=='d' && aux=='a') && !(c=='w' && aux=='s') && !(c=='a' && aux=='d'))
                c=aux;
        }

        sarpePas();

        if(gameOver) {
            system("cls");
            drawTable();
            break;
        }

        delay(0.25);
    }

    return 0;
}
