/*ID: lpjwork1
TASK: frac1
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
const int MAXN=160*160+10;				// I caculated the max num of fractions wrongly!
struct node{
	int son,mum;
	double val;
};
bool operator<(node a,node b)	{	return a.val<b.val;	}
int N,tot=0;
node data[MAXN];
set<int> seen;
int gcd(int a,int b);
ofstream fout ("frac1.out");
ifstream fin ("frac1.in");
int main() {
	fin>>N;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=i;j++)
		{
			int tgcd=gcd(i,j),son=j/tgcd,mum=i/tgcd;
			if (seen.find(son*1000+mum)!=seen.end())	continue;		// I was wrong here:wrong hash function!!!
																		// I used 10 before(wrong when N>10)
			seen.insert(son*1000+mum);
			data[++tot]=node{son,mum,(double)son/mum};
		}
	sort(data+1,data+1+tot);
	fout<<"0/1"<<endl;
	for (int i=1;i<=tot;i++)
		fout<<data[i].son<<'/'<<data[i].mum<<endl;
    fout.close();fin.close();
    return 0;
}

int gcd(int a,int b)
{
	if (!a||!b)	return a>b?a:b;
	for (int temp;temp=a%b,temp;a=b,b=temp);
	return b;
}
