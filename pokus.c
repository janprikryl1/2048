#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Inicializuj generátor náhodných čísel pomocí aktuálního času
    srand(time(0));
    int rozsah = 4;
    int min = 0;


    int pole[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int x = 0; x < 4; x++)
        {
            pole[i][x] = 0;
        }
        
    }
    pole[rand() % rozsah + min][rand() % rozsah + min] = 2;
    
    for (int i = 0; i < 4; i++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (pole[i][x]) {
                printf("%d ", pole[i][x]);
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }






    /*for (int i = 0; i < 10; i++) {
        int nahodne_cislo = rand() % rozsah + min;

        printf("%d\n", nahodne_cislo);
    }*/

    return 0;
}
