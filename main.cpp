#ifndef SIZE
#define SIZE 26
#endif

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct TrieNode {
	char alpha;
	bool isEndOfWord;
	TrieNode* children[SIZE];
};
TrieNode* root;

void initializeRoot() {
	root = new TrieNode;
	root->isEndOfWord = false;
	
	for (int i=0 ; i<SIZE ; i++) {
		root->children[i] = 0;
	}
}

	for (int i=0 ; i<SIZE ; i++) {
		root->children[i] = 0;
	}
}

void insertWord(const string &word) {
	TrieNode *p = root;
	for (short i=0 ; i<word.length() ; i++){
		short j;
		for (j=0 ; j<SIZE && (p->children[j] != 0) ; ) {
			if ((p->children[j])->alpha == word[i]) {
				p = p->children[j];
				j=0;
				i++;
			}
			else
				j++;
		}
		TrieNode* Node = new TrieNode;
		Node->isEndOfWord = false;
		Node->alpha = word[i];
		for (short k=0 ; k<SIZE; k++)
			Node->children[k] = 0;
		p->children[j] = Node;
		p = p->children[j];
	}
	p->isEndOfWord = true;
}


void display(TrieNode* root, char word_suggestion[], short counts) {
	if (root->isEndOfWord) {
			//cout<<root->alpha<<endl;
		word_suggestion[counts] = root->alpha;
		word_suggestion[counts+1] = '\0';
		cout << word_suggestion << endl;
	}
	for (short i=0 ; i<SIZE ; i++) {
		if (root->children[i] != 0) {
				//cout<< root->alpha;
			word_suggestion[counts] = root->alpha;
			display(root->children[i], word_suggestion, counts+1);
		}
	}
}

void traverseTrie(char word[]){
	char word_suggestion[20];
	TrieNode *p = root;
	TrieNode *prev = 0;
	int display_flag = 0;
	int i = 0;
	int flag = 0;

	while (word[i] != '\0') {
        prev = p;
        for (short j=0 ; j<SIZE ; j++) {
            if (p->children[j] != 0 && (p->children[j])->alpha == word[i]) {
                p = p->children[j];
            }
        }
        i++;
        //cout<<p->alpha<<endl;
        if(prev == p) {
            cout<<"No match found !"<<endl;
            flag = 1;
            break;
        }
	}

    if(flag == 0)
        display(p, word, --i);
}

bool openFile() {
	ifstream wordFile;
	wordFile.open("EnglishWords.txt");

}

void traverseTrie(char word[]){
	char word_suggestion[20];
	TrieNode *p = root;
	strcpy(word_suggestion, word);
	
	short j;
	for (j=0 ; j<SIZE && p->children[j]!=0 ; j++) {
		if (p->children[j]->alpha == word[0]) {
			p = p->children[j];
			break;
		}
	}
	
	if (j != SIZE) {
		int i = 0;
		while(word[i+1] != '\0'){
			if(word[i] == p->alpha)
				for(short j=0 ; j<SIZE ; j++)
					if(word[i+1] == (p->children[j])->alpha) {
						p = p->children[j];
						break;
					}
			i++;
		}
		display(p, word, i);
	}
	else {
		cout << "No word can be formed using the letters typed." << endl;
	}
}

bool openFile() {
	ifstream wordFile;
	wordFile.open("/Users/saroopa/Desktop/Data Structures/EnglishWords.txt");
	if (!wordFile) {
		cout << "Couldn't open file." << endl;
		return false;
	}
	else {
		string word;
		while (!wordFile.eof()) {
			getline(wordFile, word);
			insertWord(word);
		}
		return true;
	}
}


int main() {
	initializeRoot();
	if(openFile()) {
		char phrase[20];
		cout<<"Enter beginning letters of a word:  ";
		cin>>phrase;
		traverseTrie(phrase);
	}
	return 0;
}
