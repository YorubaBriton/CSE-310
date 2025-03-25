#include "hash.h"
#include <iostream>
#include <string>
#include <cmath>


using namespace std;

Node::Node(string t) : token(t), next(nullptr) {}

HashTable::HashTable (int k) : numberSlots(k) {
    table = new Node*[numberSlots];
    for (int i = 0; i < numberSlots; i++) {
        table[i] = nullptr;
        }
    }
    HashTable::~HashTable() {
        for(int i = 0; i < numberSlots; i++) {
            Node* currentNode = table[i];
            while(currentNode) {  
                Node* tempNode = currentNode;
                currentNode = currentNode->next;
                delete tempNode;
            }
        }
        delete[] table;
    }

    int HashTable::hash_function(const string& token) {
        unsigned long hash = 0;
        int prime = 31;
        for (char ch : token) {
            hash = (hash * prime + ch) % numberSlots;
        }
        return hash;
    }

    void HashTable::insert(const string& token) {
        int index = hash_function(token);
        Node* newNode = new Node(token);
        newNode->next = table[index];
        table[index] = newNode;
    }

    void HashTable::printFirst5Slots() {
        cout << "==== Printing the contents contained in the first 5 slots ====" << endl;
        for (int i = 0; i < min(5, numberSlots); i++) {
            cout << "Slot " << i << ": ";
            Node* currentNode = table[i];
            while (currentNode) {
                cout << currentNode->token << " ";
                currentNode = currentNode->next;
            }
            cout << endl;
        }
    }

    void HashTable::printSlotLengths() {
        cout << "==== Print the length of each slot ====" << endl;
        for (int i = 0; i < numberSlots; i++) {
            int count = 0;
            Node* currentNode = table[i];
            while (currentNode) {
                count++;
                currentNode = currentNode->next;
            }
            cout << "Slot " << i << ": " << count << endl;
        }
    }

    double HashTable::computeStdDevelopment() {
        double mean = 0;
        double variance = 0;
        int* slotLengths = new int[numberSlots];
        for (int i = 0; i < numberSlots; i++) {
            int count = 0;
            Node* currentNode = table[i];
            while (currentNode) {
                count++;
                currentNode = currentNode->next;
            }
            slotLengths[i] = count;
            mean += count;
        }
        mean /= numberSlots;
        for (int i = 0; i < numberSlots; i++) {
            variance += (slotLengths[i] - mean) * (slotLengths[i] - mean);
        }
        variance /= numberSlots;
        delete[] slotLengths;
        cout << "==== Standard deviation of the slot lengths ====" << endl;
        cout << sqrt(variance) << endl;
        return sqrt(variance);
    }