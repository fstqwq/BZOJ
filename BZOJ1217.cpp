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
int ch;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

#define MAXN 10005

struct edge {
	int next,to;
}e[MAXN<<1];

int n,ecnt=0,f[MAXN],head[MAXN],label[MAXN];

void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
}

int q[MAXN];

void bfs() {
	int h=1,t=2;
	q[h]=1;
	f[1]=1;
	while (h<t) {
		int x=q[h++];
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].to!=f[x]) {
				f[e[now].to]=x;
				q[t++]=e[now].to;
			}
		}
	}
}

void mark(int x,int val) {
	if (val<=label[x]) return;
	label[x]=val;
	if (val) {
		for (int now=head[x];now;now=e[now].next) {
			mark(e[now].to,val-1);
		}
	}
}

int main() {
	read(n);
	for (int i=1,u,v;i<n;i++) {
		read(u);read(v);
		add(u,v);
		add(v,u);
	}
	bfs();
	memset(label,-1,sizeof(label));
	int ans=0;
	for (int i=n;i>0;i--) {
		if (label[q[i]]==-1) {
			mark(f[q[i]],1);
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}

