/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct cellg
{
  void* info;           /* adresa informatie */
  struct cellg *next;   /* adresa nextatoarei celule */
} TCellG , *TLG; /* tipurile cell, Lista  */

typedef struct { 
	int shows;
	char *word;
} InfoWord;

typedef struct {
  int nr_letters;
  TLG listaCuvinte;
} InfoNumberLetters;

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie ShowTH /eliberare un element */

/* functii lista generica */
int Ins_IncLG(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/
void DestroyLG(TLG* aL, TF fe); /* distruge lista */
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(TLG*, TF);
void Ins_Word(TLG *aL, char *word);
void InsInfoWord(TLG *aL, void *elem);
void afisInfoNumberLetters(void *info);
void afisInfoNumberLetters_Maxim(TLG letter_list, int nr_max, int pos);
void DestroyInfoNumberLetters(void *info);

#endif
