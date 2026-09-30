#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include <algorithm>
#include <vector>

#include "HashMap.h"

// helper to clean a token (keep original comments near the logic)
static std::string cleanWord(const std::string& raw) {
    // une regex qui reconnait les caractères anormaux (négation des lettres)
    static const std::regex re( R"([^a-zA-Z])");
    // élimine la ponctuation et les caractères spéciaux
    std::string w = std::regex_replace(raw, re, "");
    // passe en lowercase
    std::transform(w.begin(), w.end(), w.begin(), ::tolower);
    return w;
}

int main(int argc, char** argv) {
    using namespace std;
    using namespace std::chrono;

    // Allow filename as optional first argument, default to project-root/WarAndPeace.txt
    // Optional second argument is mode (e.g. "count" or "unique").
    string filename = "../WarAndPeace.txt";
    string mode = "count";
    if (argc > 1) filename = argv[1];
    if (argc > 2) mode = argv[2];

    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Could not open '" << filename << "'. Please provide a readable text file as the first argument." << endl;
        cerr << "Usage: " << (argc>0?argv[0]:"TME2") << " [path/to/textfile]" << endl;
        return 2;
    }
    cout << "Parsing " << filename << " (mode=" << mode << ")" << endl;
    
    auto start = steady_clock::now();
    
    // prochain mot lu
    string word;

    if (mode == "count") {
        size_t nombre_lu = 0;
    
        // default counting mode: count total words
        while (input >> word) {
            // élimine la ponctuation et les caractères spéciaux
            word = cleanWord(word);

            // word est maintenant "tout propre"
            if (nombre_lu % 100 == 0)
                // on affiche un mot "propre" sur 100
                cout << nombre_lu << ": "<< word << endl;
            nombre_lu++;
        }
    input.close();
    cout << "Finished parsing." << endl;
    cout << "Found a total of " << nombre_lu << " words." << endl;

    } else if (mode == "unique") {
        vector <string> vu;
        
        while (input >> word) {
            // élimine la ponctuation et les caractères spéciaux
            word = cleanWord(word);
            bool trouve = false;
            // add to seen if it is new
            for(auto & element : vu){
                if(element == word){
                    trouve = true;
                    break;
                }
            }
            if(!trouve){
                vu.push_back(word);//si on a pas trouve on ajoute
            }
        }
    input.close();
    // TODO
    cout << "Found " << vu.size() << " unique words." << endl;

    }else if (mode == "freq") {
        vector <pair<string, int>> vu;
        
        while (input >> word) {
            // élimine la ponctuation et les caractères spéciaux
            word = cleanWord(word);
            bool trouve = false;
            // add to seen if it is new
            for(auto & element : vu){
                if(element.first == word){
                    //vu[i].second++;
                    element.second++;
                    trouve = true;
                    break;
                }
                //i++;
            }
            if(!trouve){
                vu.push_back(make_pair(word,1));//si on a pas trouve on ajoute
                //i = 0;
            }
        }
    input.close();
    std::sort(vu.begin(),vu.end(),[] (const pair<string, int> & a, const pair<string, int> & b) {
        return a.second > b.second;});
    for(int i = 0; i < 10; ++i ){
        cout << vu[i].first << " : " << vu[i].second << endl;
    }

    for(auto & elem : vu){
        if(elem.first == "war"){
            cout << elem.first << " : " << elem.second << endl;
        } else if(elem.first == "peace"){
            cout << elem.first << " : " << elem.second << endl;
        } else if(elem.first == "toto"){
            cout << elem.first << " : " << elem.second << endl;
        }        
    }
    cout << "Found " << vu.size() << " unique words." << endl;

    }
else if (mode == "freqhash") {
    HashMap <string, int> vu(1024);
    
    while (input >> word) {
        // élimine la ponctuation et les caractères spéciaux
        word = cleanWord(word);

        int* ptr = vu.get(word);
        if(ptr != nullptr){
            //incremente
            vu.put(word,(*ptr)+1);//valeur de pointeur augmentée
        }else{
            vu.put(word,1);
        }

        
    }
    input.close();
    std::vector<std::pair<string,int>> entrees;
    entrees = vu.toKeyValuePairs();
    std::sort(entrees.begin(), entrees.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });
    for (size_t i = 0; i < 10; ++i) {
        cout << entrees[i].first << " : " << entrees[i].second << endl;
    }
    cout << "Found " << entrees.size() << " unique words." << endl;

}
    else {
        // unknown mode: print usage and exit
        cerr << "Unknown mode '" << mode << "'. Supported modes: count, unique" << endl;
        input.close();
        return 1;
    }

    // print a single total runtime for successful runs
    auto end = steady_clock::now();
    cout << "Total runtime (wall clock) : " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}


