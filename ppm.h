//ppm.h
//Riesenie UJC-DU1, 16.3.2014
//Autor: Jan Profant, FIT
// Prelozene: gcc 4.8.1



#ifndef _PPM_H_
#define _PPM_H_

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char *data; // RGB bajty, celkom 3*xsize*ysize
};

//funkcia ppm_read nacitava udaje z obrazku typu ppm do struktury

struct ppm * ppm_read(const char * filename);

//funkcia ppm_write zapisuje obsah struktury zadanu parametrom do obrazku

int ppm_write(struct ppm *p, const char * filename);

#endif
