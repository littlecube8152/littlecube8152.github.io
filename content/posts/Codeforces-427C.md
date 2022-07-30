---
title: "[Codeforces] 427C"
description: "Checkposts"
date: 2021-04-21T02:17:49+08:00
draft: false
tags: ["codeforces","tutorial"]
summary: "笨方塊想學寫程式被爆揍，燒雞"
---

雖這題很水，但還是記錄一下又寫掉新的演算法了:happy_mention:  

## 題序
[Link](https://codeforces.com/contest/427/problem/C)  
有$N$個區域跟$M$個單向道，你可以在其中一些設立警局，  
一個警局有效的巡邏範圍是：  
如果有警局在$i$，而且有路徑從$i \rightarrow j$以及$j \rightarrow i$，  
這樣那個警局就可以巡邏到$j$，  
問全部區域都被警局巡邏到的情況**最小花費**跟**方案數**。  

## 提示
### Hint 1
什麼樣範圍中的點只要設立一個？  
　　  
## 想法
SCC裸題啦XD   
就不解釋了，基本上用兩次DFS會比較好實作。  

## AC Code
[Link](https://codeforces.com/contest/427/submission/113643274)