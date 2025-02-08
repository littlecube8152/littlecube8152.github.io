---
title: "[Codeforces] 587F"
description: "Duff is Mad"
date: 2023-10-28T02:00:00+08:00
draft: false
summary: "笨方塊想學寫程式被爆揍，燒雞"
---

期中考前隨興寫題目寫到一題字串題，最終用了很奇怪的複雜度過了，自己還算錯一次，覺得這樣值得紀念所以寫了這篇文。  

## 題目敘述
[Link](https://codeforces.com/contest/587/problem/F)  
有 $n$ 個由小寫字母組成的字串 $s_i$，支援 $q$ 筆詢問：  
 - 讓 $\mathrm{occ}(t, s)$ 表示字串 $s$ 出現了幾次 $t$，給定 $l, r, k$ 回答 $\sum_{i=l}^{r}\mathrm{occ}(s_i, s_k)$.  

$1 \leq n, q, \sum |s_i| \leq 10^5$

## Weird Solution

考慮離線並對字串的長短分塊，假設 $N = \max (\sum |s_i|, q)$。  

 - Case 1. $s_i \geq K$  
   可以將所有字串丟進 AC 自動機中求得所有 $\mathrm{occ}(s_j, s_i)$，直接用前綴和離線回答答案。時間複雜度 $O\left(N \cdot \frac N K\right)$。
 - Case 2. $s_i \leq K$
   一樣丟進 AC 自動機中匹配，不過事先對自動機上節點預處理「不斷跳 fail link 第一個遇到的字串結尾節點」，這時候每次匹配一個新的字元的時候，一口氣按照這個預處理的結果不斷跳下去並蒐集所有節點。  
   求答案時可以直接對蒐集到的所有節點計算「某個節點上有多少位於 $l, r$ 之間的字串尾」。時間複雜度 $O\left(N \cdot K^2 \log N\right)$。

這樣總時間複雜度取 $K = \left(\dfrac{N}{\log N}\right)^{\frac 1 3}$，會得到 $O\left(N^{\frac 5 3}\log^{\frac 1 3} N\right)$，空間只需要 $O(N\Sigma)$ 開自動機。  

實際寫下去會過（感覺是沒有人特別卡，不過這個作法應該不至於太糟，應該還是會過的）。  

小插曲是，我以為 Case 2 的其實只有 $O\left(N \cdot K \sqrt K \log N\right)$，不過實際上「跳 $\sqrt N$ 次就會結束」必須要以總共的字串長度來看，所以算出了另一個奇怪複雜度，不過代進去實際數字其實差不多就是了，所以沒有差太多。

## Better Solution

事實上 Case 2. 有個更好用的性質，也就是利用 fail link 會形成一棵樹，根會在起始節點，所以上面的問題會變成一個掃描線問題，每個節點要查詢的會是根到祖先的路徑，每個詢問要查詢的就是那一堆走到的狀態分別到祖先的路徑上全部的總和，也就是說，我們要解下列的問題：  

有一棵定好根的樹，我們要想辦法處理：  
 - $O(N)$ 次單點加值
 - $O(NK)$ 次查詢根到祖先的和

第一個操作顯然可以貴一點，所以我們考慮對 DFS order 分塊，並讓單點加值變成子樹加值，而路徑詢問變成單點詢問，所以 Case 2 就可以被壓進 $O(NK)$，總時間複雜度來到乾淨的 $O(N \sqrt N)$。

## Reference Code

[Weird Solution](https://codeforces.com/contest/587/submission/230061757) （注意那個註解是我之前算錯複雜度的，所以以這篇為主）  
[Better Solution](https://codeforces.com/contest/587/submission/230062033)  
