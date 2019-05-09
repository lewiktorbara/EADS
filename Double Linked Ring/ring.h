#include <iostream>
#include <vector>
#include <new>
#include <memory>
#include <stdlib.h>

using namespace std;
#ifndef RING_H
#define RING_H
//template<typename Key, typename Info>
//class Iterator;

//template<typename Key, typename Info>
//struct data;

template<typename Key, typename Info>
class Ring{
private:
struct Node{
Key key;
Info info;
Node* next;
Node* prev;
};

Node* any;
int nr;

public:

class Iterator{
private:
    friend class Ring;
    mutable Node* current;

    Iterator( Node *x ): current( x ) {};
public:
    struct data{
    Key &key;
    Info &info;
    };

    Iterator(): current( NULL ) {};

    Iterator( const Iterator &x ): current( x.current ) {};



    ~Iterator() = default;

    Iterator operator=( const Iterator &x )const
    {
			current = x.current;
			return *this;
    };
        data operator*(){
        data out{
            current->key,
            current->info
        };
        return out;
    }
    const data operator*()const{
        data out{
            current->key,
            current->info
        };
        return out;
     }

    bool operator==(const Iterator &x)const{
        if(current == x.current)
            return true;
        return false;
    }
    bool operator!=(const Iterator &x)const{
        return !(*this == x);
    }
    Iterator operator++()const{
        if(current != NULL)
        current = current->next;
        return *this;
    }
    Iterator operator++(int unused)const{
        Iterator temp(current);
        if(current != NULL)
        current = current->next;
        return temp;
    }
    Iterator operator--()const{
        if(current != NULL)
        current = current->prev;
        return *this;
    }
    Iterator operator--(int unused)const{
        Iterator temp(current);
        if(current != NULL)
        current = current->prev;
        return temp;
    }
    Iterator operator+=(int n)const{
        if(current != NULL)
            for(int i=0; i<n; i++)
                current = current->next;
        return *this;
    }
    Iterator operator-=(int n)const{
        if(current != NULL)
            for(int i=0; i<n; i++)
                current = current->prev;
        return *this;
    }



};
typedef const Iterator Const_Iterator;

Ring(){
    this->any = NULL;
    this->nr = 0;
}
Ring(const Ring &x){
    this->any = NULL;
    this->nr = 0;
    *this = x;
};
~Ring(){
   clearRing();
};

bool operator==(const Ring &x)const{
    if(x.any == NULL && this->any == NULL)
        return true;
    if(this->nr != x.nr)
        return false;

    Node* currn = this->any;
    Node* currp = this->any->prev;
    Node* tempn = x.any;
    Node* tempp = x.any->prev;
    do{
        if(currn->info != tempn->info || currn->key != tempn->key)
            return false;
        if(currp->info != tempp->info || currp->key != tempp->key)
            return false;

    currn = currn->next;
    tempn = tempn->next;
    currp = currp->prev;
    tempp = tempp->prev;
    }while(tempn->prev != tempp->next && tempn->prev != tempp  && currn->prev != currp->next && currn->prev != currp);

    return true;
}
bool operator!=(const Ring &x)const{
    return !(*this == x);
};
Ring operator+(const Ring &x)const{
    Ring newRing(*this);
    Ring addedRing(x);

    Node *addedEnd = addedRing.any->prev;
    Node *newEnd = newRing.any->prev;
    newRing.any->prev = addedEnd;
    addedRing.any->prev = newEnd;
    newEnd->next = addedRing.any;
    addedEnd->next = newRing.any;

    return newRing;

};
Ring &operator=(const Ring &x){
    if(*this == x)
        return *this;

    this->clearRing();
    if(x.isEmpty())
        return *this;

    Node* curr = x.any;
    do{
    this->addNode(curr->key, curr->info);
    curr = curr->next;
    }while(curr != x.any);
    return *this;
};


friend ostream& operator<<(ostream &os, const Ring &x){
    if(x.isEmpty())
        cout<<"Ring is empty"<<"\n";
    else{
        Node* curr = x.any;
        do{
        cout<<"["<<curr->key<<","<<curr->info<<"] -> ";
        curr = curr->next;
        }while(curr != x.any);
        cout<<"\n";
    }


    return os;
};

bool isEmpty()const{
    if(this->any == NULL)
        return true;
    return false;
};
void clearRing(){
    while(any != NULL)
        deleteBack();
};
int howManyKeyExist(Key key)const{//////
    if(isEmpty())
        return 0;
    int i = 0;
    Node *currn = this->any;
    Node *currp = this->any->prev;
    do{
        if(currn == currp){
            if(currn->key == key)
                i++;
        }else{
        if(currn->key == key)
            i++;
        if(currp->key == key)
            i++;
        }


        currn = currn->next;
        currp = currp->prev;
    }while(currn->prev != currp->next && currn->prev != currp);
    return i;
};
int howManyInfoExist(Info info)const{/////
    if(isEmpty())
        return 0;
    int i = 0;
    Node *currn = this->any;
    Node *currp = this->any->prev;
    do{
        if(currn == currp){
            if(currn->info == info)
                i++;
        }else{
        if(currn->info == info)
            i++;
        if(currp->info == info)
            i++;
        }


        currn = currn->next;
        currp = currp->prev;
    }while(currn->prev != currp->next && currn->prev != currp);
    return i;
};
bool iteratorExists(const Iterator &x)const{
    if(isEmpty() || x.current == NULL)
        return false;

    Node *currn = this->any;
    Node *currp = this->any->prev;
    do{

        if(currn == x.current)
            return true;
        if(currp == x.current)
            return true;

        currn = currn->next;
        currp = currp->prev;
    }while(currn->prev != currp->next && currn->prev != currp);
    return false;
};

bool addNode(Key key, Info info){
    if(this->isEmpty()){
        Node* temp = new Node;
        temp->info = info;
        temp->key = key;
        temp->next = temp;
        temp->prev = temp;
        any = temp;
        nr++;
        return true;
    }

    Node* temp = new Node;
    temp->key = key;
    temp->info = info;
    temp->prev = any->prev;
    temp->next = any;
    any->prev->next = temp;
    any->prev = temp;
    nr++;
    return true;


};
bool addNodeByIterator(const Iterator &x){
    if(x.current == NULL)
        return false;
    return addNode(x.current->key, x.current->info);
};
bool addNodeAfterKey(Key key, Info info, Key where, int repeat){
    if(repeat > howManyKeyExist(where) || isEmpty() || repeat < 1)
        return false;
    Node* curr = this->any;
    while(repeat){
        if(curr->key == where){
            if(--repeat)
                curr = curr->next;
        }else{
        curr = curr->next;
        }
    }

    Node* temp = new Node;
    temp->key = key;
    temp->info = info;
    temp->prev = curr;
    temp->next = curr->next;
    curr->next->prev = temp;
    curr->next = temp;
    nr++;
    return true;
};
bool addNodeBeforeKey(Key key, Info info, Key where, int repeat){
    if(repeat > howManyKeyExist(where) || isEmpty() || repeat < 1)
        return false;
    Node* curr = this->any;
    while(repeat){
        if(curr->key == where){
            if(--repeat)
                curr = curr->next;
        }else{
        curr = curr->next;
        }

    }

    Node* temp = new Node;
    temp->key = key;
    temp->info = info;
    temp->prev = curr->prev;
    temp->next = curr;
    curr->prev->next = temp;
    curr->prev = temp;
    nr++;
    return true;

};
bool addNodeAfterInfo(Key key, Info info, Info where, int repeat){
    if(repeat > howManyInfoExist(where) || isEmpty() || repeat < 1)
        return false;
    Node* curr = this->any;
    while(repeat){
        if(curr->info == where){
            if(--repeat)
                curr = curr->next;
        }else{
        curr = curr->next;
        }
    }

    Node* temp = new Node;
    temp->key = key;
    temp->info = info;
    temp->prev = curr;
    temp->next = curr->next;
    curr->next->prev = temp;
    curr->next = temp;
    nr++;
    return true;
};
bool addNodeBeforeInfo(Key key, Info info, Info where, int repeat){
    if(repeat > howManyInfoExist(where) || isEmpty() || repeat < 1)
        return false;
    Node* curr = this->any;
    while(repeat){
        if(curr->info == where){
            if(--repeat)
                curr = curr->next;
        }else{
        curr = curr->next;
        }
    }

    Node* temp = new Node;
    temp->key = key;
    temp->info = info;
    temp->prev = curr->prev;
    temp->next = curr;
    curr->prev->next = temp;
    curr->prev = temp;
    nr++;
    return true;
};
bool addVectorOfNodes(const vector<Key> &x, const vector<Info> &y){
    bool b = false;
    int s = (x.size() > y.size() ? y.size() : x.size());
    for(unsigned int i=0; i<s; i++){
        this->addNode(x[i], y[i]);
        b = true;
    }
    return b;
};

bool deleteFront(){
    if(isEmpty())
        return false;
    if(any->next == any){
        delete any;
        any = NULL;
        return true;
    }
    Node* temp = this->any;
    any->prev->next = any->next;
    any->next->prev = any->prev;
    any = any->next;
    delete temp;

    return true;
}
bool deleteBack(){
    if(isEmpty())
        return false;
    if(any->next == any){
        delete any;
        any = NULL;
        return true;
    }

    Node* temp = any->prev;
    any->prev = temp->prev;
    temp->prev->next = any;
    delete temp;
    return true;

}
bool deleteByKey(Key where, int repeat){
    if(repeat > howManyKeyExist(where) || isEmpty() || repeat <1)
        return false;
    if(where == any->key && repeat == 1){
        deleteFront();
        return true;
    }
    Node* curr = this->any;
    while(repeat){
        if(curr->key == where){
            if(--repeat)
                curr = curr->next;
        }else{
        curr = curr->next;
        }
    }
    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    delete curr;
    return true;


};
bool deleteByIterator(const Iterator &x){////////////////////////////
    if(!(iteratorExists(x)))
        return false;

    if(isEmpty())
        return false;
    if(x.current == any){
        deleteFront();
        return true;
    }
    Node* temp = x.current;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    return true;


};


vector<Key> getVectorOfKey()const{
    vector<Key> temp;
    if(isEmpty())
        return temp;
    Node* curr = this->any;
    do{
        temp.push_back(curr->key);
        curr = curr->next;
    }while(curr != any);
    return temp;
};
vector<Key> getVectorOfKeyByInfo(Info info)const{
    vector<Key> temp;
    if(isEmpty())
        return temp;
    Node *curr = this->any;
    do{
        if(curr->info == info)
            temp.push_back(curr->key);

        curr = curr->next;

    }while(curr != this->any);
    return temp;
};
vector<Key> getVectorOfKeyFrom(int where, int number)const{
    vector<Key> temp;
    if(isEmpty() )
        return temp;
    Node* curr = this->any;
    if(where < 0){
        while(where)
           if(where++)
               curr = curr->prev;
    }else{
        while(where)
            if(where--)
                curr = curr->next;
    }

    if(number>=0){
        while(number)
            if(number--){
                temp.push_back(curr->key);
                curr = curr->next;
        }
    }else{
        while(number)
            if(number++){
                temp.push_back(curr->key);
                curr = curr->prev;
            }
    }
    return temp;
};

vector<Info> getVectorOfInfo()const{
    vector<Info> temp;
    if(isEmpty())
        return temp;
    Node* curr = this->any;
    do{
        temp.push_back(curr->info);
        curr = curr->next;
    }while(curr != any);
    return temp;
};
vector<Info> getVectorOfInfoByKey(Key key)const{
    vector<Info> temp;
    if(isEmpty())
        return temp;
    Node *curr = this->any;
    do{
        if(curr->key == key)
            temp.push_back(curr->info);

        curr = curr->next;

    }while(curr != this->any);
    return temp;
};
vector<Info> getVectorOfInfoFrom(int where, int number)const{
    vector<Info> temp;
    if(isEmpty() )
        return temp;
    Node* curr = this->any;
    if(where < 0){
        while(where)
           if(where++)
               curr = curr->prev;
    }else{
        while(where)
            if(where--)
                curr = curr->next;
    }

    if(number>=0){
        while(number)
            if(number--){
                temp.push_back(curr->info);
                curr = curr->next;
        }
    }else{
        while(number)
            if(number++){
                temp.push_back(curr->info);
                curr = curr->prev;
            }
    }
    return temp;
};

Iterator anything()const{
    return Iterator(any);
}

Const_Iterator anyconst()const{
    return Const_Iterator(any);
}

int getNr()const{
    return this->nr;
};

void setNr(int nr){
    this->nr = nr;
};

};




