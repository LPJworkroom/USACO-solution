/*ID: lpjwork1
TASK: tour
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
const int MAXN=100+10;

int dp[MAXN][MAXN];
bool graph[MAXN][MAXN];
int N,V;
map<string,int> namemap;	//map from city name to index

ofstream fout ("tour.out");
ifstream fin ("tour.in");
int main() {
	fin>>N>>V;
	for (int i=1;i<=N;i++)
	{
		string temp;fin>>temp;
		namemap[temp]=i;
	}
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++)	graph[i][j]=false,dp[i][j]=0;
	graph[N][N]=true;
		
	for (int i=0;i<V;i++)
	{
		string stru,strv;
		int u,v;
		fin>>stru>>strv;
		u=namemap[stru];v=namemap[strv];
		if (v<u)	swap(u,v);
		graph[u][v]=true;
	}
	
	dp[1][1]=1;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++)
		{
			if (dp[i][j]==0)	continue;
			int destfloor=max(i,j)+1;
			if (destfloor==N+1){
				if (graph[i][N]&&graph[j][N])	dp[N][N]=max(dp[N][N],dp[i][j]);
			}
			else
			for (int k=destfloor;k<=N;k++)
			{
				if (graph[i][k])	dp[k][j]=max(dp[k][j],dp[i][j]+1);
				if (graph[j][k])	dp[i][k]=max(dp[i][k],dp[i][j]+1);
			}
		}
		
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=N;j++)	cout<<dp[i][j]<<' ';
		cout<<endl;
	}
	
	if (dp[N][N]==0)	fout<<1<<endl;
	else	fout<<dp[N][N]<<endl;
    fout.close();fin.close();
    return 0;
}
