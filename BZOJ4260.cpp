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

#define MAXN 400005
#define bitwise 29
struct trie_node {
	int l,r;
}t[MAXN*32];
int tcnt=0;
int n,a[MAXN],f[MAXN],g[MAXN];
void clear() {
	t[0].l=t[0].r=0;
	tcnt=0;
}
void insert(int x) {
	int now=0;
	for (int i=bitwise;i>-1;i--) {
		if ((x>>i)&1) {
			if (!t[now].l) t[now].l=++tcnt,t[tcnt].l=t[tcnt].r=0;
			now=t[now].l;
		}
		else {
			if (!t[now].r) t[now].r=++tcnt,t[tcnt].l=t[tcnt].r=0;
			now=t[now].r;
		}
	}
}
int query(int x) {
	int now=0,ret=0;
	for (int i=bitwise;i>-1;i--) {
		ret<<=1;
		if ((x>>i)&1) {
			if (!t[now].r) now=t[now].l;
			else now=t[now].r,ret|=1;
		}
		else {
			if (!t[now].l) now=t[now].r;
			else now=t[now].l,ret|=1;
		}
	}
	return ret;
}
int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	clear();
	f[0]=0;
	insert(0);
	for (int i=1,sum=0;i<=n;i++) {
		sum^=a[i];
		f[i]=max(f[i-1],query(sum));
		insert(sum);
	}
	clear();
	g[n+1]=0;
	insert(0);
	for (int i=n,sum=0;i>0;i--) {
		sum^=a[i];
		g[i]=max(g[i+1],query(sum));
		insert(sum);
	}
	int ans=0;
	for (int i=1;i<n;i++) {
		ans=max(ans,f[i]+g[i+1]);
	}
	printf("%d\n",ans);
	return 0;
}

