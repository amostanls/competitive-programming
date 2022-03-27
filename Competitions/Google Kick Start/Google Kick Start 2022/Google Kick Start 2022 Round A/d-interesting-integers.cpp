#include <bits/stdc++.h>

using namespace std;

#define i64 long long
#define ii pair<int,int>
#define fi first
#define se second
#define ld long double
#define all(x) x.begin(),x.end()
#define sz(x) (int)x.size()
#define dbg if(0)
#define BUG(x) dbg cerr << (#x) << " is " << (x) << endl

int A[15],B[15];
//    cnt  a  b  0 prod  sum
i64 dp[13][2][2][2][110][110];
int vis[13][2][2][2][110][110];
int tar=0;
int visnum=0;

i64 calc(int pos, int aok, int bok, int zero, int prod, int sum){
    if(pos == -1)
        return sum == tar && prod == 0;
    
    if(vis[pos][aok][bok][zero][prod][sum] == visnum)
        return dp[pos][aok][bok][zero][prod][sum];

    i64 res = 0;
    vis[pos][aok][bok][zero][prod][sum] = visnum;

    for(int d = 0; d < 10; d++){
        if(!aok && d < A[pos])continue; 
        if(!bok && d > B[pos])continue;

        int naok = aok || d > A[pos];
        int nbok = bok || d < B[pos];

        int nzero = zero && d == 0;
        int nprod = (prod * d) % tar;
        if(nzero) nprod = 1;
        int nsum = sum + d;

        res += calc(pos-1, naok, nbok, nzero, nprod, nsum);
    }

    return dp[pos][aok][bok][zero][prod][sum] = res;
}

void solve(){
    string a,b; cin>>a>>b;
    
    reverse(all(a));
    reverse(all(b));
    
    memset(dp,0,sizeof(dp));
    memset(vis,0,sizeof(vis));
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));
    
    for(int i=0; i<a.length(); i++)
        A[i] = a[i]-'0';
    for(int i=0; i<b.length(); i++)
        B[i] = b[i]-'0';
    
    i64 ans = 0;
    for(int i=1; i<=108; i++){
        tar = i;
        visnum = i;
        ans += calc(12,0,0,1,1,0);
    }
    cout<<ans<<'\n';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin>>t;
    for(int i=1; i<=t; i++){
        cout<<"Case #"<<i<<": ";
        solve();
    }
    return 0;
}
