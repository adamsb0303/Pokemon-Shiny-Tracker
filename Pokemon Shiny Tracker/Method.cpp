#include <iostream>
#include <string>
#include "Method.h"
#include "Game.h"
#include "Pokemon.h"

Method::Method() {
	modifier = 1;
    base = 8192;
    previousEncounters = 0;
	shinyCharm = false;
	lure = false;
}

void Method::printMethods(std::string methods[5]) {
	for (int i = 0; i < 5; i++) {
		if (methods[i].compare(" ") != 0)
			std::cout << i + 1 << ". " << methods[i] << "\n";
		else
			break;
	}
}

void Method::setMethod(std::string method, Game currentGame) {
    if (currentGame.generation >= 5)
        base = base/2;
    if (method.substr(method.length() - 2, method.length() - 1).compare("S") == 0 && currentGame.generation >= 5)
        shinyCharm = true;
    if (currentGame.name.substr(0, 3).compare("Let") == 0) {
        char yn;
        std::cout << "Are you using a Lure? y/n\n";
        std::cin >> yn;
        yn = tolower(yn);
        lure = yn == 'y';
    }
    if (shinyCharm)
        modifier+= 2;
    if (lure)
        modifier++;

    if (method.compare("None") == 0)
        name = "None";
    else if (method.compare("Breeding with Shiny") == 0) {
        name = "Breeding with Shiny";
        modifier += 127;
    }
    else if (method.compare("Masuda") == 0) {
        name = "Masuda";
        if (currentGame.generation == 4)
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
    else if (method.compare("DexNav Chaining") == 0)
        name = "DexNav Chaining";
    else if (method.compare("SOS Chaining") == 0)
        name = "SOS Chaining";
    else if (method.compare("Ultra Wormholes") == 0)
        name = "Ultra Wormholes";
    else if (method.compare("Catch Combo") == 0)
        name = "Catch Combo";
    else if (method.compare("Total Encounters") == 0) {
        name = "Total Encounters";
        std::cout << "Enter the number of enounters prior to this hunt. This value can be found in the pokedex.\n";
        std::cin >> previousEncounters;
    }
}

void Method::shinyHunt(Pokemon pokemon) {
    pokemon.name[0] = toupper(pokemon.name[0]);
    char userInput = ' ';
    pokemon.encounters--;
    for (;;) {
        if (userInput != '1' && userInput != '2') {
            system("CLS");
            std::cout << "Current Hunt: " << pokemon.name << std::endl << "Enter:\n1 Caught\n2 Save and Exit\n3 Reset Counter\n\n";
            pokemon.encounters++;
            Method::generateOdds(pokemon.encounters);
            std::cout << pokemon.encounters;
            userInput = getchar();
            if (userInput == '3') {
                pokemon.encounters = -2;
                continue;
            }
        }
        else
            break;
    } 

    if (userInput == '1') {
        pokemon.pokemonCaught();
        exit(0);
    }
    if (userInput == '2') {
        pokemon.savePokemonData();
        exit(0);
    }
}

void Method::generateOdds(double encounters) {
    std::cout << "Current Shiny Chance\n";
    if (name.compare("Radar Chaining") == 0) {
        if (encounters >= 40)
            encounters = 39;
        std::cout <<  "1/" << simpilifyFraction(static_cast<int>(((65535 / (8200 - encounters * 200)) + modifier - 1) * 10 + 0.5)/10, (65536 / (1 + (abs(base - 8196) / 4096)))) << "\n\n";
    }
    else if (name.compare("Chain Fishing") == 0) {
        if (encounters >= 20)
            encounters = 20;
        std::cout << "1/" << simpilifyFraction(modifier + encounters*2, base) << "\n\n";
    }
    else if (name.compare("DexNav Chaining") == 0) {

    }
    else if (name.compare("SOS Chaining") == 0) {
        if (encounters >= 0 && encounters <= 10)
            std::cout << "1/" << simpilifyFraction(modifier, base) << "\n\n";
        else if (encounters > 10 && encounters <= 20)
            std::cout << "1/" << simpilifyFraction(modifier + 4.0, base) << "\n\n";
        else if (encounters > 20 && encounters <= 30)
            std::cout << "1/" << simpilifyFraction(modifier + 8.0, base) << "\n\n";
        else
            std::cout << "1/" << simpilifyFraction(modifier + 12.0, base) << "\n\n";
    }
    else if (name.compare("Ultra Wormholes") == 0) {
        std::cout << "Assuming Light Year is 5,000 or higher\n1 Ring : 10%\n2 Rings : 19%\n3 Rings : 36%\n\n";
    }
    else if (name.compare("Catch Combo") == 0) {
        if(encounters <= 10)
            std::cout << "1/" << simpilifyFraction(modifier, base) << "\n\n";
        else if (encounters > 10 && encounters <= 20)
            std::cout << "1/" << simpilifyFraction(modifier + 3.0, base) << "\n\n";
        else if (encounters > 20 && encounters <= 30)
            std::cout << "1/" << simpilifyFraction(modifier + 7.0, base) << "\n\n";
        else if (encounters > 30)
            std::cout << "1/" << simpilifyFraction(modifier + 11.0, base) << "\n\n";
    }
    else if (name.compare("Total Encounters") == 0) {
        int totalEncounters = previousEncounters + encounters;
        std::cout << totalEncounters << " Total Encounters\n";
        if(totalEncounters < 50)
            std::cout << "1/" << simpilifyFraction(modifier, base) << "\n\n";
        else if(totalEncounters >= 50 && totalEncounters < 100)
            std::cout << "1/" << simpilifyFraction(modifier + 1.0, base) << "\n\n";
        else if (totalEncounters >= 100 && totalEncounters < 200)
            std::cout << "1/" << simpilifyFraction(modifier + 2.0, base) << "\n\n";
        else if (totalEncounters >= 200 && totalEncounters < 300)
            std::cout << "1/" << simpilifyFraction(modifier + 3.0, base) << "\n\n";
        else if (totalEncounters >= 300 && totalEncounters < 500)
            std::cout << "1/" << simpilifyFraction(modifier + 4.0, base) << "\n\n";
        else if (totalEncounters >= 500)
            std::cout << "1/" << simpilifyFraction(modifier + 5.0, base) << "\n\n";
    }
    else {
        std::cout << "1/" << simpilifyFraction(modifier, base) << "\n\n";
    }
}

int simpilifyFraction(double num, int den) {
    return den / num;
}