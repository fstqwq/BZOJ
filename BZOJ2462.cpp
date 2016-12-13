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
#include <bitset>
#define MAXN 1005
#define P1 19260817
#define MOD 100000009
typedef long long LL;
using namespace std;
int n,m,A,B,q;
LL pp=1000000007,pA,pB;
int wtf,ha[MAXN][MAXN],hha[MAXN][MAXN];
char s[MAXN];
bitset<MOD> hhh;

int main() {
	scanf("%d%d%d%d",&n,&m,&A,&B);
	pB=1;
	for (int i=1;i<=B;i++) {
		pB<<=1;
		if (pB>P1) pB-=P1;
	}
	pA=1;
	for (int i=1;i<=A;i++) pA=(pA*pp)%MOD;
	for (int i=1;i<=n;i++) {
		scanf("%s",s+1);
		ha[i][0]=0;
		for (int j=1;j<=m;j++) {
			ha[i][j]=ha[i][j-1]<<1;
			if (s[j]=='1') ha[i][j]|=1;
			if (ha[i][j]>P1) ha[i][j]-=P1;
		}
	}
	for (int i=1;i<=n;i++) 
		for (int j=B;j<=m;j++) {
			hha[i][j]=(ha[i][j]-pB*ha[i][j-B])%P1;
			if (hha[i][j]<0) hha[i][j]+=P1;
		}
	memset(ha,0,sizeof(ha));
	for (int j=B;j<=m;j++) {
		for (int i=1;i<=n;i++) {
			ha[i][j]=(ha[i-1][j]*pp+hha[i][j])%MOD;
		}
	}
	memset(hha,0,sizeof(hha));
	for (int i=A;i<=n;i++)
		for (int j=B;j<=m;j++) {
			hha[i][j]=(ha[i][j]-ha[i-A][j]*pA)%MOD;
			if (hha[i][j]<0) hha[i][j]+=MOD;
			hhh[hha[i][j]]=true;
		}
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		int val=0;
		for (int j=1;j<=A;j++) {
			scanf("%s",s+1);
			int tmp=0;
			for (int k=1;k<=B;k++) {
				tmp<<=1;
				if (s[k]=='1') tmp|=1;
				if (tmp>P1) tmp-=P1;
			}
			val=int((val*pp+tmp)%MOD);
		}
		if (hhh[val]) puts("1");
		else puts("0");
	}

	return 0;
}

