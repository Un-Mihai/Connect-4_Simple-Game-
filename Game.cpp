#include "Game.h"
#include "Rama.h"
#include "GeneratorMutari.h"

#include <iostream>

Game::Game(int width, int height) : rama(width / 100, height / 100) {
	InitWindow(width, height, "Connect 4");
	SetTargetFPS(60);
	culoare_rama = Color(61, 92, 200, 255);
	this->width = width;
	this->height = height;

	GeneratorMutari::setCuloare((rama.getCuloareLaRand() == 1) ? 'R' : 'G');
}

void Game::Start() {
	while (WindowShouldClose) {

		BeginDrawing();

		ClearBackground(culoare_rama);

		deseneazaJetoane();

		if(rama.getCuloareLaRand() == 2){
			getInputMouse();
		}
		else {
			int coloana = GeneratorMutari::getColoanaMutare();
			int rand = rama.getRandPreview(coloana);
			rama.realizeazaMutare(coloana, rand);
		}

		EndDrawing();
		
	}
}

void Game::getInputMouse() {
	int x = GetMouseX();
	int y = rama.getRandPreview(x / 100);

	if (y != -1) {
		Color culoare_preview = (rama.getCuloareLaRand() == 1) ? Color(224, 212, 60, 80) : Color(223, 30, 30, 80);
		DrawCircle(x - x % 100 + 50, y * 100 + 50, 30, culoare_preview);
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		std::cout << x << '\n';
		rama.realizeazaMutare(x / 100, y);
		GeneratorMutari::realizeazaMutareJucator(x / 100, y);
	}
}

void Game::deseneazaJetoane() const {
	for (int i = 0; i < height / 100; i++) {
		for (int j = 0; j < width / 100; j++) {
			Color culoare_jeton;
			switch (rama.getJeton(i, j)) {
			case 1:
				culoare_jeton = Color(224, 212, 60, 255);
				break;
			case 2:
				culoare_jeton = Color(223, 30, 30, 255);
				break;
			default:
				culoare_jeton = Color(189, 189, 189, 255);
			}
			DrawCircle(j * 100 + 50, i * 100 + 50, 30, culoare_jeton);
		}
	}
}