#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<map>
#include<vector>
#include<set>
#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cctype>
#include<cstring>
#include<stack>
using namespace std;
inline void read(int &x) {
	char c; bool flag=false;
	do c=getchar(); while(c!='-'&&(c<'0'||c>'9'));
	if(c=='-') flag=true,c=getchar(); x=c-'0';
	while('0'<=(c=getchar())&&c<='9') x=x*10+c-'0';
	if(flag) x=-x;
}
const int maxn=100010;
const int maxp=1e7;
struct Node {
	int l,r,cnt; long long val;
}t[maxn*50];
int m,n,root[maxn],cnt;
vector<int> I[maxn],R[maxn];
void update(int &r1,int r2,int l,int r,int pos,int val) {
	r1=++cnt; t[r1]=t[r2]; t[r1].cnt+=val; t[r1].val+=val*pos;
	if(l==r) return ;
	int mid=l+r>>1;
	if(pos<=mid) update(t[r1].l,t[r2].l,l,mid,pos,val);
	else update(t[r1].r,t[r2].r,mid+1,r,pos,val);
}
long long query(int rt,int l,int r,int k) {
	if(l==r) return 1LL*k*l;
	int mid=l+r>>1;
	if(t[t[rt].l].cnt>=k) return query(t[rt].l,l,mid,k);
	return t[t[rt].l].val+query(t[rt].r,mid+1,r,k-t[t[rt].l].cnt);
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(m),read(n);
	for(int i=1,s,e,p;i<=m;++i) {
		read(s),read(e),read(p);
		I[s].push_back(p);
		R[e].push_back(p); 
	}
	root[0]=0; t[0].l=t[0].r=t[0].val=t[0].cnt=0;
	for(int i=1,cur;i<=n;++i) {
		cur=root[i-1];
		for(int j=0;j<I[i].size();++j) update(cur,cur,1,maxp,I[i][j],1);
		for(int j=0;j<R[i-1].size();++j) update(cur,cur,1,maxp,R[i-1][j],-1);
		root[i]=cur;
	}
	long long pre=1;
	for(int i=1,k,x,a,b,c;i<=n;++i) {
		read(x),read(a),read(b),read(c);
		k=1+(a*pre+b)%c;
		if(k>=t[root[x]].cnt) pre=t[root[x]].val;
		else pre=query(root[x],1,maxp,k);
		printf("%lld\n",pre);
	}
	return 0;
}

