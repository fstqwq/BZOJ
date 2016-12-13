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

#define MAXN 2005

struct edge {
	int next,to,w,flow;
}e[10005];

const int src=0,sink=1;

int gcd(int a,int b) {
	if (b) return gcd(b,a%b);
	else return a;
}


int a,b;
int ecnt=1,head[MAXN];


void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].w=w;
	e[ecnt].flow=1;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].w=-w;
	e[ecnt].flow=0;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

void build() {
	for (int i=a;i<=b;i++) {
		add(src,i<<1,0);
		add((i<<1)^1,sink,0);
	}
	for (int y=a;y<b;y++)
		for (int x=y+1;x<=b;x++) {
			int z2=x*x-y*y,z=int(sqrt(z2));
			if (z2==z*z && gcd(y,z)==1) {
				add(x<<1,(y<<1)^1,x+y);
				add(y<<1,(x<<1)^1,x+y);
			}
		}
}
int dis[MAXN],pre[MAXN],pos[MAXN];
bool inq[MAXN];
queue <int> q;

bool spfa() {
	memset(dis,200,sizeof(dis));
	memset(pre,0,sizeof(pre));
	q.push(src);
	dis[src]=0;
	while (!q.empty()) {
		int x=q.front(),d=dis[x];q.pop();
		inq[x]=0;
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && dis[e[now].to]<d+e[now].w) {
				dis[e[now].to]=d+e[now].w;
				pre[e[now].to]=x;
				pos[e[now].to]=now;
				if (!inq[e[now].to]) {
					inq[e[now].to]=1;
					q.push(e[now].to);
				}
			}
		}
	}
	return (pre[sink]!=0);	
}

void work() {
	int p=0;
	long long ans=0;
	while (spfa()) {
		p++;
		ans+=dis[sink];
		for (int now=sink;now!=src;now=pre[now]) {
			e[pos[now]].flow--;
			e[pos[now]^1].flow++;
		}
	}
	cout<<p/2<<" "<<ans/2<<endl;
}

int main() {
	scanf("%d%d",&a,&b);
	build();
	work();
	return 0;
}

