---
title: "JOISC 2021 Day 2"
description: "Escape Route"
date: 2023-03-12T00:00:00+08:00
draft: false
tags: ["JOISC", "OI"]
summary: "笨方塊耍笨寫 JOISC 被爆揍，燒雞"
---

<style type="text/css">
#TableOfContents > ul > li:nth-child(2) > ul
{
    display: none;
}
</style>

可能是因為我不會日文，但我還是覺得這題很酷所以想寫一下我怎麼做的。  

## 題敘
[Link](https://oj.uz/problem/view/JOI21_escape_route)

有一張 $N$ 點 $M$ 邊無向圖，每天的長度是 $S$，  
第 $i$ 條邊連接 $A_i,\\,B_i$，在那一天的時間點小於等於 $L_i$ 的時候可以行走，費時 $C_i$（也就是要在時間點 $L_i - C_i$ 當下或之前出發才有料），  
有 $Q$ 筆詢問，第 $j$ 筆想詢問從第 1 天的時間點 $T_j$ 開始，從 $U_i$ 走到 $V_i$ 需要多久。  
$2 \leq N \leq 90,\\,M \leq \frac{N(N-1)}{2},\\,2 \leq S \leq 10^{15},\\,1 \leq L_i \leq C_i < S,\\,1 \leq Q \leq 3 \times 10^6,\\,0 \leq T_j < S$  
圖是連通、沒有自環也沒有重邊的（不考慮 $L_i,\\,C_i$）。    

</br></br></br></br></br></br>

## 題解

讓我們來觀察一下，先把 $S$ 這個問題很大的人處理掉，如果我們先去考慮第一天可以走多遠，那第二天之後就只要對每個根跑一次 Dijkstra 就能做完，每次 Query 是 $\mathcal O(QN)$。  

### $\mathcal O(N^5)$

#### Observation
> 實際上，對一個點 $u$ 當根，考慮第一天以內的時間點 $t$ 開始，從 $u$ 往下走到所有節點 $v$ 的時間，  
> 紀錄 $d_t(u,\\,v)$ 是 $u,\\,v$ 兩點在時間點 $t$ 以內的距離，  
> 只會有 $\mathcal O(M) = \mathcal O(N^2)$ 種不一樣的 $d_t$。  

把時間點 $t$ 設成 $0$ 開始跑 Dijkstra 可以得到當下從 $u$ 出發走到所有節點 $v$ 的時間，考慮這個最短路樹，一定存在另一個 $t'$ 讓時間在 $t'$ 之後有一條邊不能走，  
在 $[t,\\, t')$ 的時間底下，現在的這棵最短路樹一定是最優的，所以我們只要在 $t'$ 之後重蓋一棵，  
這種切換的時間點最多只有 $M$ 個，因為每次邊都會少一條，  
（注意有可能有一個時間點突然拔掉很多條）  
所以直接蓋出每個根 $\mathcal O(N) \times \mathcal O(N^2)$ 個時間點 $\times$ 每次 Dijkstra $\mathcal O(N^2)$，  

### $\mathcal O(N^4)$  

要怎麼刪邊？  
刪邊似乎超難，那考慮倒流的問題：加邊？  
好像還是很難，那我們來看看我們平常是怎麼加邊的，  

首先第一個性質是，加邊的答案只會更好，所以原本適用的邊不會再被拔掉。  

考慮我們已經有全點對最短路 $d(u,\\,v)$，那要加入一條邊 $(x,\\,y)$ 權重是 $w$，我們會需要做這件事：  
枚舉 $u,\\,v$，然後更新 $d(u,\\,v) = \min(d(u,\\,v), d(u,\\,x) + w + d(y,\\,v), d(u,\\,y) + w + d(x,\\,v))$，  
為了方便把無向圖轉換成有向，式子簡化成只要計算一邊 $d(u,\\,v) = \min(d(u,\\,v), d(u,\\,x) + w + d(y,\\,v))$，  
可以觀察更新的順序不影響結果，因為最短路勢必是簡單路徑（這裡假設邊權為正，事實上要是非負，那也會存在一條是簡單路）。  

用這個想法，讓時光倒流，計算新的 $t$ 的時候，會加入至少一條邊，  
加入一條邊 $(x,\\,y)$ 的時候，可以寫成 $d_t(u,\\,v) = \min(d_t(u,\\,v), d_t(u,\\,x) + w + d_{t+d_t(u,\\,v), d_t(u,\\,x)}(y,\\,v))$，  
考慮起點是固定的，那從起點走到 $y$ 的（也就是前兩項）是固定的，而且這個時間點是在我們現在要算的 $t$ 之後，讓 $t+d_t(u,\\,v), d_t(u,\\,x)$ 是 $t'$，   
那作法就很明顯了，我們把這些更新通通丟進 priority_queue 裡面，每次拿時間最大的更新去做，  
如果現在時間點最大的更新發生在 $t'$，我們想說明當下不可能有其他更新會讓 $y$ 往下走的時間更好。  
假設確實存在另一個更新發生在加入圖中會產生另一個更新發生在比 $t'$ 更大的時間點，這兩個更新一定都是發生在以 $y$ 為根的圖上，  
那實際上這個更新至少要到 $T$ 才會發揮作用，因為沒有加入這條邊就不可能會影響後面的所有更新，  
因此，我們可以知道當把時間最大的更新拿去做的時候，我們想知道時間點在 $t'$ 以後的所有點的答案其實都已經固定下來了，  
所以我們只需要一邊蓋一邊詢問，每次更新從 Dijkstra $\mathcal O(N^2)$ 變為 $\mathcal O(N)$，  
總共更新的數量也維持不變是 $\mathcal O(N^3)$，在 pq 裡面只會多一個 $\log$，  
總時間複雜度來到 $\mathcal O(N^4)$，加上前面的查詢 $\mathcal O(QN)$ 足以通過。  

其實這題明明想法不難但為啥截至現在只有 11 個人寫 <emoji>🤔</emoji>

<details>
    <summary> Code </summary>

```cpp
#include "escape_route.h"
#include <bits/stdc++.h>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define F first
#define S second
#define ll long long
using namespace std;

const ll inf = 100'000'000'000'000'000;
ll d1[90][90 * 90 + 5][90], d2[90][90], from[90];
vector<ll> tp[90];
vector<pll> last[90][90];

int getT(int i, ll t)
{
    return upper_bound(tp[i].begin(), tp[i].end(), t, greater<>()) - tp[i].begin() - 1;
}

void update(int N, int r, int t, int u, int v, ll w)
{
    int vt = getT(v, d1[r][t][u] + w);
    if (vt < 0)
        return;
    for (int i = 0; i < N; i++)
        d1[r][t][i] = min(d1[r][t][u] + w + d1[v][vt][i] - tp[v][vt], d1[r][t][i]);
}

pll calcNextEdge(int N, int r, ll T, int t)
{
    ll nt = -1, ni = -1, nj = -1;
    for (int i = 0; i < N; i++)
        if (!last[r][i].empty())
            if (nt < T - (d1[r][t][i] - last[r][i].back().F))
                nt = T - (d1[r][t][i] - last[r][i].back().F), ni = i;

    if (ni >= 0)
    {
        nj = last[r][ni].back().S;
        last[r][ni].pop_back();
    }
    return pll(nj, nt);
}

vector<ll> calculate_necessary_time(
    int N, int M, ll S, int Q,
    vector<int> A, vector<int> B, vector<ll> L, vector<ll> C, vector<int> U, vector<int> V, vector<ll> T)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            last[i][A[j]].emplace_back(pll(C[j] - L[j], j));
            last[i][B[j]].emplace_back(pll(C[j] - L[j], j));
        }
        for (int j = 0; j < N; j++)
            sort(last[i][j].begin(), last[i][j].end());
    }

    priority_queue<tuple<ll, int, int>> pq;
    for (int i = 0; i < N; i++)
    {
        tp[i].emplace_back(S - 1);
        for (int j = 0; j < N; j++)
            d1[i][0][j] = (i == j ? S - 1 : inf << 1);
        auto [j, nt] = calcNextEdge(N, i, tp[i].back(), (int)tp[i].size() - 1);
        if (nt >= 0)
            pq.push(make_tuple(nt, i, j));
    }

    while (!pq.empty())
    {
        auto [t, i, j] = pq.top();
        pq.pop();
        if (t < tp[i].back())
        {
            tp[i].emplace_back(t);
            int tt = (int)tp[i].size() - 1;
            for (int k = 0; k < N; k++)
                d1[i][tt][k] = d1[i][tt - 1][k] - (tp[i][tt - 1] - tp[i][tt]);
        }
        update(N, i, (int)tp[i].size() - 1, A[j], B[j], L[j]);
        update(N, i, (int)tp[i].size() - 1, B[j], A[j], L[j]);
        auto [k, nt] = calcNextEdge(N, i, tp[i].back(), (int)tp[i].size() - 1);
        if (nt >= 0)
            pq.push(make_tuple(nt, i, k));
    }
    
    vector<pair<int, pll>> E[90];
    for (int i = 0; i < M; i++)
    {
        E[A[i]].emplace_back(make_pair(B[i], pll(C[i], L[i])));
        E[B[i]].emplace_back(make_pair(A[i], pll(C[i], L[i])));
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            d2[i][j] = (i == j ? 0 : inf);
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push(pll(0, i));
        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > d2[i][u])
                continue;
            for (auto [v, p] : E[u])
            {
                auto [c, l] = p;
                ll nd = (d % S <= c - l ? d : (d + S - 1) / S * S) + l;
                if (nd < d2[i][v])
                {
                    d2[i][v] = nd;
                    pq.push(pll(d2[i][v], v));
                }
            }
        }
    }

    vector<ll> ans(Q);
    for (int i = 0; i < Q; i++)
    {
        int t = upper_bound(tp[U[i]].begin(), tp[U[i]].end(), T[i], greater<>()) - tp[U[i]].begin() - 1;
        ans[i] = inf;
        for (int j = 0; j < N; j++)
            if (d1[U[i]][t][j] < inf)
            {
                if (j == V[i])
                    ans[i] = min(ans[i], d1[U[i]][t][j] - tp[U[i]][t]);
                else
                    ans[i] = min(ans[i], S + d2[j][V[i]] - T[i]);
            }
    }
    return ans;
}
```
</details>