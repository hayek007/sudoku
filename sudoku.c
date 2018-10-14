#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>
#include <ctype.h>

void afficher_sudoku(Sudoku S){
	for(int j=0; j<11; j++){
		printf("--");
	}
	printf("\n");
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			if(j%3==0 && j>0){
				printf("| ");
			}
			if(S[i][j] == 0){
				printf(". ");
			}
			else{
				printf("%d ", S[i][j]);
			}
		}
		if((i+1)%3==0 && i>0){
			printf("\n");
			for(int j=0; j<11; j++){
				printf("--");
			}
		}
		printf("\n");
	}
}

int impossible(Sudoku S){
	int tab[9];
	for(int i=0; i<9; i++){
		for(int k=0; k<9; k++){
			tab[k] = 0;
		}
		for(int j=0; j<9; j++){
			if(S[i][j] != 0){
				if(tab[S[i][j] -1] == 1){
					return 1;
				}
				tab[S[i][j] -1] = 1;
			}
		}
	}
	for(int j=0; j<9; j++){
		for(int k=0; k<9; k++){
			tab[k] = 0;
		}
		for(int i=0; i<9; i++){
			if(S[i][j] != 0){
				if(tab[S[i][j] -1] == 1){
					return 1;
				}
				tab[S[i][j] -1] = 1;
			}
		}
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<9; k++){
				tab[k] = 0;
			}
			for(int e=i*3; e<i*3+3; e++){
				for(int f=j*3; f<j*3+3; f++){
					if(S[e][f] != 0){
						if(tab[S[e][f] -1] == 1){
							return 1;
						}
						tab[S[e][f] -1] = 1;
					}
				}
			}
		}
	}
	return 0;
}

void initialiser_sudoku(Sudoku S, FILE* fichier){
	int c;
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			do{
				c = fgetc(fichier);
			}while(!isdigit(c));
			S[i][j] = c - '0';
		}
	}
}

int verification_sudoku(Sudoku S){
	int tab[9];
	for(int i=0; i<9; i++){
		for(int k=0; k<9; k++){
			tab[k] = 0;
		}
		for(int j=0; j<9; j++){
			if(tab[S[i][j] -1] == 1){
				return 0;
			}
			tab[S[i][j] -1] = 1;
		}
	}
	for(int j=0; j<9; j++){
		for(int k=0; k<9; k++){
			tab[k] = 0;
		}
		for(int i=0; i<9; i++){
			if(tab[S[i][j] -1] == 1){
				return 0;
			}
			tab[S[i][j] -1] = 1;
		}
	}

	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<9; k++){
				tab[k] = 0;
			}
			for(int e=i*3; e<i*3+3; e++){
				for(int f=j*3; f<j*3+3; f++){
					if(tab[S[e][f] -1] == 1){
						return 0;
					}
					tab[S[e][f] -1] = 1;
				}
			}
		}
	}
	return 1;
}

void trouver_vide(Sudoku S, int* x, int* y){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			if(S[i][j] == 0){
				*x = i;
				*y = j;
				return;
			}
		}
	}
	*x = -1;
	*y = -1;
	return;
}

void trouver_jouables(Sudoku S, int ligne, int colonne, int jouables[9]){
	for(int k=0; k<9; k++){
		jouables[k] = 1;
	}

	for(int i=0; i<9; i++){
		jouables[S[i][colonne] -1 ] = 0;
	}
	for(int j=0; j<9; j++){
		jouables[S[ligne][j] -1 ] = 0;
	}

	for(int e=ligne-ligne%3; e<ligne-ligne%3+3; e++){
		for(int f=colonne-colonne%3; f<colonne-colonne%3+3; f++){
			if(S[e][f] != 0){
				jouables[S[e][f] -1 ] = 0;
			}
		}
	}



}

int resoudre(Sudoku S, unsigned int* compteur){
	(*compteur)++;
	int i, j;
	int jouables[9];
	trouver_vide(S, &i, &j);
	if(i == -1 && j == -1){
		return verification_sudoku(S);
	}
	trouver_jouables(S, i, j, jouables);
	int existe_jouables = 0;
	for(int k=0; k<9; k++){
		if(jouables[k] == 1){
			existe_jouables = 1;
		}
	}
/*	if(!existe_jouables){
		printf("Sudoku non résolvable!\n\n");
		afficher_sudoku(S);
	}
*/	for(int k=0; k<9; k++){
		if(jouables[k] == 1){
			S[i][j] = k+1;
			if(resoudre(S, compteur)){
				return 1;
			}
		}
	}
	S[i][j] = 0;
	return 0;

}
