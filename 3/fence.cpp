/*ID: lpjwork1
TASK: fence
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
#include<stack>
#include<fstream>
#include<list>
using namespace std;
const int MAXV=500,MAXE=1024;
int E,tot=1;
int edge[MAXE*2+10];
vector<vector<int> > e(500+10);
list<int> head[MAXV+10];
stack<int> recur;
stack<int> path;
//queue<int> path;
bool vis[MAXE*2+10];
void addedge(int,int);
bool cmp(int& a,int& b)
{
	return edge[a]<edge[b];
}
int findbeg();
ofstream fout ("fence.out");
ifstream fin ("fence.in");
int main() {
	fin>>E;
	for (int i=0;i<E;i++)
	{
		int u,v;fin>>u>>v;
		e[u].push_back(v);
	}
	for (int i=1;i<=500;i++)
	{
		for (auto j:e[i])
		{
			addedge(i,j);addedge(j,i);
		}
	}
	for (int i=1;i<=500;i++)	head[i].sort(cmp);
	int beg=findbeg();
	
	//while (e[beg].empty())	beg++;
	cout<<beg;
	recur.push(beg);
	while (!recur.empty())
	{
		int now=recur.top();
		while (!head[now].empty()&&vis[head[now].front()])	head[now].pop_front();
		if (head[now].empty()){
			recur.pop();path.push(now);
		}
		else{
			int num=head[now].front(),v=edge[num];
			recur.push(v);
			vis[num]=vis[num^1]=true;
			head[now].pop_front();
		}
	}
	while (!path.empty()){
		fout<<path.top()<<endl;
		path.pop();
	}
    fout.close();fin.close();
    return 0;
}

int findbeg()
{
	vector<int> odds;
	for (int i=1;i<=MAXV;i++)
	{
		//cout<<head[i].size()<<' ';
		if (head[i].size()&1)	odds.push_back(i);
	}
	//cout<<endl<<odds.size()<<endl;
	if (odds.size()==2)	return odds[0];
	int ret=0;
	while (head[ret].size()==0)	ret++;
	return ret;
}

void addedge(int u,int v)
{
	edge[++tot]=v;head[u].push_front(tot);
}
