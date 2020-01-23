#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

// 10^9/8 = 125000000
unsigned char *bitmap=NULL ;
long long maxmemsize = 0;
long long maxwidth=0 ;
long long height=0 ;

//long long maxmemorysize = 100000000L;	// 100M
long long maxmemorysize = 500000000L;	// 500M
bool bdebug = false;


long long bitmap_count() {
    long long ans=0 ;
    for(long long i=0; i< maxmemsize; i++) {
        if ( bitmap[i] ) {
            for (int j=0; j<8; j++) {
                if ( bitmap[i] & (0x01<<j) )
                    ans++ ;
            }
        }
    }
    return ans ;
}

// set bitmap
// 픽셀이 비트맵으로 대응하지 않고, 0~1 범위가 비트맵(0)으로 대응.
// 따라서 한 칸(마지막 인덱스는 제외)을 줄인다.
void bitmap_set_rect(vector<int> rect) {
    int x1, y1 ;
    int x2, y2  ;
    x1 = rect[0] ;
    y1 = rect[1] ;
    x2 = rect[2]-1 ;
    y2 = rect[3]-1 ;

    if (x1>x2 || y1>y2) {
        cout << "Error: first index is greater than second index." << endl ;
        return ;
    }
    
    int bx1 = x1/8 ;    // start block index
    int bx2 = x2/8 ;    // end block index
    int bsize = bx2-bx1+1 ; // need block cnt.
    unsigned char m1=0x00, m2=0x00 ; // one row start block, end block byte. 8bit.

	if (bdebug)
		cout << "x1="<<x1<<" x2="<<x2<<endl ;
	if (bdebug)
		cout << "y1="<<y1<<" y2="<<y2<<endl ;
	if (bdebug)
		cout << "bx1=" << bx1 << " bx2=" << bx2 << " bsize=" << bsize << endl ;
    // how many bit set in first block? 0=8, 1=7, ... 7=1
    m1 = 0 ;
    for (int i=x1%8; i<8 ;i++)
        m1 |= 0x01<<i ;
    m2 = 0 ;
    for (int i=0; i<=x2%8 ;i++)
        m2 |= 0x01<<i ;
    if ( bx1==bx2 ) { // same block
        m1 = 0 ;
        for (int i=x1%8; i<=x2%8 ;i++)
            m1 |= 0x01<<i ;
    }
	if (bdebug)
		printf("%0x %0x\n", m1, m2) ;
    // cout << "m1=" << std::hex << m1 << " m2="<< std::hex << m2 <<endl ;

    for(int y=y1; y<=y2; y++) {
		if (y % 1000 == 0) {
//			printf("debug:y=%ld\n", y);
		}
        if (bx1==bx2) {
            // one block
            bitmap[y*maxwidth+bx1] |= m1 ;
        }
        else if (bx1+1==bx2) {
            // two block
            bitmap[y*maxwidth+bx1] |= m1 ;
            bitmap[y*maxwidth+bx1+1] |= m2 ;
        }
        else {
            //printf("0x%x 0x%x\n", bitmap[y*maxwidth+bx1], bitmap[y*maxwidth+bx2]) ;
            bitmap[y*maxwidth+bx1] |= m1 ;
            bitmap[y*maxwidth+bx2] |= m2 ;
            //printf("0x%x 0x%x \n", m1, m2) ;
            memset(&bitmap[y*maxwidth+bx1+1], 0xFF, bsize-2) ;
        }
    }
	if (bdebug)
		printf("debug: end\n");
}

// 원점으로 평행이동. (move left bottom point to origin)
vector<vector<int> > leftdown(vector<vector<int> > rectangles, long long &maxbuffersize)
{
    int minx=100000, miny=100000 ;
    int maxx=0, maxy=0 ;
    int x1, y1 ;
    int x2, y2  ;
    vector<vector<int> > retrect ;

    for (int i=0; i<rectangles.size(); i++) {
        vector<int> rect = rectangles[i] ;
        x1 = rect[0] ;
        y1 = rect[1] ;
        x2 = rect[2] ;
        y2 = rect[3] ;
        if (x1<minx) minx = x1 ;
        if (x2<minx) minx = x2 ;
        if (y1<miny) miny = y1 ;
        if (y2<miny) miny = y2 ;
        if (x1>maxx) maxx = x1 ;
        if (x2>maxx) maxx = x2 ;
        if (y1>maxy) maxy = y1 ;
        if (y2>maxy) maxy = y2 ;
    }
	if (bdebug)
		cout << "minx=" << minx << " miny=" << miny << endl ;
	if (bdebug)
		cout << "width="<<maxx-minx << " height="<<maxy-miny << endl ;

    maxwidth = (maxx-minx)/8+1 ;    // max width length(byte)
    height = maxy-miny ;
	if (bdebug)
		cout << "maxwidth=" << maxwidth << endl ;
	maxbuffersize = maxwidth * height;
    
    // recalc
    for (int i=0; i<rectangles.size(); i++) {
        vector<int> rect = rectangles[i] ;
        rect[0] -= minx;
        rect[1] -= miny;
        rect[2] -= minx;
        rect[3] -= miny;
        retrect.push_back(rect) ;
    }
    return retrect ;
}

