---
title: "IZhO 2021 Day 2 B"
description: "Rooms"
date: 2022-11-20T08:00:00+08:00
draft: false
tags: ["IZhO", "OI"]
summary: "笨方塊耍笨寫 IZhO 被芒果爆揍，燒雞"
---

<style type="text/css">
#TableOfContents > ul > li:nth-child(3) > ul
{
    display: none;
}
</style>


## 前言
原本是要寫這場的 virtual 心得，不過打得有夠爛所以就算了吧 -w-  
基本上的問題是我太久沒寫程式，想東西都想不出來，  
放著放著就想出這題來了，紀錄一下順便譴責題解耍我跟稍微拯救一下快變廢墟的 blog。  

## 題敘
[Link](https://codeforces.com/group/Uo1lq8ZyWf/contest/311770/problem/B)

有 $n$ 間房間，用 $n+1$ 間門隔開，頭尾兩間往外是出口。  
第 $i$ 個房間可以獲得經驗值 $a_i$，但是第 $j$ 道門需要當前的經驗至少是 $b_j$ 才能通過。  
任意時刻可以花 $1$ 單位的金錢購買 $1$ 單位的經驗，  
對所有房間輸出抵達出口的最少花費。  
$1 \leq n \leq 10^6,\\,0 \leq a_i,\\,b_j \leq 10^9$  

</br></br></br></br></br></br>

## 題解
### Greedy
首先不管 $n$ 的範圍的話，每個房間分開的策略會是 greedy 的往 $b_j$ 最小的房間先破，直到走到其中一端的終點為止。    
觀察：在兩邊 $b_j$ 都一樣的話，不管哪邊先走都一樣。  
把這個走的順序變換一下，就會得到從最小的門開始，把兩邊打通然後更新其中所有點的花費，現在我們就得解決這個問題。  

### 合併關係
把每次合併計成用門的點連下去兩邊代表的點，然後把合併區間代表的點設成這個門的點。  
顯然合併關係會是一棵樹，而只有門有兩個子節點，  
每個點現在的花費就是從葉子往上走直到某個節點已經把最左邊或者最右邊的門打通的花費，  
這裡可以用啟發式合併做到 $\mathcal O(n \log^2 n)$，可是他太爛了。  

### 觀察
重要觀察：如果一個房間往上走的方法中間先開了第 $i$ 道門再開第 $j$ 道門，我們可以想成是他需要多花費 $b_j - b_i$ 的經驗。  
這時候就有很好維護的性質：  
 - 要開門的時候會多出花費，這個花費可以先把前面累計的經驗都花掉。  
 - 但是進到新的地方得到的經驗不能抵銷掉之前的花費，因為之前的花費必須拿錢補足。  

也就是說，每個人都可以維護兩個數字：**之前拿錢補足的花費**跟**現在還剩下多少經驗可以用**，  
而兩兩操作合併只要按照實際上的時間先後就好，順序並不重要。

就以範例一（$a = \\{2,\\,1,\\,3\\},\\,b = \\{9,\\,8,\\,5,\\,7\\}$）的第 $2$ 間房間來講，依序會是：  
 - 得到經驗 1 單位，總花費是 0，剩下 1 單位經驗  
 - 開第 3 道門，花掉 5 點經驗，總花費是 4，剩下 0 單位經驗  
 - 得到經驗 3 單位，總花費是 4，剩下 3 單位經驗  
 - 開第 4 道門，花掉 7 - 5 = 2 點經驗，總花費是 4，剩下 1 單位經驗  

所以根據這個重要的想法，我們只要
 - 蓋出這棵樹（單調隊列 $\mathcal O(n)$ 或 `set` $\mathcal O(n \log n)$）  
 - 預處理哪些節點不需要繼續往上走（如果一個節點已經可以抵達出口，那它不需要在乎祖先所有的花費）  
 - DFS 計算答案（單調隊列 $\mathcal O(n)$）

總共就有線性時間的做法了，不需要大算法、大資節，甚至比官解描述的解法還要好。  


<details>
  <summary>AC Code</summary>

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define F first
#define S second
using namespace std;
 
ll n, a[2000006], ans[1000006], l[2000006], r[2000006], root, over[2000006], sum[2000006];
vector<int> child[2000006];
 
bool pre(int i)
{
	if (1 <= i && i <= 2 * n && child[i].empty())
		sum[i] = a[i];
 
	for (int j : child[i])
	{
		over[i] |= pre(j);
		sum[i] += sum[j];
	}
 
	if (i == 0 || i == 2 * n + 2)
		over[i] = 1;
	return over[i];
}
 
ll wall(int i)
{
	if (i % 2 == 0)
		return 0;
	else
		return a[i];
}
 
pll merge(pll p, ll k)
{
	if (k > 0)
		p.S += k;
	else if (k < 0)
	{
		if (p.S + k <= 0)
			p = pll(p.F + p.S + k, 0);
		else
			p = pll(p.F, p.S + k);
	}
	return p;
}
 
 
pll zero = pll(0, 0);
 
 
void dfs(int i, pll &pre)
{
	if (child[i].empty())
	{
		pll cur = merge(merge(pll(0, a[i]), pre.F), pre.S);
		ans[i / 2] = -cur.F;
	}
	else
	{
		for (int j = 0; j <= 1; j++)
			if (!over[child[i][j]])
			{
				pll cur = merge(merge(pll(0, sum[child[i][j ^ 1]]), pre.F), pre.S);
				cur = merge(merge(pll(-max(0LL, wall(i) - wall(child[i][j])), 0), cur.F), cur.S);
				dfs(child[i][j], cur);
			}
			else
				dfs(child[i][j], zero);
	}
}
 
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[2 * i];
	for (int i = 0; i <= n; i++)
		cin >> a[2 * i + 1];
	vector<pll> v;
	a[0] = a[2 * n + 2] = 1e12;
	for (int i = 1; i <= 2 * n + 2; i++)
	{
		if (i & 1)
		{
			while (!v.empty() && v.back().F < a[i])
				v.pop_back();
			if (!v.empty())
				l[i] = v.back().S;
			v.push_back(pii(a[i], i));
		}
		else
			l[i] = v.back().S;
	}
	v.clear();
	for (int i = 2 * n + 1; i >= 0; i--)
	{
		if (i & 1)
		{
			while (!v.empty() && v.back().F <= a[i])
				v.pop_back();
			if (!v.empty())
				r[i] = v.back().S;
			v.push_back(pii(a[i], i));
		}
		else
			r[i] = v.back().S;
	}
	for (int i = 0; i <= 2 * n + 2; i++)
	{
		if (l[i] == 0 && r[i] == 0)
			root = i;
		else if (a[l[i]] < a[r[i]])
			child[l[i]].emplace_back(i);
		else
			child[r[i]].emplace_back(i);
	}
	pre(root);
	dfs(root, zero);
	for(int i = 1; i <= n; i++)
		cout << ans[i] << " \n"[i == n];
}
```
  
</details>
