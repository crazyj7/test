// colorbook.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>	// for sort
#include <cstdlib>	// for random
#include <time.h>
#include <unordered_map>
#include <deque>
#define DEBUG_WIN 1

#if (DEBUG_WIN)
#include <windows.h>
#endif

using namespace std;

// 0=no print, 1=some log, 2=full log
int idebug = 2;
#if (DEBUG_WIN)

int clock_gettime(int, struct timespec* tv)
{
	static int initialized = 0;
	static LARGE_INTEGER freq, startCount;
	static struct timespec tv_start;
	LARGE_INTEGER curCount;
	time_t sec_part;
	long nsec_part;

	if (!initialized) {
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&startCount);
		timespec_get(&tv_start, TIME_UTC);
		initialized = 1;
	}

	QueryPerformanceCounter(&curCount);

	curCount.QuadPart -= startCount.QuadPart;
	sec_part = curCount.QuadPart / freq.QuadPart;
	nsec_part = (long)((curCount.QuadPart - (sec_part * freq.QuadPart))
		* 1000000000UL / freq.QuadPart);

	tv->tv_sec = tv_start.tv_sec + sec_part;
	tv->tv_nsec = tv_start.tv_nsec + nsec_part;
	if (tv->tv_nsec >= 1000000000UL) {
		tv->tv_sec += 1;
		tv->tv_nsec -= 1000000000UL;
	}
	return 0;
}


unsigned long long clock_milli() {
	timespec t;
	clock_gettime(0, &t);
	unsigned long long nano = t.tv_sec * 1000000000 + t.tv_nsec;
	unsigned long long milli = nano / 1000000;
	return milli;
}
#else
unsigned long long clock_milli() {
	return 0;
}
#endif


void print_vect(vector<int> v)
{
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

void print_mat(vector<vector<int>> m)
{
	for (auto i : m) {
		print_vect(i);
	}
	cout << endl;
}

//////////////////////////////////////////////////////////////////////////////




// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	int number_of_area = 0;
	int max_size_of_one_area = 0;

	// mxn matrix ; picture
	int groupid = 0;	
	vector<vector<int>> groupmat;	// 각 셀 별 그룹번호. 1번그룹부터 시작.
	unordered_map < int, vector< int > >  grouplist; // r=v/n, c=v%n , v=r*n+c 

	if (idebug>1)
		print_mat(picture);


	// groupmat  init.
	vector<int> zero;
	for (int i = 0; i < n; i++)
		zero.push_back(0);
	for (int i = 0; i < m; i++)
		groupmat.push_back(zero);

	// grouping
	// (0,0)에서 시작해서 탐색.
	// 각 셀에서 우,하 이동가능(같은색)한지 체크하여 그룹번호를 지정.
	// value=0은 무시. 백그라운드임.
	// 이동가능시 타 그룹이면 merge. 
	int groupidx = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int col = picture[i][j];
			if (col == 0) // background ignore
				continue;
			if (groupmat[i][j] == 0) {
				// new group
				groupid++;	// 계속 증가.
				groupidx = groupid;	// 현재 그룹 id
				groupmat[i][j] = groupidx;
				grouplist[groupidx].push_back(i * n + j);
			}
			else {
				groupidx = groupmat[i][j];
			}

			// right
			if (j != n - 1 && picture[i][j + 1] == col) { // 오른쪽이동가능이고 같은색이면
				if ( groupmat[i][j+1]==0 ) // 오른쪽이 그룹 미할당상태
				{
					groupmat[i][j + 1] = groupidx;	// 동일그룹으로 할당
					grouplist[groupidx].push_back(i * n + j+1);
				}
				else if (groupmat[i][j+1]!=groupidx) {
					// 타그룹으로 되어 있으면 그룹 병합.
					// groupid를 groupmat[i][j+1] 그룹 번호로 변경
					for (auto el : grouplist[groupidx]) {
						groupmat[el / n][el % n] = groupmat[i][j + 1];
						grouplist[groupmat[i][j + 1]].push_back(el);
					}
					grouplist.erase(groupidx);
					groupidx = groupmat[i][j + 1];
				}
			}
			// down 
			if (i != m - 1 && picture[i + 1][j] == col) {
				if (groupmat[i + 1][j] == 0 ) {
					groupmat[i + 1][j] = groupidx;
					grouplist[groupidx].push_back((i + 1) * n + j);
				}
				else if (groupmat[i + 1][j] != groupidx) {
					for (auto el : grouplist[groupidx]) {
						groupmat[el / n][el % n] = groupmat[i + 1][j];
						grouplist[groupmat[i + 1][j]].push_back(el);
					}
					grouplist.erase(groupidx);
					groupidx = groupmat[i + 1][j];
				}
			}
		}
	}
	
	cout << grouplist.size() << endl;

	if (idebug)
		print_mat(groupmat);
	max_size_of_one_area = 0;
	for (auto el : grouplist) {
		if (max_size_of_one_area < el.second.size())
			max_size_of_one_area = el.second.size();
	}

	number_of_area = grouplist.size();

	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;

	cout << answer[0] << " " << answer[1] << endl;

	return answer;
}




int main()
{
    std::cout << "Hello World!\n";
	vector<vector<int>> picture = { {1, 1, 1, 0},{1, 2, 2, 0},{1, 0, 0, 1},{0, 0, 0, 1},{0, 0, 0, 3},{0, 0, 0, 3} };

	//[[1, 1, 1, 0], [1, 2, 2, 0], [1, 0, 0, 1], [0, 0, 0, 1], [0, 0, 0, 3], [0, 0, 0, 3]]
	//vector<int> r { };
	//picture.push_back(r);

	solution(picture.size(), picture[0].size(),  picture);

	return 0;
}

