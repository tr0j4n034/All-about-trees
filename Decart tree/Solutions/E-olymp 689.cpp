/// Date: 22.05.2016
/// Quite old one)

#include <bits/stdc++.h>

using namespace std;

const int me = 25;

typedef struct node{
    int value;
    long long subtree_value;
    int priority;
    int _cnt;
    node *l, *r;
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
        t->subtree_value = get_value(t->l) + t->value + get_value(t->r);
}
void Split(pnode t, pnode &l, pnode &r, int pos, int add = 0){
    if(!t)
        return void(l = r = NULL);
    int cur_pos = get_size(t->l) + add;
    if(cur_pos + 1 <= pos)
        Split(t->r, t->r, r, pos, cur_pos + 1), l = t;
    else Split(t->l, l, t->l, pos, add), r = t;
    update_size(t);
    update_value(t);
}
void Merge(pnode &t, pnode l, pnode r){
    if(!l || !r)
        t = l? l : r;
    else if(l->priority > r->priority)
        Merge(l->r, l->r, r), t = l;
    else Merge(r->l, l, r->l), t = r;
    update_size(t);
    update_value(t);
}
pnode Init(int key){
    pnode p = (pnode)malloc(sizeof(node));
    p->value = key;
    p->subtree_value = key;
    p->priority = rand();
    p->_cnt = 1;
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
bool Find(pnode t, int key){
    if(!t)
        return false;
    if(t->value == key)
        return true;
    if(t->value < key)
        return Find(t->r, key);
    return Find(t->l, key);
}
long long query(pnode &t, int l, int r){
    pnode l1, r1;
    Split(t, l1, r1, l - 1);
    pnode l2, r2;
    Split(r1, l2, r2, r - l + 1);
    long long res = get_value(l2);
    Merge(r1, l2, r2);
    Merge(t, l1, r1);
    return res;
}
int Kth_element(pnode t, int k){
    if(get_size(t->l) + 1 == k)
        return t->value;
    else if(get_size(t->l) + 1 > k)
        return Kth_element(t->l, k);
    return Kth_element(t->r, k - get_size(t->l) - 1);
}
void Swaper(pnode &t1, pnode &t2, int x, int y){
    /// t1 contains 1, 3, 5, 7...
    /// t2 contains 2, 4, 6...
    pair<int, int> ranges[2];
    ranges[0].first = (x + 2) >> 1;
    ranges[0].second = (y + 1) >> 1;
    ranges[1].first = (x + 1) >> 1;
    ranges[1].second = y >> 1;
    pnode parts[10];
    Split(t1, parts[0], parts[1], ranges[0].first - 1);
    Split(parts[1], parts[2], parts[3], ranges[0].second - ranges[0].first + 1); /// parts[2] will be used
    Split(t2, parts[4], parts[5], ranges[1].first - 1);
    Split(parts[5], parts[6], parts[7], ranges[1].second - ranges[1].first + 1); /// parts[6] will be used;
    swap(parts[2], parts[6]);
    Merge(parts[1], parts[2], parts[3]);
    Merge(t1, parts[0], parts[1]);
    Merge(parts[5], parts[6], parts[7]);
    Merge(t2, parts[4], parts[5]);
}
long long Swaper_query(pnode &t1, pnode &t2, int x, int y){
    long long res1 = 0, res2 = 0;
    pair<int, int> ranges[2];
    ranges[0].first = (x + 2) >> 1;
    ranges[0].second = (y + 1) >> 1;
    ranges[1].first = (x + 1) >> 1;
    ranges[1].second = y >> 1;
    if(ranges[0].first <= ranges[0].second){
        res1 = query(t1, ranges[0].first, ranges[0].second);
    }
    if(ranges[1].first <= ranges[1].second){
        res2 = query(t2, ranges[1].first, ranges[1].second);
    }
    return res1 + res2;
}

void Print(pnode t){
    if(!t)
        return;
    Print(t->l);
    cout << t->value << endl;
    Print(t->r);
}

int n, m;
int cases, x, type, l, r;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    /*
     t = NULL;
     for(int i = 0; i < 100; i ++){
     string type;
     int a, b;
     cin >> type;
     if(type == "insert"){
     cin >> a >> b;
     Insert(t, a, b);
     }
     else if(type == "erase"){
     cin >> a;
     Erase(t, a);
     }
     else if(type == "query"){
     cin >> a >> b;
     cout << query(t, a, b) << endl;
     }
     else if(type == "print"){
     for(int j = 1; j <= get_size(t); j ++)
     cout << j << " ---> " << Kth_element(t, j) << endl;
     }
     }
     */
    
    while(scanf("%d%d", &n, &m)){
        if(n == 0 && m == 0)
            break;
        if(cases > 0)
            putchar('\n');
        pnode t1 = NULL, t2 = NULL;
        for(int i = 1; i <= n; i ++){
            scanf("%d", &x);
            if(i & 1)
                Insert(t1, (i + 1) >> 1, x);
            else Insert(t2, i >> 1, x);
        }
        cases ++;
        printf("Swapper %d:\n", cases);
        while(m --){
            scanf("%d%d%d", &type, &l, &r);
            if(type == 1){
                Swaper(t1, t2, l, r);
            }
            else{
                printf("%lld\n", Swaper_query(t1, t2, l, r));
            }
        }
    }
    
    return 0;
}
