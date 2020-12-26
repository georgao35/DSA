#include <cstdio>

char read;
char BitMap[1<<21] = {'\0'};
char tree[1<<22] = {'\0'};
int toPush = 0;//将要放进树去的数

inline void set(char* BitMap, int k){
    BitMap[k >> 3] |= ((0x80) >> (k & 0x07));
}

inline bool get(char* BitMap, int k){
    return BitMap[k >> 3] & ((0x80) >> (k & 0x07));
}

inline void push(int topush, int length){
    int now = topush | (1<<length);
    set(tree, now);
    now >>= 1;
    while(!get(tree, now)){
        set(tree, now); now >>= 1;
    }
}

inline int getlen(int k){
    int len = 0;
    while(k){
        len++; k>>=1;
    }
    return len;
}

int main(){
    read = getchar();
    int cnt = 0;
    while(read != '\n'){
        if(read == '1') set(BitMap, cnt);
        read = getchar(); cnt++;
    }
    
    int i=0, j=0, length = cnt<24? cnt:24;
    for(;j<24 && j<cnt; j++){
        toPush <<= 1; 
        if(get(BitMap, j)) toPush |= 0x01;
    }
    push(toPush, length);

    while(i++<cnt){
        toPush &= (~(1<<length-1));
        if(j<cnt){
            toPush <<= 1; if(get(BitMap, j)) toPush |= 0x01;
        }else{
            length--;
        }
        push(toPush, length);
        j++;
    }

    int k=1;
    for(;k< 1<<25;k++){
        if(!get(tree, k)) break;
    }
    int len = getlen(k)-1;
    while(len--){
        if((k>>len) & 0x01) putchar('1');
        else putchar('0');
    }
    puts("");
    return 0;
}