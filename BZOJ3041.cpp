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
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
typedef long long LL;
int n;
int map[8][8],ans;
bool used[6],ansed;
LL now,lim;
#define istrue(x,y,z) (((x>>(y<<3))>>z)&1)
#define mark(x,y,z) (x|=((1ll<<(y<<3))<<z))
#define remove(x,y,z) (x&=(-1llu)^(((1ll<<(y<<3))<<z)))
#define inrange(x,y) (x>-1 && x<n && y>-1 && y<n)
void dfs(int x,int y,int c) {
	mark(now,x,y);
	remove(lim,x,y);
	for (int d=0;d<4;d++) {
		int tox=x+dx[d],toy=y+dy[d];
		if (inrange(tox,toy) && !istrue(now,tox,toy)) {
			if (map[tox][toy]==c) dfs(tox,toy,c);
			else mark(lim,tox,toy);
		}
	}
}

int get_dif() {
	memset(used,0,sizeof(used));
	int ret=0;
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			if (!istrue(now,i,j) && !used[map[i][j]]) {
				used[map[i][j]]=1;
				ret++;
			}
		}
	}
	return ret;
}

bool fill(int c) {
	bool flag=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) {
			if (istrue(lim,i,j) && map[i][j]==c) {
				flag=1;
				dfs(i,j,c);
			}
		}
	return flag;
}


void idas(int step) {
	int dfc=get_dif();
	if (!dfc) ansed=1;
	if (step+dfc>ans || ansed) return;
	LL nn=now,ll=lim;
	for (int i=0;i<=5;i++) {
		if (fill(i)) idas(step+1);
		now=nn,lim=ll;
	}
}

int main() {
	while (1) {
		scanf("%d",&n);
		if (!n) break;
		for (int i=0;i<n;i++) {
			for (int j=0;j<n;j++) {
				scanf("%d",map[i]+j);
			}
		}
		now=0,lim=0;
		dfs(0,0,map[0][0]);
		ansed=0;
		for (ans=0;;ans++) {
			idas(0);
			if (ansed) {printf("%d\n",ans);break;}
		}
	}
	return 0;
}

