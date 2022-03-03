#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;  // Cardinal sin

// Comparison function for map sorting
bool cmp(pair<string, int>& a,
         pair<string, int>& b)
{
    return a.second < b.second;
}
  
// Sorts a map by its values
vector<pair<string, int>> sort_map(map<string, int>& _map) {
    vector<pair<string, int>> vec;
  
    for (auto& it : _map) {
        vec.push_back(it);
    }
    sort(vec.rbegin(), vec.rend(), cmp);

    return vec;
}


// Get the frequency that each word appears in the english language
map<string, float> get_frequencies(string filename) {
    map<string, float> values;
    ifstream file(filename);

    string line, word, value;
    int splitpos;

    while (getline(file, line)) {
        splitpos = line.find(",");
        if (splitpos != 5) { continue; }

        word = line.substr(0, splitpos);
        value = line.substr(splitpos+1, line.length());

        values[word] = 1 + ((float)stoi(value) / 1226734006);  // "Magic Number" is the most amount of times any 5 letter word is used
    }

    file.close();
    return values;
}

// Gets each word and assigns it a score based on its letters and their positions
map<string, int> get_words_scores(string filename, map<string, float> freqs) {
    map<string, int> words;
    map<char, int> letters[5];
    ifstream file(filename);
    string line;

    int i;
    while (getline(file, line)) {
        for (i=0; i<5; i++) {
            letters[i][line[i]] += 1;
        }

        words[line.substr(0,5)] = 0;
    }

    map<string, int> :: iterator it;
    for (it = words.begin(); it != words.end(); it++) { 
        for (i=0; i<5; i++) {
            it->second += letters[i][it->first[i]];
        }
        // Frequency adjusted scores
        
        if (freqs.find(it->first) != freqs.end()) {
            it->second *= freqs[it->first];
        }
    }

    file.close();
    return words;
}

vector<pair<string, int>> filter_words(vector<pair<string, int>> words, string grey, string yellow, string green) {
    vector<pair<string, int>> filtered;
    bool keep = true;
    int i;

    if (yellow.length() < 5) { yellow.insert(yellow.end(), 5-yellow.length(), '-'); }
    if (green.length() < 5) { green.insert(green.end(), 5-green.length(), '-'); }

    // cout << grey << endl << yellow << endl << green << endl;

    // Unbelievably inefficient
    vector<pair<string, int>>::iterator it;
    for (it = words.begin(); it != words.end(); it++) { 
        keep = true;

        for (i=0; i<5; i++) {
            // Checking for greens
            if (green[i] != '-' && it->first[i] != green[i]) {
                keep = false;
                break; 
            }
            // Checking for yellows
            if ((yellow[i] != '-') && (it->first.find(yellow[i]) == -1) || it->first[i] == yellow[i]) {
                keep = false;
                break; 
            }
        }
        if (!keep) { continue; }

        // Checking for greys
        for (auto c : grey) {
            if (c == '-' || c == '\n') { break; }
            if (green.find(c) != -1 || yellow.find(c) != -1) { continue; }
            if (it->first.find(c) != -1) {
                keep = false;
                break; 
            }
        }
        if (!keep) { continue; }
        
        filtered.push_back(make_pair(it->first, it->second));
    }

    return filtered;
}


int main() {
    map<string, float> frequencies = get_frequencies("unigram_freq.csv");
    map<string, int> words = get_words_scores("valid-wordle-words.txt", frequencies);


    vector<pair<string, int>> sorted = sort_map(words);

    int i, j;
    string tmpgreys, greys, yellows, greens;

    tmpgreys = "";
    greys = "";
    yellows = "-----";
    greens = "-----";

    for (i=0; i<6; i++) {

        cout << "Greys: ";
        cin >> tmpgreys;
        if (tmpgreys == "DONE") { break; }
        greys += tmpgreys;

        cout << "Yellows: ";
        cin >> yellows;
        yellows.erase(remove(yellows.begin(), yellows.end(), '\n'), yellows.end());

        cout << "Greens: ";
        cin >> greens;
        greens.erase(remove(greens.begin(), greens.end(), '\n'), greens.end());

        cout << "\n\n";

        sorted = filter_words(sorted, greys, yellows, greens);

        cout << "SUGGESTED WORDS:" << endl;
        vector<pair<string, int>>::iterator it = sorted.begin();
        for (j=0; j<5; j++) {
            if (it == sorted.end()) { continue; }
            cout << it->first << ": " << it->second << endl;
            it++;
        }

        cout << "\n\n";
    }
    

    return 0;
}