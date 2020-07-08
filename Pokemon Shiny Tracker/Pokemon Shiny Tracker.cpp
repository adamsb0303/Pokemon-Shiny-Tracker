#include <iostream>
#include <fstream>
#include <string>
#include "Pokemon.h"
#include "Game.h"
#include "Method.h"

std::string pokemonSpellCheck(std::string input);

void displayShinies();

void makeLower(std::string& word);

std::string getPokemonName();

int main() {
    Pokemon selectedPokemon = Pokemon();
    char pause = ' ';
    do {
        //prompt user for the name of the pokemon that they are hunting
        std::string pokemonName = getPokemonName();
        if (pokemonName.length() > 20)
            std::cout << "The Pokemon was not recognized.";
        else {
            //Display Previously Caught Shinies
            if (pokemonName.compare("list") == 0) {
                displayShinies(); //Made more readable
                std::cout << "Press any key to exit...";
                pause = getchar();
                pause = getchar();
                exit(0);
            }

            //converts input to all lower case
            makeLower(pokemonName); //Wrote a function to make more concise
            selectedPokemon.generatePokemonData(pokemonName);
            if (selectedPokemon.name.empty())//if the pokemon wasn't generated, it spell checks the input and trys again
                selectedPokemon.generatePokemonData(pokemonSpellCheck(pokemonName));
        }
    } while (selectedPokemon.generation == 0);

    Method currentMethod = Method();
    Game currentGame = Game();
    std::string userGame;

    //if the user has never hunted this pokemon before, it asks for game and method
    if (selectedPokemon.encounters == -1) {
        do {
            std::cout << std::string(100, '\n');
            userGame = "";
            if (currentGame.findLegendaries(selectedPokemon.name)) { //checks if pokemon is mythical or legendary and limits
                currentGame.printGamesRestricted(selectedPokemon.generation, selectedPokemon.name);                     //the games that are printed to the ones that they are
            }                                                                                                           //available in
            else
                currentGame.printGames(selectedPokemon.generation, selectedPokemon.name);
            std::cout << "\nWhat game are you hunting in?\n\n";
            pause = getchar();
            getline(std::cin, userGame);
            if (pause != '\n')//had an issue where on the second loop the first letter would be captured by 'pause'
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

        //generates the objects and methods for the pokemon that this pokemon can evolve from.
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
            std::cout << std::string(100, '\n');
            currentMethod.printMethods(currentGame.methods, selectedPokemon.name);//prints methods of the selected pokemon and the previous evolutions
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
        if (currentGame.generation > 5 || currentGame.name.compare("Black 2") || currentGame.name.compare("White 2")) {//shiny charm isn't avaliable until Black 2 and White 2
            while (pause != 'y' && pause != 'n') {
                std::cout << std::string(100, '\n');
                std::cout << "Do you have a Shiny Charm? y/n\n";
                pause = getchar();
            }
            if (tolower(pause) == 'y') {
                currentMethod.shinyCharm = true;
            }
            if (pause == '\n'){};
        }
        currentMethod.setMethod(currentGame.methods[numMethod - 1], currentGame, selectedPokemon.shinyCharm);
        if(currentMethod.name.empty())
            currentMethod.setMethod(currentGame.methods[numMethod - 1], currentGame, selectedPokemon.shinyCharm);
        if (currentMethod.name.empty())
            currentMethod.setMethod(currentGame.methods[numMethod - 1], currentGame, selectedPokemon.shinyCharm);
    }
    else {
        currentGame.setCurrentGame(selectedPokemon.game, selectedPokemon);
        currentMethod.setMethod(selectedPokemon.method, currentGame, selectedPokemon.shinyCharm);
    }
    currentMethod.shinyHunt(selectedPokemon, currentGame.name);
}

//if the user's input is within 90% accurate to an actual pokemon name it assumes that the user ment to enter that pokemon name
//if the input is <90 and >60 it saves the name and prompts the user if the pokemon closest to what they entered was what they ment to enter
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
	int inputLength = input.length();
	int pokemonLength = Pokemon.length();
        for (int i = 0; i < inputLength && i < pokemonLength; i++) {
            if (tolower(input[i]) == tolower(Pokemon[i])) {
                same++;
                Pokemon[i] = '\0';
            }
            else {
		int checkLength = check.length();
                for (int j = 0; j < checkLength; j++) {
                    if (tolower(input[i]) == tolower(Pokemon[j])) {
                        same++;
                        Pokemon[i] = '\0';
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

//Function that displays previously caught shinies
void displayShinies(){
    std::ifstream caughtShinies("Pokedex/~CaughtPokemon.txt");
    std::string listShinies = "";
    int shinyCount = 1;
    if (caughtShinies.is_open())
    {
        while (getline(caughtShinies, listShinies))
        {
            std::cout << shinyCount << ". " << listShinies << "\n";
            shinyCount++;
        }
    }
}

//Turns every letter in the word to lowercase
void makeLower(std::string& word){
    int wordLength = word.length();
    for (int i = 0; i < wordLength; i++)
    {
        word[i] = tolower(word[i]);
    }
}

//Prompts the user for the name of the Pokémon they are hunting
std::string getPokemonName()
{
	std::cout<<std::string(100, '\n');
	std::string name;
	std::cout<<"Please enter the Pokémon that you would like to hunt or enter 'list' to see all previously caught shiny Pokémon."<<std::endl;
	getline(std::cin, name);
	return name;
}
