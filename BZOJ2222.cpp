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
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 305
int dp[MAXN];

int main() {
	dp[1]=1;
	dp[2]=2;
	for (int i=3;i<=300;i++) {
		printf("dp %d : %d\n",i,int(ceil(log(i)/log(3))+ceil(log(i/2)/log(2))));
	}

	return 0;
}

