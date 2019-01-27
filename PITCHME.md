# システムコールについて




   2019-02-09 田村 晃聖

---
# はじめに

## 私は,システムコールについて話します.

- システムコールって何？
- システムコールとは,OSが内蔵している基本的なルーチンを,アプリケーションで使うこと.特に基本的入出力を用いることをBIOSコールという.|

---

## なぜシステムコールについて調べようと思ったのか.


- 四号機 の制御方法に深く関わっているためです.|

- まずそれぞれ四号機と五号機との違いを見ていきます.|

---

### 五号機

    ├── fifth_robot_pkgs
    │   ├── fifth_robot_2dnav # amcl move_base
    │   ├── fifth_robot_description #cartographer simulator
    │   ├── fifth_robot_launcher #sensor_bringup launchfile
    │   ├── fifth_robot_map #map
    │   └── fifth_robot_pkgs #nothing
    ├── goal_sender #targetpose from csv
    ├── goal_sender_msgs #msg generate for goal_sender
    ├── ros_imu_filter #imu config
    ├── teleop_master #radio control
    ├── third_party #laser-driver ypspur
    └── waypoints_reader #csv

---

### 五号機のデバイス

`imu`

`3DLider`

`ypspur`

---

### 四号機

    ├── fourth_robot_2dnav #map amcl move_base param
    ├── fourth_robot_2dnav_gazebo #sim amcl move_base param
    ├── fourth_robot_bringup #joy sensor bringup waypoints-csv
    ├── fourth_robot_control #ragio control
    ├── fourth_robot_description #sim urdf xacro
    ├── fourth_robot_driver #motor controller control
    ├── fourth_robot_gazebo #world for sim
    ├── fourth_robot_slam #for imu
    ├── README.md
    └── scripts
    
---

### 四号機のデバイス

`2DLider`

`iMCs01`

`BLHD5100K`

### 使われていない

`gim30`

`imu`

---

## `fifth_robot` `fourth_robot` の違い

|`fifth_robot`|`fourth_robot`|
---|---
|`imu, 3DLider`|`2DLider`|
|`ypspur`|`iMCs01, BLHD5100K`|

この他,モータなどは割愛

---

### `motor-driver` を自分で管理する必要がありました.

四号機のモータコントローラ・ドライバの設定ファイルを調べることにしました.

---

### 四号機

'fourth_robot_driver L155~L165'


```

  if(ioctl(fd, URBTC_COUNTER_SET) < 0)
    throw logic_error("Faild to ioctl: URBTC_COUNTER_SET");

  if(write(fd, &cmd_ccmd, sizeof(cmd_ccmd)) < 0){
    ...
    throw logic_error("Faild to write");
  }

```

---

四号機では`imcs01`を使ってドライバの制御を行っていたため,`imcs01`に書き込むために`ioctl()`を使います.

### `ioctl()`って何？

- システムコール関数の一つです.|

---

### システムイメージ

![img](system_kernel.png)

---

### システムコール

- プロセス生成, 削除
- メモリ確保, 開放
- プロセス間通信
- ネットワーク
- ファイルシステム操作
- ファイル操作(デバイス操作)

があります.

この中で私は,ファイルシステム操作, ファイル操作について話します.

---

ファイルアクセスにはinode番号を介して,ファイル情報を取得します.

inode番号は,ファイルのメタデータを内包しています.

ファイルのinode番号は`ls -i`で調べることができます.

ハードリンクではinode番号は共有されます.ソフトリンクではinode番号は共有されません.

これについてはテストをしてみました.

---

target は元となったファイルを指し示します.

ハードリンクされたファイルとハードリンクをしたファイルはinode番号が等しくなっています.

ソフトリンクされたファイルとハードリンクをしたファイルはinode番号が等しくありません.

```
ls -li

1049558 soft-link-target.txt
1049559 heard-link-target.txt
1049559 heard-link-test.txt
1049560 soft-link-test.txt -> soft-link-target.txt
```

---

inode番号を得る必要がある場合,`stat()`システムコールを利用して取得することができます.

このシステムコールを利用することで,

- ファイルが存在するデバイスのデバイス番号
- inode番号
- パーミッション
- ハードリンク数
- オーナユーザID
- オーナグループID
- ファイルサイズ(バイト数)
- ファイルシステムI/Oのブロックサイズ
- 使用しているブロック数
- 最終アクセス時刻
- 最終更新時刻
- 最終情報変更時刻

---

### システムコール

<img src="img/process_and_os.png">

---

