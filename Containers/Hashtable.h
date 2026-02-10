#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>

using namespace std;

template <typename K, typename V>
class HashTable
{
private:
    struct HashNode
    {
        K key;
        V value;
        HashNode* next;

        HashNode(const K& key, const V& value)
        {
            this->key = key;
            this->value = value;
            next = nullptr;
        }
    };

    HashNode** table;
    int capacity;
    int size;

    int hashFunction(const K& key) const;

public:
    HashTable(int capacity = 101);
    ~HashTable();

    void insert(const K& key, const V& value);
    V search(const K& key) const;
    bool remove(const K& key);

    bool isEmpty() const;
    int getSize() const;

    void clear();
};
#endif