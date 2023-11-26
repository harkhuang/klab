#include <iostream>

using namespace std;

int arry[5] = {1,2,3,4,5};

int diff = 2;
int index = 2;

int show(int *p)
{
    for (int i = 0 ; i < 5 ; i++)
    {
        cout << arry[i] << "|" ;
    }
    cout << endl;
}


void init_arry()
{
    arry[0] = 1;
    arry[1] = 2;
    arry[2] = 0;
    arry[3] = 0;
    arry[4] = 0;
}

void update(int diffx)
{
    init_arry();
    while(diffx >0)
    {
        index++;
        arry[index] = arry[index -1];
        diffx--;
    }
    show(arry);
}


int main()
{
    update(0);
    update(1);
    update(2);
    update(3);
    update(4);
    return 0;
}