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

#define MAXN 200005

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}


struct node {
	int l,r,v;
}t[MAXN<<6];

int n,m,rt[MAXN],tcnt=0;

int build(int l,int r) {
	int now=++tcnt;
	if (l==r) {
		t[now].v=-1;
	}
	else {
		t[now].l=build(l,(l+r)>>1);
		t[now].r=build(((l+r)>>1)+1,r);
	}
	return now;
}

int access(int root,int x) {
	//printf("access %d %d\n",root,x);
	int l=1,r=n,mid,pos=root;
	while (l<r) {
//		printf("pos : %d\n",pos);
//		printf("%d %d\n",l,r);
		mid=(l+r)>>1;
		if (x<=mid) r=mid,pos=t[pos].l;
		else l=mid+1,pos=t[pos].r;
	}
	//printf("access complete %d \n",t[pos].v);
	return t[pos].v;
}

int modify(int old,int x,int v) {
	//printf("modify %d %d\n",x,v);
	int l=1,r=n,mid,now=++tcnt;
	int nowrt=now;
	while (l<r) {
		t[now].l=t[old].l;
		t[now].r=t[old].r;
		mid=(l+r)>>1;
		if (x<=mid) r=mid,t[now].l=tcnt+1,now=++tcnt,old=t[old].l;
		else l=mid+1,t[now].r=tcnt+1,now=++tcnt,old=t[old].r;
	}
	t[now].v=v;
	return nowrt;
}

int getf(int r,int x) {
	//printf("getf %d %d\n",r,x);
	int fx=access(r,x);
	if (fx<0) return x;
	else return getf(r,fx);
}

void merge(int r,int a,int b) {
	int fa=getf(rt[r],a);
	//printf("fa : %d\n",fa);
	int fb=getf(rt[r],b);
	//printf("fb : %d\n",fb);
	if (fa==fb) return;
	int ffa=access(rt[r],fa),ffb=access(rt[r],fb);
	//printf("ffa %d ffb %d\n",ffa,ffb);
	if (ffa<ffb) {
		int nowr=modify(rt[r],fa,ffa+ffb);
		rt[r]=modify(nowr,fb,fa);
	}
	else {
		int nowr=modify(rt[r],fb,ffa+ffb);
		rt[r]=modify(nowr,fa,fb);
	}
}

int query(int r,int a,int b) {
	int fa=getf(rt[r],a),fb=getf(rt[r],b);
	return fa==fb;
}

int main() {
	read(n);read(m);
	rt[0]=build(1,n);
	int lastans=0;
	for (int i=1,op,a,b;i<=m;i++) {
		read(op);
		if (op==1) {
			read(a);read(b);
			a^=lastans,b^=lastans;
			rt[i]=rt[i-1];
			merge(i,a,b);
		}
		else if (op==2) {
			read(a);
			a^=lastans;
			rt[i]=rt[a];
		}
		else {
			read(a);read(b);
			a^=lastans,b^=lastans;
			rt[i]=rt[i-1];
			lastans=query(i,a,b);
			putchar(lastans+'0');putchar('\n');
		}
	}
	return 0;
}

