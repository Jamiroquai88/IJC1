//
//Riesenie UJC-DU1, 16.3.2014
//Autor: Jan Profant, FIT
// Prelozene: gcc 4.8.1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "eratosthenes.h"
#include "bit-array.h"
#include "ppm.h"

int main(int argc, char *argv[])
{
    BitArray(pole, 3000000); //deklarujeme si pole 3 mil bitov
    Eratosthenes(pole); //vygenerujeme prvocisla

    struct ppm *p = NULL; //deklarujeme strukturu, priradime ukazovatelu NULL
    if (argc == 2)
    {
        p = ppm_read(argv[1]);
        if (p==NULL) return 1;
    }
    else
    {
        FatalError("Chyba pri zadavani parametrov\n");
    }


        char znak = 0;
        int k = 0;
        for (unsigned long i = 2; i < BitArraySize(pole); i++)
        {
            if (GetBit(pole, i)==0)
            {
                char maska = 0x1;
                maska &= p->data[i + 1];
                if (maska!=0)
                {
                    maska = 1 << k;
                    znak |= maska;
                }
                if (k == 7)
                {
                    if (znak==0)
                        break;
                    printf("%c", znak);
                    k = 0;
                    znak = 0;
                }
                else k++;
            }
        }

    free (p->data); //uvlonime z pamati velkost pola
    free(p); //uvolnime z pamati strukturu
    printf ("\n"); //odriadkujeme

    return 0;
}
