/*ID: lpjwork1
TASK: contact
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
int A,B,N;
map<string,int> cnt;
string data;
bool cmp(pair<string,int>& a,pair<string,int>& b)
{
	if (a.second!=b.second)
		return a.second>b.second;
	else
	if (a.first.size()!=b.first.size())
		return a.first.size()<b.first.size();
	else
		return a.first<b.first;
}
ofstream fout ("contact.out");
ifstream fin ("contact.in");
int main() {
	fin>>A>>B>>N;
	string temp;
	while (fin>>temp)	data+=temp;
	//cout<<temp;
	for (int i=0;i<data.size();i++)
	{
		for (int j=A;i+j<=data.size()&&j<=B;j++)
			cnt[string(data.begin()+i,data.begin()+i+j)]++;
	}
	vector<pair<string,int> > vec;
	for (auto it:cnt){
		pair<string,int> temp;
		temp.first=it.first;temp.second=it.second;
		vec.push_back(temp);
	}
	sort(vec.begin(),vec.end(),cmp);
	//cout<<"ok"<<endl;
	fout<<vec[0].second<<endl<<vec[0].first;
	int level=1,cnt=1;
//	cout<<"ok"<<endl;
	for (int i=1;i<vec.size();i++)
		if (vec[i].second==vec[i-1].second){
			if (cnt==6){
				fout<<endl;cnt=0;
			}
			else	fout<<' ';
			fout<<vec[i].first;
			cnt++;
		}
		else{
			level++;
			if (level>N)	break;
			fout<<endl<<vec[i].second<<endl<<vec[i].first;
			cnt=1;
		}
	fout<<endl;
    fout.close();fin.close();
    return 0;
}
