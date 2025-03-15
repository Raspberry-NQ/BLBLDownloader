# BLBLDownloader
## 这是什么?
  这是一个能够批量下载B站视频的小工具，还能断点续传（手动挡）
## 使用方法
#### 1.到github上BBDown项目，按照教程配置好
#### 2.下载本项目的可执行文件，放在和BBDown.exe同一个目录下
#### 3.打开电脑浏览器，找到想要批量下载的up主的主页，复制网址
    比如“https://space.bilibili.com/222103174?spm_id_from=333.337.search-card.all.click”
#### 4.在powershell打开目录
    执行命令 ./BBDown login,然后手机扫码登陆
    执行命令 ./BBDown https://space.bilibili.com/222103174?spm_id_from=333.337.search-card.all.click  
    注意这里换成你要的up主的网页
#### 5.可以看到在目录下生成了一个txt文件，打开，在第一行添加 “st +”并回车
#### 6.启动本项目的程序，输入1，等待运行停止，再输入2，即可开始下载
