// skilltree.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool bdebug = true;

bool check_valid(string skill, string sample) {
	size_t cindex = 0;
	bool valid = true;
	if (bdebug)
		cout << "sample=" << sample << endl;

	for (auto c : sample) {
		size_t npos = skill.find(c);
		if (npos == string::npos)
			continue;
		// found char in skill
		if (npos > cindex) {
			valid = false;
			break;
		}
		cindex = npos + 1;
	}
	cout << "valid="<< valid << endl;
	return valid;
}



int solution(string skill, vector<string> skill_trees) {
	int answer = 0;

	if (bdebug)
		cout << "skill=" << skill << endl;

	for (auto s : skill_trees) {
		if (check_valid(skill, s))
			answer++;
	}
	return answer;
}


int main()
{
	cout << solution("CBD", vector<string> {"BACDE", "CBADF", "AECB", "BDA"}) << endl;
    std::cout << "Hello World!\n";
}
