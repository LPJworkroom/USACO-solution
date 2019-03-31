/*ID: lpjwork1
TASK: lamps
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
#include<set>
using namespace std;
const int MAXN=100;
int N,C,oncnt=0,offcnt=0,anscnt=0;
int finalon[MAXN+10],finaloff[MAXN+10];
set<string> ans;
string generate(int);
void b1(bool[]);
void b2(bool[]);
void b3(bool[]);
void b4(bool[]);
bool check(string&);
ofstream fout ("lamps.out");
ifstream fin ("lamps.in");
int main() {
	fin>>N>>C;
	while (1)
	{
		int temp;fin>>temp;
		if (temp==-1)	break;
		finalon[oncnt++]=temp;
	}
	while (1)
	{
		int temp;fin>>temp;
		if (temp==-1)	break;
		finaloff[offcnt++]=temp;
	}
	for (int state=0;state<16;state++)
	{
		string nowlamp=generate(state);
		//cout<<nowlamp<<endl;
		int cnt=0;
		for (int i=state;i;i&=(i-1))	cnt++;
		//cout<<cnt<<endl;
		if (C>=cnt&&(C-cnt)%2==0&&check(nowlamp))
			ans.insert(string(nowlamp.begin()+1,nowlamp.end()));
	}
	if (ans.empty())	fout<<"IMPOSSIBLE"<<endl;
	for (auto i:ans)	fout<<i<<endl;
    fout.close();fin.close();
    return 0;
}

string generate(int state)
{
	bool lamp[N+1];for (int i=1;i<=N;i++)	lamp[i]=true;
	if (state&1)	b1(lamp);	state>>=1;
	if (state&1)	b2(lamp);	state>>=1;
	if (state&1)	b3(lamp);	state>>=1;
	if (state&1)	b4(lamp);	state>>=1;
	string ret;ret+=';';
	//for (int i=0;i<N;i++)	printf("%d",)
	for (int i=1;i<=N;i++)	ret+=lamp[i]?'1':'0';
	return ret;
}

bool check(string& nowlamp)
{
	for (int i=0;i<oncnt;i++)
		if (nowlamp[finalon[i]]=='0')	return false;
	for (int i=0;i<offcnt;i++)
		if (nowlamp[finaloff[i]]=='1')	return false;
	return true;
}

void b1(bool lamp[])
{
	for (int i=1;i<=N;i++)	lamp[i]=!lamp[i];
}

void b2(bool lamp[])
{
	for (int i=1;i<=N;i++)	if (i&1)	lamp[i]=!lamp[i];	
}

void b3(bool lamp[])
{
	for (int i=1;i<=N;i++)	if (!(i&1))	lamp[i]=!lamp[i];	
}

void b4(bool lamp[])
{
	for (int i=1;i<=N;i++)	if ((i-1)%3==0)	lamp[i]=!lamp[i];	
}
