#include <iostream>
#include <string>
#include "Method.h"
#include "Game.h"
#include "Pokemon.h"

//initialization
Method::Method() {
	modifier = 1;
    base = 8192;
    previousEncounters = 0;
    searchLevel = 0;
	shinyCharm = false;
	lure = false;
}

//Prints the methods from the array that was taken from the game that is being used
//if there is no method, it notifies the user
void Method::printMethods(std::string methods[5], std::string pokemonName) {
    std::cout << pokemonName << ":\n";
    if (methods[0] == " ") {
        std::cout << "This pokemon cannot be found shiny in the game that you selected.";
    }
	for (int i = 0; i < 5; i++) {
        if (!methods[i].compare(" ") == 0) {
            std::cout << i + 1 << ". " << methods[i] << "\n";
        }
	}
    std::cout << "\n";
}

//Sets Method Data for specified game
void Method::setMethod(std::string method, Game currentGame, std::string selectedPokemon, bool hasCharm) {
    if (currentGame.generation >= 5)//doubles shiny chances if its a gen 5 or higher game
        base = base/2;
    if(hasCharm)
        shinyCharm = hasCharm;//adds shiny charm from pokemon object
    if (currentGame.name.substr(0, 3).compare("Let") == 0) {//checks for either of the lets go games and asks if a lure is being used
        char yn;
        std::cout << "Are you using a Lure? y/n\n";
        std::cin >> yn;
        yn = tolower(yn);
        lure = yn == 'y';
    }
    if (shinyCharm)//adds shiny charm rates if user has a shiny charm
        modifier+= 2;
    if (lure)//adds lure rates if user is using a lure
        modifier++;

    //checks the method array from the given game and assigns the name and increases shiny chances of the Method being used
    if (method.compare("None") == 0)
        name = "None";
    else if (method.compare("Breeding with Shiny") == 0) {
        name = "Breeding with Shiny";
        modifier += 127;
    }
    else if (method.compare("Masuda") == 0) {
        name = "Masuda";
        if (currentGame.generation == 4)//checks generation, since shiny Masuda odds changed after gen 4
            modifier += 4;
        else
            modifier += 5;
    }
    else if (method.compare("Radar Chaining") == 0)
        name = "Radar Chaining";
    else if (method.compare("Chain Fishing") == 0)
        name = "Chain Fishing";
    else if (method.compare("Friend Safari") == 0) {
        name = "Friend Safari";
        modifier += 5;
    }
    else if (method.compare("DexNav Chaining") == 0) {
        name = "DexNav Chaining";
        std::cout << "What is the search level of your target pokemon?\n";//since Search Level can change in between uses of the application
        std::cin >> searchLevel;                                          //the user is prompted to enter the current search level
        searchLevel -= 2;
    }
    else if (method.compare("SOS Chaining") == 0)
        name = "SOS Chaining";
    else if (method.compare("Ultra Wormholes") == 0)
        name = "Ultra Wormholes";
    else if (method.compare("Catch Combo") == 0)
        name = "Catch Combo";
    else if (method.compare("Total Encounters") == 0) {
        name = "Total Encounters";
        std::cout << "Enter the number of enounters prior to this hunt. This value can be found in the pokedex.\n";//since Total Encounters can change in between uses of the application
        std::cin >> previousEncounters;                                                                            //the user is prompted to enter the current total encounters
    }
}

//The screen that the user sees during the shiny hunt
void Method::shinyHunt(Pokemon pokemon, std::string currentGame) {
    pokemon.name[0] = toupper(pokemon.name[0]);
    char userInput = ' ';
    int phase = 0;
    previousEncounters--;
    for (;;) {
        if (userInput != '1' && userInput != '2') {
            userInput = ' ';
            std::cout << std::string(100, '\n');
            if (name.compare("None") == 0)
                std::cout << "Currently no method being used.\n\n";
            else
                std::cout << "Currently using the " << name << " Method\n\n";
            std::cout << "Current Hunt: " << pokemon.name << "\n\nEnter:\n1 Caught\n2 Save and Exit\n3 Reset Counter\n4 Phase\n\n";
            if (phase != 0)
                std::cout << "Phase " << phase << "\n\n";
            Method::generateOdds(pokemon.encounters);
            std::cout << pokemon.encounters;
            userInput = getchar();

            if (userInput == '\n') {
                pokemon.encounters++;
                previousEncounters++;
            }
            if (userInput == '3') {
                pokemon.encounters--;
                searchLevel--;
                previousEncounters--;
                continue;
            }
            if (userInput == '4') {
                std::string phasePokemon;
                getline(std::cin, phasePokemon);
                pokemon.pokemonCaught(phasePokemon, currentGame, name);
                pokemon.encounters = -1;
                phase++;
            }
        }
        else
            break;
    } 

    if (userInput == '1') {
        pokemon.pokemonCaught(pokemon.name, currentGame, name);
        exit(0);
    }
    if (userInput == '2') {
        pokemon.savePokemonData(currentGame, name, shinyCharm);
        exit(0);
    }
}

