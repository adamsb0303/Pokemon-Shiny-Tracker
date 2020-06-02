#include <iostream>
#include <fstream>
#include <string>
#include "Pokemon.h"
#include "Game.h"
#include "Method.h"

int main(){
    std::string pokemonName;
    std::cout << "Please enter the Pokemon that you would like to hunt.\n";
    std::cin >> pokemonName;
    for (int i = 0; i < pokemonName.length(); i++)
        pokemonName[i] = tolower(pokemonName[i]);

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
        exit(0);
    }
    
    Pokemon selectedPokemon;
    selectedPokemon.generatePokemonData(pokemonName);
    
    Method currentMethod = Method();
    Game currentGame = Game();
    if (selectedPokemon.encounters == -1) {
        char pause = ' ';
        do {
            system("CLS");
            currentGame.printGames();
            std::string userGame = " ";
            std::cout << "What game are you hunting in?\n\n";
            pause = getchar();
            getline(std::cin, userGame);
            currentGame.setCurrentGame(userGame);
            if (currentGame.generation == 0) {
                std::cout << "The game that you entered was not recognized.";
                pause = getchar();
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
        //currentGame.setCurrentGame(selectedPokemon.game);
       // currentMethod.setMethod(selectedPokemon.method, currentGame);
    }
    currentMethod.shinyHunt(selectedPokemon);
}

