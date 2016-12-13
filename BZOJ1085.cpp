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

const int dx[8]={2,2,1,1,-1,-1,-2,-2},dy[8]={-1,1,-2,2,-2,2,-1,1};

int t,ans;
int tar[5][5]={	{1,1,1,1,1},
				{2,1,1,1,1},
				{2,2,0,1,1},
				{2,2,2,2,1},
				{2,2,2,2,2}},map[5][5];
char s[10];
inline bool dfs(int step) {
	int x,y,h=0;
	for (int i=0;i<5;i++)
		for (int j=0;j<5;j++) {
			if (map[i][j]==0) x=i,y=j;
			else {
				if (map[i][j]!=tar[i][j]) h++;
			}
		}
	if (step+h>ans) return 0;
	if (step==ans) {
		if (h==0) return 1;
		else return 0;
	}
	for (int d=0;d<8;d++) {
		int tox=x+dx[d],toy=y+dy[d];
		if (tox>-1 && tox<5 && toy>-1 && toy<5) {
			swap(map[x][y],map[tox][toy]);
			if (dfs(step+1)) return 1;
			swap(map[x][y],map[tox][toy]);
		}
	}
	return 0;
}
inline void work() {
	for (int i=0;i<5;i++) {
		scanf("%s",s);
		for (int j=0;j<5;j++) {
			if (s[j]=='1') {
				map[i][j]=1;
			}
			else if (s[j]=='0') {
				map[i][j]=2;
			}
			else {
				map[i][j]=0;
			}
		}
	}
	for (ans=0;ans<=15;ans++) {
		if (dfs(0)) {
			printf("%d\n",ans);
			return;
		}
	}
	puts("-1");
}

int main() {
	scanf("%d",&t);
	while (t--) {
		work();
	}
	return 0;
}

