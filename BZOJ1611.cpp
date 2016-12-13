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
const int dx[]={0,0,0,1,-1},dy[]={0,1,-1,0,0};
int map[305][305];
int dis[305][305];

int n;
void mark(int x,int y,int c) {
	for (int i=0;i<=4;i++) {
		int tox=x+dx[i],toy=y+dy[i];
		map[tox][toy]=min(map[tox][toy],c);
	}
}
struct statu {
	int x,y;
	statu(){}
	statu(int a,int b):x(a),y(b){}
};
queue<statu> q;

int main() {
	memset(map,31,sizeof(map));
	memset(dis,31,sizeof(dis));
	scanf("%d",&n);
	for (int i=1,x,y,c;i<=n;i++) {
		scanf("%d%d%d",&x,&y,&c);
		mark(x+1,y+1,c-1);
	}
	if (map[1][1]<0) {
		puts("-1");
		return 0;
	}
	dis[1][1]=0;
	q.push(statu(1,1));
	while (!q.empty()) {
		int x=q.front().x,y=q.front().y;q.pop();
		if (map[x][y]==0x1f1f1f1f) {
			printf("%d\n",dis[x][y]);
			return 0;
		}
		for (int d=1;d<=4;d++) {
			int tox=x+dx[d],toy=y+dy[d];
			if (tox && toy && dis[tox][toy]==0x1f1f1f1f && map[tox][toy]>dis[x][y]) {
				dis[tox][toy]=dis[x][y]+1;
				q.push(statu(tox,toy));
			}
		}
	}
	puts("-1");
	return 0;
}

