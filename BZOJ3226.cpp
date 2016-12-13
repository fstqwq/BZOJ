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
inline void readOP(int &a) {
	while (ch<'A' || ch>'Z') ch=getchar();
	a=ch;
}
inline void readRange(int &s,int &t) {
	bool flag1=0,flag2=0;
	while (ch!='(' && ch!='[') read(ch);
	if (ch=='(') flag1=1;
	read(s);read(t);
	while (ch!=')' && ch!=']') read(ch);
	if (ch==')') flag2=1;
	s=(s<<1)|flag1;
	t=(t<<1)-flag2;
}
int m,L=0,R=131072;

int main() {
	read(m);
	for (int i=1,x,s,t;i<=m;i++) {
		readOP(x);readRange(s,t);
		if (x=='U') fill(1,L,R,s,t);
		else if (x=='I') {
			if (s>L) clear(1,L,R,L,s-1);
			if (t<R) clear(1,L,R,t+1,R);
		}
		else if (x=='D') clear(1,L,R,s,t);
		else if (x=='C') {
			if (s>L) clear(1,L,R,L,s-1);
			if (t<R) clear(1,L,R,t+1,R);
			reverse(1,L,R,s,t);
		}
		else if (x=='S') {
			reverse(1,L,R,s,t);
		}
	}
	printAns();
	return 0;
}

