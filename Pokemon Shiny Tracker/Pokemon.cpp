#include <iostream>
#include <fstream>
#include <string>
#include "Pokemon.h"
#include "Game.h"

Pokemon::Pokemon() {
    name = "";
    generation = 0;
    encounters = 0;
    game = "";
    method = "";
    evolutionStage = 0;
    breedable = false;
    wild = false;
    fish = false;
    sos = false;
    special = false;
}

void Pokemon::generatePokemonData(std::string inputName) {
    char pause = ' ';
    inputName = "Pokedex/" + inputName + ".txt";
    std::ifstream Data(inputName.c_str());
    if (!Data.is_open()) {
        std::cout << "Pokemon not found.";
        pause = getchar();
        pause = getchar();
        exit(1);
    }
    std::string temp = "";
    int counter = 0;
    while (getline(Data, temp)) {
        switch (counter) {
            case 0:
                name = temp;
                break;
            case 1:
                encounters = std::stoi(temp) - 1;
                break;
            case 2:
                generation = std::stoi(temp);
                break;
            case 3:
                game = temp;
                break;
            case 4:
                method = temp;
                break;
            case 5:
                evolutionStage = std::stoi(temp);
                break;
            case 6:
                for (int i = 0; i < 4; i++)
                    family[i] = splitString(temp, i + 1, ' ');
                break;
            case 7:
                breedable = temp.compare("true") == 0;
                break;
            case 8:
                fish = temp.compare("true") == 0;
                break;
            case 9:
                sos = temp.compare("true") == 0;
                break;
            default:
                break;
        }
        counter++;
    }
    Data.close();
}

void Pokemon::getLocations(int generation, std::string name, bool isPresent) {
    std::string filePath = "Game Data/Gen" + generation;
    filePath = "/" + name + ".txt";
    std::ifstream gamePokedex(filePath.c_str());
    std::string pokemon;
    special = false;
    findStarters(generation, name);
    findLegendaries(generation, name);
    while (getline(gamePokedex, pokemon)) {
        if (name.compare(pokemon)) {
            if(!fish && !special)
                wild = true;
            break;
        }
    }
    gamePokedex.close();
}

void Pokemon::findLegendaries(int generation, std::string game) {
    std::string legends;
    std::ifstream Legendaries("Game Data/Legendaries.txt");
    while (getline(Legendaries, legends)) {
        if (name.compare(legends) == 0) {
            special = true;
            break;
        }
    }
    Legendaries.close();
}

std::string Pokemon::splitString(std::string word, int wordNumber, char seperator) {
    int index = word.find(seperator);
    if (wordNumber > 1)
        return splitString(word.substr(index + 1, word.length()), wordNumber - 1, seperator);
    else
        return word.substr(0, index);
}

void Pokemon::savePokemonData() {
    std::string filePath = "Pokedex/" + name + ".txt";
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