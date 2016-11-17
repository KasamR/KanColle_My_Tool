# KanColle_My_Tool
艦これの制空値を自動で計算してくれます！

# 熟練度や改修値について
熟練度はすべてマックスが前提となっております．つまり最初から*制空値+25*されております.

改修値については，すべて*無改修*で計算されます．

# AC_Listについて
これは，自分の持っている艦載機を*装備させたい順*に上から書いてください．
順番としては以下の通りです．
```
入力艦載機名 表示艦載機名 対空値 種類 所持数 
Iwamoto 零式艦戦53型(岩本隊) 12 0 1
```
なお，種類は下記参照．

|||
|:--:|:--:|
|艦戦または水戦|0|
|水上爆撃機|1|
|艦攻または艦爆|2|


# 入力例

艦娘の入力を要求されるので，**英字**で**頭文字は大文字**で改二であれば**末尾に2**をつけて，さらに甲であれば**kou**を加えてください．
[KMS_List](KMS_List)を参照(先頭が入力用)
```
艦娘の入力(終了はf): Kaga
艦娘の入力(終了はf): Ryujo2
艦娘の入力(終了はf): Shokaku2kou
艦娘の入力(終了はf): f
```
装備を手動で装備するか，自動で装備するか選べます．

**0**を選択すると手動で装備を選びます．
入力する艦載機は[AC_List](AC_List)を参照してくだしあ．
```
[0: 手動装備 / 1:自動装備] 0
誰に? Kaga
何を? Reppu
どこに? 4

```

**1**を入力すると自動で装備してくれます．
目標制空値を入力すれば独自のアルゴリズムで最適な装備例を提案してくれます．
```
[0: 手動装備 / 1:自動装備] 1
目標制空値は? 200
```

終わるときは**y**を入力してください．
**n**を入力すると手動装備に移行します．
```
終わる?(y/n) y
```

# コンパイルについて
g++11でお願いします．

# 出力結果
出力結果はテキストファイルで出力されます．たぶん実行ファイルと同じ場所です．

*Wepons_List.txt*というファイル名で出力されます．