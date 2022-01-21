#include <iostream>

using namespace std;

// We are using an array of linked lists that we connect to via hashes that we obtain from the hash function using calculating our key modulo 10 to obtain the position. Our hash function makes sure that as we increase the number of elements they will always fit within our array of linkedd lists which is the hash table. When there is a collision we simply add an element to the linked list placed where the hash table has a collision. 
// Linked List node

class Node{

  public:
	  int data;
	  Node* next;
};
// Hash Table
class HashTable{

  public:
    Node** HT;
    HashTable();
    int hash(int key);
    void Insert(int key);
    int Search(int key);
    ~HashTable();
};

HashTable::HashTable() {
	HT = new Node* [10];
	for (int i=0; i<10; i++){
		HT[i] = nullptr;
	}
}

int HashTable::hash(int key) {
	return key % 10;
}

void HashTable::Insert(int key) {
	int hIdx = hash(key);
	Node* t = new Node;
	t->data = key;
	t->next = nullptr;
	// Case: No nodes in the linked list
	if (HT[hIdx] == nullptr){
		HT[hIdx] = t;
	} else {
		Node* p = HT[hIdx];
		Node *q=HT[hIdx];
		// Traverse to find insert position
		while (p && p->data < key){
			q=p;
			p = p->next;
		}
		// Case: insert position is first
		if (q == HT[hIdx]){
			t->next = HT[hIdx];
			HT[hIdx] = t;
		} else {
			t->next = q->next;
			q->next = t;
		}
	}
}

int HashTable::Search(int key) {
	int hIdx = hash(key);
	Node* p = HT[hIdx];
	while (p){
		if (p->data == key){
			return p->data;
		}
		p = p->next;
	}
	return -1;
}

HashTable::~HashTable() {
	for (int i=0; i<10; i++){
		Node* p = HT[i];
		while (HT[i]){
			HT[i] = HT[i]->next;
			delete p;
			p = HT[i];
		}
	}
	delete [] HT;
}

int main() {
	int A[] = {16, 12, 25, 39, 6, 122, 5, 68, 75};
	int n = sizeof(A)/sizeof(A[0]);
	HashTable H;
	for (int i=0; i<n; i++){
		H.Insert(A[i]);
	}
	cout << "Successful Search" << endl;
	int key = 6;
	int value = H.Search(key);
	cout << "Key: " << key << ", Value: " << value << endl;
	cout << "Unsuccessful Search" << endl;
	key = 95;
	value = H.Search(key);
	cout << "Key: " << key << ", Value: " << value << endl;

	return 0;
}
