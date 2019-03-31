/*ID: lpjwork1
TASK: milk6
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
const int MAXN=32,MAXM=1000,INF=(1<<30);
struct Edge{
	int u,v,cap,ind;
	int num;
	int nxt;
} edge[MAXM*2+10];
vector<int> sortedge,ans;
int N,M,sor=1,tar,tot=1,flow=0;
int head[MAXN+10],fa[MAXN+10],dist[MAXN+10];;
Edge G[MAXM*2+10];
vector<vector<vector<int> > > data;
bool inq[MAXN+10];
queue<int> q;

void input();
void addedge(int,int,int,int,int);
void spfa();
int backtrack();
int maxflow();

bool cmp(int a,int b)
{
	if (edge[a].cap!=edge[b].cap)	return edge[a].cap>edge[b].cap;
	if (edge[a].num!=edge[b].num)	return edge[a].num<edge[b].num;
	return edge[a].ind<edge[b].ind;
}

ofstream fout ("milk6.out");
ifstream fin ("milk6.in");
int main() {
	fin>>N>>M;tar=N;
	data=vector<vector<vector<int> > >(N+1,vector<vector<int> >(N+1,vector<int>()));
	for (int i=0;i<=N;i++)	head[i]=0;
	input();
	sort(sortedge.begin(),sortedge.end(),cmp);
	for (int i=0;i<=tot;i++)	G[i]=edge[i];
	flow=maxflow();
	cout<<flow<<endl;
	fout<<flow<<' ';
	for (int i=0;i<M&&flow;i++)
	{
		int nowedge=sortedge[i],tempcap=edge[nowedge].cap,u=edge[nowedge].u,v=edge[nowedge].v;
		edge[nowedge].cap=0;
		int newflow=maxflow();
		if (newflow+tempcap==flow){
			for (int i=0;i<data[u][v].size();i++)
				ans.push_back(data[u][v][i]);
			flow=newflow;
		}
		else	edge[nowedge].cap=tempcap;
	}
	
	fout<<ans.size()<<endl;
	if (ans.size()>0){
		sort(ans.begin(),ans.end());
		for (int i=0;i<ans.size();i++)	fout<<ans[i]<<endl;
	}
    fout.close();fin.close();
    return 0;
}


/*maxflow*/


int maxflow()
{
	int flow=0;
	for (int i=0;i<=tot;i++)
	{
		G[i].cap=edge[i].cap;
		G[i].nxt=edge[i].nxt;
	}
		
	while (1)
	{
		spfa();
		if (dist[tar]==INF)	break;
		flow+=backtrack();
	}
	return flow;
}

int backtrack()
{
	int minflow=INF;
	for (int i=fa[tar];i;i=fa[G[i].u])
		minflow=min(minflow,G[i].cap);
	for (int i=fa[tar];i;i=fa[G[i].u])
	{
		G[i].cap-=minflow;
		G[i^1].cap+=minflow;
	}
	return minflow;
}

void spfa()
{
	while (!q.empty())	q.pop();
	for (int i=0;i<=N;i++)
	{
		dist[i]=INF;
		inq[i]=false;
	}
	fa[sor]=0;inq[sor]=true;dist[sor]=0;
	q.push(sor);
	int v,cap,now;
	while (!q.empty())
	{
		now=q.front();q.pop();
		
		for (int i=head[now];i;i=G[i].nxt)
		{
			v=G[i].v;cap=G[i].cap;
			if (now==tar)	return;
			if (dist[v]<=dist[now]+1||cap==0)	continue;
			dist[v]=dist[now]+1;
			fa[v]=i;
			if (!inq[v]){
				inq[v]=true;q.push(v);
			}
		}
		inq[now]=false;
	}
}

void input()
{
	int sum[N+1][N+1];
	for (int i=0;i<=N;i++)
		for (int j=0;j<=N;j++)	sum[i][j]=0;
	for (int i=1;i<=M;i++)
	{
		int u,v,cost;fin>>u>>v>>cost;
		sum[u][v]+=cost;data[u][v].push_back(i);
	}
	M=0;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++)
			if (sum[i][j]!=0){
				addedge(i,j,sum[i][j],data[i][j][0],data[i][j].size());
				M++;
			}
}

void addedge(int u,int v,int cost,int ind,int num)
{
	edge[++tot]=Edge{u,v,cost,ind,num,head[u]};
	head[u]=tot;sortedge.push_back(tot);
	edge[++tot]=Edge{v,u,0,ind+1000,1,head[v]};
	head[v]=tot;
}
