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
    string s; cin>>s;
    i64 sum = 0;
    for(auto &x:s){
        sum += (x-'0');
    }
    int jia;
    if(sum%9==0)
        jia = 0;
    else 
        jia = 9-sum%9;
    string ans = "";
    bool add = 0;
    if(jia==0){
        ans += s[0];
        ans += "0";
        for(int i=1; i<s.length(); i++)
            ans += s[i];
        cout<<ans<<"\n";
        return;
    }
    for(auto &x:s){
        int cur = x-'0';
        if(cur<=jia)
            ans += x;
        else if(!add)
            ans += char('0'+jia), add = 1, ans += x;
        else 
            ans += x;
    }
    if(!add)ans += char('0'+jia);
    cout<<ans<<"\n";
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
