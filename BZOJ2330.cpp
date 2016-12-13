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

#define MAXN 100005

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

struct edge {
	int next,to,w;
}e[MAXN<<1];

int n,m,ecnt=0,head[MAXN],dis[MAXN];
#define MOD 262143
int q[262144],h=0,t=0;

inline void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].w=w;
	e[ecnt].next=head[u];
	head[u]=ecnt;
}

int cnt[MAXN];
bool inq[MAXN];
bool spfa() {
	while (h<t) {
		int x=q[(h++)&MOD];inq[x]=0;
		for (int now=head[x];now;now=e[now].next) {
			if (dis[e[now].to]<dis[x]+e[now].w) {
				dis[e[now].to]=dis[x]+e[now].w;
				if ((cnt[e[now].to]++)>n) return 1;
				if (!inq[e[now].to]) {
					inq[e[now].to]=1;
					q[(t++)&MOD]=e[now].to;
				}
			}
		}
	}
	return 0;
}

int main() {
	read(n);read(m);
	for (int i=1,x,a,b;i<=m;i++) {
		read(x);read(a);read(b);
		if (x==1) {
			add(a,b,0);add(b,a,0);
		}
		else if (x==2) {
			if (a==b) {
				puts("-1");
				return 0;
			}
			add(a,b,1);
		}
		else if (x==3) {
			add(b,a,0);
		}
		else if (x==4) {
			if (a==b) {
				puts("-1");
				return 0;
			}
			add(b,a,1);
		}
		else {
			add(a,b,0);
		}
	}
	for (int i=1;i<=n;i++) {
		q[t]=i;t++;
		dis[i]=1;
		inq[i]=1;
	}
	if (spfa()) puts("-1");
	else {
		long long ans=0;
		for (int i=1;i<=n;i++) {
			ans+=dis[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}

