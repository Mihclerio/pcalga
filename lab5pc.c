#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n, k=0;
int d[1001][1001], f[1001][1001];

void var4()
{
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
}

void var7()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) f[i][j]=0;

    for(int i=0;i<n/2;i++)
        for(int j=0;j<n/2;j++) {
            if(j>=n/2/2 || i>=n/2/2) f[i][j]=1;
        }

    for(int i=0;i<n/2;i++)
        for(int j=(n+1)/2;j<n;j++) {
            if(j<n/2+n/2/2+(n/2%2)+(n%2) || i>=n/2/2) f[i][j]=1;
        }

    for(int i=(n+1)/2;i<n;i++)
        for(int j=0;j<n/2;j++) {
            if(j>=n/2/2 || i<n/2+n/2/2+(n/2%2)+(n%2)) f[i][j]=1;
        }

    for(int i=(n+1)/2;i<n;i++)
        for(int j=(n+1)/2;j<n;j++) {
            if(i<n/2+n/2/2+(n/2%2)+(n%2) || j<n/2+n/2/2+(n/2%2)+(n%2)) f[i][j]=1;
        }
}

void exemple4()
{
    printf("5 - Calculez la moyenne arithmetique des elements divisibles a 4 \nde la surface hachuree\n");
    printf("6 - Remplacez tous les elements de la surface non-hachuree avec des zeros.\n");
    printf("7 - Determinez la valeur et la position des elements maximaux de chaque ligne \nde la surface hachuree.\n");
}

void exemple7()
{
    printf("5 - Calculez la moyenne arithmetique des elements du perimetre \nde la surface hachuree\n");
    printf("6 - Determinez le nombre des elements impairs de chaque colonne \nde la surface hachuree\n");
    printf("7 - Determinez les elements maximaux de chaque zone de la surface non-hachuree\n");
}

void drawMatrice()
{
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    printf("La Matrice         ~\n                   ~\n");
    printf("# - hachuree       ~\n");
    printf("~ - non-hachuree   ~\n                   ~\n");
    printf("~~~~~~~~~~~~~~~~~~~~\n");

    printf("n=%d\n\n", n);

    switch(k) {
        case 1: var4(); printf("variante 4\n\n"); break;
        case 2: var7(); printf("variante 7\n\n"); break;
        default: printf("variante non selectionnee\n\n");
    }

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

void setVar()
{
    char c;
    do {
        system("cls");

        drawMatrice();

        printf("choisissez votre variante:\n\n");
        printf("1 - variante 4\n");
        printf("2 - variante 7\n");

        c = getch();
    } while(!(c>='1' && c<='2'));

    k = c-'0';

}

void setVal()
{
    srand(time(NULL));

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            d[i][j] = rand()-rand();
        }
}

void setValMan()
{
    system("cls");
    printf("entrez %d numeros de matrice\n", n*n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) scanf("%d", &d[i][j]);
}

void setTaille()
{
    system("cls");
    if(n==0)
        printf("N est NULL\n\n");
        else {
            drawMatrice();
        }

    printf("donner la taille de la matrice:\n");
    printf("n = ");
    scanf("%d", &n);
    setVal();
}

void rezolv4_1()
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

void rezolv4_2()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(!f[i][j]) d[i][j]=0;
}

void rezolv4_3()
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

void rezolv7_1()
{
    system("clc");
    drawMatrice();
    printf("a moyenne arithmetique des elements du perimetre de la surface hachuree:\n\n");

    int sum=0,nr=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            if(f[i][j]==1)
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

void rezolv7_2()
{
    system("clc");
    drawMatrice();
    printf("le nombre des elements impairs de chaque colonne de la surface hachuree:\n\n");

    for(int j=0;j<n;j++) {
        int nr=0;
        for(int i=0;i<n;i++)
            if(f[i][j] && d[i][j]%2) nr++;
        printf("colonne %d: %d elements impairs\n", j+1, nr);
    }

    printf("\nappuyez sur q pour revenir au menu\n");

    char c;
    do {
        c = getch();
    } while(c!='q');
}

void rezolv7_3()
{
    system("clc");
    drawMatrice();
    printf("les elements maximaux de chaque zone de la surface non-hachuree:\n\n");

    int mx=-2000000000;

    for(int i=0;i<n/2;i++)
        for(int j=0;j<n/2;j++) {
            if(!f[i][j] && d[i][j]>mx) mx=d[i][j];
        }

    printf("Zone 1: %d\n", mx);

    mx=-2000000000;
    for(int i=0;i<n/2;i++)
        for(int j=(n+1)/2;j<n;j++) {
            if(!f[i][j] && d[i][j]>mx) mx=d[i][j];
        }

    printf("Zone 2: %d\n", mx);

    mx=-2000000000;
    for(int i=(n+1)/2;i<n;i++)
        for(int j=0;j<n/2;j++) {
            if(!f[i][j] && d[i][j]>mx) mx=d[i][j];
        }

    printf("Zone 3: %d\n", mx);

    mx=-2000000000;
    for(int i=(n+1)/2;i<n;i++)
        for(int j=(n+1)/2;j<n;j++) {
            if(!f[i][j] && d[i][j]>mx) mx=d[i][j];
        }

    printf("Zone 4: %d\n", mx);

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
                printf("2 - choisir le numero de tache\n");
                printf("3 - changer les valeurs dans la matrice (random)\n");
                printf("4 - changer les valeurs dans la matrice (Manuel)\n");

                switch(k) {

                    case 1: exemple4(); break;
                    case 2: exemple7(); break;
                }

                printf("q - quit\n");

                c = getch();
            } while(!((c>='1' && c<='4') || (c=='q') || (c>='4' && c<='7' && k>0)));

            switch(c) {

                case '1': setTaille(); break;
                case '2': setVar(); break;
                case '3': setVal(); break;
                case '4': setValMan(); break;
                case '5':

                    switch(k) {

                        case 1: rezolv4_1(); break;
                        case 2: rezolv7_1(); break;
                    }
                break;
                case '6':

                    switch(k) {

                        case 1: rezolv4_2(); break;
                        case 2: rezolv7_2(); break;
                    }
                break;
                case '7':

                    switch(k) {

                        case 1: rezolv4_3(); break;
                        case 2: rezolv7_3(); break;
                    }
                break;
            }

            if(c=='q') {
                system("cls");
                printf("oh la la...");
                break;
            }
        }

    return 0;
}
