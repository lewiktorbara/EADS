#include <iostream>
#include "ring.h"
using namespace std;

int main()
{
   Ring<int,int> a;
   Ring<int,int> b;
    Ring<int,int> c;
    Ring<int,int>::Const_Iterator l;




    c.addNode(1,1);


    cout << c.howManyInfoExist(4);
    if(a == b)
    cout << c;

        cout << a;
        cout << b;
        cout << produce(c,0,17,false,c,31,1,false,2);

}
