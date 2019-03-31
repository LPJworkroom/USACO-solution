/*ID: lpjwork1
TASK: dualpal
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
string tobase(int num,int base);
bool ispal(string str);
int main() {
	int N,S;
	cin>>N>>S;
	for (int i=S+1;N>0;i++)
	{
		int cnt=0;
		for (int base=2;cnt<2&&base<=10;base++)
		{
			if (ispal(tobase(i,base)))	cnt++;
		}
		if (cnt==2)	{
			N--;
			cout<<i<<endl;
		}
	}
    return 0;
}

string tobase(int num,int base)
{
	string ret;
	int cur;
	while (num>0)
	{
		cur=num%base;
		if (cur>=10)	ret+='A'+cur-10;
		else			ret+='0'+cur;
		num/=base;
	}
	reverse(ret.begin(),ret.end());
	return ret;
}

bool ispal(string str)
{
	string t=str;
	reverse(t.begin(),t.end());
	return t==str;
}
