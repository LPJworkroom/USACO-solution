/*ID: lpjwork1
TASK: sprime
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
#define ll long long 
using namespace std;
int N;
void gen(int digi,int now);
bool isprime(int N);
bool test(ll,ll);
ofstream fout ("sprime.out");
ifstream fin ("sprime.in");
int main() {
	fin>>N;
	for (int i=1;i<=9;i++)
		if (isprime(i))
			gen(2,i);
    fout.close();fin.close();
    return 0;
}

void gen(int digi,int now)
{
	if (digi>N){
		if (isprime(now))	fout<<now<<endl;
		return;
	}
	for (int i=1;i<=9;i+=2)
	{
		int nxt=now*10;nxt+=i;
		if (isprime(nxt))	gen(digi+1,nxt);
	}
}

bool isprime(int N)
{
	if (N==2)	return true;
	if (!(N&1)||N==1)	return false;				// even 
	int a[8]={2,3,5,7,11,13,17,19};					// can generate a randomly
	for (int i=0;i<8&&N>=a[i];i++)
	{
		if (N==a[i])	return true;
		if (!test(N,a[i]))	return false;
	}
	return true;
}

bool test(ll p,ll a)
{
	ll ans=1,MOD=p;
	p--;
	while (p>0)
	{
		if (p&1){
			ans*=a;ans%=MOD;	
		}
		a*=a;a%=MOD;
		p>>=1;
	}
	return ans==1;
}
