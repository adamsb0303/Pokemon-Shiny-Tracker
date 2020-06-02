#include <iostream>
#include <fstream>
#include <string>
#include "Pokemon.h"
Pokemon::Pokemon() {
    name = "";
    generation = 0;;
    breedable = true;
    encounters = 0;
    game = "";
    method = "";
    evolutionStage = 0;
    huntable = true;
}

void Pokemon::generatePokemonData(std::string inputName) {
    inputName = "Pokedex/" + inputName + ".txt";
    std::ifstream Data(inputName.c_str());
    if (!Data.is_open()) {
        std::cout << "Pokemon not found.";
        exit(1);
    }
    std::string temp = "";
    getline(Data, temp);
    name = splitString(temp, 1, ',');
    generation = std::stoi(splitString(temp, 2, ','));
    breedable = splitString(temp, 3, ',').compare("true") == 0;
    encounters = std::stoi(splitString(temp, 4, ',')) - 1;
    game = splitString(temp, 5, ',');
    method = splitString(temp, 6, ',');
    evolutionStage = std::stoi(splitString(temp, 7, ','));
    for (int i = 1; i <= evolutionStage; i++) {
        family[i-1] = splitString(splitString(temp, 8 ,','), i, ' ');
    }
    huntable = splitString(temp, 9, ',').compare("true") == 0;
    Data.close();
}

std::string Pokemon::splitString(std::string word, int wordNumber, char seperator) {
    int index = word.find(seperator);
    if (wordNumber > 1)
        return splitString(word.substr(index + 1, word.length()), wordNumber - 1, seperator);
    else
        return word.substr(0, index);
}

void Pokemon::savePokemonData() {
    std::string filePath = "Pokedex/" + this->name + ".txt";
    std::ofstream Data(filePath.c_str(), std::ofstream::out | std::ofstream::trunc);
    Data << name + ",";
    Data << generation << ",";
    Data << breedable << ",";
    Data << encounters << ",";
    Data.close();
}

void Pokemon::pokemonCaught() {
    std::ofstream Data("Pokedex/~CaughtPokemon.txt");
    Data << name << "\n";
    Data.close();
}