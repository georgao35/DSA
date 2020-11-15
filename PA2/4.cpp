#include <cstdio>
#include <cctype>
typedef long long ll;

int n, m;
const int maxn = 200005;
ll tree[2*maxn];

inline int lc(int a){
    return 2*a;
}
inline int rc(int a){
    return 2*a + 1;//从1开始计数
}
inline int par(int a){
    return (a-1)/2;
}
inline unsigned int read(){
    unsigned int s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c)){ 
        w |= c == '-'; c = getchar();
    }
    while (isdigit(c)){
        s = s * 10 + c - '0'; c = getchar();
    }
    return s * w;
}

int main(){
    scanf("%d%d",&n ,&m);
    char operand;
    while(m--){
        operand = getchar(); getchar();
        int i = read(), j = read();
        if(operand == 'H'){
            
        }else{
            puts("1");
        }
    }
    return 0;
}