#include <cstdio>
#include <cctype>
typedef long long ll;
#ifdef _OJ_
#define maxm 200005
#else
#define maxm 20
#endif

int n,m;
ll tag[maxm];

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
inline int lc(int l){
    return l<<1;
}
inline int rc(int l){
    return l<<1 | 1;
}
void build(){

}

int main(){
    scanf("%d%d",&n ,&m); getchar();
    char operand;
    while(m--){
        operand = getchar(); getchar();
        int i = read(), j = read();
        if(operand == 'H'){

        }else{

        }
    }
    return 0;
}