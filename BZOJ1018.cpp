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

#define MAXN 100005
#define MAXM 100005

#define MAX_BUF_SIZE 8388608
char buf[MAX_BUF_SIZE],wbuf[MAX_BUF_SIZE],*ptr,*ptw;
inline void init_buf() {
    fread(buf,sizeof(char),MAX_BUF_SIZE,stdin);
    ptr=buf;
	ptw=wbuf;
}
inline void write_buf() {
    fwrite(wbuf,sizeof(char),ptw-wbuf,stdout);
}
#define getchar() (*(ptr++))
#define putchar(x) (*(ptw++)=x)

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

inline bool readop(int &a) {
	while (ch<'A' || ch>'Z') ch=getchar();
	if (ch=='E') return 0;
	if (ch=='O') a=1;
	if (ch=='C') a=2;
	if (ch=='A') a=3;
	while (ch!=' ') ch=getchar();
	return 1;
}
struct ri {
	int op,c1,c2;
}rr[MAXM];

struct node {
	int l,r,lch,rch,head;
	bool hasq;
}t[262144];

struct infomation {
	int c1,c2,next;
}info[MAXM<<5];

struct recover {
	int tag,val,next;
	recover(){}
	recover(int a,int b,int c):tag(a),val(b),next(c){}
}sta[MAXM<<5];

int c,m=0,root,tcnt=0,statop=0,icnt=0;
int visit[MAXM<<2],f[MAXN<<2];

int build(int l,int r) {
	int now=++tcnt;
	t[now].l=l,t[now].r=r;
	if (l<r) {
		int mid=(l+r)>>1;
		t[now].lch=build(l,mid);
		t[now].rch=build(mid+1,r);
		t[now].hasq=t[t[now].lch].hasq|t[t[now].rch].hasq;
	}
	else {
		if (rr[l].op==3) t[now].hasq=1;
	}
	return now;
}

inline int gettag(int x,int y) {
	if (y-x==1) return x;
	else return x+262144;
}

int A,B;
void add_query(int x,int l,int r) {
	if (t[x].l==l && t[x].r==r) {
		info[++icnt].c1=A;
		info[icnt].c2=B;
		info[icnt].next=t[x].head;
		t[x].head=icnt;
		return;
	}
	int mid=(t[x].l+t[x].r)>>1;
	if (l<=mid) add_query(t[x].lch,l,min(r,mid));
	if (r>mid) add_query(t[x].rch,max(mid+1,l),r);
}

int getf(int x) {
	if (f[x]<0) return x;
	return getf(f[x]);
}

int merge(int head,int c1,int c2) {
	int f1=getf(c1),f2=getf(c2);
	if (f1!=f2) {
		sta[++statop]=recover(f1,f[f1],head);
		head=statop;
		sta[++statop]=recover(f2,f[f2],head);
		head=statop;
		if (f[f1]<f[f2]) {
			f[f1]+=f[f2];
			f[f2]=f1;		
		}
		else {
			f[f2]+=f[f1];
			f[f1]=f2;
		}
	}
	return head;
}

bool is_same(int c1,int c2) {
	int f1=getf(c1),f2=getf(c2);
	return f1==f2;
}

int change(int x) {
	int head=0;
	for (int now=t[x].head;now;now=info[now].next) {
		head=merge(head,info[now].c1,info[now].c2);
	}
	return head;
}

void rec(int head) {
	for (int now=head;now;now=sta[now].next) {
		f[sta[now].tag]=sta[now].val;
	}
}

void dfs(int x) {
	int head=change(x);
	if (t[x].l==t[x].r) {
		if (is_same(rr[t[x].l].c1,rr[t[x].l].c2)) putchar('Y'),putchar('\n');
		else putchar('N'),putchar('\n');
	}
	else {
		if (t[t[x].lch].hasq) dfs(t[x].lch);
		if (t[t[x].rch].hasq) dfs(t[x].rch);
	}
	rec(head);
}

int main() {
	init_buf();
	read(c);
	m=1;
	while (readop(rr[m].op)) {
		int r1,c1,r2,c2;
		read(r1);read(c1);read(r2);read(c2);
		rr[m].c1=((r1-1)<<17)+c1;
		rr[m].c2=((r2-1)<<17)+c2;
		if (rr[m].c1>rr[m].c2) swap(rr[m].c1,rr[m].c2);
		m++;
	}
	m--;
	if (m==0) return 0;
	if (m==1) {
		if (rr[1].op==3) puts("N");
		return 0;
	}
	root=build(1,m);
	for (int i=1;i<=m;i++) {
		int tag=gettag(rr[i].c1,rr[i].c2);
		if (rr[i].op==1) {
			if (!visit[tag]) visit[tag]=i;
		}
		else if (rr[i].op==2) {
			if (visit[tag]) {
				A=rr[i].c1;
				B=rr[i].c2;
				add_query(root,visit[tag],i);
				visit[tag]=0;
			}
		}
	}
	for (int i=1;i<=c;i++) {
		if (visit[i]) {
			A=i;
			B=i+1;
			add_query(root,visit[i],m);
		}
		if (visit[i+131072]) {
			A=i+131072;
			B=i+131073;
			add_query(root,visit[i+131072],m);
		}
		if (visit[i+262144]) {
			A=i;
			B=i+131072;
			add_query(root,visit[i+262144],m);
		}
	}
	memset(f,-1,sizeof(f));
	dfs(root);
	write_buf();
	return 0;
}

