#pragma once
#ifndef GAME_H
#define GAME_H

class Pokemon;

class Game{
public:
	std::string name;
	std::string methods[11];
	int numMethods;
	int generation;
	const std::string Methods[10];
	std::string shinyLocked[15];
	bool pokemonIsPresent;

	Game();

	void printGames(int pokemonGeneration, std::string selectedPokemon);

	void printGamesRestricted(int pokemonGeneration, std::string pokemonName);

	void setCurrentGame(std::string game, Pokemon& selectedPokemon);

	void getLocations(Pokemon& selectedPokemon);

	bool findMythicals(std::string selectedPokemon);

	bool findFish(std::string selectedPokemon);

	bool findLegendaries(std::string selectedPokemon);
	
	bool avaliableLegendary(std::string pokemonName, std::string gameName, int generation);

	bool findSOS(std::string selectedPokemon);

	bool avaliableLetsGo(std::string selectedPokemon);

	bool avaliableSWSH(std::string selectedPokemon);

	void generateMethods(int generation, std::string game, Pokemon selectedPokemon);
};

#endif