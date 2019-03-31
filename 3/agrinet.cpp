/*ID: lpjwork1
TASK: agrinet
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
const int MAXN=100,INF=(1<<30);
int N,ans=0;
int edge[MAXN+10][MAXN+10],dist[MAXN+10];
bool intree[MAXN+10];
void updatedist(int);
ofstream fout ("agrinet.out");
ifstream fin ("agrinet.in");
int main() {
	fin>>N;
	for (int i=0;i<=N;i++){
		dist[i]=INF;intree[i]=false;
	}
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++)	fin>>edge[i][j];
	/*
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=N;j++)
			cout<<edge[i][j]<<' ';
		cout<<endl;
	}
	*/	
	int treesize=0;
	intree[1]=true;updatedist(1);treesize++;
	while (treesize!=N)
	{
		int tempmin=INF,minnode;
		for (int i=1;i<=N;i++)
			if (!intree[i]&&dist[i]<tempmin){
				tempmin=dist[i];minnode=i;
			}
		intree[minnode]=true;updatedist(minnode);
		ans+=dist[minnode];
		treesize++;
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void updatedist(int n)
{
	for (int i=1;i<=N;i++)
		if (!intree[i]&&edge[n][i]<dist[i])	dist[i]=edge[n][i];
}
