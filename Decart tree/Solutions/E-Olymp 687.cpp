#include <bits/stdc++.h>

using namespace std;

const int me = 10025;

typedef struct node{
    int value;
    int priority;
    int _size;
    struct node *l, *r;
}node;
typedef node* pnode;

int get_size(pnode node){
    return node ? node->_size : 0;
}
void update_size(pnode t){
    if(t)
        t->_size = get_size(t->l) + 1 + get_size(t->r);
}
void Split(pnode t, pnode &l, pnode &r, int key){
    if(!t)
        l = r = NULL;
    else if(t->value <= key)
        Split(t->r, t->r, r, key), l = t;
    else Split(t->l, l, t->l, key), r = t;
    update_size(t);
}
void Merge(pnode &t, pnode l, pnode r){
    if(!l)
        t = r;
    else if(!r)
        t = l;
    else if(l->priority > r->priority)
        Merge(l->r, l->r, r), t = l;
    else Merge(r->l, l, r->l), t = r;
    update_size(t);
}
void Insert(pnode &t, pnode it){
    if(!t)
        t = it;
    else if(it->priority > t->priority)
        Split(t, it->l, it->r, it->value), t = it;
    else if(t->value <= it->value)
        Insert(t->r, it);
    else Insert(t->l, it);
    update_size(t);
}
void Erase(pnode &t, int key){
    if(!t)
        return;
    if(t->value == key){
        pnode temp = t;
        Merge(t, t->l, t->r);
        free(temp);
    }
    else if(t->value < key)
        Erase(t->r, key);
    else Erase(t->l, key);
    update_size(t);
}
pnode Init(int val){
    pnode ret = (pnode)malloc(sizeof(node));
    ret->value = val;
    ret->priority = rand();
    ret->_size = 1;
    ret->l = ret->r = NULL;
    return ret;
}
void Insert(pnode &t, int key){
    pnode ret = Init(key);
    Insert(t, ret);
}
bool Find(pnode t, int key){
    if(!t)
        return false;
    else if(t->value == key)
        return true;
    else if(t->value < key)
        return Find(t->r, key);
    else return Find(t->l, key);
}
int Count_less(pnode t, int key){
    if(!t)
        return 0;
    else if(t->value >= key)
        return Count_less(t->l, key);
    else return get_size(t->l) + 1 + Count_less(t->r, key);
}
int Kth_element(pnode t, int k){
    if(get_size(t->l) + 1 == k)
        return t->value;
    else if(get_size(t->l) + 1 > k)
        return Kth_element(t->l, k);
    else return Kth_element(t->r, k - get_size(t->l) - 1);
}
int ans;
void get_next(pnode t, int key){
    if(!t);
    else if(t->value < key)
        get_next(t->r, key);
    else{
        ans = -1 ? t->value : min(ans, t->value);
        get_next(t->l, key);
    }
}
int Next_element(pnode t, int key){
    ans = -1;
    get_next(t, key);
    return ans;
}
void Print(pnode t){
    if(!t)
        return;
    if(t->l)
        Print(t->l);
    cout << (t->value) << " " << (t->priority) << endl;
    if(t->r)
        Print(t->r);
}
int main()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    pnode t = NULL;
    int q, x;
    int type;
    
    scanf("%d", &q);
    while(q --){
        scanf("%d %d", &type, &x);
        if(type == 1){
            Insert(t, x);
        }
        else if(type == -1){
            Erase(t, x);
        }
        else if(type == 0){
            printf("%d\n", Kth_element(t, get_size(t) - x + 1));
        }
    }
    
    return 0;
}
