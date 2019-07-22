/* 
test
*/

#include "test.h"
#include <vector>
#include <iostream>


int main()
{
	std::vector<std::pair<double, double>> v1 ;
	std::vector<std::pair<double, double>> v2 ;

	for (int i=0; i<10; i++) {
		v1.push_back( std::make_pair(i, i) ) ;
		v2.push_back( std::make_pair(i, i) ) ;
	}
	double ret = testAuth(v1, v2) ;
	std::cout << "testAuth return=" << ret << std::endl ;

	return 0 ;
}
