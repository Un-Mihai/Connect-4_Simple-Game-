#ifndef GAME_H
#define GAME_H

#include<raylib.h>
#include "Rama.h"

class Game {

private:
	Rama rama;
	int width;
	int height;

	Color culoare_rama;

	Color culoare_jeton_galben;
	Color culoare_preview_galben;
	
	Color culoare_jeton_rosu;
	Color culoare_preview_rosu;

	Color culoare_spatiu_liber;
	
public:
	Game(int, int);
	void startJoc();
	void gameOverScreen();

private:
	bool isButtonRestartApasat() const;
	void deseneazaGameOverScreen();
	void getInputUtilizator();
	void getInputGeneratorMutari();
	void deseneazaJetoane() const;
};

#endif
