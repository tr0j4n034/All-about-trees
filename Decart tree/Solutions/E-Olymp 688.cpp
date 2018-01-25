//
//  main.cpp
//  practice
//
//  Created by Mahmud on 01/24/18.
//  Copyright © 2017 Mahmud. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <climits>
#include <functional>

using namespace std;

const int MAX = 100005;

struct node {
    int value;
    int priority;
    int subtreeSize;
    bool reversed;
    node *leftChild;
    node *rightChild;
    node () {
        
    }
};
typedef node* tree;

int getValue(tree &t) {
    return t ? t->value : INT_MIN;
}
int getSize(tree &t) {
    return t ? t->subtreeSize : 0;
}
void updateSize(tree &t) {
    if (t) t->subtreeSize = getSize(t->leftChild) + 1 + getSize(t->rightChild);
}
void lazyReverse(tree &t) {
    if (t && t->reversed) {
        swap(t->leftChild, t->rightChild);
        if (t->leftChild) t->leftChild->reversed ^= true;
        if (t->rightChild) t->rightChild->reversed ^= true;
        t->reversed = false;
    }
}
tree Initialize(int value) {
    tree t = (tree)malloc(sizeof(node));
    t->value = value;
    t->priority = rand();
    t->subtreeSize = 1;
    t->reversed = false;
    t->leftChild = NULL;
    t->rightChild = NULL;
    return t;
}
void Split(tree t, tree &l, tree &r, int position, int skipped = 0) {
    lazyReverse(t);
    if (!t) {
        return void(l = r = NULL);
    }
    int currentPosition = skipped + 1 + getSize(t->leftChild);
    if (currentPosition <= position) {
        Split(t->rightChild, t->rightChild, r, position, currentPosition);
        l = t;
    } else {
        Split(t->leftChild, l, t->leftChild, position, skipped);
        r = t;
    }
    updateSize(t);
}
void Merge(tree &t, tree l, tree r) {
    lazyReverse(t);
    if (!l || !r) t = l ? l : r;
    else if (l->priority > r->priority) {
        Merge(l->rightChild, l->rightChild, r);
        t = l;
    } else {
        Merge(r->leftChild, l, r->leftChild);
        t = r;
    }
    updateSize(t);
}
void Insert(tree &t, tree &item, int position) {
    tree l, r;
    Split(t, l, r, position - 1);
    Merge(l, l, item);
    Merge(t, l, r);
}
void Insert(tree &t, int position, int key) {
    tree item = Initialize(key);
    Insert(t, item, position);
}
//void Print(tree t) {
//    if (!t) return;
//    Print(t->leftChild);
//    cout << t->value << " ";
//    Print(t->rightChild);
//}

template <class T>
void fastInput(T &N) {
    char ch;
    int sign = 1;
    N = 0;
    while ((ch = getchar_unlocked()) && ch == ' ') {};
    if (ch == '-') sign = -1;
    else if (isdigit(ch)) N = ch - '0';
    while ((ch = getchar_unlocked()) && isdigit(ch)) {
        N = (N << 1) + (N << 3) + ch - '0';
    }
    if (sign == -1) N = ~N + 1;
}

int N, Q;
int low, high;
tree t = NULL;

int printed = 0;
void Print(tree t) {
    if (!t) return;
    Print(t->leftChild);
    cout << t->value;
    printed ++;
    if (printed < N) cout << " ";
    Print(t->rightChild);
}

int main() {
    srand(unsigned(time(NULL)));
    
    function<void(tree&, int, int)> MovetoFront = [](tree &t, int low, int high) {
        tree l, r;
        Split(t, l, r, low - 1);
        tree l1, r1;
        Split(r, l1, r1, high - low + 1);
        Merge(l, l1, l);
        Merge(t, l, r1);
    };
    
    fastInput(N);
    fastInput(Q);
    for (int i = 1; i <= N; i ++) Insert(t, i, i);
    while (Q --) {
        fastInput(low);
        fastInput(high);
        MovetoFront(t, low, high);
    }
    Print(t); cout << endl;
    
    return 0;
}
