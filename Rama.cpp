#include "Rama.h"
#include<iostream>

Rama::Rama(int width, int height) {
	if (width > 15 || height > 15) {
		width = height = 15;
	}

	//marime fixa, in viitor poate scalez
	this->width = 7;
	this->height = 6;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rama[i][j] = '#';
		}
	}

	randul_galbenului = false;
	joc_finalizat = false;
}

int Rama::getCuloareLaRand() {
	return (randul_galbenului) ? 1 : 2;
}

int Rama::getRandPreview(int coloana) {
	if (rama[0][coloana] != '#') {
		return -1;
	}

	int rand = height - 1;
	while (rama[rand][coloana] != '#') {
		rand--;
	}

	return rand;
}

void Rama::afisareEroare(const char* mesaj) const {
	std::cout << mesaj << '\n';
}

bool Rama::isJocFinalizat() {
	return joc_finalizat;
}

void Rama::realizeazaMutare(int coloana, int rand) {

	if (rand == -1) {
		afisareEroare("Coloana aleasa e plina!!");
		return;
	}

	char culoare = (randul_galbenului) ? 'G' : 'R';

	rama[rand][coloana] = culoare;

	verificaStatusJoc(rand, coloana, culoare);

	randul_galbenului = !randul_galbenului;
}

void Rama::verificaStatusJoc(int rand, int coloana, char culoare){

	//orizontal
	int secventa = 0;
	for (int k = -3; k <= 3; ++k) {
		int j = coloana + k;

		if (j < 0 || j >= width) {
			continue;
		}
		
		if (rama[rand][j] != culoare) {
			secventa = 0;
			continue;
		}

		secventa++;
		if (secventa == 4) {
			joc_finalizat = true;
			return;
		}
	}

	//vertical
	secventa = 0;
	for (int k = -3; k <= 3; ++k) {
		int i = rand + k;

		if (i < 0 || i >= height) {
			continue;
		}

		if (rama[i][coloana] != culoare) {
			secventa = 0;
			continue;
		}

		secventa++;
		if (secventa == 4) {
			joc_finalizat = true;
			return;
		}
	}

	//diagonala stanga sus - dreaprta jos
	secventa = 0;
	for (int k = -3; k <= 3; ++k) {
		int i = rand + k;
		int j = coloana + k;

		if (i < 0 || i >= height || j < 0 || j >= width) {
			continue;
		}

		if (rama[i][j] != culoare) {
			secventa = 0;
			continue;
		}

		secventa++;
		if (secventa == 4) {
			joc_finalizat = true;
			return;
		}
	}

	//diagonala stanga jos - dreapta sus
	secventa = 0;
	for (int k = -3; k <= 3; ++k) {
		int i = rand - k;
		int j = coloana + k;

		if (i < 0 || i >= height || j < 0 || j >= width) {
			continue;
		}

		if (rama[i][j] != culoare) {
			secventa = 0;
			continue;
		}

		secventa++;
		if (secventa == 4) {
			joc_finalizat = true;
			return;
		}
	}

}

int Rama::getJeton(int rand, int coloana) const {
	if (rand < 0 || rand >= height || coloana < 0 || coloana >= width) {
		return -1;
	}

	if (rama[rand][coloana] == 'G') {
		return 1;
	}

	if (rama[rand][coloana] == 'R') {
		return 2;
	}

	return 0;
}