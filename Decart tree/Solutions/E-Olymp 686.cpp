//
//  main.cpp
//  practice
//
//  Created by Mahmud on 01/24/18.
//  Copyright © 2017 Mahmud. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <ctime>
#include <climits>
#include <functional>

using namespace std;

const int MODULO = 1000000000;

struct node {
    int value;
    int priority;
    node *leftChild;
    node *rightChild;
    node () {
        
    }
};
typedef node* tree;

int getValue(tree &t) {
    return t ? t->value : INT_MIN;
}
tree Initialize(int value) {
    tree t = (tree)malloc(sizeof(node));
    t->value = value;
    t->priority = rand();
    t->leftChild = NULL;
    t->rightChild = NULL;
    return t;
}
void Split(tree t, tree &l, tree &r, int key) {
    if (!t) {
        l = r = NULL;
    } else if (t->value <= key) {
        Split(t->rightChild, t->rightChild, r, key);
        l = t;
    } else {
        Split(t->leftChild, l, t->leftChild, key);
        r = t;
    }
}
void Merge(tree &t, tree l, tree r) {
    if (!l || !r) t = l ? l : r;
    else if(l->priority > r->priority) {
        Merge(l->rightChild, l->rightChild, r);
        t = l;
    }
    else {
        Merge(r->leftChild, l, r->leftChild);
        t = r;
    }
}
void Insert(tree &t, tree &item) {
    if (!t) {
        t = item;
    } else if (item->priority > t->priority) {
        Split(t, item->leftChild, item->rightChild, item->value);
        t = item;
    } else if (item->value < t->value){
        Insert(t->leftChild, item);
    } else {
        Insert(t->rightChild, item);
    }
}
bool Find(tree t, int key) {
    if (!t) return false;
    if (t->value == key) {
        return true;
    } else if(t->value > key) {
        return Find(t->leftChild, key);
    } else {
        return Find(t->rightChild, key);
    }
}
void Insert(tree &t, int value) {
    if (Find(t, value)) return;
    tree item = Initialize(value);
    Insert(t, item);
}
int getMinimum(tree t, int best = INT_MIN) {
    if (!t) return best;
    if (best == INT_MIN || t->value < best) best = t->value;
    return getMinimum(t->leftChild, best);
}
void Print(tree t) {
    if (!t) return;
    Print(t->leftChild);
    cout << t->value << " ";
    Print(t->rightChild);
}

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

tree t = NULL;
int queries, value;
int last = INT_MIN;
char type;

int main() {
    srand(unsigned(time(NULL)));
    
    function<int(tree&, int)> lowerBound = [](tree &t, int key) {
        if (Find(t, key)) return key;
        tree l, r;
        Split(t, l, r, key);
        int result = getMinimum(r);
        Merge(t, l, r);
        if (result < key) result = -1;
        return result;
    };
    
    fastInput(queries);
    while (queries --) {
        type = getchar_unlocked();
        fastInput(value);
        if (type == '+') {
            if (last != INT_MIN) value = (value + last) % MODULO;
            Insert(t, value);
            last = INT_MIN;
        }
        else {
            last = lowerBound(t, value);
            printf("%d\n", last);
        }
    }
    
    return 0;
}
