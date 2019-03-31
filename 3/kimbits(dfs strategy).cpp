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
ll N,L,I,tot=0;
void gene(ll,ll,ll);
int onecnt(ll);
void showbinary(ll);
ofstream fout ("kimbits.out");
ifstream fin ("kimbits.in");
int main() {
	fin>>N>>L>>I;I--;
	gene(N,0,0);
	cout<<tot<<endl;
	while (tot>0)
	{
		I++;
		if (onecnt(I)>L)	tot++;
		tot--;
	}
	showbinary(I);
	string a;
	for (int i=0;i<N;i++)
	{
		if (I&1)	a+='1';
		else		a+='0';
		I>>=1;
	}
	reverse(a.begin(),a.end());
	fout<<a<<endl;
    fout.close();fin.close();
    return 0;
}

void gene(ll dep,ll done,ll curnum)
{
	if (curnum>I)	return;
	if (dep==0){
		if (done<=L)	return;
		tot++;return;
	}
	if (L-done+1<dep)	gene(dep-1,done,curnum);
	gene(dep-1,done+1,curnum+(1<<(dep-1)));
}

int onecnt(ll a)
{
	int ret=0;
	while (a)
	{
		a&=(a-1);
		ret++;
	}
	return ret;
}

void showbinary(ll n)
{
	string a;
	for (int i=0;i<N;i++)
	{
		if (n&1)	a+='1';
		else		a+='0';
		n>>=1;
	}
	reverse(a.begin(),a.end());
	cout<<a<<endl;
}
