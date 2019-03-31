/*ID: lpjwork1
TASK: race3
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
const int MAXN=50,MAXM=100;
struct Edge{
	int u,v;
	int nxt;
}edge[MAXM+1];
vector<int> uvoid,split;
queue<int> q;
int head[MAXN+1],color[MAXN+1];
int N=0,tot=0;
bool vis[MAXN+1];
void input();
void addedge(int,int);
void bfs(int);
ofstream fout ("race3.out");
ifstream fin ("race3.in");
int main() {
	for (int i=0;i<=MAXN;i++)	head[i]=-1;
	input();
	/*
	for (int i=0;i<=N;i++)
	{
		cout<<i<<'|';
		for (int j=head[i];j!=-1;j=edge[j].nxt)	cout<<edge[j].v<<' ';cout<<endl;
	}
	*/
	/*try delete out edge and bfs*/
	for (int i=1;i<N;i++)
	{
		//save out edge
		int outedge=head[i];
		//delete
		head[i]=-1;
		memset(color,0,sizeof(color));
		bfs(0);
		//determine connect
		if (color[N]==0)	uvoid.push_back(i);
		//backtrack
		head[i]=outedge;
	}
	
	
	for (auto it:uvoid)
	{
		memset(color,0,sizeof(color));
		int outedge=head[it];
		head[it]=-1;bfs(0);
		head[it]=outedge;bfs(it);
		color[it]=1;
		int i;
		for (i=0;i<=N;i++)
			if (color[i]==2)	break;
		if (i>N)	split.push_back(it);
	}
	
	sort(uvoid.begin(),uvoid.end());
	sort(split.begin(),split.end());
	fout<<uvoid.size();
	for (auto it:uvoid)	fout<<' '<<it;	fout<<endl;
	fout<<split.size();
	for (auto it:split)	fout<<' '<<it;	fout<<endl;
    fout.close();fin.close();
    return 0;
}

void bfs(int sor)
{
	while (!q.empty())	q.pop();
	memset(vis,false,sizeof(vis));
	color[sor]++;vis[sor]=true;
	q.push(sor);
	while (!q.empty())
	{
		int now=q.front();q.pop();
		for (int i=head[now];i!=-1;i=edge[i].nxt)
		{
			int v=edge[i].v;
			if (!vis[v]){
				vis[v]=true;
				color[v]++;q.push(v);
			}
		}
	}
}

void input()
{
	int end;
	while (1)
	{
		while (1)
		{
			fin>>end;
			if (end==-2||end==-1)	break;
			addedge(N,end);
		}
		if (end==-1)	break;
		N++;
	}
	N--;
}

void addedge(int u,int v)
{
	Edge& now=edge[++tot];
	now.u=u;now.v=v;
	now.nxt=head[u];head[u]=tot;
}