template<typename Key, typename Info>
Ring<Key, Info> produce(const Ring<Key, Info> &r1, int start1, int len1, bool dir1, const Ring<Key, Info> &r2, int start2, int len2, bool dir2, int repeat){
    Ring<Key, Info> rout;
    if(r1.isEmpty() && r2.isEmpty())
        return rout;
    if(repeat <= 0)
        return rout;
    if(len1 <=0 && len2 <=0)
        return rout;

    if(len1 < 0)
        len1 = 0;
    if(len2 < 0)
        len2 = 0;


    if(r2.isEmpty()){
        typename Ring<Key, Info>::Const_Iterator i1 = r1.anyconst();
        if(start1 >= 0){
            i1 += start1;
        }else{
            i1 -= (-1)*start1;
        }
        while(repeat){
            if(dir1){
                for(int i = 0; i<len1; i++){
                    rout.addNodeByIterator(i1);
                    i1++;
                }
            }else{
                for(int i = 0; i<len1; i++){
                    rout.addNodeByIterator(i1);
                    i1--;
                }
            }
            repeat--;
        }

    return rout;
    }
    if(r1.isEmpty()){
        typename Ring<Key, Info>::Const_Iterator i2 = r2.anyconst();
        if(start2 >= 0){
            i2 += start2;
        }else{
            i2 -= (-1)*start2;
        }
        while(repeat){
            if(dir2){
                for(int i = 0; i<len2; i++){
                    rout.addNodeByIterator(i2);
                    i2++;
                }
            }else{
                for(int i = 0; i<len2; i++){
                    rout.addNodeByIterator(i2);
                    i2--;
                }
            }
            repeat--;
        }

    return rout;
    }

        typename Ring<Key, Info>::Const_Iterator i1 = r1.anyconst();
        typename Ring<Key, Info>::Const_Iterator i2 = r2.anyconst();

        if(start1 >= 0){
            i1 += start1;
        }else{
            i1 -= (-1)*start1;
        }
        if(start2 >= 0){
            i2 += start2;
        }else{
            i2 -= (-1)*start2;
        }

        while(repeat){
            if(dir1){
                for(int i = 0; i<len1; i++){
                    rout.addNodeByIterator(i1);
                    i1++;
                }
            }else{
                for(int i = 0; i<len1; i++){
                    rout.addNodeByIterator(i1);
                    i1--;
                }
            }
            if(dir2){
                for(int i = 0; i<len2; i++){
                    rout.addNodeByIterator(i2);
                    i2++;
                }
            }else{
                for(int i = 0; i<len2; i++){
                    rout.addNodeByIterator(i2);
                    i2--;
                }
            }
            repeat--;
        }

    return rout;
};





#endif // RING_H
