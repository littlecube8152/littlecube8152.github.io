---
title: "2022 NHSPC 全國學科能力競賽 + 模擬賽"
date: 2022-12-19T14:00:00+08:00
draft: false
tags: ["NHSPC", "OI"]
summary: "笨方塊在全國賽耍笨，不會寫程式還被爆揍，燒雞"
---

大概在 NPSC 燒完雞然後段考跟模擬考又考的很爛的時候，全國賽就快到了，  
整個十二月事好多= =  

因為兩場都是蠻重要的比賽，所以這裡開個防雷跟傳送連結。  
（如果你覺得沒差就直接往下看就好）  

**[全國模擬賽](./#全國模擬賽)**  

**[全國賽](./#全國賽)**  

</br></br></br></br></br></br></br></br>

## 全國模擬賽
### 測機
測機大概就是我一邊搭火車回家一邊看題目，  
A、C 是兩道水題，然後 B 是一題酷酷的樹題目，  
D 是奇怪的樹題目，然後 E 是 IOI 的數獨測機。  

一開始我 B 還亂吃毒但後來想一想根本就沒有這麼難啊，只要維護好查詢節點底下有多少子樹有水就好。  
D 我用怪怪方法壓到 60 分，賺  
E 我寫出來的遞迴 16 $\times$ 16 的跑不出來，雖然後面測資都喇到不錯的分數，  
但我想說要是全國賽出爆搜剪枝，那我大概就慘了。  

測機好像就沒什麼重要的東西了，所以就直接講正式賽吧。  

### 正式賽
正式賽前我在創資料夾的時候想不到全國賽到底是 N、H、S、P、C 的哪個排列，我是英文笨蛋。  

開場先看 A，  
> pA  
> 有 $n$ 個長 $L$ 重 $w_i$ 的方塊，最長可以伸出桌面多少？  
> $1 \leq n \leq 3\cdot 10^5,\\,1 \leq w_i,\\,L \leq 10^9$  
> [25] $n \leq 9$  
> [25] $w_i = 1$  
> [50] 無額外限制  

定位應該是一題水題，可是我還沒打算要推式子，所以就繼續看下去，  
> pB  
> 有 $n$ 個長 $k_i$ 的陣列 $a_i$，求所有 $a_i$ 的排列中接合的最大連續和，  
> $1 \leq n \leq 10^5,\\,1 \leq k_i \leq 10^5,\\,1 \leq \sum k_i \leq 10^6,\\,-10^9 \leq a_{i,\\,j} \leq 10^9$  
> [8] $n = 1$  
> [14] $n \leq 400$  
> [22] $n \leq 3000$  
> [56] 無額外限制  

看完就知道枚舉左右就做完了，所以只要 greedy 枚舉左邊找最好的右邊，不過稍微需要一點點實作，先繼續看下去，  

> pC  
> 有一個長度為 $n$ 的陣列 $a$，你可以把頭尾相同的子陣列反轉，  
> 也就是 $[l,\\,r]$ 可以被反轉如果當下的 $a_l = a_r$，  
> 你要最小化滿足 $a_{i - 1} < a_i > a_{i + 1}$ 或 $a_{i - 1} > a_i < a_{i + 1}$ 的 $i$ 的數量，  
> 輸出其中一組解。  
> $3 \leq N \leq 10^6,\\,1 \leq a_i \leq N$  
> [9] $N \leq 10$  
> [20] $a_i \leq 2$  
> [17] $N \leq 1000$  
> [21] $N \leq 10^5$  
> [33] 無額外限制  

稍微想完完全沒頭緒，所以就回去把 A、B 都寫掉，  

 - **0:15 B 0**  

 - **0:15 A <green>100</green>**  

我傳錯 code 了，超好笑，  

 - **0:27 B 0**  

因為我忘記判有可能是單一一個是最佳，我太笨了，  

 - **0:30 B <green>100</green>**  

回來想 C，想了很多唬爛例如能換就換之類的，但我隨便構就構出反例了，  
在這上面花了一點時間，但後來就跳題了，  

接下來看 D，  
> pD  
> 有一張 $N$ 點 $M$ 邊沒有自環的無向帶權簡單連通圖，以及一個 $p$ 為 $[1,\\,M]$ 的排列，  
> 你需要構造邊權滿足：  
>  - 第 $i$ 條邊的邊權是 $h_i$，則對 $1 \leq j < M$ 都有 $h_{p_j} < h_{p_{j+1}}$  
>  - $1 \leq h_i \leq 10^{12}$  
>  - $S$ 到 $T$ 的最短路是 $D$  
> 
> $2 \leq N \leq 10^5,\\,M \leq 2 \times 10^5,\\,1 \leq S,\\,T \leq N,\\,S \neq T,\\,1 \leq D \leq 10^{11},\\,1 \leq p_i \leq M$  
> [5] $M = N - 1$  
> [9] 圖是一個環  
> [23] $N \leq 3000,\\,M \leq 5000$  
> [63] 無額外限制  
> 如果能判斷是否有解但構造失敗可以拿一半的分數。  

首先我是有了一個最短路的假解，就是把邊權先設成 $1$ 到 $M$ 跑一次，然後把最大邊改掉，  
但我很快就想到可能有反例，例如有一條可能是 1 -> 2 -> 7 但改掉之後最短路變成 1 -> 5 -> 6，  
但這種反例又不是輕輕鬆鬆做個像 MST 的就能做，因為它會把最短路的性質弄爛。  

後來就想到只要二分搜最小的 $k$ 滿足前 $k$ 條邊的最短路 $\leq D$ 就好，  
好好寫然後跟我平常一樣出 bug 修半天就寫掉了，  

 - **1:21 D <green>100</green>**  

接下來是一題超難題 E，  
> pE  
> 有一個 $C \times C$ 的平面，網格上有一些位置會有怪人要 merge 你，  
> 每單位時間內你可以先移動一單位的距離，然後其他怪人也可以移動一單位，  
> 如果存在一個時刻你跟怪人重疊，你就會被 merge，  
> 而要是你在沒有被 merge 的情況下在網格外就算做是安全的，  
> 一開始網格上是空的，請支援 $n$ 次加入怪人，  
> 並輸出當下網格內有多少格子作為起始點，在雙方皆以最佳策略底下會逃不出網格。  
> $1 \leq n,\\,C \leq 2\times 10^5$  
> [7] $n,\\,C \leq 30$  
> [10] $n \leq 50000,\\,C \leq 1000$  
> [14] $n \leq 1000$  
> [31] $n \leq 50000$  
> [38] 無額外限制  

我看完就去上廁所想 Subtask 2，想到之後我才發現我看錯題目了，真笨。  
所以就很自然地跳了 F，  

> pF  
> 有一棵樹，給定一個點 $A$，你可以詢問 $B$ 與某個你可以決定的 $C$ 的 LCA，  
> 求在最佳策略下最壞要花多少次詢問才能找到 $B$。  
> $1 \leq A \leq N \leq 10^6$  
> [29] 給定的樹是二元樹  
> [71] 無額外限制  

看了之後就知道第一個想法是查葉子就好，但後來就沒想法了，  
感覺是 DP，但不知道要怎麼做，所以就先丟著，  

> pG  
> 有 $N$ 個數，$Q$ 詢問有多少數字在 $b_i$ 進位下位數總和是 $M$。  
> $1 \leq N,\\,M,\\,Q \leq 2 \times 10^6,\\,2 \leq b_i \leq 10^9$  
> [9] $N,\\,Q \leq 2000$  
> [29] $a_i \leq 40000$  
> [24] $a_i \leq 3 \times 10^5$  
> [38] 無額外限制  

第一想法是分塊，不知道為啥我沒有想到調和級數之類的東西，  
所以就先擱著繼續想想，然後往下看，  

> pH [Communication]  
> 你要在網格上畫圓，詳情請看題本。  

大概估了一下拿不太到分數就先跳，之後有空再碰。  

> pI  
> 給定一個大小為 $n$ 的多重集 $S$，求  
> $\displaystyle\sum_{T \subseteq S} |T| \prod_{x\in T}x \mod 998244353$，  
> $1 \leq n \leq 10^6$  
> [5] $n \leq 20$  
> [15] $n \leq 1000$  
> [30] $n \leq 10^5$  
> [15] 集合的元素 $\leq 20$  
> [35] 無額外限制  

想到的第一想法是數學，所以我稍微湊湊就發現我不會數學，  
這時候大概過半場了，我還是只有 300，我超爛，  
所以我心態幾乎快崩了，但我告訴我自己不可以，  

後來我不知道為啥跑回去想 C，  
接下來一個很關鍵的提示是我在想他要怎麼寫 checker，  
想著想著我就想到如果兩兩相鄰的元素連一條邊，那他們就會圖同構，  
而且序列就會是一條歐拉路徑，  

我以為我這樣就做完了，但我開始不知道要怎麼最小化答案，  
所以我就寫了一下吃了一堆 RE 跟 WA，  

 - **3:16 pC 0**
 - **3:19 pC 0**

接下來想 F，我想到的是令 $dp_i$ 表示 $i$ 的子樹內需要辨別的最少詢問量，  
那對一個點而言，他的所有子樹至少都需要詢問一次，而這個順序應該要是 $dp_i$ 遞減的順序是最好的，  
所以我就寫了之後過範測了耶，  

 - **3:34 pF 0**

吃了一個大大的 WA，  
所以我就開始亂改，然後又吃了一個 WA。  

 - **3:38 pF 0**

我怎麼想都覺得這樣應該就結束了吧，所以我再仔細看一次就發現我 `sort` 忘記加 `greater<>()`，  

 - **3:42 pF <green>100</green>**  

接下來大概可以做的就是 CGI，EH 等這之後再說，  
因為 C 我剛剛燒雞了所以我就選了 G 先去喇部分分，  
基本上就是 $\sqrt C$ 以下的都暴力，以上的都枚舉第二位就好，  
所以就寫了然後出了一大堆的 bug，  

 - **3:52 pG 0**
 - **3:56 pG 0**
 - **3:59 pG 0**
 - **4:02 pG 0**
 - **4:05 pG 0**
 - **4:13 pG 29**  

寫完順便壓一下常數，  

 - **4:16 pG 29**  

我原本預期可以過到 subtask 3，但我顯然壓不過去，所以就先去喇 I，  

I 我一想就想到 $\mathcal O(n^2)$ 的 DP，也就是 $dp_{i,\\,j}$ 表示前 $i$ 個取 $j$ 個的乘積總和，  
然後我就忽然想到這個 $dp$ 不就根本是假的嗎，因為大家都是乘上去而已啊，  
所以後來就變成 $ans_i$ 是前 $i$ 個的答案，而 $sum_i$ 是前 $i$ 個不考慮集合大小的答案，  
那假設第 $i$ 個是 $a_i$，  
$ans_{i} = ans_{i - 1} (a_i + 1) + sum_{i - 1} a_i + a_i$ 以及  
$sum_{i} = sum_{i} (a_i + 1)$  
所以就做完了，  

 - **4:33 pI <green>100</green>**  

後來我 C 還是想不到好的方法，所以就先是去拿了 20 分，  
我一開始想說欸不對，那直接輸出輸入應該會是好的吧，  

 - **4:36 pC 0**

直接吃了一個大大的 WA，我突然想到應該要錯不然我剛剛應該就要過了才對，  
所以我就仔細想想，利用歐拉路徑的性質直接構造一下，greedy 的讓最多人重複就好，  

 - **4:36 pC 20**  

後來就全力賭 G，順便把暴力的 9 分拿到，  
可是我還是壓不過去，怎麼會這樣...  

 - **4:49 pG 29**
 - **4:51 pG 29**
 - **4:53 pG 29**
 - **4:55 pG 38**
 - **4:57 pG 38**
 - **4:58 pG 38**

### 賽後  
一開始我以為我慘了，因為 G 應該可做的說，  
不過看板之後我竟然是一等二？？？  
記分板的狀況大概是 D 一片假解的慘烈，然後決勝點是 FG，  

我的問題是半場睡覺睡太久了，必須再想快一點，  
而 G 跟 C 其實沒有那麼難，G 只要把二位數以上的 generalize 就好，  
直接開陣列維護二位數以上的進位，均攤是指數級數和 $\leq 2$，  
所以總複雜度是 $\mathcal O(C \log C)$，  
C 則蠻酷的，搞懂如何合併歐拉路徑上的環就能做完，但我超笨。  
H 則是我應該可以拿到分數才對。  

感謝負責全國模擬賽的出題者、系統組還有其他工作人員 ><  
這份題目真的很酷，而且比賽中的體驗很棒。  

## 全國賽
### Day 1
今年還是一樣是清大辦的全國賽，  
早上我就跟高嘉泓運動會跑出去搭台鐵轉高鐵，  
我填完外出單生輔組的老師問我要不要跟另一位同學一起簽，我猶豫了一下問高嘉泓，  
高嘉泓 claim 他穿便服不會被抓，所以我就跟老師講他自己有處理好了，  
然後我一出去就看到高嘉泓被警衛攔下來了，燒雞。  

到台鐵之後就去坐沙崙線，我從台南高雄兩地通勤看過超多次但我還真的是第一次坐過，  
大概就是每個人都拿行李但沒什麼人坐的區間車（？  

到高鐵之後我們原本是預期做下一班車，因為我們覺得應該趕不上，  
但我們買完票之後上去剛好上一班車快走，我們就直接跟著上車了，  

大概在高鐵快過台中（還是已經過了）的時候，我突然想到我應該把最近想到的動態樹直徑補一補，  
因此我就在這時候打開電腦開始以全速刻 CEOI '19 diameter，  
快寫完的時候高嘉泓一邊在旁邊膜拜，我一邊開始開我的網路測範測，  
第一筆一測就爆掉了，因為他是強制在線我趕快把詢問輸出比對一下，  
結果是因為我懶得開 IO 加速所以輸入輸出弄在一起，我才以為我搞錯了，  
測了第二筆應該是對的就傳上去了，  
傳到一半高鐵剛好進隧道所以 oj.uz 上就測到一半卡住，我以為是我 TLE 了，  
一出隧道就跳 AC 了，好耶，但高鐵快到新竹了所以我趕快收拾東西，  
一收才發現我們後面好幾位的人有人的咖啡翻倒了，一路流過我們這裡，  
導致我跟高嘉泓的背包都有咖啡的味道，  

趕快下車之後我們就跑到旁邊擦，高嘉泓說他要下去廁所的時候直接沖，超強。  

下車之後我們才發現我們交通破台，Koying 下一班車還要半小時以上，wcwu 則是一點多才會到，狠人，  
我們後來就接續去年的行程去摩斯買午餐，然後等接駁車，  

第一天其實還沒有到很冷，我還穿短袖短褲跑出去吹風（  

接駁車沒啥好講的，至少今天的是，  
坐完接駁車就直接到清大了，清大好像到處都在施工，連我們比賽那棟都是，  
報到完窩不知道要去哪間教室，所以我們找了一圈又回來問工作人員才到，  
我們好像是比較早到的，然後就一邊聽開幕一邊打 tetr.io 之後準備測機，  

今年測機沒有特別講說螢幕可以轉過來，貌似是不能轉，  
題本也有~~無聊的~~小彩蛋，可是我發現得太慢了，所以我都沒拿到小禮物，  
因為 CMS 有開 testing，所以可以測實際時間，  
測出來的結果大概是這樣：
|GCC optimize||操作數|時間|
|:-|:-|-:|:-:|
|O0|`+`|$4.5 \times 10^8$|0.910s|
|O0|`^` (int)|$5 \times 10^8$|0.717s|
|O0|`^` (long long)|$4 \times 10^8$|0.817s|
|O2|`rand`|$10^8$|0.631s|
|O2|線段樹單點修改|$1.5 \times 10^6$|0.825s|
|O2|線段樹區間查詢|$10^6$|0.825s|
|Ofast|線段樹單點修改|$10^6$|0.727s|
|O2|`bitset` $\mathcal O(N^2/w)$|$2.5 \times 10^5$|0.898s|

速度感覺偏快，  

接下來就是去吃晚宴然後去飯店玩了，  
晚宴基本上跟去年差不多，只是有一些東西有換，然後今年有多🉐的真正傳人 Foxyy，  
高嘉泓超會吃，幾乎每一道都他首殺，教我大一位，  
Koying 拍照大師，我之後要小心不要被他食物的照片餓到，  
Foxyy 都亂戳別人然後亂拍很🉐的照片，超怪，  
在這時候，仲人也都拍照起來，Code Community 內外充滿了快活的空氣。  
結束的時候我們這桌還剩超多，可能我太笨了。  

到飯店領房卡的時候我以為我被拋棄了，結果是 Koing 要住第二天清大特選超強，穩了，  
後來我們開始堵 Foxyy，可是他太會卡位了，燒雞，  
Foxyy 跑來玩撲克，但我不會拱🉐也不會寫程式，所以就決定在房間裡耍🉐跟補 BOI '22，  
我確切體會到我真的是個智障，我好笨，  

中間 shaun、HNO2 跟 Gino 有來，後來大家都跑走了，今年的人好像都比較健康，  
Koying 問我要不要 7 點起來，我說好啊，  
然後我就訂了一個不會響的鬧鐘，因為我忘記他只有平日會響，我超級笨。  

 - __比賽前的策略__
    - ⬛ 記得去吃東西跟喝水  
    - ⬛ 不要在一題燒太久
    - ⬛ 不要看錯題目（寫之前再看一次，想不到就再看一次）  
    - ⬛ 高中最後一次了，享受比賽
 - __預測__
    - ⬛ 芒果、victor.gao、becaido 會穩一等獎

### Day 2

我笨笨得起來才發現我賴床了十幾分鐘還被 Koying 拍了怪照片，  
然後就收一收東西去吃早餐了，  
早餐基本上就跟選訓很像，只是稍微多一點點然後空間很大，  
接下來大家都蠻準時的，八點半全部人都到大廳集合了，但沒有工作人員來帶，  
這樣集體 queueforces 的狀況貌似是有帶隊老師去問，我們才上遊覽車被載去清大，  
所以比賽自然就延時了，延了 15 分鐘。  

比賽前貌似有人開始打模板，所以有其他人問可不可以，  
結果工作人員竟然說可以，所以大家都開始打了五分鐘的模板，  
但我模板超級短，虧爆 qwq   

開場就有 clarification 說 A 的 $w_i$ 範圍有誤，然後 $X$ 可以輸出 $0$，但我不知道是發生什麼事，   

接下來比賽就開始了，
題本貌似排版壞了，子任務配分跟範測的表格感覺有爛，但不太影響閱讀。  
> pA base  
> 有一張 $n$ 點 $m$ 邊的簡單連通圖，點上有軍隊數量 $w_i$，  
> 對每個點都滿足他相鄰的點以及他自己的軍隊數量都大於 $S$，  
> 你要規劃一個移動軍隊的策略，滿足每個點移動出去的軍隊不超過 $w_i$，  
> 一組解的分數是這樣判定的：  
> $K'$ 是有多少基地移動後的基地軍隊數量等於 $S$，  
> $X'$ 是所有移動的最大距離，  
> 測資會給定 $X$。假設最大距離是 $X$ 的時候，最佳解是是 $K^\*$，  
> 那你會得到 $\displaystyle \frac{1}{1.5^{K^*-K'}3^{\max(0,\\,X'-X)}}$ 的分數。  
> $1 \leq n,\\,S \leq 500,\\,n - 1 \leq m \leq \frac{n(n-1)}2,\\,0 \leq w_i \leq 500,\\,5 \leq X \leq 500$   
> [4] 圖是一條鍊  
> [20] 圖是一棵樹  
> [11] $X \geq 20$  
> [32] $X \geq 7$  
> [33] 無額外限制  

超噁題，丟掉。  

> pB bicycle  
> 在數線上，有 $n$ 台自行車，第 $i$ 台在 $a_i$，要停在 $m$ 個位置，第 $i$ 個在 $b_i$，  
> 一個位置只能停一台腳踏車，花費是兩者的距離，  
> 求距離以及構造一組解。  
> $1 \leq n \leq m \leq 2 \times 10^5,\\, 0 \leq a_i,\\,b_i \leq 10^9$，$a_i,\\,b_i$ 全部相異    
> [15] $m \leq 10$  
> [16] $m \leq 100$  
> [5] $m \leq 2000$  
> [64] 無額外限制  

有個很顯然的 $\mathcal O(nm)$ DP，但這題的考點應該是滿分解，  
做了一下發現我想到的 greedy 都是爛掉的，所以就跳過了，提醒自己等等回來拿分。  

> pC card
> 有一個長度為 $n$ 的 deque $S$，每一步可以拿前面或後面，  
> 第 $i$ 步如果拿掉 $S_j$ 的話可以拿到 $S_j(1 + 0.1(i-1))$，  
> 求最大得分。  
> $1 \leq n \leq 2000,\\,10 \leq S_i \leq 10^5,\\,10 | S_i$  
> [29] $n \leq 20$  
> [71] 無額外限制  

我以為又是難難 greedy，但做著做著看到範圍就發現根本就是水水 DP，  
所以我就寫掉了，我開好慢。  

 - **0:15 pC <green>100</green>**  
  
繼續看下去，  

> pD editor  
> 定義正規字串：
>  - `x` 是正規字串  
>  - 如果 $e$ 是正規字串，`[`$e$`]` 也是正規字串  
>  - 如果 $e_1,\\,e_2$ 都是正規字串，那 $e_1$`+`$e_2$ 也是正規字串。  
>
> 給定 $n$ 個正規字串 $S_i$，其中所有 `[`、`]` 都被換成 `|`，然後再有一個 `+` 被換成 `|`，  
> 請還原字串，多個解可以輸出任何一種。  
> $3 \leq |S_i|,\\,\sum |S_i| \leq 10^6$  
> [1] $\sum |S_i| \leq 20$  
> [4] $\sum |S_i| \leq 300$  
> [19] $\sum |S_i| \leq 2000$  
> [76] 無額外限制  

一看直接維護前綴後綴是否合法跟括號的層數就好，  
但我沒有判不能連續出現兩個 `+` 或 `x`，我想賭賭看他可能會有好性質可以保證，  
反正等等再加上去就好了，  
寫了寫了就傳上去了。  

 - **0:29 pD 0**  
  
我想可能掉了一些邊界 case，稍微本地生一下測資再傳，  

 - **0:33 pD 0**  
 - **0:36 pD 0**  

好吧，不如先跳題。  

> pE gears  
> 有 $n$ 個齒輪依序相接或共軸，第 $i$ 個齒輪的齒數是 $b_i^{e_i}$（$b_i \in \\{2,\\,3\\}$），  
> 輸出最後一個齒輪的轉速，如果他是 $2^f3^g$ 輸出 $f$ $g$。  
> $1 \leq n \leq 20$  
> [20] $n = 2$
> [80] 無額外限制  

大水題，隨便寫寫就吃了 WA，  

 - **0:39 pE 0**  
 - **0:41 pE 0**  

完全就是在制裁我亂做不好好想，冷靜下來就做完了，  

 - **0:44 pE <green>100</green>**  

繼續讀題，  

> pF scratchcard  
> 有 $n$ 張卡，每張卡有參數 $W_i,\\,A_i,\\,B_i,\\,C_i,\\,$，  
> $W_i$ 只有三種可能，也就是 $W_i \in \\{10^6,\\,2 \times 10^6,\\,3 \times 10^6\\}$，  
> 如果兩張相異的卡滿足  
> $W_i + W_j \leq A_i + A_j,\\,W_i + W_j \leq B_i + B_j,\\,W_i + W_j \leq C_i + C_j$，  
> 那就能對到 $W_i + W_j$ 的獎金，  
> 輸出所有可能的獎金。  
> $1 \leq n \leq 2 \times 10^5,\\,0 \leq A_i,\\,B_i,\\,C_i \leq 6 \times 10^6$  
> [6] $B_i = C_i = 6 \times 10^6$  
> [31] $C_i = 6 \times 10^6$  
> [63] 無額外限制  

一看到就是裸的三維偏序判 Yes/No 可以 $\mathcal O(n \log n)$ 做到，  
需要一個維護前綴最小值的資料結構，  
但我想說可能要實作一小段時間，所以就先放著，  

> pG tree  
> 給定每個點的 degree $d_i$，  
> 問 $n$ 個點的樹滿足 degree 條件的 Prüfer Sequence 字典序第 $k$ 大，  
> $3 \leq n \leq 1000,\\,1 \leq k \leq 10^9,\\,d_i$ 必定合法  
> [24] $n \leq 8$  
> [27] $d_1 = d_2 = 1,\\,d_3 = d_4 = \cdots = d_n = 2$  
> [49] 無額外限制   

直接抓到我不會 Prüfer Sequence，推了一下忘記怎麼從 Prüfer Sequence 還原成樹，  
但感覺是可以做的所以就先留著吧，  

> pH ussr  
> 構造一張邊是線段的 $n$ 點 $k$ 正則連通簡單平面圖。  
> $1 \leq n \leq 100,\\,1 \leq k \leq 8$  
> [4] $k \leq 2$  
> [31] $k \leq 3$  
> [38] $k \leq 4$  
> [27] 無額外限制  

看到的時候我直接慌了，我以為高中不會出平面圖就把平面圖丟掉，  
結果現在出出來我沒有半個定理可以用，被制裁 qwq  
不過感覺是可以稍微構造的，先放著，  

> pI xmas  
> 有兩個長度為 $n$ 的陣列 $a,\\,b$，  
> 你可以不斷操作，每次操作可以選取一個 $k$，  
> 讓所有 $k|i$ 的 $a_i$ 都變成 $a_i + 1$，如果操作完 $a_i > m$，那他會變成 $a_i - m$，  
> 令 $\zeta_i$ 表示操作選取 $i$ 的次數，  
> 構造字典序最小的 $\zeta_1,\\,\zeta_2,\\,\cdots,\\,\zeta_n$ 且操作完 $a$ 會變成 $b$。  
> $1 \leq n \leq 10^6,\\,1 \leq a_i,\\,b_i \leq m \leq 10^9$  
> [5] $n \leq 10,\\,m \leq 5$  
> [27] $n \leq 100$  
> [68] 無額外限制  

看了看怎麼又要字典序，結果他根本就只有一組所有操作都 $\leq m$ 的解啊，什麼鬼，  
做完就直接弄個 $\mathcal O(n \log n)$ 的調和解，  

 - **1:09 pI 32**  

看來我是被卡常了，加上 `pragma` 然後壓掉 $\mod {}$ 的次數就做完了，  

 - **1:12 pI <green>100</green>**  

回來看 D，我先去 `assert` 一下是我沒判到東西還是找不到解，  

 - **1:27 pD 0**  

結果我發現是我的解可能不合法，  
然後我不知道我到底加了啥，亂傳之後就得到 AC 了，  
好像是忘記初始化還什麼的，  

 - **1:32 pD <green>100</green>**  

接下來先去把 pB 的 36 寫掉，然後策略上是去做 FG，再喇 H 或 B 滿分，最後做 A，  

 - **1:59 pB 0**  
 
我 DP 初始狀況沒設好，我是大笨蛋。 

 - **2:03 pB 36**  
 

F 基本上就是對 $A$ sort，然後對 $B$ 開 $C$ 的 BIT，  
我習慣上是把所有詢問跟加入弄再一起 sort，所以我其實有點搞不懂為啥要雙指針，  
（掃描線不是應該很好寫嗎）  
過程中我有猶豫要不要把 $B$ 給離散化，因為 $6 \times 10^6$ 應該也開得下 BIT，  
最後的決定是離散掉，反正多三四行而且我是常數怪物，我怕卡常。  
因為可能會掃到自己，所以 BIT 上維護最大跟次大，  
寫完要測範測的時候我覺得範測數字都太大了，所以就直接去系統上找檔案，  
結果今年系統上有題本欸，好棒，  
寫完之後好像出了一個 bug，  
這時候 debug 其實有點痛苦，因為我不知道為啥我的 VSCode 不支援 structure binding，  
（但編譯是成功的，因為我是開 `compile.sh` 幫我編譯，不是內建的 code runner，）  
最後是我 `upper_bound` 多 -1，傳上去就穩穩地一發了，好耶，  

 - **2:33 pF <green>100</green>**

回來看 G 我就發現我根本就不需要在乎怎麼回溯，  
因為 Prüfer Sequence 對樹形是 1-to-1，然後每個點只會出現 degree - 1 次，  
這樣就做完了，難點在維護組合數，  
因為我懶得用前綴後綴積，所以我就直接開 `int128` 然後讓最大組合 bound 在 $10^{15}$ 以下，  
這樣就可以直接算當前前綴的組合量有多少了，  
寫完傳上去，  

 - **2:56 pG 27**  

我搞不太懂我為啥會只有 Subtask 2，但我發現我 $n=3$ 忘記判 $k>1$ 了，超笨，  

 - **2:58 pG <green>100</green>**

這時候還有兩小時我可以做 A、B 跟 H，  
A 我有想到可以隨機唬爛一下，但我不是 abc 所以我不會隨機，  
我只能亂寫亂寫吃了三次 WA，  

 - **3:24 pA 0**
 - **3:27 pA 0**
 - **3:29 pA 0**


B 我想想要不是怪怪 greedy 就是 slope trick，但兩個我都不會，  
H 我覺得可以喇分，  

所以顯然是投資 H，亂做就有 4 分了，   

 - **3:41 pH 4**

接下來 submission 有點多我不知道要怎麼講，我就直接先列一下我想的過程再把 submission 一次附上好了，  

後來我就想到 $k = 3$ 的時候可以蓋兩個同心多邊形然後內連外，  
但我沒有發現到座標不能是負的，還有我一直讓外側的那個多邊形蓋到內側，  
所以大概就長得像這樣：  

 - **3:46 pH 4**
 - **3:48 pH 4**
 - **3:51 pH 4**
 - **3:55 pH 4**
 - **3:59 pH 4**
 - **3:57 pH 4**
 - **4:03 pH 35**

後來我有想到 $k = 4$，$n$ 是偶數，但構完傳上去，  

 - **4:08 pH 35**

顯然奇數有解，但我沒想到要怎麼辦，  
那時候我就做出了全場最大的錯誤（其實也還好，但這場我真的打得比較順所以這大概就是最大敗筆吧），  
我以為 $n = 7$ 有解但我構不出來，事實上我應該直接 `assert` 一下看看有沒有，  
所以我就跳題去想喇 A 的隨機。  

我一開始出了一堆問題，像我沒意識到 $w_i$ 可能會大於 $S$，還有評分的 $K,\\,X$ 不能裝弱，所以我要再重算一次，  
總之把我踩到的雷都修一修之後就成功拿到了不到 0.5 分的 Partial 了，  
我還去問是不是他們設錯了，但果然是我爛，  
我明明 Subtask 3（4 好像也是）除了 test 8 都滿分欸 😢  

 - **4:24 pA 0**
 - **4:32 pA 0**
 - **4:34 pA 0**
 - **4:40 pA 0**
 - **4:43 pA 0**
 - **4:51 pA 0**

這時候我想說我都這麼爛，不如來載個題本貢獻社會好了，結果我一把所有題序都點開之後 CMS 就沒有回應了，  
我當下超怕，我只是開 9 個分頁應該不算 DoS 吧，  
結果是他們爛掉了，所以比賽就延了兩分鐘。  

我也不能做啥，我不會平面圖所以就繼續傳 A 看能不能拿到 1 分，1 分就好。  

 - **4:59 pA 0**
 - **5:01 pA 0**

果然我笨。  

結束的時候跟去年一樣隨身碟可以拔走，賺。  

賽後出場我把手機放在背包最底下，所以我拿不到看不到版，  
我以為我會是二等一或二等二，因為感覺芒果很容易就做出 H 然後應該會有人開出 B，  
然後芒果就問我我多少，我們兩個都 671，  
結果我猜錯了，板上面是我跟 becaido 還有芒果並列一等。 

[Unofficial Ranking](../../ranking/NHSPC-2022/Ranking.html) 

感覺這次的重點應該是 F 跟 G（所以全國模擬賽真的有預測到欸，或是我是智障不會判斷），  
還有賽後我跟芒果聯集做完 H subtask 3 的時候我真的覺得我虧爆了，  
B 我應該是想不出來，所以就還好，  
然後 A 滅台，怎麼會這樣...  

小小的檢討一下，我還有很多時間可以做 ABH，所以我應該更要小心最後可能成為關鍵的題目，  
還有 A 這種可能有 heuristic 的題目要練，只是我找不到哪裡有，可能 OI 會 vir 到，  
平面圖的部分應該高中不會再遇到了，頂多就我哪天有空寫篇平面圖論然後從此就把他們都丟掉吧。  

 - __比賽策略達成__
    - ✅ 記得去吃東西跟喝水  
    - 🟨 不要在一題燒太久
    - ✅ 不要看錯題目（寫之前再看一次，想不到就再看一次）  
    - ✅ 高中最後一次了，享受比賽
 - __預測__
    - 🟨 芒果、victor.gao、becaido 會穩一等獎

這樣有算會預測嗎？

仔細看完 CMS 的紀錄我好像半場之後就持續 Rk 1，然後我又是最早達到 671 的，所以我應該算是一等一？  
一方面有一種高中三年努力不是白費的感動，  
但一方面又好氣不能廚回去那些之前亂廚／亂舒服的人（X  
感謝一路上教過我的所有人 ><  

回到一樓之後 nathanlee 有來（但他聽到教授要演講之後就跑回去讀期末了），  
然後 shaun 跟雞塊後來也有來，我被揍爛，  

最後我就搭接駁車回家了，新竹真的好冷。  
有一件小笨事是我這禮拜忘記帶手機充電線的插頭，  
但我全國賽完手機沒電了，所以我只好跑去高鐵的充電室充，  
（感謝當時讓給我的那個人 >< 雖然你可能不會看到這裡）  
我一進去才發現裡面竟然有公共用的線，但我手機一插上去他跟我說七八小時才會好，  
後來我就換成用插頭充電腦然後再轉充手機，效率直接變四倍，  
高鐵上竟然有這種酷地方，讓我能感受到芒果電神無處不在。  

高三上學期的資訊比賽大概就到這邊了，接下來我要好好考學測了，不然我大概會沒有大學可以讀。  
