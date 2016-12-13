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

#define MAXN 805

struct edge {
	int next,to,flow;
}e[MAXN<<6];
const int source=0,sink=1;
int r,c,d,tot=0;
int ecnt=1,head[MAXN],tag[25][25],val[25][25],tt=0;
char temp[25];
int lab[MAXN];
bool visit[MAXN];
inline void add(int u,int v,int f) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=f;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=0;
	head[v]=ecnt;
}

void init() {
	scanf("%d%d%d",&r,&c,&d);
	for (int i=1;i<=r;i++) {
		scanf("%s",temp+1);
		for (int j=1;j<=c;j++) {
			val[i][j]=temp[j]-'0';
			tag[i][j]=(++tt)<<1;
			if (val[i][j]) {
				add(tag[i][j],tag[i][j]^1,val[i][j]);
			}
		}
	}
	for (int i=1;i<=r;i++) {
		scanf("%s",temp+1);
		for (int j=1;j<=c;j++) {
			if (temp[j]=='L') {
				add(0,tag[i][j],1);
				tot++;
			}
		}
	}
	for (int i=1;i<=r;i++)
		for (int j=1;j<=c;j++) {
			if (val[i][j] && (i-d<1 || i+d>r || j-d<1 || j+d>c)) {
				add(tag[i][j]^1,1,MAXN);
			}
		}
	for (int i=1;i<=r;i++)
		for (int j=1;j<=c;j++) {
			if (val[i][j]) {
				for (int k=1;k<=r;k++) {
					for (int l=1;l<=c;l++) {
						if (val[k][l] && (k-i)*(k-i)+(l-j)*(l-j)<=d*d) {
							add(tag[i][j]^1,tag[k][l],MAXN);
						}
					}
				}
			}
		}
}

queue <int> q;
bool bfs() {
	memset(lab,0,sizeof(lab));
	q.push(0);
	lab[0]=1;
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !lab[e[now].to]) {
				lab[e[now].to]=lab[x]+1;
				q.push(e[now].to);
			}
		}
	}
	if (lab[1]) return 1;
	else return 0;
}

int dfs(int x,int flow) {
	if (x==1) return flow;
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].flow && lab[e[now].to]>lab[x]) {
			int ret=dfs(e[now].to,min(flow,e[now].flow));
			if (ret) {
				e[now].flow-=ret;
				e[now^1].flow+=ret;
				return ret;
			}
		}
	}
	return 0;
}

void work() {
	int ans=0;
	while (bfs()) {
		int ret=dfs(0,MAXN);
		memset(visit,0,sizeof(visit));
		while (ret) {
			ans+=ret;
			ret=dfs(0,MAXN);
			memset(visit,0,sizeof(visit));
		}
	}
	printf("%d\n",tot-ans);
}

int main() {
	init();
	work();
	return 0;
}

