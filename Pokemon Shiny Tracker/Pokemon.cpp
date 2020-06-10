#include <iostream>
#include <fstream>
#include <string>
#include "Pokemon.h"
#include "Game.h"

//initializes variables
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
    special = false;//means that pokemon can't be shiny
    shinyCharm = false;
}

//searches for file and pulls the data from the file with the corresponding name
void Pokemon::generatePokemonData(std::string inputName) {
    char option;
    inputName[0] = toupper(inputName[0]);
    if (inputName.compare("Basculin") == 0) {
        std::cout << "Are you hunting Blue or Red Stripe Basculin? B/R\n";
        option = getchar();
        if (tolower(option) == 'b')
            inputName = inputName + "B";
        else if (tolower(option == 'r'))
            inputName = inputName + "R";
    }
    if (inputName.compare("Nidoran") == 0) {
        std::cout << "Are you hunting Male or Female Nidroran? M/F\n";
        option = getchar();
        if (tolower(option) == 'm')
            inputName = inputName + "M";
        else if (tolower(option == 'f'))
            inputName = inputName + "F";
    }

    getRegionalVariant(inputName);

    inputName = "Pokedex/" + inputName + ".txt";
    std::ifstream Data(inputName.c_str());
    char pause;
    if (!Data.is_open())
        return;
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
                    family[i] = splitString(temp, i + 1, ',');
                break;
            case 7:
                breedable = temp.compare("true") == 0;
                break;
            case 8:
                shinyCharm = temp.compare("true") == 0;
                break;
            default:
                break;
            }
            counter++;
        }
        Data.close();
    }
}

//checks to see if pokemon has a regional variant
//if it does, it asks the user if they are hunting for that variant
void Pokemon::getRegionalVariant(std::string& inputName) {
    std::string Alolan;
    char userInput;
    std::ifstream AlolaPokemon("Game Data/Alolan.txt");
    while (getline(AlolaPokemon, Alolan)) {
        if (inputName.compare(Alolan) == 0) {
            std::cout << "Are you hunting the Alolan Variant? y/n\n";
            userInput = getchar();
            if (tolower(userInput) == 'y') {
                inputName = "Alolan " + inputName;
                return;
            }
        }
    }
    AlolaPokemon.close();

    std::string Galarian;
    std::ifstream GalarPokemon("Game Data/Galarian.txt");
    while (getline(GalarPokemon, Galarian)) {
        if (inputName.compare(Galarian) == 0) {
            std::cout << "Are you hunting the Galarian Variant? y/n\n";
            userInput = getchar();
            if (userInput == '\n')
                userInput = getchar();
            if (tolower(userInput) == 'y') {
                inputName = "Galarian " + inputName;
                return;
            }
        }
    }
    GalarPokemon.close();
}

//splits a string based on the char that is provided
std::string Pokemon::splitString(std::string word, int wordNumber, char seperator) {
    int index = word.find(seperator);
    if (wordNumber > 1)
        return splitString(word.substr(index + 1, word.length()), wordNumber - 1, seperator);
    else
        return word.substr(0, index);
}

//rewrites the data to the file that was opened with the new encounter, game, and method vaules
void Pokemon::savePokemonData(std::string game, std::string method, bool shinyCharm) {
    std::string filePath = "Pokedex/" + name + ".txt";
    std::ofstream Data(filePath.c_str(), std::ofstream::out | std::ofstream::trunc);
    Data << name + "\n";
    Data << encounters << "\n";
    Data << generation << "\n";
    Data << game << "\n";
    Data << method << "\n";
    Data << evolutionStage << "\n";
    for (int i = 0; sizeof(family) / sizeof(family[0]); i++)
        if (family[i].empty())
            break;
        else
            Data << family[i] << ", ";
    if (breedable)
        Data << "\ntrue\n";
    else
        Data << "\nfalse\n";
    if (shinyCharm)
        Data << "true\n";
    else
        Data << "false\n";
    Data.close();
}

//resets pokemon file and adds information to the ~CaughtPokemon file
void Pokemon::pokemonCaught(std::string pokemon, std::string game, std::string method) {
    std::ofstream Data("Pokedex/~CaughtPokemon.txt");
    pokemon[0] = tolower(pokemon[0]);
    std::string filePath = "Pokedex/" + name + ".txt";
    std::ofstream pokemonData(filePath.c_str(), std::ofstream::out | std::ofstream::trunc);
    Data << name << ": " << encounters << " encounters | Pokemon " << game << " | " << method << "\n" ;
    pokemonData << name + "\n";
    pokemonData << 0 << "\n";
    pokemonData << generation << "\n";
    pokemonData << "" << "\n";
    pokemonData << "" << "\n";
    pokemonData << evolutionStage << "\n";
    for (int i = 0; sizeof(family) / sizeof(family[0]); i++)
        if (family[i].empty())
            break;
        else
            pokemonData << family[i] << ", ";
    if (breedable)
        pokemonData << "\ntrue\n";
    else
        pokemonData << "\nfalse\n";
    pokemonData.close();
    Data.close();
}