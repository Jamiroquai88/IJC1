//ppm.c
//Riesenie UJC-DU1, 16.3.2014
//Autor: Jan Profant, FIT
// Prelozene: gcc 4.8.1


#include <stdio.h>
#include "error.h"
#include "ppm.h"
#include <stdlib.h>

struct ppm * ppm_read(const char * filename)
{
    FILE *f;
	if ((f=fopen(filename,"rb"))==NULL)
	{
		FatalError("Chyba pri otvarani suboru\n");
	}

    struct ppm *obrazok=malloc(sizeof(struct ppm)); //alokujeme velksot struktury

    fseek(f,3,SEEK_SET); //skoc na treti bajt v subore
    if ((fscanf(f,"%u %u",&obrazok->xsize,&obrazok->ysize))!=2)
    {
        free(obrazok);
        if (fclose(f)==EOF) FatalError("Chyba pri zatvarani suboru\n");
        Warning ("Nespravny format obrazku\n"); //nacitaj velkost obrazku
        return NULL;
    }
    fseek(f,4,SEEK_CUR); //skoc na samotne RGB bajty

    obrazok->data=calloc(sizeof(char),(obrazok->xsize*3*obrazok->ysize+1)); //alokuj pole znakov o danej velkosti, nuluj ho

    unsigned pocet=fread(obrazok->data,sizeof(char),(obrazok->xsize*3*obrazok->ysize),f); //do pola nacitaj cely subor


    if (pocet>(obrazok->xsize*3*obrazok->ysize+1))
    {
        free (obrazok->data); //uvlonime z pamati velkost pola
        free(obrazok); //uvolnime z pamati strukturu
        if (fclose(f)==EOF) FatalError("Chyba pri zatvarani suboru\n");
        Warning("Chyba pri nacitavani udajov z obrazku");
        return NULL;
    }

    if (fclose(f)==EOF)
    {
        free (obrazok->data); //uvlonime z pamati velkost pola
        free(obrazok); //uvolnime z pamati strukturu
        FatalError("Chyba pri zatvarani suboru\n");
    }
    return obrazok;
}

int ppm_write(struct ppm *p, const char * filename)
{
    FILE *f;
    if ((f=fopen(filename,"wb"))==NULL)
	{
        free (p->data); //uvlonime z pamati velkost pola
        free(p); //uvolnime z pamati strukturu
		FatalError("Chyba pri otvarani suboru\n");
	}

    fprintf(f, "P6\n%u %u\n255", p->xsize, p->ysize);

    unsigned pocet=fwrite (p->data, sizeof(char),(p->xsize*3*p->ysize), f);

    if (pocet>(p->xsize*3*p->ysize+1))
    {
        Warning("Chyba pri zapisovani udajov do obrazku");
        return -1;
    }

    if (fclose(f)==EOF)
    {
        free (p->data); //uvlonime z pamati velkost pola
        free(p); //uvolnime z pamati strukturu
        FatalError("Chyba pri zatvarani suboru\n");
    }

    return 0;
}
