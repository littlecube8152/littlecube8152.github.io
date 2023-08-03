---
title: "[Virtual] NERC 2021-2022"
description: "團練篇"
date: 2022-12-07T23:00:00+08:00
draft: false
tags: ["ICPC", "NERC", "virtual"]
summary: "笨方塊耍笨 virtual NERC 拖累隊友還被爆揍，燒雞"
---

## 前言
NPSC 團練的第三場，也就是最後一場。  
這篇因為打到有點累了所以可能會有點偏紀錄性質。  

## Virtual
一開始高嘉泓先看到 C 有人開，

> pC  
> 給定三個平面上的點，求 Manhattan Steiner Tree。  

我想了一下有一些 case，但高嘉泓說他的不用直接就上去寫了。  
寫完我幫他測了一些邊界的 case，不過我們不確定可不可以輸出長度是 0 的線段所以我們就稍微改了一下傳上去，  

### 14 pC <green>+</green>
</br>

接下來換我開剛剛讀完想好解的 D，  

> pD  
> 給定兩個字串 $s,\\,t$，對每個 $s$ 裡的字元都必須選擇一個分界點，並且把分界點前面都刪除，後面都保留。  
> 問保留的結果是否可為 $t$。  
> 測資數 $\leq 10000,\\,1 \leq |s|,\\,|t| \leq 30$  

只要從後面枚舉，要是有一個時刻必須刪掉就紀錄，然後 greedy 配對就好。  

### 18 pD <green>+</green>
</br>

下一個多開的是 L，  

> pL  
> 給一張 $n$ 點 $m$ 邊的有向圖，以及一個給定的起點 $s$，  
> 求出起點在 $s$ 終點在某個 $t$ 的兩條點相異路徑，$t$ 可以自己決定。  
> $2 \leq n \leq 2 \cdot 10^5,\\,0 \leq m \leq 2 \cdot 10^5$  

高嘉泓超強，想出用 DFS 然後一個點只能推一條路出去就做完了。  

### 29 pL <green>+</green>
</br>

接下來還是跟著記分板走，所以我就先去看 J，  
> pJ  
> 給定一個表格 $c_{ij}$，求出一棵二元樹滿足  
> $\sum_{i<j}c_{ij}d_{ij}$ 最小，其中 $d_{ij}$ 是 $i,\\,j$ 在樹上的距離。  
> $1 \leq n \leq 200$  

很顯然把 $c_{ij}$ 做二維前綴和方便查詢 cost 然後做個區間 DP 就好，  
不過中間發現我一直少東少西 debug 花了一小段時間，然後還要構造那棵樹，  
最後還是寫出來了，感覺花的時間可以再少一點點。  

### 57 pJ <green>+</green>
</br>

下一題 F 是高嘉泓跟我說有很多隊做的，他看起來是數學題，  

> pF  
> 給定一個序列 $a_i$，你要把他重排成一個序列 $b_i$ 滿足：  
>  - $b_1 < b_2 > b_3 < b_4 > b_5 < \cdots$  
>  - $b_2 < b_4 < b_6 < \cdots$  
>
> 求出可能的排列數 $\mod 998\\,244\\,353$。  
> $1 \leq t \leq 2500,\\,2 \leq \sum n \leq 5000,\\, 2 | n$  

一開始高嘉泓跟我說可能是數學題，但我後來想想其實只要記錄最後一個最大的是多少就能好好 DP，  
題目很有良心把 $\text{mod}$ 設成質數可以算完直接除掉同樣數字數量階乘的模逆元，所以我就再上去寫了一題 DP，  
細節處理出了小問題，不過其實想比寫的時間要多一些，  

### 107 pF <green>+</green>
</br>

下一多人開的題目就是 I 了，  

> pI 互動題  
> 有一個 $n\times m$ 的網格，裡面藏有兩格是寶藏，  
> 你可以做以下兩種查詢：  
>  - `DIG` $x$ $y$：挖 $(x,\\,y)$ 的格子並回傳有沒有寶藏。  
>  - `SCAN` $x$ $y$：查詢 $(x,\\,y)$ 格子與兩個寶藏位置的曼哈頓距離和。  
>
> 請用 $7$ 次查詢使得兩個寶藏的位置都有被挖過至少一次。  
> $2 \leq n,\\,m \leq 16$  

一開始高嘉泓好像想到了兩個三分搜 + $3$ 次的作法，  
後來我突然想到兩個三分搜可以改成各 $3$ 次就好，共用其中一個點就變 $5 + 3 = 8$ 次了，  
不過想到這裡我們就卡了很久，不知道要怎麼壓剩下的次數。  

後來高嘉泓把式子寫開之後發現可以透過 $(1,\\,1)$ 跟 $(1,\\,m)$ 得到 $(n,\\,m)$ 的答案，壓到 $7$ 次。  
可是他寫的時候出了小狀況，所以我就上去用暴力建出圖的方法做完他的想法，  
我真的不管幾次遇到純數學題都會燒成智障欸，到底要怎麼辦...  

### 190 pI <green>+</green>
</br>

剩下的時間我們在全力做 E，因為 G 一臉看來我們是實作不出來的，  

> pE  
> 你要把 $[0,\\,l]$ 分割成 $n$ 個線段 $l_i$，滿足 $a_i \in l_i$，  
> 求出 $\max |l_i| - \min |l_i|$ 最小的其中一組解。  
> $1 \leq n \leq 10^5,\\,2 \leq l \leq 10^9,\\,0 < a_1 < a_2 < \cdots < l$  

一開始我列了一個看起來很像假解的不等式，然後發現他真的是假解，  
後來過了很久一段時間，我們就想到可以二分搜最短長度 $k$，因為感覺他的解會是比較好的，  
然後就可以二分搜差值 $d$，最後構造解，  
二分搜最短長度好解決，但二分搜差值我們想了很久，  
原本有個 greedy 的作法可是他的實作複雜程度太高了，所以我們後來就想到把所有長度都先減掉 $k$，  
然後就是找到一組解 $b_i$ 滿足  
$a_i - i \cdot k \leq b_i \leq a_{i + 1} - i \cdot k$、$0 \leq b_i \leq d$ 跟 $a_n = l - n \cdot k$  
歸出來之後我們就發現對合法範圍 greedy 就變得超好做，所以就寫下去了。  

### 239 pE -1
</br>

我改了個無關緊要的東西就再傳了一次。  

### 240 pE -2
</br>

後來我生幾筆就生出爆掉的了，  
後來我發現我的 $d$ 在二分搜的時候忘記限制那些範圍，所以就加了一些範圍然後多測幾次，

### 261 pE <green>+2</green>
</br>

可惡，斷了一發的節奏（X  

## 檢討 

其實這場除了 I 跟沒有實作大噁題 G 都還蠻順的，  
其次就是有些可以想更快，實作更穩，  
完全沒想到 NPSC 會跟這場差這麼多。  

可能我太笨了吧，我，這個 OI 不會也打不起 ICPC 的笨蛋，真的需要加強數學。  