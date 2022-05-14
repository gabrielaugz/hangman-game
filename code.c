#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>
#define TAMANHO_PALAVRA 20

// variáveis globais
char palavra[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura(){
	printf("*********************************\n");
	printf("*        JOGO DA FORCA          *\n"); // imprime o cabeçalho do jogo
	printf("*********************************\n"); 
}

void chuta(){
	char chute; 
	scanf(" %c", &chute);
	chutes[chutesdados] = chute; 
	chutesdados++;						
}

int jachutou(char letra){

	int achou = 0;
			for (int j = 0; j < chutesdados; j++){ 
				if (chutes[j] == letra){
					achou = 1;
					break;	
				}
			}

	return achou;
}

void desenhaforca(){
	for (int i = 0; i < strlen(palavra); i++){ // para um i menor que o tamanho da string 'palavra', i incrementa

		int achou = jachutou (palavra[i]); // armazenando uma função dentro de uma variável

		if (achou){
			printf("%c ", palavra[i]); 
		} else {
			printf("_ ");
		}

	}
		printf("\n");

}

void adicionapalavra(){

	char quer;
	printf("Voce deseja adicionar uma nova palavra no jogo? (S/N)");
	scanf(" %c", &quer);

	if(quer == 'S'){
		char novapalavra[TAMANHO_PALAVRA];
		printf("Qual a nova palavra?");
		scanf("%s", novapalavra);

		FILE* f;

		f = fopen("palavras.txt", "r+");
		if (f == 0){
			printf("Banco de dados nao disponivel.");
			exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);


		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);

		fclose(f);
	}

}

void escolhepalavra(){
	FILE* f;

	f = fopen("palavras.txt", "r");
	if(f == 0) {
		printf("Banco de dados nao disponivel.");
		exit(1);
	}


	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);

	srand(time(0));
	int randomico = rand() % qtddepalavras;

	for(int i = 0; i <= randomico; i++){
		fscanf(f, "%s", palavra);
	}

	fclose(f);
}

int acertou(){
	for(int i = 0; i < strlen(palavra); i++){
		if(!jachutou(palavra[i])){
			return 0;
		}
	}
	return 1;
}

int enforcou(){
	int erros = 0;
	for (int i = 0; i < chutesdados; i++){
		int existe = 0;
		for (int j = 0; j < strlen(palavra); j++){
			if (chutes[i] == palavra[j]){
				existe = 1;
				break;
			}
		}
		if(!existe) erros++;
	}
		return erros >= 5;
}

int main(){

	escolhepalavra();
	abertura();

	do {

		desenhaforca();
		chuta();

	} while (!acertou() && !enforcou());

	if(acertou()){
		printf("\nParabens, voce ganhou!\n\n");
	} else {
		printf("\nVoce perdeu.\n\n");
		printf("A palavra secreta era *%s*\n", palavra);
	}

	adicionapalavra();
}
