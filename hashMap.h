#ifndef HASHMAP_
#define HASHMAP_

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <list>

using namespace::std;

template<class T>
class hashMap {
public:
    hashMap();
    ~hashMap();
    void insert(T item);
    bool find(T item);
    int getSize() {return size;}
    bool isEmpty();
    int findHash(string word);
    int fCompares;
    int nfCompares;
private:
    const static int HASHSIZE = 150001;
    list<T> * hash;
    int size=0;
};

template <class T>
hashMap<T>::hashMap()
{
    hash = new list<T>[HASHSIZE];
}

template <class T>
hashMap<T>::~hashMap()
{
    delete [] hash;
}

template <class T>
void hashMap<T>::insert(T item)
{
    int key = findHash(item);
    hash[key].push_back(item);
    size++;
}

template <class T>
bool hashMap<T>::find(T item)
{
    string comp;
    bool found;
    int runningCompares=0;

    int key = findHash(item);
    
    typename list <T> :: iterator i;
    for (i = hash[key].begin(); i != hash[key].end(); i++) {
        comp = (string)*i;
        if (comp.compare(item)) {
            runningCompares++;
            fCompares += runningCompares;
            return true;
        }
        else {
            runningCompares++;
        }
    }
    nfCompares += runningCompares;
    return false;
}

template <class T>
bool hashMap<T>::isEmpty()
{
    if (size == 0) {
        return true;
    }
    else {
        return false;
    }
}

template <class T>
int hashMap<T>::findHash(string word)
{
    int position = 1;
    long int hash = word.length();
    for (int i=0; i < word.length(); i++) {
        hash += (int)word[i] * position;
        position++;
    }
    return hash%HASHSIZE;
}

#endif