#ifndef SIZE
#define SIZE 26
#endif

#include <iostream>
#include <fstream>
#include<string.h>
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
    root->isEndOfWord = false;

    for (int i=0 ; i<SIZE ; i++) {
        root->children[i] = 0;
    }
}


/*void insertWord(const std::string& word) {
    TrieNode* p = root;
    for (int i=1 ; i<word.length() ; i++) {
        short index = word[i] - 'a';//index = word[i] - 'a' + 1//
        if (p->children[index] == 0) {
            TrieNode* Node = new TrieNode;
            Node->isEndOfWord = false;
            Node->alpha = word[i];
            //std::cout << word[i];
            for (short i=0 ; i<SIZE; i++) {
                Node->children[i] = 0;
            }
            p->children[index] = Node;
        }
        p = p->children[index];
    }
    p->isEndOfWord = true;
    //std::cout << std::endl;
}*/

void insertWord(const std::string &word) {
    TrieNode *p = root;
    //cout<<"\n"<<p->alpha;
    for (short i=1 ; i<word.length() ; i++){
        short j;
        for (j=0 ; j<SIZE ; j++) {
            if (p->children[j] != 0) {
                if ((p->children[j])->alpha == word[i])
                    p = p->children[j];
                else
                        break;
                }
            }
            TrieNode* Node = new TrieNode;
            Node->isEndOfWord = false;
            Node->alpha = word[i];
            for (short k=0 ; k<SIZE; k++)
                Node->children[k] = 0;
            p->children[j] = Node;
            p = p->children[j];
           //cout<< p->alpha;
        }
        p->isEndOfWord = true;
}

void display(TrieNode* root, std::string word_suggestion, short count) {
        if (root->isEndOfWord) {
            //cout<<root->alpha<<endl;
            word_suggestion[count] = root->alpha;
            word_suggestion[count+1] = '\0';
            std::cout << word_suggestion << std::endl;
        }

        for (short i=0 ; i<SIZE ; i++) {
            if (root->children[i] != 0) {
                //cout<< root->alpha;
                word_suggestion[count] = root->alpha;
                display(root->children[i], word_suggestion, count+1);
            }
        }
}

/*void traverseTrie(std::string word){
    std::string word_suggestion;
    TrieNode *p = root;
    word_suggestion = word;
    int i = 0;
    while(word[i+1] != '\0'){
        if(word[i] == p->alpha)
            for(short j=0 ; j<SIZE ; j++)
                if(word[i+1] == (p->children[j])->alpha) {
                    p = p->children[j];
                    break;
                }
        i++;
        std::cout<<i;
    }
    std::cout<<word_suggestion;
    display(p, word_suggestion, i);
}*/
void openFile() {
        std::ifstream wordFile;
    wordFile.open("testWords.txt");
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

    //std::string phrase;
    //std::cout<<"Enter word beginning:  ";
    //std::cin>>phrase;
    char word[20];
    display(root, word, 0);
    //traverseTrie(phrase);
    return 0;
}
