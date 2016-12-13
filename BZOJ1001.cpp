#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;
#define MAXN 1005
#define s 2097152
#define INF 0x1f1f1f1f
#define MAX_BUF_SIZE 10485765

int ch=0;

inline int readInt(void) {
    while (ch < '0' || ch > '9') ch=getchar();
    int r=0;
    while (ch>='0' && ch<='9') {r = r * 10 + ch - '0';ch=getchar();}
    return r;
}

/* Main */
struct edge {
	int next,to,w;
}e[8000005];
int n,m,ecnt=0,src,sink,nm;
int dis[2*MAXN*MAXN],head[2*MAXN*MAXN],t[s<<1];
int row[MAXN][MAXN],col[MAXN][MAXN],slp[MAXN][MAXN],tag[MAXN][MAXN][2];
bool visit[2*MAXN*MAXN];
inline void add(int u,int v,int w) {
//	printf("%d->%d %d\n",u,v,w);
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].w=w;
	head[v]=ecnt;
}

/*inline void build() {
	nm=(n-1)*(m-1);
	src=0,sink=2*nm+1;
//	puts("A");
	for (int i=nm+1,lab=1;i<sink;i+=m-1,lab++) {
		add(src,i,col[lab][1]);
	}
//	puts("B");
	for (int i=sink-m+1,lab=1;i<sink;i++,lab++) {
		add(src,i,row[n][lab]);
	}
//	puts("C");
	for (int i=1;i<m;i++) {
		add(i,sink,row[1][i]);
	}
//	puts("D");
	for (int i=n,lab=1;i<sink-nm;i+=m-1,lab++) {
		add(i,sink,col[lab][m]);
	}
//	puts("E");
	// row
	for (int i=2;i<n;i++) {
		int from=nm+(i-2)*(m-1)+1,to=(i-1)*(m-1)+1;
		for (int j=1;j<m;j++,from++,to++) {
			add(from,to,row[i][j]);
		}
	}
//	puts("F");
	// col
	for (int j=2;j<m;j++) {
		int from=j-1,to=j+nm;
		for (int i=1;i<n;i++,from+=m-1,to+=m-1) {
			add(from,to,row[i][j]);
		}
	}
//	puts("G");
	// slope
	for (int i=1;i<n;i++) {
		int tag=1+(i-1)*(m-1);
		for (int j=1;j<m;j++,tag++) {
			add(tag,tag+nm,slp[i][j]);
		}
	}
//	puts("H");
}*/

void build2() {
	src=0,sink=1;
	int cnt=1;
	for (int i=1;i<n;i++) {
		for (int j=1;j<m;j++) {
			tag[i][j][0]=++cnt;
			tag[i][j][1]=++cnt;
		}
	}
	for (int i=1;i<m;i++) {
		add(tag[1][i][0],sink,row[1][i]);
	}
	for (int i=1;i<n;i++) {
		add(tag[i][m-1][0],sink,col[i][m]);
	}
	for (int i=1;i<n;i++) {
		add(tag[i][1][1],src,col[i][1]);
	}
	for (int i=1;i<m;i++) {
		add(tag[n-1][i][1],src,row[n][i]);
	}
	for (int i=2;i<n;i++)
		for (int j=1;j<m;j++) {
			add(tag[i-1][j][1],tag[i][j][0],row[i][j]);
		}
	for (int j=2;j<m;j++) {
		for (int i=1;i<n;i++) {
			add(tag[i][j-1][0],tag[i][j][1],col[i][j]);
		}
	}
	for (int i=1;i<n;i++)
		for (int j=1;j<m;j++) {
			add(tag[i][j][0],tag[i][j][1],slp[i][j]);
		}
}

inline void update(int x,int d) {
    t[x+=s]=d;
    for (x>>=1;x;x>>=1) t[x]=min(t[x<<1],t[(x<<1)|1]);
}

inline int query() {
    int x=1;
    while (x<s) {
        if (t[x<<1]<t[(x<<1)|1])
            x<<=1;
        else
            x=(x<<1)|1;
    }
    return x-s;
}
  

inline void dijkstra() {
	memset(dis,31,sizeof(dis));
	memset(t,31,sizeof(t));
	update(src,0);
	int x=src;
	while (t[x+s]<INF) {
		dis[x]=t[x+s];
		update(x,INF);
		visit[x]=1;
		if (x==sink) return;
		for (int now=head[x],v;now;now=e[now].next) {
            v=e[now].to;
            if (!visit[v] && dis[x]+e[now].w<t[s+v]) {
                update(v,dis[x]+e[now].w);
            }
        }
        x=query();
	}
}

int main() {
	n=readInt();
	m=readInt();
	if(n==1 || m==1) {
		if(n>m) swap(n, m);
		int ans=INF;
		for(int i=1, a; i<m; i++) {
			a=readInt();
			if(ans>a) ans=a;
		}
		printf("%d\n", ans==INF?0:ans);
		return 0;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<m;j++) {
			row[i][j]=readInt();
		}
	for (int i=1;i<n;i++)
		for (int j=1;j<=m;j++) {
			col[i][j]=readInt();
		}
	for (int i=1;i<n;i++)
		for (int j=1;j<m;j++) {
			slp[i][j]=readInt();
		}
	build2();
	dijkstra();
	printf("%d\n",dis[sink]);
	return 0;
}



