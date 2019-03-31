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
};
int dist[MAXK+1][MAXR+1][MAXC+1],kpos[MAXK+1][2],kingpos[2],
	kingdist[MAXR+1][MAXC+1],targetdist[MAXR+1][MAXC+1],distsum[MAXR+1][MAXC+1];
bool possi[MAXR+1][MAXC+1];
vector<bfsnode> possible;
int kn=0,row,col,ans=INF;
queue<bfsnode> q;
/**/
void init();
void input();
void bfsdist(int,int,int[][MAXC+1],const int[][2]);
bool inboard(int,int);
ofstream fout ("camelot.out");
ifstream fin ("camelot.in");
int main() {
	input();
	init();
	for_range(k,0,kn)
	{
		bfsdist(kpos[k][0],kpos[k][1],dist[k],kstep);
		for_range(i,0,row)
			for_range(j,0,col)
				if (possi[i][j]&&dist[k][i][j]!=INF)	possi[i][j]=true;
				else	possi[i][j]=false;
	}
	bfsdist(kingpos[0],kingpos[1],kingdist,kingstep);
	for_range(i,0,row)
		for_range(j,0,col)
			if (possi[i][j])	possible.push_back(bfsnode{i,j,0});
	int mindist=INF;
	for_range(ind,0,possible.size())
	{
		int x=possible[ind].x,y=possible[ind].y;
		/*no knight carry king*/
		int tempans=kingdist[x][y];
		for_range(i,0,kn)	tempans+=dist[i][x][y];
		ans=min(tempans,ans);
		/*for every knight carry king.need to generate target dist to every square*/
		bfsdist(x,y,targetdist,kstep);
		int mindist=INF;
		for_range(k,0,kn)
		{
			/* holy wise and useful A* */
			if (dist[k][kingpos[0]][kingpos[1]]/2>mindist)	continue;
			
			mindist=min(mindist,dist[k][kingpos[0]][kingpos[1]]);
			tempans-=(dist[k][x][y]+kingdist[x][y]);
			for_range(i,0,row)
				for_range(j,0,col)	ans=min(ans,tempans+targetdist[i][j]+dist[k][i][j]+kingdist[i][j]);
			tempans+=(dist[k][x][y]+kingdist[x][y]);
		}
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void bfsdist(int sorx,int sory,int to[][MAXC+1],const int step[][2])
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
		for_range(j,0,col)	possi[i][j]=true;
	for_range(i,0,row)
		for_range(j,0,col)	distsum[i][j]=0;
}

bool inboard(int x,int y)
{
	return (x>=0&&x<row&&y>=0&&y<col);
}
