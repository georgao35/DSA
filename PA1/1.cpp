#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
using namespace std;

char a[5005];
char b[5005];
unsigned long long IntA[1000];
unsigned long long IntB[1000];
unsigned long long result[2000];

void getInt(){
    int j = strlen(a)-1;
    int i = 0;
    while (j>=0){
        int base = 1;
        for(int k=0; k<8 && j>=0 ; k++){
            IntA[i] += base*(a[j]-'0');
            j--;
            base *= 10;
        }
        i++;
    }
    j = strlen(b)-1;
    i = 0;
    while (j>=0){
        int base = 1;
        for(int k=0; k<8 && j>=0 ; k++){
            IntB[i] += base*(b[j]-'0');
            j--;
            base *= 10;
        }
        i++;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    while(n-->0){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(IntA,0,sizeof(IntA));
        memset(IntB,0,sizeof(IntB));
        memset(result,0,sizeof(result));
        scanf("%s%s",a,b);
        getInt();
        int alen = strlen(a)/8 + ( strlen(a)%8? 1:0 );
        int blen = strlen(b)/8 + ( strlen(b)%8? 1:0 );

        for(int i=0;i<alen+blen;++i){
            for(int j=0;j<=i;j++){
                int k = i-j;
                if(j < alen and k < blen){
                    result[i] += IntA[j] * IntB[k];
                }
            }
            if(i){
                result[i] += result[i-1]/100000000;
                result[i-1] %= 100000000;
            }
        }
        int end = alen+blen-1;
        while(result[end] == 0){
            end --;
        }
        cout<<result[end--];
        while (end >= 0 ){
            cout<<setfill('0')<<setw(8)<<result[end--];
        }
        cout<<endl;
    }
    return 0;
}