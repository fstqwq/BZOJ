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
#define MAXN 210005

int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
struct point {
	int x,y;
	point(){}
	point(int a,int b):x(a),y(b){}
}p[405],d[405];

int n,m,dcnt=0,pcnt=0;
int map[25][25],st[25][25],dis[405][405];
char temp[25];

queue <point> qq;
bool bfs(int who) {
	bool flag=0;
	memset(st,-1,sizeof(st));
	st[p[who].x][p[who].y]=0;
	qq.push(p[who]);
	while (!qq.empty()) {
		point now=qq.front();qq.pop();
		int x=now.x,y=now.y;
		for (int d=0;d<4;d++) {
			int tox=dx[d]+x,toy=dy[d]+y;
			if (map[tox][toy] && st[tox][toy]==-1) {
				st[tox][toy]=st[x][y]+1;
				if (map[tox][toy]<0) {
					dis[who][-map[tox][toy]]=st[x][y]+1;
					flag=1;
				}
				else {
					qq.push(point(tox,toy));
				}
			}
		}
	}
	return flag;
}

#define MAXM 524288
struct edge {
	int next,to,flow;
}e[MAXM];

int head[MAXN],ecnt;
int tag[MAXN];
 
inline void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].flow=1;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].flow=0;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}
 
queue <int> q;
bool bfs() {
	memset(tag,0,sizeof(tag));
	tag[0]=1;
	q.push(0);
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[1]!=0;
}

bool dfs(int x) {
	if (x==1) return 1;
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].flow && tag[e[now].to]>tag[x]) {
			if (dfs(e[now].to)) {
				e[now].flow--;
				e[now^1].flow++;
				return 1;
			}
		}
	}
	return 0;
}

int dinic() {
	int ans=0;
	while (bfs()) {
		while (dfs(0)) {
			ans++;
		}
	}
	return ans;
}

bool check(int mid) {
	ecnt=1;
	memset(head,0,sizeof(head));
	for (int i=1;i<=pcnt;i++) {
		bool flag=1;
		for (int j=1;j<=dcnt;j++) {
			if (dis[i][j]<=mid) flag=0;
			for (int k=dis[i][j];k<=mid;k++) {
				add(i+1,(j<<9)+k);
			}
		}
		if (flag) return 0;
	}
	for (int i=1;i<=pcnt;i++) {
		add(0,i+1);
	}
	for (int i=1;i<=dcnt;i++) {
		for (int j=1;j<=mid;j++) {
			add((i<<9)+j,1);
		}
	}
	if (dinic()==pcnt) return 1;
	else return 0;
}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%s",temp+1);
		map[i][0]=0;
		for (int j=1;j<=m;j++) {
			if (temp[j]=='X') map[i][j]=0;
			else if (temp[j]=='.') {
				p[++pcnt]=point(i,j);
				map[i][j]=pcnt;
			}
			else {
				d[++dcnt]=point(i,j);
				map[i][j]=-dcnt;
			}
		}
		map[i][m+1]=0;
	}
	memset(dis,31,sizeof(dis));
	for (int i=1;i<=pcnt;i++) {
		if (!bfs(i)) {
			puts("impossible");
			return 0;
		}
	}
	int l=1,r=n*m,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}

