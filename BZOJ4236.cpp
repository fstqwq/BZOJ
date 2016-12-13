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
#include <map>
using namespace std;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

int n,ans=0;
char s[200005];
int cnt[3];
struct statu {
	int x,y,t;
	statu(){}
	statu(int a,int b,int c):x(a),y(b),t(c){}
	bool operator < (statu a) const {
		if (x!=a.x) return x<a.x;
		if (y!=a.y) return y<a.y;
		return t<a.t;
	}
	bool operator == (statu a) const {
		return x==a.x && y==a.y;
	}
}hh[200005];
int tot=0;
int val(char x) {
	if (x=='J') return 0;
	if (x=='O') return 1;
	return 2;
}
int main() {
	scanf("%d",&n);
	ans=0;
	scanf("%s",s+1);
	hh[++tot]=statu(0,0,0);
	for (int i=1;i<=n;i++) {
		cnt[val(s[i])]++;
		hh[++tot]=statu(cnt[2]-cnt[1],cnt[1]-cnt[0],i);
	}
	sort(hh+1,hh+tot+1);
	hh[0]=statu(hh[1].x-1,0,0);
	for (int i=1;i<=n;i++) {
		if (hh[i]==hh[i-1]) ans=max(ans,hh[i].t-hh[i-1].t),hh[i].t=hh[i-1].t;
	}
	printf("%d\n",ans);
	return 0;
}

