# 基于stm32的简单二进制矩阵键盘游戏机
## 功能描述
通过四个LED灯亮灭的不同状态，来表示一个十六进制数，每一个led灯表示一位二进制数，通过矩阵按键的16个按键来表示0-f。按下开始按键游戏开始，开始后计时一分钟，灯随机显示不同的数，玩家进行进制转换后按下对应的按键，按对后加分并显示在oled屏幕上，蜂鸣器产生提示音并产生下一个随机数，按错后蜂鸣器报警不加分并产生下一个随机数，一分钟后结束，再次按下开始按键重新开始。  
佩佩做的三级项目的作业，一个小小的简单游戏机系统，功能越做越多才发现自己太菜了会的东西还是太少了hhh
## 废话（2020-04-06）
__小作文写在最后__
忽然发现本科阶段写过的很多代码由于自己当年的懒惰，很多都已经丢失，做过的很多项目，也只剩下一个项目经历，源码都已经被我不知道丢到哪里去了hhhh。之前没有在社区上传，总是感觉自己比较菜鸡，写的代码太简单太垃圾，传了以后反而怕有些丢人。回想以前做过的寻迹小车啊pid算法啦，角度测算啦等等等等，虽然现在写出来也仍然能够实现，但却没有时间和精力。如果当时有上传上来，虽然写的比较简陋，但是也是能给自己提供一些参考意义的，不能怕丢人hhhh~之前仍然保留的部分代码我会抽空整理上传，找找以前写代码的成就感hhh

