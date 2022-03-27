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

const int mxn = (int)2e5+5;

void solve(){
    string s,t; cin>>s>>t;
    int n = s.length();
    int m = t.length();
    int ptr = 0, ptr2 = 0;
    while(ptr<n && ptr2<m){
        if(s[ptr]==t[ptr2]){
            ptr++;
            ptr2++;
        }else{
            ptr2++;
        }
    }
    if(ptr==n)cout<<m-n<<"\n";
    else cout<<"IMPOSSIBLE\n";
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
