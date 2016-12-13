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
#define MAXD 20

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
}dp[MAXD];

int n,d;

int main() {
	scanf("%d%d",&n,&d);
	dp[0]=num(1);
	for (int i=1;i<=d;i++) {
		dp[i]=dp[i-1];
		for (int j=2;j<=n;j++) {
			dp[i]=dp[i]*dp[i-1];
		}
		dp[i]=dp[i]+num(1);
	}
	if (d==0) dp[0].print();
	else (dp[d]-dp[d-1]).print();
	return 0;
}

