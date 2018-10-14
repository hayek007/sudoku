#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>

int main(int argc, char const *argv[]) {

	if(argc != 2){
		printf("Utilisation:\n./main <fichier>\n");
		exit(1);
	}
	FILE* fichier = fopen(argv[1], "r");
	if(fichier == NULL){
		printf("Erreur d'ouverture du fichier %s\n", argv[1]);
		exit(1);
	}
	Sudoku S;
	initialiser_sudoku(S, fichier);
	afficher_sudoku(S);
	if(impossible(S)){
		printf("Sudoku impossible\n");
		exit(1);
	}
	unsigned int compteur = 0;
	if(resoudre(S, &compteur)){
		printf("Sudoku résolu!\n");
		afficher_sudoku(S);
	}
	else{
		printf("Sudoku non résolu\n");
	}
	printf("Fonction appelée: %d fois\n", compteur);
	return 0;
}
