/*ID: lpjwork1
TASK: butter
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
struct Edge{
	int v,val;
	int nxt;
};
const int MAXV=800,MAXE=1450,MAXN=500,INF=(1<<30);
queue<int> q;
int V,E,N,tot=0;
int head[MAXV+1],dist[MAXV+1][MAXV+1],cows[MAXN+1];
Edge e[MAXE*2+10];
bool inq[MAXV+1];
void spfa(int);
void addedge(int,int,int);
ofstream fout ("butter.out");
ifstream fin ("butter.in");
int main() {
	for (int i=0;i<=V;i++)	head[i]=0;
	fin>>N>>V>>E;
	for (int i=1;i<=N;i++)	fin>>cows[i];
	for (int i=1;i<=E;i++)
	{
		int u,v,val;fin>>u>>v>>val;
		addedge(u,v,val);
		addedge(v,u,val);
	}
	for (int i=1;i<=V;i++)	spfa(i);
	int ans=INF;
	/*
	for (int i=1;i<=V;i++)
	{
		for (int j=1;j<=V;j++)
			cout<<dist[i][j]<<' ';
		cout<<endl;
	}
	*/
	for (int i=1;i<=V;i++)
	{
		int sum=0;
		for (int j=1;j<=N;j++)	sum+=dist[i][cows[j]];
		ans=min(ans,sum);
	}
	cout<<ans<<endl;
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void spfa(int sor)
{
	memset(inq,false,sizeof(inq));
	for (int i=0;i<=V;i++)	dist[sor][i]=INF;
	while (!q.empty())	q.pop();
	q.push(sor);
	dist[sor][sor]=0;inq[sor]=true;
	while (!q.empty())
	{
		int now=q.front();q.pop();inq[now]=false;
		for (int i=head[now];i;i=e[i].nxt)
		{
			int v=e[i].v,val=e[i].val;
			if (dist[sor][now]+val<dist[sor][v]){
				dist[sor][v]=dist[sor][now]+val;
				if (!inq[v]){
					inq[v]=true;q.push(v);
				}
			}
		}
	}
}

void addedge(int u,int v,int val)
{
	e[++tot].v=v;e[tot].val=val;
	e[tot].nxt=head[u];head[u]=tot;
}
