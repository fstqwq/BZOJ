/*This is a source code from FirstLast*/
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
#define INF 0x1f1f1f1f
struct statu{
	int x,y;
	statu(){}
	statu(int a,int b):x(a),y(b){}
};

int xp,yp,xs,ys,ans=0;
int dis[105][105],dx[8]={2,2,1,1,-1,-1,-2,-2},dy[8]={1,-1,2,-2,2,-2,1,-1};

inline bool inrange(int x,int y) {
	return x && x<100 && y && y<100;
}

inline int bfs(int x,int y) {
	memset(dis,31,sizeof(dis));
	dis[x][y]=0;
	queue <statu> q;
	q.push(statu(x,y));
	while (!q.empty()) {
		int nowx=q.front().x,nowy=q.front().y;q.pop();
		if (nowx==40 && nowy==40) return dis[nowx][nowy];
		for (int i=0;i<8;i++) {
			int tox=nowx+dx[i],toy=nowy+dy[i];
			if (inrange(tox,toy) && dis[tox][toy]==INF) {
				dis[tox][toy]=dis[nowx][nowy]+1;
				q.push(statu(tox,toy));
			}
		}
	}
}
int main() {
	scanf("%d%d%d%d",&xp,&yp,&xs,&ys);
	int x=abs(xp-xs),y=abs(ys-yp);
	while (x+y>=50) {
		if (x<y) swap(x,y);
		if (x-4>(y<<1)) x-=4;
		else x-=4,y-=2;
		ans+=2;
	}
	printf("%d\n",bfs(x+40,y+40)+ans);
	return 0;
}

