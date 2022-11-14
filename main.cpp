#include <iostream>
#include <fstream>
#include "queue.h"
#include "linearlist.h"

using namespace std;


const int NWORDS = 5757;

struct WordInfo {
    char word[6]{};
    WordInfo* ptr = nullptr;
    LinearList<WordInfo*> adjList;
};



int hamming(const char s1[], const char s2[]) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (s1[i] != s2[i]) {
            count++;
        }
    }
    return count;
}

void generateAdjacency(WordInfo words[]) {
    for (int i = 0; i < NWORDS; i++) {
        for (int j = i + 1; j < NWORDS; j++) {
            if (hamming(words[i].word, words[j].word) == 1) {
                words[i].adjList.insert(words[i].adjList.size(), &words[j]);
                words[j].adjList.insert(words[j].adjList.size(), &words[i]);
            }
        }
    }
}

int search(WordInfo wordList[], const string& word) {
    for (int i = 0; i < NWORDS; i++) {
        if (word == wordList[i].word) {
            return i;
        }
    }
    return -1;
}

bool isInList(WordInfo words[], const string& word) {
    for (int i = 0; i < NWORDS; i++) {
        if (word == words[i].word) {
            return true;
        }
    }
    return false;
}

void genLadder(WordInfo* w1, WordInfo* w2) {
    Queue<WordInfo*> Q;
    WordInfo* w;

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
    WordInfo words[NWORDS];
    string word1, word2;
    WordInfo* w1;
    WordInfo* w2;


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

    generateAdjacency(words);


    // read two words from keyboard
    cout << "Please enter two 5-letter words:";
    cin >> word1 >> word2;

    // Check to make sure the words are 5 letters in length
    if (word1.length() != 5 || word2.length() != 5) {
        throw std::invalid_argument("One of more of the inputted words are invalid.");
    }

    try {
        if (!isInList(words, word1)) throw std::domain_error("Error: First word does not exist in list.");
    }
    catch (std::domain_error& e) {
        cout << e.what() << endl;
        return 0;
    }
    try {
        if (!isInList(words, word2)) throw std::domain_error("Error: Second word does not exist in list.");
    }
    catch (std::domain_error& e) {
        cout << e.what() << endl;
        return 0;
    }


    // find both words in word list
    w1 = &words[search(words, word1)];
    w2 = &words[search(words, word2)];

    genLadder(w1, w2);

    return 0;
}