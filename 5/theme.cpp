/*ID: lpjwork1
TASK: theme
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
#include<list>
#include<fstream>
using namespace std;
const int INF=(1<<30);
int N;
ofstream fout ("theme.out");
ifstream fin ("theme.in");
int main() {
	vector<int> data,diff;
	fin>>N;data.resize(N);diff.resize(N-1);
	for (int i=0;i<N;i++)	fin>>data[i];
	list<int> shift;
	for (int i=0;i<N;i++)	shift.push_back(data[i]);
	int ans=0;
	for (int i=1;i<=N;i++)
	{
		shift.pop_back();
		auto it=shift.begin();
		int maxlen=0,diff=INF,nowlen=0;
		for (int j=i+1;j<N;j++,it++)
		{
			int nowdiff=(*it)-data[j];
			if (nowdiff==diff){
				nowlen++;
				if (nowlen>=i)	nowlen=i;
				maxlen=max(maxlen,nowlen);
			}
			else	nowlen=0;
			diff=nowdiff;
		}
		ans=max(ans,maxlen);
	}
	if (ans<4)	fout<<0<<endl;
	else		fout<<ans+1<<endl;
    fout.close();fin.close();
    return 0;
}
