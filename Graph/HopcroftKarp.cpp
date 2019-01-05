#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF (1e9)
#define N (1000011)
class HK{
public:
	queue<int> q;
	vector<int>* e;
	int* matA, *matB, *dep, nA, nB;
	HK(int nA=1000, int nB=1000){
		this->nA = nA;
		this->nB = nB;
		e = new vector<int>[nA+1];
		matA = new int[nA+1];
		matB = new int[nB+1];
		dep = new int[nA+1];
	}
	void add_edge(int u, int v){e[u].push_back(v);}
	bool bfs(){
		for(int i=1; i<=nA; i++){
			if(matA[i] == 0){
				dep[i]=0;
				q.push(i);
			}
			else dep[i]=INF;
		}
		dep[0]=INF;
		while(q.size()){
			int u = q.front(); q.pop();
			if(dep[u] < dep[0]){
				for(int i=0; i<e[u].size(); i++){
					int v = e[u][i];
					if(dep[matB[v]] == INF){
						dep[matB[v]] = dep[u]+1;
						q.push(matB[v]);
					}
				}
			}
		}
		return dep[0] != INF;
	}
	bool dfs(int u){
		if(u == 0)return true;
		for(int i=0; i<e[u].size(); i++){
			int v = e[u][i];
			if(dep[matB[v]] == dep[u] + 1){
				if(dfs(matB[v])){
					matA[u]=v;
					matB[v]=u;
					return true;
				}
			}
		}
		dep[u]=INF;
		return false;
	}
	int run(){
		for(int i=1; i<=nA; i++)matA[i]=0;
		for(int i=1; i<=nB; i++)matB[i]=0;
		int ret = 0;
		while(bfs()){
			for(int i=1; i<=nA; i++){
				if(matA[i]==0 && dfs(i)){
					ret++;
				}
			}
		}
		return ret;
	}
	~HK(){
		delete[] e;
		delete[] matA;
		delete[] matB;
		delete[] dep;
	}
};
int main(){
	int n;
	scanf("%d", &n);
	HK h = HK(n, 1000000);
	for(int i=1; i<=n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		h.add_edge(i, a);
		h.add_edge(i, b);
	}
	int mat = h.run();
	if(mat == n){
		for(int i=1; i<=n; i++)printf("%d\n", h.matA[i]);
	}
	else printf("-1\n");
	return 0;
}
