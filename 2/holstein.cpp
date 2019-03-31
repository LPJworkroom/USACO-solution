/*ID: lpjwork1
TASK: holstein
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
#include<fstream>
using namespace std;
const int MAXV=25,MAXN=15;
int V,N;
int target[MAXV],feed[MAXN][MAXV],curfeed[MAXV],sum[MAXV],ans[MAXN][MAXN],canfeed[MAXN+10];
bool chosen[MAXN+10];
bool found;
void dfs(int,int);
void revdfs(int,int);
void searchfor(int);
void output(int);
ofstream fout ("holstein.out");
ifstream fin ("holstein.in");
int main() {
	memset(sum,0,sizeof(sum));
	for (int i=0;i<MAXN;i++)	canfeed[i]=-1;
	fin>>V;
	for (int i=0;i<V;i++)	fin>>target[i];
	fin>>N;
	for (int i=0;i<N;i++)
		for (int j=0;j<V;j++)
		{
			fin>>feed[i][j];
			sum[j]+=feed[i][j];
		}
	//searchfor(1);cout<<canfeed[1]<<endl;
	int l=1,r=N,mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		cout<<mid<<endl;
		searchfor(mid);
		if (canfeed[mid])	r=mid;
		else				l=mid+1;
	}
	searchfor(l);searchfor(r);
	if (canfeed[l]==1)	output(l);
	else			output(r);
    fout.close();fin.close();
    return 0;
}

void output(int a)
{
	fout<<a<<' ';
	for (int i=0;i<a;i++)
	{
		fout<<ans[a][i];
		if (i!=a-1)	fout<<' ';
	}
	fout<<endl;
	/*
	fout<<10<<' ';
	for (int i=0;i<10;i++)
	{
		fout<<ans[10][i];
		if (i!=10-1)	fout<<' ';
	}
	fout<<endl;*/
}

void searchfor(int i)
{
	if (canfeed[i]!=-1)	return;
	found=false;
	memset(curfeed,0,sizeof(curfeed));
	memset(chosen,false,sizeof(chosen));
	if (i<=N/2)	dfs(0,i);
	else	revdfs(0,N-i);
	if (found)	canfeed[i]=1;
	else		canfeed[i]=0;
}

void dfs(int dep,int maxdep)
{
	if (found)	return;
	if (dep==maxdep){
		for (int i=0;i<V;i++)	if (curfeed[i]<target[i])	return;
		int cnt=0;
		for (int j=0;j<N;j++)
		{
			if (!chosen[j])	continue;
			ans[maxdep][cnt]=j+1;
			cnt++;
		}
		found=true;
	}
	if (found)	return;
	for (int i=dep;i<N;i++)
	{
		if (chosen[i])	continue;
		chosen[i]=1;
		for (int j=0;j<V;j++)	curfeed[j]+=feed[i][j];
		dfs(dep+1,maxdep);
		chosen[i]=0;
		for (int j=0;j<V;j++)	curfeed[j]-=feed[i][j];
	}
}

void revdfs(int dep,int maxdep)
{
	if (found)	return;
	if (dep==maxdep){
		for (int i=0;i<V;i++)	if (sum[i]-curfeed[i]<target[i])	return;
		int cnt=0;
		for (int j=0;j<N;j++)
		{
			if (chosen[j])	continue;
			ans[N-maxdep][cnt]=j+1;
			cnt++;
		}
		found=true;
	}
	if (found)	return;
	for (int i=N-1-dep;i>=0;i--)
	{
		if (chosen[i])	continue;
		chosen[i]=1;
		for (int j=0;j<V;j++)	curfeed[j]+=feed[i][j];
		revdfs(dep+1,maxdep);
		chosen[i]=0;
		for (int j=0;j<V;j++)	curfeed[j]-=feed[i][j];
	}
}
