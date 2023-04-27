/*  functii-tabHash.c - functii tabela hash */
#include "thash.h"

TH* InitTH(size_t M, TFHash fh) {
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("Allocation error hash\n");
        return NULL;
    }

    h->v = (TLG *) calloc(M, sizeof(TLG));
    if(!h->v) {
        printf("vector allocation error of TLG pointers in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

int THCode(void *el) {
    char *word = (char *)el;
    char c = word[0];

    if (c >= 'A' && c <= 'Z')
        return c - 'A';

    if (c >= 'a' && c <= 'z')
        return c - 'a';

    return -1;
}

void DestroyTH(TH** ah, TF free_elem)
{
    TLG * p, el, aux;

    /* parcurgere cu pointeri */
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        /* daca exista elemente corespunzatoare acestui hash
         * eliberam info din cell si apoi eliberam cell */
        for(el = *p; el != NULL; ) {
            aux = el;
            el = el->next;
            free_elem(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

void insertWordTH(TH *tabelaHash, char *word) {
    int cod = tabelaHash->fh((void *) word);
    
    Ins_Word(&(tabelaHash->v[cod]), word);
}
