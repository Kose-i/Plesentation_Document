# はじめに

## 私は,ioctl()について話します.

---

## なぜioctl()について調べようと思ったのか.


- 五号機 四号機 の違いを探していたためです.|

---

## fifth_robot fourth_robot の違い

---

### 五号機

---

### 五号機

---

### 四号機

---

### 四号機

---

### driver 周辺の設定ファイルの違いを調べることにしました.

#### 四号機ではimcs01を使ってドライバの制御を行っていたため,imcs01に書き込むためにioctl()を使います.

---

### ioctl関数の宣言部

`<sys/ioctl.h>`

にて次のように宣言されています.

`extern int ioctl (int __fd, unsigned long int __request, ...) __THROW;`

---
