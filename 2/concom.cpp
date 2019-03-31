/*ID: lpjwork1
TASK: concom
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
const int MAXN=100,MAXE=10000;
struct Edge{
	int to,val;
	int nxt;
};
queue<int> q;
Edge e[MAXE+10];
int tot=1,N,M;
int controll[MAXN+10][MAXN+10],head[MAXN+10];
bool iscomp[MAXN+10],vis[MAXN+10];
void initial();
void addedge(int,int,int);
void spread(int);
ofstream fout ("concom.out");
ifstream fin ("concom.in");
int main() {
	initial();
	fin>>M;
	for (int i=1;i<=M;i++)
	{
		int u,v,val;
		fin>>u>>v>>val;
		iscomp[u]=iscomp[v]=true;
		addedge(u,v,val);
	}
	for (int i=1;i<=MAXN;i++)	
		if (iscomp[i])	spread(i);
	for (int i=1;i<=MAXN;i++)
		if (iscomp[i])
		for (int j=1;j<=MAXN;j++)
			if (i!=j&&controll[i][j]>50)	fout<<i<<' '<<j<<endl;
    fout.close();fin.close();
    return 0;
}

void addedge(int u,int v,int val)
{
	Edge temp={v,val,head[u]};
	e[++tot]=temp;
	head[u]=tot;
}

void spread(int company)
{
	while (!q.empty())	q.pop();
	memset(vis,false,sizeof(vis));
	q.push(company);
	while (!q.empty())
	{
		int now=q.front();q.pop();
		vis[now]=true;
		for (int i=head[now];i;i=e[i].nxt)
		{
			int v=e[i].to,val=e[i].val;
			controll[company][v]+=val;
			if (!vis[v]&&controll[company][v]>50)	q.push(v);
		}
	}
}

void initial()
{
	memset(head,0,sizeof(head));
	memset(iscomp,false,sizeof(iscomp));
	for (int i=1;i<=MAXN;i++)	memset(controll[i],0,sizeof(controll[i]));
}
