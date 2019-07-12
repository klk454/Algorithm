#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define N (200011)
struct query{
	char op;
	int a, b;
} q[N];
map<int, int> mp;
vector<pii> per;
set<int> s[N];
map<pii, int> mp_idx;
int tree[N<<4];
void push(int x, int pos, int L, int R, int val){
	if(pos < L || pos > R)return;
	else if(pos == L && R == pos){
		tree[x]=max(tree[x], val);
		s[pos].insert(val);
		return;
	}
	int mid = (L+R)/2;
	push(2*x, pos, L, mid, val);
	push(2*x+1, pos, mid+1, R, val);
	tree[x] = max(tree[2*x], tree[2*x+1]);
	return;
}
pii get(int x, int pos, int L, int R, int val){
	if(pos > R || val >= tree[x])return pii(-1, -1);
	else if(L == R){
		auto it = upper_bound(s[L].begin(), s[L].end(), val);
		return pii(L, *it);
	}
	int mid = (L+R)/2;
	pii ret = get(2*x, pos, L, mid, val);
	if(ret.first==-1)ret = get(2*x+1,pos,mid+1,R,val);
	return ret;
}
int main(){
	int n;
	scanf("%d", &n);
	memset(tree, -1, sizeof(tree));
	for(int i=0; i<n; i++){
		scanf(" %c", &q[i].op);
		if(q[i].op == 'D'){
			scanf("%d %d", &q[i].b, &q[i].a);
			per.push_back(pii(q[i].a, q[i].b));
		}
		else scanf("%d", &q[i].a);
	}
	for(int i=0; i<per.size(); i++)mp[per[i].first]=0;
	int range=0;
	for(auto it=mp.begin(); it!=mp.end(); it++)it->second=++range;
	for(int i=0; i<per.size(); i++)per[i].first=mp[per[i].first];
	for(int i=0; i<per.size(); i++)mp_idx[per[i]]=i+1;
	for(int i=0; i<n; i++){
		if(q[i].op=='D')push(1, mp[q[i].a], 1, range, q[i].b);
		else{
			int idx = q[i].a-1;
			int a = per[idx].first, b = per[idx].second;
			pii ret(-1,-1);
			auto it = upper_bound(s[a].begin(), s[a].end(), b);
			if(it != s[a].end())ret.first=a, ret.second=*it;
			else ret = get(1, a+1, 1, range, b-1);
			if(ret.first==-1)printf("NE\n");
			else printf("%d\n", mp_idx[ret]);
		}
	}
	return 0;
}
