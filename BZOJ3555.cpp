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
#define MOD1 2147483647
#define MOD2 1000000007
using namespace std;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 30005
#define MAXM 205
typedef long long LL;
int n,m,ss;
LL frt[MAXN][MAXM],bak[MAXN][MAXM];
char s[MAXN][MAXM];
LL tmp[MAXN],ans=0;

int val(char x) {
	switch (x) {
		case '0' ... '9' : return x-'0';break;
		case 'a' ... 'z' : return x-'a'+10;break;
		case 'A' ... 'Z' : return x-'A'+36;break;
		case '_' : return 62;break;
		case '@' : return 63;break;
	}
	return -1;
}

void cal(int x) {
	frt[x][0]=0;
	for (int i=1;i<=m;i++) {
		frt[x][i]=(frt[x][i-1]*67+val(s[x][i]))%MOD1;
	}
	bak[x][m+1]=0;
	for (int i=m;i;i--) {
		bak[x][i]=(bak[x][i+1]*97+val(s[x][i]))%MOD2;
	}
}

int main() {
	read(n);read(m);read(ss);
	for (int i=1;i<=n;i++) {
		scanf("%s",s[i]+1);
		cal(i);
	}
	for (int i=1;i<=m;i++) {
		for (int j=1;j<=n;j++) {
			tmp[i]=(frt[j][i-1]<<31)+bak[j][i+1];
		}
		sort(tmp+1,tmp+n+1);
		int now=1;
		for (int j=2;j<=n;j++) {
			if (tmp[j]==tmp[j-1]) ans+=now,now++;
			else now=1;
		}
	}
	printf("%lld\n",ans);
	return 0;
}

