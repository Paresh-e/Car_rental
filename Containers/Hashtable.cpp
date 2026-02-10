#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP

#include "HashTable.h"


template <typename K, typename V>
int HashTable<K, V>::hashFunction(const K& key) const
{
    unsigned long hash = 0;
    for (char c : key)
        hash = (hash * 31 + c);

    return hash % capacity;
}

template <typename K, typename V>
HashTable<K, V>::HashTable(int capacity)
{
    this->capacity = capacity;
    size = 0;

    table = new HashNode*[capacity];
    for (int i = 0; i < capacity; i++)
        table[i] = nullptr;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    clear();
    delete[] table;
}

template <typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& value)
{
    int index = hashFunction(key);

    HashNode* head = table[index];
    HashNode* current = head;

   
    while (current != nullptr)
    {
        if (current->key == key)
        {
            current->value = value;
            return;
        }
        current = current->next;
    }

    
    HashNode* newNode = new HashNode(key, value);
    newNode->next = head;
    table[index] = newNode;

    size++;
}

template <typename K, typename V>
V HashTable<K, V>::search(const K& key) const
{
    int index = hashFunction(key);

    HashNode* current = table[index];

    while (current != nullptr)
    {
        if (current->key == key)
            return current->value;

        current = current->next;
    }

    return nullptr; 
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K& key)
{
    int index = hashFunction(key);

    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current != nullptr)
    {
        if (current->key == key)
        {
            if (prev == nullptr)
                table[index] = current->next;
            else
                prev->next = current->next;

            delete current;
            size--;
            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
    for (int i = 0; i < capacity; i++)
    {
        HashNode* current = table[i];

        while (current != nullptr)
        {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }

        table[i] = nullptr;
    }

    size = 0;
}

template <typename K, typename V>
bool HashTable<K, V>::isEmpty() const
{
    return size == 0;
}

template <typename K, typename V>
int HashTable<K, V>::getSize() const
{
    return size;
}

#endif