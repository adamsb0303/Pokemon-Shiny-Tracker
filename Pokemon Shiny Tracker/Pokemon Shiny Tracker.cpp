#include <iostream>
#include <fstream>
#include <string>
#include "Pokemon.h"
#include "Game.h"
#include "Method.h"

std::string pokemonSpellCheck(std::string input);

int main() {
    Pokemon selectedPokemon = Pokemon();
    char pause = ' ';
    do {
        system("CLS");
        std::string pokemonName;
        std::cout << "Please enter the Pokemon that you would like to hunt.\n";
        getline(std::cin, pokemonName);
        if (pokemonName.length() > 20)
            std::cout << "The Pokemon was not recognized.";
        else {
            //Display Previously Caught Shinies
            if (pokemonName.compare("list") == 0) {
                std::ifstream caughtShinies("Pokedex/~CaughtPokemon.txt");
                std::string listShinies = "";
                int shinyCount = 1;
                if (caughtShinies.is_open()) {
                    while (getline(caughtShinies, listShinies)) {
                        std::cout << shinyCount << ". " << listShinies << "\n";
                        shinyCount++;
                    }
                }
                std::cout << "Press any key to exit...";
                pause = getchar();
                pause = getchar();
                exit(0);
            }

            for (int i = 0; i < pokemonName.length(); i++)
                pokemonName[i] = tolower(pokemonName[i]);
            selectedPokemon.generatePokemonData(pokemonName);
            if (selectedPokemon.name.empty())
                selectedPokemon.generatePokemonData(pokemonSpellCheck(pokemonName));
        }
    } while (selectedPokemon.generation == 0);

    Method currentMethod = Method();
    Game currentGame = Game();
    std::string userGame;
    if (selectedPokemon.encounters == -1) {
        do {
            system("CLS");
            userGame = "";
            if (currentGame.findLegendaries(selectedPokemon)) {
                currentGame.printGamesRestricted(selectedPokemon.generation, selectedPokemon.name);
            }
            else
                currentGame.printGames(selectedPokemon.generation);
            std::cout << "\nWhat game are you hunting in?\n\n";
            pause = getchar();
            getline(std::cin, userGame);
            if (pause != '\n')
                userGame = pause + userGame;
            if (userGame.length() > 20) {
                std::cout << "The game that you entered was not recognized.";
                pause = getchar();
            }
            else {
                currentGame.setCurrentGame(userGame, selectedPokemon);
            }
            userGame = "";
        } while (currentGame.generation == 0);

        Pokemon Pokemonevolution0 = Pokemon();
        Game Gameevolution0 = Game();
        if (selectedPokemon.evolutionStage == 1 || selectedPokemon.evolutionStage == 2) {
            Pokemonevolution0.generatePokemonData(selectedPokemon.family[0]);
            Gameevolution0.setCurrentGame(currentGame.name, Pokemonevolution0);
        }

        Pokemon Pokemonevolution1 = Pokemon();
        Game Gameevolution1 = Game();
        if (selectedPokemon.evolutionStage == 2) {
            Pokemonevolution1.generatePokemonData(selectedPokemon.family[1]);
            Gameevolution1.setCurrentGame(currentGame.name, Pokemonevolution1);
        }

        int numMethod;
        std::string userMethod;
        do {
            numMethod = 0;
            system("CLS");
            currentMethod.printMethods(currentGame.methods, selectedPokemon.name);
            if (selectedPokemon.evolutionStage == 2) {
                currentMethod.printMethods(Gameevolution1.methods, Pokemonevolution1.name);
            }
            if (selectedPokemon.evolutionStage == 2 || selectedPokemon.evolutionStage == 1) {
                currentMethod.printMethods(Gameevolution0.methods, Pokemonevolution0.name);
            }
            std::cout << "\nEnter the number next to the method that you are using.\n";
            std::cin >> numMethod;
            if (numMethod > currentGame.numMethods) {
                std::cout << "The number that you entered exceeds the number of methods listed.";
                pause = getchar();
            }
        } while (numMethod > currentGame.numMethods);
        if (currentGame.generation >= 5) {
            while (pause != 'y' && pause != 'n') {
                system("CLS");
                std::cout << "Do you have a Shiny Charm? y/n\n";
                pause = getchar();
            }
            if (tolower(pause) == 'y') {
                currentMethod.shinyCharm = true;
            }
        }
        currentMethod.setMethod(currentGame.methods[numMethod - 1], currentGame, selectedPokemon.name, selectedPokemon.shinyCharm);
    }
    else {
        currentGame.setCurrentGame(selectedPokemon.game, selectedPokemon);
        currentMethod.setMethod(selectedPokemon.method, currentGame, selectedPokemon.name, selectedPokemon.shinyCharm);
    }
    currentMethod.shinyHunt(selectedPokemon, currentGame.name);
}

std::string pokemonSpellCheck(std::string input) {
    std::ifstream Pokedex("Pokedex/~Pokedex.txt");
    std::string check;
    std::string possible;
    double possiblePercent = 1;
    char YorN;
    while (getline(Pokedex, check)) {
        std::string Pokemon = check;
        double same = 0;
        int total;
        if (check.length() > input.length()) {
            total = check.length();
        }
        else
            total = input.length();
        for (int i = 0; i < input.length() && i < Pokemon.length(); i++) {
            if (tolower(input[i]) == tolower(Pokemon[i])) {
                same++;
                Pokemon[i] = NULL;
            }
            else {
                for (int j = 0; j < check.length(); j++) {
                    if (tolower(input[i]) == tolower(Pokemon[j])) {
                        same++;
                        Pokemon[i] = NULL;
                        break;
                    }
                }
            }
        }
        if ((same / total) * 100 >= 90) {
            return check;
        }
        else if ((same / total) * 100 >= 60 && (same / total) * 100 > possiblePercent) {
            possible = check;
            possiblePercent = (same / total) * 100;
        }

    }
    if (!possible.empty()) {
        std::cout << "Did you mean " << possible << "? y/n\n";
        YorN = getchar();
        if (tolower(YorN) == 'y') {
            return possible;
        }
        else
            return " ";
    }
    else {
        std::cout << "The Pokemon that you entered was not recognized.";
        YorN = getchar();
        return " ";
    }
}