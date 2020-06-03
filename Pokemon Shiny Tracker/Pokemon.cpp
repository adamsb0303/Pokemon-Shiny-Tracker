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

void Pokemon::findStarters(int generation, std::string game) {
    switch (generation) {
        case 2:
            if (name.compare("Chikorita") == 0 || name.compare("Cyndaquil") == 0 || name.compare("Totodile") == 0)
                special = true;
        case 3:
            if (name.compare("Treecko") == 0 || name.compare("Torchic") == 0 || name.compare("Mudkip") == 0)
                special = true;
        case 4:
            if (name.compare("Turtwig") == 0 || name.compare("Chimchar") == 0 || name.compare("Piplup") == 0)
                special = true;
        case 5:
            if (name.compare("Snivy") == 0 || name.compare("Tepig") == 0 || name.compare("Oshawott") == 0)
                special = true;
        case 6:
            if (name.compare("Chespin") == 0 || name.compare("Fennekin") == 0 || name.compare("Froakie") == 0 && !(game.compare("Omega Ruby") == 0 || game.compare("Alpha Sapphire")));
                special = true;
        case 7:
            if (name.compare("Rowlet") == 0 || name.compare("Litten") == 0 || name.compare("Popplio") == 0)
                special = true;
        case 8:
            if (name.compare("Grookey") == 0 || name.compare("Scorbunny") == 0 || name.compare("Sobble") == 0)
                special = true;
    }

    if (game.compare("LeafGreen") == 0 || game.compare("FireRed") == 0)
        if (name.compare("Bulbasaur") == 0 || name.compare("Charmander") == 0 || name.compare("Squirtle") == 0)
            special = true;

    if(game.compare("Emerald") == 0)
        if (name.compare("Chikorita") == 0 || name.compare("Cyndaquil") == 0 || name.compare("Totodile") == 0)
            special = true;

    if (game.compare("HeartGold") == 0 || game.compare("SoulSilver") == 0) {
        if (name.compare("Bulbasaur") == 0 || name.compare("Charmander") == 0 || name.compare("Squirtle") == 0)
            special = true;
        if (name.compare("Treecko") == 0 || name.compare("Torchic") == 0 || name.compare("Mudkip") == 0)
            special = true;
    }

    if (game.compare("X") == 0 || game.compare("Y") == 0)
        if (name.compare("Bulbasaur") == 0 || name.compare("Charmander") == 0 || name.compare("Squirtle") == 0)
            special = true;

    if (game.compare("Omega Ruby") == 0 || game.compare("Alpha Sapphire") == 0) {
        if (name.compare("Chikorita") == 0 || name.compare("Cyndaquil") == 0 || name.compare("Totodile") == 0)
            special = true;
        if (name.compare("Treecko") == 0 || name.compare("Torchic") == 0 || name.compare("Mudkip") == 0)
            special = true;
        if (name.compare("Turtwig") == 0 || name.compare("Chimchar") == 0 || name.compare("Piplup") == 0)
            special = true;
        if (name.compare("Snivy") == 0 || name.compare("Tepig") == 0 || name.compare("Oshawott") == 0)
            special = true;
    }

    if (game.compare("Sword") == 0 || game.compare("Shield") == 0)
        if (name.compare("Charmander"))
            special = true;
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