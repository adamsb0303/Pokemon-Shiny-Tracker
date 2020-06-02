#pragma once
#ifndef GAME_H
#define GAME_H

class Game{
public:
	std::string name;
	std::string methods[5];
	int numMethods;
	int generation;
	const std::string Methods[10];

	Game();

	void printGames();

	void setCurrentGame(std::string game);

	void generateMethods(int generation, std::string game);
};

#endif