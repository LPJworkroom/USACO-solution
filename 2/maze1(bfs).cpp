	/*ID: lpjwork1
TASK: maze1
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
const int MAXN=100,MAXM=38,INF=(1<<30);
const int step[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int N,M,ans=0;
vector<vector<int> > target;
int dist[MAXN+10][MAXM+10];
bool wall[MAXN+10][MAXM+10][4],vis[MAXN+10][MAXM+10];
void show();
void bfs(int,int);
FILE* fout=fopen("maze1.out","w");
FILE* fin=fopen("maze1.in","r");
int main() {
	fscanf(fin,"%d%d",&M,&N);
	for (int i=0;i<=N+1;i++)
		for (int j=0;j<=M+1;j++)
		{
			memset(wall[i][j],false,sizeof(wall[i][j]));
			dist[i][j]=INF;
		}
	char temp;
	fscanf(fin,"%c",&temp);
	for (int i=1;i<=2*N+1;i++)
	{
		char now;
		/*odd,so horizon fences*/
		if (i&1){
			for (int j=1;j<=M;j++)
			{
				fscanf(fin,"%c%c",&now,&now);
				if (now==' '&&(i==1||i==2*N+1)){
					vector<int> temp(2);
					if (i==1)	temp[0]=1;
					else		temp[0]=N;
					temp[1]=j;
					target.push_back(temp);
					now='-';
				}
				if (now=='-')	wall[i/2][j][2]=wall[i/2+1][j][0]=true;
			}
			fscanf(fin,"%c",&now);
		}
		/*vertical*/
		else{
			for (int j=1;j<=M+1;j++)
			{
				fscanf(fin,"%c",&now);
				if (now==' '&&(j==1||j==M+1)){
					vector<int> temp(2);
					if (j==1)	temp[1]=1;
					else		temp[1]=M;
					temp[0]=i/2;
					target.push_back(temp);
					now='|';
				}
				if (now=='|')	wall[i/2][j-1][1]=wall[i/2][j][3]=true;
				if (j==M+1)	break;
				fscanf(fin,"%c",&now);
			}
		}
		fscanf(fin,"%c",&now);
	}
	bfs(target[0][0],target[0][1]);
	bfs(target[1][0],target[1][1]);
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++)	ans=max(ans,dist[i][j]);
	fprintf(fout,"%d\n",ans);
	//show();
    fclose(fin);fclose(fout);
    return 0;
}

void bfs(int x,int y)
{
	int temp[2]={x,y};
	queue<vector<int> >q;
	dist[x][y]=1;
	q.push(vector<int>(temp,temp+2));
	while (!q.empty())
	{
		int x=q.front()[0],y=q.front()[1];q.pop();
		for (int dir=0;dir<4;dir++)
		{
			if (wall[x][y][dir])	continue;
			int nowx=x+step[dir][0],nowy=y+step[dir][1];
			if (dist[x][y]+1<dist[nowx][nowy]){
				dist[nowx][nowy]=dist[x][y]+1;
				temp[0]=nowx;temp[1]=nowy;
				q.push(vector<int>(temp,temp+2));
			}
		}
	}
}

void show()
{
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=M;j++)
		{
			for (int k=0;k<4;k++)
				if (wall[i][j][k]==true)	cout<<1;
				else						cout<<0;
			cout<<' ';
		}
		cout<<endl;
	}
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=M;j++)
		{
			cout<<dist[i][j]<<' ';
		}
		cout<<endl;
	}
}
