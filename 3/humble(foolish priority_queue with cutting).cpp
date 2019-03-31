/*ID: lpjwork1
TASK: humble
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
const int MAXK=100,MAXN=100000;
int K,N;
int primes[MAXK+1];
set<ll> seen;
priority_queue<ll,vector<ll>,greater<ll> > pq;
ofstream fout ("humble.out");
ifstream fin ("humble.in");
int main() {
	fin>>K>>N;
	for (int i=0;i<K;i++)	fin>>primes[i];
	sort(primes,primes+K);
	for (int i=0;i<K;i++)
	{
		pq.push(primes[i]);
		seen.insert(primes[i]);
	}
	ll ceiling=0;
	for (int i=1;i<N;i++)
	{
		//if (i%1000==0)
		//	cout<<i<<' ';
		ll now=pq.top();pq.pop();
		//if (i%1000==0)	cout<<now<<endl;
		for (int j=0;j<K;j++)
		{
			ll temp=primes[j]*now;
			if ((ceiling==0||temp<ceiling)&&seen.find(temp)==seen.end()){
				pq.push(temp);
				seen.insert(temp);
				if (ceiling==0&&pq.size()>=N)	ceiling=temp;
			}
		}
	}
	fout<<pq.top()<<endl;
    fout.close();fin.close();
    return 0;
}
