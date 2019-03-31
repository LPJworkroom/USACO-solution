/*ID: lpjwork1
TASK: telecow
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
const int MAXN=100+10,MAXM=600+10,INF=1<<30,NIL=0;
struct Edge{
	int u,v,cap;
	int cowpu;	//only edge between one node have cowpu,others is 0
	int nxt;
}edge[MAXN*2+MAXM*2],edgebk[MAXN*2+MAXM*2];

int tot=1,sor,sink,N,M,cap=0;
int head[MAXN*2],fazer[MAXN*2];

queue<int> q;

void dividnode();
void addedge(int,int,int,int);
bool bfs();
void bktrk();
int maxflow();

ofstream fout ("telecow.out");
ifstream fin ("telecow.in");
int main() {
	fin>>N>>M>>sor>>sink;
	
	for (int i=1;i<=2*N;i++)	head[i]=NIL;
	
	for (int i=0;i<M;i++)
	{
		int u,v;fin>>u>>v;
		addedge(u,v,INF,NIL);
		addedge(v,u,INF,NIL);
	}
		
	
	for (int i=1;i<=2*N;i++)
	{
		cout<<i<<':';
		for (int j=head[i];j!=NIL;j=edge[j].nxt)
			cout<<edge[j].v<<' ';
		cout<<endl;
	}
	
		
	//gene_dist();
	dividnode();
	
	for (int i=2;i<=tot;i++)
		edgebk[i]=edge[i];
	
	for (int i=1;i<=2*N;i++)
	{
		cout<<i<<':';
		for (int j=head[i];j!=NIL;j=edge[j].nxt)
			cout<<edge[j].v<<' ';
		cout<<endl;
	}
	
	cap=maxflow();
	cout<<"cap:"<<cap<<endl;
	
	int cnt=0,downcap=cap;
	vector<int> ans;
	for (int i=1;i<=N&&cnt<cap;i++)
	{
		if (i==sor||i==sink)	continue;
		/*delete out edge*/
		int backup=head[i];
		head[i]=NIL;
		cout<<i<<":";
		int tempcap=maxflow();
		if (tempcap<downcap){
			cnt++;
			downcap=tempcap;
			ans.push_back(i);
			continue;
		}
		/*recover*/
		head[i]=backup;
	}
	
	fout<<cap<<endl;
	fout<<ans[0];
	for (int i=1;i<ans.size();i++)	fout<<' '<<ans[i],cout<<ans[i]<<endl;
	fout<<endl;
    fout.close();fin.close();
    return 0;
}

int maxflow()
{
	int tempcap=0;
	while (bfs())
	{
		bktrk();
		tempcap++;
	}
	cout<<"tempcap:"<<tempcap<<endl;
	/*recover edge array*/
	for (int i=2;i<=tot;i++)
		edge[i]=edgebk[i];
		
	return tempcap;
}

void dividnode()
{
	while (!q.empty())	q.pop();
	
	Edge* tedge=new Edge[MAXN*2+MAXM*2];
	/*delete edge and head array*/ 
	for (int i=0;i<=tot;i++)	tedge[i]=edge[i],edge[i]=Edge{NIL,NIL,NIL,NIL,NIL};
	int* thead=new int[MAXN*2];
	tot=1;
	for (int i=0;i<=2*N;i++)		thead[i]=head[i],head[i]=NIL;
	
	/*internal edge*/
	for (int i=1;i<=N;i++)
		if (i!=sink&&i!=sor)	addedge(i,i+N,1,i);
	/*sor to node:edge to sor is meaningless*/
	for (int i=thead[sor];i!=NIL;i=tedge[i].nxt)
	{
		addedge(sor,tedge[i].v,INF,NIL);
		q.push(tedge[i].v);
	}
	
	for (int i=1;i<=N;i++)
	{
		if (i==sor||i==sink)	continue;
		for (int j=thead[i];j!=NIL;j=tedge[j].nxt)
		{
			int v=tedge[j].v;
			if (v==sor)	continue;
			addedge(i+N,v,INF,NIL);
		}
	}
	delete tedge;delete thead;
}

bool bfs()
{
	for (int i=1;i<=2*N;i++)	fazer[i]=NIL;
	while (!q.empty())	q.pop();
	q.push(sor);
	while (!q.empty())
	{
		int now=q.front();q.pop();
		if (now==sink)	return true;
		for (int i=head[now];i!=NIL;i=edge[i].nxt)
		{	
			int v=edge[i].v,cap=edge[i].cap;
			if (cap==0||fazer[v]!=NIL)	continue;
			fazer[v]=i;
			q.push(v);
		}
	}
	return false;
}

void bktrk()
{
	cout<<"backtrack:";
	cout<<sink<<' ';
	for (int i=sink;i!=sor;i=edge[fazer[i]].u)
	{
		//Edge& now=edge[fazer[i]],&nowb=edge[fazer[i]^1];
		Edge& now=edge[fazer[i]];
		now.cap--;
		//nowb.cap++;
		cout<<now.u<<' ';
	}
	cout<<endl;
}

void addedge(int u,int v,int cap,int cowpu)
{
	Edge temp{u,v,cap,cowpu,NIL};
	temp.nxt=head[u];
	edge[++tot]=temp;
	head[u]=tot;
}
