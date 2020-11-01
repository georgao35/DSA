#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char a1[5000], b1[5000];
long long a[625], b[625], ans[1255]; //a,b存储按8位拆分的数字数组。ans记录乘法结果
int lena, lenb, lenans;

int main()
{
    int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        memset(ans, 0, sizeof(ans));
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));

        scanf("%s%s", a1, b1);

        lena = strlen(a1);
        lenb = strlen(b1);
        int m1 = lena / 8;
        int m2 = lena % 8;
        //每次按8个数位为单位进行乘法操作
        for (int i = 0; i < m1; ++i)
        {
            for (int j = 8; j >= 1; --j)
                a[i] = a[i] * 10 + a1[lena - i * 8 - j] - '0';
        }

        if (m2 > 0)
        {
            for (int i = 0; i < m2; i++)
                a[m1] = a[m1] * 10 + a1[i] - '0';
            m1++;
        }

        int n1 = lenb / 8;
        int n2 = lenb % 8;
        for (int i = 0; i < n1; ++i)
        {
            for (int j = 8; j >= 1; --j)
                b[i] = b[i] * 10 + b1[lenb - i * 8 - j] - '0';
        }
        if (n2 > 0)
        {
            for (int i = 0; i < n2; i++)
                b[n1] = b[n1] * 10 + b1[i] - '0';
            n1++;
        }

        for (int i = 0; i < m1; i++)
            for (int j = 0; j < n1; ++j)

                ans[i + j] += a[i] * b[j];

        for (int i = 0; i < m1 + n1; i++)
        {
            ans[i + 1] += ans[i] / 100000000;
            ans[i] %= 100000000;
        }

        lenans = m1 + n1;
        while (ans[lenans] == 0 && lenans > 0)
            lenans--;

        printf("%d", ans[lenans]);
        for (int i = lenans - 1; i >= 0; --i)
        {
            printf("%08d", ans[i]);
        }
        cout << endl;
    }
    return 0;
}