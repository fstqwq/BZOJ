/*  Never stop fighting for what you believe in.    */
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
inline void readop(int &a) {
    while (ch!='Q' && ch!='B') ch=getchar();
    a=(ch=='Q');
    ch=getchar();
}
#define MAXN 300005
struct node {
    int lch,rch,v;
}t[MAXN<<5];
 
int n,m,q,tcnt=0,a[MAXN],rev[MAXN],rt[MAXN],f[MAXN];
 
int update(int x,int l,int r,int p) {
    int now=++tcnt;
    t[now].lch=t[x].lch;
    t[now].rch=t[x].rch;
    t[now].v=t[x].v+1;
    if (l!=r) {
        int mid=(l+r)>>1;
        if (p<=mid) t[now].lch=update(t[x].lch,l,mid,p);
        else t[now].rch=update(t[x].rch,mid+1,r,p);
    }
    return now;
}
int merge_tree(int x,int y) {
    if (!x) return y;
    if (!y) return x;
    t[x].lch=merge_tree(t[x].lch,t[y].lch);
    t[x].rch=merge_tree(t[x].rch,t[y].rch);
    t[x].v+=t[y].v;
    return x;
}
 
int getf(int x) {
    if (f[x]<0) return x;
    return f[x]=getf(f[x]);
}
 
void merge(int u,int v) {
    int fu=getf(u),fv=getf(v);
    if (fu!=fv) {
        if (f[fu]<f[fv]) {
            rt[fu]=merge_tree(rt[fu],rt[fv]);
            f[fu]+=f[fv];
            f[fv]=fu;
        }
        else {
            rt[fv]=merge_tree(rt[fv],rt[fu]);
            f[fv]+=f[fu];
            f[fu]=fv;
        }
    }
}
 
int kth_element(int x,int l,int r,int k) {
    if (l==r) return l;
    int mid=(l+r)>>1;
    if (t[t[x].lch].v>=k) {
        return kth_element(t[x].lch,l,mid,k);
    }
    else {
        return kth_element(t[x].rch,mid+1,r,k-t[t[x].lch].v);
    }
}
 
int main() {
//  freopen("read.in","r",stdin);
//  freopen("ans.out","w",stdout);
    read(n);read(m);
    memset(f,-1,sizeof(f));
    for (int i=1;i<=n;i++) {
        read(a[i]);
        rev[a[i]]=i;
        rt[i]=update(0,1,n,a[i]);
    }
    for (int i=1,x,y;i<=m;i++) {
        read(x);read(y);
        merge(x,y);
    }
    read(q);
    for (int i=1,op,x,y;i<=q;i++) {
        readop(op);read(x);read(y);
        if (op) {
            int fx=getf(x);
            if (-f[fx]<y) puts("-1");
            else printf("%d\n",rev[kth_element(rt[fx],1,n,y)]);
        }
        else {
            merge(x,y);
        }
    }
    return 0;
}
