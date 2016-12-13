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
#define MAXN 100005
struct statu {
	int x,v;
	statu(){}
	statu(int a,int b):x(a),v(b){}
	bool operator < (statu a) const {
		return v>a.v;
	}
};
int n,k,ans=0;
int a[MAXN],next[MAXN],prev[MAXN];
bool visit[MAXN];
inline void del(int x) {
	prev[next[x]]=prev[x];
	next[prev[x]]=next[x];
	visit[x]=1;
}
priority_queue<statu> q;
void work() {
	for (int i=2;i<=n;i++) q.push(statu(i,a[i]));
	for (int i=1;i<=k;i++) {
		while (visit[q.top().x]) q.pop();
		int x=q.top().x;q.pop();
		ans+=a[x];
		a[x]=a[prev[x]]+a[next[x]]-a[x];
		del(prev[x]);del(next[x]);
		q.push(statu(x,a[x]));
	}
}

int main() {
	read(n);read(k);
	int xx,xxx;
	read(xx);
	for (int i=2;i<=n;i++) {
		read(xxx);
		a[i]=xxx-xx;
		xx=xxx;
		prev[i]=i-1;
		next[i]=i+1;
	}
	
	prev[1]=0;
	next[1]=2;
	prev[0]=0;
	next[0]=1;
	a[0]=a[1]=a[n+1]=a[n+2]=1000000001;
	prev[n+1]=n;
	prev[n+2]=n+1;
	next[n+1]=n+2;
	next[n+2]=n+2;
	work();
	printf("%d\n",ans);
	return 0;
}

