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
#include <set>
using namespace std;
#define MAXN 100005
#define INF 123456789012345ll
typedef long long LL;
struct data {
	LL x,y;
	int id;
	data(){}
	data(LL b):x(0),y(b),id(0){}
	bool operator < (data a) const {
		return y<a.y;
	}
}a[MAXN];
bool cmp(data q,data w) {
	return q.x<w.x;
}
int n,C,f[MAXN],ans,cnt[MAXN];
multiset<data> Tree;
multiset<data>::iterator it;
int getf(int x) {
	if (f[x]<0) return x;
	return f[x]=getf(f[x]);
}
void merge(int u,int v) {
	int fu=getf(u),fv=getf(v);
	if (fu!=fv) {
		if (f[fu]<f[fv]) {
			f[fu]+=f[fv];
			f[fv]=fu;
		}
		else {
			f[fv]+=f[fu];
			f[fu]=fv;
		}
		ans--;
	}
}

int main() {
	scanf("%d%d",&n,&C);
	ans=n;
	for (int i=1;i<=n;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		a[i].x=x+y;a[i].y=x-y;a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	memset(f,-1,sizeof(f));
	Tree.insert(a[1]);
	Tree.insert(data(-INF));Tree.insert(data(INF));
	for (int i=2,j=1;i<=n;i++) {
		while (a[i].x-a[j].x>C) {
			it=Tree.find(a[j]);
			Tree.erase(it);
			j++;
		}
		it=Tree.lower_bound(a[i]);
		data x=*it;
		if (x.y-a[i].y<=C) merge(a[i].id,x.id);
		x=*--it;
		if (a[i].y-x.y<=C) merge(a[i].id,x.id);
		Tree.insert(a[i]);
	}
	printf("%d ",ans);
	for (int i=1;i<=n;i++) cnt[getf(i)]++;
	int MAX=0;
	for (int i=1;i<=n;i++) MAX=max(cnt[i],MAX);
	printf("%d\n",MAX);
	return 0;
}