void print_rect(vector<vector<int> > rectangles)
{
    for (int i=0; i<rectangles.size(); i++) {
        vector<int> rect = rectangles[i] ;
        cout << "[" << rect[0] << " "
            << rect[1] << " "
            << rect[2] << " "
            << rect[3] << "] " ;
    }
    cout << endl ;
}

long long mini_solution(vector<vector<int> > rectangles)
{
	long long answer = -1;
	long long maxbufsize = 0;

	rectangles = leftdown(rectangles, maxbufsize); // left bottom을 원점으로 평행이동. 크기를 최소화.
	if (bdebug)
		print_rect(rectangles);

	maxmemsize = maxbufsize;
	bitmap = (unsigned char*)malloc(maxmemsize);    // about max size...
	memset(bitmap, 0x00, maxmemsize); // calloc not found.
	if (bitmap == NULL) {
		cout << "error!: memory alloc failed." << endl;
		return 0;
	}
	for (int i = 0; i < rectangles.size(); i++) {
		bitmap_set_rect(rectangles[i]);
	}
	answer = bitmap_count();
	if (bdebug)
		cout << "mini_solve answer=" << answer << endl;
	free(bitmap);
	return answer;
}

// 페이지에 해당되는 영역으로 재구성.
vector<vector<int> > rectInPage(int pagenum, int pageheight, vector<vector<int> > rects) {
	long long starty = pagenum * pageheight;
	long long endy = (pagenum + 1) * pageheight;
	int x1, y1, x2, y2;
	vector<vector<int> > ret_rects;
	int offsety = 0;

	for (int i = 0; i < rects.size(); i++) {
		vector<int> rect = rects[i];
		x1 = rect[0];
		y1 = rect[1];
		x2 = rect[2];
		y2 = rect[3];
		offsety = i * pageheight;
		// in
		if (y1 >= starty && y1<endy &&
			y2>starty&& y2 <= endy) {
			if (bdebug)
				cout << " in " << y1 << " " <<y2 << endl;
			ret_rects.push_back(vector<int> {x1, y1 - offsety, x2, y2 - offsety});
		}
		// out
		else if ( (y1<starty && y2<starty ) ||
			(y1>endy && y2>endy ) ) {
			if (bdebug)
				cout << " out " << y1 << " "<< y2 << endl;
			// out.
		}
		else {
			int newy1=y1, newy2=y2 ;
			// intersect.
			if (y1 < starty)
				newy1 = starty;
			if (y2 > endy)
				newy2 = endy;
			if (bdebug)
				cout << " intersect " << y1 << " "<< y2 << " : new" << newy1 << " " << newy2<< endl;
			ret_rects.push_back(vector<int> {x1, newy1 - offsety, x2, newy2 - offsety});
		}
	}
	return ret_rects;
}

long long solution(vector<vector<int> > rectangles)
{
    long long answer = -1;
	long long maxbufsize = 0;
    // 10^9 < 2^32(int)
    // 10^9/8 = 125000000  // alloc fail
//    bitmap = (char*) malloc(125000000*125000000) ;
    
	if (bdebug)
		print_rect(rectangles);
	rectangles = leftdown(rectangles, maxbufsize) ; // left bottom을 원점으로 평행이동. 크기를 최소화.
	if (bdebug)
		print_rect(rectangles) ;

	// memory!
	// 100,000,000 // 100M // 10,000^2  // avail
	// 10,000,000,000 // 10G // 100,000^2   // mem fail
//	maxbufsize = 100000000L;	// debug 이정도는 가능. 100M
	//maxbufsize = 1000000000L;	// debug 메모리 할당에 시간이 많이 소요. 그러나 돌아감. 1G
	//maxbufsize = 10000000000L;	// 10G	// memory fail.

	if (bdebug)
		cout << "maxmemsize=" << maxbufsize << endl;

	if (maxbufsize > maxmemorysize) {
		// 메모리가 100M가 넘어가면??? 
		// maxwidth * height
		// 나누자. 
		long maxrow = maxmemorysize / maxwidth;
		if (bdebug)
			cout << "Big memory!" << endl;
		if (bdebug)
			cout << "one page max row=" << maxrow << endl;
		long pagecnt = height / maxrow +1;
		if (height % maxrow == 0) pagecnt--;
		if (bdebug)
			cout << "page count = " << pagecnt << endl;

		answer = 0;
		for (int p = 0; p < pagecnt; p++) {
			// 페이지 단위로 쪼갠다.
			if (bdebug)
				cout << " page:" << p << "/"<<pagecnt<< endl;
			vector<vector<int> > pageRects = rectInPage(p, maxrow, rectangles);
			long long mini_ans = mini_solution(pageRects);
			if (bdebug)
				cout << " mini_ans=" << mini_ans << endl;
			answer += mini_ans;
		}
	}
	else {
		answer = mini_solution(rectangles);
	}

	if (bdebug)
		cout << "answer=" << answer << endl;
    return answer;
}


