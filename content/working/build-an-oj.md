---
title: "[施工]自架 Online Judge"
date: 2030-04-07T00:37:18+08:00
draft: true
---

## 前言
覺得校內的好像很多cannot judge special judge，  
決定開始自架OJ  

## 模組
[isolate](https://github.com/ioi/isolate) - IOI開源的sandbox，預計用這個當作judger  
[isolate Manual](http://www.ucw.cz/moe/isolate.1.html) - isolate 的文件  
[vm2](https://github.com/patriksimek/vm2) - 備用的sandbox  
[seccomp](https://en.wikipedia.org/wiki/Seccomp) - 備用的sandbox  
[judge0](https://github.com/judge0/judge0) - 備用的judger  


然後我需要用python/js寫一個judge API，負責處理submission，

之後要有一個網站，至少要支援：  
- submit + 自動排版code  
- 瀏覽題目  

好像大致上就這樣，先把judge做出來，然後弄API，  
最後就能架網頁了

## 參考資料

[2017 ACM-ICPC Asia Hua-Lien Regional Contest Machine Setup Notes](https://hackmd.io/@truckski/rJ5pPbeX-?type=view)  
可能是蠻重要的筆記 先留著


## 進度

目前可以做到如何把檔案丟進去isolate裡面了  
稍微講一下isolate可以幹嘛  
他可以做到**有限制的讀/寫資料**，還有**在隔離環境執行檔案**  
如果是用WSL，預設可用的資料夾是/usr/bin (執行檔) 還有一些其他的，
所以/mnt/並沒有在裡面，需要加上 --dir='/裡面會把他當作甚麼名子'='/mnt/你檔案的位置' 之類的東西  
  
然後如果g++出現了cannot execute ‘某個東西’: **vfork: Resource temporarily unavailable**  
似乎是資源不夠，isolate要加上參數 -p 

目前還需要做的事：  
- 搞清楚要怎麼執行
- 能夠judge單一檔案
- 能弄出judge API
- 能弄出網頁  

就先這樣 我把isolate停機休息好了><  