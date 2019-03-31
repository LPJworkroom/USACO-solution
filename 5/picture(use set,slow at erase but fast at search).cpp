/*ID: lpjwork1
TASK: picture
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<list>
#include<string>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
#include<fstream>
using namespace std;
const int MAXN=5000+10;
struct rect{
	int x1,y1,x2,y2;
}rectvec[MAXN];
struct node{
	int val;
	bool isl;	//true if left,else right
};
bool operator<(const node a,const node b)
{
	return a.val<b.val;
}
int allcnt=0,goodcnt=0,movcnt=0;

int N;
/*core struct to store list of thread*/
vector<set<node> > graph;
vector<int> yvec;
/*trans y coord to yvec index*/
map<int,int> yindex;

int overlap(set<node>,set<node>);
void insert_cover(set<node>&,node&,node&);
int perim(int);

ofstream fout ("picture.out");
ifstream fin ("picture.in");
int main() {
	fin>>N;
	for (int i=0;i<N;i++)
	{
		int x1,y1,x2,y2;fin>>x1>>y1>>x2>>y2;
		rectvec[i]=rect{x1,y1,x2,y2};
		yvec.push_back(y1);yvec.push_back(y2);
	}
	
	//sort and unique yvec
	sort(yvec.begin(),yvec.end());
	yvec.resize(unique(yvec.begin(),yvec.end())-yvec.begin());
	for (int i=0;i<yvec.size();i++)	yindex[yvec[i]]=i;
	cout<<"yvec size:"<<yvec.size()<<endl;
	graph.resize(yvec.size());
	cout<<"ok"<<endl;
	//insert every rect to graph
	for (int i=0;i<N;i++)	
	{
		int x1=rectvec[i].x1,y1=rectvec[i].y1,
			x2=rectvec[i].x2,y2=rectvec[i].y2;
		for (int j=yindex[y1];j!=yindex[y2];j++)
		{
//			cout<<"insert to:"<<yvec[j]<<"--"<<yvec[j+1]<<':'<<x1<<','<<x2<<endl;
			node tmpl{x1,true},tmpr{x2,false};
			insert_cover(graph[j],tmpl,tmpr);
		}
	}
	cout<<"insert ok"<<endl;
	 /*
	for (int i=0;i<yindex.size()-1;i++)
	{
		cout<<yvec[i]<<"--"<<yvec[i+1]<<':';
		for (set<node>::iterator j=graph[i].begin();j!=graph[i].end();j++)
		{
			cout<<j->val<<'(';
			if (j->isl)	cout<<"left)";
			else		cout<<"right)";
			cout<<' ';
		}
		cout<<endl;
	}
 */
	//sum up rects perimeter
	int ans=0;
	for (int i=0;i!=yvec.size()-1;i++)	ans+=perim(i);
//	cout<<"perimetor ok"<<endl;
	cout<<ans<<endl;
	//minus overlap
	for (int i=0;i!=yvec.size()-1;i++){
		int temp=overlap(graph[i],graph[i+1]);
//		cout<<"overlap between "<<yvec[i]<<','<<yvec[i+1]<<" and "<<yvec[i+1]<<','<<yvec[i+2]<<':'<<temp<<endl;
		ans-=temp;
	}
	cout<<"goodcnt:"<<goodcnt<<endl;
	cout<<"allcnt:"<<allcnt<<endl;
	cout<<"movcnt:"<<movcnt<<endl;
	fout<<ans<<endl;
	cout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

/*insert one node to list,combine overlap threads*/
void insert_cover(set<node>& lst,node& l,node& r)
{
	allcnt++;
	if (lst.empty()){
		lst.insert(l);lst.insert(r);return;
	}
	set<node>::iterator lptr=lst.upper_bound(l),rptr=lst.upper_bound(r);
	if (lptr==lst.end()&&prev(lptr)->val==l.val)	lptr--;
	if (lptr==lst.end()||rptr==lst.begin()){
		lst.insert(l);lst.insert(r);
		return;
	}
	
	int newl,newr;
	if (lptr->isl==true){
		if (lptr!=lst.begin()&&lptr->val==prev(lptr)->val)	--lptr,--lptr,newl=lptr->val;
		else	newl=l.val;
	}
	else					--lptr,newl=lptr->val;
	if (rptr==lst.end())	newr=r.val,rptr=prev(rptr);
	else{
		if (rptr->isl==true)	newr=r.val,rptr=prev(rptr);
		else					newr=rptr->val;
	}
//	cout<<"newl,newr:"<<newl<<','<<newr<<endl;
	lst.erase(lptr,next(rptr));
	lst.insert(node{newl,true});
	lst.insert(node{newr,false});
	
}

int overlap(set<node> up,set<node> down)
{
	if (up.size()==0||down.size()==0)	return 0;
	if (up.size()%2==1||down.size()%2==1)	cout<<"wrong size!"<<up.size()<<endl;
	int ret=0;
	set<node>::iterator upl=up.begin(),downl=down.begin(),upr,downr;
	while (upl!=up.end()&&downl!=down.end())
	{
		upr=next(upl);downr=next(downl);
		//if (upr==up.end()||downr==down.end())	cout<<"?"<<endl;
		int maxl=max(upl->val,downl->val),minr=min(upr->val,downr->val);
		/*threads overlap*/
		if (maxl<minr){
			ret+=2*(minr-maxl);
			if (upl->val>downl->val&&upr->val>downr->val){
				node tmp{downr->val,true};
				up.insert(tmp);
				up.erase(upl);
				upl=up.find(tmp);
			}
			if (downl->val>upl->val&&downr->val>upr->val){
				node tmp{upr->val,true};
				down.insert(tmp);
				down.erase(downl);
				downl=down.find(tmp);
			}
		}
		if (upr->val<downr->val)	upl++,upl++;
		else						downl++,downl++;
	}
	return ret;
}

int perim(int yind)
{
//	cout<<"perimetor:"<<yind<<" size:"<<graph[yind].size()<<endl;
	int ret=0;
	for (set<node>::iterator it=graph[yind].begin();it!=graph[yind].end();++it,++it)
	{
		ret+=(yvec[yind+1]-yvec[yind])*2;	//height of rect
		ret+=((next(it)->val)-(it->val))*2;
	}
//	cout<<" is:"<<ret<<endl;
	return ret;
}
