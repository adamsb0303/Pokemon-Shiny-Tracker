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
	for (int i = pokemonGeneration - 1; i < 8; i++) {
		if (!i == 0) {
			std::cout << i + 1 << ". ";
			for (int j = 0; j < 6; j++) {
				if (j != 5 && Games[i][j + 1].compare(" ") != 0)
					std::cout << Games[i][j] << ", ";
				else {
					std::cout << Games[i][j];
					break;
				}
			}
			std::cout << "\n";
		}
	}
}

void Game::printGamesRestricted(int pokemonGeneration, std::string pokemonName){
	std::cout << "Games by Generation:\n";
	std::string avaliableGames[6];
	for (int i = pokemonGeneration - 1; i < 8; i++) {
		if (!i == 0) {
			int index = 0;
			for (int j = 0; j < 6; j++) {
				if (!avaliableLegendary(pokemonName, Games[i][j], i + 1)) {
					avaliableGames[index] = Games[i][j];
					index++;
				}
			}
			int k = 0;
			if (avaliableGames[0].compare("") != 0) {
				std::cout << i + 1 << ". ";
			}
			while (avaliableGames[k + 1].compare("") != 0) {
				std::cout << avaliableGames[k] << ", ";
				k++;
			}
			if (avaliableGames[0].compare("") != 0) {
				std::cout << avaliableGames[k] << "\n";
			}
			for (int l = 0; l < 6; l++)
				avaliableGames[l] = "";
		}
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
			if (currentGame.compare(game) == 0) {
				name = Games[i][j];
				generation = i + 1;
				getLocations(selectedPokemon);
				generateMethods(generation, name, selectedPokemon);
				created = true;
			}
		}
	}
	char pause = ' ';
	if (generation == 0) {
		std::cout << "The game that you entered was not recognized.";
		std::cout << game;
		pause = getchar();
	}
}

void Game::getLocations(Pokemon& selectedPokemon) {
	std::string filePath = "Game Data/Gen " + std::to_string(generation) + "/" + name + ".txt";
	std::ifstream gamePokedex(filePath.c_str());
	std::string pokemon;
	selectedPokemon.special = false;
	selectedPokemon.special = findMythicals(selectedPokemon);
	if(findLegendaries(selectedPokemon))
		selectedPokemon.special = avaliableLegendary(selectedPokemon.name, name, generation);
	selectedPokemon.fish = findFish(selectedPokemon);
	while (getline(gamePokedex, pokemon)) {
		if (selectedPokemon.name.compare(pokemon) == 0) {
			if (!selectedPokemon.fish && !selectedPokemon.special)
				selectedPokemon.wild = true;
			break;
		}
	}
	gamePokedex.close();
}

bool Game::findMythicals(Pokemon& selectedPokemon) {
	std::string mythics;
	std::ifstream Mythicals("Game Data/Mythicals.txt");
	while (getline(Mythicals, mythics)) {
		if (selectedPokemon.name.compare(mythics) == 0) {
			return true;
			break;
		}
	}
	Mythicals.close();
	return false;
}

bool Game::findFish(Pokemon& selectedPokemon) {
	std::string filePath;
	if (name.compare("X") == 0 || name.compare("Y") == 0)
		filePath = "Game Data/Gen 6/Fish" + name + ".txt";
	else
		filePath = "Game Data/Gen 6/FishORAS.txt";
	std::ifstream fish(filePath.c_str());
	std::string fishes;
	while (getline(fish, fishes)) {
		if (selectedPokemon.name.compare(fishes) == 0) {
			return true;
			break;
		}
	}
	fish.close();
	return false;
}

bool Game::findLegendaries(Pokemon& selectedPokemon) {
	std::string legendaries;
	std::ifstream legends("Game Data/Legendaries.txt");
	while (getline(legends, legendaries)) {
		if (selectedPokemon.name.compare(legendaries) == 0) {
			return true;
		}
	}
	legends.close();
	return false;
}

bool Game::avaliableLegendary(std::string pokemonName, std::string gameName, int generation) {
	std:: string legendaries = "";
	std::string filePath = "Game Data/Gen " + std::to_string(generation) + "/Legends" + gameName + ".txt";
	std::ifstream gameLegends(filePath.c_str());
	while (getline(gameLegends, legendaries)) {
		if (pokemonName.compare(legendaries) == 0) {
			return false;
			break;
		}
	}
	gameLegends.close();
	return true;
}

void Game::generateMethods(int generation, std::string name, Pokemon selectedPokemon) {
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

	for (int i = 0; i < 15; i++) {
		if (shinyLocked[i].compare(selectedPokemon.name) == 0) {
			selectedPokemon.special = true;
			break;
		}
	}

	if (!selectedPokemon.special)
		methods[0] = "None";
}