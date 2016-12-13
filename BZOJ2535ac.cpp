#include<stdio.h>
#include<stdlib.h>
int k[2005]={0},f[2005]={0},s[2005]={0},v[10005]={0},first[2005]={0},next[10005]={0},heap[2005]={0},pos[2005]={0};
int n,e=0,node;
void tj(int x,int y)
{
    v[++e]=y;
    next[e]=first[x];
    first[x]=e;
}
void jh_heap(int a,int b)
{
    int t=heap[a];
    heap[a]=heap[b];
    heap[b]=t;
    t=pos[heap[a]];
    pos[heap[a]]=pos[heap[b]];
    pos[heap[b]]=t;
}
void tj_heap(int x)
{
    int i;
    heap[++node]=x;
    pos[x]=node;
    for(i=node;i>1;i/=2)
    {
        if(k[heap[i/2]]<k[heap[i]]) jh_heap(i/2,i);
        else return;
    }
}
void sc()
{
    int i=1;
    jh_heap(1,node);
    node--;
    while(i*2<=node)
    {
        i*=2;
        if(i+1<=node&&k[heap[i]]<k[heap[i+1]]) i++;
        if(k[heap[i/2]]<k[heap[i]]) jh_heap(i/2,i);
        else return;
    }
}
int work(int x)
{
    int i,j,t;
    node=0;
    for(i=1;i<=n;i++)
        f[i]=heap[i]=pos[i]=0;
    for(i=1;i<=e;i++)
        f[v[i]]++;
    for(i=1;i<=n;i++)
        if(f[i]==0&&i!=x) tj_heap(i);
    for(i=n;i>=1;i--)
    {
        if(node==0) return n-i;
        t=heap[1];
        sc();
        if(k[t]<i) return n-i;
        s[i]=t;
        for(j=first[t];j!=0;j=next[j])
            if(--f[v[j]]==0&&v[j]!=x) tj_heap(v[j]);
    }
    return n;
}
int main()
{
    int m,i,a,b;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%d",&k[i]);
    for(i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        tj(b,a);//·´½¨ÍØÆËÍ¼ 
    }
    work(0);
    /*for(i=1;i<=n;i++)
    {
        printf("%d",s[i]);
        if(i<n) printf(" ");
        else printf("\n");
    }*/
    for(i=1;i<=n;i++)
    {
        printf("%d",n-work(i));
        if(i<n) printf(" ");
    }
    return 0;
}
