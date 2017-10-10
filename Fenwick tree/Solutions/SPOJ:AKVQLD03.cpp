#include <bits/stdc++.h>

using namespace std;

const int me = 1000025;

int n, q, l, r, x;
char type[3];
int ft[me];

void add(int pos, int value){
    for( ; pos < me; pos += (pos & -pos))
        ft[pos] += value;
}
int get(int pos){
    int s = 0;
    for( ; pos > 0; pos -= (pos & -pos))
        s += ft[pos];
    return s;
}

int main(){
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    scanf("%d%d", &n, &q);
    while(q --){
        scanf(" %s", &type);
        if(type[0] == 'a'){
            scanf("%d%d", &l, &x);
            add(l, x);
        }
        else{
            scanf("%d%d", &l, &r);
            printf("%d\n", get(r) - get(l - 1));
        }
    }
    
    return 0;
}
