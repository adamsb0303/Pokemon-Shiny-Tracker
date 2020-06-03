#include <iostream>
#include <string>
#include "Game.h"
#include "Pokemon.h"

const std::string Games[8][6] = { {"Red", "Green", "Blue", "Yellow", " ", " "},
								{"Gold", "Silver", "Crystal", " ", " ", " "},
								{"Ruby", "Sapphire", "FireRed", "LeafGreen", "Emerald", " "},
								{"Diamond", "Pearl", "Platinum", "HeartGold", "SoulSilver", " "},
								{"Black", "White","Black 2", "White 2", " ", " "},
								{"X", "Y", "Omega Ruby", "Alpha Sapphire", " ", " "},
								{"Sun", "Moon", "Ultra Sun", "Ultra Moon", "Let's Go Pikachu", "Let's Go Eevee"},
								{"Sword", "Shield", " ", " ", " ", " "} };

Game::Game() {
	name = "";
	generation = 0;
	for (int i = 0; i < 5; i++)
		methods[i] = " ";
	pokemonIsPresent = false;
}

void Game::printGames(int pokemonGeneration) {
	std::cout << "Games by Generation\n\n";
	for (int i = pokemonGeneration; i < 8; i++) {
		std::cout << i + 1 << ". ";
		for (int j = 0; j < 6; j++) {
			if (j != 5 && Games[i][j+1].compare(" ") != 0)
				std::cout << Games[i][j] << ", ";
			else {
				std::cout << Games[i][j];
				break;
			}
		}
		std::cout << "\n";
	}
}

void Game::setCurrentGame(std::string game, Pokemon selectedPokemon) {
	bool created = false;
	for (int i = 0; i < 8 && !created; i++) {
		for (int j = 0; j < 6; j++) {
			std::string currentGame = Games[i][j];
			for (int k = 0; k < game.length(); k++) {
				game[k] = tolower(game[k]);
			}
			for (int k = 0; k < currentGame.length(); k++)
				currentGame[k] = tolower(currentGame[k]);
			if (game.compare(currentGame) == 0) {
				name = Games[i][j];
				generation = i + 1;
				generateMethods(generation, name, selectedPokemon);
				created = true;
				break;
			}
		}
	}
	char pause = ' ';
	if (generation == 0) {
		std::cout << "The game that you entered was not recognized.";
		pause = getchar();
	}
}

void Game::generateMethods(int generation, std::string name, Pokemon selectedPokemon) {
	char pause = ' ';
	switch (generation) {
		case 2 :
			numMethods = 2;
			methods[0] = "None";
			if(selectedPokemon.breedable)
				methods[1] = "Breeding with Shiny";
			break;
		case 3:
			numMethods = 1;
			methods[0] = "None";
			break;
		case 4:
			if (name.compare("Diamond") == 0 || name.compare("Pearl") == 0 || name.compare("Platinum") == 0) {
				numMethods = 3;
				methods[0] = "None";
				if(selectedPokemon.breedable)
					methods[1] = "Masuda";
				if(selectedPokemon.wild)
					methods[2] = "Radar Chaining";
				break;
			}
			else {
				numMethods = 2;
				methods[0] = "None";
				if(selectedPokemon.breedable)
					methods[1] = "Masuda";
				break;
			}
		case 5:
			numMethods = 2;
			methods[0] = "None";
			if (selectedPokemon.breedable)
				methods[1] = "Masuda";
		case 6:
			if (name.compare("X") == 0 || name.compare("Y") == 0) {
				numMethods = 5;
				methods[0] = "None";
				if (selectedPokemon.breedable)
					methods[1] = "Masuda";
				if (selectedPokemon.wild)
					methods[2] = "Radar Chaining";
				methods[3] = "Chain Fishing";
				methods[4] = "Friend Safari";
				break;
			}
			else {
				numMethods = 4;
				methods[0] = "None";
				methods[1] = "Masuda";
				methods[2] = "Chain Fishing";
				methods[3] = "DexNav Chaining";
				break;
			}
		case 7:
			if (name.compare("Ultra Sun") == 0 || name.compare("Ultra Moon") == 0) {
				numMethods = 4;
				methods[0] = "None";
				methods[1] = "Masuda";
				methods[2] = "SOS Chaining";
				methods[3] = "Ultra Wormholes";
				break;
			}
			else if (name.compare("Sun") == 0 || name.compare("Moon") == 0) {
				numMethods = 3;
				methods[0] = "None";
				methods[1] = "Masuda";
				methods[2] = "SOS Chaining";
				break;
			}
			else {
				numMethods = 2;
				methods[0] = "None";
				methods[1] = "Catch Combo";
				break;
			}
		case 8:
			numMethods = 3;
			methods[0] = "None";
			methods[1] = "Masuda";
			methods[2] = "Total Encounters";
			break;
		default:
			break;
	}
}