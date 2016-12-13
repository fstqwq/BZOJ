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
typedef long long LL;
int ch=0;
template <class T> inline void read(T &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 50005
struct cow {
	int x,p;
	cow(){}
	cow(int a,int b):x(a),p(b){}
	bool operator < (cow a) const {
		return p<a.p;
	}
	bool operator > (cow a) const {
		return p>a.p;
	}
};
priority_queue<cow,vector<cow>,greater<cow> > disc,nodisc;
priority_queue<int,vector<int>,greater<int> > price;
int n,k,C[MAXN],P[MAXN];
bool visit[MAXN];
LL m;

int main() {
	read(n);read(k);read(m);
	for (int i=1;i<=n;i++) {
		read(P[i]);read(C[i]);
		disc.push(cow(i,C[i]));
		nodisc.push(cow(i,P[i]));
	}
	for (int i=1;i<=k;i++) price.push(0);
	int ans=n;
	for (int i=0;i<n;i++) {
		while (visit[nodisc.top().x]) nodisc.pop();
		while (visit[disc.top().x]) disc.pop();
		int Pri=nodisc.top().p,tag=0;
		if (!price.empty()) {
			int tt=disc.top().p+price.top();
			if (Pri>tt) Pri=tt,tag=1;
		}
		if (Pri>m) {ans=i;break;}
		m-=Pri;
		if (tag) {
			int x=disc.top().x;
			visit[x]=1;
			disc.pop();price.pop();
			price.push(P[x]-C[x]);
		}
		else {
			int x=nodisc.top().x;
			visit[x]=1;
			nodisc.pop();
		}
	}
	printf("%d\n",ans);
	return 0;
}

