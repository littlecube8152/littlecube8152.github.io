---
title: "[Codeforces] 86D"
description: "Powerful array"
date: 2021-03-31T12:30:20+08:00
draft: false
tags: ["codeforces","tutorial"]
summary: "笨方塊想學寫程式被爆揍，燒雞"
---

又達成成就了>w<

## 題敘
有一個陣列，  
令在區間$[l..r]$裡$a_i$出現了$k_i$次，  
問$\sum k_i^2a_i$，多筆詢問。

## 想法
用線段樹超難合併，  
但我們發現把區間左或右界加減$1$只要$\mathcal{O}(1)$的時間，  
所以考慮莫隊算法，  
如果把$a_i$移出陣列只要扣$(2k_i - 1)a_i$，  
移入只要加上$(2 k_i + 1)a_i$，  
如果把左界$K$個一塊，計算只要$\mathcal{O}(\frac{\displaystyle N}{\displaystyle K}N +NK)$，  
就是每塊的右界都要從頭到尾，左界每次最多移動$K$，
取$K = \sqrt{N}$，複雜度是$\mathcal{O}(N \sqrt{N})$，  
離線排序詢問，就可以AC了。  

## AC Code
```cpp
/*  | |       _    _  | |        _____       | |
//  | |   _  | |  | | | | _____ /  ___|__  __| |___  _____
//  | |  |_|[   ][   ]| |/  _  \| |    | | | |  _  \/  _  \  
//  | L__| | | |_ | |_| || ____|| |___ | |_| | |_| || ____|
//  L____|_| |___||___|_|\_____|\_____|\_____/\____/\_____|
//  Segment Tree is hard.
*/  
#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#pragma pack(0)
#define int long long
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define F first
#define S second
#define pb(x) emplace_back(x)
#define MOD 1000000007
#define MOD2 998244353
#define _INFINITY 9223372036854775807
#define fast ios::sync_with_stdio(0), cin.tie(0)
using namespace std;

struct query
{
    int l, r, i;
};
vector<query> v[10005];

ll n, t, arr[300005], ans[300005];

signed main()
{
    fast;
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 1; i <= t; i++)
    {
        int l, r;
        cin >> l >> r;
        v[(int)(l / sqrt(n))].pb((query{l, r, i}));
    }
    for (int i = 0; i <= ceil(sqrt(n)); i++)
        sort(v[i].begin(), v[i].end(), [](query q1, query q2) { return q1.r < q2.r; });
    for (int i = 0; i <= ceil(sqrt(n)); i++)
    {
        int l = i * sqrt(n), r = l, sum = arr[l], tmp[1000005] = {0};
        tmp[arr[l]] = 1;

        for (query q : v[i])
        {
            for (; r + 1 <= q.r;)
            {
                r++;
                sum += (tmp[arr[r]] * 2 + 1) * arr[r];
                tmp[arr[r]]++;
            }
            if (q.l < l)
            {
                for (; q.l <= l - 1;)
                {
                    l--;
                    sum += (tmp[arr[l]] * 2 + 1) * arr[l];
                    tmp[arr[l]]++;
                }
            }
            else
            {
                for (; l < q.l; l++)
                {
                    sum -= (tmp[arr[l]] * 2 - 1) * arr[l];
                    tmp[arr[l]]--;
                }
            }
            ans[q.i] = sum;
        }
    }
    for (int i = 1; i <= t;i++)
        cout << ans[i] << '\n';
}
```

