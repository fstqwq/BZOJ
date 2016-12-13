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

#define MAXL 105
#define MAXN 105

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
	num operator * (num a) const {
		num ret(0);
		for (int i=1;i<=len;i++)
			for (int j=1;j<=a.len;j++) {
				ret.v[i+j-1]+=v[i]*a.v[j];
			}
		ret.len=len+a.len-1;
		for (int i=1;i<=ret.len;i++) {
			if (ret.v[i]>9) {
				ret.v[i+1]+=ret.v[i]/10;
				ret.v[i]%=10;
				if (i==ret.len) ret.len++;
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
}fib[MAXN],dp[MAXN];

int n;

int main() {
	scanf("%d",&n);
	fib[1]=num(1);
	fib[2]=num(3);
	dp[1]=num(1);
	dp[2]=num(5);
	for (int i=3;i<=n;i++) {
		fib[i]=fib[i-1]+fib[i-2];
		dp[i]=fib[i]*fib[i];
		if ((i&1)^1) dp[i]=dp[i]-4;
	}
	dp[n].print();
	return 0;
}

