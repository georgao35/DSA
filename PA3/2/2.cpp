#include <cstdio>
#include <cstring>
#include <utility>
#include <cctype>
#include "crc32.h"
#define mod 10000103
typedef long long ll;
using namespace std;

int n;
unsigned char salt[5]; unsigned int lenSalt;
char map[19] = {'\0','0','1','2','3','4','5','6','7','8','9','t','s','i','n','g','h','u','a'};
int table[mod+3] = {0};
struct node{
    ll str; unsigned int hashResult; int next;
}allNodes[5000728];
int totalNodes=0;//str为字符串的值；nxt为下一个字符串的位置，从1开始
const int maxn = 1000005;
char Ai[maxn] = {'\0'};//每次成功的首字母

inline unsigned int gethash(const unsigned char* a, int len){
    return crc32(crc32(0, a, len), salt, lenSalt);
}

inline int hash2(unsigned int a){ return a % mod; }

char print(ll str){//根据字符串对应的数值输出字符串
    char tmp[9] = {'\0'}; int res[8];
    int len = 0;//获取值对应的字符串
    while(str){
        res[len] = str%19; len++; str/=19;
    }
    for(int j=0;j<len;j++) tmp[len-1-j] = map[res[j]];
    tmp[len] = '\0';
    puts(tmp);
    return tmp[0];
}

void insert(int hash, ll tar, unsigned hashResult){
    if(table[hash] == 0){
        allNodes[++totalNodes] = node{tar, hashResult, 0};
        table[hash] = totalNodes;
    }else{
        int cur = table[hash];
        while(allNodes[cur].next){
            if(allNodes[cur].str == tar) return;
            cur = allNodes[cur].next;
        }
        if(allNodes[cur].str == tar) return;
        allNodes[++totalNodes] = node{tar, hashResult, 0};
        allNodes[cur].next = totalNodes;
    }
}

void init(){
    int total = 19*19*19*19*19;
    char tmp[6]={'\0'}; int res[6]={0};
    for(int i=1;i<total;i++){
        int len = 0, cur = i;//获取值对应的字符串
        bool valid = true;//是否是有效的
        while(cur){
            if(cur%19 == 0){
                valid = false;
                break;
            }
            res[len] = cur%19;
            len++; cur/=19;
        }
        if(!valid) continue;
        for(int j=0;j<len;j++) tmp[len-1-j] = map[res[j]];
        tmp[len] = '\0';
        unsigned tmpHash = gethash((unsigned char*)tmp, len);
        insert(hash2(tmpHash), i, tmpHash);
    }
}

int rmap(char c){//查找字符对应的数字
    if(isdigit(c)) return c-'0'+1;
    else{
        switch (c)
        {
        case 't':
            return 11;
        case 's':
            return 12;
        case 'i':
            return 13;
        case 'n':
            return 14;
        case 'g':
            return 15;
        case 'h':
            return 16;
        case 'u':
            return 17;
        case 'a':
            return 18;
        default:
            return 19;
        }
    }
}

ll getId(char* tmp, int len){//返回字符串对应的数值id
    ll base = 1; ll ans = 0;
    while(len--){
        ans += base*rmap(tmp[len]);
        base*=19;
    }
    return ans;
}

void push(int now){
    unsigned char tmp[9] = {'\0'};
    if(now >= 5){
        for(int i=0;i<6;i++)
            tmp[5-i] = Ai[now-i];
        unsigned tmpHash = gethash(tmp, 6);
        insert(hash2(tmpHash), getId((char*)tmp, 6), tmpHash);
    }
    if(now >= 6){
        for(int i=0;i<7;i++)
            tmp[6-i] = Ai[now-i];
        unsigned tmpHash = gethash(tmp, 7);
        insert(hash2(tmpHash), getId((char*)tmp, 7), tmpHash);
    }
    if(now >= 7){
        for(int i=0;i<8;i++)
            tmp[7-i] = Ai[now-i];
        unsigned tmpHash = gethash(tmp, 8);
        insert(hash2(tmpHash), getId((char*)tmp, 8), tmpHash);
    }
}

int main(){
    scanf("%d", &n);
    scanf("%s", salt);
    lenSalt = strlen((char*) salt);
    init();
    unsigned int tmp;
    
    int now = 0;
    for(int i=0;i<n;i++){
        scanf("%x", &tmp);
        int cur = hash2(tmp);
        if(table[cur]==0) puts("No");
        else{
            cur = table[cur];
            int cnt = 0; ll result=-1;
            while(cur){
                if(allNodes[cur].hashResult == tmp){
                    cnt++; result = allNodes[cur].str;
                    if(cnt>1) break;
                }
                cur = allNodes[cur].next;
            }
            if(cnt > 1) puts("Duplicate");
            else if(cnt == 1){
                Ai[now] = print(result);//打印并返回匹配上的字符串的第一个字符
                push(now);
                now++;
            }
            else puts("No");
        }
    }
    return 0;
}
