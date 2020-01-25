// territory_move.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <string>
//#include <pair> -> util
#include <utility>
#include <algorithm>	// for sort

#include <cstdlib>	// for random
#include <time.h>

//#include <map>
#include <unordered_map>
#include <deque>

//#include <chrono>
//#include <time.h>
#define DEBUG_WIN 1

#if (DEBUG_WIN)
	#include <windows.h>
#endif

using namespace std;


// 0=no print, 1=some log, 2=full log
int idebug = 1;

int n = 0;
int gheight=0;
vector<vector<int>> groupmat;

//vector<int> groupmat_one;	// group id list.  그룹목록 삭제

//unordered_map<int, vector<pair<int, int>>> grouplist; // 그룹번호별 매트릭스상위치(r,c) 리스트.
//unordered_map<int, list<pair<int, int>>> grouplist; // 그룹번호별 매트릭스상위치(r,c) 리스트.  value 타입이 vector가 list보다 빠르다.
unordered_map<int, vector<int>> grouplist; // pair를 삭제. value=i*n+j. 

bool desc(int a, int b) {
	return a > b;
}

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

void print_mat(deque < vector<int>> m)
{
	for (auto i : m) {
		print_vect(i);
	}
	cout << endl;

}

bool can_move(vector<vector<int>> &input, int i, int j, char d) {
	int i2 = i;
	int j2 = j;
	switch (d) {
	case 'l':
		j2--;
		break;
	case 'r':
		j2++;
		break;
	case 'u':
		i2--;
		break;
	case 'd':
		i2++;
		break;
	}
	if (i2 < 0 || j2 < 0)
		return false;
	if (i2 >= n || j2 >= n)
		return false;
	return (abs(input[i][j] - input[i2][j2]) <= gheight);
}


vector<pair<int, int>> find_group(int groupid) {
	vector<pair<int, int>> r;
	for (int m1 = 0; m1 < n; m1++) {
		for (int m2 = 0; m2 < n; m2++) {
			if (groupmat[m1][m2] == groupid)
				r.push_back(make_pair(m1, m2) );
		}
	}
	return r;
}

vector<pair<int,int>>  update_group(int oldgroupid, int newgroupid) {
	int cnt = 0;
	vector<pair<int, int>> r;

	for (int m1 = 0; m1 < n; m1++) {
		for (int m2 = 0; m2 < n; m2++) {
			if (groupmat[m1][m2] == oldgroupid) {
				cnt++;
				groupmat[m1][m2] = newgroupid;
				r.push_back(make_pair(m1, m2));
			}
		}
	}
	return r;
}


