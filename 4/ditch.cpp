/*ID: lpjwork1
TASK: ditch
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
const int MAXN=200,MAXM=200*2,INF=(1<<30);
struct Edge{
	int u,v,cap;
	int nxt;
} edge[MAXM+1];
queue<int> q;
int head[MAXN+1],level[MAXN+1],fa[MAXN+1];
bool vis[MAXN+1],found=false;
int tot=1,N,M,sor,sink,ans=0;
void get_level();
void find_flow(int);
void back_track();
void addedge(int,int,int);
ofstream fout ("ditch.out");
ifstream fin ("ditch.in");
int main() {
	fin>>M>>N;sor=1;sink=N;//cout<<N<<' '<<M<<endl;
	for (int i=0;i<=N;i++)	head[i]=0;
	for (int i=0;i<M;i++)
	{
		int u,v,cap;fin>>u>>v>>cap;
		addedge(u,v,cap);
	}
	while (1)
	{
		get_level();
		if (level[sink]==-1)	break;
		for (int i=0;i<=N;i++)	fa[i]=0;
		found=false;
		find_flow(sor);
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
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
		if (level[v]<=level[now]||cap==0)	continue;
		fa[v]=i;
		find_flow(v);
	}
}

void back_track()
{
	int mincap=INF;
	for (int i=fa[sink];i;i=fa[edge[i].u])
	{
		int cap=edge[i].cap;mincap=min(mincap,cap);
	}
	ans+=mincap;
	for (int i=fa[sink];i;i=fa[edge[i].u])
	{
		edge[i].cap-=mincap;edge[i^1].cap+=mincap;
	}
}

void get_level()
{
	while (!q.empty())	q.pop();
	for (int i=0;i<=N;i++)	level[i]=-1;
	level[sor]=0;q.push(sor);
	while (!q.empty())
	{
		int now=q.front();q.pop();
		for (int i=head[now];i;i=edge[i].nxt)
		{
			int v=edge[i].v;
			if (level[v]==-1&&edge[i].cap>0){
				level[v]=level[now]+1;q.push(v);
			}
		}
	}
}

void addedge(int u,int v,int cap)
{
	Edge& now=edge[++tot];
	now.u=u;now.v=v;now.cap=cap;
	now.nxt=head[u];head[u]=tot;
	Edge& back=edge[++tot];
	back.u=v;back.v=u;back.cap=0;
	back.nxt=head[v];head[v]=tot;
}
