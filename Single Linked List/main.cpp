#include <iostream>

#include "sequance.h"

using namespace std;


int main()
{   Sequence<int, int> a;
    for(int i =0 ; i<10; i++)
        a.addElement(i,i);

    Sequence<int, int> b(a);
    Sequence<int, int> c = b;
    a.deleteElement(4);
    b.deleteFromKey(4,2);
    c.addAfterKey(5, 11, 5);
    cout << "Sequence a:"<< " \n"<< a << "Sequence b:"<< " \n"<< b<< "Sequence c:"<< " \n"<< c;

    b.clearSequence();
    c.clearSequence();

    for(int i = 5; i<15; i++)
        b.addElement(i,i);
    cout << b;

    cout<< a+b;
    cout << b+a;


    Sequence<int, char> d;
    Sequence<int, char> e;
    Sequence<int, char> f;


    for(int i =0; i<10; i++)
        d.addElement(i, 'a'+i);


    split(d, 0, e, 3, f,1); //splitting sequence from beginning
    cout<<"First case:"<<"\n" <<d << e << f;

        split(d, 14, e, 5, f,3); // splitting sequence beyond source sequence
    cout<<"Second case:"<<"\n"<< d << e << f;

        split(d, 0, e, 0, f,0); // splitting sequence by 0 for each result
   cout<<"Third case:"<<"\n"<< d << e << f;

        split(d, 4, e, 0, f,1); // splitting sequence to one result
    cout<<"Forth case:"<<"\n"<< d << e << f;


    return 0;
}
