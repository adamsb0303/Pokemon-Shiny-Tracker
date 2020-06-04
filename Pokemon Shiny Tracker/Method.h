#pragma once
#ifndef METHOD_H
#define METHOD_H

class Pokemon;
class Game;

class Method{
public:
	std::string name;
	std::string games;
	int modifier;
	int base;
	int previousEncounters;
	int searchLevel;
	bool shinyCharm;
	bool lure;

	Method();

	void printMethods(std::string methods[5], std::string pokemonName);

	void setMethod(std::string method, Game game, std::string selectedPokemon);

	void shinyHunt(Pokemon pokemon);

	void generateOdds(double encounters);
};

	int simpilifyFraction(double num, int den);
#endif