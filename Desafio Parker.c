#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


enum fparametro {mantem, aumenta};

// Structs ---------------------------------------------------------------------------------------------------------------------------------------------------- //

typedef struct value {
	char palavra[6];
	char palavrasorted[6];
	int binary;
} value;

typedef struct ht_item {
	long int key;
	value item;
} ht_item;

typedef struct node {
	ht_item pair;
	node *proximo;
} node;

typedef struct noderesposta {
	char resposta[5][6];
	noderesposta *proximo;
} noderesposta;

typedef struct superpointer {
	int count;
	node *phead;
} superpointer;

typedef struct ponteirocomcount {
	int count;
	value *ponteiro;
} ponteirocomcount;

typedef struct hashtable {
	int size;
	int count;
	int count_anagramas;
	int count_letrasrepetidas;
	superpointer *lista;
} hashtable;

typedef struct checkletras {
	int binary;
	short int *ponteirotamanho;
} checkletras;


// Variavel global--------------------------------------------------------------------------------------------------------------------------------------------- //

noderesposta *respostafinal = NULL;

void set_cursor(bool visible) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------ //

// Funcao para usar a Clibrary function de quicksort -> (https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm)
// para entender mais ainda como funciona -> https://www.geeksforgeeks.org/comparator-function-of-qsort-in-c/
// basicalmente o papel dela é só pegar dois valores e determinar se um menos o outro da <0, ==0 ou >0
// mudar int para char para o sort ser correto
int comparefunc (const void *a, const void *b) {
	return ( *(char*)a - *(char*)b );
}


