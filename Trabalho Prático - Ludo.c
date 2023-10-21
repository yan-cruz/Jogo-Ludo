/******************************************************************************
                            Trabalho Prático - AED's I

                 Universidade do Estado de Minas Gerais - 06/2023

                                Aluno: Yan Cruz
                    1º período, Eng. da Computação, 1EngCM16.

			  Professor: Edwaldo Rodrigues


		     “Se você não pode fazer grandes coisas, 
		    faça pequenas coisas de forma grandiosa."

						-- Napoleon Hill

*******************************************************************************/

// Incluindo as Bibliotecas - Início
	#include <stdio.h>
	#include <string.h>
	#include <time.h>
	#include <stdlib.h>
// Incluindo as Bibliotecas - Fim



// Structs - Início
	typedef struct player{
		char nome[10];
		char cor;
		int peoesFinais;
	} player;

	typedef struct peao{
		int casa;
        int posicao;
		char nome[3];
		int voltaCompleta;
		int casasRestantes;
	} peao;

	typedef struct tabuleiro{
		char nome[3];
	}tab;
// Structs - Fim



// Protótipo das Funções - Início
	int jogarDado ();
	void moverPeao(char peaoAtual[3], int casaAtual, int valorDado, tab casa[52][16], int quantJogadores, char spawnY[4][3], char spawnG[4][3], char spawnR[4][3], char spawnB[4][3], player jogadores[4], int indice, tab safeZoneY[6][16], tab safeZoneR[6][16], tab safeZoneG[6][16], tab safeZoneB[6][16], peao peaoYellow[4], peao peaoRed[4], peao peaoGreen[4], peao peaoBlue[4]);
	void imprimirTabuleiro(tab casa[52][16], tab safeZoneY[6][16], tab safeZoneR[6][16], tab safeZoneB[6][16], tab safeZoneG[6][16], char spawnY[4][3], char spawnG[4][3], char spawnR[4][3], char spawnB[4][3]);
	int moverPeaoSafeZone(char peaoAtual[3], int casaAtual, int valorDado, tab casa[52][16], int quantJogadores, char spawnY[4][3], char spawnG[4][3], char spawnR[4][3], char spawnB[4][3], player jogadores[4], int indice, tab safeZoneY[6][16], tab safeZoneR[6][16], tab safeZoneG[6][16], tab safeZoneB[6][16], peao peaoYellow[4], peao peaoRed[4], peao peaoGreen[4], peao peaoBlue[4]);
// Protótipo das Funções - Fim



