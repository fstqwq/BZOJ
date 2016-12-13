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
const int dx[]={1,-1,0,0,1,-1,1,-1},dy[]={0,0,1,-1,1,1,-1,-1};
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 705
struct point {
	int x,y,v;
	bool operator < (point a) const {
		return v>a.v;
	}
}p[MAXN*MAXN];
int n,m,pcnt=0,ans=0;
int map[MAXN][MAXN];
bool visit[MAXN][MAXN];
void dfs(int x,int y) {
	visit[x][y]=1;
	for (int d=0;d<8;d++) {
		int tox=x+dx[d],toy=y+dy[d];
		if (!visit[tox][toy] && map[tox][toy]<=map[x][y]) dfs(tox,toy);
	}
}

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			read(map[i][j]);
			p[++pcnt].x=i,p[pcnt].y=j,p[pcnt].v=map[i][j];
		}
	}
	for (int i=0;i<=n+1;i++) visit[i][0]=visit[i][m+1]=1;
	for (int i=1;i<=m;i++) visit[0][i]=visit[n+1][i]=1;
	sort(p+1,p+pcnt+1);
	for (int i=1;i<=pcnt;i++) {
		if (!visit[p[i].x][p[i].y]) {
			dfs(p[i].x,p[i].y);
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}

