/*ID: lpjwork1
TASK: castle
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
const int MAXN=50+10;
int N,M,roomid=0;;
int step[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int wallmap[MAXN][MAXN],room[MAXN][MAXN],area[MAXN*MAXN];
void makeroom();
void flood_fill(int);
void breakwall();
ofstream fout ("castle.out");
ifstream fin ("castle.in");
int main() {
	fin>>M>>N;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++)	fin>>wallmap[i][j];
	makeroom();
	breakwall();
    fout.close();fin.close();
    return 0;
}

void makeroom()
{
	for (int i=1;i<=N;i++)	for (int j=1;j<=M;j++)	room[i][j]=-1;		//not assigned
	memset(area,0,sizeof(area));
	for (int i=N;i>0;i--)	
		for (int j=1;j<=M;j++)
			if (room[i][j]==-1){
				room[i][j]=0;
				flood_fill(++roomid);	
			}
	fout<<roomid<<endl;								//rooms have
	int maxarea=0;
		for (int i=1;i<=roomid;i++)	maxarea=max(maxarea,area[i]);
	fout<<maxarea<<endl;							//largest room
	/*for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=M;j++)
			printf("%4d",room[i][j]);
		printf("\n");
	}
	for (int i=1;i<=roomid;i++)	printf("%d ",area[i]);	printf("\n");*/
}

void flood_fill(int id)
{
	int visted;
	do {
		visted=0;
		for (int i=1;i<=N;i++)
			for (int j=1;j<=M;j++)
				if (room[i][j]==0){
					visted++;
					room[i][j]=id;area[id]++;
					int wall=wallmap[i][j];
					for (int dir=0;dir<4;dir++,wall>>=1)
					{
						if (wall&1)	continue;
						int nowr=i+step[dir][0],nowc=j+step[dir][1];
						if (room[nowr][nowc]==-1)	room[nowr][nowc]=0;
					}
				}
	}while (visted);
}

void breakwall()
{
	int maxarea=0,ansr=1,ansc=1,answ=1;
	for (int j=1;j<=M;j++)
		for (int i=N;i>0;i--)
			for (int dir=1;dir<=2;dir++)
			{
				int nowr=i+step[dir][0],nowc=j+step[dir][1];
				if (room[nowr][nowc]!=room[i][j]&&area[room[nowr][nowc]]+area[room[i][j]]>maxarea){
					maxarea=area[room[nowr][nowc]]+area[room[i][j]];
					ansr=i;ansc=j;answ=dir;
				}
			}
	fout<<maxarea<<endl;
	fout<<ansr<<' '<<ansc<<' ';
	if (answ==1)	fout<<'N';
	else			fout<<'E';
	fout<<endl;
}
