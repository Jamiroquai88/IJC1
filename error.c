//error.c
//Riesenie UJC-DU1, 16.3.2014
//Autor: Jan Profant, FIT
// Prelozene: gcc 4.8.1


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

//funkcia Warning pracuje ako printf, svoj vystup zapisuje na stderr

void Warning(const char *fmt, ...)
{
    va_list args;
    vfprintf (stderr,"Chyba: ",args);
    vfprintf (stderr,fmt,args);
    va_end(args);
}

//Funkcia FatalError vypisuje chybovy vypis na stderr a nasledne odpali program

void FatalError(const char *fmt, ...)
{
    va_list args;
    vfprintf (stderr,"Chyba: ",args);
    vfprintf (stderr,fmt,args);
    va_end(args);
    exit (1);
}
