//
//  main.cpp
//  practice
//
//  Created by Mahmud on 01/31/18.
//  Copyright © 2017 Mahmud. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <climits>
#include <functional>
#include <cassert>

using namespace std;

const int MODULO = 1000000000;

struct node {
    int value;
    int priority;
    long long subtreeSum;
    node *leftChild;
    node *rightChild;
    node () {
        
    }
};
typedef node* tree;

int getValue(tree &t) {
    return t ? t->value : INT_MIN;
}
long long getSubtreeSum(tree &t) {
    return t ? t->subtreeSum : 0;
}
void update(tree t) {
    if (t) {
        t->subtreeSum = getSubtreeSum(t->leftChild) + t->value + getSubtreeSum(t->rightChild);
    }
}
tree Initialize(int value) {
    tree t = (tree)malloc(sizeof(node));
    t->value = value;
    t->priority = rand();
    t->subtreeSum = value;
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
    update(t);
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
    update(t);
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
    update(t);
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

long long getSum(tree t, int key) { // sum of elements <= key
    if (!t) return 0;
    long long sum = 0;
    if (t->value <= key) sum += getSubtreeSum(t->leftChild) + t->value;
    else sum += getSum(t->leftChild, key);
    if (t->value < key) sum += getSum(t->rightChild, key);
    return sum;
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
int queries, value, low, high;
int last = INT_MIN;
char type;

int main() {
    srand(unsigned(time(NULL)));
    
    fastInput(queries);
    while (queries --) {
        type = getchar_unlocked();
        if (type == '+') {
            fastInput(value);
            if (last != INT_MIN) value = (value + last) % MODULO;
            Insert(t, value);
            last = INT_MIN;
        }
        else {
            fastInput(low);
            fastInput(high);
            long long result = getSum(t, high) - getSum(t, low - 1);
            //cerr << "sum to high: " << getSum(t, high) << endl;
            //cerr << "sum to low - 1: " << getSum(t, low - 1) << endl;
            last = result % MODULO;
            printf("%lld\n", result);
        }
    }
    
    return 0;
}

