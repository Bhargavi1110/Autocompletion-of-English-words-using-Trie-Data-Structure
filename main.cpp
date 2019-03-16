//
//  main.cpp
//  WordComplete
//
//  Created by Saroopa on 3/15/19.
//  Copyright © 2019 Saroopa-Bhargavi. All rights reserved.
//

#define SIZE 26

#include <iostream>
#include <fstream>
//#include <string>
#include <cstdio>

using namespace std;

struct TrieNode {
    char alpha;
    bool isEndOfWord;
    TrieNode* children[SIZE];
};
struct TrieNode* root;


void initializeRoot() {
    root = new TrieNode;
    root->alpha = 'q';
    root->isEndOfWord = true;
    
    for (int i=0 ; i<SIZE ; i++) {
        root->children[i] = 0;
    }
}


void insertWord(const string& word) {
    TrieNode* p = root;
    TrieNode* q = 0;
    short letter_count = 1;
    
checkForLetter:
    short child_count = 0;
    while (p->children[child_count] != 0) {
        child_count++;
    
        if (p->children[child_count]->alpha == word[letter_count]) {
            q = p;
            p = p->children[child_count];
            letter_count++;
            break;
        }
    }
    
    if (p->children[child_count] != 0)
        goto checkForLetter;
    
    else {
        while (word[letter_count+1] != '\0') {
            TrieNode* Node = new TrieNode;
            Node->alpha = word[letter_count];
            
            cout << Node->alpha;
            
            if (word[letter_count+1] == '\0')
                Node->isEndOfWord = true;
            else
                Node->isEndOfWord = false;
            
            short i=0;

            for (i=0 ; q != 0 and q->children[i] != 0 ; i++);
            if (q != 0)
                q->children[i] = Node;

            
            for (i=0 ; i<SIZE ; i++) {
                Node->children[i] = 0;
            }
      
            q = Node;
            letter_count++;
        }

        cout << endl;
        
    }
}

bool isLeafNode(struct TrieNode* root)
{
    return root->isEndOfWord != false;
}

// function to display the content of Trie
void display(struct TrieNode* root, string str, short count)
{
    // If node is leaf node, it indiicates end
    // of string, so a null charcter is added
    // and string is displayed
    if (isLeafNode(root))
    {
        str[count] = '\0';
        cout << str << endl;
    }

    int i;
    for (i = 0; i < SIZE; i++)
    {
        // if NON NULL child is found
        // add parent key to str and
        // call the display function recursively
        // for child node
        if (root->children[i])
        {
            str[count] = i + 'a';
            display(root->children[i], str, count+1);
        }
    }
}


void openFile() {
    ifstream wordFile;
    wordFile.open("/Users/saroopa/Desktop/Data Structures/Package/testWords.txt");
    if (!wordFile) {
        cout << "Couldn't open file." << endl;
    }
    else {
        short i = 0;
        string word;
        while (!wordFile.eof()) {
            getline(wordFile, word);
            cout << word << endl;
            insertWord(word);
            i++;
        }
    }
}


int main() {
    initializeRoot();
    openFile();
    

//    short count= 0;
//    string str;
//    display(root, str, count);

    
    
    return 0;
}
