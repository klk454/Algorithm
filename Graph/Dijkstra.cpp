#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll, int>
#define INF (1e18)
class Dijkstra{
public:
	vector<pli>* e;
	ll* dist;
	int n;
	priority_queue<pli, vector<pli>, greater<pli> > pq;
	Dijkstra(int n=100001){
		this->n = n;
		e=new vector<pli>[n+1];
		dist=new ll[n+1];
		for(int i=1; i<=n; i++)dist[i]=INF;
	}
	void add_edge(int u, int v, ll cost){
		e[u].push_back(pli(cost, v));
	}
	void add_src(int src){
		dist[src]=0;
		pq.push(pli(0, src));
	}
	ll* process(){
		while(pq.size()){
			pli now = pq.top(); pq.pop();
			int u = now.second;
			ll d = now.first;
			if(d > dist[u])continue;
			for(int i=0; i<e[u].size(); i++){
				int v=e[u][i].second; ll c=e[u][i].first;
				if(dist[v] > dist[u] + c){
					dist[v] = dist[u] + c;
					pq.push(pli(dist[v], v));
				}
			}
		}
		return dist;
	}
	~Dijkstra(){delete[] e;delete[] dist;}
};
int main(){
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	Dijkstra p = Dijkstra(n);
	while(m--){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		p.add_edge(a, b, c);
	}
	p.add_src(s);
	ll* d = p.process();
	for(int i=1; i<=n; i++){
		if(d[i] == INF)printf("INF\n");
		else printf("%lld\n", d[i]);
	}
	return 0;
}
