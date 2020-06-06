#pragma once
#ifndef POKEMON_H
#define POKEMON_H

class Game;

class Pokemon {
public:
	std::string name;
	int encounters;
	int generation;
	std::string game;
	std::string method;
	int evolutionStage;
	std::string family[4];
	bool breedable;
	bool wild;
	bool fish;
	bool sos;
	bool special;

	Pokemon();

	void generatePokemonData(std::string inputName);

	void getRegionalVariant(int generation);

	std::string splitString(std::string word, int wordNumber, char seperator);

	void savePokemonData();

	void pokemonCaught();
};

#endif