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
    inputName = "Pokedex/" + inputName + ".txt";
    std::ifstream Data(inputName.c_str());
    if (!Data.is_open()) {
    }
    else {
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