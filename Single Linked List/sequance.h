#include <iostream>
#include <vector>

using namespace std;
#ifndef SEQUANCE_H
#define SEQUANCE_H



template <typename Key, typename Info>
class Sequence{

private:
    struct element{
    Key key;
    Info info;
    element* next;
    };
    element* head;
    int nr;



public:
    Sequence(){ //constructor
    this->head = NULL;
    this->nr = 0;
    };
    Sequence(const Sequence &x){ //copy constructor
        head = NULL;
        nr = 0;
        *this = x;
    };
    ~Sequence(){//deconstructor
        this->clearSequence();
    };

    bool operator==(const Sequence &x)const{
        if(this->isEmpty() && x.isEmpty())
            return true;
        if(this->nr != x.nr)
            return false;

        element* xtr = x.head;
        element* ptr = this->head;
        while(xtr != NULL && ptr != NULL){
            if(ptr->key != xtr->key || ptr->info != xtr->info)
                return false;
            xtr = xtr->next;
            ptr = ptr->next;
        }
        return true;

    };
    bool operator!=(const Sequence &x)const{
        return !(*this == x);
    };
    Sequence operator+(const Sequence &x)const{//it adds to the first object elements from the other if there is no the same keys
        Sequence<Key, Info> temp = *this;

        element* ptr = x.head;
        while(ptr != NULL){
            temp.addAtTheEnd(*ptr);
            ptr = ptr->next;
        }
        return temp;
    }
    Sequence &operator=(const Sequence &x){
        if(*this == x)
            return *this;

        this->clearSequence();
        if(x.isEmpty())
            return *this;

        element* xtr =x.head;
        element* ptr;
        element* etr = NULL;
        while(xtr != NULL){
            ptr = new element();
            ptr->key = xtr->key;
            ptr->info = xtr->info;
            ptr->next = NULL;
            if(etr == NULL)
                this->head = ptr;
            else
                etr->next = ptr;

            xtr = xtr->next;
            etr = ptr;
        }
        this->nr = x.nr;

        return *this;
    };

    friend ostream& operator<<(ostream& os, const Sequence &x){ //display every element key:info in next line
        element* ptr = x.head;
        while(ptr != NULL){
        cout<<ptr->key<<":"<<ptr->info<<"\n";
        ptr = ptr->next;
        }
        cout<<"\n";
        return os;
    };

    bool isEmpty()const{ //check if object posses elements
    if(this->head == NULL)
        return true;
    else
        return false;
    };
    void clearSequence(){ // deletes all elements
    if(this->isEmpty())
        return;

    while(head != NULL){
        element* ptr = head;
        head = head->next;
        delete ptr;
    }
    this->nr = 0;
    };

    bool keyExists(Key key)const{ // check if in object is element with given key
        if(this->isEmpty())
            return false;
        element* ptr = this->head;
        while(ptr != NULL){
            if(ptr->key == key)
                return true;
            ptr = ptr->next;
        }
        return false;
    };
    bool infoExists(Info info)const{ // check if in object is element with given info
        if(this->isEmpty())
            return false;

        element* ptr = this->head;
        while(ptr != NULL){
            if(ptr->info == info)
                return true;
            ptr = ptr->next;
        }
        return false;
    }
    bool addElement(Key key, Info info){ // adds at the beginning  of list if possible new element with given data
    if(this->keyExists(key))
        return false;

    element* ptr = new element();
    ptr->key = key;
    ptr->info = info;
    ptr->next = head;
    head = ptr;
    this->nr++;
    return true;
};
    bool addElement(const element &x){  // adds at the beginning  of list if possible new element with given data
    return addElement(x.key, x.info);
    };
    bool addAtTheEnd(Key key, Info info){   // adds at the end  of list if possible new element with given data
        if(this->keyExists(key))
            return false;

        if(this->isEmpty())
            return this->addElement(key, info);

        element *ptr = this->head;
        while(ptr->next != NULL)
            ptr = ptr-> next;

        element *etr = new element();
        etr->key = key;
        etr->info = info;
        etr->next = NULL;
        ptr->next = etr;
        this->nr++;
        return true;
    }
    bool addAtTheEnd(const element &x){ // adds at the end  of list if possible new element with given data
        return this->addAtTheEnd(x.key, x.info);
    };
    bool addAfterKey(Key k, Key key, Info info){    // adds after element with given key if possible new element with given data
        if(this->keyExists(key))
            return false;
        if(!this->keyExists(k))
            return addAtTheEnd(key, info);

        element* ptr = this->head;
        while(ptr->key != k)
            ptr = ptr->next;

        element* etr = new element();
        etr->key = key;
        etr->info = info;
        etr->next = ptr->next;
        ptr->next = etr;
        this->nr++;
        return true;
    };
    bool addAfterKey(Key k,const element &x){   // adds after element with given key if possible new element with given data
       return addAfterKey(k, x.key, x.info);
    };
    bool addVector(const vector<element> &x){  //adds elements contained in vector at the beginning of list if possible
        bool b = false;
        for(int i=0; i<x.size(); i++)
            if(this->addElement(x[i])){
                b = true;
            }
            return b;

    };
    bool addVectorAtTheEnd(const vector<element> &x){   //adds elements contained in vector at the end of list if possible
        bool b = false;
        for(unsigned int i=0; i<x.size(); i++)
            if(this->addAtTheEnd(x[i])){
                b = true;
            }
        return b;

    };
    bool addVectorAfterKey(Key k, const vector<element> &x){  //adds elements contained in vector after element with given key if possible
        bool b = false;
        if(this->addAfterKey(k,x[0])){
                b = true;
            }
        for(int i=1; i<x.size(); i++)
            if(this->addAfterKey(x[i-1].key ,x[i])){
                b = true;
            }
        return b;

    };
    bool getAddVectorAtTheEnd(const Sequence &x,int b,int n){ //adds elements taken from another object contained in vector at the end of list if possible
       return addVectorAtTheEnd(x.getElementsFromPlace(b,n));
    }

