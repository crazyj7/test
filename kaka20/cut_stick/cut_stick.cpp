// cut_stick.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <string>

#include <stack>


using namespace std;
bool bdebug = true;


int solution(string arrangement) {
	int answer = 0;
	// ()는 레이저
	// (는 막대 시작. )는 막대 끝.
	//

	// ()이면 레이저로 스택에 있는 모든 막대들을 자른다. 개수(값)가 1개 증가.
	// (이면 스택에 막대 추가. 1추가.
	// )이면 스택에서 막대 꺼냄. 값 꺼냄.
	stack<int> stick;

	for (int i=0; i < arrangement.length(); i++) {
		if (arrangement[i] == '(' && arrangement[i + 1]==')' ) {
			// laser
			answer += stick.size();
			i++;
			continue;
		}
		if (arrangement[i] == '(') {
			// stick start
			stick.push(1);
			answer++;
		}
		if (arrangement[i] == ')') {
			stick.pop();
		}
	}




	return answer;
}


int main()
{
    std::cout << "Hello World!\n";
	int iret;

	iret = solution("()(((()())(())()))(())");
	cout << iret << endl;

	return 0;
}



