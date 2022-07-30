---
title: "Ubuntu 雙系統"
date: 2022-07-27T00:00:47+08:00
draft: false
tags: ["ubuntu"]
summary: "笨方塊耍笨裝 Ubuntu 被爆揍，燒雞"
---

看到網路上都有很多關於 Ubuntu 的安裝，  
後來自己也總算是安裝成功了，所以就來寫一下統整紀錄好了。

下方列出的參考是一些資料的來源。

## 安裝 Ubuntu
我是以先有安裝好 Windows 的背景下安裝的，如果只想裝 Ubuntu 的我猜可以直接跳到開始安裝。  
Windows 版本是 Windows 10，我不確定 11 有沒有變，但大概 Windows 7、8 都差不多。  

參考[Win10 and Ubuntu 雙系統安裝筆記](https://medium.com/caesars-study-review-on-web-development/win10-and-ubuntu-%E9%9B%99%E7%B3%BB%E7%B5%B1%E5%AE%89%E8%A3%9D%E7%AD%86%E8%A8%98-bc824bef7fb4)。  

### 整理磁區
首先在裝之前，要先清出空間來。  
你可以直接裝一顆新硬碟，或是從舊的擠出空間。  

在 Windows 上按右鍵，開啟**磁碟管理**，接下來就是準備從硬碟裡擠出空間，直接對你要擠出空間來的磁碟分割點右鍵，按下**壓縮磁碟區...**
{{< figure src="/images/install-ubuntu/compress-disk.png" width="400" >}}  
這時候如果順利的話，會直接成功生出一堆空間給你切出來，不過，我自己在切 C: 的時候有遇到能切出來的超級少的問題，爬了文發現這是因為 Windows 還有一堆檔案不是連續存下去的，所以很容易產生只能切一點點的問題。  

參考[在Windows11,10, 8, 7中無法壓縮C槽](https://www.diskpart.com/tw/windows-10/unable-to-shrink-partition-c-0310.html)。

你需要拿掉的有：
- 系統保護，也就是把系統建立還原點的功能拿掉，這個功能在**系統** -> **進階系統設定** -> **系統保護**，注意因為主要是存的檔案造成壓不出空間，**會刪掉所有系統還原點**，使用前要先注意（看要不要放棄切 C:，直接找其他的槽切）
- 系統分頁檔案，這個功能好像是類似虛擬記憶體，在**系統** -> **進階系統設定** -> **進階** -> **效能** -> **進階** -> **虛擬記憶體**，要把他都設成沒有系統分頁檔。
- 停用休眠：直接以系統管理員執行
```cmd
powercfg.exe /hibernate off
```
- 停用 core dump，這個東西在**系統** -> **進階系統設定** -> **進階** -> **啟動與修復**，把它改成「(無)」。

全部做完之後重開機，然後看看可不可以壓出你要的空間了，不管壓不壓得出來，在結束後最好把那些選項都調回來。  
在我的案例裡我還是壓不出來，最終似乎除了訴諸一些~~奇怪的~~硬碟操作工具以外，就是得乖乖地換一個槽切，我自己是選擇後者，折衷在 D: 槽切。

#### 空間要切出多少？
以我來說，我是看到其他人是切總共 50 GB，但要注意的是會有一部份被切成 swap 磁區（置換磁區），這個部分好像是用來休眠或者暫存使用的，根據[上面那篇](https://medium.com/caesars-study-review-on-web-development/win10-and-ubuntu-%E9%9B%99%E7%B3%BB%E7%B5%B1%E5%AE%89%E8%A3%9D%E7%AD%86%E8%A8%98-bc824bef7fb4)的說法，要準備 swap 磁區大概這麼大：  

|RAM<sub>(GB)</sub>| 1 | 2 | 3 | 4 | 5 | 6 | 8 | 12 | 16 ||
|:-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|:-|
|不需要休眠|1|1|2|2|2|2|3|3|4||
|需要休眠  |2|3|5|6|7|8|11|15|20||
|最大值    |2|4|6|8|10|12|16|24|32|(in **GB**)

我不確定這個值是怎麼算出來的，網路上各個來源說的也好像不太一樣，原則上好像是要留一點點空間，然後要休眠的話就要再多加 RAM 上去。  

所以如果你要讓 Ubuntu 有一定的大小的話，那你就要額外算你的 swap 磁區要多大，這樣才不會燒雞。  

#### 切出來的磁區要怎麼辦？
當它顯示是可用空間的時候，我的作法是先不要理他，等到進 Ubuntu 安裝的時候再說。  
到時候 Ubuntu 安裝的地方在 Windows 一般來講是讀不到的（但反過來可以），  
所以不要像我一樣笨還把 D: 重新編號成 E: 然後自己燒雞。  

### 準備 Ubuntu 安裝

先把這些東西關掉：  
- BIOS 裡的  
    - Intel Rapid Start Technology 關掉  
        如果沒有就不用關。
    - UEFI 開機  
        這個一定要有。
    - Secure boot 關掉  
        這個似乎不一定，但我自己是有先關掉比較保險。  
- Windows 裡的
    - Windows 快速啟動關掉  
        他在 **控制台** -> **硬體和音效** -> **電源選項** -> **選擇按下電源按鈕時的行為** 裡，必要時先把**變更目前無法使用的設定**關掉。  

然後準備好一顆 Ubuntu 的安裝 USB，我是參考[上面那篇](https://medium.com/caesars-study-review-on-web-development/win10-and-ubuntu-%E9%9B%99%E7%B3%BB%E7%B5%B1%E5%AE%89%E8%A3%9D%E7%AD%86%E8%A8%98-bc824bef7fb4)的推薦用 Rufus 做，先下載好 Ubuntu 的 ISO 映像檔，然後選 GPT、FAT32，燒進去就可以開始裝了。  

### 安裝 Ubuntu
去 UEFI 裡把開機順序第一個改成 USB（好像叫 Linus 什麼的），然後儲存退出，開始裝。  
接下來就只需要注意幾個點就好，首先是  

#### 安裝語言
這裡選英文萬一進到 tty 比較不會出事，但如果要方便調語言的話可以選中文。  
到時候是可以調的，參考 [How do I change the language via a terminal?](https://askubuntu.com/questions/133318/how-do-i-change-the-language-via-a-terminal)，只需要改  
- `/etc/default/locale`
```bash
LANG="en_US"
LANGUAGE="en_US:en"
```
- `~/.pam_environment`
```bash
LANG=en_US
LANGUAGE=en_US
```
就好。  

#### 磁碟切割
這部分比較重要，萬一弄錯就可以上香了。  
找到剛剛騰出來的可用空間，依序切好  
- 主分割區 — 剛剛的 swap 大小 — 開始位置 — 置換空間（swap）  
- 主分割區 — 給 Ubuntu 的大小 — 開始位置 — Ext4 — 掛載在`/`  
然後一般來說開機載入程式好像不太需要動，我也不是很清楚。  

#### 等待
去耍廢、直播、或是把 `m` 打成 `n`，然後等他裝好。  

### 進入 Ubuntu
裝好之後就照著他的設定，然後接下來重要的事是先把時間調好。  

下這個指令：  
```bash
timedatectl set-local-rtc 1 --adjust-system-clock
```

不然的話 Ubuntu 跟 Windows 的時間會打架，~~但如果你住在 UTC+0 就沒差了~~。  


### 後記
之後我可能會再丟一篇負責記錄我是怎麼搞爆他重裝一次、處理用英文裝 Discord 很醜的問題、還有如何裝 Nvidia 顯卡驅動跟在 Minecraft 裡用它，  
而且我好像還欠一篇我想寫的 CF 解題文章，但我好懶好笨，都打輸 IOI 滿分金芒果手，🥭🖐️⚡🥇🛐。  