    bool deleteElement(Key key){ //deletes element with given key
        if(this->isEmpty())
            return false;
        element* ptr = this->head;
        if(head->key == key){
            head = head->next;
            delete ptr;
            this->nr--;
            return true;
        }

        while(ptr->next != NULL){
            if(ptr->next->key == key){
                element* etr = ptr->next;
                ptr->next = etr->next;
                delete etr;
                this->nr--;
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    };
    bool deleteAllByInfo(Info info){ // deletes elements with given info
        if(this->isEmpty())
            return false;
        if(!this->infoExists(info))
                return false;

        while(head->info == info){
       /* element *ptr = this->head;
        head = head->next;
        delete ptr;
        this->nr--;*/
        this->deleteElement(head->key);
        if(this->isEmpty())
            return true;
        }

        element *ptr = this->head;
        while(ptr->next != NULL){
            if(ptr->next->info == info){
                element *etr = ptr->next;
                ptr->next = etr->next;
                delete etr;
                this->nr--;
                }else
                ptr = ptr->next;

        }

    return true;
    };
    bool deleteFromKey(Key key, int n){ // deletes at most n elements in line beginning from key to n-th element after key or to the and of list
        if(this->isEmpty())
            return false;

     //   if(!this->keyExists(key))
       //     return false;
        if(head->key == key){
            int i=n;
            while(i && head != NULL){
                this->deleteElement(head->key);
                i--;
            }

          return true;
        }

        element *ptr = this->head;
        while(ptr->next != NULL){
            if(ptr->next->key == key){
                int i = n;
                while(i && ptr->next != NULL){
                element *etr = ptr->next;
                ptr->next = etr->next;
                delete etr;
                this->nr--;
                i--;
                }
                return true;
                }else
                ptr = ptr->next;

        }
        return false;


        };

    vector<Key> getAllKey()const{ //returns all keys from the list
        vector<Key> temp;
        element *ptr = this->head;
        while(ptr != NULL){
            temp.push_back(ptr->key);
            ptr = ptr->next;
        }
        return temp;
    }
    vector<Info> getAllInfo()const{// returns all info from the list
        vector<Info> temp;
        element *ptr = this->head;
        while(ptr != NULL){
            temp.push_back(ptr->info);
            ptr = ptr->next;
        }
        return temp;
    }
    vector<Key> getByInfo(Info info)const{ // returns all keys of elements that contains given info
        vector<Key> temp;
        element *ptr = this->head;
        while(ptr != NULL){
            if(ptr->info == info)
                temp.push_back(ptr->key);
                ptr = ptr->next;
        }
        return temp;
    }
    vector<element> getAllElements()const{ // returns all elements from the list
    vector<element> temp;
        element *ptr = this->head;
        while(ptr != NULL){
            temp.push_back(*ptr);
            ptr = ptr->next;
        }
        return temp;
    }
    vector<element> getElementsFromKey(Key key, int n)const{ // returns at most n elements in line beginning from key to n-th element after key or to the and of list
        vector<element> temp;

        if(!this->keyExists(key))
            return temp;

        element *ptr = this->head;
        int i = n;
        while(ptr->key != key)
            ptr = ptr->next;

        while(ptr != NULL && i>0){
            temp.push_back(ptr);
            ptr = ptr->next;
            i--;
        }
        return temp;
    };
    vector<element> getElementsFromPlace(int b, int n)const{  //b position of begin in counting from 0, n number of elements to copy
        vector<element> temp;

        if(b >= this->nr)
            return temp;

        element *ptr = this->head;
        int i = n;

        for(int j = b; j>0; j--)
                ptr = ptr->next;

        while(ptr != NULL && i>0){
            temp.push_back(*ptr);
            ptr = ptr->next;
            i--;
        }
        return temp;
    };


    void setNr(int n){ //change number of of elements in the list
    this->nr = n;
    };

    int getNr()const{ // returns number of of elements in the list
    return this->nr;
    };
};

template <typename Key, typename Info>
int split(const Sequence<Key,Info>& source, int start, Sequence<Key,Info>& result1, int step1, Sequence<Key,Info>& result2, int step2){// use methods from the class, not optimal
    result1.clearSequence();
    result2.clearSequence();


    if(start >= source.getNr())
        return 0;

    if(step1 < 0)
        step1 = 0;

    if(step2 < 0)
        step2 = 0;

    if(step1 == 0 && step2 == 0)
        return 0;



    int i = start;
    while(i < source.getNr()){
        result1.getAddVectorAtTheEnd(source, i, step1);
        i+=step1;

        if(i >= source.getNr()){
            return source.getNr()-start;
        }
        result2.getAddVectorAtTheEnd(source, i, step2);
        i+=step2;

    }
    return source.getNr()-start;
}

template <typename Key, typename Info>
    struct element{
    Key key;
    Info info;
    element* next;
    };



#endif // SEQUANCE
