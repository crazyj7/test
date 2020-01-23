// printqueue.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;
bool bdebug = true;

void print_vect(vector<int> v)
{
	if (!bdebug)
		return;
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

int argmax(vector<int> &v, int startindex=0) {
	int index = startindex;
	int maxvalue = v[index];
	for (int i = startindex+1; i < v.size(); i++) {
		if (maxvalue < v[i]) {
			maxvalue = v[i];
			index = i;
		}
	}
	return index;
}


// 중요도는 1~9 범위. (클수록 중요)
// location은 0부터 시작. (위치)
// answer는 1부터 시작. (순번)
// 
// 큐에서 대기작업의 가장 앞에 있는 것을 처리하기 전에 
// 지금 것 보다 중요한 작업이 있으면 큐에 마지막으로 보낸다.
// 이것을 반복하여 중요도 큰 것 부터 처리.
// 
// 중요도가 다음 순서일 때, loc에 있는 작업은 몇 번째로 처리될 것인지 확인.
int solution(vector<int> priorities, int location) {
	int answer = 0;
	vector<int> loc;

	for (int i = 0; i < priorities.size(); i++) {
		loc.push_back(i);
	}

	if (bdebug)
		printf("input:");
	print_vect(priorities);

	for (int i = 0; i < priorities.size()-1; i++) {
		int mi = argmax(priorities, i+1);
		if (priorities[mi] > priorities[i]) {
			// 더 중요한게 큐에 있다. 
			// i부터 mi-1까지 뒤로 보낸다. 
			vector<int> sub(priorities.begin() + i, priorities.begin() + mi);
			priorities.erase(priorities.begin() + i, priorities.begin() + mi);
			priorities.insert(priorities.end(), sub.begin(), sub.end());
			//
			vector<int> isub(loc.begin() + i, loc.begin() + mi);
			loc.erase(loc.begin() + i, loc.begin() + mi);
			loc.insert(loc.end(), isub.begin(), isub.end());

		}
	}
	print_vect(priorities);
	print_vect(loc);

	for (int i = 0; i < loc.size(); i++) {
		if (location == loc[i])
		{
			answer = i;
			break;
		}
	}
	answer++;

	return answer;
}


int main()
{
    std::cout << "Hello World!\n";

	solution(vector<int> {2,1,3, 2}, 3);
	//solution(vector<int> { 1, 1, 9, 1, 1, 1 }, 3);

	return 0;
}
