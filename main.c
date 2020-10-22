#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n;
int d[1001][1001], f[1001][1001];

void drawMatrice()
{
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    printf("La Matrice         ~\n                   ~\n");
    printf("# - hachuree       ~\n");
    printf("~ - non-hachuree   ~\n                   ~\n");
    printf("~~~~~~~~~~~~~~~~~~~~\n");

    printf("n=%d\n\n", n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) f[i][j]=0;

    for(int i=0;i<n/2;i++)
        for(int j=0;j<n/2;j++)
            f[i][j]=1;

    for(int i=(n+1)/2;i<n;i++)
        for(int j=0;j<n/2;j++) f[i][j]=1;

    for(int i=0;i<n/2;i++)
        for(int j=(n+1)/2;j<n;j++)
            {
                if(j<=n-i-1) f[i][j]=1;
            }

    printf("condition:\n\n");
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++)
            if(f[i][j]) printf("#"); else printf("~");
        printf("\n");
    }

    printf("\n\n");

    printf("Matrice de valeurs:\n\n");
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++)
            printf("%d ", d[i][j]);
        printf("\n");
    }

    printf("\n\n");
}

void setVal(int n)
{
    srand(time(NULL));

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            d[i][j] = rand()-rand();
        }
}

void setTaille()
{
    system("cls");
    if(n==0)
        printf("N est NULL\n\n");
        else {
            drawMatrice(n);
        }

    printf("donner la taille de la matrice:\n");
    printf("n = ");
    scanf("%d", &n);
    setVal(n);
}

void cond1()
{
    system("clc");
    drawMatrice();
    printf("la moyenne arithmetique des elements divisibles a 4 \nde la surface hachuree:\n\n");

    int sum=0,nr=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            if(f[i][j]==1 && d[i][j]%4==0)
                sum+=d[i][j], nr++;
        }


    if(nr>0)
        printf("%.2f\n\n", sum*1.0/nr);
    else
        printf("0\n\n");

    printf("appuyez sur q pour revenir au menu\n");

    char c;
    do {
        c = getch();
    } while(c!='q');
}

void cond2()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(!f[i][j]) d[i][j]=0;
}

void cond3()
{
    system("clc");
    drawMatrice();
    printf("la valeur et la position des elements maximaux de chaque ligne \nde la surface hachuree\n\n");

    for(int i=0;i<n;i++) {
        int mx=d[i][0], pos=1;
        for(int j=1;j<n;j++) {
            if(f[i][j] && d[i][j]>mx) {
                mx=d[i][j];
                pos=j+1;
            }
        }
        printf("Line %d: %d %d\n", i+1, mx, pos);
    }

    printf("\n");

    printf("appuyez sur q pour revenir au menu\n");

    char c;
    do {
        c = getch();
    } while(c!='q');
}

int main()
{
    char c;

        while(1) {
            do {
                system("cls");
                if(n==0)
                    printf("N est NULL\n\n");
                    else {
                        drawMatrice();
                    }

                if(n==0) {
                    c='1';
                    break;
                }

                printf("1 - Donner la taille de la matrice d[n][n]\n");
                if(n>0) {
                    printf("2 - changer les valeurs dans la matrice\n");
                    printf("3 - Calculez la moyenne arithmetique des elements divisibles a 4 \nde la surface hachuree\n");
                    printf("4 - Remplacez tous les elements de la surface non-hachuree avec des zeros.\n");
                    printf("5 - Determinez la valeur et la position des elements maximaux de chaque ligne \nde la surface hachuree.\n");
                    printf("q - quit\n");
                }

                c = getch();
            } while(!(((c >= '1' && c <='5') && !(c==2 && !n)) || (c=='q')));

            switch(c) {

                case '1': setTaille(); break;
                case '2': setVal(n); break;
                case '3': cond1(); break;
                case '4': cond2(); break;
                case '5': cond3(); break;

            }

            if(c=='q') {
                system("cls");
                printf("oh la la...");
                break;
            }
        }

    return 0;
}
