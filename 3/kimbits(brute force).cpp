/*ID: lpjwork1
TASK: kimbits
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
#define ll long long 
ll N,L,I,tot=0,ans;
ll maxcnt=0;
ll combine[40][40]={0};
void rev_gene(ll,ll,ll);
void gene(ll,ll,ll);
ofstream fout ("kimbits.out");
ifstream fin ("kimbits.in");
int main() {
	for (int i=0;i<=31;i++){
		combine[0][i]=1;
	}
	fin>>N>>L>>I;
	//cout<<I<<endl;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=i;j++)
			combine[j][i]=combine[j-1][i-1]+combine[j][i-1];
	/*	
	for (int i=0;i<=N;i++)
	{
		for (int j=0;j<=N;j++)	cout<<combine[j][i]<<' ';
		cout<<endl;
	}
	*/
	for (int i=0;i<=L;i++)	maxcnt+=combine[i][N];
	cout<<maxcnt<<' '<<I<<endl;
	if (maxcnt-I<I){
		I=maxcnt-I+1;
		cout<<"rev gene"<<endl;
		//cout<<I<<endl;
		//cout<<"ok"<<endl;
		rev_gene(N,L,0);
	}
	else{
		//for (int i=1;i<=N;i++)
			gene(N,L,0);
	}
	//cout<<ans<<endl;
	string a;
	for (int i=0;i<N;i++)
	{
		if (ans&1)	a+='1';
		else		a+='0';
		ans>>=1;
	}
	reverse(a.begin(),a.end());
	fout<<a<<endl;
    fout.close();fin.close();
    return 0;
}

void gene(ll dep,ll last,ll curnum)
{
	if (tot>I)	return;
	if (dep==0){
		//cout<<curnum<<endl;
		tot++;
		if (tot%10000000==0)	cout<<tot<<endl;
		if (tot==I)//	fout<<curnum<<endl;
		ans=curnum;
		return;
	}
	if (last==0)	gene(0,last,curnum);
	else	{
		gene(dep-1,last,curnum);
		gene(dep-1,last-1,curnum+(1<<(dep-1)));
	}
}

void rev_gene(ll dep,ll last,ll curnum)
{
	if (tot>I)	return;
	if (dep==0){
		//cout<<curnum<<endl;
		tot++;
		if (tot%10000000==0)	cout<<tot<<endl;
		if (tot==I)//	fout<<curnum<<endl;
		ans=curnum;
		return;
	}
	if (last==0)	rev_gene(0,last,curnum);
	else{
		rev_gene(dep-1,last-1,curnum+(1<<(dep-1)));
		rev_gene(dep-1,last,curnum);	
	}
}
