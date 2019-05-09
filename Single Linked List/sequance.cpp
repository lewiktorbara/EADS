#include <iostream>
#include <stdio.h>

#include "sequance.h"

using namespace std;

/*template<typename Key, typename Info>
Sequence<Key,Info>::Sequence(){
    this->head = NULL;
    this->nr = 0;
}*/

/*template<typename Key, typename Info>
Sequence<Key,Info>::Sequence(const Sequance<Key,Info> &x){
    head = NULL;
    element* ptr = new element;
    ptr->key = key;
    ptr->info = info;
    this->addElement(*ptr);


}

template<typename Key, typename Info>
bool Sequence<Key, Info>::isEmpty(){
    if(this->head == NULL)
        return true;
    return false;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::clearSequence(){
    if(this->isEmpty())
        return;

    while(head != NULL){
        element* ptr = head;
        head = head->next;
        delete ptr;
    }
    this->nr = 0;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::elementExists(Key key){
    if(this->isEmpty())
        return false;

    element* ptr = head;
    while(ptr != NULL){
        if(ptr->key == key)
            return true;
        ptr = ptr->next;
    }
    return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::addElement(Key key, Info info){
    if(this->elementExists(key))
        return false;

    element* ptr = new element;
    ptr->key = key;
    ptr->info = info;
    ptr->next = head;
    head = ptr;
    this->nr++;
    return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::addElement(const element &x){
    return this->addElement(x.key, x.info);
}

/*template<typename Key, typename Info>
bool Sequence<Key, Info>::deleteElement(Key key){
    if(this.elemetExists(key) == false)
        return false;

    element* ptr = head;
    while(ptr->next->key != key)
            ptr = ptr-next;



}

template<typename Key, typename Info>
int Sequence<Key,Info>::getNr()

template<typename Key, typename Info>
void Sequence<Key,Info>::setNr(int n)
*/
