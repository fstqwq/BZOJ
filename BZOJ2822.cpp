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

#define MAXL 5005

struct num {
	int v[MAXL],len;
	num(){}
	void init() {
		memset(v,0,MAXL<<2);
		len=0;
	}
	num (int x) {
		init();
		while (x) {
			v[++len]=x%10;
			x/=10;
		}
	}
	num operator + (num a) const {
		num ret=a;
		ret.len=max(len,a.len);
		for (int i=1;i<=len;i++) {
			ret.v[i]+=v[i];
			if (ret.v[i]>9) {
				ret.v[i]-=10;
				ret.v[i+1]++;
			}
		}
		if (ret.v[ret.len+1]) ret.len++;
		return ret;
	}
	num operator - (num a) const {
		num ret=*this;
		for (int i=1;i<=a.len;i++) {
			ret.v[i]-=a.v[i];
			if (ret.v[i]<0) {
				ret.v[i]+=10;
				ret.v[i+1]--;
			}
		}
		for (int i=ret.len+1;i<len;i++) {
			if (ret.v[i]<0) {
				ret.v[i]+=10;
				ret.v[i+1]--;
			}
		}
		while (ret.v[ret.len]==0) ret.len--;
		return ret;
	}
	num operator * (num a) const {
		num ret(0);
		for (int i=1;i<=len;i++)
			for (int j=1;j<=a.len;j++) {
				ret.v[i+j-1]+=v[i]*a.v[j];
			}
		ret.len=len+a.len-1;
		for (int i=1;i<=ret.len;i++) {
			if (ret.v[i]>9) {
				int temp=ret.v[i]/10;
				ret.v[i+1]+=temp;
				ret.v[i]-=temp*10;
				if (i==ret.len) ret.len++;
			}
		}
		return ret;
	}
	num operator * (int a) const {
		num ret(0);
		for (int i=1;i<=len;i++) {
			ret.v[i]+=v[i]*a;
			if (ret.v[i]>9) {
				int temp=ret.v[i]/10;
				ret.v[i+1]+=temp;
				ret.v[i]-=temp*10;
			}
		}
		ret.len=len;
		while (ret.v[ret.len+1]) {
			ret.len++;
			if (ret.v[ret.len]>9) {
				int temp=ret.v[ret.len]/10;
				ret.v[ret.len+1]+=temp;
				ret.v[ret.len]-=temp*10;
			}
		}
		return ret;
	}
	num operator - (int x) const {
		num ret=*this;
		ret.v[1]-=x;
		for (int i=1;i<ret.len;i++) {
			if (ret.v[i]>=0) break;
			ret.v[i]+=10;
			ret.v[i+1]--;
		}
		if (ret.v[ret.len]==0) ret.len--;
		return ret;
	}
	void print() {
		for (int i=len;i;i--) putchar(v[i]+'0');
		putchar('\n');
	}
}ans(1);

#define MAXN 505

int n,pcnt=0,p[MAXN],minp[MAXN<<1],cnt[MAXN<<1];
bool notprime[MAXN<<1];

void init() {
	int nn=n<<1;
	for (int i=2;i<=nn;i++) {
		if (!notprime[i]) {
			p[++pcnt]=i;
			minp[i]=pcnt;
			for (int j=i*i;j<=nn;j+=i) {
				notprime[j]=1;
				if (!minp[j]) minp[j]=pcnt;
			}
		}
	}
}

void calc(int x,int v) {
	while (x!=1) {
		cnt[minp[x]]+=v;
		x/=p[minp[x]];
	}
}

int main() {
	scanf("%d",&n);
	init();
	for (int i=2*n;i>n+1;i--) calc(i,1);
	for (int i=n;i>0;i--) calc(i,-1);
	for (int i=1;i<=pcnt;i++) {
		while (cnt[i]) ans=ans*p[i],cnt[i]--;
	}
	ans.print();
	return 0;
}

