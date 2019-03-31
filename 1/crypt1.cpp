/*ID: lpjwork1
TASK: crypt1
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
int digiset[9],havedigi[10];
int N;
int generate(int now,int dig);
bool check(int num,int dig);
ofstream fout ("crypt1.out");
ifstream fin ("crypt1.in");
int main() {
	int ans=0,A,B,num1,num2,num3;
	fin>>N;
	for (int i=0;i<10;i++)	havedigi[i]=0;
	for (int i=0;i<N;i++)
	{
		fin>>digiset[i];
		havedigi[digiset[i]]=1;
	}
	//for (int i=0;i<N*N;i++)	generate(i,2);
	for (int i=0;i<N*N*N;i++)			//A
		for (int j=0;j<N*N;j++)			//B
		{
			A=generate(i,3);						//generate num with k digit
			B=generate(j,2);
			//cout<<A<<' '<<i<<' '<<B<<' '<<j<<endl;
			num1=B%10*A;num2=B/10*A;num3=A*B;
			if (check(num1,3)&&check(num2,3)&&check(num3,4)&&num1+num2*10==num3){
			//	cout<<"ok"<<endl;
				ans++;
			}
		}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

int generate(int now,int dig)
{
	//cout<<now;
	int ret=0;
	for (int i=1;i<=dig;i++)
	{
		ret+=digiset[now%N];
		ret*=10;
		now/=N;
	}
	//cout<<' '<<ret/10<<endl;
	return ret/10;
}

bool check(int num,int dig)
{
	int cur;
	for (int i=1;i<=dig;i++)
	{
		if (num==0)	return false;
		cur=num%10;
		if (!havedigi[cur])	return false;
		num/=10;
	}
	if (num>0)	return false;
	return true;
}
