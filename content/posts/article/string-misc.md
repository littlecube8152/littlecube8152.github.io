---
title: "[String] 字串雜談"
date: 2022-07-31T00:00:00+08:00
draft: false
tags: ["string"]
summary: "笨方塊耍笨寫字串被爆揍，燒雞"
---

寫字串被揍爛到有點心得，紀錄一下學到的酷東西。

## Hashing
雜湊的碰撞機率，可以把它看成幾乎是把字串隨機打在對應域 $p$ 裡，所以打 $k$ 次不撞的機率是
$$\frac{p}{p}\times\frac{p-1}{p}\times\frac{p-2}{p}\times\cdots\times\frac{p-k+1}{p}$$
利用 $e^x \approx 1 + x$ 來看，因為通常 $p$ 不會太小，所以
$$\frac{p-k}{p} = 1 - \frac{k}{p} \approx \mathrm{exp}\left(-\frac k p\right)$$
也就是說
$$\frac{p}{p}\times\frac{p-1}{p}\times\frac{p-2}{p}\times\cdots\times\frac{p-k+1}{p} \approx \mathrm{exp}\left(-\frac{k(k-1)}{2p}\right)$$
再用一次得到撞到的機率是
$$1 - \frac{p}{p}\times\frac{p-1}{p}\times\frac{p-2}{p}\times\cdots\times\frac{p-k+1}{p} \approx \frac{k(k-1)}{2p}$$
所以說對 $p$ 而言，大概只能辨別 $\mathcal O(\sqrt p)$ 種不同的字串，不然就會撞到。

## Minimum Rotation
這個問題主要是想解決對一個環狀字串，找到他字典序最小的排列方法。  
顯然可以用 Suffix Array 做掉，但這裡介紹一個酷酷的方法。  

