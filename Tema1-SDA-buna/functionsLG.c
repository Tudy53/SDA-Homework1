/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "tlg.h"

InfoWord *alocInfoWord(char *word) {
	// it allocates the structure that contains as info the word and its number of appearances
    InfoWord *info = (InfoWord *)malloc(sizeof(InfoWord));
    if (info == NULL ) {
        printf("Alocarea nu a avut loc!\n");
        return NULL;
    }

    info->word = (char *)malloc((strlen(word) + 1) * sizeof(char));
    if (info->word == NULL) {
        printf("Alocarea nu a avut loc!\n");
        free(info);
        return NULL;
    }

    info->shows = 1;
    strcpy(info->word, word);

    return info;
}

void DestroyInfoWord(void *info) {
    free(((InfoWord *)info)->word);
    free(info);
}

void afisInfoWord(void *info) {
	printf("%s/%d", ((InfoWord *)info)->word, ((InfoWord *)info)->shows);
}

InfoNumberLetters *alocInfoNumberLetters(int nr_ch, InfoWord *info_word) {
	// it allocates the structure that contains as info the words list with the same initial character and the number of characters
    InfoNumberLetters *info = (InfoNumberLetters *)malloc(sizeof(InfoNumberLetters));
    if (info == NULL) {
        printf("Alocarea nu a avut loc!\n");
        return NULL;
    }
    
    TLG lista_cuvinte = NULL;
    InsInfoWord(&lista_cuvinte, info_word);

    info->nr_letters = nr_ch;
    info->listaCuvinte = lista_cuvinte;
}

void DestroyInfoNumberLetters(void *info) {
	DestroyLG(&(((InfoNumberLetters *)info)->listaCuvinte), DestroyInfoWord);
	free(info);
}

void afisInfoNumberLetters(void *info) {
	printf("(%d:", ((InfoNumberLetters *)info)->nr_letters);
	TLG L = ((InfoNumberLetters *)info)->listaCuvinte;
	for (; L->next; L = L->next) {
		afisInfoWord(L->info);
		printf(", ");
	}
	afisInfoWord(L->info);
	printf(")");
}

int comp_nr_max_shows(void *e1, int nr_max) {
	InfoWord *c1 = (InfoWord*)e1;
	return c1->shows > nr_max ? 1 : 0;
}

void afisInfoNumberLetters_Maxim(TLG letter_list, int nr_max, int pos) {
    int prima_shows = 0;
    for (; letter_list; letter_list = letter_list->next) {
        TLG L = ((InfoNumberLetters *)(letter_list->info))->listaCuvinte;
        for (; L && comp_nr_max_shows(L->info, nr_max); L = L->next);

        if (L != NULL) {
            if (!prima_shows) {
                prima_shows = 1;
                printf("pos%d: ", pos);
            }
            
            printf("(%d: ", ((InfoNumberLetters *)letter_list->info)->nr_letters);
            for (; L->next; L = L->next) {
                afisInfoWord(L->info);
                printf(", ");
            }
            afisInfoWord(L->info);
            printf(")");
        }
    }

	if (prima_shows) {
		printf("\n");
	}
}


int comp_nr_shows(void *e1, void *e2) {
	InfoWord *c1 = (InfoWord*)e1;
	InfoWord *c2 = (InfoWord*)e2;

	return c1->shows - c2->shows;
}

int comp_nr_letters(void *e1, int nr_letters) {
	InfoNumberLetters *c1 = (InfoNumberLetters *)e1;

	return c1->nr_letters - nr_letters;
}

int compare_lexicographically(void *e1, void *e2) {
	InfoWord *c1 = (InfoWord*)e1;
	InfoWord *c2 = (InfoWord*)e2;
	
	return strcmp(c1->word, c2->word);
}


void InsInfoWord(TLG *aL, void *elem) {
	if (*aL == NULL) {
		*aL = (TCellG *)malloc(sizeof(TCellG));
		(*aL)->info = elem;
		(*aL)->next = NULL;
		return;
	}


	TLG L = *aL, ant = NULL;
	TCellG *cell;
	for (; L && compare_lexicographically(L->info, elem) != 0; ant = L, L = L->next);

	// it didn't find the word from elem
	if (L == NULL) {
		cell = (TCellG *)malloc(sizeof(TCellG));
		cell->info = elem;
	} else if (compare_lexicographically(L->info, elem) == 0) {
		((InfoWord *)L->info)->shows++;
		
		cell = L;
		DestroyInfoWord(elem);

		if (ant == NULL) {
			return;
		} else {
			ant->next = L->next;
		}
	}

	for (ant = NULL, L = *aL; L && comp_nr_shows(L->info, cell->info) > 0; ant = L, L = L->next);

	// if the number of  de aparitii is identical then we have to go lexicographically to the right possition
	if (L && comp_nr_shows(L->info, cell->info) == 0) {
		
		for (; L && compare_lexicographically(L->info, cell->info) < 0 && comp_nr_shows(L->info, cell->info) == 0;
		 ant = L, L = L->next);
	}
	
	if (ant == NULL) {
		cell->next = *aL;
		*aL = cell;
	} else {
		ant->next = cell;
		cell->next = L;
	}
}


void Ins_Word(TLG *aL, char *word) {
	InfoWord *elem = alocInfoWord(word);
	if (elem == NULL) {
		return;
	}

	int nr_letters = strlen(word);

	if (*aL == NULL) {
		InfoNumberLetters *info_nr_letters = alocInfoNumberLetters(nr_letters, elem);
		
		if (info_nr_letters == NULL)
			return;

		TCellG *cell = (TCellG *)malloc(sizeof(TCellG));
		if (cell == NULL) {
			printf("Alocarea nu a avut loc!\n");
			return;
		}

		cell->info = info_nr_letters;

		cell->next = NULL;
		*aL = cell;

		return;
	}
	

	TLG L = *aL, ant = NULL;

	for (;L && comp_nr_letters(L->info, nr_letters) < 0; ant = L, L = L->next);

	if (L && comp_nr_letters(L->info, nr_letters) == 0) {
		InsInfoWord(&(((InfoNumberLetters *)(L->info))->listaCuvinte), elem);
		return;
	}

	InfoNumberLetters *info_nr_letters = alocInfoNumberLetters(nr_letters, elem);
	if (info_nr_letters == NULL)
		return;

	TCellG *cell = (TCellG *)malloc(sizeof(TCellG));
	if (cell == NULL) {
		printf("Alocarea nu a avut loc!\n");
		return;
	}

	cell->info = info_nr_letters;

	if (ant == NULL) {
		cell->next = *aL;
		*aL = cell;
		return;
	}

	ant->next = cell;
	cell->next = L;
}

void DestroyLG(TLG* aL, TF free_elem) // destroys the list
{
	while(*aL != NULL)
    {
        TLG aux = *aL; // the address of the eliminated cell
        if (!aux)
            return;

        free_elem(aux->info);  // releasese the space occupied by an element
        *aL = aux->next;
        free(aux); // it releases the space occupied by the cell
    }
}


void ShowTH(TLG* aL, TF show_element)
{
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }

	printf("[\n");
	for(; *aL; aL = &(*aL)->next) {
		show_element((*aL)->info);
    }
	printf("]\n");
}

