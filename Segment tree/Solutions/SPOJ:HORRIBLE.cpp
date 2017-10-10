/*
 O(T * Q * log(N)) solution based on segment trees.
 A good problem to practice segment trees.
 */

//#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <list>
#include <utility>
#include <cassert>

#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:200000000")

using namespace std;

#define mp make_pair
#define pb push_back
#define y1 lalalalalala
#define index lalalalalalala
#define forn(i, a, b) for(int i = a ; i <= b ; i ++)
#define fore(i, a, b) for(int i = a ; i >= b ; i --)
#define show(a, i) cout << "a[" << i << "] = " << a[i] << endl;
#define all(x) x.begin(), x.end()

typedef long long ll;
typedef pair<int, int>pii;
typedef pair<int, pair<int, int> >ppii;

const int MAX = 1.e5;
const int INF = 1.e9 + 1;
const double eps = 1.e-9;
const double PI = 3.14159265358979311599796;

int getint()
{
    char ch;
    int neg = 1;
    int val = 0;
    
    while (ch = getchar())
    {
        if (ch == '-')   neg = -1;
        else if (ch > 57 || ch < 48)  break;
        else val = 10 * val + ch - 48;
    }
    val = val * neg;
    return val;
}

vector<ll> a, st, lazy;
int t, n, q, f, l, r;
ll v;

ll build(int i, int low, int high)
{
    if (low > high)
        return 0LL;
    
    if (low == high)
    {
        st[i] = a[low];
        return st[i];
    }
    
    int mid = (low + high) >> 1;
    
    return st[i] = build(i << 1, low, mid)
    + build((i << 1) | 1, mid + 1, high);
}

void update(int i, int low, int high, int l, int r, int v)
{
    if (lazy[i] != 0)
    {
        st[i] += lazy[i] * (1LL * (high - low + 1));
        
        if (low != high)
        {
            lazy[i + i] += lazy[i];
            lazy[i + i + 1] += lazy[i];
        }
        
        lazy[i] = 0;
    }
    
    if (low > high || low > r || high < l)
        return;
    
    if (low >= l && high <= r)
    {
        st[i] += v * (1LL * (high - low + 1));
        
        if (low != high)
        {
            lazy[i + i] += v;
            lazy[i + i + 1] += v;
        }
        
        return;
    }
    
    int mid = (low + high) >> 1;
    
    update(i + i, low, mid, l, r, v);
    update(i + i + 1, mid + 1, high, l, r, v);
    
    st[i] = st[i + i] + st[i + i + 1];
}

ll query(int i, int low, int high, int l, int r)
{
    if (low > high || low > r || high < l)
        return 0;
    
    if (lazy[i] != 0)
    {
        st[i] += lazy[i] * (1LL * (high - low + 1));
        
        if (low != high)
        {
            lazy[i + i] += lazy[i];
            lazy[i + i + 1] += lazy[i];
        }
        
        lazy[i] = 0;
    }
    
    if (low >= l && high <= r)
        return st[i];
    
    int mid = (low + high) >> 1;
    
    return query(i << 1, low, mid, l, r)
    + query((i << 1) | 1, mid + 1, high, l, r);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(false);
    
    cin >> t;
    
    while (t--)
    {
        cin >> n >> q;
        
        //a.resize(n + 1, 0);
        st.resize((n << 3) + 1000);
        lazy.resize((n << 3) + 1000);
        
        //build(1, 1, n);
        
        fill(st.begin(), st.end(), 0LL);
        fill(lazy.begin(), lazy.end(), 0LL);
        
        while (q--)
        {
            cin >> f;
            
            if (f == 1)
            {
                cin >> l >> r;
                assert(l <= r);
                cout << query(1, 1, n, l, r) << endl;
            }
            else
            {
                cin >> l >> r >> v;
                assert(l <= r);
                update(1, 1, n, l, r, v);
                
            }
        }
    }
    return 0;
}
