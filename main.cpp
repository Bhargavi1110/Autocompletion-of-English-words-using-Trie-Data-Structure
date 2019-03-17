//
//  main.cpp
//  WordComplete
//
//  Created by Saroopa on 3/15/19.
//  Copyright © 2019 Saroopa-Bhargavi. All rights reserved.
//

#ifndef SIZE
#define SIZE 26
#endif

#include <iostream>
#include <fstream>
#include <stdlib.h>


struct TrieNode {
	char alpha;
	bool isEndOfWord;
	TrieNode* children[SIZE];
};
struct TrieNode* root;


void initializeRoot() {
    root = new TrieNode;
    root->alpha = 'q';
    root->isEndOfWord = false;
    
    for (int i=0 ; i<SIZE ; i++) {
        root->children[i] = 0;
    }
}


void insertWord(const std::string& word) {
    TrieNode* p = root;
    
    for (short i=1 ; i<word.length() ; i++) {
        
        short index = word[i] - 'a';
        if (p->children[index] == 0) {
            
            TrieNode* Node = new TrieNode;
            Node->isEndOfWord = false;
            Node->alpha = word[i];
            std::cout << word[i];
            
            for (short i=0 ; i<SIZE; i++) {
                Node->children[i] = 0;
            }

            p->children[index] = Node;
        }
        p = p->children[index];
    }
    
    p->isEndOfWord = true;
    std::cout << std::endl;
}


void display(TrieNode* root, char word_suggestion[], short count) {
    if (root->isEndOfWord) {
        word_suggestion[count] = '\0';
        std::cout << word_suggestion << std::endl;
    }

    for (short i=0 ; i<SIZE ; i++) {
        if (root->children[i] != 0) {
            word_suggestion[count] = root->alpha;
            display(root->children[i], word_suggestion, count+1);
        }
    }

}


void openFile() {
	std::ifstream wordFile;
    wordFile.open("/Users/saroopa/Desktop/Data Structures/Package/qWords.txt");
    if (!wordFile) {
        std::cout << "Couldn't open file." << std::endl;
    }
    else {
        std::string word;
        while (!wordFile.eof()) {
            getline(wordFile, word);
            insertWord(word);
        }
    }
}


int main() {
    initializeRoot();
    openFile();
	
    char word[20];
    display(root, word, 0);

    return 0;
}
