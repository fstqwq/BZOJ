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
#define MAXN 10005
struct edge {
	int next,to;
}e[MAXN];
int n,m,ecnt=0;
int in[MAXN],head[MAXN],s[MAXN],K[MAXN],scnt=0;
void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
}
struct statu {
	int x,v;
	statu(){}
	statu(int a,int b):x(a),v(b){}
	bool operator < (statu a) const {
		return v<a.v;
	}
};
priority_queue<statu> q;
void work_1() {
	for (int i=1;i<=ecnt;i++) in[e[i].to]++;
	for (int i=1;i<=n;i++) if (!in[i]) q.push(statu(i,K[i]));
	while (!q.empty()) {
		int x=q.top().x;q.pop();
		s[++scnt]=x;
		for (int now=head[x];now;now=e[now].next) {
			if (--in[e[now].to]==0) {
				q.push(statu(e[now].to,K[e[now].to]));
			}
		}
	}
	for (int i=n;i;i--) {
		printf("%d ",s[i]);
	}
	putchar('\n');
}

int work_2(int xx) {
	for (int i=1;i<=n;i++) in[i]=0;
	for (int i=1;i<=ecnt;i++) in[e[i].to]++;
	while (!q.empty()) q.pop();
	for (int i=1;i<=n;i++) if (!in[i] && i!=xx) q.push(statu(i,K[i]));
	for (int kkk=n;kkk>=1;kkk--) {
		if (q.empty()) return n-kkk;
		int x=q.top().x;q.pop();
		if (K[x]<kkk) return n-kkk;
		for (int now=head[x];now;now=e[now].next) {
			if (--in[e[now].to]==0 && e[now].to!=xx) {
				q.push(statu(e[now].to,K[e[now].to]));
			}
		}
	}
	return n;
}


int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) {
		read(K[i]);
	}
	for (int i=1,u,v;i<=m;i++) {
		read(v);read(u);
		add(u,v);
	}
	work_1();
	for (int i=1;i<=n;i++) {
		printf("%d",n-work_2(i));
		if (i<n) printf(" ");
	}
	return 0;
}