int main() {
    vector<vector<int> > retrect ;


	// 메모리 테스트 part1  // fail.
	retrect.clear();
	retrect.push_back(vector<int> {0, 0, 100000, 100000});
	if (solution(retrect) == 10000000000L) {
		cout << "OK" << endl << endl;
	}
	else {
		cout << "FAIL" << endl << endl;
	}
	return 0;

	// 메모리 테스트 part2  // 힘겹게. 메모리 1G 정도는 돌아간다.
	/*
	retrect.clear();
	retrect.push_back(vector<int> {0, 0, 100000, 100000});
	if (solution(retrect) == 10000000000L) {
		cout << "OK" << endl << endl;
	}
	else {
		cout << "FAIL" << endl << endl;
	}*/




    vector<int> r {0,0,8,1} ;
    retrect.push_back(r) ;
    if (solution(retrect)==8) {
		cout << "OK" << endl << endl;
    } else {
		cout << "FAIL" << endl << endl;
    }


	retrect.clear();
	r = vector<int>{ 0,0,8,2 };
	retrect.push_back(r);
	if (solution(retrect) == 16) {
		cout << "OK" << endl << endl;
	}
	else {
		cout << "FAIL" << endl<<endl;
	}

	retrect.clear();
	r = vector<int>{ 10,10,20,12 };
	retrect.push_back(r);
	if (solution(retrect) == 20) {
		cout << "OK" << endl << endl;
	}
	else {
		cout << "FAIL" << endl << endl;
	}

	// 중복 in test
	retrect.clear();
	r = vector<int>{ 10,10,20,12 };
	retrect.push_back(r);
	retrect.push_back(vector<int> {13,10,18,11});
	if (solution(retrect) == 20) {
		cout << "OK" << endl << endl;
	}
	else {
		cout << "FAIL" << endl << endl;
	}

	// 중복 part.
	// [[0, 1, 4, 4], [3, 1, 5, 3]]
	retrect.clear();
	retrect.push_back(vector<int> {0, 1, 4, 4});
	retrect.push_back(vector<int> {3, 1, 5, 3});
	if (solution(retrect) == 14) {
		cout << "OK" << endl << endl;
	}
	else {
		cout << "FAIL" << endl << endl;
	}

	// 중복 part2
	// [[1, 1, 6, 5], [2, 0, 4, 2], [2, 4, 5, 7], [4, 3, 8, 6], [7, 5, 9, 7]]
	retrect.clear();
	retrect.push_back(vector<int> {1, 1, 6, 5});
	retrect.push_back(vector<int> {2, 0, 4, 2});
	retrect.push_back(vector<int> {2, 4, 5, 7});
	retrect.push_back(vector<int> {4, 3, 8, 6});
	retrect.push_back(vector<int> {7, 5, 9, 7});
	if (solution(retrect) == 38) {
		cout << "OK" << endl << endl;
	}
	else {
		cout << "FAIL" << endl << endl;
	}



    // retrect.push_back(vector<int> {20,20,80,80}) ;

    // retrect.push_back(vector<int> {2,0,4,2}) ;
    // retrect.push_back(vector<int> {2,4,5,7}) ;
    // retrect.push_back(vector<int> {4,3,8,6}) ;
    // retrect.push_back(vector<int> {7,5,90,70}) ;

//    string s = "[[1, 1, 6, 5], [2, 0, 4, 2], [2, 4, 5, 7], [4, 3, 8, 6], [7, 5, 9, 7]]" ;

//    solution(retrect) ;
    return 0 ;
}