checkletras checa (char *input, fparametro condicao) {

	static short int tamanho[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	checkletras output;


	if (input == NULL) {
		output.ponteirotamanho = tamanho;
		return (output);
	}

	switch (*input) {
		case 'a':
			if (condicao == aumenta) tamanho[0]++;
			else output.binary = 0b10000000000000000000000000;
			break;
		case 'b':
			if (condicao == aumenta) tamanho[1]++;
			else output.binary = 0b01000000000000000000000000;
			break;
		case 'c':
			if (condicao == aumenta) tamanho[2]++;
			else output.binary = 0b00100000000000000000000000;
			break;
		case 'd':
			if (condicao == aumenta) tamanho[3]++;
			else output.binary = 0b00010000000000000000000000;
			break;
		case 'e':
			if (condicao == aumenta) tamanho[4]++;
			else output.binary = 0b00001000000000000000000000;
			break;
		case 'f':
			if (condicao == aumenta) tamanho[5]++;
			else output.binary = 0b00000100000000000000000000;
			break;
		case 'g':
			if (condicao == aumenta) tamanho[6]++;
			else output.binary = 0b00000010000000000000000000;
			break;
		case 'h':
			if (condicao == aumenta) tamanho[7]++;
			else output.binary = 0b00000001000000000000000000;
			break;
		case 'i':
			if (condicao == aumenta) tamanho[8]++;
			else output.binary = 0b00000000100000000000000000;
			break;
		case 'j':
			if (condicao == aumenta) tamanho[9]++;
			else output.binary = 0b00000000010000000000000000;
			break;
		case 'k':
			if (condicao == aumenta) tamanho[10]++;
			else output.binary = 0b00000000001000000000000000;
			break;
		case 'l':
			if (condicao == aumenta) tamanho[11]++;
			else output.binary = 0b00000000000100000000000000;
			break;
		case 'm':
			if (condicao == aumenta) tamanho[12]++;
			else output.binary = 0b00000000000010000000000000;
			break;
		case 'n':
			if (condicao == aumenta) tamanho[13]++;
			else output.binary = 0b00000000000001000000000000;
			break;
		case 'o':
			if (condicao == aumenta) tamanho[14]++;
			else output.binary = 0b00000000000000100000000000;
			break;
		case 'p':
			if (condicao == aumenta) tamanho[15]++;
			else output.binary = 0b00000000000000010000000000;
			break;
		case 'q':
			if (condicao == aumenta) tamanho[16]++;
			else output.binary = 0b00000000000000001000000000;
			break;
		case 'r':
			if (condicao == aumenta) tamanho[17]++;
			else output.binary = 0b00000000000000000100000000;
			break;
		case 's':
			if (condicao == aumenta) tamanho[18]++;
			else output.binary = 0b00000000000000000010000000;
			break;
		case 't':
			if (condicao == aumenta) tamanho[19]++;
			else output.binary = 0b00000000000000000001000000;
			break;
		case 'u':
			if (condicao == aumenta) tamanho[20]++;
			else output.binary = 0b00000000000000000000100000;
			break;
		case 'v':
			if (condicao == aumenta) tamanho[21]++;
			else output.binary = 0b00000000000000000000010000;
			break;
		case 'w':
			if (condicao == aumenta) tamanho[22]++;
			else output.binary = 0b00000000000000000000001000;
			break;
		case 'x':
			if (condicao == aumenta) tamanho[23]++;
			else output.binary = 0b00000000000000000000000100;
			break;
		case 'y':
			if (condicao == aumenta) tamanho[24]++;
			else output.binary = 0b00000000000000000000000010;
			break;
		case 'z':
			if (condicao == aumenta) tamanho[25]++;
			else output.binary = 0b00000000000000000000000001;
			break;
	}

	return (output);
}


int generate_binary (char *input) {

	int binoutput = 0;
	checkletras checadummy;


	while (*input) {

		checadummy = checa(input, mantem);

		if (checadummy.binary & binoutput) {	// se letra repetida
			binoutput = -99;
			return (binoutput);
		} else
			binoutput += checadummy.binary;

		input++;
	}
	return (binoutput);
}

// Linked list functions -------------------------------------------------------------------------------------------------------------------------------------- //

int insere (superpointer *arraytoinput, ht_item pair) { // int para retornar valor caso não adicione nada

	node *pagora, *pnovo;

	//DEBUGGING----------------------------------------
	static int count = 0;
	char dummy1[6], dummy2[6];
	bool conflitoflag = false;
	//------------------------------------------------

	pagora= arraytoinput->phead;
	strcpy(dummy1, pair.item.palavra);
	qsort(dummy1, 5, sizeof(char), comparefunc);

	while (pagora) {
		//DEBUGGING----------------------------------------
		/*
		[SOLVED] Esse trecho não cobre os conflitos em que um anagrama a um item entra depois de um não-anagrama ter entrado antes dele,
		por exemplo: entra a, depois b, depois outro a denovo. O último a não vai entrar como anagrama e sim não-anagrama pois compara-se com b.
		resolver isso fazendo checar contra todos os itens da lista.
		Ele "quase" garante que nenhuma string diferente gera a mesma key. "Quase" pq, denovo, ele só compara com o último da fila antes de
		adicionar. Se a entra, depois b, depois c com a mesma key de a, ele vai comparar com b e ver keys diferentes.
		Resolver ambos esses problemas comparando com todos os itens da lista [/SOLVED]
		[SOLVED] Depois também averiguar todos os casos que deram index repetidos mesmo com keys diferentes
		Ou seja, três possibilidades de conflito a averiguar: 1ª - anagramas (keys iguais e nomes "iguais"), esperado e ok.
		2º - keys iguais e nomes diferentes (redflag). Nao aconteceu, keys unicas para todos itens da pool - ok.
		3º - keys diferentes, nomes diferentes mas mesmo index. Checar eficiência da hashfunction.
		Checado e resolvido. A eficiência da hashtable (taxa de conflitos) é diretamente proporcional ao tamanho da mesma, portanto
		aumentando-se o seu tamanho, diminui-se os conflitos (uma hashtable de tamanho proporcional a key gerada tem 0 conflitos, mas
		muitos espaços vazios.
		[/SOLVED]
		[SOLVED] E por último remover primeiro da lista todos as palavras que tem letras repetidas dentro delas e depois aí sim remover os anagramas
		Fazer nessa ordem pra bater os resultados com o vídeo [/SOLVED]
		*/
		//-------------------------------------------------

		strcpy(dummy2, pagora->pair.item.palavra);
		qsort(dummy2, 5, sizeof(char), comparefunc);

		if (pagora->pair.key == pair.key) {
			if (strcmp(dummy1, dummy2) != 0)	// se keys iguais E nomes diferentes (não anagramas)
				printf("conflito grave! key igual e item diferente %d\n", count);
			return (1); // senão, ANAGRAMA (keys iguais e nome igual.... der
		}

		else 	// keys diferentes (e obrigatoriamente(?) nomes diferentes
			conflitoflag = true;

		pagora= pagora->proximo;
	}

	if (conflitoflag) {
		count++;
//		printf("conflito %d\n", count);
	}


	pnovo= (node*)malloc(sizeof(node));
	if (!pnovo) {								// em caso de memoria insuficiente
		printf ("Erro! Memoria insuficiente!.");
		exit (69);
	}


	/* precisa checar denovo pois a checagem de cima coloca o pagora como NULL;
	até da pra deixar pagora uma casa antes de NULL (pra checagem pagora->proximo ali em baixo passar, mas daí ia precisar de if ali em cima pra
	breakar antes do while terminar, ia precisar modificar um tanto aqui em baixo e o ganho é neglegível, então só deixei assim mesmo
	e percorre a lista duas vezes e pronto cabou */
	pagora= arraytoinput->phead;
	strcpy(pair.item.palavrasorted, dummy1);
	pnovo->pair = pair;
	pnovo->proximo = NULL;
	arraytoinput->count++;

	checa(pair.item.palavrasorted, aumenta);	// aumenta tabelas do alfabeto

	if (!pagora) {				// se lista vazia
		arraytoinput->phead= pnovo;
	}

	else {
		while (pagora->proximo)
			pagora= pagora->proximo;
		pagora->proximo= pnovo;
	}

	return (0);
}


void limpa(superpointer *input) {					// lembre-se que ela precisa do endereço do VERDADEIRO array, ou seja, se essa funcao for chamada por outra funcao, checar se ela esta mandando o endereço real e não o de cópias

	node *pinicio, *pdummy;
	pinicio= input->phead;

	while (pinicio != NULL) {
		pdummy= pinicio;
		pinicio= pinicio->proximo;
		free(pdummy);
	}

	input->phead= NULL;
	input->count=0;

}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------ //

// HashTable functions ---------------------------------------------------------------------------------------------------------------------------------------- //

hashtable create_hashtable (int size) {

	hashtable new_table;

	// Funcão retornará ponteiro do tipo "ponteiro para superponteiro", quantidade size e cada valor do tamanho de um superponteiro
	new_table.lista = (superpointer*)calloc(size, sizeof(superpointer));
	new_table.size = size;
	new_table.count = 0;
	new_table.count_anagramas = 0;
	new_table.count_letrasrepetidas = 0;


	// Seta todos os superponteiros da lista para NULL e zera seus counts
	for (int i=0; i<size; i++) {
		new_table.lista->phead = NULL;
		new_table.lista->count = 0;
	}
	return (new_table);
}


long int generate_key (char *item) {

	long int key = 0;
	char dummy[6];

	strcpy(dummy, item);
	qsort(dummy, 5, sizeof(char), comparefunc);


	for (int i=0; i<5; i++) {
		key = 31 * key + dummy[i];
	}

	return key;

	/*	// old key function
	for (int i=0; i<5; i++) {
		key += dummy[i]*(i+1);
	}
	*/
}


short int generate_hash (long int key, hashtable table) {

	double dummy = 0, dummy2 = 0;

// WIP - maneiras de melhorar a hashfunction e diminuir conflito o maximo possivel sem aumentar o size da table
	if (key%2) { // impar
		key += 31;
	} else { // par
		key -= 7;
	}

	short int resultant_hash = key % table.size;
	return resultant_hash;
}


void add_ht_item (hashtable *table, char *palavra) {	// table-> (table com setas aqui porque estamos usando um PONTEIRO PARA A HASHTABLE)

	ht_item pair;	// usa-se a copia pair para guardar o item, sua key e seu bin
	short int index;


	pair.item.binary = generate_binary(palavra);

	if (pair.item.binary == -99) {	// se letras repetidas
		table->count_letrasrepetidas++;
		return;
	}

	strcpy(pair.item.palavra, palavra);
	pair.key = generate_key(palavra);
	index = generate_hash(pair.key, *table);
	if (insere(&(table->lista[index]), pair))	// retorna valor 1 caso seja anagrama
		table->count_anagramas++;
	else
		table->count++;

}


void free_table (hashtable table) {

	for (int i=0; i<table.size; i++) {
		if (table.lista[i].phead) 	// se não nulo
			limpa(&(table.lista[i]));

	}
	free (table.lista);
	table.lista = NULL;
	table.count = 0;
	table.size = 0;
}


void insere_resposta (char input[5][6]) {

	noderesposta *pagora, *pnovo;


	pnovo= (noderesposta*)malloc(sizeof(noderesposta));
	if (!pnovo) {								// em caso de memoria insuficiente
		printf ("Erro! Memoria insuficiente!.");
		exit (69);
	}

	for (int i=0; i<5; i++)
		strcpy(pnovo->resposta[i], input[i]);

	pnovo->proximo = NULL;

	pagora = respostafinal;

	if (!pagora) 								// se lista vazia
		respostafinal = pnovo;

	else {
		while (pagora->proximo)
			pagora= pagora->proximo;
		pagora->proximo= pnovo;
	}
}


// ------------------------------------------------------------------------------------------------------------------------------------------------------------ //

void resolve_desafio (ponteirocomcount *lista, int size, int posicaoi, int posicaoj) {

	int bin1, bin2;
	static int bincheck = 0;
	static short int matchflag = 0;
	static char resposta[5][6];
	char chardummy[6] = {'0', '0', '0', '0', '0', '\0'};
	static int progress = 0, porcentagem = 0, respostacount = 0;


	for (int i=posicaoi; i<26; i++) {
		for (int j=posicaoj; j<lista[i].count; j++) {

			bin1 = lista[i].ponteiro[j].binary;
			bincheck += bin1;
			strcpy(resposta[matchflag], lista[i].ponteiro[j].palavra);

			for (int k=i+1; k<26; k++) {
				for (int w=0; w<lista[k].count; w++) {

					bin2 = lista[k].ponteiro[w].binary;

					if (!(bincheck & bin2)) {
						matchflag++;
						if (matchflag < 4)
							resolve_desafio (lista, size, k, w);
						else {
							strcpy(resposta[matchflag], lista[k].ponteiro[w].palavra);
							insere_resposta (resposta);
							respostacount++;

							strcpy(resposta[matchflag], chardummy);
							matchflag--;
							//bincheck -= bin1;
							//	return;
						}
					}
				}
			}

			strcpy(resposta[matchflag], chardummy);
			bincheck -= bin1;

			if (matchflag) {		// caso não seja a palavra principal
				matchflag -=1;
				return;
			}

			progress++;
			if (((progress*100)/size) > porcentagem) {
				porcentagem = (progress*100)/size;
				printf ("\n%d%% feito!!!\n", (progress*100)/size);
			}
		}
	}

	printf ("\nEncontrado %d respostas!\nSalvo em: palavras_finais.txt\n\n", respostacount);
	return;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------ //


int main () {


	FILE *pfileorigem, *pfiledestino, *pfilefinal;
	char bufferpalavra[30], checkpalavra[6], letra = 'a';
	int dummyint = 0, dummycount = 0, letracount = 0, ptotalcount = 0, palavracount = 0, bin1, bin2;
	hashtable listahash;
	checkletras checatamanho;
	ponteirocomcount listamastigada[26];
	value dummyvalue;
	node *dummyponteiro = NULL;
	noderesposta *nodeagora = NULL;

	listahash = create_hashtable(15923);

//	printf ("tamanho eh %d\n", sizeof(bufferpalavra));
	memset(bufferpalavra, '\0', 30);
	pfileorigem = fopen("words_alpha.txt", "r");
	if (pfileorigem == NULL) {
		printf ("ERRO! FILE (words_alpha.txt) nao encontrado!");
		exit (69);
	}
	pfiledestino = fopen("five_words.txt", "w");
	pfilefinal = fopen("palavras_finais.txt", "w");


	while (fscanf(pfileorigem, "%s", &bufferpalavra) != EOF) {

		if (strlen(bufferpalavra) == 5) {

			add_ht_item(&listahash, bufferpalavra);

			fputs(bufferpalavra, pfiledestino);
			fputs("\n", pfiledestino);

		}

		memset(bufferpalavra, '\0', strlen(bufferpalavra));
		ptotalcount++;

	}

	checatamanho = checa(NULL, mantem);

	for (int i=0; i<26; i++) {

		listamastigada[i].count = 0;
		if (checatamanho.ponteirotamanho[i] == 0)
			listamastigada[i].ponteiro = NULL;
		else
			listamastigada[i].ponteiro = (value*)calloc(checatamanho.ponteirotamanho[i], sizeof(value));

//		printf("\nletra %c: %d\n", letra, checatamanho.ponteirotamanho[i]);
//		letra++;
		letracount += checatamanho.ponteirotamanho[i];
	}

//	printf("\nFRASES TOTAIS: %d\n", letracount);
	printf("\nCalculando...\n");
//	printf("\033[?25l");	// remove cursor
	set_cursor(false);

	for (int i=0; palavracount < listahash.count; i++) {

		if (listahash.lista[i].phead) {		// se index nao NULL
			dummyponteiro = listahash.lista[i].phead;

			while (dummyponteiro) {		// pega os valores da lista encadeada e coloca na tabela apropriada
				dummyvalue = dummyponteiro->pair.item;
				dummyint = dummyvalue.palavrasorted[0] - 97;		// converte pro index (letra) correto
				dummycount = listamastigada[dummyint].count;

				listamastigada[dummyint].ponteiro[dummycount] = dummyvalue;

				palavracount++;
				listamastigada[dummyint].count++;
				dummyponteiro = dummyponteiro->proximo;				// avança lista encadeada até chegar em NULL
			}
		}
	}

// Resolve desafio -------------------------------------------------------------------------------------------------------------------------------------------- //

	resolve_desafio (listamastigada, listahash.count, 0, 0);

	nodeagora = respostafinal;

	while (nodeagora) {

		for (int i=0; i<5; i++) {
			fputs(nodeagora->resposta[i], pfilefinal);
			if (i == 4) fputs("\n", pfilefinal);
			else fputs(" ", pfilefinal);
		}

		nodeagora = nodeagora->proximo;
	}


	fclose(pfileorigem);
	fclose(pfiledestino);
	fclose(pfilefinal);
	printf("Numero total de palavras analisadas = %d", ptotalcount);
	printf("\n\nApenas palavras com 5 letras = %d", listahash.count_anagramas + listahash.count_letrasrepetidas + listahash.count);
	printf("\n\nRemovendo palavras com letras repetidas = %d", listahash.count_anagramas + listahash.count);
	printf("\n\nRemovendo anagramas = %d", listahash.count);


	nodeagora = respostafinal;
	while (nodeagora) {
		respostafinal = nodeagora->proximo;
		free(nodeagora);
		nodeagora = respostafinal;
	}

	for (int i=0; i<26; i++) {
		if (listamastigada[i].ponteiro)
			free(listamastigada[i].ponteiro);
	}

	free_table(listahash);

	return (0);

}