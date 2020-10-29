#include <stdio.h>
#include <time.h>

int w[22][22], gameOver, score;

void delay(double number_of_seconds)
{
    double milli_seconds=1000 * number_of_seconds;

    clock_t start_time=clock();

    while(clock()<start_time+milli_seconds);
}

void startGame()
{
    for(int i=0;i<22;i++) {
        w[0][i]=-1;
        w[i][0]=-1;
        w[21][i]=-1;
        w[i][21]=-1;
    }

    for(int i=1;i<21;i++)
        for(int j=1;j<21;j++)
            w[i][j]=0;

    gameOver=0;
    score=0;
}

void snakeGame()
{
    startGame();
    char c='d';

    struct snake {
        int x,y;
    };

    struct snake snk[400];
    int len=2, apple=0;
    snk[0].x=10;
    snk[0].y=10;
    snk[1].x=10;
    snk[1].y=9;
    w[10][10]=1;
    w[10][9]=2;

    void drawTable()
    {
        for(int i=0;i<22;i++) {
            for(int j=0;j<22;j++)
                switch(w[i][j]) {
                    case -1: printf("# "); break;
                    case 0: printf("  "); break;
                    case 1: gameOver ? printf("X ") : printf("@ "); break;
                    case 2: printf("o "); break;
                    case 3: printf("0 "); break;
                }
            printf("\n");
        }
    }

    void snakeRun()
    {
        struct snake last=snk[len-1];
        for(int i=len-1;i>0;i--)
            snk[i]=snk[i-1];

        switch(c) {
            case 'd': snk[0].y++; break;
            case 's': snk[0].x++; break;
            case 'a': snk[0].y--; break;
            case 'w': snk[0].x--; break;
        }

        if(w[snk[0].x][snk[0].y]==3) {
            w[snk[0].x][snk[0].y]=0;
            apple=0;
            snk[len]=last;
            len++;
            score+=len-2;
        } else {
            w[last.x][last.y]=0;
        }

        if(w[snk[0].x][snk[0].y]==2) {
            gameOver=1;
        }

        if(snk[0].x==0 || snk[0].x==21 || snk[0].y==0 || snk[0].y==21) gameOver=1;

        for(int i=1;i<=20;i++)
            for(int j=1;j<=20;j++)
                if(w[i][j]==1 || w[i][j]==2)
                    w[i][j]=0;

        for(int i=1;i<len;i++)
            w[snk[i].x][snk[i].y]=2;
        w[snk[0].x][snk[0].y]=1;
    }

    void setApple()
    {
        apple=1;
        srand(time(NULL));
        while(1) {
            int x=rand()%20+1;
            int y=rand()%20+1;
            if(!w[x][y]) {
                w[x][y]=3;
                break;
            }
        }
    }

    while(1) {
        system("cls");

        printf("******************\n");
        printf("*      Snake     *\n");
        printf("******************\n\n");

        printf("Score: %d\n\n", score);

        if(!apple)
            setApple();

        drawTable();

        if ( kbhit() && !gameOver) {
            char aux=getch();

            if(aux==c) {
                snakeRun();
                continue;
            } else {
                switch(aux) {
                    case 'w':
                        if(c!='s') c='w';
                    break;
                    case 'd':
                        if(c!='a') c='d';
                    break;
                    case 's':
                        if(c!='w') c='s';
                    break;
                    case 'a':
                        if(c!='d') c='a';
                    break;
                }
            }
        }

        snakeRun();

        if(gameOver) {
            system("cls");
            drawTable();
            printf("\nGAME OVER\n\n");
            printf("PRESS q FOR RETURN");

            do {
                c=getch();
            } while(!(c=='q'));

            break;
        }

        delay(0.10);
    }
}

