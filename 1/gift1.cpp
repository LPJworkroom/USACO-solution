/*ID: lpjwork1
TASK: gift1
LANG: C++11
*/
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");
	map<string,int> acc;
	vector<string> rank;
    int N;fin>>N;
    for (int i=0;i<N;i++){
    	string str;fin>>str;
    	rank.push_back(str);
    	//cout<<str<<endl;
    	acc[str]=0;
	}
	for (int i=0;i<N;i++)
	{
		string str;int mon;
		fin>>str>>mon;
		//cout<<str<<' '<<mon<<endl;
		int n,gift=0;fin>>n;
		if (n!=0){
			gift=mon/n;acc[str]-=gift*n;
		//	cout<<gift<<' '<<acc[str]<<endl;
		}
		for (int j=0;j<n;j++)
		{
			string t;fin>>t;
			acc[t]+=gift;
		}
	}
	//cout<<"ok"<<endl;
	for (int i=0;i<N;i++){
		fout<<rank[i]<<' '<<acc[rank[i]]<<endl;
		//cout<<rank[i]<<' '<<acc[rank[i]]<<endl;
	}
	fout.close();fin.close();
    return 0;
}
