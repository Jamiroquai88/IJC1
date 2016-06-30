//bit-array.h
//Riesenie UJC-DU1, 16.3.2014
//Autor: Jan Profant, FIT
// Prelozene: gcc 4.8.1

#ifndef _BITARRAY_H_
#define _BITARRAY_H_

#include <limits.h>
#include <stdbool.h>
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long *BitArray_t;

//velkost unsigned long v bajtoch

#define SIZE_OF_UL sizeof (unsigned long)

// vytvori pole typu unsigned long, nuluje ho

#define BitArray(pole,velkost) \
    unsigned long pole [((velkost % SIZE_OF_UL*8)==0) ? (velkost/(SIZE_OF_UL*8)+1UL) : (velkost/(SIZE_OF_UL*8)+2UL)]={[0] = (velkost),}

//vrati vlekost pola v bitoch ulozeneho na prvom prvku pola

#define BitArraySize(pole) \
    ((pole)[0])

#ifdef USE_INLINE

    inline bool GetBit (BitArray_t pole,unsigned long index)
    {
        if (index>=BitArraySize(pole))
        {
            FatalError("Index %ld mimo rozsah 0..%ld\n",(long)(index),(long)BitArraySize(pole));
            return -1;
        }
        else return ((pole[index/(SIZE_OF_UL*8)+1UL] & (1UL << (index % (SIZE_OF_UL*8)))) ? 1UL : 0UL);
    }

    inline void SetBit (BitArray_t pole,unsigned long index, bool vyraz)
    {
        if (index>=BitArraySize(pole)) FatalError("Index %ld mimo rozsah 0..%ld\n",(long)(index),(long)BitArraySize(pole));
        else (vyraz==0) ? (pole[index/(SIZE_OF_UL*8)+1UL] &= ~(1UL << (index % (SIZE_OF_UL*8)))) : ((pole[(index/(SIZE_OF_UL*8))+1UL]) |= (1UL << (index % (SIZE_OF_UL*8))));
    }


#else

//nastavi bit v bitovom poli na hodnotu zadanu vyrazom, v pripade prekrocenia medzi vola FatalError

#define SetBit(pole,index,vyraz) \
   (index>=BitArraySize(pole)) ? FatalError("Index %ld mimo rozsah 0..%ld\n",(long)(index),(long)BitArraySize(pole)),5 : DU1_SET_BIT(pole,index,vyraz)

//pomocne makro pre nastavovanie bitov

#define DU1_SET_BIT(pole,index,vyraz) \
    (vyraz==0) ? (pole[index/(SIZE_OF_UL*8)+1UL] &= ~(1UL << (index % (SIZE_OF_UL*8)))) : ((pole[(index/(SIZE_OF_UL*8))+1UL]) |= (1UL << (index % (SIZE_OF_UL*8))))

//ziska bit z pola urceneho indexom, v pripade prekrocenia medzi vola FatalError

#define GetBit(pole,index) \
    ((index>=BitArraySize(pole))) ? FatalError("Index %ld mimo rozsah 0..%ld\n",(long)(index),(long)BitArraySize(pole)),5 : DU1_GET_BIT(pole,index)

//pomocne makro pre ziskavanie hodnotu bitu

#define DU1_GET_BIT(pole,index) \
    ((pole[index/(SIZE_OF_UL*8)+1UL] & (1UL << (index % (SIZE_OF_UL*8)))) ? 1UL : 0UL)

#endif




#endif
