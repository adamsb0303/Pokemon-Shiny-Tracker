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

	void printGames(int pokemonGeneration);

	void printGamesRestricted(int pokemonGeneration, std::string pokemonName);

	void setCurrentGame(std::string game, Pokemon selectedPokemon);

	void getLocations(Pokemon& selectedPokemon);

	bool findMythicals(Pokemon& selectedPokemon);

	bool findFish(Pokemon& selectedPokemon);

	bool findLegendaries(Pokemon& selectedPokemon);
	
	bool avaliableLegendary(std::string pokemonName, std::string gameName, int generation);

	bool findSOS(Pokemon selectedPokemon);

	void generateMethods(int generation, std::string game, Pokemon selectedPokemon);
};

#endif