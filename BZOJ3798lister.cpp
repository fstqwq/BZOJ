/*	Never stop fighting for what you believe in.	*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

int cnt=0;

inline bool check(int x) {
	for (int i=2,sqx=(int)sqrt(x);i<=sqx;i++) {
		if (x%i==0) return 0;
	}
	for (int i=1,j=(int)sqrt(x);i<=j;) {
		while (i*i+j*j<x) i++;
		while (i*i+j*j>x) j--;
		if (i*i+j*j==x) return 1;
	}
	return 0;
}

int main() {
	freopen("list.txt","w",stdout);
	printf("const int list[]={0");
	for (int i=1;i<300023808;i++) {
		if (check(i)) cnt++;
		if ((i&65535)==65535) printf(",%d",cnt),fflush(stdout);
	}
	printf("};");
	return 0;
}

