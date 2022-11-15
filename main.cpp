#include <iostream>
#include <fstream>
#include "queue.h"
#include "linearlist.h"

using namespace std;

const int NWORDS = 5757;

struct WordData {
    char word[6]{};
    WordData *ptr = nullptr;
    LinearList<WordData*> adjList;
};



int hamming(const char *s1, const char *s2) {             // Checks to see how far apart words are from each other in similar letters
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (s1[i] != s2[i]) {
            count++;
        }
    }
    return count;
}

void generateAdjacency(WordData words[]) {
    for (int i = 0; i < NWORDS; i++) {
        for (int j = i + 1; j < NWORDS; j++) {
            if (hamming(words[i].word, words[j].word) == 1) {
                words[i].adjList.insert(words[i].adjList.size(), &words[j]);
                words[j].adjList.insert(words[j].adjList.size(), &words[i]);
            }
        }
    }
}

int wordSearch(WordData *wordList, const string& word) {                       // Searches for word in list
    for (int i = 0; i < NWORDS; i++) {
        if (word == wordList[i].word) {
            return i;                                                       // if word found, return the index of the word.
        }
    }
    throw std::domain_error("Word not found in list.");
}

bool isInList(WordData *words, const string& word) {                       // Function checks to see if word exists in list
    for (int i = 0; i < NWORDS; i++) {
        if (word == words[i].word) {
            return true;                                                    // if so, return true
        }
    }
    return false;                                                           // if not, return false
}

void genLadder(WordData* w1, WordData* w2) {
    Queue<WordData*> Q;
    WordData* w;

    Q.enqueue(w2);

    while (!Q.isEmpty()) {
        w = Q.dequeue();
        for (int i = 0; i < w->adjList.size(); i++) {
            if (w->adjList[i]->ptr == nullptr && w->adjList[i]->word != w2->word) {
                w->adjList[i]->ptr = w;
                Q.enqueue(w->adjList[i]);
            }
        }
    }

    if (w1->ptr != nullptr) {
        cout << "Ladder:" << endl;
        cout << w1->word << endl;
        w = w1->ptr;

        while (w != nullptr) {
            cout << w->word << endl;
            w = w->ptr;
        }
    }
    else {
        cout << "No ladder exists";
    }
}


int main() {
    WordData words[NWORDS];
    string word1, word2;
    WordData* w1;
    WordData* w2;

    // Read words from text file and insert them into the words list
    ifstream inFile;
    inFile.open("sgb-words.txt");
    if (!inFile)
    {
        cout << "The file has failed to open" << endl;
    }
    else
    {
        int i = 0;
        while (!inFile.eof())
        {
            inFile >> words[i].word;
            i++;
        }

    }

    generateAdjacency(words);   // Generates adjacency lists for each word in word list


    // read two words from keyboard
    cout << "Please enter two 5-letter words:";
    cin >> word1 >> word2;

    // Check to make sure the words are 5 letters in length
    try {
        if (word1.length() != 5 || word2.length() != 5) throw std::invalid_argument("One of more of the inputted words are invalid. Make sure the words entered are 5 letters in length.");

    } catch (std::invalid_argument &e) {
        cout << "Error: " << e.what() << endl;
        return 0;
    }

    // Check to make sure inputted words exist in the list.
    try {
        if (!isInList(words, word1)) throw std::domain_error("First word does not exist in list.");
    }
    catch (std::domain_error &e) {
        cout << "Error: " << e.what() << endl;
        return 0;
    }
    try {
        if (!isInList(words, word2)) throw std::domain_error("Second word does not exist in list.");
    }
    catch (std::domain_error& e) {
        cout << "Error: " << e.what() << endl;
        return 0;
    }

    // find both words in word list and return the index of the word
    w1 = &words[wordSearch(words, word1)];                  // assign words[index] to w1
    w2 = &words[wordSearch(words, word2)];                  // assign words[index] to w2

    genLadder(w1, w2);                                               // Call final function to generate word ladder.

    return 0;
}