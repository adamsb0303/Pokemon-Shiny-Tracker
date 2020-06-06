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
    char option;
    if (inputName.compare("basculin") == 0) {
        std::cout << "Are you hunting Blue or Red Stripe Basculin? B/R\n";
        option = getchar();
        if (tolower(option) == 'b')
            inputName = inputName + "B";
        else if (tolower(option == 'r'))
            inputName = inputName + "R";
    }
    if (inputName.compare("nidoran") == 0) {
        std::cout << "Are you hunting Male or Female Nidroran? M/F\n";
        option = getchar();
        if (tolower(option) == 'm')
            inputName = inputName + "M";
        else if (tolower(option == 'f'))
            inputName = inputName + "F";
    }
    inputName = "Pokedex/" + inputName + ".txt";
    std::ifstream Data(inputName.c_str());
    if (!Data.is_open());
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
            default:
                break;
            }
            counter++;
        }
        Data.close();
    }
}

void Pokemon::getRegionalVariant(int gen) {
    if (gen >= 7) {
        std::string Alolan;
        char userInput;
        std::ifstream AlolaPokemon("Game Data/Alolan.txt");
        while (getline(AlolaPokemon, Alolan)) {
            if (name.compare(Alolan) == 0) {
                std::cout << "Are you hunting the Alolan Variant? y/n\n";
                userInput = getchar();
                if (userInput == 'y')
                    name = "Alolan " + name;
            }
        }
        AlolaPokemon.close();
    }
    if (gen >= 8) {
        std::string Galarian;
        char userInput;
        std::ifstream GalarPokemon("Game Data/Galarian.txt");
        while (getline(GalarPokemon, Galarian)) {
            if (name.compare(Galarian) == 0) {
                std::cout << "Are you hunting the Galarian Variant? y/n\n";
                userInput = getchar();
                userInput = getchar();
                if (userInput == 'y')
                    name = "Galarian " + name;
            }
        }
        GalarPokemon.close();
    }
}

std::string Pokemon::splitString(std::string word, int wordNumber, char seperator) {
    int index = word.find(seperator);
    if (wordNumber > 1)
        return splitString(word.substr(index + 1, word.length()), wordNumber - 1, seperator);
    else
        return word.substr(0, index);
}

void Pokemon::savePokemonData(std::string game, std::string method) {
    std::string filePath = "Pokedex/" + name + ".txt";
    std::ofstream Data(filePath.c_str(), std::ofstream::out | std::ofstream::trunc);
    Data << name + "\n";
    Data << generation << "\n";
    Data << encounters << "\n";
    Data << game << "\n";
    Data << method << "\n";
    Data << evolutionStage << "\n";
    Data << breedable << "\n";
    Data.close();
}

void Pokemon::pokemonCaught(std::string pokemon) {
    std::ofstream Data("Pokedex/~CaughtPokemon.txt");
    pokemon[0] = tolower(pokemon[0]);
    std::string filePath = "Pokedex/" + name + ".txt";
    std::ofstream pokemonData(filePath.c_str(), std::ofstream::out | std::ofstream::trunc);
    Data << name << ": " << encounters << " encounters" << "\n" ;
    pokemonData << name + "\n";
    pokemonData << generation << "\n";
    pokemonData << 0 << "\n";
    pokemonData << "" << "\n";
    pokemonData << "" << "\n";
    pokemonData << evolutionStage << "\n";
    pokemonData << breedable << "\n";
    pokemonData.close();
    Data.close();
}