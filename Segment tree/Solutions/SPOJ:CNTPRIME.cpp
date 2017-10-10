/*
 O(T * (N + Q * log(N))) solution based on segment trees.
 For range updates, lazy propagation technique is used.
 In order to find primes, sieve is done at the beginning.
 */

#include <bits/stdc++.h>

using namespace std;

const int me = 50025;
const int MAX = 1000025;

int t, n, q, type, l, r, x;
int a[me], u[MAX], st[me << 2], lazy[me << 2];

int build(int I, int low, int high){
    if(low > high)
        return 0;
    if(low == high)
        return st[I] = u[ a[low] ];
    int mid = (low + high) >> 1;
    return st[I] = build(I + I, low, mid)
    + build(I + I + 1, mid + 1, high);
}
void push(int I, int low, int high){
    if(lazy[I] != -1){
        st[I] = (high - low + 1) * lazy[I];
        lazy[I + I] = lazy[I];
        lazy[I + I + 1] = lazy[I];
        lazy[I] = -1;
    }
}
void update(int I, int low, int high, int l, int r, int value){
    push(I, low, high);
    if(low > high || low > r || high < l)
        return;
    if(low >= l && high <= r){
        lazy[I] = value;
        push(I, low, high);
        return;
    }
    int mid = (low + high) >> 1;
    update(I + I, low, mid, l, r, value);
    update(I + I + 1, mid + 1, high, l, r, value);
    st[I] = st[I + I] + st[I + I + 1];
}
int get(int I, int low, int high, int l, int r){
    push(I, low, high);
    if(low > high || low > r || high < l)
        return 0;
    if(low >= l && high <= r)
        return st[I];
    int mid = (low + high) >> 1;
    return get(I + I, low, mid, l, r)
    + get(I + I + 1, mid + 1, high, l, r);
}
int main(){
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    for(int i = 2; i < MAX; i ++)
        if(!u[i])
            for(int j = i + i; j < MAX; j += i)
                u[j] = 1;
    for(int i = 1; i < MAX; i ++)
        u[i] ^= 1;
    
    scanf("%d", &t);
    for(int c = 0; c < t; c ++){
        scanf("%d%d", &n, &q);
        for(int i = 1; i < (me << 2); i ++)
            lazy[i] = -1;
        for(int i = 1; i <= n; i ++)
            scanf("%d", &a[i]);
        build(1, 1, n);
        printf("Case %d:\n", c + 1);
        while(q --){
            scanf("%d", &type);
            if(type == 0){
                scanf("%d%d%d", &l, &r, &x);
                update(1, 1, n, l, r, u[x]);
            }
            else{
                scanf("%d%d", &l, &r);
                printf("%d\n", get(1, 1, n, l, r));
            }
        }
    }
    
    return 0;
}
