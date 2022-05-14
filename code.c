#include <stdio.h>
#include <string.h>

// variáveis globais
char palavra[20];
char chutes[26];
int tentativas = 0;

void abertura(){
	printf("*********************************\n");
	printf("*        JOGO DA FORCA          *\n"); // imprime o cabeçalho do jogo
	printf("*********************************\n"); 
}

void chuta(){
	char chute; 
	scanf(" %c", &chute);
	chutes[tentativas] = chute; 
	tentativas++;						
}

int jachutou(char letra){

	int achou = 0;
			for (int j = 0; j < tentativas; j++){ 
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

void escolhepalavra(){
	sprintf(palavra, "MELANCIA");	// armazena strings em arrays
}

int main(){
	
	int acertou = 0; int enforcou = 0;

	escolhepalavra(palavra);
	abertura();

	do {

		desenhaforca(palavra, chutes, tentativas);
		chuta(chutes, &tentativas);

	} while (!acertou && !enforcou);
}
