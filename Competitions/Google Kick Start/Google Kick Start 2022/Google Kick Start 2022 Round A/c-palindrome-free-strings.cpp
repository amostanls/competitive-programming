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

int n;
string s;
bool can;

bool check(int cnt, string &tmp){
    if(tmp.length()<cnt)return true;
    for(int i=0; i<3; i++){
        int now = tmp.length()-1-i;
        int opp = tmp.length()-cnt+i;
        if(tmp[tmp.length()-1-i]!=tmp[opp])return true;
    }
    return false;
}

void Solve(int ptr, string tmp){
    if(ptr==n){
        can = 1;
        return;
    }
//    cout<<ptr<<" "<<tmp<<"\n";
    if(s[ptr]=='?'){
        if(tmp.length()==6){
            reverse(all(tmp));
            tmp.pop_back();
            reverse(all(tmp));
        }
        tmp.push_back('0');
        if(check(5,tmp)&&check(6,tmp)){
            Solve(ptr+1,tmp);
        }
        if(can)return;
        tmp.back()='1';
        if(check(5,tmp)&&check(6,tmp)){
            Solve(ptr+1,tmp);
        }
        if(can)return;
    }else{
        if(tmp.length()==6){
            reverse(all(tmp));
            tmp.pop_back();
            reverse(all(tmp));
        }
        tmp.push_back(s[ptr]);
        if(check(5,tmp)&&check(6,tmp)){
            Solve(ptr+1,tmp);
        }
        if(can)return;
    }
}

void solve(){
    cin>>n;
    cin>>s;
    if(n<=4){
        cout<<"POSSIBLE\n";
        return;
    }
    can = 0;
    Solve(0,"");
    if(can){
        cout<<"POSSIBLE\n";
    }else{
        cout<<"IMPOSSIBLE\n";
    }
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
