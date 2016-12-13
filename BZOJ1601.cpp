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
#define MAXN 305
int ch;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
struct edge {
	int u,v,w;
	edge(){}
	edge(int a,int b,int c):u(a),v(b),w(c){}
	bool operator < (edge a) const {
		return w<a.w;
	}
}e[MAXN*MAXN];
int n,ecnt=0,f[MAXN];
int getf(int x) {
	if (f[x]<0) return x;
	return f[x]=getf(f[x]);
}
bool merge(int u,int v) {
	int fu=getf(u),fv=getf(v);
	if (fu==fv) return 1;
	if (f[fu]<fv) {
		f[fu]+=f[fv];
		f[fv]=fu;
	}
	else {
		f[fv]+=f[fu];
		f[fu]=fv;
	}
	return 0;
}

int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		int w;
		read(w);
		e[++ecnt]=edge(0,i,w);
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) {
			int w;
			read(w);
			if (i!=j) e[++ecnt]=edge(i,j,w);
		}
	sort(e+1,e+ecnt+1);
	memset(f,-1,sizeof(f));
	int ans=0;
	for (int i=1,j=1;i<=n;i++) {
		while (merge(e[j].u,e[j].v)) j++;
		ans+=e[j].w;
		j++;
	}
	printf("%d\n",ans);
	return 0;
}

