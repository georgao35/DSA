#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n,m,k;
const int maxL = 50105;
char a[maxL], b[maxL];

int d[2][maxL];

int min(int a, int b){
    return (a<b)? a:b;
}

int max(int a, int b){
    return (a>b)? a:b;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    cin >> a >> b;
    int ans = -1;
    for(int i=0;i<m;++i){
        d[0][i] = 0;
        d[1][i] = 0;
    }
    for(int i=0;i<n;++i){
        for(int j=max(0,i-k);j<min(i+k,m);++j){
            if(a[i] == b[j])
                d[(i+1)%2][j+1] = d[i%2][j] + 1;
            else
                d[(i+1)%2][j+1] = max(d[i%2][j+1] ,  d[(i+1)%2][j]);
        }
    }
    ans = m+n-2*d[n%2][m];
   // if(ans > k)
        //ans = -1;
    printf("%d\n",ans);
    return 0;
}