ファイルシステムのシステムコールのインターフェース

- ファイルの作成,削除: create(), unlink()
- ファイルを開く,閉じる: open(), close()
- 開いたファイルからデータを読み出す: read()
- 開いたファイルにデータを書き込む: write()
- 開いたファイルの所定のⅠに移動: lseek()
- 上記以外のファイルシステム依存の特殊な処理: ioctl()

---

## `open()`システムコール

open()システムコールはファイルディスクリプタを返すシステムコール関数です.

エラーが発生した場合には-1が返ります.

```
#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

int open(const char *name, int flags);

int open(const char *name, int flags, mode_t mode);
```

---

## `open()`システムコール

flagsにはO_RDONLY, O_WRONLY, O_RDWRを指定します.

またビットOR演算子で動作を制御することができます.

---

## `open()`システムコール

O_APPEND
- ファイルを追加書きモード

O_ASYNC
- ファイルが端末またはソケット時にシグナルを発生させます.

O_CREAT
- 指定されたファイルがないときに,新たに作成します.

O_DIRECT
- ダイレクトI/O用にファイルを開く.

---

## `open()`システムコール

O_DIRECTORY
- nameがディレクトリでない場合はエラーを返します.

O_EXCL
- nameの名前が存在していた場合エラーを返します.

O_LARGEFILE
- サイズが2G以上のファイルを開くときに指定します.64ビットアーキテクチャの場合デフォルトで設定されます.

O_NOCTTY
- nameが端末を指す場合に,プロセスの制御端末にしません.

---

## `open()`システムコール

O_NOFOLLOW
- nameがシンボリックリンクのときにエラーを返します.

O_NONBLOCK
- ファイルをノンブロックモードで開きます.

O_SYNC
- 同期I/O用にファイルを開きます.

O_TRUNC
- ファイルがすでに存在し,かつ書き込み用のフラグを与えられているとき,ファイルをトランケートします.


---

## `open()`システムコール

modeはパーミッションを指定できます

こちらもビットOR演算子で渡すことができます.

---

## `open()`システムコール

S_IRWXU

- rwx --- ---

S_IRUSR

- r-- --- ---

S_IWUSR

- -w- --- ---

S_IXUSR

- --x --- ---

---

## `open()`システムコール

S_IRWXG

- --- rwx ---

S_IRGRP

- --- r-- ---

S_IWGRP

- --- -w- ---

S_IXGRP

- --- --x ---

---

## `open()`システムコール

S_IRWXO
 
- --- --- rwx

S_IROTH

- --- --- r--

S_IWOTH

- --- --- -w-

S_IXOTH

- --- --- --x

---

## `creat()`システムコール

`creat()`システムコールは`open()`システムコールの特殊化と言っても良いでしょう.

```
int creat(const char* name, mode_t mode);
```

これは次のコードと同義です.
```
int creat(const char* name, mode_t mode)
{
  return open(name, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
```

---

## `read()`システムコール

```
#include < unistd.h >

ssize_t read(int fd, void *buf, size_t len);
```

ここで引数のlenはバイト数を与えます.

ファイルディスクリプタを与え,lenバイトbufに読み込みます.

受け取ったバイト数を返します.エラーが発生した場合は-1が返ります.

途中に何かの割り込みがあった場合,戻り値とlenが異なるために識別することができます.

---

## `ioctl()`システムコール

ioctl関数の宣言部

`#include < sys/ioctl.h >`

にて次のように宣言されています.

`extern int ioctl (int __fd, unsigned long int __request, ...) __THROW;`

ファイルディスクリプタを取り,ファイルへアクセスします.

---

## `ioctl()`システムコール

`ioctl()`システムコールは特殊なI/O操作時に使用されるものです.

シリアルポートとのデータ受送信などに使用されます.

帯域外通信が可能です.

---

## `ioctl()`システムコール

```
ioctl(cdrom_fd, CDROMEJECT, 0);
```

とすることで,デバイスのCDのイジェクトを要求することができます.

---

このように,`ioctl()`を使用するときは,そのデバイスの操作マニュアルについて調べる必要があります.

---

### 参考資料

[最新パソコン・IT用語辞典](https://www.kinokuniya.co.jp/f/dsg-01-978477414174)

[［試して理解］Linuxのしくみ～実験と図解で学ぶOSとハードウェアの基礎知識](http://gihyo.jp/book/2018/978-4-7741-9607-7)実験プログラム

[Linuxシステムプログラミング](https://www.oreilly.co.jp/books/9784873113623/)
