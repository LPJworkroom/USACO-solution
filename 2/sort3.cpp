/*ID: lpjwork1
TASK: sort3
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
const int MAXN=1000+10;
int N,ans=0;
int cnt[4][4],data[MAXN],cnt3[4];
ofstream fout ("sort3.out");
ifstream fin ("sort3.in");
int main() {
	fin>>N;
	for (int i=1;i<=N;i++)
	{
		fin>>data[i];
		cnt3[data[i]]++;
	}
	//for (int i=1;i<=3;i++)	cout<<cnt3[i]<<' ';	cout<<endl;
	for (int i=1;i<=N;i++)
	{
		int now=(i<=cnt3[1]?1:i<=cnt3[2]+cnt3[1]?2:3);
		cnt[now][data[i]]++;
	}
	/*
	for (int i=1;i<=3;i++)
	{
		for (int j=1;j<=3;j++)
			cout<<cnt[i][j]<<' ';
		cout<<endl;
	}*/
	for (int i=1;i<=3;i++)	N-=cnt[i][i];
	for (int i=1;i<=3;i++)
		for (int j=1;j<=3;j++)
		{
			if (j==i)	continue;
			int swap=min(cnt[i][j],cnt[j][i]);
			ans+=swap;
			N-=swap*2;
			cnt[i][j]-=swap;cnt[j][i]-=swap;
		}
	//if (N)	ans+=N-1;								// I was wrong here!!!!
	ans+=N/3*2;
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}
