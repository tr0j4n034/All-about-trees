//
//  main.cpp
//  practice
//
//  Created by Mahmud on 7/1/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>

using namespace std;

const int S = 100005;

struct node{
    int value;
    node *l;
    node *r;
    node () {
        
    }
};
typedef node* pnode;

int getValue(pnode &p) {
    return p ? p->value : 0;
}
pnode initialize(int value) {
    pnode p = (pnode)malloc(sizeof(node));
    p->value = value;
    p->l = NULL;
    p->r = NULL;
    return p;
}
pnode add(pnode &p, int low, int high, int position, int v) {
    if (!p) p = initialize(0);
    if (low == high) {
        pnode current = initialize(p->value + v);
        return current;
    }
    int middle = (low + high) >> 1;
    pnode current = initialize(0);
    if (position <= middle) {
        current->l = add(p->l, low, middle, position, v);
        current->r = p->r;
    }
    else {
        current->l = p->l;
        current->r = add(p->r, middle + 1, high, position, v);
    }
    current->value = getValue(current->l) + getValue(current->r);
    return current;
}
int get(pnode &p, int low, int high, int l, int r) {
    if (!p) return 0;
    if (low > r || high < l) return 0;
    if (low >= l && high <= r) return p->value;
    int middle = (low + high) >> 1;
    return get(p->l, low, middle, l, r)
    + get(p->r, middle + 1, high, l, r);
}
int getKthElement(pnode &p, int low, int high, int K) {
    if (getValue(p) <= K) return high;
    if (low == high) {
        return low - 1;
    }
    int middle = (low + high) >> 1;
    if (getValue(p->l) > K) {
        return getKthElement(p->l, low, middle, K);
    }
    else {
        return getKthElement(p->r, middle + 1, high, K - getValue(p->l));
    }
}

int N;
int a[S];
int lastPosition[S];
int result[S];
pnode roots[S];

int main() {
    cin >> N;
    for (int i = 1; i <= N; i ++) cin >> a[i];
    
    for (int i = N; i > 0; i --) {
        roots[i] = add(roots[i + 1], 1, N, i, +1);
        if (lastPosition[a[i]] > 0) {
            roots[i] = add(roots[i], 1, N, lastPosition[a[i]], -1);
        }
        lastPosition[a[i]] = i;
    }
    for (int i = 1; i <= N; i ++) {
        for (int j = 1; j <= N; j = getKthElement(roots[j], 1, N, i) + 1) {
            result[i] ++;
        }
    }
    for (int i = 1; i <= N; i ++) {
        cout << result[i];
        if (i < N) cout << " ";
    }
    cout << endl;
    
    return 0;
}

