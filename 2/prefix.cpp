/*ID: lpjwork1
TASK: prefix
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
using namespace std;
const int MAXN=200000,charbase='A';
vector<vector<string> > dic(27);
int ans=0;
string obj;
bool canreach[MAXN+10];
int max(int,int);
ofstream fout ("prefix.out");
ifstream fin ("prefix.in");
int main() {
	memset(canreach,false,sizeof(canreach));
	while (1)
	{
		string temp;fin>>temp;
		//cout<<"now:"<<temp<<endl;
		if (temp==".")	break;
		dic[temp[0]-charbase].push_back(temp);
	}
	while (1)
	{
		string temp;fin>>temp;
		if (temp.empty())	break;
		obj+=temp;
	}
	/*
	for (auto i:dic)
	{
		for (auto j:i)	cout<<j<<' ';
		cout<<endl;	
	}*/
	//cout<<obj<<endl;
	canreach[0]=true;
	for (int pos=0;pos<=ans;pos++)
		if (canreach[pos]){
			int nowchar=obj[pos];
			for (auto i:dic[nowchar-charbase])
			{
				//cout<<pos<<' '<<i<<' ';
				//string nxtstr="a";
				string nxtstr(obj.begin()+pos,obj.begin()+pos+min(obj.size(),i.size()));
				//cout<<nxtstr<<endl;
				if (i==nxtstr){		/*canmatch*/
					ans=max(ans,pos+i.size());
					canreach[pos+i.size()]=true;
				}
			}
		}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

int max(int a,int b)
{
	return a>b?a:b;
}
