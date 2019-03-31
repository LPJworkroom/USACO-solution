/*ID: lpjwork1
TASK: frameup
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
const int MAXH=30,MAXW=30;
int H,W,N=0;
vector<string> ans;
vector<vector<vector<int> > > appear(26),valid(26);
string permut;
char data[MAXH+1][MAXW+1],backup[30][MAXH+1][MAXW+1],itocmap[26];
int ctoimap[26];
bool used[26];

void redo(int);
void checkappear(int,int,char);
bool checkwhole(int,int,int,int,char);
void color(int,int,int,int);
bool checkedge(int,int,int,int,char);
void copy(char (&)[MAXH+1][MAXW+1],char (&)[MAXH+1][MAXW+1]);
ofstream fout ("frameup.out");
ifstream fin ("frameup.in");
int main() {
	fin>>H>>W;
	for (int i=0;i<26;i++)	ctoimap[i]=-1;
	for (int i=0;i<H;i++)
		for (int j=0;j<W;j++)
		{
			fin>>data[i][j];
			if (data[i][j]!='.')
			{
				if (ctoimap[data[i][j]-'A']==-1){
					ctoimap[data[i][j]-'A']=N;
					itocmap[N]=data[i][j];
					N++;
				}
				data[i][j]=ctoimap[data[i][j]-'A']+'A';
				vector<int> temp(2);
				temp[0]=i;temp[1]=j;
				appear[data[i][j]-'A'].push_back(temp);
			}
		}
	for (int i=0;i<26;i++)	used[i]=false;
	for (int c=0;c<N;c++)
	{
		char now='A'+c;
		for (int x=0;x<H;x++)
			for (int y=0;y<W;y++)	checkappear(x,y,now);
	}
//	for (int i=0;i<N;i++)
//	{
//		cout<<i<<endl;
//		for (int j=0;j<valid[i].size();j++)	cout<<valid[i][j][0]<<' '<<valid[i][j][1]
//		<<' '<<valid[i][j][2]<<' '<<valid[i][j][3]<<endl;
//	}
	redo(0);
	for (int i=0;i<26;i++)	used[i]=false;
	sort(ans.begin(),ans.end());
	for (int i=0;i<ans.size();i++)	fout<<ans[i]<<endl;
    fout.close();fin.close();
    return 0;
}

void checkappear(int x,int y,char c)
{	
	for (int h=3;h+x<=H;h++)
		for (int w=3;w+y<=W;w++)
		{
			if (!checkedge(x,y,h,w,c))	continue;
			int i;
			for (i=0;i<appear[c-'A'].size();i++)
			{
				int px=appear[c-'A'][i][0],py=appear[c-'A'][i][1];
				if (!(((px==x||px==x+h-1)&&(py>=y&&py<y+w))||
					((py==y||py==y+w-1)&&(px>=x&&px<x+h))))	break;
			}
			if (i!=appear[c-'A'].size())	continue;
			vector<int> temp(4);
			temp[0]=x;temp[1]=y;temp[2]=h;temp[3]=w;
			valid[c-'A'].push_back(temp);
		}
}

bool checkwhole(int x,int y,int h,int w,char c)
{
	for (int i=x;i<x+h;i++)
		if ((data[i][y]!=c&&data[i][y]!='@')||(data[i][y+w-1]!=c&&data[i][y+w-1]!='@'))	return false;
	for (int i=y;i<y+w;i++)
		if ((data[x][i]!=c&&data[x][i]!='@')||(data[x+h-1][i]!=c&&data[x+h-1][i]!='@'))	return false;
	return true;
}

bool checkedge(int x,int y,int h,int w,char c)
{
	int i;
	if (data[x][y]==c||data[x+h-1][y]==c||data[x+h-1][y+w-1]==c||data[x][y+w-1]==c)	return true;
	for (i=x;i<x+h;i++)	if (data[i][y]!=c)	break;
	if (i==x+h)	return true;
	for (i=x;i<x+h;i++)	if (data[i][y+w-1]!=c)	break;
	if (i==x+h)	return true;
	for (i=y;i<y+w;i++)	if (data[x][i]!=c)	break;
	if (i==y+w)	return true;
	for (i=y;i<y+w;i++)	if (data[x+h-1][i]!=c)	break;
	if (i==y+w)	return true;
	return false;
}

void redo(int dep)
{
	if (dep==N){
		string temp=permut;
		for (int i=0;i<temp.size();i++)	temp[i]=itocmap[temp[i]-'A'];
		reverse(temp.begin(),temp.end());
		ans.push_back(temp);
		return;
	}
	for (int j=0;j<N;j++)
	{
		if (used[j])	continue;
		for (int k=0;k<valid[j].size();k++)
		{
			vector<int>& vec=valid[j][k];
			if (checkwhole(vec[0],vec[1],vec[2],vec[3],j+'A')){
			used[j]=true;
			copy(backup[dep],data);
			color(vec[0],vec[1],vec[2],vec[3]);
			permut+=(j+'A');
			redo(dep+1);
			used[j]=false;
			permut.pop_back();
			copy(data,backup[dep]);
			break;
			}
		}
	}
}

void color(int x,int y,int h,int w)
{
	for (int i=x;i<x+h;i++)	data[i][y]=data[i][y+w-1]='@';
	for (int i=y;i<y+w;i++)	data[x][i]=data[x+h-1][i]='@';
}

void copy(char (&a)[MAXH+1][MAXW+1],char (&b)[MAXH+1][MAXW+1])
{
	for (int i=0;i<H;i++)
		for (int j=0;j<W;j++)	a[i][j]=b[i][j];
}
