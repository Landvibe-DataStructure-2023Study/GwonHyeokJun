#include <iostream>
#include <string>

using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

struct Entry{
    int key;
    string value;
    int valid;

    Entry(){
        key = 0;
        value = "";
        valid = NOITEM;
    }
    Entry(int key, string value){
        this->key = key;
        this->value = value;
        valid = ISITEM;
    }

    void erase(){
        valid = AVAILABLE;
    }
};

class HashTable{
public:
    Entry* table;
    int maxSize;
    int divisor;
    HashTable(int maxSize){
        this->maxSize = maxSize;
        table = new Entry[maxSize];
        divisor = 0;
    }
    HashTable(int maxSize, int divisor){
        this->maxSize = maxSize;
        this->divisor = divisor;
        table = new Entry[maxSize];
    }
    int LinearHash(int key){
        return key % maxSize;
    }
    int DoubleHash(int key){
        return divisor - (key % divisor);
    }

    void put(int key, string value){
        int index = LinearHash(key);
        int probing = 1;

        if(table[index].valid == ISITEM && probing <= maxSize){
            if(divisor == 0){ // ´ÜÀÏÇØ½Ì
                index = LinearHash(++index);
            } else { // ÀÌÁßÇØ½Ì
                index = LinearHash(++index);
            }
            probing++;
        }
        if(probing > maxSize){
            return;
        }
        table[index] = Entry(key, value);
    }
};