/* Good Luck*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

int n,m,Q,U,V,t;
priority_queue <int> q;
void work() {
	for (int i=1,a;i<=n;i++) {
		read(a);
		q.push(a);
	}
	int nowtot=0;
	bool flag=0;
	for (int i=1,x,lena,lenb,opcnt=1;i<=m;i++,opcnt++) {
		x=q.top()+nowtot;q.pop();
		lena=int(LL(x)*U/V);lenb=x-lena;
		nowtot+=Q;
		q.push(lena-nowtot);q.push(lenb-nowtot);
		if (opcnt==t) {
			opcnt=0;
			if (flag) putchar(' ');
			else flag=1;
			printf("%d",x);
		}
	}
	putchar('\n');
	flag=0;
	for (int i=1,x,opcnt=1,ta=n+m;i<=ta;i++,opcnt++) {
		x=q.top()+nowtot;q.pop();
		if (opcnt==t) {
			opcnt=0;
			if (flag) putchar(' ');
			else flag=1;
			printf("%d",x);
		}
	}
	putchar('\n');
}
int a[100005];
queue <int> Que[3];
void work_QX() {
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	sort(a+1,a+n+1);
	for (int i=n;i>0;i--) Que[0].push(a[i]);
	bool flag=0;
	int nowtot=0;
	for (int i=1,x,tag,lena,lenb,opcnt=1;i<=m;i++,opcnt++) {
		x=-0x7fffffff;
		for (int j=0;j<3;j++) {
			if (!Que[j].empty() && Que[j].front()>x) {
				tag=j,x=Que[j].front();
			}
		}
		x+=nowtot;
		Que[tag].pop();
		nowtot+=Q;
		lena=int(LL(x)*U/V);lenb=x-lena;
		Que[1].push(lena-nowtot);Que[2].push(lenb-nowtot);
		if (opcnt==t) {
			opcnt=0;
			if (flag) putchar(' ');
			else flag=1;
			printf("%d",x);
		}
	}
	putchar('\n');
	flag=0;
	for (int i=1,x,tag,opcnt=1,ta=n+m;i<=ta;i++,opcnt++) {
		x=-0x7fffffff;
		for (int j=0;j<3;j++) {
			if (!Que[j].empty() && Que[j].front()>x) {
				tag=j,x=Que[j].front();
			}
		}
		Que[tag].pop();
		if (opcnt==t) {
			opcnt=0;
			if (flag) putchar(' ');
			else flag=1;
			printf("%d",x+nowtot);
		}
	}
}

int main() {
	read(n);read(m);read(Q);read(U);read(V);read(t);
	work_QX();
	return 0;
}


