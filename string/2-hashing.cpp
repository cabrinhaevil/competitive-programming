#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define hash apdmfoiwahofqjenfoj

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int maxn = 1e6;
const ll mod = 1e9+7;
ll pa = 0;
ll pb = 0;

ll power_a[maxn+7] = {};
ll power_b[maxn+7] = {};
ll inverse_a[maxn+7] = {};
ll inverse_b[maxn+7] = {};

ll modpow(ll x, ll n){
    if (n == 0) return 1;
    ll y = modpow(x, n/2);
    if (n&1) return y*y % mod * x % mod;
    return y*y % mod;
}

struct hash{
    int n;
    pair<ll, ll> val = {0, 0};
    pair<ll, ll> rval = {0, 0};
    vector<pair<ll, ll>>prefix;
    vector<pair<ll, ll>>suffix;

    hash(const string &s){
        n = (int)s.size();
        prefix.resize(n);
        suffix.resize(n);

        for(int i = 0;i < n;i++){
            (val.first += s[i]*power_a[i]) %= mod;
            (val.second += s[i]*power_b[i]) %= mod;
            prefix[i] = val;
        }

        for(int i = n-1;i >= 0;i--){
            (rval.first += s[i]*power_a[n-1-i]) %= mod;
            (rval.second += s[i]*power_b[n-1-i]) %= mod;
            suffix[i] = rval;
        }
    }

    pair<ll, ll> substr(int i, int j){
        if (i == 0) return prefix[j];
        pair<ll, ll>res = {0, 0};
        res.first = (prefix[j].first-prefix[i-1].first+mod) % mod *inverse_a[i] % mod;
        res.second = (prefix[j].second-prefix[i-1].second+mod) % mod *inverse_b[i] % mod;
        return res;
    }

    pair<ll, ll> rsubstr(int i, int j){
        if (j == n-1) return suffix[i];
        pair<ll, ll>res = {0, 0};
        res.first = (suffix[i].first-suffix[j+1].first+mod) % mod *inverse_a[n-1-j] % mod;
        res.second = (suffix[i].second-suffix[j+1].second+mod) % mod *inverse_b[n-1-j] % mod;
        return res;
    }

    bool is_palindrome(int i, int j){
        if (i == j) return true;
        int len = j-i+1;
        int k = len/2;
        return substr(i, i+k-1) == rsubstr(j-k+1, j);
    }
};

void build(){
    while(pa < 100) pa = rng();
    while(pb < 100) pb = rng();

    ll ipa = modpow(pa, mod-2);
    ll ipb = modpow(pb, mod-2);

    ll pwra = 1;
    ll pwrb = 1;
    ll ipwra = 1;
    ll ipwrb = 1;
    for(int i = 0;i < maxn;i++){
        power_a[i] = pwra;
        power_b[i] = pwrb;
        inverse_a[i] = ipwra;
        inverse_b[i] = ipwrb;
        (pwra *= pa) %= mod;
        (pwrb *= pb) %= mod;
        (ipwra *= ipa) %= mod;
        (ipwrb *= ipb) %= mod;
    }
}

int main(){

    build();

    string s = "abacaba";
    int n = (int)s.size();

    hash h(s);
    cout << h.is_palindrome(0, n-1) << endl;

    return 0;
}
