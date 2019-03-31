/*ID: lpjwork1
TASK: starry
LANG: C++11
*/
#include<iostream>
#include<queue>
#include<vector>
#include<fstream>
#include<string.h>
#include<algorithm>
using namespace std;
const int MAXH=100,MAXW=100,MAXN=500,INF=(1<<30),
step[8][2]={{1,0},{-1,0},{0,1},{0,-1},{-1,1},{-1,-1},{1,1},{1,-1}};
struct point{
	int x,y;
};
/*all clusters in 2D vector format*/
vector<vector<vector<int> > > clusters;
/*index of clusters same group*/
vector<vector<int> > group;
/*first coord of clusters*/
vector<point> points;
int W,H,N;
char map[MAXH][MAXW];
queue<point> q;

bool match(vector<vector<int> >&,vector<vector<int> >&);
bool inboard(int,int);
void spin(vector<vector<int> >&);
void symtra(vector<vector<int> >&);
void bfs(int,int,vector<vector<bool> >&);
ifstream fin("starry.in");
ofstream fout("starry.out");
int main()
{
	fin>>W>>H;
	for (int i=0;i<H;i++)
		for (int j=0;j<W;j++)
			fin>>map[i][j];
	{
	vector<vector<bool> > vis(H,vector<bool>(W,false));
	for (int i=0;i<H;i++)
		for (int j=0;j<W;j++)
			/*get clusters*/
			if (!vis[i][j]&&map[i][j]=='1')	bfs(i,j,vis);
	}
	
	cout<<clusters.size()<<endl;
	for (int i=0;i<points.size();i++)	cout<<points[i].x<<' '<<points[i].y<<endl;
	
	vector<bool> vis(clusters.size(),false);
	for (int i=0;i<clusters.size();i++)
	{
		if (vis[i])	continue;
		vis[i]=true;
		vector<int> tempgrup;
		tempgrup.push_back(i);
		vector<vector<int> >& nowclu=clusters[i];
		/*find new clusters to match*/
		for (int j=i+1;j<clusters.size();j++)
		{
			if (vis[j])	continue;
			for (int t=0;t<4;t++)
			{
				if (match(nowclu,clusters[j])){
					tempgrup.push_back(j);
					vis[j]=true;break;
				}
				spin(nowclu);
			}
			if (vis[j])	continue;
			symtra(nowclu);
			for (int t=0;t<4;t++)
			{
				if (match(nowclu,clusters[j])){
					tempgrup.push_back(j);
					vis[j]=true;break;
				}
				spin(nowclu);
			}
		}
		group.push_back(tempgrup);
	}
	cout<<group.size()<<endl;
	for (int i=0;i<group.size();i++)
	{
		for (int j=0;j<group[i].size();j++)	cout<<points[group[i][j]].x<<' '<<points[group[i][j]].y<<'|';
		cout<<endl;
	}
	/*color same group*/
	char iro='a';
	for (int i=0;i<group.size();i++,iro++)
	{
		for (int j=0;j<group[i].size();j++)
		{
			q.push(points[group[i][j]]);
			map[points[group[i][j]].x][points[group[i][j]].y]=iro;
		}
		while (!q.empty())
		{
			int x=q.front().x,y=q.front().y;q.pop();
			for (int k=0;k<8;k++)
			{
				int nx=x+step[k][0],ny=y+step[k][1];
				if (!inboard(nx,ny)||map[nx][ny]!='1')	continue;
				map[nx][ny]=iro;
				q.push(point{nx,ny});
			}
		}
	}
	for (int i=0;i<H;i++)
	{
		for (int j=0;j<W;j++)	fout<<map[i][j];
		fout<<endl;
	}
	return 0;
}

void symtra(vector<vector<int> >& c)
{
	for (int i=0;i<c.size();i++)
		reverse(c[i].begin(),c[i].end());
}

void spin(vector<vector<int> >& c)
{
	int h=c.size(),w=c[0].size();
	vector<vector<int> > ret(w,vector<int>(h));
	for (int i=0;i<h;i++)
		for (int j=0;j<w;j++)
			ret[j][h-1-i]=c[i][j];
	c=ret;
}

bool match(vector<vector<int> >& c1,vector<vector<int> >& c2)
{
	int h1=c1.size(),w1=c1[0].size(),h2=c2.size(),w2=c2[0].size();
	if (h1!=h2||w1!=w2)	return false;
	for (int i=0;i<h1;i++)
		for (int j=0;j<w1;j++)	if (c1[i][j]!=c2[i][j])	return false;
	return true;

}

bool inboard(int x,int y)
{
	return (x<H&&x>=0&&y<W&&y>=0);
}

void bfs(int sx,int sy,vector<vector<bool> >& vis)
{
	cout<<"bfs!"<<' '<<sx<<' '<<sy<<endl;
	vis[sx][sy]=true;
	vector<point> stars;
	q.push(point{sx,sy});
	points.push_back(point{sx,sy});
	while (!q.empty())
	{
		int x=q.front().x,y=q.front().y;
		stars.push_back(q.front());q.pop();
		for (int i=0;i<8;i++)
		{
			int nx=x+step[i][0],ny=y+step[i][1];
			if (!inboard(nx,ny)||vis[nx][ny]||map[nx][ny]!='1')	continue;
			vis[nx][ny]=true;
			q.push(point{nx,ny});
		}
	}
	int l=INF,r=0,u=INF,d=0;
	for (int i=0;i<stars.size();i++)
	{
		l=min(stars[i].y,l);u=min(stars[i].x,u);d=max(stars[i].x,d);r=max(stars[i].y,r);
	}
	int h=d-u+1,w=r-l+1;
	/*found cluster*/
	vector<vector<int> > tclu(h,vector<int>(w,0));
	for (int i=0;i<stars.size();i++)
	{
		int x=stars[i].x,y=stars[i].y;
		tclu[x-u][y-l]=1;
	}
	clusters.push_back(tclu);
}

