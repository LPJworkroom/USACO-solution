/*ID: lpjwork1
TASK: comehome
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
#include<fstream>
using namespace std;
const int base='a'-1,capbase='A'-1,MAXN=26,INF=(1<<30);
int e[MAXN*2+1][MAXN*2+1],dist[MAXN*2+1];
bool havecow[MAXN*2+1];
int M,ans=INF;
bool iscap(char a)	{	return a>='A'&&a<='Z';	}
void spfa(int);
ofstream fout ("comehome.out");
ifstream fin ("comehome.in");
int main() {
	fin>>M;
	for (int i=1;i<=MAXN*2;i++)
		for (int j=1;j<=MAXN*2;j++)	e[i][j]=INF;
	for (int i=1;i<=MAXN*2;i++)	dist[i]=INF;
	for (int i=1;i<=MAXN*2;i++)	
		if (i>MAXN&&i!=2*MAXN)	havecow[i]=true;
		else					havecow[i]=false;
	for (int i=1;i<=M;i++)
	{
		char u,v;int val;
		fin>>u>>v>>val;
		if (iscap(u))	u=base+u-capbase+MAXN;
		if (iscap(v))	v=base+v-capbase+MAXN;
		u-=base;v-=base;
		e[u][v]=e[v][u]=min(e[u][v],val);
	}
	spfa(2*MAXN);
	int minind;
	for (int i=MAXN+1;i<2*MAXN;i++)
		if (dist[i]<ans){
			ans=dist[i];
			minind=i;
		}
	fout<<char(minind-MAXN+capbase)<<' '<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void spfa(int sor)
{
	bool inq[MAXN+1];memset(inq,false,sizeof(inq));
	queue<int> q;
	inq[sor]=true;dist[sor]=0;
	q.push(sor);
	while (!q.empty())
	{
		int now=q.front();q.pop();
		for (int i=1;i<=MAXN*2;i++)
		{
			if (i!=now&&dist[now]+e[now][i]<dist[i]){
				dist[i]=dist[now]+e[now][i];
				if (!inq[i])	q.push(i);
			}
		}
		inq[now]=false;
	}
}
