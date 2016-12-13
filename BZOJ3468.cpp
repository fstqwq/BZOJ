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


#define MAXN 305
#define MOD 12345

const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
struct data {
	int x,y,v;
	data(){}
	data(int a,int b,int c):x(a),y(b),v(c){}
	bool operator < (data a) const {
		return v<a.v;
	}
}d[MAXN*MAXN];

int n,m,cnt=0,K;
int a[MAXN][MAXN];
int f[MAXN][MAXN][205],z[205][205];

void init() {
	z[1][1]=1;
	for (int i=2;i<=K;i++) {
		for (int j=1;j<=i;j++) {
			z[i][j]=z[i-1][j-1]+z[i-1][j];
			if (z[i][j]>=MOD) z[i][j]-=MOD;
		}
	}
}

int main() {
	scanf("%d%d%d",&n,&m,&K);
	K++;
	init();
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			scanf("%d",a[i]+j);
			d[++cnt]=data(i,j,a[i][j]);
		}
		a[i][0]=a[i][m+1]=1234567890;
	}
	for (int i=1;i<=m;i++) a[0][i]=a[n+1][i]=1234567890;
	sort(d+1,d+cnt+1);
	for (int ii=1;ii<=cnt;ii++) {
		int x=d[ii].x,y=d[ii].y;
		for (int q=1;q<=K;q++) f[x][y][q]=1;
		for (int q=0;q<4;q++) {
			int tox=x+dx[q],toy=y+dy[q];
			if (a[tox][toy]<a[x][y]) {
				for (int i=1;i<=K;i++) {
					for (int j=1;j<=i;j++) {
						f[x][y][i]=(f[x][y][i]+f[tox][toy][j]*z[i][j])%MOD;
					}
				}
			}
		}
		for (int i=1;i<=K;i++) {
			printf("F %d %d %d = %d\n",x,y,i,f[x][y][i]);
		}
	}
	for (int ii=1;ii<=K;ii++) {
		int ans=0;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) {
				ans+=f[i][j][ii];
				if (ans>=MOD) ans-=MOD;
			}
		printf("%d\n",ans);
	}
	return 0;
}
