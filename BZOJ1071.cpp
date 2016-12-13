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

#define MAXN 5005

int n,A,B,C;

struct data {
	int h,v,s;
}p[MAXN],q[MAXN];

bool byH(data a,data b) {
	return a.h<b.h;
}

bool byS(data a,data b) {
	return a.s<b.s;
}

int main() {
	scanf("%d%d%d%d",&n,&A,&B,&C);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&p[i].h,&p[i].v);
		p[i].s=A*p[i].h+B*p[i].v;
		q[i]=p[i];
	}
	sort(p+1,p+n+1,byH);
	sort(q+1,q+n+1,byS);
	for (int i=1;i<=n;i++) {
		
	}

	return 0;
}

