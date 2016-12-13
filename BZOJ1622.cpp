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
#define MAXN 1005
int n,m,len[MAXN],cnt[MAXN],slen;
char a[MAXN][MAXN],s[MAXN];

bool check(int x) {
	for (int i=0,j=0;i<len[x];i++) {
		if (a[x][i]==s[j]) {
			j++;
			if (j==slen) return 1;
		}
	}
	return 0;
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%s",a[i]);
		len[i]=(int)strlen(a[i]);
		for (int j=0;j<len[i];j++) {
			if (a[i][j]>='a') a[i][j]-='a'-'A';
		}
	}
	for (int i=1;i<=m;i++) {
		scanf("%s",s);
		slen=(int)strlen(s);
		for (int j=0;j<slen;j++) {
			if (s[j]>='a') s[j]-='a'-'A';
		}
		for (int j=1;j<=n;j++) {
			if (check(j)) cnt[j]++;
		}
	}
	for (int i=1;i<=n;i++) {
		printf("%d\n",cnt[i]);
	}
	return 0;
}

