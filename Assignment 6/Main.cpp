#include<list>
#include<iostream>
#include<iterator>
#include<utility>
#include<string>
#include<cmath>
using namespace std;

int dataSize = 0;
int hashSize = 1;

pair<string, char>* codePair = new pair<string, char>[0];
list<char>* hashTab = new list<char>[hashSize];

//Adds specified element and hash code to the codePair array
void addElement(string tempStr, char tempChar) {
	pair<string, char>* addPair = new pair<string, char>[dataSize + 1];

	for (int i = 0; i < dataSize; i++) {
		addPair[i] = codePair[i];
	}

	addPair[dataSize].first = tempStr;
	addPair[dataSize].second = tempChar;

	codePair = addPair;
	dataSize += 1;
}

//Removes specified element from the codePair array
void removeElement(string tempStr, char tempChar) {
	pair<string, char>* removePair = new pair<string, char>[dataSize - 1];
	int index = -1;

	for (int i = 0; i < dataSize; i++) {
		if (codePair[i].first == tempStr && codePair[i].second == tempChar) {
			index = i;
		}
	}

	if (index != -1) {
		//removes element from array
		for (int i = index; i < dataSize - 1; i++) {
			codePair[i] = codePair[i + 1];
		}

		for (int i = 0; i < dataSize - 1; i++) {
			removePair[i] = codePair[i];
		}

		dataSize -= 1;
	}
	else {
		cout << "Sorry, element not found..." << endl;
	}
}

//Computes the hash code and inserts it into the corresponding indexes
void computeHash(int size) {
	//changed this to greater or equal so you could rehash if you made changes to the codePair
	if (size >= hashSize) {
		hashSize = size;
		int index;
		delete[] hashTab;
		hashTab = new list<char>[hashSize];

		for (int i = 0; i < dataSize; i++) {
			index = 0;
			for (int x = 2; x >= 0; x--) {
				index += ((int)((codePair[i].first)[x]) * (int)pow(31, x));
			}
			index %= hashSize;
			hashTab[index].push_back(codePair[i].second);
		}
	}
}

//Traverses over the hash table and prints each element
void traverseHash() {
	for (int i = 0; i < hashSize; i++) {
		cout << i << ": ";
		list<char>::iterator b = hashTab[i].begin();
		list<char>::iterator e = hashTab[i].end();
		for (; b != e; b++) {
			cout << *b << "->";
		}
		cout << "NULL" << endl;
	}
}

int main() {

	addElement("abc", 'Y');
	addElement("r98", 'A');
	addElement("11y", 'L');
	addElement("q54", 'G');
	addElement("p88", 'O');
	addElement("bb1", 'R');
	addElement("www", 'I');
	addElement("nbn", 'T');
	addElement("pop", 'H');
	addElement("87u", 'M');
	addElement("ede", 'S');
	addElement("kk8", 'A');
	addElement("711", 'L');
	addElement("mom", 'G');
	addElement("28m", 'O');
	computeHash(15);
	traverseHash();

	cout << endl << endl << endl;

	removeElement("p88", 'O');
	computeHash(15);
	traverseHash();

	cout << endl << endl << endl;

	addElement("abc", 'Y');
	computeHash(15);
	traverseHash();

	delete[] hashTab;
	delete[] codePair;
	return 0;
}