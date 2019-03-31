/*ID: lpjwork1
TASK: schlnet
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<list>
#include<string>
#include<string.h>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<set>
#include<fstream>
using namespace std;
const int MAXN=100,MAXM=10000*2,INF=(1<<30);
/*stk to stimulate recursive and toprank to save top order*/
stack<int> stk,toprank;
/*degree is out-degree,fa is union-find set*/
vector<list<int> > head,revhead;
vector<int> idegree,odegree,fa;
bool vis[MAXN+10];
/*viscnt is how many nodes visted*/
int N,viscnt;
void input();
void bfs(int);
void topsort(int);
int min_idegree();
int min_odegree();
ofstream fout ("schlnet.out");
ifstream fin ("schlnet.in");
int main() {
	fin>>N;
	fa.resize(N+1);
	head.resize(N+1);
	revhead.resize(N+1);
	idegree.resize(N+1);
	odegree.resize(N+1);
	input();
	for (int i=1;i<=N;i++)
	{
		if (head[i].size()==0)	cout<<"no odegree:"<<i<<endl;
		odegree[i]=head[i].size();
		if (idegree[i]==0)	cout<<"no idegree:"<<i<<endl;
	}
	viscnt=0;
	/*now degree is ready,subtast A*/
{
	memset(vis,false,sizeof(vis));
	vector<list<int> > thead;
	thead=head;
	/*
	for (int i=1;i<=N;i++)
		if (!vis[i])	topsort(i);
	*/
	/*manualy stimulate stack*/
	while (toprank.size()!=N)
	{
		if (stk.empty()){
			int u=min_idegree();	//not neccessary min degree,just for fun
			vis[u]=true;
			stk.push(u);
		}
		int now=stk.top();
		while (!head[now].empty()&&vis[head[now].front()])	head[now].pop_front();
		if (head[now].empty()){
			stk.pop();
			toprank.push(now);
		}
		else{
				stk.push(head[now].front());
				vis[head[now].front()]=true;
				head[now].pop_front();
			}
	}
	head=thead;
}
 
	cout<<"toprank ok"<<endl;
	while (!stk.empty())	stk.pop();
	memset(vis,false,sizeof(vis));
	queue<int> q;
	/*now nodes are in right rank in toprank*/
	int befN=N;
	N=1;
	while (!toprank.empty())
	{
		while (!toprank.empty()&&vis[toprank.top()])	toprank.pop();
		if (toprank.empty())	break;
		q.push(toprank.top());
		vis[toprank.top()]=true;
		toprank.pop();
		vector<int> tomerge;
		/*bfs and shrink nodes*/
		cout<<"............"<<endl;
		while (!q.empty())
		{
			int now=q.front();q.pop();tomerge.push_back(now);
			cout<<now<<endl;
			for (auto i=revhead[now].begin();i!=revhead[now].end();i++)
				if (!vis[*i]){
					q.push(*i);
					vis[*i]=true;
				}
		}
		cout<<"............"<<endl;
		/*make union-find set*/
		for (int i=0;i<tomerge.size();i++)
			fa[tomerge[i]]=N;		//N is new union's index
		N++;
	}
	N--;
	/*now N is count of SCC*/
	cout<<"merge ok"<<endl;
	/*make new graph*/
	int idegree[N+1],odegree[N+1];
	for (int i=0;i<=N;i++)	idegree[i]=odegree[i]=0;
	/*new graph*/
	vector<list<int> > nhead(N+1);
	for (int i=1;i<=befN;i++)
	{
		int u=fa[i];
		for (auto it=head[i].begin();it!=head[i].end();it++)
		{
			int v=fa[*it];
			if (find(nhead[u].begin(),nhead[u].end(),v)==nhead[u].end()&&
					 u!=v){
				nhead[u].push_back(v);
				idegree[v]++;
			}
		}
	}
	/*task A is count of 0 indegree SCC*/
	int ansa=0;
	for (int i=1;i<=N;i++)
		if (idegree[i]==0)	ansa++;
	fout<<ansa<<endl;
	
	for (int i=1;i<=N;i++)	odegree[i]=nhead[i].size();
	for (int i=1;i<=N;i++)
	{
		cout<<i<<":";
		for (auto it=nhead[i].begin();it!=nhead[i].end();it++)	cout<<(*it)<<' ';cout<<endl;
	}
	cout<<"newhead ok"<<endl;
	int ansb=0,icnt=0,ocnt=0,iocnt=0;
	for (int i=1;i<=N;i++)
	{
		if (odegree[i]==0&&idegree[i]==0){
			iocnt++;continue;
		}
		if (odegree[i]==0)	ocnt++;
		if (idegree[i]==0)	icnt++;
	}
	cout<<"icnt:"<<icnt<<endl;
	cout<<"ocnt:"<<ocnt<<endl;
	cout<<"iocnt:"<<iocnt<<endl;
	
	/*core formula!*/
	ansb=max(icnt,ocnt)+iocnt;
	if (N==1)	ansb=0;
	
	fout<<ansb<<endl;
    fout.close();fin.close();
    return 0;
}

int min_idegree()
{
	int ret=0,minde=INF;
	for (int i=1;i<=N;i++)
		if (!vis[i]&&idegree[i]<minde){
			minde=idegree[i];ret=i;
		}
	return ret;
}

void input()
{
	for (int i=1;i<=N;i++)
	{
		while (1)
		{
			int temp;fin>>temp;
			if (temp==0)	break;
			head[i].push_back(temp);
			revhead[temp].push_back(i);
			idegree[temp]++;
		}
	}
}

void bfs(int sor)
{
	queue<int> q;
	vis[sor]=true;viscnt++;
	q.push(sor);
	while (!q.empty())
	{
		int now=q.front();q.pop();
		for (auto i=head[now].begin();i!=head[now].end();i++)
			if (!vis[*i]){
				vis[*i]=true;viscnt++;
				q.push(*i);
			}
	}
}

void topsort(int now)
{
	vis[now]=true;
	for (auto i=head[now].begin();i!=head[now].end();i++)
		if (!vis[*i])	topsort(*i);
	toprank.push(now);
}
