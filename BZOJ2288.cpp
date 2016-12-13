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
	bool f=0;
	while (ch<'0' || ch>'9') {if (ch=='-') f=1;ch=getchar();}
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
	if (f) a=-a;
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
int n,zcnt=0,cnt=0,m,ans=0;
int a[MAXN],next[MAXN],prev[MAXN];
bool visit[MAXN];
inline void del(int x) {
	prev[next[x]]=prev[x];
	next[prev[x]]=next[x];
	visit[x]=1;
}
priority_queue<statu> q;
void work() {
	for (int i=2;i<=cnt;i++) {
		q.push(statu(i,abs(a[i])));
	}
	for (int i=zcnt;i>m;i--) {
		while (visit[q.top().x]) {
			q.pop();
		}
		int x=q.top().x;q.pop();
		a[x]=a[prev[x]]+a[next[x]]+a[x];
		del(prev[x]);del(next[x]);
		q.push(statu(x,abs(a[x])));
	}
	for (int i=2;i<=cnt;i++) {
		if (!visit[i] && a[i]>0) ans+=a[i];
	}
}

int main() {
	read(n);read(m);
	read(a[2]);cnt=2;prev[2]=1;next[2]=3;if (a[2]>0) zcnt=1;
	for (int i=2,x;i<=n;i++) {
		read(x);
		if (abs(a[cnt])+abs(x)==abs(a[cnt]+x)) {a[cnt]+=x;continue;}
		a[++cnt]=x;
		if (a[cnt]>0) zcnt++;
		prev[cnt]=cnt-1;
		next[cnt]=cnt+1;
	}
	if (a[2]<=0) a[2]=-1000000001;
	prev[1]=0;
	next[1]=2;
	prev[0]=0;
	next[0]=1;
	if (a[cnt]<=0) a[cnt]=-1000000001;
	a[0]=a[1]=a[cnt+1]=a[cnt+2]=-1000000001;
	prev[cnt+1]=cnt;
	prev[cnt+2]=cnt+1;
	next[cnt+1]=cnt+2;
	next[cnt+2]=cnt+2;
	work();
	printf("%d\n",ans);
	return 0;
}


