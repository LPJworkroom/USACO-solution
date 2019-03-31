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
/*save all rectangles*/
struct rect{
	int x1,y1,x2,y2;
}rectvec[MAXN];
/*node in Threadset*/
struct node{
	int val;
	bool isl;	//true if left,else right
};
/*STL set need operator<*/
bool operator<(const node a,const node b)
{
	return a.val<b.val;
}

int N;
/*scan line sets*/
set<node> up,down;
/*save all y coordinates*/
vector<int> yvec;
/*trans y coord to yvec index*/
map<int,int> yindex;

/*get overlap between up and down*/
int overlap(set<node>,set<node>);
/*insert thread to ThreadSet*/
void insert_cover(set<node>&,node&,node&);
/*get one ThreadSet perimetor*/
int perim(set<node>&,int);

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
	/*sort and unique*/
	sort(yvec.begin(),yvec.end());
	yvec.resize(unique(yvec.begin(),yvec.end())-yvec.begin());
	for (int i=0;i<yvec.size();i++)	yindex[yvec[i]]=i;
	
	int ans=0;
	
	for (int i=0;i<yvec.size();i++)
	{
		up=down;down.clear();
		for (int j=0;j<N;j++)
		{
			int x1=rectvec[j].x1,y1=rectvec[j].y1,
			x2=rectvec[j].x2,y2=rectvec[j].y2;
			/*not yet touch,or the rectangle all scanned*/
			if (y1!=yvec[i]||y1==y2)	continue;
			node tmpl{x1,true},tmpr{x2,false};
			insert_cover(down,tmpl,tmpr);
			/*cut thread down*/
			rectvec[j].y1=yvec[i+1];
		}
		ans+=perim(down,i);
		ans-=overlap(up,down);
	}
	
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

/*insert one node,combine overlap threads*/
void insert_cover(set<node>& lst,node& l,node& r)
{
	if (lst.empty()){
		lst.insert(l);lst.insert(r);return;
	}
	
	set<node>::iterator lptr=lst.upper_bound(l),rptr=lst.upper_bound(r);
	/*if l.val equals last element int lst*/ 
	if (lptr==lst.end()&&prev(lptr)->val==l.val)	--lptr;
	
	if (lptr==lst.end()||rptr==lst.begin()){
		lst.insert(l);lst.insert(r);
		return;
	}
	
	int newl,newr;
	if (lptr->isl==true){
		/*connect with prev thread*/
		if (lptr!=lst.begin()&&lptr->val==prev(lptr)->val)	--lptr,--lptr,newl=lptr->val;
		else	newl=l.val;
	}
	else					--lptr,newl=lptr->val;
	
	if (rptr==lst.end())	newr=r.val;
	else{
		if (rptr->isl==true)	newr=r.val;
		else					newr=rptr->val,rptr=next(rptr);
	}
	lst.erase(lptr,rptr);
	lst.insert(node{newl,true});
	lst.insert(node{newr,false});
}

int overlap(set<node> up,set<node> down)
{
	if (up.size()==0||down.size()==0)	return 0;
	int ret=0;
	set<node>::iterator upl=up.begin(),downl=down.begin(),upr,downr;
	while (upl!=up.end()&&downl!=down.end())
	{
		upr=next(upl);downr=next(downl);
		int maxl=max(upl->val,downl->val),minr=min(upr->val,downr->val);
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

int perim(set<node>& todo,int yind)
{
	int ret=0;
	for (set<node>::iterator it=todo.begin();it!=todo.end();++it,++it)
	{
		ret+=(yvec[yind+1]-yvec[yind])*2;	//height of rect
		ret+=((next(it)->val)-(it->val))*2;
	}
	return ret;
}
