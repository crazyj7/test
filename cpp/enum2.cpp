#include <iostream>

typedef enum _fruit {
	APPLE=0,
	BANANA, GRAPE
} FRUIT;

using namespace std ;

int main()
{
	FRUIT a,b ;
	a=APPLE ;
	b=BANANA;
	cout << "a=" << a << endl ;
	cout << "b=" << b << endl ;
	return 0 ;
}
