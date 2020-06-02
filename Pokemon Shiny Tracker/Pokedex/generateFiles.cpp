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
                            "poliwag","poliwhirl","poliwrath";
                            };
   for(int i = 0; i < 130; i++){
      std::string filePath = list[i] + ".txt";
      std::ofstream myFile(filePath.c_str());
      myFile << list[i] << ",1,true,0, , ,0, ,true";
   }
}
