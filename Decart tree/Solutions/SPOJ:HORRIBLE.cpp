/*
 O((N + Q) * log(N)) solution based on decart trees.
 Although the problem can be solved more efficiently by using Fenwick or
 Segment trees, i just wanted to demonstrate range updates in Decart trees.
 
 */

#include <bits/stdc++.h>

using namespace std;

const int me = 200025;

typedef struct node{
    long long value;
    long long subtree_value;
    long long lazy;
    int priority;
    int _cnt;
    bool rev;
    node *l;
    node *r;
}node;
typedef node* pnode;

int get_size(pnode t){
    return t? t->_cnt : 0;
}
long long get_value(pnode t){
    return t? t->subtree_value : 0;
}
void update_size(pnode t){
    if(t)
        t->_cnt = get_size(t->l) + 1 + get_size(t->r);
}
void update_value(pnode t){
    if(t)
        t->subtree_value = get_value(t->l) +
        get_value(t->r) + t->value;
}
void push_node(pnode t){
    if(t && t->rev){
        t->rev = 0;
        swap(t->l, t->r);
        if(t->l)
            t->l->rev ^= 1;
        if(t->r)
            t->r->rev ^= 1;
    }
    if(t && t->lazy){
        t->value += t->lazy;
        t->subtree_value += 1LL * (t->lazy) * get_size(t);
        if(t->l)
            t->l->lazy += t->lazy;
        if(t->r)
            t->r->lazy += t->lazy;
        t->lazy = 0;
    }
}
void Reset(pnode t){
    if(t)
        t ->subtree_value = t->value;
}
void combine(pnode &t, pnode l, pnode r){
    if(!l || !r)
        t = l ? l : r;
    else t->subtree_value = l->subtree_value + r->subtree_value;
}
void operation(pnode t){
    if(!t)
        return;
    Reset(t);
    push_node(t->l);
    push_node(t->r);
    combine(t, t->l, t);
    combine(t, t->r, t);
}
void Split(pnode t, pnode &l, pnode &r, int pos, int add = 0){
    if(!t)
        return void(l = r = NULL);
    push_node(t);
    int cur_pos = add + get_size(t->l);
    if(cur_pos + 1 <= pos)
        Split(t->r, t->r, r, pos, cur_pos + 1), l = t;
    else Split(t->l, l, t->l, pos, add), r = t;
    update_size(t);
    operation(t);
}
void Merge(pnode &t, pnode l, pnode r){
    push_node(l);
    push_node(r);
    if(!l || !r)
        t = l? l : r;
    else if(l->priority > r->priority)
        Merge(l->r, l->r, r), t = l;
    else Merge(r->l, l, r->l), t = r;
    update_size(t);
    operation(t);
}
pnode Init(int key){
    pnode p = (pnode)malloc(sizeof(node));
    p->value = key;
    p->priority = rand();
    p->subtree_value = key;
    p->rev = 0;
    p->_cnt = 1;
    p->lazy = 0;
    p->l = p->r = NULL;
    return p;
}
void Insert(pnode &t, pnode item, int pos){
    pnode l1, r1;
    Split(t, l1, r1, pos - 1);
    Merge(l1, l1, item);
    Merge(t, l1, r1);
}
void Insert(pnode &t, int pos, int key){
    pnode p = Init(key);
    Insert(t, p, pos);
}
void Erase(pnode &t, int pos){
    pnode l1, r1;
    Split(t, l1, r1, pos - 1);
    pnode l2, r2;
    Split(r1, l2, r2, 1);
    Merge(t, l1, r2);
}
void Reverse(pnode &t, int l, int r){
    pnode l1, r1;
    Split(t, l1, r1, l - 1);
    pnode l2, r2;
    Split(r1, l2, r2, r - l + 1);
    l2->rev ^= 1;
    Merge(r1, l2, r2);
    Merge(t, l1, r1);
}
void Add(pnode &t, int l, int r, int v){
    update_size(t);
    push_node(t);
    update_value(t);
    pnode l1, r1;
    Split(t, l1, r1, l - 1);
    pnode l2, r2;
    update_size(l1);
    push_node(l1);
    Split(r1, l2, r2, r - l + 1);
    l2->lazy += v;
    Merge(r1, l2, r2);
    Merge(t, l1, r1);
}
bool Find(pnode t, int key){
    if(!t)
        return false;
    if(t->value == key)
        return true;
    if(t->value < key)
        return Find(t->r, key);
    return Find(t->l, key);
}
int Kth_element(pnode t, int k){
    if(get_size(t->l) + 1 == k)
        return t->value;
    if(get_size(t->l) + 1 > k)
        return Kth_element(t->l, k);
    return Kth_element(t->r, k - get_size(t->l) - 1);
}
long long query(pnode &t, int l, int r){
    update_size(t);
    push_node(t);
    pnode l1, r1;
    Split(t, l1, r1, l - 1);
    pnode l2, r2;
    update_size(r1);
    push_node(r1);
    Split(r1, l2, r2, r - l + 1);
    //update_size(l2);
    push_node(l2);
    long long res = get_value(l2);
    Merge(r1, l2, r2);
    Merge(t, l1, r1);
    return res;
}
void Print(pnode t){
    if(!t)
        return;
    Print(t->l);
    cout << t->value << endl;
    Print(t->r);
}
int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    /*
     pnode t = NULL;
     for(int i = 0; i < 100; i ++){
     int a, b;
     string type;
     
     cin >> type;
     if(type == "insert"){
     cin >> a >> b;
     Insert(t, a, b);
     }
     else if(type == "erase"){
     cin >> a;
     Erase(t, a);
     }
     else if(type == "find"){
     cin >> a;
     if(Find(t, a))
     cout << a << " exists in tree" << endl;
     else cout << a << " does not exist in tree" << endl;
     }
     else if(type == "kth"){
     cin >> a;
     cout << Kth_element(t, a) << endl;
     }
     else if(type == "query"){
     cin >> a >> b;
     cout << query(t, a, b) << endl;
     }
     else if(type == "reverse"){
     cin >> a >> b;
     Reverse(t, a, b);
     }
     else if(type == "print"){
     for(int j = 1; j <= get_size(t); j ++)
     cout << j << "-th element is " << Kth_element(t, j) << endl;
     }
     }
     */
    pnode t = NULL;
    int tt, n, q, type, a, b, x;
    
    cin >> tt;
    while(tt --){
        cin >> n >> q;
        t = NULL;
        for(int i = 1; i <= n; i ++)
            Insert(t, i, 0);
        while(q --){
            cin >> type;
            if(type == 0){
                cin >> a >> b >> x;
                Add(t, a, b, x);
            }
            else{
                cin >> a >> b;
                cout << query(t, a, b) << endl;
            }
        }
    }
    
    return 0;
}
/**
 1
 8 6
 0 2 4 26
 0 4 8 80
 0 4 5 20
 1 8 8
 0 5 7 14
 1 4 8
 
 0 0 0 0 0 0 0 0
 0 26 26 26 0 0 0 0
 0 26 26 106 80 80 80 80
 0 26 26 126 100 80 80 80
 0 26 26 126 114 94 94 80
 */
