#include<iostream>

#include "Rama.h"
#include "Game.h"

int main() {
	Game* game = new Game(700, 600);
	game->Start();
}