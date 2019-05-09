#include <iostream>
#include "Dictionary.h"

using namespace std;

int main()
{

    Dictionary<int, int> a;
    for(int i=15; i >0 ; i--)
    a.insert(i,i);

    Dictionary<int, int> b(a);
    b.remove(8);
    b.remove(5);
    b.remove(12);

    Dictionary<int,int> c = b;
    c.insert(12,12);
    c.insert(100,111);

    Dictionary<int,int>::Iterator ia = a.begin();
    for(int i=0; i<10; i++)
        ia++;
    cout<< *ia << "\n";

    Dictionary<int,int>::Const_Iterator cib = b.const_middle();
    Dictionary<int,int>::Const_Iterator ib(cib);
    for(int i = 0; i<20; i++)
        ib--;
    cout<< *ib<<"\n";


    c.print_t();



    return 0;
}
