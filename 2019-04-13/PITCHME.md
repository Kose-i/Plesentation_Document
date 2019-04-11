@css[Introduction]

@snap[north span-100]
@css[top-title](強化学習の覚書)
@snapend

@snap[south span-50]
@css[top-name](2019-04-13 田村　晃聖)
@snapend

---
@snap[north-west]
@css[start](はじめに)
@snapend

強化学習とは,機械学習の１分野です.

強化学習では,教師あり学習と教師なし学習の中間的なもので,教師データが一部分でしか与えられません.

そのため,ボードゲームやロボットの歩行などで使用されます.

---
@snap[north-west]
@css[start](はじめに)
@snapend

```
\-----  -> \------------
|Agent|    |Environment|
\-----  <- \------------
```

Agent は　環境に対する主体のことで,行動(action)を起こします

Environmentは, Agent の行動に対して,環境の情報と,報酬を与えます.

報酬を最大化することが強化学習の目的です.

有名な問題に,多腕バンディッド問題があります.

---
@snap[north-west]
@css[start](はじめに)
@snapend

探索:環境の知識を収集すること

利用:環境から得られた知識を元に次の行動を決定すること

@snap[north]
@css[](探索と利用のトレードオフ)
@snapend
---
@snap[north-west]
@css[start](はじめに)
@snapend

- greedy algorithm
```
      これまで腕iから得られた報酬の和
ui = --------------------------------
        これまで腕iをプレイした回数
```
- ε-greedy algorithm
```
確率εでランダムに腕を選ぶ
確率1-εでこれまでの報酬の平均uiが最大の腕を選ぶ
```
- UCB1 algorithm
```
R:払戻額の最大値と最小値の差
まだ選んだことのない腕があれば,そのうちのひとつを選ぶ.

     これまで腕iから得られた報酬の和
ui = -------------------------------
         これまで腕iを選んだ回数
         __________________________
        /2ln(これまでの総プレイ数)
Ui =R* /---------------------------
      v これまで腕iをプレイした回数

ui + Uiが最大の腕を選ぶ
```

---
@snap[north-west]
@css[start](はじめに)
@snapend
---
@snap[north-west]
@css[inter-title](方策オン型学習と方策オフ型学習)
@snapend

方策オン型学習 ...次の行動が更新に影響を与える.

方策オフ型学習 ...次の行動が更新に影響しない.

---
@snap[north-west]
@css[inter-title](TD学習)
@snapend

現在の推定値を学習中の目標値として使用して問題を解いていく手法

Temporal Difference Learningという.

「Rt+1 + γV(St+1) - V(St)」を「TD誤差」という.

この誤差を０に近づくように更新していく手法.

---
@snap[north-west]
@css[inter-title](Sarsa法)
@snapend

現在の状態 Ｓt と,その状態で取る行動 ａt ,行動によって得られた報酬 ｒt 次の状態 Ｓt+1 次の行動 ａt を使う.

行動を確率で決める.

---
@snap[north-west]
@css[inter-title](Q学習)
@snapend

強化学習の中で最も一般的に使われているアルゴリズム.

Q値を決定することで報酬の最大化を目指す.

---
@snap[north-west]
@css[finish-title](参考文献)
@snapend

[プログラマのための ディープラーニングのしくみがわかる数学入門](http://www.socym.co.jp/book/1179)

[これからの強化学習](https://www.morikita.co.jp/books/book/3034)

---
