/*ID: lpjwork1
TASK: stall4
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
const int MAXC=200,MAXS=200,MAXN=400,MAXM=MAXN*MAXN*2,INF=(1<<30);
struct Edge{
	int u,v,cap;
	int nxt;
} edge[MAXM+10];
queue<int> q;
int head[MAXN+10],fa[MAXN+10],level[MAXN+10];
int C,S,sor,sink,ans=0,tot=1,N;
bool found=false;
void get_level();
void find_flow(int);
void back_track();
void addedge(int,int);
ofstream fout ("stall4.out");
ifstream fin ("stall4.in");
int main() {
	fin>>C>>S;
	N=C+S+2;
	for (int i=0;i<=N;i++)	head[i]=0;
	sor=C+S+1;sink=sor+1;
	for (int i=1;i<=C;i++)
	{
		int n;fin>>n;
		for (int j=0;j<n;j++)
		{
			int v;fin>>v;
			addedge(i,v+C);
		}
	}
	for (int i=1;i<=C;i++)	addedge(sor,i);
	for (int i=1;i<=S;i++)	addedge(i+C,sink);
	while (1)
	{
		found=false;
		get_level();
		if (level[sink]==INF)	break;
		for (int i=0;i<=N;i++)	fa[i]=0;
		find_flow(sor);
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void back_track()
{
	int mincap=INF;
	for (int i=fa[sink];i;i=fa[edge[i].u])
		mincap=min(mincap,edge[i].cap);
	ans+=mincap;
	for (int i=fa[sink];i;i=fa[edge[i].u])
	{
		edge[i].cap-=mincap;
		if (edge[i].u!=sor&&edge[i].v!=sink)	edge[i^1].cap+=mincap;
	}
}

void find_flow(int now)
{
	if (found)	return;
	if (now==sink){
		back_track();found=true;return;
	}
	for (int i=head[now];i;i=edge[i].nxt)
	{
		int v=edge[i].v,cap=edge[i].cap;
		if (cap==0||level[v]<=level[now])	continue;
		fa[v]=i;
		find_flow(v);
	}
}

void get_level()
{
	while (!q.empty())	q.pop();
	for (int i=0;i<=N;i++)	level[i]=INF;
	level[sor]=0;q.push(sor);
	while (!q.empty())
	{
		int now=q.front();q.pop();
		for (int i=head[now];i;i=edge[i].nxt)
		{
			int v=edge[i].v,cap=edge[i].cap;
			if (level[now]+1<level[v]&&cap>0){
				level[v]=level[now]+1;q.push(v);
			}
		}
	}
}

void addedge(int u,int v)
{
	Edge& to=edge[++tot];
	to=Edge{u,v,1,head[u]};head[u]=tot;
	Edge& back=edge[++tot];
	back=Edge{v,u,0,head[v]};head[v]=tot;
}
