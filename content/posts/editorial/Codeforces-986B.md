---
title: "[Codeforces] 986B"
description: "Petr and Permutations"
date: 2021-03-30T15:05:49+08:00
draft: false
tags: ["codeforces","tutorial"]
summary: "笨方塊想學寫程式被爆揍，燒雞"
---

卡好久...終於AC了><

## 題敘
有一個$1$ ~ $n$的排列($10 ^ 3 \leq n \leq 10 ^ 6$)，  
問你它是隨機交換$3n$還是$7n + 1$次的陣列。

## 想法

### 排列
排列最重要的性質有一個：  
就是把index跟value組成圖會有好多個環(或只有一個)，  
每次操作會增加一個環或減少一個環，而初始有$n$個(自環)  
所以環的數量的奇偶就可以解決這個問題，  
$n$個環操作$3n$次一定是偶數，    
操作$7n + 1$次一定是奇數。

### 逆序數對
燒雞，我一直吃WA  
qwq

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

int n, m, arr[1000005], bit[1000005];
signed main()
{

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 1; i <= n; i++)
    {
        if (arr[i] == 0)
            continue;
        m ^= 1;
        int k = i;
        while(k)
        {
            int t = k;
            k = arr[k];
            arr[t] = 0;
        }
    }
    if (m)
        cout << "Um_nik";
    else
        cout << "Petr";
}
```