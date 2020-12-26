#include <cstdio>
#include <cstring>
typedef long long ll;

const int maxn = 25;
char str[maxn]; int len;
int nxt[maxn], times[maxn];

void buildNxt(){
    int j = 0;
    int t = nxt[0] = -1;
    while(j < len){
        if ( 0 > t || str[j] == str[t] ) { 
          j ++; t ++;
          nxt[j] = t; 
       } else 
          t = nxt[t];
    }
}

long long solve(){
    times[0] = 0;
    for(int i=1;i<=len;i++){
        times[i] = times[nxt[i]]+1;
    }
    ll ans = len;
    for(int i=len;i>=0;i--){
        ans += times[nxt[i]];
    }
    return ans;
}

int main(){
    scanf("%s", str);
    len = strlen(str);
    buildNxt();
    printf("%lld", solve());
    return 0;
}