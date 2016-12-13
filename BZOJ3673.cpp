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

#define MAXN 20005

struct edge {
	int next,to;
}e[MAXN];

struct data {
	int q,a,b;
}qr[MAXN];

int n,m,ecnt=0,f[MAXN],ans[MAXN],head[MAXN],acf[MAXN];

void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
}

int lab[MAXN<<1],val[MAXN<<1],top=0;

int getf(int x) {
	if (f[x]==x) return f[x];
	return getf(f[x]);
}

void modify(int i,int v) {
	lab[++top]=i;
	val[top]=f[i];
	f[i]=v;
}

void merge(int a,int b) {
	int fa=getf(a),fb=getf(b);
	if (fa!=fb) {
		modify(fa,fb);
	}
}

void recover(int tt) {
	while (top!=tt) {
		f[lab[top]]=val[top];
		top--;
	}
}

bool issame(int u,int v) {
	return getf(u)==getf(v);
}

void dfs(int x) {
	// answer querys
	for (int v=x+1;v<=m && qr[v].q==3;ans[v]=issame(qr[v].a,qr[v].b),v++);
	for (int now=head[x];now;now=e[now].next) {
		int v=e[now].to;
		if (qr[v].q==1) {
			int rec=top;
			merge(getf(qr[v].a),getf(qr[v].b));
			dfs(v);
			recover(rec);
		}
		else {
			dfs(v);
		}
	}
}

int main() {
	memset(ans,-1,sizeof(ans));
	scanf("%d%d",&n,&m);
	for (int i=1,last=0;i<=m;i++) {
		scanf("%d",&qr[i].q);
		if (qr[i].q==1) {
			scanf("%d%d",&qr[i].a,&qr[i].b);
			add(last,i);
			last=i;
		}
		else if (qr[i].q==2){
			scanf("%d",&qr[i].a);
			add(acf[qr[i].a],i);
			last=i;
		}
		else {
			scanf("%d%d",&qr[i].a,&qr[i].b);
		}
		acf[i]=last;
	}
	for (int i=1;i<=n;i++) f[i]=i;
	dfs(0);
	for (int i=1;i<=m;i++) if (ans[i]!=-1) printf("%d\n",ans[i]);
	return 0;
}