int solution(vector<vector<int>> land, int height) {
	int answer = 0;
	unsigned long long t1, t2;
	
	gheight = height;
	n = land.size();

	if (idebug) {
		printf("height=%d n=%d\n", gheight, n);
	}
	//bool bret = can_move(land, 1, 1, 'r');
	//printf("%d\n", bret);
	//bret = can_move(land, 1, 1, 'd');
	//printf("%d\n", bret);

	// 그룹행렬 초기화
	vector<int> row;
	for (int i = 0; i < n; i++)
		row.push_back(0);
	for (int i = 0; i < n; i++)
		groupmat.push_back(row);

	if (idebug)
		printf("phase1. groupping...\n");

	// 1단계. 그루핑.
	int groupcnt = 0;
	int groupidx = 0;	// inc
	for (int i = 0; i < n; i++) {

		if (idebug) {
			printf("progress=%.2f  groupcnt=%d\n", ((i + 1.0) / n) * 100.0, groupcnt);
		}
		t1 = clock_milli();

		for (int j = 0; j < n; j++) {

			int gi = groupmat[i][j];
			int gr = 0;
			int gd = 0;


			if (gi == 0) {	// new group
				groupcnt++;
				groupidx++;
				groupmat[i][j] = groupidx;
				gi = groupidx;
				//groupmat_one.push_back(gi);	

				//grouplist[gi] = vector<pair<int, int>>{ make_pair(i, j) };
				//grouplist[gi] = list<pair<int, int>>{ make_pair(i, j) };
				grouplist[gi] = vector<int>{ i * n + j };

			}
			bool canr = false;
			bool cand = false;
			if (can_move(land, i, j, 'r')) {
				gr = groupmat[i][j + 1];
				if (gr == 0) {
					groupmat[i][j + 1] = gi;
					gr = gi;
					//grouplist[gi].push_back(make_pair(i, j + 1));
					grouplist[gi].push_back(i * n + j + 1);
				}
				else if (gr != gi) {
					canr = true;
					groupcnt--;
				}
			}
			if (can_move(land, i, j, 'd')) {
				gd = groupmat[i + 1][j];
				if (gd == 0) {
					groupmat[i + 1][j] = gi;
					gd = gi;
					//grouplist[gi].push_back(make_pair(i+1, j));
					grouplist[gi].push_back((i+1) * n + j);
				}
				else if (gd != gi) {
					if (gr != gd) {	// 이미 gr도 해당되기 때문에 groupcnt를 중복해서 줄이면 안됨.
						groupcnt--;
						cand = true;
					}
				}
			}



			if (canr || cand ){
				if (canr) {
					for (auto itg : grouplist[gr]) {
						//groupmat[itg.first][itg.second] = gi;
						groupmat[itg / n][itg % n] = gi;
					}
					grouplist[gi].insert(grouplist[gi].end(), grouplist[gr].begin(), grouplist[gr].end());
					grouplist.erase(gr);
				}
				if (cand) {
					for (auto itg : grouplist[gd]) {
						//groupmat[itg.first][itg.second] = gi;
						groupmat[itg / n][itg % n] = gi;
					}
					grouplist[gi].insert(grouplist[gi].end(), grouplist[gd].begin(), grouplist[gd].end());
					grouplist.erase(gd);
				}
			} // end of if can move.

		} // end of for j
		t2 = clock_milli();
		if (idebug) {
			cout << "time=" << t2 - t1 << "ms" << endl;
		}
	} // end of for i

	if (idebug)
		printf("group count=%d\n", groupcnt);

	if (idebug>1) {
		printf("input\n");
		print_mat(land);

		print_mat(groupmat);
		printf("group list\n");
		//print_vect(groupmat_one);
	}

	// make groupmatrix -> 1D
	//for (int m1 = 0; m1 < n; m1++) {
	//	for (int m2 = 0; m2 < n; m2++) {
	//		groupmat_one.push_back(groupmat[m1][m2]);
	//	}
	//}
	//int firstgroupid = groupmat_one[0];
	int firstgroupid = groupmat[0][0];
	if (idebug>1) {
		printf("first groupid =%d\n", firstgroupid);
	}

	vector<pair<int, int>> group1 = find_group(firstgroupid);

	// debug
	if (idebug>1) {
		for (auto it : group1) {
			printf("(%d,%d) ", it.first, it.second);
		}
		printf("\n") ;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Phase2 . search the lowest cost path.
	deque<vector<int>> allbridge;

	//int tmpb[6] = { 1,2,3,4,5,6 };
	//vector<int> r(tmpb, tmpb + 6);
	//allbridge.push_back(r);

	//tmpb[0] = 9;
	//r = vector<int>(tmpb, tmpb + 6);
	//allbridge.push_back(r);
	//
	//for (auto x : allbridge) {
	//	printf("%d\n", x[0]);
	//}

	t1 = clock_milli();
	while (groupcnt>1) {
		int mincost = 99999;
		int mincostgroup = 0;

		if ( idebug > 1) {
			printf("group count=%d\n", groupcnt);
		}
		if (idebug && (groupcnt % 1000 == 1)) {
			printf("group count=%d\n", groupcnt);
		}

		for (auto it : group1) {
			int cost = -1;
			int gi = -1;

			// left check 
			if (it.second == 0)
				gi = -1;
			else
				gi = groupmat[it.first][it.second - 1];
			if (gi!=-1 && gi != firstgroupid) {
				cost = abs(land[it.first][it.second] - land[it.first][it.second - 1]);
				vector<int> tmp{ it.first, it.second, it.first, it.second - 1, gi, cost };
				allbridge.push_back(tmp);
			}

			// right check 
			if (it.second >= n-1)
				gi = -1;
			else
				gi = groupmat[it.first][it.second + 1];
			if (gi != -1 && gi != firstgroupid) {
				cost = abs(land[it.first][it.second] - land[it.first][it.second + 1]);
				vector<int> tmp{ it.first, it.second, it.first, it.second + 1, gi, cost };
				allbridge.push_back(tmp);
			}

			// up check 
			if (it.first == 0)
				gi = -1;
			else
				gi = groupmat[it.first-1][it.second ];
			if (gi != -1 && gi != firstgroupid) {
				cost = abs(land[it.first][it.second] - land[it.first-1][it.second]);
				vector<int> tmp{ it.first, it.second, it.first-1, it.second, gi, cost };
				allbridge.push_back(tmp);
			}

			// down check 
			if (it.first >= n - 1)
				gi = -1;
			else
				gi = groupmat[it.first+1][it.second];
			if (gi != -1 && gi != firstgroupid) {
				cost = abs(land[it.first][it.second] - land[it.first+1][it.second]);
				vector<int> tmp{ it.first, it.second, it.first+1, it.second, gi, cost };
				allbridge.push_back(tmp);
			}
		}
		if (idebug>1) {
			printf("all bridge count=%d\n", allbridge.size());
		}
		if (allbridge.size() == 0) {
			printf("Error! allbridge is empty!!!\n");
			break;
		}

		// debug
		if (idebug>1) {
			print_mat(allbridge);
		}

		// find min cost
		int idxbr = 0;
		for (int m1 = 0; m1 < allbridge.size(); m1++) {
			if (mincost > allbridge[m1][5]) {
				mincost = allbridge[m1][5];
				mincostgroup = allbridge[m1][4];
				idxbr = m1;
			}
		}
		if (idebug>1) {
			printf("mincost=%d mingroup=%d   (%d,%d)->(%d,%d)\n", mincost, mincostgroup,
				allbridge[idxbr][0], allbridge[idxbr][1], allbridge[idxbr][2], allbridge[idxbr][3]);
		}
		answer += mincost;

		// merge group mincostgroup into firstgroup
		// delete bridge where gropuid==mincostgroup
		for (int m1 = 0; m1 < allbridge.size(); m1++) {
			if (mincostgroup == allbridge[m1][4]) {
				allbridge.erase(allbridge.begin() + m1);
				m1--;
			}
		}
		//group1 = update_group(mincostgroup, firstgroupid);
		group1.clear();
		for (auto itg : grouplist[mincostgroup]) {
			//group1.push_back(make_pair(itg.first, itg.second));
			//groupmat[itg.first][itg.second] = firstgroupid;
			group1.push_back(make_pair(itg / n, itg % n));
			groupmat[itg / n][itg % n] = firstgroupid;
		}
		grouplist.erase(mincostgroup);


		groupcnt--;
	}
	t2 = clock_milli();
	if (idebug) {
		cout << "Phase2 time=" << t2 - t1 << "ms" << endl;
	}



	return answer;
}



vector<vector<int>> make_random(int size) {
	vector < vector<int> >  v;
	srand(time(NULL));
	for (int m1 = 0; m1 < size; m1++) {
		vector<int > r;
		for (int m2 = 0; m2 < size; m2++) {
			int value = rand() % 100;
			r.push_back(value);
		}
		v.push_back(r);
	}
	return v;
}

int main()
{
    std::cout << "Hello World!\n";
	int h = 1;
	groupmat.clear();

	//h = 3, r=15
	//h=3;
	//vector<vector<int>> land{ {1,4,8,10}, {5,5,5,5}, {10,10,10,10},{10,10,10,20} }; 

	//h=1, r=18, 
	//h = 1;
	//vector< vector<int>> land{ {10, 11, 10, 11},{2, 21, 20, 10},{1, 20, 21, 11},{2, 1, 2, 1} };


	// 300, 40 ; 103s ; many groups...
	// 300, 60, 27s	; less group
	h = 30;
	vector<vector<int>> land;
	land = make_random(300);

	int t1 = time(NULL);
	int iret = solution(land, h);
	int t2 = time(NULL);

	printf("answer=%d\n", iret);
	printf("time=%d\n", t2 - t1);


	return 0;
}

