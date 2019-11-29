#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main()  
{
    vector<int> v{10,20,30,40,50};
    int i;

    for(i=0; i<5; ++i)
    {
       cout<<v[i]<<"  ";
    }
    cout << endl ;

     for(i=0; i<5; ++i)
     {
      	rotate(v.rbegin(),v.rbegin()+1,v.rend());
        cout<<v[0]<<"  ";
     }
     cout << endl ;
}
