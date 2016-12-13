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
#define MAXN 1005
typedef long long LL;
int n,m,f[MAXN];

int getf(int x) {
	if (f[x]<0) return x;
	return f[x]=getf(f[x]);
}
void merge(int u,int v) {
	int fu=getf(u),fv=getf(v);
	if (fu!=fv) {
		if (f[fu]<f[fv]) {
			f[fu]+=f[fv];
			f[fv]=fu;
		}
		else {
			f[fv]+=f[fu];
			f[fu]=fv;
		}
	}
}
bool visit[MAXN];
double dis[MAXN],ans=0;
LL power(LL x) {return x*x;}
LL X[MAXN],Y[MAXN];
double dist(int a,int b) {
	return sqrt(power(X[a]-X[b])+power(Y[a]-Y[b]));
}
void prim() {
	for (int i=2;i<=n;i++) dis[i]=1e9;
	int x=1,to;
	double mindis;
	while (1) {
		visit[x]=1;
		to=-1;
		mindis=1e10;
		for (int i=1;i<=n;i++) {
			if (!visit[i]) {
				if (getf(i)==getf(x)) {
					dis[i]=0;
				}
				else {
					dis[i]=min(dis[i],dist(x,i));
				}
				if (dis[i]<mindis) {
					mindis=dis[i];
					to=i;
				}
			}
		}
		if (to==-1) break;
		ans+=mindis;
		merge(x,to);
		x=to;
	}
}
int main() {
	read(n);read(m);
	for (int i=1,xx,yy;i<=n;i++) {
		read(xx);read(yy);
		X[i]=xx,Y[i]=yy;
	}
	memset(f,-1,sizeof(f));
	for (int i=1,u,v;i<=m;i++) {
		read(u);read(v);
		merge(u,v);
	}
	prim();
	printf("%.2lf\n",ans);
	return 0;
}

