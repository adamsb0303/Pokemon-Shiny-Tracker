#include <fstream>
#include <iostream>
#include <string>
#include "Game.h"
#include "Pokemon.h"

//Array of all Pokemon Games
const std::string Games[8][6] = { {"Red", "Green", "Blue", "Yellow", " ", " "},
								{"Gold", "Silver", "Crystal", " ", " ", " "},
								{"Ruby", "Sapphire", "FireRed", "LeafGreen", "Emerald", " "},
								{"Diamond", "Pearl", "Platinum", "HeartGold", "SoulSilver", " "},
								{"Black", "White","Black 2", "White 2", " ", " "},
								{"X", "Y", "Omega Ruby", "Alpha Sapphire", " ", " "},
								{"Sun", "Moon", "Ultra Sun", "Ultra Moon", "Lets Go Pikachu", "Lets Go Eevee"},
								{"Sword", "Shield", " ", " ", " ", " "} };

//Initialize variables for Game
Game::Game()
:name(""), methods(), numMethods(0), generation(0), Methods(), shinyLocked(), pokemonIsPresent(true)
{
	for (int i = 0; i < 5; i++)
		methods[i] = " ";
}

//Prints all games
//doesn't print lets go or swsh games if they aren't avaliable
void Game::printGames(int pokemonGeneration, std::string selectedPokemon) {
	std::cout << "Games by Generation:\n";
	for (int i = pokemonGeneration - 1; i < 8; i++) {
		if (!i == 0) {
			if (i == 7 && !avaliableSWSH(selectedPokemon)) {
				break;
			}
			std::cout << i + 1 << ". ";
			for (int j = 0; j < 6; j++) {
				if (i == 6 && j == 3 && !avaliableLetsGo(selectedPokemon)) {
					std::cout << Games[i][j];
					break;
				}
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

//if the pokemon is a legendary it only prints the games that it is caught in
void Game::printGamesRestricted(int pokemonGeneration, std::string pokemonName){
	std::cout << "Games by Generation:\n";
	std::string avaliableGames[6];
	int generationsAvaliable = 0;
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
				generationsAvaliable++;
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
	if (generationsAvaliable == 0) {
		std::cout << "\nThis pokemon can't be shiny hunted through normal means.";
		getchar();
		exit(1);
	}
}

//searches through Game array for name that matches the game that the user entered
//notifies user if the games isn't recognized
void Game::setCurrentGame(std::string game, Pokemon& selectedPokemon) {
	bool created = false;
	for (int i = 0; i < 8 && !created; i++) {
		for (int j = 0; j < 6; j++) {
			std::string currentGame = Games[i][j];
			int length = game.length();
			for (int k = 0; k < length; k++) {
				game[k] = tolower(game[k]);
			}
			length = currentGame.length();
			for (int k = 0; k < length; k++)
				currentGame[k] = tolower(currentGame[k]);
			if (currentGame.compare(game) == 0) {
				name = Games[i][j];
				generation = i + 1;
				getLocations(selectedPokemon);
				generateMethods(generation, name, selectedPokemon);
			}
		}
	}
	//char pause = ' ';
	if (generation == 0) {
		std::cout << "The game that you entered was not recognized";
		getchar();
	}
}


//In the cases of fish and legendary's the way that they are found change based on what game is selected
//for example, X has fish that Y doesn't and some most legendarys can't be found in all pokemon games
void Game::getLocations(Pokemon& selectedPokemon) {
	std::string filePath = "Game Data/Gen " + std::to_string(generation) + "/" + name + ".txt";
	std::ifstream gamePokedex(filePath.c_str());
	std::string pokemon;
	selectedPokemon.special = false;
	if(findLegendaries(selectedPokemon.name))
		selectedPokemon.special = avaliableLegendary(selectedPokemon.name, name, generation);
	selectedPokemon.fish = findFish(selectedPokemon.name);
	selectedPokemon.sos = findSOS(selectedPokemon.name);
	while (getline(gamePokedex, pokemon)) {
		if (selectedPokemon.name.compare(pokemon) == 0) {
			if (!selectedPokemon.fish && !selectedPokemon.special)
				selectedPokemon.wild = true;
			break;
		}
	}
	gamePokedex.close();
}

//Searches files based on the game that was selected and checks
//if the pokemon can be fished in only the generation 6 games
//because the only fish hunting methods are only found in gen 6
bool Game::findFish(std::string selectedPokemon) {
	std::string filePath;
	if (name.compare("X") == 0 || name.compare("Y") == 0)
		filePath = "Game Data/Gen 6/Fish" + name + ".txt";
	else
		filePath = "Game Data/Gen 6/FishORAS.txt";
	std::ifstream fish(filePath.c_str());
	std::string fishes;
	while (getline(fish, fishes)) {
		if (selectedPokemon.compare(fishes) == 0) {
			return true;
			break;
		}
	}
	fish.close();
	return false;
}

//Returns true if the pokemon is a legendary
bool Game::findLegendaries(std::string selectedPokemon) {
	std::string legendaries;
	std::ifstream legends("Game Data/Legendaries.txt");
	while (getline(legends, legendaries)) {
		if (selectedPokemon.compare(legendaries) == 0) {
			return true;
		}
	}
	legends.close();
	return false;
}

//removes special tag if the legendary is avaliable in the game that is selected
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

//returns true if the pokemon can all for help
bool Game::findSOS(std::string selectedPokemon) {
	std::string sosPokemon = "";
	std::ifstream SOS;
	if (name.substr(0, 5).compare("Ultra") == 0)
		SOS.open("Game Data/Gen 7/SOSUltra.txt");
	else
		SOS.open("Game Data/Gen 7/SOS.txt");
	while (getline(SOS, sosPokemon)) {
		if (selectedPokemon.compare(sosPokemon) == 0) {
			return true;
			break;
		}
	}
	if (selectedPokemon.compare("Baltoy") == 0 && name.compare("Ultra Moon") == 0)
		return true;
	if (selectedPokemon.compare("Golett") == 0 && name.compare("Ultra Sun") == 0)
		return true;
	SOS.close();
	return false;
}

//returns true if the pokemon can be found in the lets go games
bool Game::avaliableLetsGo(std::string selectedPokemon) {
	std::string pokemonName;
	std::ifstream letsGo("Game Data/Gen 7/LetsGoPokedex.txt");
	while (getline(letsGo, pokemonName)) {
		if (selectedPokemon.compare(pokemonName) == 0) {
			return true;
		}
	}
	letsGo.close();
	return false;
}

//returns true if the pokemon can be found in Sword or Shield
bool Game::avaliableSWSH(std::string selectedPokemon) {
	std::string pokemonName;
	std::ifstream SWSH("Game Data/Gen 8/SWSHPokedex.txt");
	while (getline(SWSH, pokemonName)) {
		if (selectedPokemon.compare(pokemonName) == 0) {
			return true;
		}
	}
	SWSH.close();
	return false;
}

//based on the game generation and name, the method names are added to an array
//adds shiny locked pokemon based on the game
//based on tags generated above, limits methods that are added to the array
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
			if (name.compare("Diamond") == 0 || name.compare("Pearl") == 0 || name.compare("Platinum") == 0) {	//radar chaining isn't avaliable in HGSS
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
			if (name.compare("X") == 0 || name.compare("Y") == 0) {		//Radar isn't in ORAS and DexNav isn't in XY
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
			if (name.compare("Sun") == 0 || name.compare("Moon") == 0) {	//Worm holes aren't in SM
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
			else if (name.compare("Ultra Sun") == 0 || name.compare("Ultra Moon") == 0) {
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
				if (!selectedPokemon.name.substr(0, 6).compare("Alolan") == 0) {//Alolan Pokemon can only be traded for
					numMethods = 2;
					if (selectedPokemon.wild)
						methods[1] = "Catch Combo";
				}
				else
					numMethods = 1;
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
		if (shinyLocked[i].compare(selectedPokemon.name) == 0) {//adds special tag to pokemon that are shiny locked
			selectedPokemon.special = true;
			break;
		}
	}

	if (!selectedPokemon.special)
		methods[0] = "None";
}
