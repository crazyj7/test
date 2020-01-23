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



using namespace std;


//bool bdebug = true;
bool bdebug = false;

int n = 0;
int gheight=0;
vector<vector<int>> groupmat;
vector<int> groupmat_one;	// group id list.

unordered_map<int, vector<pair<int, int>>> grouplist; // 그룹번호별 매트릭스상위치(r,c) 리스트.

bool desc(int a, int b) {
	return a > b;
}


void print_vect(vector<int> v)
{
	if (!bdebug)
		return;
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

void print_mat(vector<vector<int>> m)
{
	if (!bdebug)
		return;
	for (auto i : m) {
		print_vect(i);
	}
	cout << endl;
}

void print_mat(deque < vector<int>> m)
{
	if (!bdebug)
		return;
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
	
	gheight = height;
	n = land.size();

	if (bdebug) {
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

	if (true)
		printf("phase1. groupping...\n");

	// 1단계. 그루핑.
	int groupcnt = 0;
	int groupidx = 0;	// inc
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int gi = groupmat[i][j];
			int gr = 0;
			int gd = 0;
			if (gi == 0) {	// new group
				groupcnt++;
				groupidx++;
				groupmat[i][j] = groupidx;
				gi = groupidx;
				groupmat_one.push_back(gi);	

				grouplist[gi] = vector<pair<int, int>>{ make_pair(i, j) };

			}
			bool canr = false;
			bool cand = false;
			if (can_move(land, i, j, 'r')) {
				gr = groupmat[i][j + 1];
				if (gr == 0) {
					groupmat[i][j + 1] = gi;
					gr = gi;
					grouplist[gi].push_back(make_pair(i, j + 1));
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
					grouplist[gi].push_back(make_pair(i+1, j));
				}
				else if (gd != gi) {
					if (gr != gd) {	// 이미 gr도 해당되기 때문에 groupcnt를 중복해서 줄이면 안됨.
						groupcnt--;
						cand = true;
					}
				}
			}

			if (canr || cand ){
				// 그룹 병합 작업.
				if (canr) {
					// gr 그룹 삭제(병합)
					auto it = find(groupmat_one.begin(), groupmat_one.end(), gr);
					if (it == groupmat_one.end()) {
						printf("error!: not found??\n");
					}
					groupmat_one.erase(it);

				}
				if ( cand && gr!=gd ) {
					// gd 그룹 삭제(병합)
					auto it = find(groupmat_one.begin(), groupmat_one.end(), gd);
					if (it == groupmat_one.end()) {
						printf("error!: not found??\n");
					}
					groupmat_one.erase(it);
				}

				// 여기서 오버헤드가 클 것으로 예상됨!!!!!
				// 이것을 해결하려면??? 그룹별 위치를 저장해야 한다. map. int: pair<int,int> 
				/*for (int m1 = 0; m1 < n; m1++) {
					for (int m2 = 0; m2 < n; m2++) {
						if (canr) {
							if (groupmat[m1][m2] == gr)
								groupmat[m1][m2] = gi;
						}
						if (cand && gr!=gd ) {
							if (groupmat[m1][m2] == gd)
								groupmat[m1][m2] = gi;
						}
					}
				}*/
				if (canr) {
					for (auto itg : grouplist[gr]) {
						groupmat[itg.first][itg.second] = gi;
						grouplist[gi].push_back(make_pair(itg.first, itg.second));

					}
				}
				if (cand) {
					for (auto itg : grouplist[gd]) {
						groupmat[itg.first][itg.second] = gi;
						grouplist[gi].push_back(make_pair(itg.first, itg.second));
					}
				}


			}
		}
	}

	if (true)
		printf("group count=%d\n", groupcnt);

	if (bdebug) {
		printf("input\n");
		print_mat(land);

		print_mat(groupmat);
		printf("group list\n");
		print_vect(groupmat_one);
	}

	// make groupmatrix -> 1D
	//for (int m1 = 0; m1 < n; m1++) {
	//	for (int m2 = 0; m2 < n; m2++) {
	//		groupmat_one.push_back(groupmat[m1][m2]);
	//	}
	//}
	int firstgroupid = groupmat_one[0];
	if (bdebug) {
		printf("first groupid =%d\n", firstgroupid);
	}

	vector<pair<int, int>> group1 = find_group(firstgroupid);

	// debug
	if (bdebug) {
		for (auto it : group1) {
			printf("(%d,%d) ", it.first, it.second);
		}
		printf("\n") ;
	}

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
	while (groupcnt>1) {
		int mincost = 99999;
		int mincostgroup = 0;

		if (bdebug)
			printf("group count=%d\n", groupcnt);
		if (groupcnt % 1000 == 1) {
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
			if (gi > firstgroupid) {
				cost = abs(land[it.first][it.second] - land[it.first][it.second - 1]);
				vector<int> tmp{ it.first, it.second, it.first, it.second - 1, gi, cost };
				allbridge.push_back(tmp);
			}

			// right check 
			if (it.second >= n-1)
				gi = -1;
			else
				gi = groupmat[it.first][it.second + 1];
			if (gi > firstgroupid) {
				cost = abs(land[it.first][it.second] - land[it.first][it.second + 1]);
				vector<int> tmp{ it.first, it.second, it.first, it.second + 1, gi, cost };
				allbridge.push_back(tmp);
			}

			// up check 
			if (it.first == 0)
				gi = -1;
			else
				gi = groupmat[it.first-1][it.second ];
			if (gi > firstgroupid) {
				cost = abs(land[it.first][it.second] - land[it.first-1][it.second]);
				vector<int> tmp{ it.first, it.second, it.first-1, it.second, gi, cost };
				allbridge.push_back(tmp);
			}

			// down check 
			if (it.first >= n - 1)
				gi = -1;
			else
				gi = groupmat[it.first+1][it.second];
			if (gi > firstgroupid) {
				cost = abs(land[it.first][it.second] - land[it.first+1][it.second]);
				vector<int> tmp{ it.first, it.second, it.first+1, it.second, gi, cost };
				allbridge.push_back(tmp);
			}
		}
		if (bdebug) {
			printf("all bridge count=%d\n", allbridge.size());
		}
		if (allbridge.size() == 0) {
			printf("Error! allbridge is empty!!!\n");
			break;
		}

		// debug
		if (bdebug) {
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
		if (bdebug) {
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

		group1 = update_group(mincostgroup, firstgroupid);
		groupcnt--;
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
	vector<vector<int>> land;

	//h = 3, r=15
	//h=3;
	//vector<vector<int>> land{ {1,4,8,10}, {5,5,5,5}, {10,10,10,10},{10,10,10,20} }; 

	//h=1, r=18, 
	//h = 1;
	//vector< vector<int>> land{ {10, 11, 10, 11},{2, 21, 20, 10},{1, 20, 21, 11},{2, 1, 2, 1} };
	groupmat.clear();

	// 300, 40 ; 103s ; many groups...
	// 300, 60, 27s	; less group
	h = 60;
	land = make_random(300);

	int t1 = time(NULL);
	int iret = solution(land, h);
	int t2 = time(NULL);

	printf("answer=%d\n", iret);
	printf("time=%d\n", t2 - t1);

	return 0;
}

