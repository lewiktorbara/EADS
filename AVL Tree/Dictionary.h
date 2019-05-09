#include<stdlib.h>
#include<string>
#include<iostream>

using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H


template<typename Key, typename Info>
class Dictionary {
private:
    struct Node{
    Key key;
    Info info;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    Node(Key ke, Info in):
        key(ke),info(in), left(nullptr), right(nullptr),
        parent(nullptr), height(0) {};
    Node(Key ke, Info in, int h):
        key(ke), info(in), left(nullptr), right(nullptr),
        parent(nullptr), height(h) {};

    };

    Node* root;




    int getHeight(Node* x){  // returns the number of nodes below, if nullptr returns -1
       return x == nullptr ? -1 : x->height;
     }
    Node* search(const Key key, Node* x)const{  //returns node with given key among given node and his children, if node with given key doesn't exists returns nullptr
        if(!x)
            return x;
        if(x->key == key)
            return x;
        if(x->key < key)
            return search(key, x->right);
        if(x->key > key)
            return search(key, x->left);
    }
    Node* copy(Node* x){    // returns copy of given node with his children
        if(!x)
            return nullptr;

        Node* net;

        if(x){
            net = new Node(x->key, x->info, x->height);
            net->left = copy(x->left);
            if(net->left)
                net->left->parent = net;
            net->right = copy(x->right);
            if(net->right)
                net->right->parent = net;

        }
        return net;
    }
    void print(Node* x)const{ // displays node and children of given node without view about the balance
        if(!x)
            return;

        print(x->left);
        cout << "-[" << x->key << "," << x->info << "]-";
        print(x->right);
    }
    void clear(Node* x){    //deletes given node and his children

        if(!x)
            return;

        clear(x->left);
        clear(x->right);

        delete x;
    }
    Node* findMax(Node* x)const{    // returns node with the smallest key among given node and his children
        if(!x)
            return nullptr;
        if(!x->right)
            return x;

        return findMax(x->right);
    }
    Node* findMin(Node *x)const{    // returns node with the greatest key among given node and his children
        if(!x)
            return nullptr;
        if(!x->left)
            return x;

        return findMin(x->left);
    }
    Node* insert(const Key &key, const Info &info, Node* x){    //returns node in which structure creates new node and add it to given node, the balances the whole structure of tree
        if(!x)
            return new Node(key, info, 0);

        else if(key > x->key){
            x->right = insert(key, info, x->right);
            x->right->parent = x;
            if(getHeight(x->right) - getHeight(x->left) == 2){
                if(key > x->right->key)
                    x = lrotate(x);
                else
                    x = llrotate(x);
            }
        }
        else if(key < x->key){
            x->left = insert(key, info, x->left);
            x->left->parent = x;
            if(getHeight(x->left) - getHeight(x->right) == 2){
                if(key < x->left->key)
                    x = rrotate(x);
                else
                    x = rrrotate(x);

            }
        }
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;

    }
    Node* remove(const Key &key, Node* x){      //returns node in which structure deletes the node with given key among children of given nodes, then balances the whole structure of tree, if there is no node with given key it does nothing
        Node *temp;
        if(!x)
            return nullptr;

        else if(key < x->key)
            x->left = remove(key, x->left);
        else if(key > x->key)
            x->right = remove(key, x->right);
        else if(x->left && x->right){
                temp = findMin(x->right);
                x->key = temp->key;
                x->info = temp->info;
                x->right = remove(x->key, x->right);
        }else{
            temp = x;
            if(!x->left)
                x = x->right;
            else if(!x->right)
                x = x->left;
            delete temp;
        }
        if(!x)
            return x;


        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        if (getHeight(x->left) - getHeight(x->right) == 2) {
            if (getHeight(x->left->left) - getHeight(x->left->right) == 1) return rrotate(x);
            else return rrrotate(x);
        } else if (getHeight(x->right) - getHeight(x->left) == 2) {
            if (getHeight(x->right->right) - getHeight(x->right->left) == 1) return lrotate(x);
            else return llrotate(x);
        }

        return x;
    }
    Node* rrotate(Node* &x){    //algorithm of single right rotation to balance th tree
        Node *temp = x->left;
        x->left = temp->right;
        if(temp->right)
            temp->right->parent = x;
        temp->parent = x->parent;
        temp->right = x;
        x->parent = temp;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }
    Node* lrotate(Node* &x){    //algorithm of single left rotation to balance th tree
        Node *temp = x->right;
        x->right = temp->left;
        if(temp->left)
            temp->left->parent = x;
        temp->parent = x->parent;
        temp->left = x;
        x->parent = temp;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }
    Node* llrotate(Node* &x){   //algorithm of double left rotation to balance th tree
        x->right = rrotate(x->right);
        return lrotate(x);
    }
    Node* rrrotate(Node* &x){   //algorithm of double right rotation to balance th tree
        x->left = lrotate(x->left);
        return rrotate(x);
    }

        //method taken from
     // https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console

    int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][255]){ // prints balanced tree
        char b[20];
        int width = 5;

        if (!tree) return 0;

        sprintf(b, "(%03d)", tree->key);

        int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
        int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
        for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
        for (int i = 0; i < width; i++)
            s[2 * depth][offset + left + i] = b[i];

        if (depth && is_left) {

            for (int i = 0; i < width + right; i++)
                s[2 * depth - 1][offset + left + width/2 + i] = '-';

            s[2 * depth - 1][offset + left + width/2] = '+';
            s[2 * depth - 1][offset + left + width + right + width/2] = '+';

        } else if (depth && !is_left) {

            for (int i = 0; i < left + width; i++)
                s[2 * depth - 1][offset - width/2 + i] = '-';

            s[2 * depth - 1][offset + left + width/2] = '+';
            s[2 * depth - 1][offset - width/2 - 1] = '+';
        }
#endif

        return left + width + right;
    }



