//eratosthenes.c
//Riesenie UJC-DU1, 16.3.2014
//Autor: Jan Profant, FIT
// Prelozene: gcc 4.8.1

#include <stdio.h>
#include "bit-array.h"
#include <math.h>

//funkcia nastavi bitove pole, indexy maju hodnotu 0 pokial ide o prvocislo

void Eratosthenes(BitArray_t pole)
{
    unsigned long i;
    unsigned long j;
    unsigned long q=(int)sqrt(BitArraySize(pole)); //cyklus s pevnym poctom opakovani ide do druhej odmocniny z pocrtu prvkov pola, dalej to je bezpredmetne
    for (i=2;i<=q;i++)
    {
        if (GetBit(pole,i)==0)
            for (j=2;(j*i)<(BitArraySize(pole));j++) //vyskrtavame nasobky z bitoveho pola
            {
                SetBit(pole,(i*j),1);
            }
    }
}
