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
#define MAXN 105
#define MAXM 10005
int n,m,a[MAXM],map[105][105];

int main() {
	read(n);read(m);
	for (int i=1;i<=m;i++)read(a[i]);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			read(map[i][j]);
		}
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++) 
				if (map[j][k]>map[j][i]+map[i][k])
					map[j][k]=map[j][i]+map[i][k];
	int ans=0;
	a[0]=1;a[m+1]=n;
	for (int i=0;i<=m;i++) {
		ans+=map[a[i]][a[i+1]];
	}
	printf("%d\n",ans);
	return 0;
}

