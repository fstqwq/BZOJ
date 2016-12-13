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
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 505

struct data {
	int x,y,v;
	bool operator < (data a) const {
		return v<a.v;
	}
}d[MAXN*MAXN];

struct query {
	int x1,y1,x2,y2,k;
}q[60005];

int n,Q,dcnt=0,a[MAXN][MAXN],sum[MAXN][MAXN],f[60005],ans[60005];

int getf(int x) {
	if (f[x]==x) return x;
	return f[x]=getf(f[x]);
}

bool isin(int x,int y,int k) {
	return x>q[k].x1 && x<=q[k].x2 && y>q[k].y1 && y<=q[k].y2;
}

int main() {
	read(n);read(Q);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			read(d[++dcnt].v);
			d[dcnt].x=i,d[dcnt].y=j;
		}
	}
	sort(d+1,d+dcnt+1);
	for (int i=1;i<=Q;i++) {
		read(q[i].x1);read(q[i].y1);read(q[i].x2);read(q[i].y2);read(q[i].k);
		q[i].x1--;q[i].y1--;
		f[i]=i;
	}
	f[Q+1]=Q+1;
	for (int i=1;i<=n;i++) {
		int st=(i-1)*n;
		for (int j=1;j<=n;j++) {
			a[d[st+j].x][d[st+j].y]=1;
		}
		for (int x=1;x<=n;x++) {
			for (int y=1;y<=n;y++) {
				sum[x][y]=a[x][y]+sum[x-1][y]+sum[x][y-1]-sum[x-1][y-1];
			}
		}
		for (int w=getf(1);w<=Q;w=getf(w+1)) {
			int tot=sum[q[w].x2][q[w].y2]-sum[q[w].x1][q[w].y2]-sum[q[w].x2][q[w].y1]+sum[q[w].x1][q[w].y1];
			if (tot>=q[w].k) {
				int qqq=tot-q[w].k;
				for (int j=n;j;j--) {
					if (isin(d[st+j].x,d[st+j].y,w)) {
						if (!(qqq--)) {
							ans[w]=d[st+j].v;
						}
					}
				}
				f[w]=w+1;
			}
		}
	}
	for (int i=1;i<=Q;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}