//prints the odds in terms of 1/x
void Method::generateOdds(double encounters) {
    if (name.compare("Radar Chaining") == 0) {
        if (encounters >= 40)//probablity doesn't increase after 39 encounters
            encounters = 39;
        std::cout <<  "Current Shiny Chance\n1/" << simpilifyFraction(static_cast<int>(((65535 / (8200 - encounters * 200)) + modifier - 1) * 10 + 0.5)/10, (65536 / (1 + (abs(base - 8196) / 4096)))) << "\n\n";
    }
    else if (name.compare("Chain Fishing") == 0) {
        if (encounters >= 20)//probability doesn't increase after 20 encounters.
            encounters = 20;
        std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + encounters*2, base) << "\n\n";
    }
    //calculates points based of Search Level and calculates probability
    else if (name.compare("DexNav Chaining") == 0) {
        int searchPoints = searchLevel;
        double points = 0;
        if (searchLevel < 999) {
            searchLevel++;
            if (searchPoints >= 100) {
                points += 100 * 6.0;
                searchPoints -= 100;
            }
            else
                points += searchLevel * 6.0;

            if (searchPoints >= 100) {
                points += 100 * 2.0;
                searchPoints -= 100;
            }
            else
                points += searchLevel * 2.0;

            if (searchPoints > 0) {
                points += 1 * searchPoints;
            }
        }
        else
            points = 1599;
        points = points / 100;
        double shinyOdds = points / 10000;
        double normalOdds = 1 - shinyOdds;
        
        if(encounters == 49)
            std::cout << "Search Level\n" << searchLevel << "\nCurrent Shiny Chance\n1/" << static_cast<int>(1/(1 - pow(normalOdds, modifier + 5))) << "\n\n";
        else if (encounters == 99)
            std::cout << "Search Level\n" << searchLevel << "\nCurrent Shiny Chance\n1/" << static_cast<int>(1 /(1 - pow(normalOdds, modifier + 10))) << "\n\n";
        else if(static_cast<int>(1 / (1 - pow(normalOdds, modifier))) < base && searchLevel != 0)
            std::cout << "Search Level\n" << searchLevel << "\nCurrent Shiny Chance\n1/" << static_cast<int>(1 /(1 - pow(normalOdds, modifier))) << "\n\n";
        else
            std::cout << "Search Level\n" << searchLevel << "\nCurrent Shiny Chance\n1/" << simpilifyFraction(modifier, base) << "\n\n";
    }
    //1-10 no change. 10-20 add 4 to modifier. 20-30 add 8. >30 add 12 
    else if (name.compare("SOS Chaining") == 0) {
        if (encounters >= 0 && encounters < 10)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier, base) << "\n\n";
        else if (encounters >= 10 && encounters < 20)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 4.0, base) << "\n\n";
        else if (encounters >= 20 && encounters < 30)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 8.0, base) << "\n\n";
        else
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 12.0, base) << "\n\n";
    }
    //Light years is to volatile of a quantity to try to calculate.
    else if (name.compare("Ultra Wormholes") == 0) {
        std::cout << "Assuming Light Year is 5,000 or higher\n1 Ring : 10%\n2 Rings : 19%\n3 Rings : 36%\n\n";
    }
    //1-10 no change. 10-20 add 3 to modifier. 20-30 add 7. >30 add 11
    else if (name.compare("Catch Combo") == 0) {
        if(encounters < 10)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier, base) << "\n\n";
        else if (encounters >= 10 && encounters < 20)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 3.0, base) << "\n\n";
        else if (encounters >= 20 && encounters < 30)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 7.0, base) << "\n\n";
        else if (encounters >= 30)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 11.0, base) << "\n\n";
    }
    //1-50 no change. 50-100 add 1 to modifier. 100-200 add 2. 200-300 add 3. 300-500 add 4. >500 add 5
    else if (name.compare("Total Encounters") == 0) {
        std::cout << previousEncounters << " Total Encounters\n";
        if(previousEncounters < 50)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier, base) << "\n\n";
        else if(previousEncounters >= 50 && previousEncounters < 100)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 1.0, base) << "\n\n";
        else if (previousEncounters >= 100 && previousEncounters < 200)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 2.0, base) << "\n\n";
        else if (previousEncounters >= 200 && previousEncounters < 300)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 3.0, base) << "\n\n";
        else if (previousEncounters >= 300 && previousEncounters < 500)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 4.0, base) << "\n\n";
        else if (previousEncounters >= 500)
            std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier + 5.0, base) << "\n\n";
    }
    //methods such as Masuda and None are caught here
    else {
        std::cout << "Current Shiny Chance\n1/" << simpilifyFraction(modifier, base) << "\n\n";
    }
}

//divides the denominator by the numerator to put the fraction in terms of 1/x
int simpilifyFraction(double num, int den) {
    return den / num;
}