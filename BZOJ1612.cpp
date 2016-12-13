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
#define MAXN 105
int ch;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}


int n,m,ans=0,map[MAXN][MAXN];
int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) map[i][i]=1;
	for (int i=1,u,v;i<=m;i++) {
		read(u);read(v);
		map[u][v]=1;
	}
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++) if (map[i][k])
			for (int j=1;j<=n;j++) if (map[k][j]) map[i][j]=1;
	for (int i=1;i<=n;i++) {
		int tot=0;
		for (int j=1;j<=n;j++) {
			if (map[i][j]||map[j][i]) tot++;
		}
		if (tot==n) ans++;
	}
	printf("%d\n",ans);
	return 0;
}

