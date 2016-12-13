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
typedef unsigned long long LL;
#define MAXN 200005

struct query {
	int x,y,id;
	LL ha;
	bool operator < (query a) const {
		return y<a.y;
	}
}q[MAXN];
int n,m,k,tcnt=0;
int a[MAXN];
LL ha[MAXN],mi;
bool ans[MAXN];
LL hh(int l,int r) {
	LL ret=ha[r]-ha[l-1]*mi;
	return ret;
}
void getHash(LL &ret) {
	ret=0;
	for (int i=1,x;i<=k;i++) {
		read(x);
		ret=ret*19260817+x;
	}
}
map<LL,int> Tree;
int main() {
	read(n);read(m);read(k);
	ha[0]=0;
	for (int i=1;i<=n;i++) {
		read(a[i]);
		ha[i]=ha[i-1]*19260817+a[i];
	}
	mi=1;
	for (int i=1;i<=k;i++) mi=mi*19260817;
	for (int i=1;i<=m;i++) {
		read(q[i].x);read(q[i].y);getHash(q[i].ha);q[i].id=i;
	}
	sort(q+1,q+m+1);
	int i=k,j=1;
	while (j<=m && q[j].y<k) j++;
	for (;i<=n;i++) {
		Tree[hh(i-k+1,i)]=i;
		while (j<=m && q[j].y==i) {
			if (Tree[q[j].ha]>=q[j].x+k-1) ans[q[j].id]=1;
			j++;
		}
	}
	for (i=1;i<=m;i++) 
		if (ans[i]) puts("No");
		else puts("Yes");
	return 0;
}

