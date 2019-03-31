/*ID: lpjwork1
TASK: fracdec
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
#include<sstream>
using namespace std;
int a,b;	
string ans;
int seen[100000+10];
void input();
ofstream fout ("fracdec.out");
FILE* fin=fopen("fracdec.in","r");
int main() {
	input();
	int t=a/b;a=a%b;
	stringstream ss;ss<<t;
	ss>>ans;
	ans+='.';
	int i=ans.size();
	seen[a]=i-1;a*=10;
	while (1)
	{
		if (a==0)	break;
		int dd=a/b;a=a%b;
		if (seen[a]!=0){
			//cout<<a<<' '<<seen[a]<<endl;
			ans+=(dd+'0');
			ans.insert(ans.begin()+seen[a]+1,'(');
			ans.push_back(')');
			break;	
		}
		seen[a]=i;
		ans+=dd	+'0';
		a*=10;
		i++;
	}
	if (ans[ans.size()-1]=='.')	ans+='0';
	i=0;
	//ans="1234567890123456789012345678901234567890123456789012345678901234567890123456";
	while (i!=ans.size())
	{
		fout<<ans[i];
		i++;
		if (i%76==0)	fout<<endl;
	}
	if (i%76!=0)	fout<<endl;
    fout.close();fclose(fin);
    return 0;
}

void input()
{
	char temp;
	fscanf(fin,"%d%c%d",&a,&temp,&b);
}
