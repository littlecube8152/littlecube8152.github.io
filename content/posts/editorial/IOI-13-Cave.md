---
title: "[IOI] '13 Cave"
date: 2021-03-30T23:21:27+08:00
draft: false
tags: ["IOI", "OI", "tutorial"]
summary: "笨方塊想寫 IOI 題被爆揍，燒雞"
---

成就達成 第一題 IOI  

## 題敘
[Link - oj.uz](https://oj.uz/problem/view/IOI13_cave)
[Link - TIOJ](https://tioj.ck.tp.edu.tw/problems/1839)  

**這題是一題互動題。**  
有$N$個開關($N \leq 5 \times 10^3$)，對應到$N$個不透明的門，  
你可以試$70000$次開關的組合，得到最前面有多少門是開著的，  
問開關對應到的組合跟開關的正確位置(上或下)。  

## 想法

$5000 \log_2 5000 < 70000$  
然後開關又剛好只有上跟下，所以可以套二分搜，  
整體不難，但細節有點多，  
主要想法就是先看這個門是**上會開還是下會開**，  
然後把不確定的所有開關分兩半(這裡用位置分也是好的，而且比較容易debug)，  
兩份一個填0，一個填1，再根據之前得到的結果判斷解在哪一側，    
注意即使不在二分搜範圍也要給初始值，解出來的也要填，  
然後Interactor oj.uz上有，可以幫助debug，  

另外值得注意的是他的互動函式是傳入陣列，  
所以用變數為長度的陣列可以這樣設：
```cpp
int *array = new int[n];
```
不過實際上**不需要**，因為`a[b]`事實上等價於`*(a + b)`，  
而陣列的傳入是傳入陣列頭的指標，  
所以其實多開長度不會有問題，可以直接傳  
(常數會小很多，因為指標本身就要多開記憶體再刪掉)  

還有使用Interactor的時候本機可以用cerr來debug  
上傳要註解掉，不然有機會TLE。  

## AC Code
這份是可以AC oj.uz上的：  
```cpp
/*  | |       _    _  | |        _____       | |
//  | |   _  | |  | | | | _____ /  ___|__  __| |___  _____
//  | |  |_|[   ][   ]| |/  _  \| |    | | | |  _  \/  _  \  
//  | L__| | | |_ | |_| || ____|| |___ | |_| | |_| || ____|
//  L____|_| |___||___|_|\_____|\_____|\_____/\____/\_____|
//  Segment Tree is hard.
*/
//#pragma GCC optimize("O3,unroll-loops")
#include "cave.h"

int n, comb[5005], match[5005], attempt[5005], S[5005], D[5005];

int bs(int l, int r, int i, int state)
{
    if (l == r)
        return l;
    int mid = (l + r) / 2;
    for (int j = 0; j < l; j++)
        if (comb[j] != -1)
            attempt[j] = comb[j];
    for (int j = l; j <= mid; j++)
        if (comb[j] == -1)
            attempt[j] = state;
        else
            attempt[j] = comb[j];
    for (int j = mid + 1; j <= r; j++)
        if (comb[j] == -1)
            attempt[j] = state ^ 1;
        else
            attempt[j] = comb[j];
    for (int j = r + 1; j < n; j++)
        if (comb[j] != -1)
            attempt[j] = comb[j];
    int verdict = tryCombination(attempt);
    if (verdict == i)
        return bs(mid + 1, r, i, state);
    else
        return bs(l, mid, i, state);
}

void exploreCave(int N)
{
    n = N;
    for (int i = 0; i < n; i++)
        match[i] = comb[i] = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (comb[j] == -1)
                attempt[j] = 0;
            else
                attempt[j] = comb[j];
                
        int verdict = tryCombination(attempt), state, pos;
        if (verdict == i)
            state = 1;
        else
            state = 0;
        pos = bs(0, n - 1, i, state);
        //cerr << i << "->" << pos << ":" << state << '\n';
        comb[pos] = state;
        match[pos] = i;
    }
    for (int i = 0; i < n; i++)
        S[i] = comb[i], D[i] = match[i];
    answer(S, D);
}
```

然後是TIOJ上的：
```cpp
/*  | |       _    _  | |        _____       | |
//  | |   _  | |  | | | | _____ /  ___|__  __| |___  _____
//  | |  |_|[   ][   ]| |/  _  \| |    | | | |  _  \/  _  \  
//  | L__| | | |_ | |_| || ____|| |___ | |_| | |_| || ____|
//  L____|_| |___||___|_|\_____|\_____|\_____/\____/\_____|
//  Segment Tree is hard.
*/
#pragma GCC optimize("Ofast,unroll-loops")

#include "lib1839.h"

int n, comb[5005], match[5005], attempt[5005], S[5005], D[5005];

int bs(int l, int r, int i, int state)
{
    if (l == r)
        return l;
    int mid = (l + r) / 2;
    for (int j = 0; j < l; j++)
        if (comb[j] != -1)
            attempt[j] = comb[j];
    for (int j = l; j <= mid; j++)
        if (comb[j] == -1)
            attempt[j] = state;
        else
            attempt[j] = comb[j];
    for (int j = mid + 1; j <= r; j++)
        if (comb[j] == -1)
            attempt[j] = state ^ 1;
        else
            attempt[j] = comb[j];
    for (int j = r + 1; j < n; j++)
        if (comb[j] != -1)
            attempt[j] = comb[j];
    int verdict = tryCombination(attempt);
    if (verdict == i)
        return bs(mid + 1, r, i, state);
    else
        return bs(l, mid, i, state);
}

signed main()
{
    while (1)
    {
        n = Initialize();
        for (int i = 0; i < n; i++)
            match[i] = comb[i] = -1;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                if (comb[j] == -1)
                    attempt[j] = 0;
                else
                    attempt[j] = comb[j];

            int verdict = tryCombination(attempt), state, pos;
            if (verdict == i)
                state = 1;
            else
                state = 0;
            pos = bs(0, n - 1, i, state);
            //cerr << i << "->" << pos << ":" << state << '\n';
            comb[pos] = state;
            match[pos] = i;
        }
        for (int i = 0; i < n; i++)
            S[i] = comb[i], D[i] = match[i];
        answer(S, D);
    }
}
```
