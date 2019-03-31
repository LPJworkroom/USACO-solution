/*ID: lpjwork1
TASK: wormhole
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<string.h>
#include<vector>
#include<fstream>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=12+1,INF=1<<30;
struct hole{
	int x,ind;
};
bool operator<(hole a,hole b)	{return a.x<b.x;}
int N,ans=0;
int g[MAXN][MAXN],nxt[MAXN];
bool sele[MAXN],vis[MAXN],finish[MAXN];
map<int,vector<hole> > ycnt;
queue<int> q;
void bf(int now);
void showmap();
bool dfs(int);
bool check();
ofstream fout ("wormhole.out");
ifstream fin ("wormhole.in");
int main() 
{
	for (int i=1;i<=N;i++)	for (int j=1;j<=N;j++)	g[i][j]=0;
	fin>>N;
	for (int i=1;i<=N;i++)
	{
		nxt[i]=sele[i]=0;
		int x,y;fin>>x>>y;
		hole temp{x,i};
		ycnt[y].push_back(temp);
	}
	for (auto it:ycnt)
	{
		sort(it.second.begin(),it.second.end());
		for (int i=0;i<it.second.size()-1;i++)
			nxt[it.second[i].ind]=it.second[i+1].ind;						//  +x holes have edge
	}
	//showmap();
	//for (int i=1;i<=N;i++)	cout<<nxt[i]<<' ';cout<<endl;
	bf(1);
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void bf(int now)
{
	if (now==N){
		showmap();
		if (check())	ans++;
		return;	
	}
	if (sele[now])	{
		bf(now+1);return;
	}
	for (int i=now+1;i<=N;i++)
		if (!sele[i]){			//	can add edge
			sele[i]=true;
			g[now][nxt[i]]=1;
			g[i][nxt[now]]=1;
			bf(now+1);
			sele[i]=false;
			g[now][nxt[i]]=0;
			g[i][nxt[now]]=0;
		}
}

bool check()
{
	memset(vis,false,sizeof(vis));	
	memset(finish,false,sizeof(finish));
	for (int i=1;i<=N;i++)
		if (!finish[i]&&dfs(i))	return true;
	return false;	
}

bool dfs(int now)
{
	if (vis[now]&&!finish[now])	return true;
	vis[now]=1;
	for (int i=1;i<=N;i++)
		if (g[now][i]&&dfs(i))	return true;
	finish[now]=1;
	return false;
}
/*bool check()
{
	for (int i=1;i<=N;i++)
	{
		//if (!vis[i]){
			memset(vis,false,sizeof(vis));
			while (!q.empty())	q.pop();
			vis[i]=1;q.push(i);
			while (!q.empty())
			{
				int now=q.front();q.pop();
				for (int j=1;j<=N;j++)
					if (g[now][j]){
						if (vis[j])	return true;
						vis[j]=1;
						q.push(j);
					}
			}
		}
	return false;
}
*/

void showmap()
{
	for (int i=1;i<=N;i++){
		for (int j=1;j<=N;j++)
			printf("%d ",g[i][j]);
		printf("\n");
	}
	printf("//////////////////////////////////////////////////\n");	
}
