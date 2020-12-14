#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

set<int> tree;

int main(){
    int n;
    scanf("%d", &n); getchar();
    while(n--){
        char operand = getchar(); getchar(); 
        int para; scanf("%d",&para); getchar();
        if(operand == 'A') tree.insert(para);
        else if(operand == 'B') tree.erase(para);
        else{
            int a = *max_element(tree.begin(),lower_bound(tree.begin(),tree.end(),para));
            if(a > para) a = -1;
            printf("%d\n",a);
        }
    }

    return 0;
}