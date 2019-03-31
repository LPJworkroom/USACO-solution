/*ID: lpjwork1
TASK: camelot
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
#include<ctime>
#define for_range(i,x,y)	for (int i=x;i<y;i++)
using namespace std;
const int MAXC=30,MAXR=26,base='A'-1,MAXK=26*30,INF=(1<<20);
const int 	kstep[8][2]={{-2,1},{-1,2},{-2,-1},{-1,-2},{2,1},{1,2},{2,-1},{1,-2}},
			kingstep[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
struct bfsnode{
	int x,y,dist;
	int king;
};
int dist[MAXK+1][MAXR+1][MAXC+1][2],kpos[MAXK+1][2],kingpos[2],
	kingdist[MAXR+1][MAXC+1],distsum[MAXR+1][MAXC+1],exmove[MAXR+1][MAXC+1];
int kn=0,row,col,ans=INF;
queue<bfsnode> q;
/**/
void init();
void input();
void knbfs(int,int,int[][MAXC+1][2],const int[][2]);
void bfs(int,int,int[][MAXC+1],const int[][2]);
bool inboard(int,int);
ofstream fout ("camelot.out");
ifstream fin ("camelot.in");
int main() {
	input();
	init();
	for_range(k,0,kn)
	{
		knbfs(kpos[k][0],kpos[k][1],dist[k],kstep);
		for_range(i,0,row)
			for_range(j,0,col)
				if (dist[k][i][j][0]!=INF)	distsum[i][j]+=dist[k][i][j][0];
				else						distsum[i][j]=INF;
		for_range(i,0,row)
			for_range(j,0,col)
			{
				exmove[i][j]=min(exmove[i][j],dist[k][i][j][1]-dist[k][i][j][0]);
			}
	}
	for_range(i,0,row)
		for_range(j,0,col)
		{
			/*nobody carries king*/
			ans=min(ans,distsum[i][j]+kingdist[i][j]);
			/*one knight take the shortest route to (i,j)*/
			ans=min(ans,distsum[i][j]+exmove[i][j]);
		}
	cout<<ans<<endl;
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
} 

void bfs(int sorx,int sory,int to[][MAXC+1],const int step[][2])
{
	for_range(i,0,row)
			for_range(j,0,col)	to[i][j]=INF;
	while (!q.empty())	q.pop();
	to[sorx][sory]=0;
	q.push(bfsnode{sorx,sory,0});
	while (!q.empty())
	{
		int x=q.front().x,y=q.front().y,dist=q.front().dist;q.pop();
		for_range(i,0,8)
		{
			int newx=x+step[i][0],newy=y+step[i][1];
			if (!inboard(newx,newy)||to[newx][newy]!=INF)	continue;
			to[newx][newy]=dist+1;
			q.push(bfsnode{newx,newy,dist+1});
		}
	}
}

void input()
{
	fin>>col>>row;
	char r;fin>>r>>kingpos[1];r-=base;kingpos[0]=r;
	kingpos[0]--;kingpos[1]--;
	int c;
	while (1)
	{
		r='$';c=-1;
		fin>>r>>c;
		if (r=='$'||c==-1)	return;
		kpos[kn][0]=r-base;kpos[kn][1]=c;
		kpos[kn][0]--;kpos[kn][1]--;
		kn++;
	}
}

void init()
{
	for_range(i,0,row)
		for_range(j,0,col)	distsum[i][j]=0;
	for_range(i,0,row)
			for_range(j,0,col)	exmove[i][j]=INF;
	bfs(kingpos[0],kingpos[1],kingdist,kingstep);
}

bool inboard(int x,int y)
{
	return (x>=0&&x<row&&y>=0&&y<col);
}

void knbfs(int knx,int kny,int to[][MAXC+1][2],const int step[][2])
{
	while (!q.empty())	q.pop();
	for_range(i,0,row)
		for_range(j,0,col)
			for_range(k,0,2)	to[i][j][k]=INF;
	to[knx][kny][0]=0;
	q.push(bfsnode{knx,kny,0,0});
	q.push(bfsnode{knx,kny,kingdist[knx][kny],1});
	while (!q.empty())
	{
		bfsnode& now=q.front();
		int x=now.x,y=now.y,dist=now.dist;int king=now.king;
		q.pop();
		for_range(i,0,8)
		{
			int newx=x+step[i][0],newy=y+step[i][1];
			if (!inboard(newx,newy))	continue;
			/*without king*/
			if (king==0){
				if (to[newx][newy][0]>dist+1){
					to[newx][newy][king]=dist+1;
					q.push(bfsnode{newx,newy,dist+1,0});
				}
				if (to[newx][newy][1]>dist+1+kingdist[newx][newy]){
					to[newx][newy][1]=dist+1+kingdist[newx][newy];
					q.push(bfsnode{newx,newy,dist+1+kingdist[newx][newy],1});
				}
			}
			/*with king*/
			else
				if (to[newx][newy][1]>dist+1){
					to[newx][newy][1]=dist+1;
					q.push(bfsnode{newx,newy,dist+1,1});
				}
		}
	}
}