參考 [Lyndon Factorization](https://cp-algorithms.com/string/lyndon_factorization.html)，部分用詞可能不一樣。  

### Lyndon word 
對一個字串 $S$ 而言，他是 Lyndon word 若且唯若
 - $S$ 的字典序比他的所有非空也非本身的後綴來的**嚴格**小。  
其實他就等價他的字典序比他所有環狀字串裡字典序**嚴格**最小的排列方法。  

例如 `abc` 是一個 Lyndon word，但 `aa` 就不是（因為 `a` $<$ `aa`）。  

### Lyndon Factorization 
對一個字串 $S$ 的 Lyndon Factorization 定義為，把 $S$ 切成若干個子字串 $s_1,\\,s_2,\\,\cdots,\\,s_k$ 滿足  
 - $s_1 + s_2 + s_3 + \cdots + s_k = S$，其中 $+$ 是字串串接。  
 - $s_1,\\,s_2,\\,\cdots,\\,s_k$ 都是 Lyndon word 。  
 - $s_1 \geq s_2 \geq \cdots \geq s_k$，其中 $\geq$ 是字典序比較。  
我們先不管他存不存在，先觀察知道如果存在的話，會帶給我們什麼好處。  

對字串 $S + S$ 的 Lyndon Factorization 而言，如果其中一個 $s_i$ 的開頭在第一份的 $S$ 裡，結尾在第二份的 $S$ 裡，那這個子字串的起點一定是其中一個 Minimum Rotation 的開頭。  
考慮所有在這之前的 $s_j\quad(j < i)$ 的開頭，從他們當開頭一定不可能會更好，因為第三條定義：  
 - $s_1 \geq s_2 \geq \cdots \geq s_k$，其中 $\geq$ 是字典序比較。  

考慮所有在這之前不是 $s_j\quad(j < i)$ 開頭的，他們一定更差，因為 Lyndon word 的定義：  
 - $S$ 的字典序比他的所有非空也非本身的後綴來的**嚴格**小。  

考慮所有在這之後在第一個 $S$ 裡，不是 $s_j\quad(j > i)$ 開頭的，他們也一定更差，因為 Lyndon word 的定義：  
 - $S$ 的字典序比他的所有非空也非本身的後綴來的**嚴格**小。  

考慮所有在這之後剩下的那些位置，他們不可能是答案，因為他們一定在前面就被排除了。  

假如我們找不到這樣的 $s_i$ 呢？  
那答案就一定是不旋轉，因為在第二份 $S$ 的開頭就可以剛好適用剛剛的性質。  

### Duval's Algorithm
問題就在，我們要怎麼找到 Lyndon Factorization？  
剛剛我們甚至連存在性都沒有證明，現在我們要證明它的存在性，利用構造演算法。  

現在定義一個新的概念，我們說一個字串 $S$ 是 almost Lyndon word，如果他是由相同的 Lyndon word $s$ 重複以及一段（可能是空的）$s$ 的前綴。  
為什麼這樣定義呢？因為我們可以觀察 almost Lyndon word 有一個性質：  
 - almost Lyndon word 前面重複的那些 $s$ 可以分別切成獨立的 Lyndon word。  

而 Duval's Algorithm 的概念很簡單，他把字串分成三分，分別是：  
**Lyndon Factorization 完的**、**almost Lyndon word**、**還沒處理的**。  

這個演算法的概念是，我們嘗試把還沒處理的最前面一個加入 almost Lyndon word 裡，假如加不進去就把 almost Lyndon word 的前綴那些重複的 $s$ 切掉，然後繼續做。  
但這樣永遠會滿足條件嗎？我們來觀察一下：  
 - 假如加入的字元剛好跟 $s$ 的重複出現吻合  
    那加入一定沒問題。  
 - 假如加入的字元 $ > s$ 接下來的重複出現字元  
    那一樣可以把它加入，也沒問題，因為此時雖然不滿足 $s$ 的重複出現，但整個 almost Lyndon word 現在是 Lyndon word 了，所以可以把它設成 $s$，繼續操作。
 - 假如加入的字元 $ < s$ 接下來的重複出現字元  
    那就需要把前面完整的所有 $s$ 都倒出來變成 Lyndon Factorization 完的。這裡雖然直覺會覺得可以繼續往下做完，但實際上要是這個 $s$ 的前綴有循環就會燒雞，所以要把所有剩下的 almost Lyndon word 都設成還沒處理。  

我們可以驗證一下前兩個條件一定會保持，而第三個條件呢？  
首先，同一批切出去的 $s$ 一定會一樣，所以沒問題。  
而不同批切出去的呢？前面一定會比較大，假如是遇到字元變小，那新的那個屬實會更小，而遇到結尾的話，那新的會是前綴，也確實會比較小。  

大概到這裡已經有演算法的雛型了，繼續把它寫個更詳細一點：  
首先有三個指標，$i$ 指著 **almost Lyndon word** 的開始，$j$ 指著**還沒處理的**開始，而 $k$ 則是用來告訴我們，要維持 $s$ 重複出現的話，下一個字元是什麼。  
一開始 $i = k = 0,\\,j = i + 1$。  
 - 假如加入的字元剛好跟 $s$ 的重複出現吻合  
    那我們就能放心把 $j,\\,k$ 都增加 $1$。   
 - 假如加入的字元 $ > s$ 接下來的重複出現字元  
    那我們就能放心把 $j$ 都增加 $1$，但這時 $s$ 重置了，所以 $k$ 設成 $i$。   
 - 假如加入的字元 $ < s$ 接下來的重複出現字元  
    那我們就需要依序把前面的都清出去，因為 $j,\\,k$ 剛好差一個 $s$ 的長度，所以可以不斷用 $j - k$ 當長度切出去。切完之後把 $k$ 設成 $i$，$j$ 設成 $i+1$，這裡是因為，雖然這邊留下來的是 $s$ 的前綴，但一個 Lyndon word 的前綴有可能不是 Lyndon word，所以我們要把它重新拆解。  

時間複雜度：儘管我們有機會失敗，但每次失敗至少都會有一半的字元被算好，所以整體來說鐵定是 $\mathcal O(|S|)$ 的。

最後只多了判斷哪個是 Minimum Rotation，實作如下：

```cpp
int mincyc(string s)
{
    int n = s.size();
    s = s + s;
    int i = 0, ans = 0;
    while (i < s.size())
    {
        int j = i + 1, k = i;
        while (j < s.size() && s[j] >= s[k])
        {
            k = (s[j] > s[k] ? i : k + 1);
            ++j;
        }
        while (i <= k)
        {
            if(i < n && i + j - k >= n)
                ans = i;
            i += j - k;
        }
    }
    return ans;
}
```

這裡有個小細節可以簡化，也就是 16 - 17 行其實可以改在迴圈開始做，
```cpp
int mincyc(string s)
{
    int n = s.size();
    s = s + s;
    int i = 0, ans = 0;
    while (i < s.size())
    {
        ans = i;
        int j = i + 1, k = i;
        while (j < s.size() && s[j] >= s[k])
        {
            k = (s[j] > s[k] ? i : k + 1);
            ++j;
        }
        while (i <= k)
            i += j - k;
    }
    return ans;
}
```
因為，同一批丟出去的其實會一樣，所以這樣寫也會對。  
