#include "Game.h"
#include "Rama.h"
#include "GeneratorMutari.h"

#include <iostream>

Game::Game(int width, int height) : rama(width / 100, height / 100) {
	InitWindow(width, height, "Connect 4");
	SetTargetFPS(60);
	
	this->width = width;
	this->height = height;
	
	this->culoare_rama = Color(61, 92, 200, 255);

	this->culoare_jeton_galben = Color(224, 212, 60, 255);
	this->culoare_preview_galben = Color(224, 212, 60, 80);

	this->culoare_jeton_rosu = Color(223, 30, 30, 255);
	this->culoare_preview_rosu = Color(223, 30, 30, 80);

	this->culoare_spatiu_liber = Color(189, 189, 189, 255);

	GeneratorMutari::setCuloare((rama.getCuloareLaRand() == 'G') ? 'R' : 'G');
}

void Game::startJoc() {
	while (!rama.isJocFinalizat() && !WindowShouldClose()) {

		BeginDrawing();

		ClearBackground(culoare_rama);

		deseneazaJetoane();

		if (rama.getCuloareLaRand() == 'R') {
			getInputUtilizator();
		}
		else {
			getInputGeneratorMutari();
		}

		EndDrawing();
	}

	if (WindowShouldClose()) {
		CloseWindow();
		return;
	}

	gameOverScreen();
}

void Game::gameOverScreen() {
	bool joc_nou = false;
	while (!joc_nou && !WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(culoare_rama);

		deseneazaGameOverScreen();

		EndDrawing();

		if (isButtonRestartApasat()) {
			rama.reset();
			GeneratorMutari::reset();
			joc_nou = true;
		}
	}

	if (WindowShouldClose()) {
		CloseWindow();
		return;
	}

	float timp_start = GetTime();
	while (GetTime() - timp_start < 0.5f) {
		BeginDrawing();

		ClearBackground(culoare_rama);

		deseneazaGameOverScreen();

		EndDrawing();
	}

	startJoc();
}

bool Game::isButtonRestartApasat() const{
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		return false;
	}

	int x = GetMouseX();
	int y = GetMouseY();

	if (!(x >= 300 && x <= 450 && y >= 280 && y <= 320)) {
		return false;
	}

	return true;
}


void Game::getInputGeneratorMutari() {
	int coloana = GeneratorMutari::getColoanaMutare();
	int rand = rama.getRandPreview(coloana);
	rama.realizeazaMutare(coloana, rand);
}

void Game::getInputUtilizator() {
	int x = GetMouseX();
	int y = rama.getRandPreview(x / 100);

	if (y != -1) {
		Color culoare_preview = (rama.getCuloareLaRand() == 'G') ? culoare_preview_galben : culoare_preview_rosu;
		DrawCircle(x - x % 100 + 50, y * 100 + 50, 30, culoare_preview);
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		rama.realizeazaMutare(x / 100, y);
		GeneratorMutari::realizeazaMutareJucator(x / 100, y);
	}
}

void Game::deseneazaGameOverScreen() {
	deseneazaJetoane();

	//overlay gri transparent
	DrawRectangle(0, 0, this->width, this->height, Color(118, 115, 114, 90));

	if (rama.getCuloareLaRand() == 'R') {
		DrawText("Ai pierdut!", 200, 150, 50, WHITE);
	}
	else {
		DrawText("Ai casigat!", 200, 150, 50, WHITE);
	}

	DrawRectangle(275, 280, 150, 40, Color(20, 158, 31, 255));

	DrawText("Restart", 290, 290, 20, WHITE);
}

void Game::deseneazaJetoane() const {
	for (int i = 0; i < this->height / 100; i++) {
		for (int j = 0; j < this->width / 100; j++) {
			Color culoare_jeton;
			switch (rama.getJeton(i, j)) {
			case 'G':
				culoare_jeton = this->culoare_jeton_galben;
				break;
			case 'R':
				culoare_jeton = this->culoare_jeton_rosu;
				break;
			default:
				culoare_jeton = this->culoare_spatiu_liber;
			}
			DrawCircle(j * 100 + 50, i * 100 + 50, 30, culoare_jeton);
		}
	}
}