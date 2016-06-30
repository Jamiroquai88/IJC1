//prvocisla.c
//Riesenie UJC-DU1, 16.3.2014
//Autor: Jan Profant, FIT
// Prelozene: gcc 4.8.1

#include <stdio.h>
#include "ppm.h"
#include "error.h"
#include "bit-array.h"
#include "eratosthenes.h"

int main ()
{
    BitArray(p,101000001); //zistujeme prvocisla do 101 mil, teda musime dat +1 bit, na ktory nesmieme siahat
    Eratosthenes(p); //vygeneruje nam prvocisla
    unsigned long i;
    int k=0;
    int h[10]; //pole pre ukladanie hodnot na vypis
    for (i=BitArraySize(p)-1;k<10;i--) // prechadzame pole odzadu, zistujeme ci to je prvocislo, ak ano, ukladame do pola
        if (GetBit(p,i)==0UL)
        {
            h[k]=i;
            k++;
        }
    for (i=10;i!=0;i--) printf ("%d\n",h[i-1]); //vypis prvkov vzostupne
}
