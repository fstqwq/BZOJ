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
priority_queue<int,vector<int>,greater<int> > q;
int n;
long long ans=0;
int main() {
	scanf("%d",&n);
	for (int i=1,a;i<=n;i++) scanf("%d",&a),q.push(a);
	while (--n) {
		int t1=q.top();q.pop();
		t1+=q.top();q.pop();
		ans+=t1;
		q.push(t1);
	}
	printf("%lld\n",ans);
	return 0;
}

