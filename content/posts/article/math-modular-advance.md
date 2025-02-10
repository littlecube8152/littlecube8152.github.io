---
title: "[數論] 進階質數與模運算"
date: 2021-07-29T09:18:25+08:00
draft: false
tags: ["math"]
summary: "笨方塊想學更多數學被爆揍，燒雞"
---

[2021 Jul 29] 初稿  
[2021 Aug 17] 我發現 Miller-Rabin 質數測試部分是爛掉的，之後會把這部分重寫，請先不要參考  
[2025 Feb 10] 拿掉質數跟原根，以及重新修整一些敘述。這兩個主題有機會的話會（大概不是在這裡）補上。

## 質數

待補。

## 除法
### Newton--Raphson 除法
與直式除法不同的是，Newton--Raphson 除法的目的是在除法的式子中：

$$N / D = Q$$

如果能找到 $D$ 的乘法反元素（即倒數），
就可以用**乘法**的方式去做除法。

所以如果能找到一個方程式 $f(x)$ 讓 $x = 1/D$ 是其中的一根，就可以用牛頓法去求解，
先觀察一下牛頓法的迭代過程：

$$x_{i+1} = x_i - \dfrac{f(x_i)}{f'(x_i)}$$

最好想到的方程式是$ f(x) = Dx - 1$，然而微分過後會出現 $f'(x) = D$，
分母有出現 $D$，然而我們還沒計算出 $D$ 的反元素，這個方程式是不可行的，
所以我們把原式 $x = 1/D$ 換成$D = 1/x$，
就有 $f(x) = 1/x - D$，微分過後會出現 $f'(x) = - 1/x^2$，
此時代入牛頓法的公式，會得到：

$$ x_{i+1} = x_i - \frac{\frac{ 1}{x_i} - D}{- \frac{1}{{x_i}^2}} = x_i - \frac{x_i - D{x_i}^2}{- 1} = x_i + x_i - D{x_i}^2 = x_i(2 - Dx_i)$$

雖然 $x_i + x_i - D{x_i}^2$ 和 $x_i(2 - Dx_i)$ 看起來很像，不過計算時用後者，意義上的精度會是前者的兩倍。

如果把第 $i$ 步的錯誤設為 $\varepsilon_i = 1 - Dx_i$，則第 $i+1$ 步的錯誤就會是：

$$\varepsilon_{i+1} = 1 - Dx_{i+1} = 1 - Dx_i(2 - Dx_i)  = 1 - 2Dx_i - D^2x_i^2 = (1 - Dx_i)^2 = \varepsilon_i^2$$

也就是說誤差會持續被開平方根，但同時也表示初始值 $x_0$ 不能亂選，
最終取得 $N$ 位精度需要 $O(\log N)$ 的時間。  
  
## 進階模運算
### 數論函數
其實數論函數本身沒有什麼特殊的，基本上就是符合 $f:\mathbb{Z}^+ \rightarrow \mathbb{C}$。
簡單來說就是滿足吃進一個正整數，吐出一個 $\mathbb{Z}$、$\mathbb{R}$ 或 $\mathbb{C}$ 的都算。

### 積性函數
一個積性函數要滿足：
- 定義域是 $\mathbb{Z}^+$，也就是說要是**數論函數**
- 當 $\mathrm{gcd}(a,b) = 1$，$f(a)f(b) = f(ab)$

以下都是積性函數：
- $\Phi(n)$ --- 歐拉函數  
- $\mu(n)$ --- 莫比烏斯函數
    -  $\begin{cases}\mu(n) = 1 & n = 1 \newline \mu(n) = (-1)^k & n = p_1 p_2 \cdots p_k \newline \mu(n) = 0 & n\mathrm{~有次數大於~1~的質因數}\end{cases}$  
- $\mathrm{gcd}(n, k)$ （當 $k$ 固定）--- 最大公因數  
- $1(n)$ --- 1 函數  
    - $1(n) = 1$

另外積性函數有個很重要的性質：

$$
    n = p_1^{a_1} p_2^{a_2} \cdots p_k^{a_k} \Longrightarrow
    f(n) = f(p_1^{a_1})f(p_2^{a_2}) \cdots f(p_k^{a_k})
$$

### 狄利克雷卷積
定義狄利克雷卷積的目的在於：
讓數論函數的乘法是狄利克雷卷積、加法是普通加法，
就可以讓數論函數是一個交換環（一個環但多滿足交換律）。

定義兩個數論函數的狄利克雷卷積如下：

$$(f * g)(n) = \displaystyle\sum_{d|n}f(d)g(\frac{n}{d})$$

注意它也有另一個形式：

$$(f * g)(n) = \displaystyle\sum_{dd'= n}f(d)g(d')$$

而狄利克雷卷積滿足下列運算：  
 - 交換律 $f * g = g * f$  
     -  證明：用第二種形式就很顯然，因為整數乘法有交換律。  
 - 結合律 $(f * g) * h = f * (g * h)$
     -  證明：用第二種形式也很顯然，因為下面總和會是三個東西乘起來 $abc = n$ 然後 $f(a)g(b)h(c)$ 的總和。
 - 分配律 $f * (g + h) = f * g + f * h$  
     -  證明：可以自己驗。
 - 有單位函數 $\epsilon$ 使得 $f * \epsilon = f$  
     -  其中 $\begin{cases}\epsilon(n) = 1 & n = 1 \newline \epsilon(n) = 0 & \mathrm{otherwise}\end{cases}$  
 - 對於任意數論函數 $f$，若 $f(1) \neq 0$，則存在**唯一的 $f^{-1}$** ，使得 $f * f^{-1} = \epsilon$  
     -  可以先構造，因為要有 $f(1)f^{-1}(1) = 1$，$f^{-1}(1) = f(1)^{-1}$，  
        而對 $n \neq 1$，有以下這件事：

        $$\sum_{d|n}f(d) f^{-1}(\frac{n}{d}) = 0$$
        所以可以直接用 $f(1)f^{-1}(n) = -\sum_{d|n, d\neq 1}f(d) f^{-1}(\frac{n}{d})$ 推出
        $f^{-1}(n) = -\frac{\sum_{d|n, d\neq 1}f(d) f^{-1}(\frac{n}{d})}{f(1)}$
     -  因為前面有交換律所以自然會有 $f * f^{-1} = f^{-1} * f = \epsilon$  
     -  假如有兩個 $g, h$ 都有 $f * g = f * h = \epsilon$，那 $\epsilon = f * h = f * g * g^{-1} * h = f * g^{-1} * h \Rightarrow g = h$ 所以 $g = h$，反元素唯一。
 - 積性函數的狄利克雷卷積還是積性函數
     -  證明：
        令 $\mathrm{gcd}(a, b) = 1$，  
        $   \begin{align*}(f * g)(ab)&  = \sum_{d|ab}f(d)g(\frac{ab}{d}) \newline
            & = \sum_{d_a|a}\sum_{d_b|b}f(d_ad_b)g(\frac{ab}{d_ad_b}) \newline
            & = \sum_{d_a|a}\sum_{d_b|b}f(d_a)f(d_b)g(\frac{a}{d_a})g(\frac{b}{d_b}) \newline
            & = \sum_{d_a|a}f(d_a)g(\frac{a}{d_a})\sum_{d_b|b}f(d_b)g(\frac{b}{d_b}) \newline
            & = (f * g)(a)(f * g)(b) \newline\end{align*}$
 - $f, g, f * g$ 三個裡面有兩個是積性的，那剩下的也是。
     -  證明：如果 $f, g$ 是那直接根據上面。如果不是那不失一般性假設 $f, f* g$ 是。
        反證一下，根據良序定理（粗淺的說，我們可以把整數數對排好順序，然後找最小的東西），
        $g$ 若不是積性，那可以找到最小的組合 $a, b$ 互質使得 $g(a)g(b) \neq g(ab)$。
        這邊最小的定義可以找 $a + b$ 最小的。
        這代表說所有 $a' + b' < a + b$ 都會還有 $g(a')g(b') = g(a'b')$。

        $$ 
            \begin{align*} (f * g)(a)(f * g)(b) 
            & = \sum_{pq = a} f(p)g(q) \sum_{rs = b}f(r)g(s) \\
            & = \sum_{pq = a, rs = b} f(p)g(q)f(r)g(s) \\
            & = \sum_{pq = a, rs = b} f(pr)g(q)g(s) \\
            & = f(1)g(a)g(b) + \sum_{pq = a, rs = b, pr \neq 1} f(pr)g(q)g(s) \\
            & = f(1)g(a)g(b) + \sum_{xy = ab, pr \neq 1} f(pr)g(qs) & (*) \\
            & = f(1)g(a)g(b) + (f * g)(ab) - g(ab) \\
            & = g(a)g(b) + (f * g)(ab) - g(ab) 
            \end{align*}
        $$ 
        $(*)$ 這步第一個是因為只有 $qs = ab$ 這組是不能用上面的方法拿掉的（這剛好也是我們想要的）。
        第二是因為 $(p, s), p \mid a, s \mid b$ 的所有方法會一一對應到 $x \mid ab$，
        因為 $a, b$ 互質，任何質因數一定只有一邊有效。

        所以 $g(a)g(b) = g(ab)$，矛盾。$g$ 是積性。  
 -  積性函數的反元素（不是反函數）還是積性函數
    - 由上一點可證
        

### 莫比烏斯反演 
首先，觀察到

$$\sum_{d|n}\mu(d) = [n = 1]$$

原因是因為：
假如 $n$ 有 $k$ 種質因數，

$$\sum_{d|n}\mu(d) = \binom{k}{0} - \binom{k}{1} + \binom{k}{2} - \cdots + (-1)^k \binom{k}{k} = \begin{cases}  1 & n = 1 \\ (1 - 1)^{k} = 0 & \mathrm{otherwise} \end{cases}$$

（考慮到取二次方以上都是 $0$）

當 $n = 1$，$\text{原式} = 1$，否則$\text{原式} = 0$。
所以我們有 $\sum_{d|n}\mu(d) = \epsilon$。
也就是說：

$$\sum_{d|n}\mu(d)1(\frac{n}{d}) = \epsilon(n) \Rightarrow \mu * 1 = \epsilon \Rightarrow \mu^{-1} = 1$$
  
根據這個性質，可以發現如果有兩個函數滿足
$F(x) = \sum_{d|x}f(d)$，
就可以透過莫比烏斯函數的逆函數做出這個轉換：

$$F(x) = \sum_{d|x}f(d)1(\frac{n}{d})$$
$$F = f * 1 \Longrightarrow F * \mu = f$$
<!-- $f(x) = \displaystyle\sum_{d|x}F(d)\mu(\frac{n}{d})$   -->
對於某些跟因數有關的函數可以做出這樣的轉換。  


## 因數
### 因數個數

對於一個整數 $N$，他的因數個數是 $d(N)$。

簡單的因數個數 $d(N)$ 的上界是 $O(\sqrt N)$，
用於估計的話最實際的方法就是跑個爆搜去看看，
不過因數個數也是有一個數學上的上界的，
這邊會一步一步推導出來。

首先需要知道的有：

$$\begin{equation} e^x \approx 1 + x + \dfrac{x^2}{2!} + \dfrac{x^3}{3!} + \cdots \geq 1 + x \tag{1} \end{equation}$$
（在 $x$ 很小的時候，$e^x$ 的泰勒展開式。）

接下來，如果 $N$ 有 $k$ 個質數，可以把 $N$ 表示成：  

$$\begin{equation} N = p_1^{a_1} \cdots p_k^{a_k} \tag{2} \end{equation}$$

然後又由一點點的排列組合，$d(N)$ 可以表示為：

$$\begin{equation} d(N) = (a_1 + 1) \cdots  (a_k + 1) \tag{3} \end{equation}$$

現在要證明的是，對於任何 $\varepsilon > 0$，都有一個常數 $C_\varepsilon$ 使得：

$$\begin{equation} d(N) \leq C_\varepsilon N^\varepsilon \tag{4} \end{equation}$$

換句話說就是：

$$\begin{equation} d(N) = o(N^\varepsilon) \end{equation}$$

證明的方式是，
首先，把 $(4)$ 寫成這個樣子：

$$\begin{equation} \dfrac{d(N)}{N^\varepsilon} \leq C_\varepsilon \tag{5} \end{equation}$$
左邊的部分用 $(2)(3)$ 帶入，得到：

$$\begin{equation} \displaystyle\prod_{i = 1}^{k}\dfrac{a_i + 1}{p_i^{\varepsilon a_i}} \tag{6} \end{equation}$$

把每個質因數分開討論，
分母是指數成長，分子是線性成長，所以在這個條件下 $a_i$ 夠大時分母會超過分子。
但是 $\varepsilon$ 是可以任意選的，所以可能有些組合會讓分子大於分母，
不過可以發現，要達成分子大於分母，必須要 $a_i$ 夠小、$p_i$ 也夠小。  

對於夠大的質數，想要比較的是 $p_i^{\varepsilon a_i} \geq a_i + 1$。

由於 $e^{a_i} \geq a_i + 1$（使用 $(1)$ 的泰勒展開式），
可以先確定當 $p_i^{\varepsilon a_i} \geq e^{a_i} \geq a_i + 1$ 的時候，
$p_i \geq e^{1/\varepsilon}$，而且這一項的貢獻最多只有 $1$。

那對於 $p_i < e^{1/\varepsilon}$ 的質數呢？  
由於 $a_i \rightarrow \infty$ 的時候，$\frac{a_i + 1}{p_i^{\varepsilon a_i}}$ 會趨近於 $0$，
所以這個 $\frac{a_i + 1}{p_i^{\varepsilon a_i}}$ 一定會有某個常數 $C_{p_i, \varepsilon}$ 是他的上界，
因此，所有小於 $e^{1/\varepsilon}$ 的質數都只有對 $(6)$ 有有限度的貢獻，
但是總共的小質數數量也被 $\varepsilon$ 給限制住了，
所以 $(6)$ 就會小於某個只隨著 $\varepsilon$ 變動的常數 $C_\varepsilon$，因此原式得證。

競程中似乎有一個上界是 $O(\sqrt[3]{N})$，這個上界可以用剛剛所證明的代進數字，
不過這樣估因為常數的關係會有點不準。  

有了這個上界之後，可以更進一步把他限制得更緊：

首先，要達到更緊的上界，要先把 $C_\varepsilon$ 求出比較精確的值，
回去考慮 $(6)$：

$$\begin{equation} \displaystyle\prod_{i = 1}^{k}\dfrac{a_i + 1}{p_i^{\varepsilon a_i}} \tag{6, revisited} \end{equation}$$

分母的部分可以用剛剛用過的 $(1)$（泰勒展開式）處理一下：

$$\begin{equation} p_i^{\varepsilon a_i} = e^{\varepsilon a_i \ln p_i} \geq 1 + \varepsilon a_i \ln p_i \end{equation}$$

所以

$$\begin{equation} \dfrac{a_i + 1}{p_i^{\varepsilon a_i}} \leq \dfrac{a_i + 1}{1 + \varepsilon a_i \ln p_i} \leq O\left(\dfrac{1}{\varepsilon \log p_i}\right) \tag{7} \end{equation}$$

當然這個上界可以再逼近一點，不過 $e^x$ 的泰勒展開式在 $x$ 很小的時候相當的精確，所以能逼近的不多。
  
把 $(7)$ 代入 $(6)$，會發現 $(6)$ 的上界是：  

$$\begin{equation} \displaystyle\prod_{p < e^{1/\varepsilon}} O\left(\dfrac{1}{\varepsilon \log p_i}\right) \end{equation}$$ 

為了方便討論，把小於 $e^{1/\varepsilon}$ 的質數的上界設為 $e^{1/\varepsilon}$、$\log p_i$ 的上界設為 $\log 2$ 並當作常數，  
當然還是可以再更逼近一點，但是這裡有個小技巧：  
在處理 $A^B$ 這類的上界的時候，除了 $A$ 很接近 $1$ 的情況，否則把 $B$ 限縮在更好的上界會比限縮 $A$ 更有效。  

因此會得到：  
$$\begin{equation} (6) \leq O\left(\dfrac{1}{\varepsilon}\right)^{\displaystyle e^{1/\varepsilon}} = e^{\displaystyle e^{O({1/\varepsilon})}} \end{equation}$$  
（因為是漸近符號，可以這樣操作）  

這樣表示：  
$$\begin{equation} d(N) \leq e^{\displaystyle e^{O({1/\varepsilon})}}N^\varepsilon \end{equation}$$
將 $\varepsilon$ 設為 $\dfrac{C}{\log \log N}$ 的時候（其中 $C$ 是某個相當大的常數），  
觀察右邊的兩個東西，都取一次自然對數得到：  
$e^{O({\log \log N / C})} = \log^{1/C} N$ 跟 $\dfrac{N C \ln N}{\log \log N}$  
而第二項的成長會超過第一項，所以把他帶入之後得到：  
$$d(N) \leq N^{O(1/\log \log N)}$$  

### 質因數種類數

首先，先定義一個東西叫做**質數階乘**，對於質數 $P$：

$P\# = \displaystyle\prod_{p \leq P \text{ and } p \text{ is prime}} p$  

把質因數種類數表示成 $\omega(n)$，顯然最差的狀況會發生在 $n$ 是質數階乘的時候，  

根據一些酷酷的[定](https://en.wikipedia.org/wiki/Primorial)[理](https://en.wikipedia.org/wiki/Chebyshev_function)，有這個東西：

$$\log x\# = \vartheta(x) \sim x$$
所以 $p\# = e^{(1 + o(1))p}$。

令 $p$ 是第 $k$ 個質數，所以有 $p \sim k \ln k$，
由於 $\log p\# =  \vartheta(p) \sim p$，
（$\vartheta$ 是 first Chebyshev function）
這樣就會推導出：

$$k = \omega(p\#) = \omega(e^{(1 + o(1))p}) = \omega(e^{(1 + o(1))k \ln k}) = \omega(k^{(1 + o(1))k})$$


接下來就是把 $k$ 解出來了，因為：

$$p\# = k^{(1 + o(1))k}$$

所以：

$$k = \dfrac{\ln p\#}{W(\ln p\#)}$$

其中 $W$ 是 Lambert W function，簡單來說是 $f(x) = xe^x$ 的反函數，

把它用上下界代入：

$$k = \frac{\ln p\#}{\log(\ln p\#) - O(\log \log (\ln p\#))} \sim \frac{\ln p\#}{\log(\ln p\#)} = O\left(\frac{\log p\#}{\log \log p\#}\right)$$

由這個結論得知，$\omega(n)$ 會是 $O(\frac{\log n}{\log \log n})$ 的。



### Reference
[The Divisor Bound](https://terrytao.wordpress.com/2008/09/23/the-divisor-bound/)  
[Primorial](https://en.wikipedia.org/wiki/Primorial)  
[Prime number theorem](https://en.wikipedia.org/wiki/Prime_number_theorem)  
[Upper bound number of distinct prime factors](https://math.stackexchange.com/questions/938204/upper-bound-number-of-distinct-prime-factors)  
[Chebyshev function](https://en.wikipedia.org/wiki/Chebyshev_function)  
[Inequalities On The Lambert W Function And Hyperpower Function](https://www.emis.de/journals/JIPAM/images/107_07_JIPAM/107_07_www.pdf)  

