#include <iostream>
#include <fstream>
#include <string>
#include "Pokemon.h"
#include "Game.h"
#include "Method.h"

int main() {
    Pokemon selectedPokemon;
    char pause = ' ';
    do {
        std::string pokemonName;
        std::cout << "Please enter the Pokemon that you would like to hunt.\n";
        std::cin >> pokemonName;
        if (pokemonName.length() > 11)
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
        }
    } while (selectedPokemon.generation == 0);

    
    
    Method currentMethod = Method();
    Game currentGame = Game();
    if (selectedPokemon.encounters == -1) {
        do {
            system("CLS");
            currentGame.printGames(selectedPokemon.generation);
            std::string userGame = " ";
            std::cout << "\nWhat game are you hunting in?\n\n";
            pause = getchar();
            getline(std::cin, userGame);
            if (userGame.length() > 11) {
                std::cout << "The game that you entered was not recognized.";
                pause = getchar();
            }
            else {
                currentGame.setCurrentGame(userGame, selectedPokemon);
            }
        } while (currentGame.generation == 0);
        
        int numMethod;
        std::string userMethod;
        do {
            numMethod = 0;
            system("CLS");
            currentMethod.printMethods(currentGame.methods);
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
                std::cin >> pause;
            }
            if (tolower(pause) == 'y') {
                currentMethod.shinyCharm = true;
            }
        }
        currentMethod.setMethod(currentGame.methods[numMethod - 1], currentGame);
    }
    else {
        currentGame.setCurrentGame(selectedPokemon.game, selectedPokemon);
        currentMethod.setMethod(selectedPokemon.method, currentGame);
    }
    currentMethod.shinyHunt(selectedPokemon);
}

