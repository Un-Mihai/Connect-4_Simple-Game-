#include "GeneratorMutari.h"

char GeneratorMutari::culoare;
char GeneratorMutari::culoare_inamic;
char GeneratorMutari::copie_rama[6][7] = {
	{'#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#'},
	{'#', '#', '#', '#', '#', '#', '#'}
};


void GeneratorMutari::setCuloare(char culoare) {
	GeneratorMutari::culoare = culoare;
	GeneratorMutari::culoare_inamic = (culoare == 'G') ? 'R' : 'G';
}

void GeneratorMutari::realizeazaMutareJucator(int coloana, int rand) {
	copie_rama[rand][coloana] = culoare_inamic;
}

void GeneratorMutari::realizeazaMutare(int coloana, char culoare_mutare) {
	if (copie_rama[0][coloana] != '#') {
		return;
	}

	int rand = 5;
	while (copie_rama[rand][coloana] != '#') {
		rand--;
	}

	copie_rama[rand][coloana] = culoare_mutare;
}

void GeneratorMutari::undoMutare(int coloana) {
	if (copie_rama[5][coloana] == '#') {
		return;
	}

	int rand = 0;
	while (copie_rama[rand][coloana] == '#') {
		rand++;
	}

	copie_rama[rand][coloana] = '#';
}

int GeneratorMutari::getColoanaMutare() {
	int scor_maxim = -10000;
	int coloana_aleasa = 0;
	for (int i = 0; i < 7; i++) {
		if (copie_rama[0][i] != '#') {
			continue;
		}

		realizeazaMutare(i, culoare);
		int scor_mutare = getScorMutare(0, 6, false);
		undoMutare(i);

		if (scor_mutare > scor_maxim) {
			scor_maxim = scor_mutare;
			coloana_aleasa = i;
		}
	}
	realizeazaMutare(coloana_aleasa, culoare);
	return coloana_aleasa;
}

int GeneratorMutari::getScorMutare(int current_depth, int max_depth, bool maximize) { // minimax

	if (current_depth == max_depth) {
		return getEvaluareMutare();
	}

	int scor_curent = getEvaluareMutare();
	if (scor_curent <= -900000 || scor_curent >= 900000) {
		if (scor_curent > 0) {
			return scor_curent - current_depth * 1000;
		}
		return scor_curent + current_depth * 1000;
	}

	if (maximize) {

		int scor_maxim = -1000000;

		for (int i = 0; i < 7 && scor_maxim < 900000; i++) {
			if (copie_rama[0][i] != '#') {
				continue;
			}

			realizeazaMutare(i, culoare);
			int scor_mutare = getScorMutare(current_depth + 1, max_depth, !maximize);
			undoMutare(i);

			if (scor_mutare > scor_maxim) {
				scor_maxim = scor_mutare;
			}
		}

		return scor_maxim;
	}

	int scor_minim = 1000000;

	for (int i = 0; i < 7 && scor_minim > -900000; i++) {
		if (copie_rama[0][i] != '#') {
			continue;
		}

		realizeazaMutare(i, culoare_inamic);
		int scor_mutare = getScorMutare(current_depth + 1, max_depth, !maximize);
		undoMutare(i);

		
		if (scor_mutare < scor_minim) {
			scor_minim = scor_mutare;
		}
	}

	return scor_minim;
}

int GeneratorMutari::getEvaluareMutare() {// evaluarea returneaza efectiv scorul acelei pozitii si atat, nu se duce mai departe
	return getScorOrizontal() + getScorVertical() + getScorDiagonal();
}

int GeneratorMutari::getScorOrizontal() {
	int scor_orizontal = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			scor_orizontal += getScorLinie(i, j, 0, 1, culoare);
		}
	}

	int scor_orizontal_inamic = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			scor_orizontal_inamic += getScorLinie(i, j, 0, 1, culoare_inamic);
		}
	}

	return scor_orizontal - scor_orizontal_inamic;
}

int GeneratorMutari::getScorVertical() {
	int scor_vertical = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			scor_vertical += getScorLinie(i, j, 1, 0, culoare);
		}
	}

	int scor_vertical_inamic = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			scor_vertical_inamic += getScorLinie(i, j, 1, 0, culoare_inamic);
		}
	}

	return scor_vertical - scor_vertical_inamic;
}

int GeneratorMutari::getScorDiagonal() {
	int scor_diagonal = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			scor_diagonal += getScorLinie(i, j, 1, 1, culoare);
		}
	}

	for (int i = 3; i < 6; i++) { 
		for (int j = 0; j < 4; j++) {
			scor_diagonal += getScorLinie(i, j, -1, 1, culoare);
		}
	}

	int scor_diagonal_inamic = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			scor_diagonal_inamic += getScorLinie(i, j, 1, 1, culoare_inamic);
		}
	}

	for (int i = 3; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			scor_diagonal_inamic += getScorLinie(i, j, -1, 1, culoare_inamic);
		}
	}

	return scor_diagonal - scor_diagonal_inamic;
}

int GeneratorMutari::getScorLinie(int y, int x, int pas_y, int pas_x, char culoare_verificare) {
	int nr_jetoane = 0; // numarul de jetoane ale generatorului (inamicul jucatorului)
	int scor = 0;
	char culoare_oponent = (culoare_verificare == 'G') ? 'R' : 'G';

	for (int i = 0; i < 4; i++) {
		if (copie_rama[y][x] == culoare_oponent) {
			return 0;
		}

		if (copie_rama[y][x] == culoare_verificare) {
			nr_jetoane++;
			if (x == 3) {
				scor += 10;
			}
		}


		x += pas_x;
		y += pas_y;
	}

	switch (nr_jetoane) {
		case 4: return scor + 1000000;
		case 3: return scor + 10000;
		case 2: return scor + 100;
	}


	return scor;
}

void GeneratorMutari::reset() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			copie_rama[i][j] = '#';
		}
	}
}