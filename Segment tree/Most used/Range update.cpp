//
//  main.cpp
//  practice
//
//  Created by Mahmud on 10/9/17.
//  Copyright © 2017 Mahmud. All rights reserved.
//


/*
 Min/Max segment tree
 build: O(N)
 query: O(log(N))
 */


#include <iostream>

using namespace std;

const int MAX_SIZE = 1 << 20;
const int INFINITY = INT_MAX;

int N;
int queryCount;
int data[MAX_SIZE];
int lazy[MAX_SIZE << 2];
int stree[MAX_SIZE << 2];


void merge(int I) {// change operator according to your demands
    stree[I] = min(stree[I << 1], stree[I << 1 | 1]);
}
void push(int I, int low, int high) {
    if (lazy[I]) {
        // change the following line according to your demands
        stree[I] = lazy[I];
        if (low != high) {
            lazy[I << 1] = lazy[I];
            lazy[I << 1 | 1] = lazy[I];
        }
        lazy[I] = 0;
    }
}
void buildTree(int I, int low, int high) {
    if (low == high) {
        stree[I] = data[low];
        return;
    }
    int middle = (low + high) >> 1;
    buildTree(I << 1, low, middle);
    buildTree(I << 1 | 1, middle + 1, high);
    merge(I);
}
void rangeUpdate(int I, int low, int high, int leftBorder, int rightBorder, int newValue) {
    push(I, low, high);
    if (low > rightBorder || high < leftBorder) {
        return;
    }
    if (low >= leftBorder && high <= rightBorder) {
        lazy[I] = newValue;
        push(I, low, high);
        return;
    }
    int middle = (low + high) >> 1;
    rangeUpdate(I << 1, low, middle, leftBorder, rightBorder, newValue);
    rangeUpdate(I << 1 | 1, middle + 1, high, leftBorder, rightBorder, newValue);
    merge(I);
}
int query(int I, int low, int high, int l, int r) {
    push(I, low, high);
    if (low > r || high < l) {
        return INFINITY;
    }
    if (low >= l && high <= r) {
        return stree[I];
    }
    int middle = (low + high) >> 1;
    return min(query(I << 1, low, middle, l, r),
               query(I << 1 | 1, middle + 1, high, l, r));
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i ++) {
        cin >> data[i];
    }
    buildTree(1, 1, N);
    
    cin >> queryCount;
    while (queryCount --) {
        int type;
        cin >> type;
        
        if (type == 1) { // update query
            int leftBorder, rightBorder;
            int newValue;
            cin >> leftBorder >> rightBorder >> newValue;
            rangeUpdate(1, 1, N, leftBorder, rightBorder, newValue);
        }
        else { // ask query
            int leftBorder, rightBorder;
            cin >> leftBorder >> rightBorder;
            int result = query(1, 1, N, leftBorder, rightBorder);
            cout << result << endl;
        }
    }
    
    return 0;
}
