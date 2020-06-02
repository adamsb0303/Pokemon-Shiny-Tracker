#pragma once
#ifndef POKEMON_H
#define POKEMON_H

class Pokemon {
public:
	std::string name;
	int generation;
	int encounters;
	std::string game;
	std::string method;
	int evolutionStage;
	std::string family[4];
	bool breedable;
	bool wild;
	bool fish;
	bool huntable;
	Pokemon();
	void generatePokemonData(std::string inputName);
	std::string splitString(std::string word, int wordNumber, char seperator);
	void savePokemonData();
	void pokemonCaught();
};

#endif