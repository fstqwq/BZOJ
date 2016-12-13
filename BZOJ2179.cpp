#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<sstream>
#include<stack>
#include<map>
#include<vector>
#include<set>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cstring>
#include<climits>
#define swap(x,y) x^=y;y^=x;x^=y
using namespace std;
inline void read(int &x) {
	char c;
	do c=getchar(); while(c<'0'||c>'9'); x=c-'0';
	while('0'<=(c=getchar())&&c<='9') x=x*10+c-'0';
}
inline void readx(int &x) {
	char c; int a=1;
	do c=getchar(); while((c<'0'||c>'9')&&c!='-');
	if(c=='-') a=-1,c=getchar(); x=c-'0';
	while('0'<=(c=getchar())&&c<='9') x=x*10+c-'0'; x*=a;
}
void out(int a) {
	if(a>9) out(a/10);
	putchar(a%10+'0');
}
inline void outx(int a) {
	if(a<0) putchar('-'),a=-a;
	out(a);
}
inline int abs(int x) {
	int y=x>>31;
	return (x+y)^y;
}
inline int max(int x,int y) {
	int m=(x-y)>>31;
	return y&m|x&~m;
}
inline int ave(int x,int y) {return (x&y)+((x^y)>>1); }
#define lim 10000
#define maxn 121000
struct LL {
	int a[maxn];
	inline void operator = (int x) {
		a[0]=0;
		while(x) a[++a[0]]=x%lim,x/=lim;
		if(!a[0]) a[0]=1;
	}
	inline void print() {
		printf("%d",a[a[0]]);
		if(a[a[0]]<0||a[a[0]]>=lim) cout<<"fky"<<endl;
		for(int i=a[0]-1;i;--i) {
			printf("%04d",a[i]); //width should be manualy changed
			if(a[i]<0||a[i]>=lim) cout<<"fky"<<endl;
		}
		printf("\n");
	}
	inline void read() {
		char s[maxn]; int len; a[0]=1; a[1]=0;
		scanf("%s",s); len=strlen(s);
		for(int i=len-1,now=1;i>=0;--i,now*=10) {
			if(now==lim) now=1,a[++a[0]]=0;
			a[a[0]]+=now*(s[i]-'0');
		}
		while(a[0]>1&&!a[a[0]]) --a[0];
	}
	void operator ++ () {
		++a[1]; a[a[0]+1]=0;
		for(int i=1;i<=a[0];++i)
			if(a[i]==lim) ++a[i+1];
			else break;
		if(a[a[0]+1]) ++a[0];
	}
	LL operator * (LL b)const {
		LL c; c.a[0]=a[0]+b.a[0]; c.a[1]=0; long long tmp=0;
		if(c.a[0]>=maxn) throw *this;
		for(int k=1;k<c.a[0];++k) {
			for(int i=max(1,k+1-b.a[0]),j=k+1-i;i<=a[0]&&j;++i,--j)
				tmp+=a[i]*b.a[j];
			tmp+=c.a[k]; c.a[k]=tmp%lim; c.a[k+1]=tmp/lim; tmp=0;
		}
		if(c.a[0]>1&&!c.a[c.a[0]]) --c.a[0];
		return c;
	}
	LL operator - (LL b)const { //support only biger-smaller
		LL c; c.a[0]=1;
		for(int i=1,x=0;i<=a[0];++i) {
			if(i>b.a[0]) b.a[i]=0;
			c.a[i]=a[i]-b.a[i]+x; x=0;
			if(c.a[i]<0) c.a[i]+=lim,x=-1;
			if(c.a[i]) c.a[0]=i;
		}
		return c;
	}
	LL operator ^ (int t) {
		LL c,a=*this; c=1;
		while(t) {
			if(t&1) c=a*c;
			a=a*a; t>>=1;
		}
		return c;
	}
};
//S[21]
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
//	int n,d; read(n); read(d);
//    if(d<=0) {printf("1"); return 0; }
//	S[0]=1;
//	for(int i=1;i<=d;i++) S[i]=S[i-1]^n,++S[i];
//	(S[d]-S[d-1]).print();
	int n;
	scanf("%d",&n);
	LL a,b;
	a.read(); b.read();
	//a.print(); b.print();
	(a*b).print();
	return 0;
}