void tetrisGame()
{
    startGame();

    int figure=0, tip, x, y, rot;
    char c;

    void drawTable()
    {
        for(int i=0;i<22;i++) {
            for(int j=0;j<22;j++)
                switch(w[i][j]) {
                    case -1:printf("~ "); break;
                    case 0: printf("  "); break;
                    case 1: printf("# "); break;
                }
            printf("\n");
        }
    }

    void tetrisRun()
    {
        switch(tip) {
            case 0:
                if(x>0) {
                    w[x][y]=0;
                    w[x][y+1]=0;
                }
                x++;
                w[x+1][y]=1;
                w[x+1][y+1]=1;
                if(w[x+2][y]!=0 || w[x+2][y+1]!=0)
                    figure=0;
            break;
            case 1:
                switch(rot) {
                    case 1:
                        w[x][y]=0;
                        w[x][y+1]=0;
                        w[x][y+2]=0;
                        w[x][y+3]=0;
                        x++;
                        w[x][y]=1;
                        w[x][y+1]=1;
                        w[x][y+2]=1;
                        w[x][y+3]=1;
                        if(w[x+1][y]!=0 || w[x+1][y+1]!=0 || w[x+1][y+2]!=0 || w[x+1][y+3]!=0)
                            figure=0;
                    break;
                    case 2:
                        w[x][y]=0;
                        x++;
                        w[x+3][y]=1;
                        if(w[x+4][y]!=0)
                            figure=0;
                    break;
                }
            break;
        }
    }

    void tetrisMove(char c)
    {
        switch(c) {
            case 'd':
                switch(tip) {
                    case 0:
                        if(w[x][y+2]==0 && w[x+1][y+2]==0) {
                            w[x][y]=0;
                            w[x+1][y]=0;
                            y++;
                            w[x][y+1]=1;
                            w[x+1][y+1]=1;
                        }
                    break;
                    case 1:
                        switch(rot) {
                            case 1:
                                if(w[x][y+4]==0) {
                                    w[x][y]=0;
                                    y++;
                                    w[x][y+3]=1;
                                }
                            break;
                            case 2:
                                if(w[x][y+1]==0 && w[x+1][y+1]==0 && w[x+2][y+1]==0 && w[x+3][y+1]==0) {
                                    w[x][y]=0;
                                    w[x+1][y]=0;
                                    w[x+2][y]=0;
                                    w[x+3][y]=0;
                                    y++;
                                    w[x][y]=1;
                                    w[x+1][y]=1;
                                    w[x+2][y]=1;
                                    w[x+3][y]=1;
                                }
                            break;
                        }
                    break;
                }
            break;
            case 'a':
                switch(tip) {
                    case 0:
                        if(w[x][y-1]==0 && w[x+1][y-1]==0) {
                            w[x][y+1]=0;
                            w[x+1][y+1]=0;
                            y--;
                            w[x][y]=1;
                            w[x+1][y]=1;
                        }
                    break;
                    case 1:
                        switch(rot) {
                            case 1:
                                if(w[x][y-1]==0) {
                                    w[x][y+3]=0;
                                    y--;
                                    w[x][y]=1;
                                }
                            break;
                            case 2:
                                if(w[x][y-1]==0 && w[x+1][y-1]==0 && w[x+2][y-1]==0 && w[x+3][y-1]==0) {
                                    w[x][y]=0;
                                    w[x+1][y]=0;
                                    w[x+2][y]=0;
                                    w[x+3][y]=0;
                                    y--;
                                    w[x][y]=1;
                                    w[x+1][y]=1;
                                    w[x+2][y]=1;
                                    w[x+3][y]=1;
                                }
                            break;
                        }
                    break;
                }
            break;
        }
    }

    void tetrisRotate()
    {
        switch(tip) {
            case 1:
                switch(rot) {
                    case 1:
                        if(!w[x-1][y+1] && !w[x+1][y+1] && !w[x+2][y+1]) {
                            rot=2;
                            w[x][y]=0;
                            w[x][y+2]=0;
                            w[x][y+3]=0;
                            x--;
                            y++;
                            w[x][y]=1;
                            w[x+2][y]=1;
                            w[x+3][y]=1;
                        }
                    break;
                    case 2:
                        if(!w[x+1][y-1] && !w[x+1][y+1] && !w[x+1][y+2]) {
                            rot=1;
                            w[x][y]=0;
                            w[x+2][y]=0;
                            w[x+3][y]=0;
                            x++;
                            y--;
                            w[x][y]=1;
                            w[x][y+2]=1;
                            w[x][y+3]=1;
                        }
                    break;
                }
        }
    }

    void setFigure()
    {
        srand(time(NULL));

        tip=rand()%2;
        figure=1;
        rot=1;

        switch(tip) {
            case 0:
                if(w[1][9] || w[1][10])
                    gameOver=1;

                x=0;
                y=9;

                w[1][9]=1;
                w[1][10]=1;
            break;
            case 1:
                if(w[1][8] || w[1][9] || w[1][10] || w[1][11])
                    gameOver=1;

                x=1;
                y=8;

                w[1][8]=1;
                w[1][9]=1;
                w[1][10]=1;
                w[1][11]=1;
            break;
        }
    }

    while(1) {
        system("cls");

        printf("******************\n");
        printf("*     Tetris     *\n");
        printf("******************\n\n");

        printf("Score: %d\n\n", score);

        if(!figure)
            setFigure();

        if(gameOver) {
            system("cls");
            drawTable();
            printf("\nGAME OVER\n\n");
            printf("PRESS q FOR RETURN");

            do {
                c=getch();
            } while(!(c=='q'));

            break;
        }

        drawTable();

        if ( kbhit() && !gameOver) {
            char aux=getch();

            if(aux=='w') {
                tetrisRotate();
                continue;
            }

            if(aux=='s') {
                tetrisRun();
                continue;
            } else {
                if(aux=='a' || aux=='d') {
                    tetrisMove(aux);
                    continue;
                }
            }
        }

        tetrisRun();

        delay(0.30);
    }
}

int main()
{
    char c;
    while(1) {
        do {
            system("cls");

            printf("******************\n");
            printf("*  RETRO JOCURI  *\n");
            printf("******************\n\n\n");

            printf("1 - Snake\n");
            printf("2 - Tetris\n");

            c=getch();
        } while(!((c>='1' && c<='2') || (c=='q')));

        switch(c) {
            case '1':snakeGame(); break;
            case '2':tetrisGame(); break;
        }

        if(c=='q') {
            system("cls");
            printf("APASA ORICE BUTON PENTRU A IESI");
            return 0;
        }
    }



    return 0;
}
