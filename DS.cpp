#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ll long long 
#define ii pair<int,int>
#define fi first
#define se second
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end
#define eb emplace_back
#define vi vector<int>
template<class T> using oset = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

//think backwards

struct BIT{
	vi bit;
	int N;
	void init(int n){
		N=n;
		bit.assign(n+1,0);
	}
	void add(int pos, int v){
		while(pos<=N){
			bit[pos]+=v;
			pos += pos&-pos;
		}
	}
	//sum from 1 to pos
	int sum(int pos){
		int ret = 0;
		while(pos){
			ret += bit[pos];
			pos -= pos&-pos;
		}
		return ret;
	}
	int query(int le, int ri){
		return sum(ri)-sum(le-1);
	}
};

struct ST{
	vi tree,lazy;
	void init(n){
		tree.assign(n*4,0);
		lazy.assign(n*4,0);
	}
	void puttag(int id,int le, int ri, int v){
		int len = ri-le+1;
		tree[id]+=v*len;
		lazy[id]+=v;
	}
	void pushdown(int id, int le, int ri){
		int x = lazy[id];
		lazy[id]=0;
		if(x==0||le==ri){
			return;
		}
		int mid=(le+ri)>>1;
		puttag(id*2,le,mid,v);
		puttag(id*2+1,mid+1,ri,v);
	}
	void pushup(int id, int le, int ri){
		tree[id]=tree[id*2]+tree[id*2+1];
	}
	//update by point
	void upd1(int x, int v, int id, int le, int ri){
		if(le==ri){
			puttag(id,v);
			return;
		}
		pushdown(id,le,ri);
		int mid=(le+ri)>>1;
		if(x<=mid)upd1(x,v,id*2,le,mid);
		else upd1(x,v,id*2+1,mid+1,ri);
		pushup(id,le,ri);
	}
	
	//update by range
	void upd2(int x, int y, int v, int id int le, int ri){
		if(x>ri||le>y||le<ri)return;
		if(x<=le&&ri<=y){
			puttag(id,le,ri,v);
			return;
		}
		pushdown(id,le,ri);
		int mid=(le+ri)>>1;
		upd2(x,y,v,id*2,le,mid);
		upd2(x,y,v,id*2+1,mid+1,ri);
		pushup(id,le,ri);
	}
	int query(int x, int y, int id, int le, int ri){
		if(x>ri||le>y)return 0;
		if(x<=le&&ri<=y){
			return tree[id];
		}
		pushdown(id,le,ri);
		int mid=(le+ri)>>1;
		int left = query(x,y,id*2,le,mid);
		int right = query(x,y,id*2+1,mid+1,ri);
		return left+right;
	}
}

struct DSU{
	vi par;
	int cc;
	void init(int n){
		par.resize(n+1);
		iota(all(par),0);
		cc=n;
	}
	int rt(int u){
		if(par[u]!=u)par[u]=rt(par[u]);
		return par[u];
	}
	bool merge(int u, int v){
		u=rt(u); v=rt(v);
		if(u==v)return 0;
		if(rand()%2)swap(u,v);
		par[u]=v;
		cc--;
		return 1;
	}
	bool sameset(int u, int v){
		u=rt(u); v=rt(v);
		return u==v;
	}
};

struct DSU2{ //with rollback
	vi par;
	int cc;
	vector<ii>updates;
	void init(int n){
		par.resize(n+1);
		iota(all(par),0);
		cc=n;
	}
	int rt(int u){
		if(par[u]!=u)return rt(par[u]);
		return par[u];
	}
	bool merge(int u, int v){
		u=rt(u); v=rt(v);
		if(u==v){
			updates.eb(-1,-1);
			return 0;
		}
		if(rand()%2)swap(u,v);
		updates.eb(v,par[v]);
		par[v]=u;
		cc--;
		return 1;
	}
	bool sameset(int u, int v){
		u=rt(u); v=rt(v);
		return u==v;
	}
	void rollback(){
		if(updates.empty())return;
		int v = updates.back().fi;
		int pv = updates.back().se;
		int curp = par[v]; //aka u
		//do whatever you want
		par[v]=pv;
	}
};

//centroid decomp
{
	const int mxn = 1e5;
	int siz[mxn];
	bool vis[mxn];
	void dfs_sz(int u, int p){
		siz[u]=1;
		for(int v:adj[u]){
			if(v==p||vis[v])continue;
			dfs_sz(v,u);
			siz[u]+=siz[v];
		}
	}
	int centroid(int u, int p, int sizz){
		for(int v:adj[u]){
			if(v==p||vis[v])continue;
			if(siz[v]*2>sizz)return centroid(v,u,sizz);
		}
		return u;
	}
	void solve(int u=0, int p=-1){
		dfs_sz(u,-1);
		int ct = centroid(u,-1,siz[u]);
		//do whatever you want to solve with your centroid, prolly dfs ct
		/* in func dfs
		 * for(int v:adj[ct]){
		 * 		if(v==p||vis[v])continue;
		 * 		
		 * }
		 */ 
		vis[ct]=1;
		for(int v:adj[u]){
			if(v==p||vis[v])continue;
			solve(v,u);
		}
	}
}

//geometry
struct pt{
	int x,y;
};

bool ccw(pt a, pt b, pt c){
	return 1ll*(b.x-a.x)*(c.y-a.y)>1ll*(b.y-a.y)*(c.x-a.x);
}

bool inside(pt a, pt b, pt c, pt x){
	int cnt = ccw(a,b,x)+ccw(b,c,x)+ccw(c,a,x);
	return cnt==0||cnt==3;
}
					
//wavelet tree
int a[100005];
struct WT{
	vector<vi>pos,val;
	void init(int n){
		pos.resize(n+1);
		val.resize(n+1);
		int le=1; //lowest value among elements
		int ri=(int)1e5; //highest value among elements
		for(int i=0; i<n; i++){
			val[1].eb(a[i]);
		}
		int mid=(le+ri)>>1;
		if(val[1][0]<=mid)pos[1].eb(1);
		else pos[1].eb(0);
		for(int i=1; i<sz(val[1]); i++){
			if(val[1][i]<=mid)pos[1].eb(pos.back()+1);
			else pos[1].eb(pos.back());
		}
		build(2,le,mid);
		build(2+1,mid+1,ri);
	}
	void build(int id, int le, int ri){
		int prev = id/2;
		for(int x:val[prev]){
			if(le<=x&&x<=ri)val[id].eb(x);
		}
		int mid=(le+ri)>>1;
		if(val[id].empty()||le==ri)return;
		if(val[id][0]<=mid)pos[id].eb(1);
		else pos[id].eb(0);
		for(int i=1; i<sz(val[1]); i++){
			if(val[id][i]<=mid)pos[1].eb(pos.back()+1);
			else pos[1].eb(pos.back());
		}
		build(id*2,le,mid);
		build(id*2+1,mid+1,ri);
	}
	//v-th smallest element in [x,y];id=1,le=lowest,ri=highest
	int query(int x, int y, int v, int id, int le, int ri){
		if(le==ri)return le;
		int mid=(le+ri)/2;
		int left=pos[id][y];
		if(x)left-=pos[id][x-1];
		int right = y-x+1-left;
		int le_n=0, ri_n=0;
		if(v<=left){
			if(x)le_n=pos[id][x-1];
			ri_n=le_n+left-1;
			return query(le_n,ri_n,v,id*2,le,mid);
		}else{
			v-=left;
			if(x)le_n=pos[id][x-1];
			ri_n=le_n+right-1;
			return query(le_n,ri_n,v,id*2+1,mid+1,ri);
		}
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	
	return 0;
}
