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

#define MAXL 1253
#define MOD 100000000

char temp[MAXL*10];

struct num {
	int a[MAXL+5];
	num(){memset(a,0,sizeof(a));}
	int &operator [](int i) {return a[i];}
	void operator /=(int x) {
		for (int i=MAXL;i>=1;i--) {
			a[i-1]+=a[i]%x*MOD,a[i]/=x;
		}
	}
	void operator -=(num &b) {
		for (int i=1;i<=MAXL;i++) {
			a[i]=a[i]-b[i]+(a[i-1]+MOD)/MOD-1,a[i-1]=(a[i-1]+MOD)%MOD;
		}
	}
	void operator *=(int x) {
		for (int i=1;i<=MAXL;i++) {
			a[i]=a[i]*x+a[i-1]/MOD,a[i-1]%=MOD;
		}
	}
	bool operator < (num &b) {
		for (int i=MAXL;i>0;i--) {
			if (a[i]!=b[i]) return a[i]<b[i];
		}
		return 0;
	}
	bool iszero() {
		for (int i=1;i<=MAXL;i++) if (a[i]!=0) return 0;
		return 1;
	}
	void read() {
		for (int i=0;i<8;i++) temp[i]='0';
		scanf("%s",temp+8);
		int len=(int)strlen(temp+1),p=1;
		while (len-8*p+1>0) {
			sscanf(temp+len-8*p+1,"%8d",&a[p]);
			p++;
		}
	}
	void print() {
		int p=MAXL;
		while (!a[p] && p>0) p--;
		printf("%d",a[p--]);
		while (p>0) printf("%08d",a[p--]);
		printf("\n");
	}
}a,b;

num gcd(num x,num y) {
	int g=0;
	while (!x.iszero() && !y.iszero()) {
		bool xx=(x[1]&1)^1,yy=(y[1]&1)^1;
		if (xx&&yy) {g++;x/=2;y/=2;}
		else if (xx||yy) {
			if (xx) x/=2;
			else y/=2;
		}
		if (y<x) x-=y;
		else y-=x;
	}
	if (x<y) x=y;
	while (g--) x*=2;
	return x;
}


int main() {
	a.read();
	b.read();
	gcd(a,b).print();
	return 0;
}

