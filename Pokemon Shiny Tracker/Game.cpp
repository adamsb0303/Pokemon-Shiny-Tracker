#include <fstream>
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
	pokemonIsPresent = true;
}

void Game::printGames(int pokemonGeneration) {
	std::cout << "Games by Generation:\n";
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
	bool created = true;
	for (int i = 0; i < 8 && created; i++) {
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
				selectedPokemon.getLocations(generation, name, pokemonIsPresent);
				if (!pokemonIsPresent) {
					created = false;
					break;
				}
				generateMethods(generation, name, selectedPokemon);
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
	if(!selectedPokemon.special)
		methods[0] = "None";
	switch (generation) {
		case 2 :
			numMethods = 2;
			if(selectedPokemon.breedable)
			methods[1] = "Breeding with Shiny";
			break;
		case 3:
			numMethods = 1;
			break;
		case 4:
			if (name.compare("Diamond") == 0 || name.compare("Pearl") == 0 || name.compare("Platinum") == 0) {
				numMethods = 3;
				if(selectedPokemon.breedable)
					methods[1] = "Masuda";
				if(selectedPokemon.wild)
					methods[2] = "Radar Chaining";
				break;
			}
			else {
				numMethods = 2;
				if(selectedPokemon.breedable)
					methods[1] = "Masuda";
				break;
			}
		case 5:
			numMethods = 2;
			if (selectedPokemon.breedable)
				methods[1] = "Masuda";

			shinyLocked[0] = "Reshiram";
			shinyLocked[1] = "Zekrom";
			if (name.compare("Black") == 0 || name.compare("White") == 0) {
				shinyLocked[3] = "Victini";
			}
			break;
		case 6:
			if (name.compare("X") == 0 || name.compare("Y") == 0) {
				numMethods = 5;
				if (selectedPokemon.breedable)
					methods[1] = "Masuda";
				if (selectedPokemon.wild)
					methods[2] = "Radar Chaining";
				if(selectedPokemon.fish)
					methods[3] = "Chain Fishing";

				std::ifstream friendSafari("Game Data/Friend Safari.txt");
				std::string safariPokemon;
				while (getline(friendSafari, safariPokemon)) {
					if (selectedPokemon.name.compare(safariPokemon) == 0) {
						methods[4] = "Friend Safari";
						break;
					}
				}
				friendSafari.close();

				shinyLocked[0] = "Articuno";
				shinyLocked[1] = "Zapdos";
				shinyLocked[2] = "Moltres";
				shinyLocked[3] = "Mewtwo";
				shinyLocked[4] = "Xerneas";
				shinyLocked[5] = "Yveltal";
				shinyLocked[6] = "Zygarde";
			}
			else {
				numMethods = 4;
				if(selectedPokemon.breedable)
					methods[1] = "Masuda";
				if(selectedPokemon.fish)
					methods[2] = "Chain Fishing";
				if(selectedPokemon.wild)
					methods[3] = "DexNav Chaining";

				shinyLocked[0] = "Kyogre";
				shinyLocked[1] = "Groudon";
				shinyLocked[2] = "Rayquaza";
				shinyLocked[3] = "Deoxys";
			}
			break;
		case 7:
			if (name.compare("Sun") == 0 || name.compare("Moon") == 0) {
				numMethods = 3;
				if(selectedPokemon.breedable)
					methods[1] = "Masuda";
				if(selectedPokemon.sos)
					methods[2] = "SOS Chaining";

				shinyLocked[0] = "Tapu Koko";
				shinyLocked[1] = "Tapu Lele";
				shinyLocked[2] = "Tapu Bulu";
				shinyLocked[3] = "Tapu Fini";
				shinyLocked[4] = "Cosmog";
				shinyLocked[5] = "Solgaleo";
				shinyLocked[6] = "Lunala";
				shinyLocked[7] = "Nihilego";
				shinyLocked[8] = "Buzzwole";
				shinyLocked[9] = "Pheromosa";
				shinyLocked[10] = "Xurkitree";
				shinyLocked[11] = "Celesteela";
				shinyLocked[12] = "Kartana";
				shinyLocked[13] = "Guzzlord";
				shinyLocked[14] = "Necrozma";
			}
			if (name.compare("Ultra Sun") == 0 || name.compare("Ultra Moon") == 0) {
				numMethods = 4;
				if(selectedPokemon.breedable)
					methods[1] = "Masuda";
				if(selectedPokemon.sos)
					methods[2] = "SOS Chaining";
				std::ifstream Wormholes("Game Data/Wormholes.txt");
				std::string wormhole;
				while (getline(Wormholes, wormhole)) {
					if(selectedPokemon.name.compare(wormhole) == 0) {
						methods[3] = "Ultra Wormholes";
						break;
					}
				}
				Wormholes.close();

				shinyLocked[0] = "Tapu Koko";
				shinyLocked[1] = "Tapu Lele";
				shinyLocked[2] = "Tapu Bulu";
				shinyLocked[3] = "Tapu Fini";
				shinyLocked[4] = "Cosmog";
				shinyLocked[5] = "Solgaleo";
				shinyLocked[6] = "Lunala";
				shinyLocked[7] = "Zygarde";
			}
			else {
				numMethods = 2;
				if(selectedPokemon.wild)
					methods[1] = "Catch Combo";
			}
			break;
		case 8:
			numMethods = 3;
			if(selectedPokemon.breedable)
				methods[1] = "Masuda";
			if(selectedPokemon.wild)
				methods[2] = "Total Encounters";

			shinyLocked[0] = "Type: Null";
			shinyLocked[1] = "Zacian";
			shinyLocked[2] = "Zamazenta";
			shinyLocked[3] = "Eternatus";
			break;
		default:
			break;
	}
}