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
struct TrieNode* root;


void initializeRoot() {
	root = new TrieNode;
	root->alpha = 'q';
	root->isEndOfWord = false;
	
	for (int i=0 ; i<SIZE ; i++) {
		root->children[i] = 0;
	}
}

void insertWord(const std::string &word) {
	TrieNode *p = root;
//	cout<<"\n";
	for (short i=1 ; i<word.length() ; i++){
		short j;
		for (j=0 ; j<SIZE && (p->children[j] != 0) ;) {
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
//		cout<< p->alpha;
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
	strcpy(word_suggestion, word);
	int i = 0;
	while(word[i+1] != '\0'){
		if(word[i] == p->alpha)
			for(short j=0 ; j<SIZE ; j++)
				if(word[i+1] == (p->children[j])->alpha) {
					p = p->children[j];
					break;
				}
		i++;
			//std::cout<<i;
	}
//	cout<<word_suggestion;
	display(p, word_suggestion, i);
}
void openFile() {
	ifstream wordFile;
	wordFile.open("/Users/saroopa/Desktop/Data Structures/Package/qWords.txt");
	if (!wordFile) {
		cout << "Couldn't open file." << endl;
	}
	else {
		string word;
		while (!wordFile.eof()) {
			getline(wordFile, word);
			insertWord(word);
		}
	}
}


int main() {
	initializeRoot();
	openFile();
        
//	char word[20];
//	display(root, word, 0);
	
        char phrase[20];
	cout<<"Enter word beginning:  ";
        cin>>phrase;
	traverseTrie(phrase);        

	return 0;
}
