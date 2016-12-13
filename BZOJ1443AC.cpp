#include<cstdio>
#include<ctime>
#include<iostream>
int n,m;
char s[128][128];
int xs[]={-1,0,1,0};
int ys[]={0,-1,0,1};
int px[128][128],py[128][128],d[128][128],now,v[128][128],ed[128][128];
bool dfs(int x,int y){
    d[x][y]=now;
    if(px[x][y]&&d[px[x][y]][py[x][y]]!=now)return dfs(px[x][y],py[x][y]);
    for(int i=0;i<4;i++){
        int x1=x+xs[i],y1=y+ys[i];
        if(d[x1][y1]!=now&&s[x1][y1]=='.'&&!px[x1][y1]){
            px[x][y]=x1;py[x][y]=y1;
            px[x1][y1]=x;py[x1][y1]=y;
            return 1;
        }
    }
    for(int i=0;i<4;i++){
        int x1=x+xs[i],y1=y+ys[i];
        if(d[x1][y1]!=now&&s[x1][y1]=='.'&&dfs(x1,y1)){
            px[x][y]=x1;py[x][y]=y1;
            px[x1][y1]=x;py[x1][y1]=y;
            return 1;
        }
    }
    return 0;
}
void dfs2(int x,int y){
    if(ed[x][y]||s[x][y]!='.')return;
    ed[x][y]=1;
    v[x][y]=1;
    for(int i=0;i<4;i++){
        int x1=x+xs[i],y1=y+ys[i];
        if(px[x1][y1])dfs2(px[x1][y1],py[x1][y1]);
    }
}
int main(){
	freopen("read.in","r",stdin);
	freopen("ans.out","w",stdout);
	int a=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='.'&&!px[i][j]){
                ++now;
                a+=dfs(i,j);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='.'&&!px[i][j])v[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='.'&&!px[i][j])dfs2(i,j);
        }
    }
    bool win=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(v[i][j])win=1;
        }
    }
    puts(win?"WIN":"LOSE");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(v[i][j])printf("%d %d\n",i,j);
        }
	}
    return 0;
}
