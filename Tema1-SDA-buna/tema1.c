#include "thash.h"

int is_letter(char c) {
	if (c == '-')
		return 1;
	
	if (c >= 'A' && c <= 'Z')
		return 1;

	if (c >= 'a' && c <= 'z')
		return 1;

	return 0;
}

int valid_word(char *word) {
	int nr_ch = strlen(word);
	if (nr_ch < 3) 
		return 0;

	int i = 0;
	for (i = 0; i < nr_ch; i++) {
		if (!is_letter(word[i]))
			return 0;
	}

	return 1;
}

void print_all_function(TH *hashTable) {
	TLG L;
	int i = 0;
	for (i = 0; i < Nr_El; i++) {
		if (hashTable->v[i]) {
			printf("pos %d: ", i);
			L = hashTable->v[i];

			for (; L; L = L->next) {
				afisInfoNumberLetters(L->info);
			}

			printf("\n");
		}
	}
}

void insert_function(TH *hashTable, char *prop) {
	char *word = strtok(prop, " .,");
	while (word != NULL) {
		if (valid_word(word)) {
			insertWordTH(hashTable, word);	
		}
		word = strtok(NULL, " .,");
	}
}

void afisPrintMaxim(TH *hashTable, int nr_max) {
	int i = 0;
	for (i = 0; i < Nr_El; i++) {
		if (hashTable->v[i]) {
			afisInfoNumberLetters_Maxim(hashTable->v[i], nr_max, i);
		}
	}
}

void print_function(TH *hashTable, char *prop) {
	if (is_letter(prop[0])) {
		int nrletters = atoi(prop + 2);
		int cod = hashTable->fh(prop); // e prima litera
		TLG L = hashTable->v[cod];
		for (; L; L = L->next) {
			if (nrletters == ((InfoNumberLetters *)(L->info))->nr_letters) {
				afisInfoNumberLetters(L->info);
				printf("\n");
				return;
			}
		}
	} else {
		int nr_max = atoi(prop); // ia numarul maxim de aparitii
		afisPrintMaxim(hashTable, nr_max);
	}
}

int main(int argvc, char *argv[]) {

	TH *hashTable = InitTH(Nr_El, THCode);
	if (hashTable == NULL) {
		printf("Alocarea nu a avut loc!\n");
        return -1;
	}

	char *linie = (char *)malloc(MAX_NR_CH_LINE * sizeof(char));
    if (linie == NULL) {
        printf("Alocarea nu a avut loc!\n");
        return -1;
    }
	
	
	FILE* f = fopen(argv[1], "rt");

	while (fgets(linie, MAX_NR_CH_LINE, f) != NULL) {
		if (linie[strlen(linie) - 1] == '\n') {
			linie[strlen(linie) - 1] = '\0';
		}

		//inseamna ca pe aceasta linie am doar print
		if (strcmp(linie, "print") == 0) {
			print_all_function(hashTable);
		} else {
			char *command = strtok(linie, " ");
			//verific ce comanda am:
			if (strcmp(command, "insert") == 0) {
				insert_function(hashTable, linie + 7);
			}

			if (strcmp(command, "print") == 0) {
				print_function(hashTable, linie + 6);
			}
		}
	}

	DestroyTH(&hashTable, DestroyInfoNumberLetters);
	free(linie);
	fclose(f);
	
  	return 0;
}
