#include <iostream>
#include <cstdio>
using namespace std;

bool toLeft(int x, int y, int i);
void sort(int begin, int end, int*);

int n,m;
const int maxN = 200005;
int x[maxN], y[maxN];

int main(){
    scanf("%d",&n);
    x[0] = 0;
    y[0] = 0;
    for(int i=1;i<=n;++i){
        scanf("%d",&x[i]);
    }
    for(int i=1;i<=n;++i){
        scanf("%d",&y[i]);
    }
    sort(0,n,x);
    sort(0,n,y);
    scanf("%d",&m);
    while(m-->0){
        int pX,pY;
        scanf("%d%d",&pX,&pY);
        int left = 0;
        int right = n+1;
        while(right - left > 1){
            int mid = (right + left)/2;
            if(toLeft(pX, pY, mid)){
                right = mid;
            }else{
                left = mid;
            }
        }
        printf("%d\n",left);
    }
    return 0;
}

bool toLeft(int px, int py, int i){
    int x1 = x[i], y1 = y[i];
    return (x1-px)*y1 - x1*py > 0;
}

void sort(int begin, int end, int* data){
    if(begin < end){
        int i = begin, j = end;
        int tmp = data[i];
        while (i<j)
        {
            while (i<j && data[j]>tmp)
                j--;
            if(i<j)
                data[i++] = data[j];
            while(i<j && data[i]<tmp)
                i++;
            if(i<j)
                data[j--] = data[i];
        }
        data[i] = tmp;
        sort(begin, i-1, data);
        sort(i+1, end, data);
    }
}