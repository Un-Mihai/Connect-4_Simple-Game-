#ifndef GAME_H
#define GAME_H

#include<raylib.h>
#include "Rama.h"

class Game {

private:
	Color culoare_rama;
	Rama rama;
	int width;
	int height;
	
public:
	Game(int, int);
	void Start();

private:
	void getApasare();
	void deseneazaJetoane();
	void deseneazaPreview();
};

#endif
