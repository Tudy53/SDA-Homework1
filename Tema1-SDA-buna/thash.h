#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#define Nr_El 26
#define MAX_NR_CH_LINE 200

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);
typedef int (*TFCmp)(void*, void*);
typedef void (*TF)(void*);
typedef int (*TFHash)(void*);

typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

// functions hash table
int THCode(void *el);
TH* InitTH(size_t M, TFHash fh);
void DestroyTH(TH**aa, TF fe);
void AfiTH(TH*a, TF afiEl);
void insertWordTH(TH *tabelaHash, char *word);

#endif