// Função Principal - Início
	int main (){

		// Dado - Início
			int valorDado[3];
			char acionaDado;
			srand(time(NULL)); // Gerando uma semente para a geração dos números, com base na hora atual
		// Dado - Fim



		// Criando as variáveis do tabuleiro - Início
			tab casa[52][16];
			for (int i=0; i<52; i++){
				for (int j=0; j<16; j++){
					strcpy(casa[i][j].nome, "  ");
				}
			}
			tab safeZoneY[6][16];
			for (int i=0; i<6; i++){
				for (int j=0; j<16; j++){
					strcpy(safeZoneY[i][j].nome, "  ");
				}
			}
			tab safeZoneR[6][16];
			for (int i=0; i<6; i++){
				for (int j=0; j<16; j++){
					strcpy(safeZoneR[i][j].nome, "  ");
				}
			}
			tab safeZoneB[6][16];
			for (int i=0; i<6; i++){
				for (int j=0; j<16; j++){
					strcpy(safeZoneB[i][j].nome, "  ");
				}
			}
			tab safeZoneG[6][16];
			for (int i=0; i<6; i++){
				for (int j=0; j<16; j++){
					strcpy(safeZoneG[i][j].nome, "  ");
				}
			}
		// Criando as variáveis do tabuleiro - Fim



		// Criando as variáveis do jogador - Início
			int quantJogadores;
			int vencendor=0;
            char vencendorNome[10];
			int perdeVez=0;
		// Criando as variáveis do jogador - Fim



		// Criando variáveis diversas - Início
			int i, j;
			char peaoAtual[3];
			player jogadores[4];
			peao peaoYellow[4];
			peao peaoGreen[4];
			peao peaoRed[4];
			peao peaoBlue[4];
			char spawnY[4][3];
			char spawnG[4][3];
			char spawnR[4][3];
			char spawnB[4][3];
			int dado;
			int rodadas=0;
		// Criando variáveis diversas - Fim



		// Tela Inicial - Início
			printf("\n\n");
			printf("          \033[37mSeja bem-vindo ao\n");
			printf("\n \033[31m##     \033[33m##   ## \033[32m######   \033[34m#####   \033[37m####"); 
			printf("\n \033[31m##     \033[33m##   ## \033[32m##   ## \033[34m##   ##  \033[37m####");
			printf("\n \033[31m##     \033[33m##   ## \033[32m##   ## \033[34m##   ##   \033[37m## ");
			printf("\n \033[31m##     \033[33m##   ## \033[32m##   ## \033[34m##   ##      ");
			printf("\n \033[31m######  \033[33m#####  \033[32m######   \033[34m#####   \033[37m####");
			printf("\n\n\n");
		// Tela Inicial - Fim



		// Definindo a quantidade de jogadores - Início
			printf("\n Digite a quantidade de jogadores (2-4): ");
			scanf("%d", &quantJogadores);

			if (quantJogadores<2 || quantJogadores>4){
				do {
					if (quantJogadores<2 || quantJogadores>4){
						getchar();
						printf("\n Quantidade inválida! Digite novamente: ");
						scanf("%d", &quantJogadores);
					}
				} while (quantJogadores<2 || quantJogadores>4);

				printf("\n\n Gerando tabuleiro para %d jogadores...\n\n", quantJogadores);
				for(int i=0; i<quantJogadores; i++){
					printf("\n Digite o nome do %dº jogador: ", i+1);
					setbuf(stdin, NULL);
					fgets(jogadores[i].nome, 10, stdin);
					jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';

                    if (i==0){
                        jogadores[i].cor = 'Y';
                    }
                    else if (i==1){
                        jogadores[i].cor = 'R';
                    }
                    else if (i==2){
                        jogadores[i].cor = 'G';
                    }
                    else if (i==3){
                        jogadores[i].cor = 'B';
                    }
				}
				printf("\n O jogo vai começar!");
			}
			else {
				printf("\n\n Gerando tabuleiro para %d jogadores...\n\n", quantJogadores);
				for(int i=0; i<quantJogadores; i++){
					printf("\n Digite o nome do %dº jogador: ", i+1);
					setbuf(stdin, NULL);
					fgets(jogadores[i].nome, 10, stdin);
					jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';

					if (i==0){
                        jogadores[i].cor = 'Y';
                    }
                    else if (i==1){
                        jogadores[i].cor = 'R';
                    }
                    else if (i==2){
                        jogadores[i].cor = 'G';
                    }
                    else if (i==3){
                        jogadores[i].cor = 'B';
                    }
				}
				printf("\n\n O jogo vai começar!");
			}
		// Definindo a quantidade de jogadores - Fim



		// Pré-Definindo os peões iniciais, de acordo com a quantidade de jogadores - Início
			if (quantJogadores==2){
				strcpy(peaoYellow[0].nome, "Y1");
				strcpy(peaoYellow[1].nome, "Y2");
				strcpy(peaoYellow[2].nome, "Y3");
				strcpy(peaoYellow[3].nome, "Y4");
				strcpy(spawnY[0], "Y1");
				strcpy(spawnY[1], "Y2");
				strcpy(spawnY[2], "Y3");
				strcpy(spawnY[3], "Y4");
				
				strcpy(peaoRed[0].nome, "R1");
				strcpy(peaoRed[1].nome, "R2");
				strcpy(peaoRed[2].nome, "R3");
				strcpy(peaoRed[3].nome, "R4");
				strcpy(spawnR[0], "R1");
				strcpy(spawnR[1], "R2");
				strcpy(spawnR[2], "R3");
				strcpy(spawnR[3], "R4");

				strcpy(peaoGreen[0].nome, "  ");
				strcpy(peaoGreen[1].nome, "  ");
				strcpy(peaoGreen[2].nome, "  ");
				strcpy(peaoGreen[3].nome, "  ");
				strcpy(spawnG[0], "  ");
				strcpy(spawnG[1], "  ");
				strcpy(spawnG[2], "  ");
				strcpy(spawnG[3], "  ");

				strcpy(peaoBlue[0].nome, "  ");
				strcpy(peaoBlue[1].nome, "  ");
				strcpy(peaoBlue[2].nome, "  ");
				strcpy(peaoBlue[3].nome, "  ");
				strcpy(spawnB[0], "  ");
				strcpy(spawnB[1], "  ");
				strcpy(spawnB[2], "  ");
				strcpy(spawnB[3], "  ");
			}
			else if (quantJogadores==3){
				strcpy(peaoYellow[0].nome, "Y1");
				strcpy(peaoYellow[1].nome, "Y2");
				strcpy(peaoYellow[2].nome, "Y3");
				strcpy(peaoYellow[3].nome, "Y4");
				strcpy(spawnY[0], "Y1");
				strcpy(spawnY[1], "Y2");
				strcpy(spawnY[2], "Y3");
				strcpy(spawnY[3], "Y4");
				
				strcpy(peaoRed[0].nome, "R1");
				strcpy(peaoRed[1].nome, "R2");
				strcpy(peaoRed[2].nome, "R3");
				strcpy(peaoRed[3].nome, "R4");
				strcpy(spawnR[0], "R1");
				strcpy(spawnR[1], "R2");
				strcpy(spawnR[2], "R3");
				strcpy(spawnR[3], "R4");

				strcpy(peaoGreen[0].nome, "G1");
				strcpy(peaoGreen[1].nome, "G2");
				strcpy(peaoGreen[2].nome, "G3");
				strcpy(peaoGreen[3].nome, "G4");
				strcpy(spawnG[0], "G1");
				strcpy(spawnG[1], "G2");
				strcpy(spawnG[2], "G3");
				strcpy(spawnG[3], "G4");

				strcpy(peaoBlue[0].nome, "  ");
				strcpy(peaoBlue[1].nome, "  ");
				strcpy(peaoBlue[2].nome, "  ");
				strcpy(peaoBlue[3].nome, "  ");
				strcpy(spawnB[0], "  ");
				strcpy(spawnB[1], "  ");
				strcpy(spawnB[2], "  ");
				strcpy(spawnB[3], "  ");
			}
			else if (quantJogadores==4){
				strcpy(peaoYellow[0].nome, "Y1");
				strcpy(peaoYellow[1].nome, "Y2");
				strcpy(peaoYellow[2].nome, "Y3");
				strcpy(peaoYellow[3].nome, "Y4");
				strcpy(spawnY[0], "Y1");
				strcpy(spawnY[1], "Y2");
				strcpy(spawnY[2], "Y3");
				strcpy(spawnY[3], "Y4");

				strcpy(peaoRed[0].nome, "R1");
				strcpy(peaoRed[1].nome, "R2");
				strcpy(peaoRed[2].nome, "R3");
				strcpy(peaoRed[3].nome, "R4");
				strcpy(spawnR[0], "R1");
				strcpy(spawnR[1], "R2");
				strcpy(spawnR[2], "R3");
				strcpy(spawnR[3], "R4");

				strcpy(peaoGreen[0].nome, "G1");
				strcpy(peaoGreen[1].nome, "G2");
				strcpy(peaoGreen[2].nome, "G3");
				strcpy(peaoGreen[3].nome, "G4");
				strcpy(spawnG[0], "G1");
				strcpy(spawnG[1], "G2");
				strcpy(spawnG[2], "G3");
				strcpy(spawnG[3], "G4");

				strcpy(peaoBlue[0].nome, "B1");
				strcpy(peaoBlue[1].nome, "B2");
				strcpy(peaoBlue[2].nome, "B3");
				strcpy(peaoBlue[3].nome, "B4");
				strcpy(spawnB[0], "B1");
				strcpy(spawnB[1], "B2");
				strcpy(spawnB[2], "B3");
				strcpy(spawnB[3], "B4");
			}
		// Pré-Definindo os peões iniciais, de acordo com a quantidade de jogadores - Fim



		// Pré - Definindo as veriavés de controle - Início
			for (int i =0; i<quantJogadores; i++){
				jogadores[i].peoesFinais = 0;
			}

			for (int i=0; i<4; i++){
				peaoYellow[i].casasRestantes = 6;
				peaoRed[i].casasRestantes = 6;
				peaoGreen[i].casasRestantes = 6;
				peaoBlue[i].casasRestantes = 6;
			}
		// Pré - Definindo as veriavés de controle - Fim


		// Criando o tabuleiro - Início
			printf("\n\n");
			printf("\n");
			printf(" \033[37m**********************************************************************************\n");
			printf(" \033[37m*                                                                                *\n");
			printf(" \033[37m*                                 ____ ____ ____                                 *\n");
			printf(" \033[37m*                                |    |    |    |                                *\n");
			printf(" \033[37m*                                | %s | %s | %s |                                *\n", casa[0][0].nome, casa[1][0].nome, casa[2][0].nome);
			printf(" \033[37m*        \033[32m____G____\033[37m               |____|\033[31m____\033[37m|\033[31m____\033[37m|               \033[31m____R____\033[37m        *\n");
			printf(" \033[37m*       \033[32m|    |    |\033[37m              |    \033[31m|   R|   R|\033[37m              \033[31m|    |    |\033[37m       *\n");
			printf(" \033[37m*       \033[32m| %s | %s |\033[37m              | %s \033[31m| %s | %s |\033[37m              \033[31m| %s | %s |\033[37m       *\n", spawnG[0], spawnG[1], casa[51][0].nome , safeZoneR[0][0].nome, casa[3][0].nome , spawnR[0], spawnR[1]);
			printf(" \033[37m*       \033[32m|____|____|\033[37m              |____\033[31m|____|____|\033[37m              \033[31m|____|____|\033[37m       *\n");
			printf(" \033[37m*       \033[32m|    |    |\033[37m              |*   \033[31m|   R|\033[37m    |              \033[31m|    |    |\033[37m       *\n");
			printf(" \033[37m*       \033[32m| %s | %s |\033[37m              | %s \033[31m| %s |\033[37m %s |              \033[31m| %s | %s |\033[37m       *\n", spawnG[3], spawnG[2], casa[50][0].nome , safeZoneR[1][0].nome, casa[4][0].nome , spawnR[3], spawnR[2]);
			printf(" \033[37m*       \033[32m|____|____|\033[37m              |____\033[31m|____|\033[37m____|              \033[31m|____|____|\033[37m       *\n");
			printf(" \033[37m*                                |    \033[31m|   R|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[31m| %s |\033[37m %s |                                *\n", casa[49][0].nome , safeZoneR[2][0].nome, casa[5][0].nome );
			printf(" \033[37m*                                |____\033[31m|____|\033[37m____|                                *\n");
			printf(" \033[37m*                                |    \033[31m|   R|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[31m| %s |\033[37m %s |                                *\n", casa[48][0].nome , safeZoneR[3][0].nome, casa[6][0].nome );
			printf(" \033[37m*                                |____\033[31m|____|\033[37m____|                                *\n");
			printf(" \033[37m*                                |    \033[31m|   R|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[31m| %s |\033[37m %s |                                *\n", casa[47][0].nome , safeZoneR[4][0].nome, casa[7][0].nome );
			printf(" \033[37m*   ____ \033[32m____ \033[37m____ ____ ____ ____|____\033[31m|____|\033[37m____|____ ____ ____ ____ ____ ____   *\n");
			printf(" \033[37m*  |    \033[32m|   G|\033[37m    |    |    |    |    |    |    |    |    |    |   *|    |    |  *\n");
			printf(" \033[37m*  | %s \033[32m| %s |\033[37m %s | %s | %s | %s | == | == | == | %s | %s | %s | %s | %s | %s |  *\n", casa[41][0].nome , casa[42][0].nome , casa[43][0].nome , casa[44][0].nome , casa[45][0].nome , casa[46][0].nome , casa[8][0].nome , casa[9][0].nome , casa[10][0].nome , casa[11][0].nome , casa[12][0].nome , casa[13][0].nome );
			printf(" \033[37m*  |____\033[32m|____|____\033[37m|\033[32m____\033[37m|\033[32m____\033[37m|\033[32m____\033[37m|____|____|____|\033[34m____\033[37m|\033[34m____\033[37m|\033[34m____\033[37m|\033[34m____\033[37m|\033[34m____\033[37m|____|  *\n");
			printf(" \033[37m*  |    \033[32m|   G|   G|   G|   G|   G|\033[37m    |    |    \033[34m|   B|   B|   B|   B|   B|\033[37m    |  *\n");
			printf(" \033[37m*  | %s \033[32m| %s | %s | %s | %s | %s |\033[37m == | == | == \033[34m| %s | %s | %s | %s | %s |\033[37m %s |  *\n", casa[40][0].nome , safeZoneG[0][0].nome, safeZoneG[1][0].nome, safeZoneG[2][0].nome, safeZoneG[3][0].nome, safeZoneG[4][0].nome, safeZoneB[4][0].nome, safeZoneB[3][0].nome, safeZoneB[2][0].nome, safeZoneB[1][0].nome, safeZoneB[0][0].nome, casa[14][0].nome );
			printf(" \033[37m*  |____\033[32m|____|____|____|____|____|\033[37m____|____|____\033[34m|____|____|____|____|____|\033[37m____|  *\n");
			printf(" \033[37m*  |    |    |   *|    |    |    |    |    |    |    |    |    |    \033[34m|   B|\033[37m    |  *\n");
			printf(" \033[37m*  | %s | %s | %s | %s | %s | %s | == | == | == | %s | %s | %s | %s \033[34m| %s |\033[37m %s |  *\n", casa[39][0].nome , casa[38][0].nome , casa[37][0].nome , casa[36][0].nome , casa[35][0].nome , casa[34][0].nome , casa[20][0].nome , casa[19][0].nome , casa[18][0].nome , casa[17][0].nome , casa[16][0].nome , casa[15][0].nome );
			printf(" \033[37m*  |____|____|____|____|____|____|____|\033[33m____\033[37m|____|____|____|____|____\033[34m|____|\033[37m____|  *\n");
			printf(" \033[37m*                                |    \033[33m|   Y|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[33m| %s |\033[37m %s |                                *\n", casa[33][0].nome , safeZoneY[4][0].nome, casa[21][0].nome );
			printf(" \033[37m*                                |____\033[33m|____|\033[37m____|                                *\n");
			printf(" \033[37m*                                |    \033[33m|   Y|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[33m| %s |\033[37m %s |                                *\n", casa[32][0].nome , safeZoneY[3][0].nome, casa[22][0].nome );
			printf(" \033[37m*                                |____\033[33m|____|\033[37m____|                                *\n");
			printf(" \033[37m*                                |    \033[33m|   Y|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[33m| %s |\033[37m %s |                                *\n", casa[31][0].nome , safeZoneY[2][0].nome, casa[23][0].nome );
			printf(" \033[37m*        \033[33m____Y____\033[37m               |____\033[33m|____|\033[37m____|               \033[34m____B____\033[37m        *\n");
			printf(" \033[37m*       \033[33m|    |    |\033[37m              |    \033[33m|   Y|\033[37m   *|              \033[34m|    |    |\033[37m       *\n");
			printf(" \033[37m*       \033[33m| %s | %s |\033[37m              | %s \033[33m| %s |\033[37m %s |              \033[34m| %s | %s |\033[37m       *\n", spawnY[0], spawnY[1], casa[30][0].nome , safeZoneY[1][0].nome, casa[24][0].nome , spawnB[0], spawnB[1]);
			printf(" \033[37m*       \033[33m|____|____|\033[37m              |\033[33m____\033[33m|____|\033[37m____|              \033[34m|____|____|\033[37m       *\n");
			printf(" \033[37m*       \033[33m|    |    |\033[37m              \033[33m|Y   |   Y|\033[37m    |              \033[34m|    |    |\033[37m       *\n");
			printf(" \033[37m*       \033[33m| %s | %s |\033[37m              \033[33m| %s | %s |\033[37m %s |              \033[34m| %s | %s |\033[37m       *\n", spawnY[3], spawnY[2], casa[29][0].nome , safeZoneY[0][0].nome, casa[25][0].nome , spawnB[3], spawnB[2]);
			printf(" \033[37m*       \033[33m|____|____|\033[37m              \033[33m|____|____|\033[37m____|              \033[34m|____|____|\033[37m       *\n");
			printf(" \033[37m*                                |    |    |    |                                *\n");
			printf(" \033[37m*                                | %s | %s | %s |                                *\n", casa[28][0].nome , casa[27][0].nome , casa[26][0].nome );
			printf(" \033[37m*                                |____|____|____|                                *\n");
			printf(" \033[37m*                                                                                *\n");
			printf(" \033[37m*                                                                                *\n");
			printf(" \033[37m**********************************************************************************\n\n");
		// Criando o tabuleiro - Fim
	


		// Loop Principal - Início

			// Um "do" fará o controle das rodadas, equanto o jogo não houver vencedores.
			do {
				int peaoValidado = 7;
				for (int i=0; i<quantJogadores; i++){
					printf(" %s, tecle 'enter' para lançar o dado: ", jogadores[i].nome);
					setbuf(stdin, NULL);
					scanf("%c", &acionaDado);
					

					// Caso o jogador aperte outra tecla, um "do" espera ele digitar a tecla correta.
					if (acionaDado != '\n'){
						do {
							if (acionaDado == '\n'){
								valorDado[0] = jogarDado();
							}
							else {
								getchar();
								printf(" Tecla inválida! Tecle 'enter' para lançar o dado: ");
								getchar();
								scanf("%c", &acionaDado);
							}
						} while (acionaDado != '\n');
					}

					// Quando a tecla for válida, começam as ações.
					else if (acionaDado == '\n'){

						// A função "jogarDado" é chamada para gerar um valor de 1 à 6.
						valorDado[0] = jogarDado();

						// Caso for 6, ele pede pro jogador jogar novamente
						if (valorDado[0]==6){
							printf(" Você tirou um 6! Tecle 'enter' para lançar o dado novamente: ");
							setbuf(stdin, NULL);
							scanf("%c", &acionaDado);

							// Verifica se é a tecla correta, se sim, joga novamente, se não, espera a tecla certa
							do {
								if (acionaDado == '\n'){
									valorDado[1] = jogarDado();
								}
								else {
									getchar();
									printf(" Tecla inválida! Tecle 'enter' para lançar o dado: ");
									getchar();
									scanf("%c", &acionaDado);
								}
							} while (acionaDado != '\n');

							// Caso for 6 de novo, ele pede pro jogador jogar novamente
							if (valorDado[1]==6){
								printf(" Você tirou um 6! Tecle 'enter' para lançar o dado novamente: ");
								setbuf(stdin, NULL);
								scanf("%c", &acionaDado);

								// Verifica se é a tecla correta, se sim, joga novamente, se não, espera a tecla certa
								do {
									if (acionaDado == '\n'){
										valorDado[2] = jogarDado();
									}
									else {
										getchar();
										printf(" Tecla inválida! Tecle 'enter' para lançar o dado: ");
										getchar();
										scanf("%c", &acionaDado);
									}
								} while (acionaDado != '\n');

								// Caso for 6 de novo, ele perde a vez
								if (valorDado[2]==6){
									perdeVez++;
									printf(" Você tirou três vezes o número 6 e perdeu a vez!\n\n");
								}

								// Caso for diferente, começa a usar os valores armazenados
								else {

									// Cria um "for" para percorrer todos os valores do dado
									for (int rdd=0; rdd<3; rdd++){

										// Caso for 1, aparece "casa", caso não for, aparece "casas". Puramente estético
										if (valorDado[rdd]==1){
											printf(" %s, selecione um peão para andar %d casa: ", jogadores[i].nome, valorDado[rdd]);
										}
										else if (valorDado[rdd]!=1){
											printf(" %s, selecione um peão para andar %d casas: ", jogadores[i].nome, valorDado[rdd]);
										}
										setbuf(stdin, NULL);
										fgets(peaoAtual, 3, stdin);
										getchar();


										// Caso o peão não seja da cor do jogador, ele pede pra selecionar outro
										if ((jogadores[i].cor!=peaoAtual[0])){
											do {
												if (valorDado[rdd]==1){
													printf(" Peão inválido! Selecione um peão para andar %d casa: ", valorDado[rdd]);
												}
												else if (valorDado[rdd]!=1){
													printf(" Peão inválido! Selecione um peão para andar %d casas: ", valorDado[rdd]);
												}
												setbuf(stdin, NULL);
												fgets(peaoAtual, 3, stdin);
												getchar();
											} while (jogadores[i].cor!=peaoAtual[0]);
										}

										// Testa novamente, e agora, como o peão é válido, ele entra
										if (jogadores[i].cor==peaoAtual[0]){
											int casaAtual;
											int casaAtualEncontrada=0;
											
											// Capta o número do peão atual
											int numPeao;
											for (numPeao=0; numPeao<4; numPeao++){
												if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
													break;
												}
												else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
													break;
												}
												else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
													break;
												}
												else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
													break;
												} 
											}
											
											// Define a variável "dado" com o valor atual
											dado = valorDado[rdd];

											// O "for" percorre todas as casas e tenta achar o peão
											for (casaAtual=0; casaAtual<52; casaAtual++){

												// Caso ache, chama função "moverPeao" normalmente
												if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
													moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
													imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
													casaAtualEncontrada = 1;
													break;
												}
											}

											// Caso não ache, o peão está na SafeZone, logo, chama função "moverPeaoSafeZone" normalmente
											if (casaAtualEncontrada==0){
												for (casaAtual=0; casaAtual<5; casaAtual++){
													if (jogadores[i].cor=='Y'){
														if (strcmp(safeZoneY[casaAtual][0].nome, peaoAtual)==0){
															peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															if (peaoValidado==1){
																for (numPeao=0; numPeao<4; numPeao++){
																	if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																		break;
																	} 
																}

																// O "for" percorre todas as casas e tenta achar o peão
																for (casaAtual=0; casaAtual<52; casaAtual++){

																	// Caso ache, chama função "moverPeao" normalmente
																	if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																		moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																		imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																		casaAtualEncontrada = 1;
																		break;
																	}
																}
																if (casaAtualEncontrada==0){
																	peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																	casaAtualEncontrada = -1;
																	break;
																}
																if (casaAtualEncontrada==0){
																	moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																}
															}
															else if (peaoValidado==0){
																printf("\nVocê não possue peões válidos!\n");
																break;
															}
														}
													}
													else if (jogadores[i].cor=='R'){
														if (strcmp(safeZoneR[casaAtual][0].nome, peaoAtual)==0){
															peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															if (peaoValidado==1){
																for (numPeao=0; numPeao<4; numPeao++){
																	if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																		break;
																	} 
																}

																// O "for" percorre todas as casas e tenta achar o peão
																for (casaAtual=0; casaAtual<52; casaAtual++){

																	// Caso ache, chama função "moverPeao" normalmente
																	if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																		moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																		imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																		casaAtualEncontrada = 1;
																		break;
																	}
																}
																if (casaAtualEncontrada==0){
																	peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																	casaAtualEncontrada = -1;
																	break;
																}
																if (casaAtualEncontrada==0){
																	moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																}
															}
															else if (peaoValidado==0){
																printf("\nVocê não possue peões válidos!\n");
																break;
															}
														}
													}
													else if (jogadores[i].cor=='G'){
														if (strcmp(safeZoneG[casaAtual][0].nome, peaoAtual)==0){
															peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															if (peaoValidado==1){
																for (numPeao=0; numPeao<4; numPeao++){
																	if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																		break;
																	} 
																}

																// O "for" percorre todas as casas e tenta achar o peão
																for (casaAtual=0; casaAtual<52; casaAtual++){

																	// Caso ache, chama função "moverPeao" normalmente
																	if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																		moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																		imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																		casaAtualEncontrada = 1;
																		break;
																	}
																}
																if (casaAtualEncontrada==0){
																	peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																	casaAtualEncontrada = -1;
																	break;
																}
																if (casaAtualEncontrada==0){
																	moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																}
															}
															else if (peaoValidado==0){
																printf("\nVocê não possue peões válidos!\n");
																break;
															}
														}
													}
													else if (jogadores[i].cor=='B'){
														if (strcmp(safeZoneB[casaAtual][0].nome, peaoAtual)==0){
															peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															if (peaoValidado==1){
																for (numPeao=0; numPeao<4; numPeao++){
																	if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																		break;
																	}
																	else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																		break;
																	} 
																}

																// O "for" percorre todas as casas e tenta achar o peão
																for (casaAtual=0; casaAtual<52; casaAtual++){

																	// Caso ache, chama função "moverPeao" normalmente
																	if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																		moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																		imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																		casaAtualEncontrada = 1;
																		break;
																	}
																}
																if (casaAtualEncontrada==0){
																	peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																	casaAtualEncontrada = -1;
																	break;
																}
																if (casaAtualEncontrada==0){
																	moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																}
															}
															else if (peaoValidado==0){
																printf("\nVocê não possue peões válidos!\n");
																break;
															}
														}
													}
												}
											}
											printf("\n");
											rodadas++;
											if (peaoValidado==0){
												break;
											}
											if (casaAtualEncontrada==0){
												moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
												imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
											}

											// Caso chegue no final do número de jogadores, zero o "i"
											if (i==quantJogadores){
												i=0;
											}
										}
									}
								}
							}
							else {
								for (int rdd=0; rdd<2; rdd++){
									if (valorDado[rdd]==1){
										printf(" %s, selecione um peão para andar %d casa: ", jogadores[i].nome, valorDado[rdd]);
									}
									else if (valorDado[rdd]!=1){
										printf(" %s, selecione um peão para andar %d casas: ", jogadores[i].nome, valorDado[rdd]);
									}
									setbuf(stdin, NULL);
									fgets(peaoAtual, 3, stdin);
									getchar();


									if ((jogadores[i].cor)!=peaoAtual[0]){
										do {
											if (valorDado[rdd]==1){
												printf(" Peão inválido! Selecione um peão para andar %d casa: ", valorDado[rdd]);
											}
											else if (valorDado[rdd]!=1){
												printf(" Peão inválido! Selecione um peão para andar %d casas: ", valorDado[rdd]);
											}
											setbuf(stdin, NULL);
											fgets(peaoAtual, 3, stdin);
											getchar();
										} while (jogadores[i].cor!=peaoAtual[0]);
									}
									if ((jogadores[i].cor)==peaoAtual[0]){

										int casaAtual;
										int casaAtualEncontrada=0;
										
										int numPeao;
										for (numPeao=0; numPeao<4; numPeao++){
											if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
												break;
											}
											else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
												break;
											}
											else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
												break;
											}
											else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
												break;
											} 
										}

										dado = valorDado[rdd];
										for (casaAtual=0; casaAtual<52; casaAtual++){
											if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
												moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
												imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
												casaAtualEncontrada = 1;
												break;
											}
										}
										if (casaAtualEncontrada==0){
											for (casaAtual=0; casaAtual<5; casaAtual++){
												if (jogadores[i].cor=='Y'){
													if (strcmp(safeZoneY[casaAtual][0].nome, peaoAtual)==0){
														peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
														if (peaoValidado==1){
															for (numPeao=0; numPeao<4; numPeao++){
																if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																	break;
																} 
															}

															// O "for" percorre todas as casas e tenta achar o peão
															for (casaAtual=0; casaAtual<52; casaAtual++){

																// Caso ache, chama função "moverPeao" normalmente
																if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																	moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																	casaAtualEncontrada = 1;
																	break;
																}
															}
															if (casaAtualEncontrada==0){
																peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																casaAtualEncontrada = -1;
																break;
															}
															if (casaAtualEncontrada==0){
																moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
															}
														}
														else if (peaoValidado==0){
															printf("\nVocê não possue peões válidos!\n");
															break;
														}
													}
												}
												else if (jogadores[i].cor=='R'){
													if (strcmp(safeZoneR[casaAtual][0].nome, peaoAtual)==0){
														peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
														if (peaoValidado==1){
															for (numPeao=0; numPeao<4; numPeao++){
																if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																	break;
																} 
															}

															// O "for" percorre todas as casas e tenta achar o peão
															for (casaAtual=0; casaAtual<52; casaAtual++){

																// Caso ache, chama função "moverPeao" normalmente
																if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																	moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																	casaAtualEncontrada = 1;
																	break;
																}
															}
															if (casaAtualEncontrada==0){
																peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																casaAtualEncontrada = -1;
																break;
															}
															if (casaAtualEncontrada==0){
																moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
															}
														}
														else if (peaoValidado==0){
															printf("\nVocê não possue peões válidos!\n");
															break;
														}
													}
												}
												else if (jogadores[i].cor=='G'){
													if (strcmp(safeZoneG[casaAtual][0].nome, peaoAtual)==0){
														peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
														if (peaoValidado==1){
															for (numPeao=0; numPeao<4; numPeao++){
																if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																	break;
																} 
															}

															// O "for" percorre todas as casas e tenta achar o peão
															for (casaAtual=0; casaAtual<52; casaAtual++){

																// Caso ache, chama função "moverPeao" normalmente
																if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																	moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																	casaAtualEncontrada = 1;
																	break;
																}
															}
															if (casaAtualEncontrada==0){
																peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																casaAtualEncontrada = -1;
																break;
															}
															if (casaAtualEncontrada==0){
																moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
															}
														}
														else if (peaoValidado==0){
															printf("\nVocê não possue peões válidos!\n");
															break;
														}
													}
												}
												else if (jogadores[i].cor=='B'){
													if (strcmp(safeZoneB[casaAtual][0].nome, peaoAtual)==0){
														peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
														if (peaoValidado==1){
															for (numPeao=0; numPeao<4; numPeao++){
																if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																	break;
																}
																else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																	break;
																} 
															}

															// O "for" percorre todas as casas e tenta achar o peão
															for (casaAtual=0; casaAtual<52; casaAtual++){

																// Caso ache, chama função "moverPeao" normalmente
																if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																	moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																	imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																	casaAtualEncontrada = 1;
																	break;
																}
															}
															if (casaAtualEncontrada==0){
																peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																casaAtualEncontrada = -1;
																break;
															}
															if (casaAtualEncontrada==0){
																moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
															}
														}
														else if (peaoValidado==0){
															printf("\nVocê não possue peões válidos!\n");
															break;
														}
													}
												}
											}
										}
										printf("\n");
										rodadas++;
										if (casaAtualEncontrada==0){
											moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
											imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
										}
										if (i==quantJogadores){
											i=0;
										}
									}
								}
							}
						}
						else {
							int achaPeao=0;
							for (int kk=0; kk<52; kk++){
								for (int pp=0; pp<16; pp++){
									if ((casa[kk][pp].nome[0]==jogadores[i].cor) || (safeZoneY[kk][pp].nome[0]==jogadores[i].cor) || (safeZoneR[kk][pp].nome[0]==jogadores[i].cor) || (safeZoneG[kk][pp].nome[0]==jogadores[i].cor) || (safeZoneB[kk][pp].nome[0]==jogadores[i].cor)){
										achaPeao = 1;
										break;
									}
								}
							}
							if (achaPeao==1){
								if (valorDado[0]==1){
									printf(" %s, selecione um peão para andar %d casa: ", jogadores[i].nome, valorDado[0]);
								}
								else if (valorDado[0]!=1){
									printf(" %s, selecione um peão para andar %d casas: ", jogadores[i].nome, valorDado[0]);
								}
								setbuf(stdin, NULL);
								fgets(peaoAtual, 3, stdin);
								getchar();

								if ((jogadores[i].cor)!=peaoAtual[0]){
									do {
										if (valorDado[0]==1){
											printf(" Peão inválido! Selecione um peão para andar %d casa: ", valorDado[0]);
										}
										else if (valorDado[0]!=1){
											printf(" Peão inválido! Selecione um peão para andar %d casas: ", valorDado[0]);
										}
										setbuf(stdin, NULL);
										fgets(peaoAtual, 3, stdin);
										getchar();
									} while (jogadores[i].cor!=peaoAtual[0]);
								}
								if ((jogadores[i].cor)==peaoAtual[0]){
									int casaAtual;
									int casaAtualEncontrada=0;
									
									int numPeao;
									for (numPeao=0; numPeao<4; numPeao++){
										if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
											break;
										}
										else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
											break;
										}
										else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
											break;
										}
										else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
											break;
										} 
									}

									dado = valorDado[0];
									for (casaAtual=0; casaAtual<52; casaAtual++){
										if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
											moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
											imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
											casaAtualEncontrada = 1;
											break;
										}
									}
									if (casaAtualEncontrada==0){
										for (casaAtual=0; casaAtual<5; casaAtual++){
											if (jogadores[i].cor=='Y'){
												if (strcmp(safeZoneY[casaAtual][0].nome, peaoAtual)==0){
													peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
													if (peaoValidado==1){
														for (numPeao=0; numPeao<4; numPeao++){
															if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																break;
															} 
														}

														// O "for" percorre todas as casas e tenta achar o peão
														for (casaAtual=0; casaAtual<52; casaAtual++){

															// Caso ache, chama função "moverPeao" normalmente
															if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																casaAtualEncontrada = 1;
																break;
															}
														}
														if (casaAtualEncontrada==0){
															peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
															casaAtualEncontrada = -1;
															break;
														}
														if (casaAtualEncontrada==0){
															moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
														}
													}
													else if (peaoValidado==0){
														printf("\nVocê não possue peões válidos!\n");
														break;
													}
												}
											}
											else if (jogadores[i].cor=='R'){
												if (strcmp(safeZoneR[casaAtual][0].nome, peaoAtual)==0){
													peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
													if (peaoValidado==1){
														for (numPeao=0; numPeao<4; numPeao++){
															if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																break;
															} 
														}

														// O "for" percorre todas as casas e tenta achar o peão
														for (casaAtual=0; casaAtual<52; casaAtual++){

															// Caso ache, chama função "moverPeao" normalmente
															if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																casaAtualEncontrada = 1;
																break;
															}
														}
														if (casaAtualEncontrada==0){
															peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
															casaAtualEncontrada = -1;
															break;
														}
														if (casaAtualEncontrada==0){
															moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
														}
													}
													else if (peaoValidado==0){
														printf("\nVocê não possue peões válidos!\n");
														break;
													}
												}
											}
											else if (jogadores[i].cor=='G'){
												if (strcmp(safeZoneG[casaAtual][0].nome, peaoAtual)==0){
													peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
													if (peaoValidado==1){
														for (numPeao=0; numPeao<4; numPeao++){
															if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																break;
															} 
														}

														// O "for" percorre todas as casas e tenta achar o peão
														for (casaAtual=0; casaAtual<52; casaAtual++){

															// Caso ache, chama função "moverPeao" normalmente
															if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																casaAtualEncontrada = 1;
																break;
															}
														}
														if (casaAtualEncontrada==0){
															peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
															casaAtualEncontrada = -1;
															break;
														}
														if (casaAtualEncontrada==0){
															moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
														}
													}
													else if (peaoValidado==0){
														printf("\nVocê não possue peões válidos!\n");
														break;
													}
												}
											}
											else if (jogadores[i].cor=='B'){
												if (strcmp(safeZoneB[casaAtual][0].nome, peaoAtual)==0){
													peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
													if (peaoValidado==1){
														for (numPeao=0; numPeao<4; numPeao++){
															if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
																break;
															}
															else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
																break;
															} 
														}

														// O "for" percorre todas as casas e tenta achar o peão
														for (casaAtual=0; casaAtual<52; casaAtual++){

															// Caso ache, chama função "moverPeao" normalmente
															if (strcmp(casa[casaAtual][0].nome, peaoAtual)==0){
																moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
																imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
																casaAtualEncontrada = 1;
																break;
															}
														}
														if (casaAtualEncontrada==0){
															peaoValidado = moverPeaoSafeZone(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
															casaAtualEncontrada = -1;
															break;
														}
														if (casaAtualEncontrada==0){
															moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
															imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
														}
													}
													else if (peaoValidado==0){
														printf("\nVocê não possue peões válidos!\n");
														break;
													}
												}
											}
										}
									}
									printf("\n");
									rodadas++;
									if (casaAtualEncontrada==0){
										moverPeao(peaoAtual, casaAtual, dado, casa, quantJogadores, spawnY, spawnG, spawnR, spawnB, jogadores, i, safeZoneY, safeZoneR, safeZoneG, safeZoneB, peaoYellow, peaoRed, peaoGreen, peaoBlue);
										imprimirTabuleiro(casa, safeZoneY, safeZoneR, safeZoneB, safeZoneG, spawnY, spawnG, spawnR, spawnB);
									}
									if (i==quantJogadores){
										i=0;
									}
								}
							}
							// Caso não encontre peão, ele mostra que não há peões para movimentar
							else {
								printf(" %s, você não possue peões disponíveis para movimentar!\n\n", jogadores[i].nome);
							}
						}
					}
				}

				// Zera os valores do dado e também a variável "perdeVez"
				valorDado[0] = 0;
				valorDado[1] = 0;
				valorDado[2] = 0;
				perdeVez=0;

				// Verifica se algum jogador possui 4 peões na casa final (vencendor)
                for (int y=0; y<quantJogadores; y++){
                    if (jogadores[y].peoesFinais==4){
                        vencendor=1;
                        strcpy(vencendorNome, jogadores[y].nome);
                    }
                }
			} while (vencendor!=1);

			// Mostra o resultado do jogo
            printf("Parabéns, %s!\n", vencendorNome);
            printf("Após essa longa partida, você é o vencedor!");

			return 0;

		// Loop Principal - Fim
	}