public:


    class Iterator {
        friend class Dictionary;
        mutable Node* curr;
        Iterator(Node *x){
            curr = x;
        }
        Node* operator->() const{
            return curr;
        }
    public:
        Iterator(){
        curr = nullptr;
        }

        Iterator(const Iterator &x){
            this->curr = x.curr;
        }

        ~Iterator(){}

        bool operator==(const Iterator &x)const{
            if(curr == x.curr)
                return true;
            return false;
        }
        bool operator!=(const Iterator &x)const{
            return !(*this == x);
        }

        Iterator operator=(const Iterator &x){
            if(*this == x) return *this;
            curr = x.curr;
            return *this;
        }

        Iterator &operator++()const{
            if(!curr)
                return *this;

            if(curr->right != nullptr){
                curr = curr->right;
            while(curr->left != nullptr)
                curr = curr->left;
            }else{
                Node *temp = curr->parent;
                while(temp && curr == temp->right){
                    curr = temp;
                    temp = temp->parent;
                }
                curr = temp;
            }
            return *this;
        }

        Iterator operator++(int)const{
            if(!curr)
                return *this;

            auto out = new Iterator(curr);

            if(curr->right != nullptr){
                curr = curr->right;
            while(curr->left != nullptr)
                curr = curr->left;
            }else{
                Node *temp = curr->parent;
                while(temp && curr == temp->right){
                    curr = temp;
                    temp = temp->parent;
                }
                curr = temp;
            }
           return *out;
        }

        Iterator &operator--()const{
            if(!curr)
                return *this;

            if(curr->left != nullptr){
                curr = curr->left;
            while(curr->right != nullptr)
                curr = curr->right;
            }else{
                Node *temp = curr->parent;
                while(temp && curr == temp->left){
                    curr = temp;
                    temp = temp->parent;
                }
                curr = temp;
            }
            return *this;
        }

        Iterator operator--(int)const {
            if(!curr)
                return *this;

            auto out = new Iterator(curr);

            if(curr->left != nullptr){
                curr = curr->left;
            while(curr->right != nullptr)
                curr = curr->right;
            }else{
                Node *temp = curr->parent;
                while(temp && curr == temp->left){
                    curr = temp;
                    temp = temp->parent;
                }
                curr = temp;
            }
           return *out;
        }


        Key operator*()const{
            if(!curr)
                return 0;
            return curr->key;
        }

      bool operator!()const{
            if(!curr)
                return true;
            return false;
        }
    };

    typedef const Iterator Const_Iterator;

    Dictionary(){
        root = nullptr;
    }
    ~Dictionary(){
        clear();
    }
    Dictionary(const Dictionary<Key,Info> &x){
        this->root = nullptr;
        *this = x;
    }

    Dictionary<Key, Info> &operator=(const Dictionary<Key,Info>& x){
        if(*this == x)
            return *this;

        this->clear();
        this->root = copy(x.root);
        return *this;
    }


    bool operator==(const Dictionary &x)const{
        if(this->root == nullptr && x.root == nullptr)
            return true;
        if(this->root == nullptr || x.root == nullptr)
            return false;

        Const_Iterator t2 = x.const_begin();
        for(Const_Iterator t1 = this->const_begin(); t1 != Iterator(nullptr) ; t1++){
            if( !t1 && !t2)
                return true;
            if( !t1 || !t2)
                return false;
            if( t1->key != t2->key || t1->info != t2->info)
                return false;
            t2++;
        }
        return true;
    }
    bool operator!=(const Dictionary &x)const{
        return !(*this == x);
    }
    friend ostream& operator<<(ostream &os, const Dictionary &x){ //use private method print to display tree
        if(!x.root){
            cout << "The tree is empty";
        }else{
            x.print(x.root);
        }
        return os;

    }
    void print_t()    {  //use private method _print_t
        char s[20][255];
        for (int i = 0; i < 20; i++)
            sprintf(s[i], "%80s", " ");

        _print_t(this->root, 0, 0, 0, s);

        for (int i = 0; i < 20; i++)
            printf("%s\n", s[i]);
    }

    bool isEmpty(){     //checks if tree is empty
        return this->root == nullptr;
    }
    void clear(){          //deletes all nodes in the tree
        clear(this->root);
        this->root = nullptr;
    }
    bool keyExists(const Key &key){ //checks if node with given key exists
        return search(key, this->root) != nullptr;
    }
    unsigned int getHeight(){       //returns height of tree
        return getHeight(this->root);
    }


    bool insert(const Key &key, const Info &info){

        if(keyExists(key))
            return 0;

        this->root = insert(key, info, this->root);
        return 1;


    }
    bool remove(const Key &key){
        if(!keyExists(key))
            return 0;
        this->root = remove(key, this->root);
            return 1;
    }

    Iterator begin(){
        return Iterator(findMin(root));
    }
    Iterator end(){
        return Iterator(findMax(root));
    }
    Iterator middle(){
        return Iterator(root);
    }
    Const_Iterator const_begin()const{
        return Const_Iterator(findMin(root));
    }
    Const_Iterator const_end()const{
        return Const_Iterator(findMax(root));
    }
    Const_Iterator const_middle()const{
        return Const_Iterator(root);
    }

    };




#endif // DICTIONARY_H
