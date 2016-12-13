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
#define MAXN 1100
int n,fa[MAXN],S,T;
double x[MAXN],y[MAXN],r[MAXN],x_t,y_t,s[MAXN],ans=0;;

bool flag=0;

double dis(int a,int b) {
	return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}

void dfs(int p) {
	ans+=s[p];
	if (p==T) {
		flag=1;
		printf("%d\n",int(ans));
		return;
	}
	for (int i=1;i<=n;i++) {
		if (abs(dis(p,i)-(r[i]+r[p]))<1e-8 && i!=fa[p]) {
			fa[i]=p;
			s[i]=s[p]*r[p]/r[i];
			dfs(i);
			if (flag) return;
		}
	}
	ans-=s[p];
}

int main() {
	scanf("%d%lf%lf",&n,&x_t,&y_t);
	for (int i=1;i<=n;i++) {
		scanf("%lf%lf%lf",x+i,y+i,r+i);
		if (x[i]==0 && y[i]==0) S=i;
		else if (x[i]==x_t && y[i]==y_t) T=i;
	}
	s[S]=10000;
	fa[S]=0;
	dfs(S);
	return 0;
}

