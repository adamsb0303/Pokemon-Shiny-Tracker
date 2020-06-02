#include <iostream>
#include <fstream>
#include <fstream>

int main() {
   std::string list[130] = {"bulbasaur", "ivysaur", "venusaur",
                            "charmander", "charmeleon", "charizard",
                            "squirtle", "wartortle", "blastoise",
                            "caterpie", "metapod", "butterfree",
                            "weedle", "kakuna", "beedrill",
                            "pidgey", "pidgeotto", "pidgeot",
                            "rattata", "raticate",
                            "spearow", "fearow",
                            "ekans", "arbok",
                            "pikachu", "raichu",
                            "sandshrew", "sandslash",
                            "nidoran_f", "nidorina", "nidoqueen",
                            "nidoran_m", "nidorino", "nidoking",
                            "clefairy", "clefable",
                            "vulpix", "ninetales",
                            "jigglypuff","wigglytuff",
                            "zubat","golbat",
                            "oddish","gloom","vileplume"
                            "paras","parasect",
                            "venonat","venomoth",
                            "diglett","dugtrio",
                            "meowth","persian",
                            "psyduck","golduck",
                            "mankey","primeape",
                            "growlithe", "arcanine",
                            "poliwag","poliwhirl","poliwrath",
                            };
                            
std::string Games[8][6] = { {"Red", "Green", "Blue", "Yellow", " ", " "},
								{"Gold", "Silver", "Crystal", " ", " ", " "},
								{"Ruby", "Sapphire", "FireRed", "LeafGreen", "Emerald", " "},
								{"Diamond", "Pearl", "Platinum", "HeartGold", "SoulSilver", " "},
								{"Black", "White","Black 2", "White 2", " ", " "},
								{"X", "Y", "Omega Ruby", "Alpha Sapphire", " ", " "},
								{"Sun", "Moon", "Ultra Sun", "Ultra Moon", "Let's Go Pikachu", "Let's Go Eevee"},
								{"Sword", "Shield", " ", " ", " ", " "} };
   //for(int i = 0; i < 130; i++){
      //std::string filePath = list[i] + ".txt";
      //std::ofstream myFile(filePath.c_str());
      //myFile << list[i] << ",1,true,0, , ,0, ,true";
      for(int i = 0; i < 8; i++){
         for(int j = 0; j < 6; j++){
            std::string filePath = "Game Data/" + Games[i][j] + ".txt";
            std::ofstream(filePath.c_str());
         }
      }
   //}
}
