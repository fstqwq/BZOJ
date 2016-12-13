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
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
int ch=0;
inline void read(int &a) {
	bool f=0;
	while (ch<'0' || ch>'9') {if (ch=='-') f=1;ch=getchar();}
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
	if (f) a=-a;
}

int tx,ty,n,dis[1024][1024];
bool map[1024][1024];
queue <int> q;
int bfs() {
	map[512][512]=1;
	dis[512][512]=0;
	q.push((512<<11)|512);
	while (!q.empty()) {
		int x=q.front()>>11,y=q.front()&2047;q.pop();
		if (x==tx && y==ty) return dis[x][y];
		for (int d=0;d<4;d++) {
			int tox=x+dx[d],toy=y+dy[d];
			if (tox && tox<1023 && toy && toy<1023 && !map[tox][toy]) {
				dis[tox][toy]=dis[x][y]+1;
				map[tox][toy]=1;
				q.push((tox<<11)|toy);
			}
		}
	}
	return -1;
}


int main() {
	read(tx);read(ty);read(n);
	tx+=512,ty+=512;
	memset(dis,0x3f,sizeof(dis));
	for (int i=1,a,b;i<=n;i++) {
		read(a);read(b);
		map[a+512][b+512]=1;
	}
	printf("%d\n",bfs());
	return 0;
}

