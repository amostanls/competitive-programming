#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define eb emplace_back
#define mt make_tuple
#define all(x) (x).begin(), (x).end() 
#define MOD 1000000007

typedef long long ll;
typedef pair <int, int> ii;
typedef pair <ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef long double ld;

const ll INF=LLONG_MAX;
const int mxn=1e5+5;
vi adj[mxn];
int sz[mxn],dist[mxn],n,ans[mxn];

void dfs(int u, int p=-1){
	sz[u]=1;
	dist[u]=0;
	for(int v:adj[u]){
		if(v==p)continue;
		dfs(v,u);
		sz[u]+=sz[v];
		dist[u]+=dist[v]+sz[v];
	}
}

void dfs2(int u, int p=-1){
	for(int v:adj[u]){
		if(v==p)continue;
		dist[v] += dist[u]-sz[v]-dist[v];
		dist[v] += n-sz[v];
		dfs2(v,u);
	}
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
	cin >> n;
	for(int i=0; i<n-1; i++){
		int u,v;
		cin >> u >> v;
		u--; v--;
		adj[u].eb(v);
		adj[v].eb(u);
	}
	dfs(0);
	dfs2(0);
	for(int i=0; i<n; i++){
		cout << i << ' ' << dist[i] << endl;
	}
}
	
// READ & UNDERSTAND
// ll, int overflow, array bounds, memset(0)
// special cases (n=1?), n+1 (1-index)
// do smth instead of nothing & stay organized
// WRITE STUFF DOWN
