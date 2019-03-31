/*ID: lpjwork1
TASK: charrec
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
const int INF=(1<<30),MAXL=1200;
struct dpnode{
	int corrup;
	string ans;
}dp[MAXL];
ofstream fout ("charrec.out");
ifstream fin ("charrec.in");
ifstream fontin ("font.in");

int N,line;
vector<vector<string> >font;
vector<string> data;

bool update(int);
bool unknown(int);
void readin(int,vector<string>&);
int gene_dup(vector<string>& tchar,char& dest);
int gene_ideal(vector<string>& tchar,char& dest);
int gene_missing(vector<string>& tchar,char& dest);
int compare(string& tchar,string& model);
void show(vector<string>& todo);

int main() {
	dp[0].corrup=0;
	
	fontin>>N;
	fin>>N;
	for (int i=1;i<=N;i++)	dp[i].corrup=INF;
	/*font file*/
	for (int i=0;i<27;i++)
	{
		vector<string> tfont;
		for (int j=0;j<20;j++)
		{
			string temp;
			fontin>>temp;
			tfont.push_back(temp);
		}
		font.push_back(tfont);
	//	show(tfont);
	}
	
	for (int i=0;i<N;i++)
	{
		string temp;fin>>temp;
		data.push_back(temp);
	}
	cout<<data.size()<<endl;
	for (line=0;line<=N;line++)
	{
		/*ideal success,no next checks*/
		if (update(20))	continue;
		update(19);
		update(21);
	}
	fout<<dp[N].ans<<endl;
	for (int i=0;i<=N;i++)	cout<<dp[i].corrup<<" ";cout<<endl;
    fout.close();fin.close();fontin.close();
    return 0;
}

bool update(int step)
{
	/*out of boundary*/
	if (line-step<0||dp[line-step].corrup==INF)	return false;
	vector<string> tchar;
	readin(step,tchar);
	//show(tchar);
	int potent;
	char appender;
	switch (step)
	{
		case 19:potent=gene_missing(tchar,appender);break;
		case 20:potent=gene_ideal(tchar,appender);break;
		case 21:potent=gene_dup(tchar,appender);break;
	}
	potent+=dp[line-step].corrup;
	/*update successly*/
	if (potent<dp[line].corrup){
		dp[line].corrup=potent;
		string temp=dp[line-step].ans+appender;
//		cout<<line<<endl;
		dp[line].ans=temp;
	}
	return appender=='?';
}

int compare(string& tchar,string& model)
{
	int ret=0;
	for (int i=0;i<tchar.size();i++)
		if (tchar[i]!=model[i])	ret++;
	return ret;
}

int gene_dup(vector<string>& tchar,char& dest)
{
	/*every line's difference with font's line:
	 *first colomn is line correspond,second colomn
	 *one line before
	 */
	int diff[21][2],mincor=INF;
	for (int i=0;i<27;i++)
	{
		int corrup=INF;
		for (int j=0;j<21;j++)	diff[j][0]=diff[j][1]=0;
		vector<string>& model=font[i];
		/*generate first colomn*/
		for (int j=0;j<20;j++)	diff[j][0]=compare(tchar[j],font[i][j]);
		for (int j=1;j<21;j++)	diff[j][1]=compare(tchar[j],font[i][j-1]);
		int tempcor=0;
		/*initial:first line deleted*/
		for (int j=1;j<21;j++)	tempcor+=diff[j][1];
		corrup=min(corrup,tempcor);
		/*line j recover,line j+1 deleted*/
		for (int j=0;j<20;j++)
		{
			tempcor+=diff[j][0];
			tempcor-=diff[j+1][1];
			corrup=min(corrup,tempcor);
		}
		if (corrup<mincor){
			mincor=corrup;
			dest=(i==0?' ':('a'+i-1));
		}
	}
	if (unknown(mincor))	dest='?';
	return mincor;
}

int gene_missing(vector<string>& tchar,char& dest)
{
	/*every line's difference with font's line:
	 *first colomn correspond,second colomn
	 *one more layer
	 */
	int diff[19][2],mincor=INF;
	for (int i=0;i<27;i++)
	{
		int corrup=INF;
		for (int j=0;j<19;j++)	diff[j][0]=diff[j][1]=0;
		vector<string>& model=font[i];
		/*generate first colomn*/
		for (int j=0;j<19;j++)	diff[j][0]=compare(tchar[j],font[i][j]);
		for (int j=0;j<19;j++)	diff[j][1]=compare(tchar[j],font[i][j+1]);
		int tempcor=0;
		/*initial:insert before first line*/
		for (int j=0;j<19;j++)	tempcor+=diff[j][1];
		corrup=min(corrup,tempcor);
		/*line j move before insert line*/
		for (int j=0;j<19;j++)
		{
			tempcor+=diff[j][0];
			tempcor-=diff[j][1];
			corrup=min(corrup,tempcor);
		}
		if (corrup<mincor){
			mincor=corrup;
			dest=(i==0?' ':('a'+i-1));
		}
	}
	if (unknown(mincor))	dest='?';
	return mincor;
}

int gene_ideal(vector<string>& tchar,char& dest)
{
	int corrup=INF;
	for (int i=0;i<27;i++)
	{
		vector<string>& model=font[i];
		int tcorrup=0;
		for (int j=0;j<20;j++)	tcorrup+=compare(tchar[j],model[j]);
		if (tcorrup<corrup){
			corrup=tcorrup;
			dest=(i==0?' ':('a'+i-1));
		}
	}
	if (unknown(corrup))	dest='?';
	return corrup;
}

void readin(int num,vector<string>& dest)
{
	dest.clear();
	for (int i=line-num;i!=line;i++)
		dest.push_back(data[i]);
//	show(dest);
}

bool unknown(int corrup)
{
	return corrup>0.3*20*20;
}

void show(vector<string>& todo)
{
	cout<<"////////////////////////////////////\n";
	for (int i=0;i<todo.size();i++)
		cout<<todo[i]<<endl;
}
