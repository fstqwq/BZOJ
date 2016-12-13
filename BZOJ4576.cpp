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
#define MAXN 300005
int n,ans=0,a[MAXN],f[66][MAXN];
int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	for (int i=1;i<=n;i++) f[a[i]][i]=i+1;
	for (int i=2;i<=59;i++)
		for (int j=1;j<=n;j++) {
			if (!f[i][j]) f[i][j]=f[i-1][f[i-1][j]];
			if (f[i][j]) ans=i;
		}
	printf("%d\n",ans);
}


