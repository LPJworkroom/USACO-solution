/*ID: lpjwork1
TASK: pprime
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
int pow10[10]={1,10,100,1000,10000,100000,1000000,10000000,1000000000};
int a,b;
bool isprime(int);
bool test(ll,ll);
void generate(int);
ofstream fout ("pprime.out");
ifstream fin ("pprime.in");
int main() {
	fin>>a>>b;
	int cnta=0,cntb=0;
	for (int i=a;i;i/=10)	cnta++;
	for (int i=b;i;i/=10)	cntb++;
	for (int i=cnta;i<=cntb;i++)
		generate(i);
    fout.close();fin.close();
    return 0;
}

void generate(int cnt)
{
	bool isodd=(cnt&1);
	cnt--;
	for (int i=pow10[cnt/2];i<pow10[cnt/2+1];i++)					// bef half part
	{
		int ans=0,tnum=i;
		if (isodd){
			ans+=(tnum%10)*pow10[cnt/2];tnum/=10;
		}
		int di=cnt/2;if (isodd)	di--;
		for (;di>=0;di--)
		{
			int nowdi=tnum%10;
			ans+=nowdi*pow10[di]+nowdi*pow10[cnt-di];
			tnum/=10;
		}
		if (ans<a)	continue;
		if (ans>b)	return;
	//	cout<<ans<<endl;
		if (isprime(ans))	fout<<ans<<endl;
	}
}

bool isprime(int N)
{
	if (!(N&1))	return false;				// even 
	int a[5]={2,3,5,7,11};					// can generate a randomly
	for (int i=0;i<5&&N>=a[i];i++)
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
		if (p&1)	
			/*for (int i=1,tans=ans;i<a;i++)
			{
				ans+=tans;ans%=MOD;					//ans*=a;
			}*/
		{	ans*=a;ans%=MOD;}
		/*for (int i=a,ta=a;i>1;i--)
		{
			a+=ta;a%=MOD;
		}*/
		a*=a;a%=MOD;
		p>>=1;
	}
	return ans==1;
}

