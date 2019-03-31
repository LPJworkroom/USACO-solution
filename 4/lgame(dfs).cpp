/*ID: lpjwork1
TASK: lgame
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
const int cbase='a',scotab[26]={2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
int N,usedsize=0,maxsco=0;
int gave[26],cost[26],used[10];string collet;
vector<string> dic;
vector<int> score;
vector<vector<string> > ans;
bool veccmp(vector<string>& a,vector<string>& b)
{
	for (int i=0;i<a.size()&&i<b.size();i++)	if (a[i]!=b[i])	return a[i]<b[i];
	return a.size()<b.size();
}
bool cmp(string& a,string& b)
{
	return a.size()>b.size();
}

bool check();
void add(string&);
void erase(string&);
void getsco(int,int);
void getans(int,int);
int makesco(string&);
ofstream fout ("lgame.out");
ifstream fin ("lgame.in");
ifstream fdic("lgame.dict");
int main() {
	fin>>collet;
	for (int i=0;i<26;i++)	gave[i]=cost[i]=0;
	for (auto c:collet)	gave[c-cbase]++;
	/*get valid string*/
	while (1)
	{
		string temp;
		fdic>>temp;
		if (temp==".")	break;
		int mycount[26];memset(mycount,0,sizeof(mycount));
		for (int i=0;i<temp.size();i++)	mycount[temp[i]-cbase]++;
		int i;
		for (i=0;i<26;i++)
			if (mycount[i]>gave[i])	break;
		if (i==26)	dic.push_back(temp);
	}
	/*long string first*/
	sort(dic.begin(),dic.end(),cmp);
	N=dic.size();
	for (int i=0;i<N;i++)	score.push_back(makesco(dic[i]));
	getsco(0,0);cout<<maxsco<<endl;
	getans(0,0);
	for (int i=0;i<ans.size();i++)	sort(ans[i].begin(),ans[i].end());
	sort(ans.begin(),ans.end(),veccmp);
	fout<<maxsco<<endl;
	for (int i=0;i<ans.size();i++)
	{
		fout<<ans[i][0];
		for (int j=1;j<ans[i].size();j++)	fout<<' '<<ans[i][j];
		fout<<endl;
	}
    fout.close();fin.close();fdic.close();
    return 0;
}

int makesco(string& a)
{
	int ret=0;
	for (int i=0;i<a.size();i++)	ret+=scotab[a[i]-cbase];
	return ret;
}

void getans(int ind,int nowsco)
{
	if (nowsco==maxsco){
		vector<string> tempvec;
		for (int i=0;i<usedsize;i++)	tempvec.push_back(dic[used[i]]);
		ans.push_back(tempvec);
		return;
	}
	for (int i=ind;i<N;i++)
	{
		add(dic[i]);
		if (check()){
			used[usedsize++]=i;
			/*how many time have you done this?*/
			//getsco(i+1,nowsco+score[i]);
			getans(i+1,nowsco+score[i]);
			usedsize--;
		}
		erase(dic[i]);
	}
}

void getsco(int ind,int nowsco)
{
	for (int i=ind;i<N;i++)
	{
		add(dic[i]);
		if (check()){
			maxsco=max(maxsco,nowsco+score[i]);
			getsco(i+1,nowsco+score[i]);
		}
		erase(dic[i]);
	}
}

void erase(string& a)
{
	for (auto c:a)	cost[c-cbase]--;
}

bool check()
{
	int i;
	for (i=0;i<26;i++)
		if (gave[i]<cost[i])	break;
	return (i==26);
}

void add(string& a)
{
	for (auto c:a)	cost[c-cbase]++;
}

