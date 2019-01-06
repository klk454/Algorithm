#include <bits/stdc++.h>
using namespace std;
#define INF (1e9)
class Dinic{
public:
	class Edge{
	public:
		int v, cap, inv_idx;
		Edge(int v, int cap, int inv_idx){
			this->v = v;
			this->cap = cap;
			this->inv_idx = inv_idx;
		}
	};
	vector<Edge> *e;
	int* dep, *st, n;
	Dinic(int n){
		this->n = n;
		dep = new int[n];
		st = new int[n];
		e = new vector<Edge>[n];
	}
	void add_edge(int u, int v, int cap){
		Edge edge = Edge(v, cap, e[v].size());
		Edge rev_edge = Edge(u, 0, e[u].size());
		e[u].push_back(edge);
		e[v].push_back(rev_edge);
	}
	bool bfs(int src, int sink){
		queue<int> q;
		q.push(src);
		for(int i=0; i<n; i++)dep[i]=-1;
		dep[src]=0;
		while(q.size()){
			int now = q.front(); q.pop();
			for(int i=0; i<e[now].size(); i++){
				Edge edge = e[now][i];
				if(dep[edge.v] != -1 || edge.cap == 0)continue;
				q.push(edge.v);
				dep[edge.v] = dep[now] + 1;
			}
		}
		return dep[sink] != -1;
	}
	int dfs(int x, int sink, int flow){
		if(x == sink)return flow;
		for(int& i=st[x]; i<e[x].size(); i++){
			Edge edge = e[x][i];
			if(edge.cap == 0 || dep[edge.v] != dep[x] + 1)continue;
			if(int ret = dfs(edge.v, sink, min(flow, edge.cap))){
				e[x][i].cap -= ret;
				e[edge.v][edge.inv_idx].cap += ret;
				return ret;
			}
		}
		return 0;
	}
	int run(int src, int sink){
		int ret = 0;
		while(bfs(src, sink)){
			for(int i=0; i<n; i++)st[i]=0;
			while(int t = dfs(src, sink, INF))ret += t;
		}
		return ret;
	}
	~Dinic(){
		delete[] e;
		delete[] dep;
	}
};
int main(){
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	Dinic d = Dinic(n+m+3);
	int sink = n+m+2;
	int two = n+m+1;
	int src = 0;
	d.add_edge(src, two, k);
	for(int i=1; i<=n; i++){
		int a, b;
		scanf("%d", &a);
		while(a--){
			scanf("%d", &b);
			d.add_edge(i, n+b, 1);
		}
		d.add_edge(src, i, 1);
		d.add_edge(two, i, 1);
	}
	for(int i=n+1; i<=n+m; i++)d.add_edge(i, sink, 1);
	int ans = d.run(src, sink);
	printf("%d\n", ans);
	return 0;
}
