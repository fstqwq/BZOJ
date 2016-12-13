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

struct data {
	int L,W;
	char s[103][103];
	data():L(0),W(1){}
	char *operator [] (unsigned long long x) {return s[x];}
	void readline() {
		scanf("%s",s[++L]);
		int cnt=1;
		for (int i=0;s[L][i];i++) if (s[L][i]==',') cnt++;
		if (cnt>W) W=cnt;
	}
}a[105];

int n,maxlen=0,pos[105];
char ans[105][20005];
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		int x;scanf("%d",&x);a[i].readline();
		for (int j=1;j<=x;j++) a[i].readline();
		maxlen=max(maxlen,x);
	}
	maxlen++;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=maxlen;j++) {
			int cnt=1;
			for (int k=0;a[i][j][k];k++) {
				ans[j][++pos[j]]=a[i][j][k];
				if (a[i][j][k]==',') cnt++;
			}
			while (cnt++<=a[i].W) ans[j][++pos[j]]=',';
		}
	}
	for (int j=1;j<=maxlen;j++) {
		ans[j][pos[j]]='\0';
		puts(ans[j]+1);
	}
	return 0;
}

