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
const int dx[]={1,-1,2,-2,1,-1,2,-2},dy[]={2,2,1,1,-2,-2,-1,-1};
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
int m,n,map[35][35],add[35][35],dis[35][35],sx,sy,ex,ey;
long long cnt[35][35];
bool inq[35][35];
bool inrange(int x,int y) {
	return x>0 && x<=m && y>0 && y<=n;
}

queue <int> q;
void spfa() {
	q.push((sx<<10)|sy);
	memset(dis,31,sizeof(dis));
	memset(add,31,sizeof(dis));
	dis[sx][sy]=0;
	add[sx][sy]=0;
	cnt[sx][sy]=1;
	while (!q.empty()) {
		int nowx=q.front()>>10,nowy=q.front()&1023;q.pop();
		inq[nowx][nowy]=0;
		for (int d=0;d<8;d++) {
			int tox=nowx+dx[d],toy=nowy+dy[d];
			if (!inrange(tox,toy) || map[tox][toy]==2) continue;
			int toadd=add[nowx][nowy]+(map[tox][toy]==0);
			if (toadd<add[tox][toy]) {
				add[tox][toy]=toadd;
				dis[tox][toy]=dis[nowx][nowy]+1;
				cnt[tox][toy]=cnt[nowx][nowy];
				if (!inq[tox][toy]) {
					inq[tox][toy]=1;
					q.push((tox<<10)|toy);
				}
			}
			else if (toadd==add[tox][toy]) {
				if (dis[nowx][nowy]+1<dis[tox][toy]) {
					dis[tox][toy]=dis[nowx][nowy]+1;
					cnt[tox][toy]=cnt[nowx][nowy];
					if (!inq[tox][toy]) {
						inq[tox][toy]=1;
						q.push((tox<<10)|toy);
					}
				}
				else if (dis[nowx][nowy]+1==dis[tox][toy]) {
					cnt[tox][toy]+=cnt[nowx][nowy];
					if (!inq[tox][toy]) {
						inq[tox][toy]=1;
						q.push((tox<<10)|toy);
					}
				}
			}
		}
	}
}

int main() {
	read(m);read(n);
	for (int i=1;i<=m;i++) 
		for (int j=1;j<=n;j++) {
			read(map[i][j]);
			if (map[i][j]==3) {
				sx=i,sy=j;
			}
			else if (map[i][j]==4) {
				ex=i,ey=j;
			}
		}
	spfa();
	if (add[ex][ey]>n*m) puts("-1");
	else printf("%d\n%d\n%lld\n",add[ex][ey],dis[ex][ey],cnt[ex][ey]);
	return 0;
}

