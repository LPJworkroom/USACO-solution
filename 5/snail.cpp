/*ID: lpjwork1
TASK: snail
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
//#include<map>
#include<string>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
#include<fstream>
using namespace std;
const int MAXN=120,step[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
char map[MAXN+2][MAXN+2];
int N,ans=0;
void input();
void dfs(int,int,int);
void show();
ofstream fout ("snail.out");
ifstream fin ("snail.in");
int main() {
	fin>>N;
	input();
	show();
	map[1][1]='v';
	dfs(1,1,1);
	cout<<ans<<endl;
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void dfs(int x,int y,int len)
{
	/*
	show();
	cout<<x<<' '<<y<<' '<<len<<endl;
	*/
	for (int i=0;i<4;i++)
	{
		int nx=x+step[i][0],ny=y+step[i][1];
		if (map[nx][ny]=='#'||map[nx][ny]=='v')	continue;
		int dex=step[i^1][0],dey=step[i^1][1];
		int tlen=len;
		while (map[nx][ny]=='.')
		{
			map[nx][ny]='v';
			nx=nx+step[i][0];ny=ny+step[i][1];
			tlen++;
		}
		ans=max(ans,tlen);
		if (map[nx][ny]=='#')
			dfs(nx+dex,ny+dey,tlen);
		//backtrack
		nx+=dex;ny+=dey;
		while (nx!=x||ny!=y)
		{
			map[nx][ny]='.';
			nx+=dex;ny+=dey;
		}
	}
}

void input()
{
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++)	map[i][j]='.';
	for (int i=0;i<=N+1;i++)	map[0][i]=map[N+1][i]='#';
	for (int i=0;i<=N+1;i++)	map[i][0]=map[i][N+1]='#';
	int n;fin>>n;fin.get();
	for (int i=0;i<n;i++)
	{
		char col;fin>>col;
		int row;fin>>row;fin.get();
		map[row][col-'A'+1]='#';
	}
}

void show()
{
	for (int i=0;i<=N+1;i++)
	{
		for (int j=0;j<=N+1;j++)	cout<<map[i][j];
		cout<<endl;
	}
}
