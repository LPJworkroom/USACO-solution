/*ID: lpjwork1
TASK: fence6
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
const int MAXN=100,MAXNO=200,INF=(1<<20);
struct Fence{
	int len;
	int no1,no2;
	bool nei1[MAXN+1],nei2[MAXN+1];
}fence[MAXN+1];
queue<int> q;
int N,tot=0,ans=INF;
int dist[MAXNO+1][MAXNO+1],g[MAXNO+1][MAXNO+1];
bool inq[MAXNO+1];
void input();
void spfa(int);
ofstream fout ("fence6.out");
ifstream fin ("fence6.in");
int main() {
	for (int i=0;i<=MAXNO;i++)
		for (int j=0;j<=MAXNO;j++)	g[i][j]=-1;
	input();
	for (int i=1;i<=N;i++)
	{
		int no1=fence[i].no1,no2=fence[i].no2;
		g[no1][no2]=g[no2][no1]=INF;
		spfa(no1);
		ans=min(ans,dist[no1][no2]+fence[i].len);
		g[no1][no2]=g[no2][no1]=fence[i].len;
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void spfa(int sor)
{
	while (!q.empty())	q.pop();
	memset(inq,false,sizeof(inq));
	for (int i=0;i<=tot;i++)	dist[sor][i]=INF;
	dist[sor][sor]=0;inq[sor]=true;
	q.push(sor);
	while (!q.empty())
	{
		int now=q.front();q.pop();
		for (int i=1;i<=tot;i++)
			if (g[now][i]!=-1&&g[now][i]+dist[sor][now]<dist[sor][i]){
				dist[sor][i]=g[now][i]+dist[sor][now];
				if (!inq[i]){
					q.push(i);inq[i]=true;
				}
			}
		inq[now]=false;
	}
}

void input()
{
	fin>>N;
	for (int i=1;i<=N;i++)
	{
		int index;
		fin>>index;
		Fence& now=fence[index];
		memset(now.nei1,false,sizeof(now.nei1));
		memset(now.nei2,false,sizeof(now.nei2));
		int len;fin>>len;now.len=len;
		now.no1=++tot;now.no2=++tot;
		g[now.no1][now.no2]=g[now.no2][now.no1]=len;
		int no1size,no2size;fin>>no1size>>no2size;
		for (int j=0;j<no1size;j++){
			int temp;fin>>temp;now.nei1[temp]=true;
		}
		for (int j=0;j<no2size;j++){
			int temp;fin>>temp;now.nei2[temp]=true;
		}
	}
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=N;j++)
		{
			if (i==j)	continue;
			Fence& fi=fence[i],&fj=fence[j];
			if (fi.nei1[j]&&fj.nei1[i])
				g[fi.no1][fj.no1]=g[fj.no1][fi.no1]=0;
			if (fi.nei2[j]&&fj.nei1[i])
				g[fi.no2][fj.no1]=g[fj.no1][fi.no2]=0;
			if (fi.nei1[j]&&fj.nei2[i])
				g[fi.no1][fj.no2]=g[fj.no2][fi.no1]=0;
			if (fi.nei2[j]&&fj.nei2[i])
				g[fi.no2][fj.no2]=g[fj.no2][fi.no2]=0;
		}
	}
}
