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

#define MAXW 10005
#define MOD 2147483647
int n,m,w;

struct point {
	int x,y;
	point(){}
	point(int a,int b):x(a),y(b){}
}p[MAXW];

int xcnt,xt[MAXW],ycnt,yt[MAXW];

int main() {
	scanf("%d%d%d",&n,&m,&w);
	for (int i=1;i<=w;i++) {
		scanf("%d%d",&p[i].x,&p[i].y);
		xt[i]=p[i].x;
		yt[i]=p[i].y;
	}
	sort(xt+1,xt+n+1);xcnt=int(unique(xt+1,xt+n+1)-xt-1);
	sort(yt+1,yt+n+1);ycnt=int(unique(yt+1,yt+n+1)-yt-1);
	return 0;
}

