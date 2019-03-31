/*ID: lpjwork1
TASK: heritage
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
struct node{
	char val;
	int l,r;
} tree[30];
int tot=0;
string pre_order,in_order,ans;
int create(string&,string&);
void post(int);
ofstream fout ("heritage.out");
ifstream fin ("heritage.in");
int main() {
	fin>>in_order>>pre_order;
	create(pre_order,in_order);
	post(1);
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

int create(string& pre,string& in)
{
	if (pre.empty())	return 0;
	char now=pre[0];
	int index=++tot;
	tree[index].val=now;
	int cut=0;
	while (cut<in.size()&&in[cut]!=now)	cut++;
	cout<<cut<<' '<<pre.size()<<' '<<in.size()<<endl;
	cout<<pre<<' '<<in<<endl;
	
	string lpre(pre.begin()+1,pre.begin()+min((int)pre.size(),cut+1)),rpre(pre.begin()+min((int)pre.size(),cut+1),pre.end());
	string lin(in.begin(),in.begin()+min((int)in.size(),cut)),rin(in.begin()+min((int)in.size(),1+cut),in.end());
	tree[index].l=create(lpre,lin);
	tree[index].r=create(rpre,rin);
	return index;
}

void post(int ind)
{
	if (ind==0)	return;
	post(tree[ind].l);
	post(tree[ind].r);
	ans+=tree[ind].val;
}
