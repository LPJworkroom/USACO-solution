/*ID: lpjwork1
TASK: palsquare
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
int base;
string tobase(int);
bool ispal(string&);
ofstream fout ("palsquare.out");
ifstream fin ("palsquare.in");
int main() {
	fin>>base;
	for (int i=1;i<=300;i++)
	{
		int square=i*i;
		string t=tobase(square);
		if (ispal(t))	fout<<tobase(i)<<' '<<t<<endl;
	}
    fout.close();fin.close();
    return 0;
}

string tobase(int num)
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

bool ispal(string& str)
{
	string t=str;
	reverse(t.begin(),t.end());
	return t==str;
}
