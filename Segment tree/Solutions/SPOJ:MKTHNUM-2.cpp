/*
 O((N + Q) * log(N)) solution based on merge sort trees
 The problem has various solutions, including merge sort tree and sqrt decomposition.
 You can use static pool for nodes(pointers) in order to speed up the solution.
 */

#include <bits/stdc++.h>

using namespace std;

const int me = 100025;
const int MAX_LOG = 20;

int n, q, l, r, k;
int a[me], where[me], v[me];
int st[MAX_LOG][me << 2];

void Merge(int I, int l1, int r1, int l2, int r2){
    int ptr = l1;
    while(l1 <= r1 && l2 <= r2)
        st[I][ptr ++] = st[I + 1][l1] < st[I + 1][l2] ? st[I + 1][l1 ++] : st[I + 1][l2 ++];
    while(l1 <= r1)
        st[I][ptr ++] = st[I + 1][l1 ++];
    while(l2 <= r2)
        st[I][ptr ++] = st[I + 1][l2 ++];
}
void build(int I, int low, int high){
    if(low > high)
        return;
    if(low == high){
        st[I][low] = where[low];
        return;
    }
    int mid = (low + high) >> 1;
    build(I + 1, low, mid);
    build(I + 1, mid + 1, high);
    Merge(I, low, mid, mid + 1, high);
}
int get(int I, int low, int high, int l, int r){
    return upper_bound(st[I] + low, st[I] + high + 1, r) - lower_bound(st[I] + low, st[I] + high + 1, l);
}
int Kth_element(int I, int low, int high, int l, int r, int k){
    if(low == high)
        return low;
    int mid = (low + high) >> 1;
    int has = get(I + 1, low, mid, l, r);
    if(has >= k)
        return Kth_element(I + 1, low, mid, l, r, k);
    else
        return Kth_element(I + 1, mid + 1, high, l, r, k - has);
}
void compress(){
    map<int, int> m, pos;
    for(int i = 1; i <= n; i ++)
        m[ a[i] ] = 1;
    int ptr = 1;
    for(auto i : m)
        pos[i.first] = ptr ++;
    for(int i = 1; i <= n; i ++){
        int value = a[i];
        a[i] = pos[ a[i] ];
        where[ a[i] ] = i;
        v[ a[i] ] = value;
    }
}
int main(){
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    compress();
    build(1, 1, n);
    while(q --){
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", v[Kth_element(1, 1, n, l, r, k)]);
    }
    
    return 0;
}