// Função Principal - Fim



// Criando as Funções - Início


	// Jogar dado - Início

		/* Função feita para gerar um valor entre 1 e 6. 
		Bem simples, não possue parâmetros e retorna um valor inteiro */

		int jogarDado (){
			return rand() % 6 + 1;
		};
	// Jogar dado - Fim



	// Peão andar - Início
		
		/* Função feita para a movimentação das peças, exceto dentro das "SafeZones". 
		Um pouco complexa, recebe como parâmetro quase todos os dados do jogo. */

		void moverPeao(char peaoAtual[3], int casaAtual, int valorDado, tab casa[52][16], int quantJogadores, char spawnY[4][3], char spawnG[4][3], char spawnR[4][3], char spawnB[4][3], player jogadores[4], int indice, tab safeZoneY[6][16], tab safeZoneR[6][16], tab safeZoneG[6][16], tab safeZoneB[6][16], peao peaoYellow[4], peao peaoRed[4], peao peaoGreen[4], peao peaoBlue[4]){
			
			// Criação de algumas variáveis de controle. 
			int peaoEncontrado=0; 
			int novaCasa;
			int movimentacao = 7;

			// São criados dois laços "for", para percorrer todas as casas do tabuleiro, bem como seus níveis ou posições.
			for (int i=0; i<52; i++){ 
				for (int l=0; l<16; l++){

					// É feita uma verificação para saber se o peão selecionado pelo jogador está dentro daquela casa.
					if ((strcmp(casa[i][l].nome, peaoAtual))==0){
						casaAtual = i; 

						// É criado um laço de repetição para descobrir qual o número daquele peão, bem como se ele já completou uma volta no tabuleiro.
						int numPeao;
						for (numPeao=0; numPeao<4; numPeao++){
							if (strcmp(peaoYellow[numPeao].nome, peaoAtual)==0){

								// Condição para definir uma volta completa. Varia de acordo com as cores do jogador.
								if (peaoYellow[numPeao].casa>=21 && peaoYellow[numPeao].casa<=26){

									// Define a volta completa como TRUE.
									peaoYellow[numPeao].voltaCompleta = 1;
									break;
								}
							}
							else if (strcmp(peaoRed[numPeao].nome, peaoAtual)==0){
								if (peaoRed[numPeao].casa>=47 || peaoRed[numPeao].casa==0){
									peaoRed[numPeao].voltaCompleta = 1;
									break;
								}
							}
							else if (strcmp(peaoGreen[numPeao].nome, peaoAtual)==0){
								if (peaoGreen[numPeao].casa>=34 && peaoGreen[numPeao].casa<39){
									peaoGreen[numPeao].voltaCompleta = 1;
									break;
								}
							}
							else if (strcmp(peaoBlue[numPeao].nome, peaoAtual)==0){
								if (peaoBlue[numPeao].casa>=8 || peaoBlue[numPeao].casa<=13){
									peaoBlue[numPeao].voltaCompleta = 1;
									break;
								}
							} 
						}

						// Aqui começa os teste para saber qual é a situação do peão
						if (jogadores[indice].cor=='Y'){

							// Um for vai percorrer todas as posições daquela casa
							for (int kk=0; kk<52; kk++){
								for (int pp=0; pp<16; pp++){

									// Assim que encontrar o peão, verifica sua condição
									if (strcmp(casa[kk][pp].nome, peaoYellow[numPeao].nome)==0){
										if ((valorDado+casaAtual)>27 && peaoYellow[numPeao].voltaCompleta==1){

											// Pode ser -1, onde ele vai entrar na safeZone
											movimentacao = -1;
											break;
										}
										else {

											// Pode ser 0, onde ele vai se movimentar normalmente pelo tabuleiro
											movimentacao = 0; 
											break;
										}
									}
								}

								// Se uma movimentação for definida, o for se encerra
								if (movimentacao != 7){
									break;
								}
							}
						}
						else if (jogadores[indice].cor=='R'){
							for (int kk=0; kk<52; kk++){
								for (int pp=0; pp<16; pp++){
									if (strcmp(casa[kk][pp].nome, peaoRed[numPeao].nome)==0){
										if ((casaAtual + valorDado)>51){
											if ((((casaAtual + valorDado) % 51) - 1)>1 && peaoRed[numPeao].voltaCompleta==1){
												movimentacao = -1;
												break;
											}
											else {
												movimentacao = 0;
												break;
											}
										}
										else {
											if (casaAtual + valorDado>1 && peaoRed[numPeao].voltaCompleta==1){
												movimentacao = -1;
												break;
											}
											else {
												movimentacao = 0;
												break;
											}
										}
									}
								}
								if (movimentacao!=7){
									break;
								}
							}
						}
						else if (jogadores[indice].cor=='G'){
							for (int kk=0; kk<52; kk++){
								for (int pp=0; pp<16; pp++){
									if (strcmp(casa[kk][pp].nome, peaoGreen[numPeao].nome)==0){
										if ((valorDado+casaAtual)>40 && peaoGreen[numPeao].voltaCompleta==1){
											movimentacao = -1;
											break;
										}
										else {
											movimentacao = 0;
											break;
										}
									}
								}
								if (movimentacao!=7){
									break;
								}
							}
						}
						else if (jogadores[indice].cor=='B'){
							for (int kk=0; kk<52; kk++){
								for (int pp=0; pp<16; pp++){
									if (strcmp(casa[kk][pp].nome, peaoBlue[numPeao].nome)==0){
										if ((valorDado+casaAtual)>14 && peaoBlue[numPeao].voltaCompleta==1){
											movimentacao = -1;
											break;
										}
										else {
											movimentacao = 0;
											break;
										}
									}
								}
								if (movimentacao!=7){
									break;
								}
							}
						}


						// Caso o peão irá entrar na safeZone
						if (movimentacao==-1){

							// Verifica qual a cor do jogador
							if (jogadores[indice].cor=='Y'){

								// Novamente verifica se o peão escolhido vai entrar na SafeZone
								if ((valorDado+casaAtual)>27 && peaoYellow[numPeao].voltaCompleta==1){

									// Caso a nova posição esteja livre, o peão é movido pra lá.
									if (strcmp(safeZoneY[((casaAtual+valorDado) % 27) - 1][0].nome, "  ")==0){
										strcpy(casa[casaAtual][peaoYellow[numPeao].posicao].nome, "  ");
										strcpy(safeZoneY[((casaAtual+valorDado) % 27) - 1][0].nome, peaoAtual);

										// Os índices do peão são alterados
										peaoYellow[numPeao].posicao = 0;
										int casaNova = ((casaAtual+valorDado) % 27) - 1;
										peaoYellow[numPeao].casa = casaNova;
										peaoYellow[numPeao].casasRestantes = (6 - (((casaAtual+valorDado) % 27) - 2)) - 2;


										// Limpa a posição atual
										strcpy(casa[i][l].nome, "  ");
									}

									// Caso a nova casa não esteja livre, uma nova posição, dentro daquela casa, é procurada para que o peão seja movido.
									else {
										for (int j=1; j<16; j++){
											if (strcmp(safeZoneY[((casaAtual+valorDado) % 27) - 1][j].nome, "  ")==0){
												strcpy(casa[casaAtual][peaoYellow[numPeao].posicao].nome, "  ");
												strcpy(safeZoneY[((casaAtual+valorDado) % 27) - 1][j].nome, peaoAtual);
												peaoYellow[numPeao].posicao = j;
												int casaNova = ((casaAtual+valorDado) % 27) - 1;
												peaoYellow[numPeao].casa = casaNova;
												peaoYellow[numPeao].casasRestantes = (6 - (((casaAtual+valorDado) % 27) - 2)) - 2;
												strcpy(casa[i][l].nome, "  ");
												break;
											}
										}
									}
								}
							}
							else if (jogadores[indice].cor=='R'){
								if ((casaAtual + valorDado)>51){
									if ((((casaAtual + valorDado) % 51) - 1)>1 && peaoRed[numPeao].voltaCompleta==1){
										if (strcmp(safeZoneR[((casaAtual+valorDado) % 51) - 3][0].nome, "  ")==0){
											strcpy(casa[casaAtual][peaoYellow[numPeao].posicao].nome, "  ");
											strcpy(safeZoneR[((casaAtual+valorDado) % 51) - 3][0].nome, peaoAtual);
											peaoRed[numPeao].posicao = 0;
											int casaNova = ((casaAtual+valorDado) % 51) - 3;
											peaoRed[numPeao].casa = casaNova;
											peaoRed[numPeao].casasRestantes = (6 - (((casaAtual+valorDado) % 51) - 3)) - 2;
											strcpy(casa[i][l].nome, "  ");
										}
										else {
											for (int j=1; j<16; j++){
												if (strcmp(safeZoneR[((casaAtual+valorDado) % 51) - 3][j].nome, "  ")==0){
													strcpy(casa[casaAtual][peaoRed[numPeao].posicao].nome, "  ");
													strcpy(safeZoneR[((casaAtual+valorDado) % 51) - 3][j].nome, peaoAtual);
													peaoRed[numPeao].posicao = j;
													int casaNova = ((casaAtual+valorDado) % 51) - 3;
													peaoRed[numPeao].casa = casaNova;
													peaoRed[numPeao].casasRestantes = (6 - (((casaAtual+valorDado) % 51) - 3)) - 2;
													strcpy(casa[i][l].nome, "  ");  
													break;
												}
											}
										}
									}
								}
								else {
									if (casaAtual + valorDado>1 && peaoRed[numPeao].voltaCompleta==1){
										if (strcmp(safeZoneR[(casaAtual+valorDado) - 2][0].nome, "  ")==0){
											strcpy(casa[casaAtual][peaoYellow[numPeao].posicao].nome, "  ");
											strcpy(safeZoneR[(casaAtual+valorDado) - 2][0].nome, peaoAtual);
											peaoRed[numPeao].posicao = 0;
											int casaNova = (casaAtual+valorDado) - 2;
											peaoRed[numPeao].casa = casaNova;
											peaoRed[numPeao].casasRestantes = (6 - ((casaAtual+valorDado) - 2)) - 2;
											strcpy(casa[i][l].nome, "  ");  
										}
										else {
											for (int j=1; j<16; j++){
												if (strcmp(safeZoneR[(casaAtual+valorDado) - 2][j].nome, "  ")==0){
													strcpy(casa[casaAtual][peaoYellow[numPeao].posicao].nome, "  ");
													strcpy(safeZoneR[(casaAtual+valorDado) - 2][j].nome, peaoAtual);
													peaoRed[numPeao].posicao = j;
													int casaNova = (casaAtual+valorDado) - 2;
													peaoRed[numPeao].casa = casaNova;
													peaoRed[numPeao].casasRestantes = (6 - ((casaAtual+valorDado) - 2)) - 2;
													strcpy(casa[i][l].nome, "  ");  
													break;
												}
											}
										}
									}
								}
							}
							else if (jogadores[indice].cor=='G'){
								if ((valorDado+casaAtual)>40 && peaoGreen[numPeao].voltaCompleta==1){
									if (strcmp(safeZoneG[((casaAtual+valorDado) % 40) - 1][0].nome, "  ")==0){
										strcpy(casa[casaAtual][peaoGreen[numPeao].posicao].nome, "  ");
										strcpy(safeZoneG[((casaAtual+valorDado) % 40) - 1][0].nome, peaoAtual);
										peaoGreen[numPeao].posicao = 0;
										int casaNova = ((casaAtual+valorDado) % 40) - 1;
										peaoGreen[numPeao].casa = casaNova;
										peaoGreen[numPeao].casasRestantes = (6 - ((casaAtual+valorDado) % 40) - 1) - 2;
										strcpy(casa[i][l].nome, "  ");  
									}
									else {
										for (int j=1; j<16; j++){
											if (strcmp(safeZoneG[((casaAtual+valorDado) % 40) - 1][j].nome, "  ")==0){
												strcpy(casa[casaAtual][peaoGreen[numPeao].posicao].nome, "  ");
												strcpy(safeZoneG[((casaAtual+valorDado) % 40) - 1][j].nome, peaoAtual);
												peaoGreen[numPeao].posicao = j;
												peaoGreen[numPeao].casa = ((casaAtual+valorDado) % 40) - 1;
												peaoGreen[numPeao].casasRestantes = (6 - ((casaAtual+valorDado) % 40) - 1) - 2;
												strcpy(casa[i][l].nome, "  ");  
												break;
											}
										}
									}
								}
							}
							else if (jogadores[indice].cor=='B'){
								if ((valorDado+casaAtual)>14 && peaoBlue[numPeao].voltaCompleta==1){
									if (strcmp(safeZoneB[((casaAtual+valorDado) % 14) - 1][0].nome, "  ")==0){
										strcpy(casa[casaAtual][peaoBlue[numPeao].posicao].nome, "  ");
										strcpy(safeZoneB[((casaAtual+valorDado) % 14) - 1][0].nome, peaoAtual);
										peaoBlue[numPeao].posicao = 0;
										int casaNova = ((casaAtual+valorDado) % 14) - 1;
										peaoBlue[numPeao].casa = casaNova;
										peaoBlue[numPeao].casasRestantes = (6 - ((casaAtual+valorDado) % 14) - 1) - 2;
										strcpy(casa[i][l].nome, "  ");  
									}
									else {
										for (int j=1; j<16; j++){
											if (strcmp(safeZoneB[((casaAtual+valorDado) % 14) - 1][j].nome, "  ")==0){
												strcpy(casa[casaAtual][peaoBlue[numPeao].posicao].nome, "  ");
												strcpy(safeZoneB[((casaAtual+valorDado) % 14) - 1][j].nome, peaoAtual);
												peaoBlue[numPeao].posicao = j;
												peaoBlue[numPeao].casa = ((casaAtual+valorDado) % 14) - 1;
												peaoBlue[numPeao].casasRestantes = (6 - ((casaAtual+valorDado) % 14) - 1) - 2;
												strcpy(casa[i][l].nome, "  ");  
												break;
											}
										}
									}
								}
							}
						} 


						// Caso o peão irá movimentar-se normalmente pelo tabuleiro.
						if (movimentacao==0){ 

							// Limpa a posição atual
							strcpy(casa[i][l].nome, "  ");

							// Verifica se a nova casa é maior que 51, para usar diferentes operações.
							if ((casaAtual + valorDado)>51){

								// Caso a nova casa esteja livre, o peão é movido pra ela, e seu índice "posição" definido como 0.
								if (strcmp(casa[((casaAtual + valorDado) % 51) - 1][0].nome, "  ")==0){
									strcpy(casa[((casaAtual + valorDado) % 51) - 1][0].nome, peaoAtual);
									for (int p=0; p<4; p++){
										if (strcmp(peaoYellow[p].nome, peaoAtual)==0){
											peaoYellow[p].posicao = 0;
										}
										else if (strcmp(peaoRed[p].nome, peaoAtual)==0){
											peaoRed[p].posicao = 0;
										}
										else if (strcmp(peaoGreen[p].nome, peaoAtual)==0){
											peaoGreen[p].posicao = 0;
										}
										else if (strcmp(peaoBlue[p].nome, peaoAtual)==0){
											peaoBlue[p].posicao = 0;
										} 
									}
								}

								// Caso a nova casa não esteja livre, novas operações serão realizadas.
								else {
									novaCasa = ((casaAtual + valorDado) % 51) - 1;
									char peaoCasa[3];

									// O peão da casa é armazenado
									strcpy(peaoCasa, casa[((casaAtual + valorDado) % 51) - 1][0].nome);


									// Caso o "PeãoCasa" seja da mesma cor que o peão escolhido pelo jogador, ou for uma casa protegida, é buscada uma nova posição para aquele peão, dentro da nova casa.
									if (casa[((casaAtual + valorDado) % 51) - 1][0].nome[0]==peaoAtual[0] || novaCasa==3 || novaCasa==11 || novaCasa==16 || novaCasa==24 || novaCasa==29 || novaCasa==37 || novaCasa==42 || novaCasa==50){
										
										// Este for procura uma posição livre para o peão, e este é armazenado nela.
										for (int j=1; j<16; j++){
											if (strcmp(casa[((casaAtual + valorDado) % 51) - 1][j].nome, "  ")==0){

												// Coloca o peão escolhido na nova posição.
												strcpy(casa[((casaAtual + valorDado) % 51) - 1][j].nome, peaoAtual);
												int posicaoPeao = j;

												// Neste momento, sua posição é armazenada.
												for (int p=0; p<4; p++){
													if (strcmp(peaoYellow[p].nome, peaoAtual)==0){
														peaoYellow[p].posicao = posicaoPeao;
													}
													else if (strcmp(peaoRed[p].nome, peaoAtual)==0){
														peaoRed[p].posicao = posicaoPeao;
													}
													else if (strcmp(peaoGreen[p].nome, peaoAtual)==0){
														peaoGreen[p].posicao = posicaoPeao;
													}
													else if (strcmp(peaoBlue[p].nome, peaoAtual)==0){
														peaoBlue[p].posicao = posicaoPeao;
													} 
												}
												break;
											}
										}
									}

									// Caso não seja da mesma cor, ou não for uma casa segura, o peão é "comido" e retorna pro seu respectivo Spawn.
									else {
										if (peaoCasa[0] == 'Y'){
											for (int p=0; p<4; p++){
												if (strcmp(spawnY[p], "  ")==0){
													strcpy(spawnY[p], peaoCasa);
													break;
												}
											}
										}
										else if (peaoCasa[0] == 'R'){
											for (int p=0; p<4; p++){
												if (strcmp(spawnR[p], "  ")==0){
													strcpy(spawnR[p], peaoCasa);
													break;
												}
											}
										}
										else if (peaoCasa[0] == 'G'){
											for (int p=0; p<4; p++){
												if (strcmp(spawnG[p], "  ")==0){
													strcpy(spawnG[p], peaoCasa);
													break;
												}
											}
										}
										else if (peaoCasa[0] == 'B'){
											for (int p=0; p<4; p++){
												if (strcmp(spawnB[p], "  ")==0){
													strcpy(spawnB[p], peaoCasa);
													break;
												}
											}
										}

										// Coloca o peão escolhido na nova posição
										strcpy(casa[((casaAtual + valorDado) % 51) - 1][0].nome, peaoAtual); 
									}
								}
							}

							// Caso não for maior que 50, operações mais simples são realizadas, porém com o mesmo intuito.
							else {
								novaCasa = casaAtual + valorDado;
								if (strcmp(casa[casaAtual + valorDado][0].nome, "  ")==0){
									strcpy(casa[casaAtual + valorDado][0].nome, peaoAtual);
									for (int p=0; p<4; p++){
										if (strcmp(peaoYellow[p].nome, peaoAtual)==0){
											peaoYellow[p].posicao = 0;
										}
										else if (strcmp(peaoRed[p].nome, peaoAtual)==0){
											peaoRed[p].posicao = 0;
										}
										else if (strcmp(peaoGreen[p].nome, peaoAtual)==0){
											peaoGreen[p].posicao = 0;
										}
										else if (strcmp(peaoBlue[p].nome, peaoAtual)==0){
											peaoBlue[p].posicao = 0;
										} 
									}
								}
								else {
									char peaoCasa[3];
									strcpy(peaoCasa, casa[casaAtual + valorDado][0].nome);
									if (casa[casaAtual + valorDado][0].nome[0]==peaoAtual[0] || novaCasa==3 || novaCasa==11 || novaCasa==16 || novaCasa==24 || novaCasa==29 || novaCasa==37 || novaCasa==42 || novaCasa==50){
										for (int j=1; j<16; j++){
											if (strcmp(casa[casaAtual + valorDado][j].nome, "  ")==0){
												strcpy(casa[casaAtual + valorDado][j].nome, peaoAtual);
												int posicaoPeao = j;
												for (int p=0; p<4; p++){
													if (strcmp(peaoYellow[p].nome, peaoAtual)==0){
														peaoYellow[p].posicao = posicaoPeao;
													}
													else if (strcmp(peaoRed[p].nome, peaoAtual)==0){
														peaoRed[p].posicao = posicaoPeao;
													}
													else if (strcmp(peaoGreen[p].nome, peaoAtual)==0){
														peaoGreen[p].posicao = posicaoPeao;
													}
													else if (strcmp(peaoBlue[p].nome, peaoAtual)==0){
														peaoBlue[p].posicao = posicaoPeao;
													} 
												}
												break;
											}
										}
									}
									else {
										if (peaoCasa[0] == 'Y'){
											for (int p=0; p<4; p++){
												if (strcmp(spawnY[p], "  ")==0){
													strcpy(spawnY[p], peaoCasa);
													break;
												}
											}
										}
										else if (peaoCasa[0] == 'R'){
											for (int p=0; p<4; p++){
												if (strcmp(spawnR[p], "  ")==0){
													strcpy(spawnR[p], peaoCasa);
													break;
												}
											}
										}
										else if (peaoCasa[0] == 'G'){
											for (int p=0; p<4; p++){
												if (strcmp(spawnG[p], "  ")==0){
													strcpy(spawnG[p], peaoCasa);
													break;
												}
											}
										}
										else if (peaoCasa[0] == 'B'){
											for (int p=0; p<4; p++){
												if (strcmp(spawnB[p], "  ")==0){
													strcpy(spawnB[p], peaoCasa);
													break;
												}
											}
										}
										strcpy(casa[casaAtual + valorDado][0].nome, peaoAtual);  // Atualizar a nova posição
									}
								}
							}
						} 
						peaoEncontrado=1;
					}
				}

				// Se for encontrado algum peão, o loop é encerrado.
				if (peaoEncontrado==1){
					break;
				}
			}

			// Caso nenhum peão for encontrado, e o valor do dado é 6, serão realizadas operações para remover o peão do Spawn.
			if (peaoEncontrado==0){
				if (valorDado==6){
					if (jogadores[indice].cor=='Y'){

						// O for procura qual peão o jogador escolheu.
						for (int k=0; k<4; k++){
							if (strcmp(spawnY[k], peaoAtual)==0){
								
								// Limpa a casa no Spwan.
								strcpy(spawnY[k], "  ");
								novaCasa = 29;
								casaAtual = 29;
								
								// E armazena ele em sua casa de saida, respectiva a sua cor, em uma posição que estiver livre.
								for (int t=0; t<16; t++){
									if (strcmp(casa[29][t].nome, "  ")==0){
										strcpy(casa[29][t].nome, peaoAtual);
										for (int p=0; p<4; p++){
											if (strcmp(peaoYellow[p].nome, peaoAtual)==0){
												peaoYellow[p].posicao = t;
											}
										}
										break;
									}
								}
								
							}
						}
					}
					else if (jogadores[indice].cor=='G'){
						for (int k=0; k<4; k++){
							if (strcmp(spawnG[k], peaoAtual)==0){
								strcpy(spawnG[k], "  ");
								novaCasa = 42;
								casaAtual = 42;
								for (int t=0; t<16; t++){
									if (strcmp(casa[42][t].nome, "  ")==0){
										strcpy(casa[42][t].nome, peaoAtual);
										for (int p=0; p<4; p++){
											if (strcmp(peaoGreen[p].nome, peaoAtual)==0){
												peaoGreen[p].posicao = t;
											}
										}
										break;
									}
								}
							}
						}
					}
					else if (jogadores[indice].cor=='R'){
						for (int k=0; k<4; k++){
							if (strcmp(spawnR[k], peaoAtual)==0){
								strcpy(spawnR[k], "  ");
								novaCasa = 3;
								casaAtual = 3;
								for (int t=0; t<16; t++){
									if (strcmp(casa[3][t].nome, "  ")==0){
										strcpy(casa[3][t].nome, peaoAtual);
										for (int p=0; p<4; p++){
											if (strcmp(peaoRed[p].nome, peaoAtual)==0){
												peaoRed[p].posicao = t;
											}
										}
										break;
									}
								}
							}
						}
					}
					else if (jogadores[indice].cor=='B'){
						for (int k=0; k<4; k++){
							if (strcmp(spawnB[k], peaoAtual)==0){
								strcpy(spawnB[k], "  ");
								strcpy(casa[16][0].nome, peaoAtual);
								novaCasa = 16;
								casaAtual = 16;
								for (int t=0; t<16; t++){
									if (strcmp(casa[16][t].nome, "  ")==0){
										strcpy(casa[16][t].nome, peaoAtual);
										for (int p=0; p<4; p++){
											if (strcmp(peaoBlue[p].nome, peaoAtual)==0){
												peaoBlue[p].posicao = t;
											}
										}
										break;
									}
								}
							}
						}
					}
				}
			}

			// Define novos índices para os peões movimentados.
			for (int p=0; p<4; p++){
				if (strcmp(peaoYellow[p].nome, peaoAtual)==0){
					peaoYellow[p].casa = novaCasa;
				}
				else if (strcmp(peaoRed[p].nome, peaoAtual)==0){
					peaoRed[p].casa = novaCasa;
				}
				else if (strcmp(peaoGreen[p].nome, peaoAtual)==0){
					peaoGreen[p].casa = novaCasa;
				}
				else if (strcmp(peaoBlue[p].nome, peaoAtual)==0){
					peaoBlue[p].casa = novaCasa;
				} 
			}

			// É realizada uma verificação para que, caso existam peões em alguma posição abaixo da primeira, eles vão subindo de posição, para aparecerem na tela.
			if (strcmp(casa[casaAtual][0].nome, "  ") == 0) {
				int contPosicao=0;

				// O for percorre todas as posições da casa
				for (int j = 0; j<16; j++) {

					// Verifica se existem peões naquela casa.
					if (strcmp(casa[casaAtual][j].nome, "  ") != 0) {


						// Caso exista, o nome do peão é copiado para a primeira posição. 
						strcpy(casa[casaAtual][contPosicao].nome, casa[casaAtual][j].nome);

						// A nova posição é armazenada.
						for (int k=0; k<4; k++){
							if (strcmp(casa[casaAtual][j].nome, peaoYellow[k].nome)==0){
								peaoYellow[k].posicao = contPosicao;
								break;
							}
							else if (strcmp(casa[casaAtual][j].nome, peaoRed[k].nome)==0){
								peaoRed[k].posicao = contPosicao;
								break;
							}
							else if (strcmp(casa[casaAtual][j].nome, peaoGreen[k].nome)==0){
								peaoGreen[k].posicao = contPosicao;
								break;
							}
							else if (strcmp(casa[casaAtual][j].nome, peaoBlue[k].nome)==0){
								peaoBlue[k].posicao = contPosicao;
								break;
							}
						}

						// Limpar a antiga posição.
						strcpy(casa[casaAtual][j].nome, "  ");
						contPosicao++;
					}
				}
			}
		};
	// Peão andar - Fim



	// Imprimir tabuleiro - Início

		/* Função feita para a impressão do tabuleiro gráfico. 
		Bem simples, recebe como parâmetro todas as casas do tabuleiro. */

		void imprimirTabuleiro(tab casa[52][16], tab safeZoneY[6][16], tab safeZoneR[6][16], tab safeZoneB[6][16], tab safeZoneG[6][16], char spawnY[4][3], char spawnG[4][3], char spawnR[4][3], char spawnB[4][3]){
			printf("\n\n");
			printf("\n");
			printf(" \033[37m**********************************************************************************\n");
			printf(" \033[37m*                                                                                *\n");
			printf(" \033[37m*                                 ____ ____ ____                                 *\n");
			printf(" \033[37m*                                |    |    |    |                                *\n");
			printf(" \033[37m*                                | %s | %s | %s |                                *\n", casa[0][0].nome, casa[1][0].nome, casa[2][0].nome);
			printf(" \033[37m*        \033[32m____G____\033[37m               |____|\033[31m____\033[37m|\033[31m____\033[37m|               \033[31m____R____\033[37m        *\n");
			printf(" \033[37m*       \033[32m|    |    |\033[37m              |    \033[31m|   R|   R|\033[37m              \033[31m|    |    |\033[37m       *\n");
			printf(" \033[37m*       \033[32m| %s | %s |\033[37m              | %s \033[31m| %s | %s |\033[37m              \033[31m| %s | %s |\033[37m       *\n", spawnG[0], spawnG[1], casa[51][0].nome , safeZoneR[0][0].nome, casa[3][0].nome , spawnR[0], spawnR[1]);
			printf(" \033[37m*       \033[32m|____|____|\033[37m              |____\033[31m|____|____|\033[37m              \033[31m|____|____|\033[37m       *\n");
			printf(" \033[37m*       \033[32m|    |    |\033[37m              |*   \033[31m|   R|\033[37m    |              \033[31m|    |    |\033[37m       *\n");
			printf(" \033[37m*       \033[32m| %s | %s |\033[37m              | %s \033[31m| %s |\033[37m %s |              \033[31m| %s | %s |\033[37m       *\n", spawnG[3], spawnG[2], casa[50][0].nome , safeZoneR[1][0].nome, casa[4][0].nome , spawnR[3], spawnR[2]);
			printf(" \033[37m*       \033[32m|____|____|\033[37m              |____\033[31m|____|\033[37m____|              \033[31m|____|____|\033[37m       *\n");
			printf(" \033[37m*                                |    \033[31m|   R|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[31m| %s |\033[37m %s |                                *\n", casa[49][0].nome , safeZoneR[2][0].nome, casa[5][0].nome );
			printf(" \033[37m*                                |____\033[31m|____|\033[37m____|                                *\n");
			printf(" \033[37m*                                |    \033[31m|   R|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[31m| %s |\033[37m %s |                                *\n", casa[48][0].nome , safeZoneR[3][0].nome, casa[6][0].nome );
			printf(" \033[37m*                                |____\033[31m|____|\033[37m____|                                *\n");
			printf(" \033[37m*                                |    \033[31m|   R|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[31m| %s |\033[37m %s |                                *\n", casa[47][0].nome , safeZoneR[4][0].nome, casa[7][0].nome );
			printf(" \033[37m*   ____ \033[32m____ \033[37m____ ____ ____ ____|____\033[31m|____|\033[37m____|____ ____ ____ ____ ____ ____   *\n");
			printf(" \033[37m*  |    \033[32m|   G|\033[37m    |    |    |    |    |    |    |    |    |    |   *|    |    |  *\n");
			printf(" \033[37m*  | %s \033[32m| %s |\033[37m %s | %s | %s | %s | == | == | == | %s | %s | %s | %s | %s | %s |  *\n", casa[41][0].nome , casa[42][0].nome , casa[43][0].nome , casa[44][0].nome , casa[45][0].nome , casa[46][0].nome , casa[8][0].nome , casa[9][0].nome , casa[10][0].nome , casa[11][0].nome , casa[12][0].nome , casa[13][0].nome );
			printf(" \033[37m*  |____\033[32m|____|____\033[37m|\033[32m____\033[37m|\033[32m____\033[37m|\033[32m____\033[37m|____|____|____|\033[34m____\033[37m|\033[34m____\033[37m|\033[34m____\033[37m|\033[34m____\033[37m|\033[34m____\033[37m|____|  *\n");
			printf(" \033[37m*  |    \033[32m|   G|   G|   G|   G|   G|\033[37m    |    |    \033[34m|   B|   B|   B|   B|   B|\033[37m    |  *\n");
			printf(" \033[37m*  | %s \033[32m| %s | %s | %s | %s | %s |\033[37m == | == | == \033[34m| %s | %s | %s | %s | %s |\033[37m %s |  *\n", casa[40][0].nome , safeZoneG[0][0].nome, safeZoneG[1][0].nome, safeZoneG[2][0].nome, safeZoneG[3][0].nome, safeZoneG[4][0].nome, safeZoneB[4][0].nome, safeZoneB[3][0].nome, safeZoneB[2][0].nome, safeZoneB[1][0].nome, safeZoneB[0][0].nome, casa[14][0].nome );
			printf(" \033[37m*  |____\033[32m|____|____|____|____|____|\033[37m____|____|____\033[34m|____|____|____|____|____|\033[37m____|  *\n");
			printf(" \033[37m*  |    |    |   *|    |    |    |    |    |    |    |    |    |    \033[34m|   B|\033[37m    |  *\n");
			printf(" \033[37m*  | %s | %s | %s | %s | %s | %s | == | == | == | %s | %s | %s | %s \033[34m| %s |\033[37m %s |  *\n", casa[39][0].nome , casa[38][0].nome , casa[37][0].nome , casa[36][0].nome , casa[35][0].nome , casa[34][0].nome , casa[20][0].nome , casa[19][0].nome , casa[18][0].nome , casa[17][0].nome , casa[16][0].nome , casa[15][0].nome );
			printf(" \033[37m*  |____|____|____|____|____|____|____|\033[33m____\033[37m|____|____|____|____|____\033[34m|____|\033[37m____|  *\n");
			printf(" \033[37m*                                |    \033[33m|   Y|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[33m| %s |\033[37m %s |                                *\n", casa[33][0].nome , safeZoneY[4][0].nome, casa[21][0].nome );
			printf(" \033[37m*                                |____\033[33m|____|\033[37m____|                                *\n");
			printf(" \033[37m*                                |    \033[33m|   Y|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[33m| %s |\033[37m %s |                                *\n", casa[32][0].nome , safeZoneY[3][0].nome, casa[22][0].nome );
			printf(" \033[37m*                                |____\033[33m|____|\033[37m____|                                *\n");
			printf(" \033[37m*                                |    \033[33m|   Y|\033[37m    |                                *\n");
			printf(" \033[37m*                                | %s \033[33m| %s |\033[37m %s |                                *\n", casa[31][0].nome , safeZoneY[2][0].nome, casa[23][0].nome );
			printf(" \033[37m*        \033[33m____Y____\033[37m               |____\033[33m|____|\033[37m____|               \033[34m____B____\033[37m        *\n");
			printf(" \033[37m*       \033[33m|    |    |\033[37m              |    \033[33m|   Y|\033[37m   *|              \033[34m|    |    |\033[37m       *\n");
			printf(" \033[37m*       \033[33m| %s | %s |\033[37m              | %s \033[33m| %s |\033[37m %s |              \033[34m| %s | %s |\033[37m       *\n", spawnY[0], spawnY[1], casa[30][0].nome , safeZoneY[1][0].nome, casa[24][0].nome , spawnB[0], spawnB[1]);
			printf(" \033[37m*       \033[33m|____|____|\033[37m              |\033[33m____\033[33m|____|\033[37m____|              \033[34m|____|____|\033[37m       *\n");
			printf(" \033[37m*       \033[33m|    |    |\033[37m              \033[33m|Y   |   Y|\033[37m    |              \033[34m|    |    |\033[37m       *\n");
			printf(" \033[37m*       \033[33m| %s | %s |\033[37m              \033[33m| %s | %s |\033[37m %s |              \033[34m| %s | %s |\033[37m       *\n", spawnY[3], spawnY[2], casa[29][0].nome , safeZoneY[0][0].nome, casa[25][0].nome , spawnB[3], spawnB[2]);
			printf(" \033[37m*       \033[33m|____|____|\033[37m              \033[33m|____|____|\033[37m____|              \033[34m|____|____|\033[37m       *\n");
			printf(" \033[37m*                                |    |    |    |                                *\n");
			printf(" \033[37m*                                | %s | %s | %s |                                *\n", casa[28][0].nome , casa[27][0].nome , casa[26][0].nome );
			printf(" \033[37m*                                |____|____|____|                                *\n");
			printf(" \033[37m*                                                                                *\n");
			printf(" \033[37m*                                                                                *\n");
			printf(" \033[37m**********************************************************************************\n\n");
		};
	// Imprimir tabuleiro - Fim



	// Mover peão, na SafeZone - Início

		/* Função feita para a movimentação das peças, desta vez, dentro das "SafeZones". 
		Um pouco menos complexa que a "moverPeao", recebe como parâmetro quase todos os dados do jogo. */

		int moverPeaoSafeZone(char peaoAtual[3], int casaAtual, int valorDado, tab casa[52][16], int quantJogadores, char spawnY[4][3], char spawnG[4][3], char spawnR[4][3], char spawnB[4][3], player jogadores[4], int indice, tab safeZoneY[6][16], tab safeZoneR[6][16], tab safeZoneG[6][16], tab safeZoneB[6][16], peao peaoYellow[4], peao peaoRed[4], peao peaoGreen[4], peao peaoBlue[4]){
			
			int pulaRodada=0;

			// Captura o número do peão
			int numPeao;
			int entrou = 0;
			for (int p=0; p<4; p++){
				if (strcmp(peaoYellow[p].nome, peaoAtual)==0){
					numPeao = p;
				}
				else if (strcmp(peaoRed[p].nome, peaoAtual)==0){
					numPeao = p;
				}
				else if (strcmp(peaoGreen[p].nome, peaoAtual)==0){
					numPeao = p;
				}
				else if (strcmp(peaoBlue[p].nome, peaoAtual)==0){
					numPeao = p;
				}
			}

			// Verifica a cor do jogador
			if (jogadores[indice].cor=='Y'){

				// Procura a casa que o peão atual está
				for (int i=0; i<5; i++){
					for (int l=0; l<16; l++){
						if ((strcmp(safeZoneY[i][l].nome, peaoAtual))==0){


							int casaAtual = i;
							if ((casaAtual+valorDado)>peaoYellow[numPeao].casasRestantes){
								do {
									if (valorDado==1){
										printf(" Peão inválido! Selecione um peão para andar %d casa: ", valorDado);
									}
									else if (valorDado!=1){
										printf(" Peão inválido! Selecione um peão para andar %d casas: ", valorDado);
									}
									setbuf(stdin, NULL);
									fgets(peaoAtual, 3, stdin);
									getchar();

									for (int y=0; y<4; y++){
										if (strcmp(peaoYellow[y].nome, peaoAtual)==0){
											numPeao = y;
										}
									}
									pulaRodada++;
									if (pulaRodada>5){
										return 0;
									}
								} while ((casaAtual+valorDado)>peaoYellow[numPeao].casasRestantes);
								if (pulaRodada<5){
									return 1;
								}
							}
							if ((casaAtual+valorDado)<peaoYellow[numPeao].casasRestantes){

								// Caso a nova casa esteja livre, ele copia o peão pra ela
								if (strcmp(safeZoneY[casaAtual + valorDado][0].nome, "  ")==0){
									strcpy(safeZoneY[casaAtual + valorDado][0].nome, peaoAtual);
									strcpy(safeZoneY[i][l].nome, "  "); 
									peaoYellow[numPeao].posicao = 0;
									peaoYellow[numPeao].casa = casaAtual+valorDado;
									peaoYellow[numPeao].casasRestantes -= casaAtual+valorDado;
                                    if (peaoYellow[numPeao].casasRestantes==0){
                                        jogadores[indice].peoesFinais++;
                                    }
									entrou++;
								}

								// Caso a nova casa não esteja livre, ele procura uma casa vazia e copia o peão pra ela
								else {
									for (int j=1; j<16; j++){
										if (strcmp(safeZoneY[casaAtual + valorDado][j].nome, "  ")==0){
											strcpy(safeZoneY[casaAtual + valorDado][j].nome, peaoAtual);
											strcpy(safeZoneY[i][l].nome, "  "); 
											int posicaoPeao = j;
											peaoYellow[numPeao].posicao = posicaoPeao; 
											peaoYellow[numPeao].casa = casaAtual+valorDado;
											peaoYellow[numPeao].casasRestantes -= casaAtual+valorDado;

											// Se o peão entrar na casa final dele, soma 1 nos peões finais do player
                                            if (peaoYellow[numPeao].casasRestantes==0){
                                                jogadores[indice].peoesFinais++;
                                            }
											entrou++;
											break;
										}
									}
								}
							}
						}
					}

					// Caso o peão entre em alguma das verificações, ele fecha do "for"
					if (entrou!=0){
						break;
					}
				}
			}
			else if (jogadores[indice].cor=='R'){
				for (int i=0; i<5; i++){
					for (int l=0; l<16; l++){
						if ((strcmp(safeZoneR[i][l].nome, peaoAtual))==0){
							int casaAtual = i;
							if ((casaAtual+valorDado)>peaoRed[numPeao].casasRestantes){
								do {
									if (valorDado==1){
										printf(" Peão inválido! Selecione um peão para andar %d casa: ", valorDado);
									}
									else if (valorDado!=1){
										printf(" Peão inválido! Selecione um peão para andar %d casas: ", valorDado);
									}
									setbuf(stdin, NULL);
									fgets(peaoAtual, 3, stdin);
									getchar();

									for (int y=0; y<4; y++){
										if (strcmp(peaoRed[y].nome, peaoAtual)==0){
											numPeao = y;
										}
									}
									pulaRodada++;
									if (pulaRodada>5){
										return 0;
									}
								} while ((casaAtual+valorDado)>peaoRed[numPeao].casasRestantes);
								if (pulaRodada<5){
									return 1;
								}
							}
							if ((casaAtual+valorDado)<peaoRed[numPeao].casasRestantes){
								if (strcmp(safeZoneR[casaAtual + valorDado][0].nome, "  ")==0){
									strcpy(safeZoneR[casaAtual + valorDado][0].nome, peaoAtual);
									strcpy(safeZoneR[i][l].nome, "  "); 
									peaoRed[numPeao].posicao = 0;
									peaoRed[numPeao].casa = casaAtual+valorDado;
									peaoRed[numPeao].casasRestantes -= casaAtual+valorDado;
                                    if (peaoRed[numPeao].casasRestantes==0){
                                        jogadores[indice].peoesFinais++;
                                    }
									entrou++;
								}
								else {
									for (int j=1; j<16; j++){
										if (strcmp(safeZoneR[casaAtual + valorDado][j].nome, "  ")==0){
											strcpy(safeZoneR[casaAtual + valorDado][j].nome, peaoAtual);
											strcpy(safeZoneR[i][l].nome, "  "); 
											int posicaoPeao = j;
											peaoRed[numPeao].posicao = posicaoPeao; 
											peaoRed[numPeao].casa = casaAtual+valorDado;
											peaoRed[numPeao].casasRestantes -= casaAtual+valorDado;
                                            if (peaoRed[numPeao].casasRestantes==0){
                                                jogadores[indice].peoesFinais++;
                                            }
											entrou++;
											break;
										}
									}
								}
							}
						}
					}
					if (entrou!=0){
						break;
					}
				}
			}
			else if (jogadores[indice].cor=='G'){
				for (int i=0; i<5; i++){
					for (int l=0; l<16; l++){
						if ((strcmp(safeZoneG[i][l].nome, peaoAtual))==0){  
							int casaAtual = i;
							if ((casaAtual+valorDado)>peaoGreen[numPeao].casasRestantes){
								do {
									if (valorDado==1){
										printf(" Peão inválido! Selecione um peão para andar %d casa: ", valorDado);
									}
									else if (valorDado!=1){
										printf(" Peão inválido! Selecione um peão para andar %d casas: ", valorDado);
									}
									setbuf(stdin, NULL);
									fgets(peaoAtual, 3, stdin);
									getchar();

									for (int y=0; y<4; y++){
										if (strcmp(peaoGreen[y].nome, peaoAtual)==0){
											numPeao = y;
										}
									}
									pulaRodada++;
									if (pulaRodada>5){
										return 0;
									}
								} while ((casaAtual+valorDado)>peaoGreen[numPeao].casasRestantes);
								if (pulaRodada<5){
									return 1;
								}
							}
							if ((casaAtual+valorDado)<peaoGreen[numPeao].casasRestantes){
								if (strcmp(safeZoneG[casaAtual + valorDado][0].nome, "  ")==0){
									strcpy(safeZoneG[casaAtual + valorDado][0].nome, peaoAtual);
									strcpy(safeZoneG[i][l].nome, "  "); 
									peaoGreen[numPeao].posicao = 0;
									peaoGreen[numPeao].casa = casaAtual+valorDado;
									peaoGreen[numPeao].casasRestantes -= casaAtual+valorDado;
                                    if (peaoGreen[numPeao].casasRestantes==0){
                                        jogadores[indice].peoesFinais++;
                                    }
									entrou++;
								}
								else {
									for (int j=1; j<16; j++){
										if (strcmp(safeZoneG[casaAtual + valorDado][j].nome, "  ")==0){
											strcpy(safeZoneG[casaAtual + valorDado][j].nome, peaoAtual);
											strcpy(safeZoneG[i][l].nome, "  "); 
											int posicaoPeao = j;
											peaoGreen[numPeao].posicao = posicaoPeao; 
											peaoGreen[numPeao].casa = casaAtual+valorDado;
											peaoGreen[numPeao].casasRestantes -= casaAtual+valorDado;
                                            if (peaoGreen[numPeao].casasRestantes==0){
                                                jogadores[indice].peoesFinais++;
                                            }
											entrou++;
											break;
										}
									}
								}
							}
						}
					}
					if (entrou!=0){
						break;
					}
				}
			}
			else if (jogadores[indice].cor=='B'){
				for (int i=0; i<5; i++){
					for (int l=0; l<16; l++){
						if ((strcmp(safeZoneB[i][l].nome, peaoAtual))==0){ 
							int casaAtual = i;
							if ((casaAtual+valorDado)>peaoBlue[numPeao].casasRestantes){
								do {
									if (valorDado==1){
										printf(" Peão inválido! Selecione um peão para andar %d casa: ", valorDado);
									}
									else if (valorDado!=1){
										printf(" Peão inválido! Selecione um peão para andar %d casas: ", valorDado);
									}
									setbuf(stdin, NULL);
									fgets(peaoAtual, 3, stdin);
									getchar();

									for (int y=0; y<4; y++){
										if (strcmp(peaoBlue[y].nome, peaoAtual)==0){
											numPeao = y;
										}
									}
									pulaRodada++;
									if (pulaRodada>5){
										return 0;
									}
								} while ((casaAtual+valorDado)>peaoBlue[numPeao].casasRestantes);
								if (pulaRodada<5){
									return 1;
								}
							}
							if ((casaAtual+valorDado)<peaoBlue[numPeao].casasRestantes){
								if (strcmp(safeZoneB[casaAtual + valorDado][0].nome, "  ")==0){
									strcpy(safeZoneB[casaAtual + valorDado][0].nome, peaoAtual);
									strcpy(safeZoneB[i][l].nome, "  "); 
									peaoBlue[numPeao].posicao = 0;
									peaoBlue[numPeao].casa = casaAtual+valorDado;
									peaoBlue[numPeao].casasRestantes -= casaAtual+valorDado;
                                    if (peaoBlue[numPeao].casasRestantes==0){
                                        jogadores[indice].peoesFinais++;
                                    }
									entrou++;
								}
								else {
									for (int j=1; j<16; j++){
										if (strcmp(safeZoneB[casaAtual + valorDado][j].nome, "  ")==0){
											strcpy(safeZoneB[casaAtual + valorDado][j].nome, peaoAtual);
											strcpy(safeZoneB[i][l].nome, "  "); 
											int posicaoPeao = j;
											peaoBlue[numPeao].posicao = posicaoPeao; 
											peaoBlue[numPeao].casa = casaAtual+valorDado;
											peaoBlue[numPeao].casasRestantes -= casaAtual+valorDado;
                                            if (peaoBlue[numPeao].casasRestantes==0){
                                                jogadores[indice].peoesFinais++;
                                            }
											entrou++;
											break;
										}
									}
								}
							}
						}
					}
					if (entrou!=0){
						break;
					}
				}
			}
		};
	// Mover peão, na SafeZone - Fim



// Criando as Funções - Fim
